#ifndef _GMDB_WRAPPER_H
#define _GMDB_WRAPPER_H

#include <cstdint>

using db_object = void*;
using db_object_type = uint32_t;
using db_conn_type = uint32_t;
using db_key_info_t = int;

extern int db_write_obj(db_object obj);
extern int db_update_obj(db_object obj, db_key_info_t* key_info, void* key_data);

#endif