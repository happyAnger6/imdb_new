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

int db_read_obj(db_object obj, db_key_info_t* key_info, void* key_data)
{
    return 0;
}

int db_set_key_data(db_object obj, db_key_info_t* key_info, void* key_data)
{

}
