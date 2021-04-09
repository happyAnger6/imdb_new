/*
* Copyright (c) Huawei Technologies Co., Ltd. 2012-2021. All rights reserved.
* Description:
* Author:
* Create:
*/

#ifndef __DB_VRF_CLASS_DATA_H_
#define __DB_VRF_CLASS_DATA_H_

#include <stdint.h>
#include "db_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* All the Index ID define as following  */
#define DB_VRF_CLASS_DATA_VRF_CLASS_DATA_KEY_ID 1
#define DB_VRF_CLASS_DATA_LOCALHASH_KEY_ID 265

/* struct definition */
/* struct definition of vrf_class_data */
#pragma pack(1)
typedef struct tagvrf_class_data_struct_t {
    uint32_t table_id;
    uint32_t producer_pid;
    uint32_t vr_id;
    uint32_t vrf_index;
    uint32_t topology_id;
    uint32_t vrf_state;
    uint8_t vrf_data_machine;
    uint32_t vrf_state_version;
    uint32_t vrf_data_version;
    uint32_t smooth_flag;
} vrf_class_data_struct_t;
#pragma pack()

/* key struct definition of vrf_class_data */
#pragma pack(1)
typedef struct tagdb_vrf_class_data {
    uint32_t  table_id;
    uint32_t  producer_pid;
    uint32_t  vr_id;
    uint32_t  vrf_index;
} db_vrf_class_data_key_t;

typedef struct tagdb_vrf_class_data_localhash_key {
    uint32_t  table_id;
    uint32_t  producer_pid;
} db_vrf_class_data_localhash_key_t;

#pragma pack()

/* common operation */
int db_create_vrf_class_data_obj(db_object_type object_type, db_conn_type conn_type, db_object* object);

int db_create_vrf_class_data_obj_specific_conn(db_object_type object_type, db_connect_t conn, db_object* object);

void db_release_vrf_class_data_object(db_object object);

int db_reset_vrf_class_data_object(db_object object, db_object_type object_type);

int db_reset_vrf_class_data_batch_object(db_object object, db_object_type object_type);

int db_set_vrf_class_data_all_fields(db_object object, void* data, uint32_t length);

/* Node vrf_class_data's Field Enum Type */
typedef enum tagvrf_class_data_field_type {
    VRF_CLASS_DATA_TABLE_ID_FIELD_ID = 0,
    VRF_CLASS_DATA_PRODUCER_PID_FIELD_ID = 1,
    VRF_CLASS_DATA_VR_ID_FIELD_ID = 2,
    VRF_CLASS_DATA_VRF_INDEX_FIELD_ID = 3,
    VRF_CLASS_DATA_TOPOLOGY_ID_FIELD_ID = 4,
    VRF_CLASS_DATA_VRF_STATE_FIELD_ID = 5,
    VRF_CLASS_DATA_VRF_DATA_MACHINE_FIELD_ID = 6,
    VRF_CLASS_DATA_VRF_STATE_VERSION_FIELD_ID = 7,
    VRF_CLASS_DATA_VRF_DATA_VERSION_FIELD_ID = 8,
    VRF_CLASS_DATA_SMOOTH_FLAG_FIELD_ID = 9,
} vrf_class_data_field_type_e;

/* Node vrf_class_data's set function. */
/* Comment: vrf数据 */
/* Comment: vrpv8中的fes table_id */
int db_set_vrf_class_data_table_id(db_object object, uint32_t field_table_id);
/* Comment: table对应的生产者Pid */
int db_set_vrf_class_data_producer_pid(db_object object, uint32_t field_producer_pid);
/* Comment: VR ID */
int db_set_vrf_class_data_vr_id(db_object object, uint32_t field_vr_id);
/* Comment: VRF ID */
int db_set_vrf_class_data_vrf_index(db_object object, uint32_t field_vrf_index);
/* Comment: 拓扑ID */
int db_set_vrf_class_data_topology_id(db_object object, uint32_t field_topology_id);
/* Comment: 表状态 */
int db_set_vrf_class_data_vrf_state(db_object object, uint32_t field_vrf_state);
/* Comment: 此Pid+tableid+vrid+vrfid下的状态机 */
int db_set_vrf_class_data_vrf_data_machine(db_object object, uint8_t field_vrf_data_machine);
/* Comment: 此Pid和tableId下的VrfState版本号 */
int db_set_vrf_class_data_vrf_state_version(db_object object, uint32_t field_vrf_state_version);
/* Comment: 此Pid+tableId+vrid+Vrf下的VrfData版本号 */
int db_set_vrf_class_data_vrf_data_version(db_object object, uint32_t field_vrf_data_version);
/* Comment: 此Pid+tableId+vrid+Vrf下数据是否平滑结束 */
int db_set_vrf_class_data_smooth_flag(db_object object, uint32_t field_smooth_flag);

/* Node vrf_class_data's get function. */
/* Comment: vrf数据 */
/* Comment: vrpv8中的fes table_id */
int db_get_vrf_class_data_table_id(db_object object, uint32_t* field_table_id);
/* Comment: table对应的生产者Pid */
int db_get_vrf_class_data_producer_pid(db_object object, uint32_t* field_producer_pid);
/* Comment: VR ID */
int db_get_vrf_class_data_vr_id(db_object object, uint32_t* field_vr_id);
/* Comment: VRF ID */
int db_get_vrf_class_data_vrf_index(db_object object, uint32_t* field_vrf_index);
/* Comment: 拓扑ID */
int db_get_vrf_class_data_topology_id(db_object object, uint32_t* field_topology_id);
/* Comment: 表状态 */
int db_get_vrf_class_data_vrf_state(db_object object, uint32_t* field_vrf_state);
/* Comment: 此Pid+tableid+vrid+vrfid下的状态机 */
int db_get_vrf_class_data_vrf_data_machine(db_object object, uint8_t* field_vrf_data_machine);
/* Comment: 此Pid和tableId下的VrfState版本号 */
int db_get_vrf_class_data_vrf_state_version(db_object object, uint32_t* field_vrf_state_version);
/* Comment: 此Pid+tableId+vrid+Vrf下的VrfData版本号 */
int db_get_vrf_class_data_vrf_data_version(db_object object, uint32_t* field_vrf_data_version);
/* Comment: 此Pid+tableId+vrid+Vrf下数据是否平滑结束 */
int db_get_vrf_class_data_smooth_flag(db_object object, uint32_t* field_smooth_flag);

int db_get_vrf_class_data_all_fields(db_object object, void* data, uint32_t length);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
