//
//  TSRingQueue.hpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/15.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#ifndef TSRingQueue_hpp
#define TSRingQueue_hpp

#include "TSType.h"
#include "TSError.h"

#define TS_RING_QUEUE_DFT_SIZE 512

template <typename T>
class TSRingQueue {
private:
    TS_U32 m_nSize;
    TS_U32 m_nHead;
    TS_U32 m_nTail;
    TS_U32 m_nItemsCount;
    T *m_pData;
    
public:
    TSRingQueue(TS_U32 nSize=TS_RING_QUEUE_DFT_SIZE);
    ~TSRingQueue();
    
    TS_U32 Push(T data);
    TS_U32 Pop(T *data);
    TS_U32 Front(T *pData) const;
    TS_U32 Back(T *pData)  const;
    bool   IsFull() const;
    bool   IsEmpty() const;
    TS_U32 Count() const;
    TS_U32 Size() const;
    void   Clean();
    
};


template<typename T>
TSRingQueue<T>::TSRingQueue(
                            TS_U32 nSize /*=TS_RING_QUEUE_DFT_SIZE*/)
:m_nSize(nSize)
,m_nHead(0)
,m_nTail(0)
,m_nItemsCount(0)
,m_pData(NULL)
{
    m_pData = new T[m_nSize];
}

template<typename T>
TSRingQueue<T>::~TSRingQueue()
{
    if (m_pData) delete[]m_pData;
}

template<typename T>
TS_U32 TSRingQueue<T>::Push(T data)
{
    if ((m_nItemsCount >= m_nSize) || (NULL == m_pData))
        return TS_Err_ContainerFull;
    
    TS_U32 nPos = (m_nTail % m_nSize);
    m_pData[nPos] = data;
    m_nTail++;
    m_nItemsCount++;
    
    return TS_Err_None;
}

template<typename T>
TS_U32 TSRingQueue<T>::Pop(T *pOutData)
{
    if ((m_nItemsCount == 0) || (NULL == m_pData))
        return TS_Err_ContainerEmpty;
    if (NULL == pOutData)
        return TS_Err_BadParam;
    
    TS_U32 nPos = (m_nHead % m_nSize);
    *pOutData = m_pData[nPos];
    m_nHead++;
    m_nItemsCount--;
    
    return TS_Err_None;
}

template<typename T>
TS_U32 TSRingQueue<T>::Front(T *pOutData) const
{
    if ((m_nItemsCount == 0) || (NULL == m_pData))
        return TS_Err_ContainerEmpty;
    
    TS_U32 nPos = (m_nHead % m_nSize);
    *pOutData = m_pData[nPos];
    
    return TS_Err_None;
}

template<typename T>
TS_U32 TSRingQueue<T>::Back(T *pOutData) const
{
    if ((m_nItemsCount == 0) || (NULL == m_pData))
        return TS_Err_ContainerEmpty;
    
    TS_U32 nPos = (m_nTail-1 % m_nSize);
    *pOutData = m_pData[nPos];
    
    return TS_Err_None;
}

template<typename T>
bool TSRingQueue<T>::IsFull() const
{
    return (m_nItemsCount >= m_nSize);
}

template<typename T>
bool TSRingQueue<T>::IsEmpty() const
{
    return (0 == m_nItemsCount);
}

template<typename T>
TS_U32 TSRingQueue<T>::Count() const
{
    return m_nItemsCount;
}

template<typename T>
TS_U32 TSRingQueue<T>::Size() const
{
    return m_nSize;
}

template<typename T>
void TSRingQueue<T>::Clean()
{
    m_nHead = 0;
    m_nTail = 0;
    m_nItemsCount = 0;
}



#endif /* TSRingQueue_hpp */
