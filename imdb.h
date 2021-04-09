#ifndef _IMDB_H
#define _IMDB_H

#include <cstdint>
#include <cstring>
#include <cassert>

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>
#include <map>
#include <memory>

#include "gm_errno.h"
#include "db_wrapper.h"

namespace imdb {

class FieldBase{
public:
    virtual const char *name() const = 0;

    virtual int operator=(void *data) { return 0; }
    virtual int operator=(uint32_t data) { return 0; }
    virtual int operator=(uint16_t data) { return 0; }
    virtual int operator=(uint8_t data) { return 0; }
    virtual int operator=(uint64_t data) { return 0; }

    virtual bool le(const FieldBase *other) { return false; }
    virtual bool eq(const FieldBase *other) { return false; }

    virtual FieldBase* clone() = 0;

    virtual int value(void *out_data) = 0;
    virtual int set_data(void *data) = 0;
    virtual int get_data(void *data, uint32_t len) = 0;
    virtual bool is_update() { return false; };
};

class FieldFactoryBase {
public:
    virtual FieldBase* CreateField() = 0;
};

/*  Factory create a Field
    T should be a Field type, for example Field<uint32_t>.    
    Example:
        FieldFactory<Field<uint32_t>>
*/
template<typename T> /*T should be Field<T> type, for example Field<uint32_t>.*/
class FieldFactory : public FieldFactoryBase{
public:
    const char* name;
    int pos;
    int offset;
    int len;

    FieldFactory(const char *name, int pos, int offset, int len) : name(name), 
                    pos(pos), offset(offset), len(len) {}
    FieldBase* CreateField()
    {
        return new T(this);
    }
};

template<typename T>
class Field :public FieldBase
{
    T _data;
    bool _is_update = false;
    FieldFactoryBase *_pFactory;

    using FieldTFactory = FieldFactory<T>;
    using FieldT = Field<T>;
public:

    Field(FieldFactoryBase *pFactory) : _pFactory(pFactory) {}

    Field(const Field<T> &other)
    {
        _data = other._data;
        _pFactory = other._pFactory;
    }

    FieldBase* clone() {
        Field<T> *pNewField = static_cast<Field<T>*>(_pFactory->CreateField());
        pNewField->_data = _data;
        pNewField->_is_update = _is_update;
        return pNewField;
    }

    int set_data(void *data)
    {
        FieldTFactory *pFactory = (FieldTFactory *)_pFactory;
        memcpy(&_data, (char*)data + pFactory->offset, pFactory->len);
        _is_update = true;
        return 0;
    }
    
    int get_data(void *data, uint32_t len)
    {
        FieldTFactory *pFactory = (FieldTFactory *)_pFactory;
        memcpy((char*)data + pFactory->offset, &_data, pFactory->len);
        return 0;
    }

    int operator=(void *data)
    {
        _data = *((T *)data);
        _is_update = true;
        return 0;
    }
    
    int operator=(uint32_t data)
    {
        _data = (uint32_t)data;
        _is_update = true;
        return 0;
    }
    
    int operator=(uint16_t data)
    {
        _data = (uint16_t)data;
        _is_update = true;
        return 0;
    }

    int operator=(uint8_t data)
    {
        _data = (uint8_t)data;
        _is_update = true;
        return 0;
    }
    
    int operator=(uint64_t data)
    {
        _data = (uint64_t)data;
        _is_update = true;
        return 0;
    }

    bool le(const FieldBase *other) { 
        return _data < ((Field<T> *)other)->_data;
    }
    
    bool eq(const FieldBase *other) { 
        return _data == ((Field<T> *)other)->_data;
    }

    int value(void *out_data)
    {
        FieldTFactory *pFactory = (FieldTFactory *)_pFactory;
        memcpy(out_data, &_data, pFactory->len);
        return 0;
    }

    const char *name() const
    {
        FieldTFactory *pFactory = (FieldTFactory *)_pFactory;
        return pFactory->name;
    }
    
    bool is_update() { 
        return _is_update; 
    }
};

using FieldsType = std::vector<FieldBase*>;

class TableBase : public FieldBase{
public:
    virtual FieldBase& operator[](const char* name) = 0;
    virtual int save() = 0;
    virtual int read_obj(db_key_info_t *key, void* key_data, void *buf, uint32_t len) = 0;
    virtual int update_obj(db_key_info_t *key_info, void *key_data) = 0;

public:
    FieldsType fields;
};

class IndexCompare {
public:
    bool operator()(const std::vector<FieldBase*> &lhs, const std::vector<FieldBase*> &rhs) {
        if(lhs.size() != rhs.size())
            return true;
        
        int i = 0;
        for(auto left: lhs) {
            auto right = rhs[i++];
            if(left->eq(right))
                continue;

            return left->le(right);
        }

        return false;
    }
};

using IndexType = std::vector<FieldBase*>; 
using IndexDbType = std::multimap<IndexType, TableBase*, IndexCompare>;
using FieldFactoriesType = std::vector<FieldFactoryBase*>;

template<typename T>
class Table : public TableBase{
public:
static int primary_key_id;
static FieldFactoriesType fields_factories;

static std::map<int, FieldFactoriesType> indexes_factories;
static std::map<int, std::vector<int>> indexes_poses;

static std::map<IndexType, TableBase*, IndexCompare> primary_index_db;
static std::map<int, IndexDbType> index_dbs;

private:
    using index_iter_type = IndexDbType::iterator;
    struct table_iter {
        index_iter_type cur;
        index_iter_type next;
        index_iter_type end;
    } cur_iter;

public:
    Table() 
    {
        for (auto factory: fields_factories) {
            fields.push_back(factory->CreateField());
        }
    }

    Table(const Table<T> &other)
    {
        for(auto other_value: other.fields)
            fields.push_back(other_value->clone());
    }

    void update_from_iter(const TableBase* other)
    {
        auto iter = fields.begin();
        while(iter != fields.end()) {
            delete *iter;
            iter = fields.erase(iter);
        }

        for(auto pField: other->fields) {
            fields.push_back(pField->clone());
        }
    }

    FieldBase* clone() {
        return nullptr;
    }

    ~Table()
    {
        auto iter = fields.begin();
        while(iter != fields.end()){
            delete *iter;
            iter = fields.erase(iter);
        }
    }
    
    const char* name() const {
        return nullptr;
    }

    
    FieldBase& operator[](const char* name)
    {
        for(auto pField : fields) {
            if(!strcmp(pField->name(), name)) {
                return *pField;
            }
        }
    }

    int operator=(void *data) {
        return 0;
    }

    int value(void *out_data) {
        return 0;
    }

    int set_data(void *data) {
        return 0;
    }

    int get_data(void *data, uint32_t len) {
        return 0;
    }

    std::vector<FieldBase* > create_index(int index_id, std::vector<FieldBase*> &fields)
    {
        std::vector<FieldBase*> index;
        
        auto index_poses = indexes_poses[index_id];
        for (auto pos : index_poses) {
            index.push_back(fields[pos]->clone());
        }

        return index;
    }

    void destory_index(std::vector<FieldBase*> &index)
    {
        for(auto pField: index)
            delete pField;
    }

    void update_old_with_new(TableBase *pOld)
    {
        int i = 0;
        for(auto pField: fields) {
            if(pField->is_update()) {
                delete pOld->fields[i];
                pOld->fields[i] = pField->clone();
            }
            i++;
        }
    }

    int save()
    {
        auto new_table = new Table<T>(*this);

        auto iter = indexes_poses.begin();
        while(iter != indexes_poses.end()) {
            auto index = create_index(iter->first, this->fields);
            if (iter->first == primary_key_id) {
                auto ret = primary_index_db.insert({index, new_table});
                assert(ret.second == true);
            } else {
                index_dbs[iter->first].insert({index, new_table});
            }
            iter++;
        }

        return 0;
    }

    int remove_obj(db_key_info_t *key_info, void *key_data)
    {
        auto pOldTable = erase_table_by_primary_key(key_info, key_data);
        if (pOldTable == nullptr)
            return STATUS_OBJECT_DOESNT_EXIST;

        delete_indexes(pOldTable);

        delete pOldTable;
        return 0;
    }

    int update_obj(db_key_info_t *key_info, void *key_data)
    {
        auto pOldTable = find_table_by_primary_key(key_info, key_data);
        if (pOldTable == nullptr)
            return STATUS_OBJECT_DOESNT_EXIST;

        update_old_with_new(pOldTable);
        return 0;
    }

    /*caller should free the return index.*/
    std::vector<FieldBase*> make_index(uint16_t index_id, void *key_data)
    {
        std::vector<FieldBase*> index;

        for(auto index_factory: indexes_factories[index_id]) {
            auto pField = index_factory->CreateField();
            pField->set_data(key_data);
            index.push_back(pField);
        }

        return index;
    }

    void free_index(std::vector<FieldBase*> &index)
    {
        for(auto pField: index){
            delete pField;
        }
    }

    int delete_indexes(const TableBase *pOldTable)
    {
        auto index_dbs_iter = index_dbs.begin();
        while(index_dbs_iter != index_dbs.end()) {
            delete_one_index(index_dbs_iter->first, pOldTable);
            index_dbs_iter++;
        }
    }

    int delete_one_index(int index_id, const TableBase* pOldTable)
    {
        auto db_iter = index_dbs.find(index_id);
        if(db_iter == index_dbs.end()) {
            return 1;
        }

        auto &db = db_iter->second;
        for(auto iter = db.begin(); iter != db.end();) {
            auto pTable = iter->second;
            if(pTable == pOldTable) {
                auto index = iter->first;
                free_index(index);
                iter = db.erase(iter);
            } else {
                iter++;
            }
        }
    }
    
    TableBase* erase_table_by_primary_key(db_key_info_t *key, void* key_data)
    {
        auto id = key->index_id;
        assert(id == primary_key_id);

        auto index = make_index(id, key_data);
        auto find_iter = primary_index_db.find(index);
        free_index(index);

        if(find_iter == primary_index_db.end())
            return nullptr;

        auto pOldTable = find_iter->second;
        primary_index_db.erase(find_iter);
        return pOldTable;
    }

    TableBase* find_table_by_primary_key(db_key_info_t *key, void* key_data)
    {
        auto id = key->index_id;
        assert(id == primary_key_id); /*must use primary key*/

        auto index = make_index(id, key_data);
        auto find_iter = primary_index_db.find(index);
        free_index(index);

        if(find_iter == primary_index_db.end())
            return nullptr;

        return find_iter->second;
    }

    int read_obj(db_key_info_t *key, void* key_data, void *buf, uint32_t len)
    {

        auto pTable = find_table_by_primary_key(key, key_data);
        if(nullptr == pTable)
            return STATUS_OBJECT_DOESNT_EXIST;

        for(auto pField: pTable->fields)
            pField->get_data(buf, len);

        return 0;
    }

    int create_root_iterator(db_key_info_t *key, void* key_data, db_root_iterator *iter)
    {
        auto id = key->index_id;
        assert(id != primary_key_id); /*not support primary_key iterator.*/

        auto index = make_index(id, key_data);
        auto &db = index_dbs[id];
        cur_iter.next = db.find(index);
        cur_iter.cur = db.end();
        cur_iter.end = db.end();

        free_index(index);

        if(iter != nullptr)
            *iter = static_cast<db_root_iterator>(&cur_iter);
        return 0;
    }

    int root_iterator_next()
    {
        if(cur_iter.next == cur_iter.end)
            return STATUS_SCAN_TO_END;

        cur_iter.cur = cur_iter.next;
        cur_iter.next++;

        update_from_iter(cur_iter.cur->second);

        return 0;
    }
};

}
#endif
