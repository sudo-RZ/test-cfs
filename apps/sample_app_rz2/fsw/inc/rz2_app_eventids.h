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
 * Define RZ2 App Events IDs
 */

#ifndef RZ2_APP_EVENTS_H
#define RZ2_APP_EVENTS_H

#define RZ2_APP_RESERVED_EID      0
#define RZ2_APP_INIT_INF_EID      1
#define RZ2_APP_CC_ERR_EID        2
#define RZ2_APP_NOOP_INF_EID      3
#define RZ2_APP_RESET_INF_EID     4
#define RZ2_APP_MID_ERR_EID       5
#define RZ2_APP_CMD_LEN_ERR_EID   6
#define RZ2_APP_PIPE_ERR_EID      7
#define RZ2_APP_VALUE_INF_EID     8
#define RZ2_APP_CR_PIPE_ERR_EID   9
#define RZ2_APP_SUB_HK_ERR_EID    10
#define RZ2_APP_SUB_CMD_ERR_EID   11
#define RZ2_APP_TABLE_REG_ERR_EID 12
#define RZ2_APP_SUB_RZ1_ERR_EID   13

/* COMMS RZ1<->RZ2 (opcional):
** Si se agregan eventos nuevos para la comunicación entre apps (ej: error
** al suscribirse al mensaje de RZ1, o evento informativo al recibir el
** dato), agregar acá el próximo ID consecutivo, por ejemplo:
**   #define RZ2_APP_SUB_RZ1_ERR_EID 13
*/

#endif /* RZ2_APP_EVENTS_H */
