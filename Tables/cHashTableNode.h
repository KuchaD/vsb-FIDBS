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

public:
    cHashTableNode();
    ~cHashTableNode();

    bool Add(const TKey &key, const TData &data, int &itemCount, int &nodeCount, cMemory *memory);
    bool Find(const TKey &key, TData &data) const;

    bool AddWithoutR(const TKey &key, const TData &data, int &itemCount, int &nodeCount, cMemory *memory);
    bool FindWithoutR(const TKey &key, TData &data) const;
};

template<class TKey, class TData>
cHashTableNode<TKey, TData>::cHashTableNode()
{
    mNextNode = nullptr;
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
            if (mNextNode == nullptr) {
                if (memory == nullptr)
                {
                    mNextNode = new cHashTableNode<TKey, TData>();
                }else
                {
                    auto *mem = memory->New(sizeof(cHashTableNode<TKey, TData>));
                    mNextNode = new (mem)cHashTableNode<TKey, TData>();
                }
                nodeCount++;
            }
            ret = mNextNode->Add(key, data, itemCount, nodeCount, memory);
        }
    }
    else {
        mKey = key;
        mData = data;
        mEmptyNode = false;
        mNextNode = NULL;
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
bool cHashTableNode<TKey, TData>::AddWithoutR(const TKey &key, const TData &data, int &itemCount, int &nodeCount, cMemory *memory)
{
    auto node = this;
    while (!node->mEmptyNode)
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