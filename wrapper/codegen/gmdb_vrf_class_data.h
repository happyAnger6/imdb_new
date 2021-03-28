#ifndef _GMDB_VRF_CLASS_DATA_H
#define _GMDB_VRF_CLASS_DATA_H

#include "gmdb_wrapper.h"

extern int db_create_vrf_class_data_obj(db_object_type object_type, db_conn_type conn_type, db_object* object);

extern int db_set_vrf_class_data_table_id(db_object object, uint32_t field_table_id);

extern int db_set_vrf_class_data_producer_pid(db_object object, uint32_t field_producer_pid);

extern int db_set_vrf_class_data_topology_id(db_object object, uint8_t field_topology_id);

extern int db_get_vrf_class_data_table_id(db_object object, uint32_t* field_table_id);

#endif