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
 *   RZ2_APP Application Topic IDs
 */
#ifndef RZ2_APP_TOPICIDS_H
#define RZ2_APP_TOPICIDS_H

#include "rz2_app_topicid_values.h"

#define RZ2_APP_MISSION_CMD_TOPICID             RZ2_APP_MISSION_TIDVAL(CMD)
#define DEFAULT_RZ2_APP_MISSION_CMD_TOPICID     0x89

#define RZ2_APP_MISSION_SEND_HK_TOPICID         RZ2_APP_MISSION_TIDVAL(SEND_HK)
#define DEFAULT_RZ2_APP_MISSION_SEND_HK_TOPICID 0x8A

#define RZ2_APP_MISSION_HK_TLM_TOPICID          RZ2_APP_MISSION_TIDVAL(HK_TLM)
#define DEFAULT_RZ2_APP_MISSION_HK_TLM_TOPICID  0x8A

#define RZ2_APP_MISSION_DATA_TOPICID         RZ2_APP_MISSION_TIDVAL(DATA)
#define DEFAULT_RZ2_APP_MISSION_DATA_TOPICID 0x8B

/* COMMS RZ1<->RZ2 (paso 1/5):
** Cada mensaje que viaja por el Software Bus necesita un "topic id" propio
** y único dentro de la misión (no puede repetir 0x89/0x8A usados arriba,
** ni los 0x87/0x88 ya usados por rz1_app_topicids.h). Para crear el
** mensaje que RZ2 le mandará a RZ1 (o viceversa), agregar aquí un par de
** defines igual a los de arriba, por ejemplo:
**
**   #define RZ2_APP_MISSION_DATA_TOPICID         RZ2_APP_MISSION_TIDVAL(DATA)
**   #define DEFAULT_RZ2_APP_MISSION_DATA_TOPICID 0x8B
**
** El nombre entre paréntesis de TIDVAL(...) (aquí "DATA") debe coincidir con
** el sufijo que se use luego en rz2_app_msgids.h (paso 2/5).
*/

#endif
