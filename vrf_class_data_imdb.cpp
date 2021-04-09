
#include <vector>
#include <map>

#include "imdb.hpp"
#include "vrf_class_data_imdb.hpp"

#include "db_vrf_class_data.h"

using namespace std;
using namespace imdb;

template<>
FieldFactoriesType VRF_CLASS_DATA_IMDB_TABLE::fields_factories = {
    new FieldFactory<Field<uint32_t>>("table_id", 0, 0, sizeof(uint32_t)),
    new FieldFactory<Field<uint32_t>>("producer_pid", 1, 4, sizeof(uint32_t)),
    new FieldFactory<Field<uint32_t>>("vr_id", 2, 8, sizeof(uint32_t)),
    new FieldFactory<Field<uint32_t>>("vrf_index", 3, 12, sizeof(uint32_t)),
    new FieldFactory<Field<uint32_t>>("topology_id", 4, 16, sizeof(uint32_t)),
    new FieldFactory<Field<uint32_t>>("vrf_state", 5, 20, sizeof(uint32_t)),
    new FieldFactory<Field<uint8_t>>("vrf_data_machine", 6, 24, sizeof(uint8_t)),
    new FieldFactory<Field<uint32_t>>("vrf_state_version", 7, 25, sizeof(uint32_t)),
    new FieldFactory<Field<uint32_t>>("vrf_data_version", 8, 29, sizeof(uint32_t)),
    new FieldFactory<Field<uint32_t>>("smooth_flag", 9, 33, sizeof(uint32_t)),
};

template<>
map<int, FieldFactoriesType> VRF_CLASS_DATA_IMDB_TABLE::indexes_factories ={
    {DB_VRF_CLASS_DATA_VRF_CLASS_DATA_KEY_ID, 
    {new FieldFactory<Field<uint32_t>>("table_id", 0, 0, sizeof(uint32_t)),
     new FieldFactory<Field<uint32_t>>("producer_pid", 1, 4, sizeof(uint32_t)),
     new FieldFactory<Field<uint32_t>>("vr_id", 2, 8, sizeof(uint32_t)),
     new FieldFactory<Field<uint32_t>>("vrf_index", 3, 12, sizeof(uint32_t))
    }},
    {DB_VRF_CLASS_DATA_LOCALHASH_KEY_ID, 
    {new FieldFactory<Field<uint32_t>>("table_id", 0, 0, sizeof(uint32_t)),
     new FieldFactory<Field<uint32_t>>("producer_pid", 1, 4, sizeof(uint32_t))
    }}
};

template<>
map<int, vector<int>> VRF_CLASS_DATA_IMDB_TABLE::indexes_poses = {
    {DB_VRF_CLASS_DATA_VRF_CLASS_DATA_KEY_ID, {0, 1, 2, 3}},
    {DB_VRF_CLASS_DATA_LOCALHASH_KEY_ID, {0, 1}}
};

template<>
map<IndexType, TableBase*, IndexCompare> VRF_CLASS_DATA_IMDB_TABLE::primary_index_db = {};

template<>
map<int, IndexDbType> VRF_CLASS_DATA_IMDB_TABLE::index_dbs = {};

template<>
int VRF_CLASS_DATA_IMDB_TABLE::primary_key_id = DB_VRF_CLASS_DATA_VRF_CLASS_DATA_KEY_ID;

int db_create_vrf_class_data_obj(db_object_type object_type, db_conn_type conn_type, db_object* object)
{
    *object = new VRF_CLASS_DATA_IMDB_TABLE;
    return 0;
}

int db_set_vrf_class_data_table_id(db_object object, uint32_t field_table_id)
{
    auto table = *((VRF_CLASS_DATA_IMDB_TABLE *)object);
    table["table_id"] = field_table_id;
    return 0;
}

int db_set_vrf_class_data_producer_pid(db_object object, uint32_t field_producer_pid)
{
    auto table = *((VRF_CLASS_DATA_IMDB_TABLE *)object);
    table["producer_pid"] = field_producer_pid;
    return 0;
}

int db_set_vrf_class_data_topology_id(db_object object, uint8_t field_topology_id)
{
    auto table = *((VRF_CLASS_DATA_IMDB_TABLE *)object);
    table["topology_id"] = field_topology_id;
    return 0;
}

int db_get_vrf_class_data_table_id(db_object object, uint32_t* field_table_id)
{
    auto table = *((VRF_CLASS_DATA_IMDB_TABLE *)object);
    FieldBase &field = table["table_id"];
    return field.value((void *)field_table_id);
}
