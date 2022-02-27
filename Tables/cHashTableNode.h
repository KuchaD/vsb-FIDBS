//
// Created by David Kuchar on 27.02.2022.
//

#pragma once

#include "cHashTableNode.h"
#include "cMemory.h"

template<class TKey, class TData>
class cHashTableNode
{
private:
    bool mEmptyNode;
    TKey mKey;
    TData mData;
    cHashTableNode* mNextNode;
    int mSize = sizeof(cHashTableNode<TKey, TData>);

public:
    cHashTableNode();
    ~cHashTableNode();

    bool Add(const TKey &key, const TData &data, int &itemCount, int &nodeCount, cMemory *memory = NULL);
    bool Find(const TKey &key, TData &data) const;

    bool AddWithoutR(const TKey &key, const TData &data, int &itemCount, int &nodeCount, cMemory *memory = NULL);
    bool FindWithoutR(const TKey &key, TData &data) const;
};

template<class TKey, class TData>
cHashTableNode<TKey, TData>::cHashTableNode()
{
    mNextNode = NULL;
    mEmptyNode = true;
}

template<class TKey, class TData>
cHashTableNode<TKey, TData>::~cHashTableNode()
{
    if (mNextNode != NULL)
    {
        delete mNextNode;
        mNextNode = NULL;
    }
}

template<class TKey, class TData>
bool cHashTableNode<TKey, TData>::Add(const TKey &key, const TData &data, int &itemCount, int &nodeCount,cMemory *memory)
{
    bool ret = true;

    if (!mEmptyNode) {
        if (mKey == key) {
            ret = false;
        }
        else {
            if (mNextNode == NULL) {
                if (memory == nullptr)
                {
                    mNextNode = new cHashTableNode<TKey, TData>();
                }else
                {
                    char *mem = memory->New(mSize);
                    mNextNode = new(mem)cHashTableNode<TKey, TData>();
                }
                nodeCount++;
            }
            ret = mNextNode->Add(key, data, itemCount, nodeCount);
        }
    }
    else {
        mKey = key;
        mData = data;
        mEmptyNode = false;
        itemCount++;

        ret = true;
    }
    return ret;
}

template<class TKey, class TData>
bool cHashTableNode<TKey, TData>::Find(const TKey &key, TData &data) const
{
    if (!mEmptyNode)
    {
        if (mKey == key)
        {
            data = mData;
            return true;
        }
        else if (mNextNode != NULL)
        {
            return mNextNode->Find(key, data);
        }
    }
    return false;
}
template<class TKey, class TData>
bool cHashTableNode<TKey, TData>::AddWithoutR(const TKey &key, const TData &data, int &itemCount, int &nodeCount, cMemory *memory = NULL)
{
    auto node = this;
    while (!node.mEmptyNode)
    {
        if (node->mKey == key)
        {
            return false;
        }
        if (node->mNextNode == nullptr)
        {
            if (memory == nullptr)
            {
                node->mNextNode = new cHashTableNode<TKey, TData>();
            }
            else
            {
                auto mem = memory->New(sizeof (cHashTableNode<TKey, TData>));
                node->mNextNode = new (mem)cHashTableNode<TKey, TData>();
            }
            nodeCount++;
            node = node->mNextNode;
            break;
        }
        node = node->mNextNode;
    }

    node->mKey = key;
    node->mData = data;
    node->mEmptyNode = false;
    itemCount++;
    return true;
}

template<class TKey, class TData>
bool cHashTableNode<TKey, TData>::FindWithoutR(const TKey &key, TData &data) const
{
    auto node = this;
    while (node != nullptr)
    {
        if (node->mKey == key)
        {
            data = node->mData;
            return true;
        }

        node = node->mNextNode;
    }
    return false;
}