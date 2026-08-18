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
 *   This file contains the prototypes for the RZ1 App Ground Command-handling functions
 */

#ifndef RZ1_APP_CMDS_H
#define RZ1_APP_CMDS_H

/*
** Required header files.
*/
#include "cfe_error.h"
#include "rz1_app_msg.h"

/* COMMS RZ1<->RZ2: para conocer el tipo RZ2_APP_DataTlm_t usado abajo */
#include "rz2_app_msg.h"

CFE_Status_t RZ1_APP_SendHkCmd(const RZ1_APP_SendHkCmd_t *Msg);
CFE_Status_t RZ1_APP_ResetCountersCmd(const RZ1_APP_ResetCountersCmd_t *Msg);
CFE_Status_t RZ1_APP_ProcessCmd(const RZ1_APP_ProcessCmd_t *Msg);
CFE_Status_t RZ1_APP_NoopCmd(const RZ1_APP_NoopCmd_t *Msg);
CFE_Status_t RZ1_APP_DisplayParamCmd(const RZ1_APP_DisplayParamCmd_t *Msg);
void         RZ1_APP_HandleRz2Data(const RZ2_APP_DataTlm_t *Msg);

#endif /* RZ1_APP_CMDS_H */
