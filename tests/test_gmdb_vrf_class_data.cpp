#include "gtest/gtest.h"

#include "gmdb_vrf_class_data.h"

TEST(FieldSet, set_field)
{
    db_object obj;
    uint32_t table_id = 0;
    int ret = db_create_vrf_class_data_obj(0, 0, &obj);
    EXPECT_EQ(ret, 0);
    
    db_set_vrf_class_data_table_id(obj, 1001);
    db_get_vrf_class_data_table_id(obj, &table_id);
    EXPECT_EQ(table_id, 1001);
    
    db_set_vrf_class_data_table_id(obj, 100001);
    db_get_vrf_class_data_table_id(obj, &table_id);
    EXPECT_EQ(table_id, 100001);
}

TEST(TableSave, save_ok)
{
    db_object obj;
    int ret = db_create_vrf_class_data_obj(0, 0, &obj);
    EXPECT_EQ(ret, 0);
    
    db_set_vrf_class_data_table_id(obj, 100);
    EXPECT_EQ(0, db_write_obj(obj));
    
    ret = db_create_vrf_class_data_obj(0, 0, &obj);
    EXPECT_EQ(ret, 0);
    
    db_set_vrf_class_data_table_id(obj, 200);
    EXPECT_EQ(0, db_write_obj(obj));
}