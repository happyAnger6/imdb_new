#ifndef _IMDB_H
#define _IMDB_H

#include <cstdint>

#include <iostream>
#include <array>
#include <iterator>
#include <algorithm>
#include <utility>
#include <map>

namespace imdb {

class FieldBase{
public:
    virtual int operator=(uint32_t data) { return 0; }
    virtual int operator=(uint8_t data) { return 0; }
    virtual bool operator==(const FieldBase& other) = 0;
    virtual const void* value() const = 0;
};

template<typename T>
class Field :public FieldBase
{
    T *_data;
public:
    Field()
    { 
        _data = new T; 
    }

    ~Field()
    { 
        delete _data;
        _data = nullptr;
    }

    bool operator==(const FieldBase& rhs) 
    {
        return *((T*)(this->value())) == *((T*)(rhs.value()));
    }

    int operator=(T data)
    {
        *_data = data;
        return 0;
    }

    const void* value() const
    {
        return (void*)_data;
    }
};

class FieldFactoryBase {
public:
    virtual FieldBase* CreateField() = 0;
};

template<int P, int O, int L, typename T>
class FieldFactory : public FieldFactoryBase{
public:
    int pos = P;
    int offset = O;
    int len = L;
    const char* name;

    FieldFactory(const char *name) :name(name) {}
    FieldBase* CreateField()
    {
        return new T;
    }
};

class TableBase{
public:
    virtual FieldBase& operator[](int pos) = 0;
    virtual const FieldBase& operator[](int pos) const = 0;
    virtual int save() = 0;
};


bool operator<(const std::vector<FieldBase*>& lhs, const std::vector<FieldBase*>& rhs)
{
    if (lhs.size() != rhs.size())
        return false;

    for(auto i = 0; i < lhs.size(); i++) {
        if (*(lhs[i]) == *(rhs[i]))
            continue;

        return *(lhs[i]) < *(rhs[i]);
    }

    return false;
}

template<int N, int PK, typename T>
class Table : public Field<T>, public TableBase{
std::array<FieldBase*, N> values;
std::array<FieldBase*, PK> pks;

std::map<int, std::map<std::vector<FieldBase*>&, FieldBase*>> database;

public:
static std::array<FieldFactoryBase*, N> fields;
static std::array<int, PK> primary_keys;
static std::map<int, std::vector<int> &> indexes;

public:
    Table() 
    {
        int i = 0;
        for (auto factory: fields) {
            values[i++] = factory->CreateField();
        }

        i = 0;
        for (auto pk: primary_keys) {
            pks[i++] = values[pk];
        }

    }

    ~Table()
    {
        int i = 0;
        for(auto &value: values) {
            delete value;
            values[i++] = nullptr;
        }
    }

    int save()
    {
        std::cout << "imdb saved done..." << std::endl;
        database.insert({pks, this});
        return 0;
    }

    FieldBase& operator[](int pos)
    {
        return *(values[pos]);
    }
    
    const FieldBase& operator[](int pos) const
    {
        return *(values[pos]);
    }
    
    bool operator==(const FieldBase& other) 
    {
        return false;
    }
};

}
#endif
