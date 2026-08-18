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
 * @file
 *
 * Main header file for the Sample application
 */

#ifndef RZ2_APP_H
#define RZ2_APP_H

/*
** Required header files.
*/
#include "cfe.h"
#include "cfe_config.h"

#include "rz2_app_mission_cfg.h"
#include "rz2_app_platform_cfg.h"

#include "rz2_app_perfids.h"
#include "rz2_app_msgids.h"
#include "rz2_app_msg.h"

/************************************************************************
** Type Definitions
*************************************************************************/

/*
** Global Data
*/
typedef struct
{
    /*
    ** Command interface counters...
    */
    uint8 CmdCounter;
    uint8 ErrCounter;

    /*
    ** Housekeeping telemetry packet...
    */
    RZ2_APP_HkTlm_t HkTlm;

    /*
    ** Run Status variable used in the main processing loop
    */
    uint32 RunStatus;

    /*
    ** Operational data (not reported in housekeeping)...
    */
    CFE_SB_PipeId_t CommandPipe;

    /* COMMS RZ1<->RZ2:
    ** Si RZ2 va a RECIBIR mensajes de RZ1, se puede reusar CommandPipe
    ** (suscribiendo el nuevo MID ahí, ver rz2_app.c) o crear un pipe
    ** dedicado agregando otro campo CFE_SB_PipeId_t aquí, ej:
    **   CFE_SB_PipeId_t Rz1DataPipe;
    ** Si en cambio RZ2 solo PUBLICA datos hacia RZ1, no hace falta pipe
    ** nuevo: alcanza con CFE_MSG_Init + CFE_SB_TransmitMsg (ver rz2_app.c
    ** y rz2_app_cmds.c).
    */

    CFE_TBL_Handle_t TblHandles[RZ2_APP_PLATFORM_NUMBER_OF_TABLES];
    RZ2_APP_DataTlm_t DataTlm;
} RZ2_APP_Data_t;

/*
** Global data structure
*/
extern RZ2_APP_Data_t RZ2_APP_Data;

/****************************************************************************/
/*
** Local function prototypes.
**
** Note: Except for the entry point (RZ2_APP_Main), these
**       functions are not called from any other source module.
*/
void         RZ2_APP_Main(void);
CFE_Status_t RZ2_APP_Init(void);

#endif /* RZ2_APP_H */
