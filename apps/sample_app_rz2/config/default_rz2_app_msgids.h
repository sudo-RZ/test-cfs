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
 *   RZ2_APP Application Message IDs
 */
#ifndef DEFAULT_RZ2_APP_MSGIDS_H
#define DEFAULT_RZ2_APP_MSGIDS_H

#include "cfe_core_api_base_msgids.h"
#include "rz2_app_msgid_values.h"

#define RZ2_APP_CMD_MID     RZ2_APP_CMD_PLATFORM_MIDVAL(CMD)
#define RZ2_APP_SEND_HK_MID RZ2_APP_CMD_PLATFORM_MIDVAL(SEND_HK)
#define RZ2_APP_HK_TLM_MID  RZ2_APP_TLM_PLATFORM_MIDVAL(HK_TLM)
#define RZ2_APP_DATA_TLM_MID RZ2_APP_TLM_PLATFORM_MIDVAL(DATA)

/* COMMS RZ1<->RZ2 (paso 2/5):
** Este es el Message ID (MID) real que se usa en el código C para
** suscribirse (CFE_SB_Subscribe) y transmitir (CFE_SB_TransmitMsg) por el
** Software Bus. Se construye a partir del topic id definido en el paso 1.
** Si RZ2 va a PUBLICAR el dato hacia RZ1, usar TLM_PLATFORM_MIDVAL (como
** RZ2_APP_HK_TLM_MID); si en cambio RZ1 le va a mandar un comando a RZ2,
** usar CMD_PLATFORM_MIDVAL (como RZ2_APP_CMD_MID). Ejemplo:
**
**   #define RZ2_APP_DATA_TLM_MID RZ2_APP_TLM_PLATFORM_MIDVAL(DATA)
**
** rz1_app deberá incluir este header (rz2_app_msgids.h) para poder
** suscribirse a RZ2_APP_DATA_TLM_MID en su propio Init().
*/

#endif
