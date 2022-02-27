//
// Created by David Kuchar on 26.02.2022.
//

#pragma once

#include <assert.h>
#include <stdlib.h>
#include "cRecord.h"

template <class TKey, class TData>
class cRecordTable
{

private:
    int mCapacity;
    int mCount;
    int const mRowSize = sizeof (cRecord<TKey, TData>);


public:
    cRecordTable(int capacity);
    ~cRecordTable();

    cRecord<TKey, TData> ** mData = nullptr;
    bool Add(const TKey &key, const TData &data);
    bool Get(int rowId, TKey &key, TData &data) const;
    bool Find(const TKey &key, TData &data) const;

};

template <class TKey, class TData>
cRecordTable<TKey, TData>::cRecordTable(int capacity)
{
    mCapacity = capacity;
    mCount = 0;
    mData = new cRecord<TKey, TData>*[capacity];
}

template <class TKey, class TData>

cRecordTable<TKey, TData>::~cRecordTable()
{
    if (mData != nullptr)
    {
        for (long i = 0; i < mCount; ++i) {
            delete mData[i];
        }
        delete [] mData;
        mData = nullptr;
        mCapacity = 0;
        mCount = 0;
    }
}


template <class TKey, class TData>
bool cRecordTable<TKey, TData>::Get(int rowId, TKey &key, TData &data) const
{
    bool ret = false;
    assert(rowId >= 0 && rowId < mCount);
    ret = true;

    auto record = mData[rowId];
    key = record->key;
    data = record->data;

    return ret;
}

template <class TKey, class TData>
bool cRecordTable<TKey, TData>::Add(const TKey &key, const TData &data)
{
    bool ret = false;
    assert(mCount < mCapacity);
    ret = true;

    auto record = new cRecord<TKey, TData>();
    record->key = key;
    record->data = data;

    mData[mCount] = record;
    ++mCount;
    return ret;
}

template <class TKey, class TData>
bool cRecordTable<TKey, TData>::Find(const TKey &key, TData &data) const
{
    for (long i = 0; i < mCount; ++i) {
        if (mData[i]->key == key) {
            data = mData[i]->data;
            return true;
        }
    }

    return false;
}
