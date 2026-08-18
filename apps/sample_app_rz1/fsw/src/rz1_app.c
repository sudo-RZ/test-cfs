/************************************************************************
 * NASA Docket No. GSC-19,200-1, and identified as "cFS Draco"
 *
 * Copyright (c) 2023 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

#include "rz1_app.h"
#include "rz1_app_cmds.h"
#include "rz1_app_utils.h"
#include "rz1_app_eventids.h"
#include "rz1_app_dispatch.h"
#include "rz1_app_tbl.h"
#include "rz1_app_version.h"

/* COMMS RZ1<->RZ2: para suscribirse al MID que publica RZ2 hace falta
** conocer su definición, que vive en el header de mensajes de RZ2. */
#include "rz2_app_msgids.h"

RZ1_APP_Data_t RZ1_APP_Data;


void RZ1_APP_Main(void)
{
  CFE_Status_t     status;
  CFE_SB_Buffer_t *SBBufPtr;

  status = RZ1_APP_Init();

  if (status != CFE_SUCCESS){
    RZ1_APP_Data.RunStatus = CFE_ES_RunStatus_APP_ERROR;
  }

  while (CFE_ES_RunLoop(&RZ1_APP_Data.RunStatus) == true) {
    CFE_ES_PerfLogExit(RZ1_APP_PERF_ID);

    printf("HOLAAA1\n");

    status = CFE_SB_ReceiveBuffer(&SBBufPtr, RZ1_APP_Data.CommandPipe, 5000);

    if (status == CFE_SUCCESS) {
      /* COMMS RZ1<->RZ2:
      ** Los mensajes recibidos por el pipe (comandos, HK request, y el
      ** mensaje de RZ2 si se suscribe con el mismo pipe) se rutean acá.
      ** El "case" para el nuevo mensaje entrante va dentro de
      ** RZ1_APP_TaskPipe(), en rz1_app_dispatch.c.
      */
      RZ1_APP_TaskPipe(SBBufPtr);
    }

    /* COMMS RZ1<->RZ2: RZ1 publica el contador cada vuelta del loop */
    RZ1_APP_Data.DataTlm.Payload.Counter++;
    CFE_SB_TimeStampMsg(CFE_MSG_PTR(RZ1_APP_Data.DataTlm.TelemetryHeader));
    CFE_SB_TransmitMsg(CFE_MSG_PTR(RZ1_APP_Data.DataTlm.TelemetryHeader), true);
    printf("RZ1 envio Counter=%u\n", (unsigned int)RZ1_APP_Data.DataTlm.Payload.Counter);

  }

    CFE_ES_ExitApp(RZ1_APP_Data.RunStatus);
  }


CFE_Status_t RZ1_APP_Init(void)
{
    CFE_Status_t status;
    char         VersionString[RZ1_APP_CFG_MAX_VERSION_STR_LEN];

    memset(&RZ1_APP_Data, 0, sizeof(RZ1_APP_Data));

    RZ1_APP_Data.RunStatus = CFE_ES_RunStatus_APP_RUN;

    status = CFE_EVS_Register(NULL, 0, CFE_EVS_EventFilter_BINARY);
    if (status != CFE_SUCCESS) {
        CFE_ES_WriteToSysLog("RZ1 App: Error Registering Events, RC = 0x%08lX\n", (unsigned long)status);
    }
    else { 
        CFE_MSG_Init(CFE_MSG_PTR(RZ1_APP_Data.HkTlm.TelemetryHeader), CFE_SB_ValueToMsgId(RZ1_APP_HK_TLM_MID),
                     sizeof(RZ1_APP_Data.HkTlm));

        CFE_MSG_Init(CFE_MSG_PTR(RZ1_APP_Data.DataTlm.TelemetryHeader),
             CFE_SB_ValueToMsgId(RZ1_APP_DATA_TLM_MID),
             sizeof(RZ1_APP_Data.DataTlm));


        /* COMMS RZ1<->RZ2 (si RZ1 PUBLICA un mensaje propio hacia RZ2):
        ** inicializar acá el header del nuevo mensaje igual que arriba,
        ** usando el MID definido en rz1_app_msgids.h, ej:
        **   CFE_MSG_Init(CFE_MSG_PTR(RZ1_APP_Data.DataTlm.TelemetryHeader),
        **                CFE_SB_ValueToMsgId(RZ1_APP_DATA_TLM_MID),
        **                sizeof(RZ1_APP_Data.DataTlm));
        */

        status = CFE_SB_CreatePipe(&RZ1_APP_Data.CommandPipe, RZ1_APP_PLATFORM_PIPE_DEPTH,
                                   RZ1_APP_PLATFORM_PIPE_NAME);

        if (status != CFE_SUCCESS){
            CFE_EVS_SendEvent(RZ1_APP_CR_PIPE_ERR_EID, CFE_EVS_EventType_ERROR,
                              "RZ1 App: Error creating SB Command Pipe, RC = 0x%08lX", (unsigned long)status);
        }
    }

    if (status == CFE_SUCCESS){
        status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(RZ1_APP_SEND_HK_MID), RZ1_APP_Data.CommandPipe);
        if (status != CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(RZ1_APP_SUB_HK_ERR_EID, CFE_EVS_EventType_ERROR,
                              "RZ1 App: Error Subscribing to HK request, RC = 0x%08lX", (unsigned long)status);
        }
    }

    if (status == CFE_SUCCESS)
    {
        /*
        ** Subscribe to ground command packets
        */
        status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(RZ1_APP_CMD_MID), RZ1_APP_Data.CommandPipe);
        if (status != CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(RZ1_APP_SUB_CMD_ERR_EID, CFE_EVS_EventType_ERROR,
                              "RZ1 App: Error Subscribing to Commands, RC = 0x%08lX", (unsigned long)status);
        }
    }

    if (status == CFE_SUCCESS)
    {
        /* COMMS RZ1<->RZ2: suscripción al mensaje que publica RZ2 */
        status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(RZ2_APP_DATA_TLM_MID), RZ1_APP_Data.CommandPipe);
        if (status != CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(RZ1_APP_SUB_RZ2_ERR_EID, CFE_EVS_EventType_ERROR,
                              "RZ1 App: Error Subscribing to RZ2 Data, RC = 0x%08lX", (unsigned long)status);
        }
    }

    if (status == CFE_SUCCESS)
    {
        /*
        ** Register Example Table(s)
        */
        status = CFE_TBL_Register(&RZ1_APP_Data.TblHandles[0], "ExampleTable", sizeof(RZ1_APP_ExampleTable_t),
                                  CFE_TBL_OPT_DEFAULT, RZ1_APP_TblValidationFunc);
        if (status != CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(RZ1_APP_TABLE_REG_ERR_EID, CFE_EVS_EventType_ERROR,
                              "RZ1 App: Error Registering Example Table, RC = 0x%08lX", (unsigned long)status);
        }
        else
        {
            status = CFE_TBL_Load(RZ1_APP_Data.TblHandles[0], CFE_TBL_SRC_FILE, RZ1_APP_PLATFORM_TABLE_FILE);
        }

        CFE_Config_GetVersionString(VersionString, RZ1_APP_CFG_MAX_VERSION_STR_LEN, "RZ1 App", RZ1_APP_VERSION,
                                    RZ1_APP_BUILD_CODENAME, RZ1_APP_LAST_OFFICIAL);

        CFE_EVS_SendEvent(RZ1_APP_INIT_INF_EID, CFE_EVS_EventType_INFORMATION, "RZ1 App Initialized.%s",
                          VersionString);
    }

    return status;
}
