#include "imdb.h"

#include "gmdb_wrapper.h"
#include "gmdb_vrf_class_data.h"

using namespace imdb;

class VRF_CLASS_DATA : public FieldT {
};

using VRF_CLASS_DATA_IMDB_TABLE = Table<5, 4, VRF_CLASS_DATA>;

template<>
std::array<FieldFactoryBase*, 5> VRF_CLASS_DATA_IMDB_TABLE::fields = {
    new FieldFactory<0, 0, sizeof(uint32_t), uint32_t>,
    new FieldFactory<1, 4, sizeof(uint32_t), uint32_t>,
    new FieldFactory<2, 8, sizeof(uint32_t), uint32_t>,
    new FieldFactory<3, 12, sizeof(uint32_t), uint32_t>,
    new FieldFactory<4, 16, sizeof(uint8_t), uint8_t>,
};

template<>
std::array<int, 4> VRF_CLASS_DATA_IMDB_TABLE::primary_keys = {0, 1, 2, 3};

int db_create_vrf_class_data_obj(db_object_type object_type, db_conn_type conn_type, db_object* object)
{
    *object = new VRF_CLASS_DATA_IMDB_TABLE;
    return 0;
}

int db_set_vrf_class_data_table_id(db_object object, uint32_t field_table_id)
{
    (*(VRF_CLASS_DATA_IMDB_TABLE *)object)[0] = field_table_id;
    return 0;
}

int db_set_vrf_class_data_producer_pid(db_object object, uint32_t field_producer_pid)
{
    (*(VRF_CLASS_DATA_IMDB_TABLE *)object)[1] = field_producer_pid;
    return 0;
}

int db_set_vrf_class_data_topology_id(db_object object, uint8_t field_topology_id)
{
    (*(VRF_CLASS_DATA_IMDB_TABLE *)object)[4] = field_topology_id;
    return 0;
}

int db_get_vrf_class_data_table_id(db_object object, uint32_t* field_table_id)
{
    const FieldBase &field = (*((const VRF_CLASS_DATA_IMDB_TABLE *)object))[0];
    *field_table_id = *((uint32_t *)field.value());
    return 0;
}