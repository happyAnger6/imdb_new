#include "imdb.h"
#include "gmdb_wrapper.h"

using namespace imdb;

int db_write_obj(db_object obj)
{
    return ((TableBase *)obj)->save();
}

int db_update_obj(db_object obj, db_key_info_t* key_info, void* key_data)
{
    return ((TableBase *)obj)->save();
}

extern int db_read_obj_with_buf(db_object obj, 
        db_key_info_t* key_info, void* key_data, void* buf, uint32_t buf_len)
{
    TableBase *pTableBase = ((TableBase *)obj);
    TableIndex index = pTableBase->create_index(key_info->index_id, key_data);
    pTableBase->read_obj(index, buf, buf_len);
}

int db_set_key_data(db_object obj, db_key_info_t* key_info, void* key_data)
{

}
