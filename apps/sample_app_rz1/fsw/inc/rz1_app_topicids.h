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
 *   RZ1_APP Application Topic IDs
 */
#ifndef RZ1_APP_TOPICIDS_H
#define RZ1_APP_TOPICIDS_H

#include "rz1_app_topicid_values.h"

#define RZ1_APP_MISSION_CMD_TOPICID             RZ1_APP_MISSION_TIDVAL(CMD)
#define DEFAULT_RZ1_APP_MISSION_CMD_TOPICID     0x87

#define RZ1_APP_MISSION_SEND_HK_TOPICID         RZ1_APP_MISSION_TIDVAL(SEND_HK)
#define DEFAULT_RZ1_APP_MISSION_SEND_HK_TOPICID 0x88

#define RZ1_APP_MISSION_HK_TLM_TOPICID          RZ1_APP_MISSION_TIDVAL(HK_TLM)
#define DEFAULT_RZ1_APP_MISSION_HK_TLM_TOPICID  0x88

#define RZ1_APP_MISSION_DATA_TOPICID         RZ1_APP_MISSION_TIDVAL(DATA)
#define DEFAULT_RZ1_APP_MISSION_DATA_TOPICID 0x89   // no repetir 0x87/0x88 ya usados


/* COMMS RZ1<->RZ2 (paso 1/5):
** Cada mensaje que viaja por el Software Bus necesita un "topic id" propio
** y único dentro de la misión (no puede repetir el valor 0x87/0x88 usados arriba).
** Para crear el mensaje que RZ1 le mandará a RZ2 (o viceversa), agregar aquí
** un par de defines igual a los de arriba, por ejemplo:
**
**   #define RZ1_APP_MISSION_DATA_TOPICID         RZ1_APP_MISSION_TIDVAL(DATA)
**   #define DEFAULT_RZ1_APP_MISSION_DATA_TOPICID 0x89
**
** El nombre entre paréntesis de TIDVAL(...) (aquí "DATA") debe coincidir con
** el sufijo que se use luego en rz1_app_msgids.h (paso 2/5).
*/

#endif
