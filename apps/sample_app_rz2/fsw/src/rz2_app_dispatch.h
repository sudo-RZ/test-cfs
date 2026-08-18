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
 * Main header file for the SAMPLE application
 */

#ifndef RZ2_APP_DISPATCH_H
#define RZ2_APP_DISPATCH_H

/*
** Required header files.
*/
#include "cfe.h"
#include "rz2_app_msg.h"

void RZ2_APP_TaskPipe(const CFE_SB_Buffer_t *SBBufPtr);
void RZ2_APP_ProcessGroundCommand(const CFE_SB_Buffer_t *SBBufPtr);
bool RZ2_APP_VerifyCmdLength(const CFE_MSG_Message_t *MsgPtr, size_t ExpectedLength);

/* COMMS RZ1<->RZ2: declarar acá el prototipo del handler nuevo que se
** llama desde RZ2_APP_TaskPipe() en rz2_app_dispatch.c, ej:
**   void RZ2_APP_HandleRz1Data(const RZ1_APP_DataTlm_t *Msg);
** (implementado en rz2_app_cmds.c, ver ese archivo)
*/

#endif /* RZ2_APP_DISPATCH_H */
