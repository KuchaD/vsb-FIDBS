//
// Created by David Kuchar on 27.02.2022.
//
#pragma once

#include "cHashTableNode.h"
#include "cMemory.h"

template<class TKey, class TData>
class cHashTable
{
private:
    int mSize;
    cHashTableNode<TKey,TData>** mHashTable;
    int mItemCount = 0;
    int mNodeCount = 0;
    cMemory* mMemory;
    bool mWithoutRecursion;

private:
    inline int HashValue(const TKey &key) const;

public:
    cHashTable(int capacity, bool withMemory = false, bool withoutRecursion = false);
    ~cHashTable();

    bool Add(const TKey &key, const TData &data);
    bool Find(const TKey &key, TData &data) const;
    void PrintStat() const;
};

template<class TKey, class TData>
cHashTable<TKey,TData>::cHashTable(int capacity, bool withMemory, bool withoutRecursion)
{
    mSize = capacity / 2;
    mHashTable = new cHashTableNode<TKey,TData>*[mSize];
    for (int i = 0; i < mSize; i++)
    {
        mHashTable[i] = NULL;
    }

    mMemory = NULL;
    mWithoutRecursion = withoutRecursion;

    if(withMemory)
        mMemory = new cMemory( (capacity+1) * sizeof(cHashTableNode<TKey, TData>));
}

template<class TKey, class TData>
cHashTable<TKey, TData>::~cHashTable()
{
    if (mMemory == NULL) {
        if (mHashTable == NULL)
        for (int i = 0; i < mSize; i++) {
            if (mHashTable[i] != NULL) {
                delete mHashTable[i];
            }
        }
    }

    delete[] mHashTable;
    mHashTable = NULL;
}

template<class TKey, class TData>
bool cHashTable<TKey, TData>::Add(const TKey &key, const TData &data)
{
    int hv = HashValue(key);

    if (mHashTable[hv] == NULL)
    {
        if(mMemory == NULL)
        {
            mHashTable[hv] = new cHashTableNode<TKey, TData>();
        }
        else
        {
            char* mem = mMemory->New(sizeof(cHashTableNode<TKey, TData>));
            mHashTable[hv] = new (mem)cHashTableNode<TKey, TData>();
        }
        mNodeCount++;
    }

    if(mWithoutRecursion)
        return mHashTable[hv]->AddWithoutR(key, data, mItemCount, mNodeCount, mMemory);

    return mHashTable[hv]->Add(key, data, mItemCount, mNodeCount, mMemory);
}

template<class TKey, class TData>
bool cHashTable<TKey, TData>::Find(const TKey &key, TData &data) const
{
    int hv = HashValue(key);
    if (mHashTable[hv] == NULL) {
        return false;
    }

    if(mWithoutRecursion)
        return mHashTable[hv]->FindWithoutR(key, data);

    return mHashTable[hv]->Find(key, data);
}

template<class TKey, class TData>
inline int cHashTable<TKey, TData>::HashValue(const TKey &key) const
{
    return key % mSize;
}

template<class TKey, class TData>
void cHashTable<TKey, TData>::PrintStat() const
{
    printf("HashTable Statistics: Size: %d, ItemCount: %d, NodeCount: %d, Avg. Items/Slot: %.2f.\n",
           mSize, mItemCount, mNodeCount, (float)mItemCount / mSize);
}