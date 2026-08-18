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
 *   Specification for the RZ1_APP command and telemetry
 *   message payload and constant definitions.
 */
#ifndef DEFAULT_RZ1_APP_MSGDEFS_H
#define DEFAULT_RZ1_APP_MSGDEFS_H

#include "common_types.h"
#include "rz1_app_fcncodes.h"

typedef struct RZ1_APP_DisplayParam_Payload
{
    uint32 ValU32;                                    /**< 32 bit unsigned integer value */
    int16  ValI16;                                    /**< 16 bit signed integer value */
    char   ValStr[RZ1_APP_MISSION_STRING_VAL_LEN]; /**< An example string */
} RZ1_APP_DisplayParam_Payload_t;

/*************************************************************************/
/*
** Type definition (RZ1 App housekeeping)
*/

typedef struct RZ1_APP_HkTlm_Payload
{
    uint8 CommandCounter;
    uint8 CommandErrorCounter;
    uint8 spare[2];
} RZ1_APP_HkTlm_Payload_t;

typedef struct RZ1_APP_Data_Payload
{
    uint32 Counter;
} RZ1_APP_Data_Payload_t;
// esta parte es la que define el payload del mensaje que RZ1 le va a mandar a RZ2 (o viceversa), siguiendo el mismo estilo que RZ1_APP_HkTlm_Payload_t de arriba. Se usa luego en rz1_app_msgstruct.h (paso 4/5) para armar el mensaje completo (header + payload).

/* COMMS RZ1<->RZ2 (paso 3/5):
** Acá va el struct con los DATOS que RZ1 le quiere mandar a RZ2 (o al revés),
** siguiendo el mismo estilo que RZ1_APP_HkTlm_Payload_t de arriba.
** Ejemplo:
**
**   typedef struct RZ1_APP_Data_Payload
**   {
**       uint32 SomeValue;
**   } RZ1_APP_Data_Payload_t;
**
** Este payload se usa luego en rz1_app_msgstruct.h (paso 4/5) para armar
** el mensaje completo (header + payload).
*/

#endif
