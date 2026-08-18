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

/**
 * \file
 *   This file contains the source code for the RZ1 App Ground Command-handling functions
 */

/*
** Include Files:
*/
#include "rz1_app.h"
#include "rz1_app_cmds.h"
#include "rz1_app_msgids.h"
#include "rz1_app_eventids.h"
#include "rz1_app_version.h"
#include "rz1_app_tbl.h"
#include "rz1_app_utils.h"
#include "rz1_app_msg.h"

/* The sample_lib module provides the SAMPLE_Function() prototype */
#include "sample_lib.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
CFE_Status_t RZ1_APP_SendHkCmd(const RZ1_APP_SendHkCmd_t *Msg)
{
    int i;

    /*
    ** Get command execution counters...
    */
    RZ1_APP_Data.HkTlm.Payload.CommandErrorCounter = RZ1_APP_Data.ErrCounter;
    RZ1_APP_Data.HkTlm.Payload.CommandCounter      = RZ1_APP_Data.CmdCounter;

    /*
    ** Send housekeeping telemetry packet...
    */
    CFE_SB_TimeStampMsg(CFE_MSG_PTR(RZ1_APP_Data.HkTlm.TelemetryHeader));
    CFE_SB_TransmitMsg(CFE_MSG_PTR(RZ1_APP_Data.HkTlm.TelemetryHeader), true);

    /* COMMS RZ1<->RZ2 (lado EMISOR): estas dos líneas de arriba son el
    ** patrón exacto para publicar cualquier mensaje por el Software Bus
    ** (mismo que usa apps/obc_hk en su AppMain). Para publicar el dato
    ** hacia RZ2 se llamaría igual, pero con el struct del payload nuevo:
    **   CFE_SB_TimeStampMsg(CFE_MSG_PTR(RZ1_APP_Data.DataTlm.TelemetryHeader));
    **   CFE_SB_TransmitMsg(CFE_MSG_PTR(RZ1_APP_Data.DataTlm.TelemetryHeader), true);
    */

    /*
    ** Manage any pending table loads, validations, etc.
    */
    for (i = 0; i < RZ1_APP_PLATFORM_NUMBER_OF_TABLES; i++)
    {
        CFE_TBL_Manage(RZ1_APP_Data.TblHandles[i]);
    }

    return CFE_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* SAMPLE NOOP commands                                                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
CFE_Status_t RZ1_APP_NoopCmd(const RZ1_APP_NoopCmd_t *Msg)
{
    RZ1_APP_Data.CmdCounter++;

    CFE_EVS_SendEvent(RZ1_APP_NOOP_INF_EID, CFE_EVS_EventType_INFORMATION, "SAMPLE: NOOP command %s",
                      RZ1_APP_VERSION);

    return CFE_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function resets all the global counter variables that are     */
/*         part of the task telemetry.                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
CFE_Status_t RZ1_APP_ResetCountersCmd(const RZ1_APP_ResetCountersCmd_t *Msg)
{
    RZ1_APP_Data.CmdCounter = 0;
    RZ1_APP_Data.ErrCounter = 0;

    CFE_EVS_SendEvent(RZ1_APP_RESET_INF_EID, CFE_EVS_EventType_INFORMATION, "SAMPLE: RESET command");

    return CFE_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function Process Ground Station Command                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
CFE_Status_t RZ1_APP_ProcessCmd(const RZ1_APP_ProcessCmd_t *Msg)
{
    CFE_Status_t               Status;
    void *                     TblAddr;
    RZ1_APP_ExampleTable_t *TblPtr;
    const char *               TableName = "RZ1_APP.ExampleTable";

    /* Sample Use of Example Table */
    RZ1_APP_Data.CmdCounter++;
    Status = CFE_TBL_GetAddress(&TblAddr, RZ1_APP_Data.TblHandles[0]);
    if (Status < CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("RZ1 App: Fail to get table address: 0x%08lx", (unsigned long)Status);
    }
    else
    {
        TblPtr = TblAddr;
        CFE_ES_WriteToSysLog("RZ1 App: Example Table Value 1: %d  Value 2: %d", TblPtr->Int1, TblPtr->Int2);

        RZ1_APP_GetCrc(TableName);

        Status = CFE_TBL_ReleaseAddress(RZ1_APP_Data.TblHandles[0]);
        if (Status != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("RZ1 App: Fail to release table address: 0x%08lx", (unsigned long)Status);
        }
        else
        {
            /* Invoke a function provided by RZ1_APP_LIB */
            SAMPLE_LIB_Function();
        }
    }

    return Status;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* A simple example command that displays a passed-in value                   */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
CFE_Status_t RZ1_APP_DisplayParamCmd(const RZ1_APP_DisplayParamCmd_t *Msg)
{
    RZ1_APP_Data.CmdCounter++;
    CFE_EVS_SendEvent(RZ1_APP_VALUE_INF_EID, CFE_EVS_EventType_INFORMATION,
                      "RZ1_APP: ValU32=%lu, ValI16=%d, ValStr=%s", (unsigned long)Msg->Payload.ValU32,
                      (int)Msg->Payload.ValI16, Msg->Payload.ValStr);

    return CFE_SUCCESS;
}

/* COMMS RZ1<->RZ2 (lado RECEPTOR): procesa el mensaje que llega de RZ2,
** llamado desde el "else if" agregado en rz1_app_dispatch.c. Mismo patrón
** que usa apps/telecom/fsw/src/telecom_app.c al recibir OBC_HK_TLM_MID.
*/
void RZ1_APP_HandleRz2Data(const RZ2_APP_DataTlm_t *Msg)
{
    printf("RZ1 recibio de RZ2: Counter=%u\n", (unsigned int)Msg->Payload.Counter);
}
