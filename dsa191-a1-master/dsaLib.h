/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List {
    L1Item<T>   *_pHead;// The head pointer of linked list
    L1Item<T>   *_pEnd; // The End pointer of linked list
    size_t      _size;// number of elements in this list
public:
    L1List() : _pHead(NULL), _pEnd(NULL), _size(0) {}
    ~L1List();

    void    clean();
    bool    isEmpty() {
        return _pHead == NULL;
    }
    size_t  getSize() {
        return _size;
    }

    T&      at(int i);// give the reference to the element i-th in the list
    T&      operator[](int i);// give the reference to the element i-th in the list

    bool    find(T& a, int& idx);// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
    int     insert(int i, T& a);// insert an element into the list at location i. Return 0 if success, -1 otherwise
    int     remove(int i);// remove an element at position i in the list. Return 0 if success, -1 otherwise.

    int     push_back(T& a);// insert to the end of the list
    int     insertHead(T& a);// insert to the beginning of the list

    int     removeHead();// remove the beginning element of the list
    int     removeLast();// remove the last element of the list

    void    reverse();


    
    #pragma region return void
    void    traverse(void (*op)(T&)) {
        // duyet qua het cac phan tu
        // TODO: Your code goes here
        L1Item<T>* p =_pHead;
        while (p)
        {
            op(p->data);
            p=p->pNext;
        }
    }
    void    traverse(void (*op)(T&, void*), void* pParam) {
        // TODO: Your code goes here
        L1Item<T>* p = _pHead;
        while (p)
        {
            op(p->data, pParam);
            p       = p->pNext;
        }
    }
    void    traverse(void (*op)(T&, bool), bool pParam) {
        // TODO: Your code goes here
        L1Item<T>* p = _pHead;
        while (p)
        {
            op(p->data, pParam);
            p       = p->pNext;
        }
    }

    // get array ouput
    void traverse(int (*op)(T&, int), int _cityid, void* &pOutput, int N )
    {
        L1Item<T>* pNode    = _pHead;
        int IDStation       = -1;

        pOutput             = new int [N];
        int index = 0;

        while (pNode)
        {
            IDStation = (*op)(pNode->data, _cityid);

            if (IDStation != -1)
            {
                *(((int*)pOutput)+index) = IDStation;
                index++;
            }

            pNode = pNode->pNext;
        }
    }

#pragma endregion

    #pragma region return int 
    // count num line of city
    int traverse(bool (*op)(T&, int), int id)
    {
        
        L1Item<T>*  pNode    = _pHead;
        int         NumLines = 0;

        while (pNode)
        {
            if ((*op)(pNode->data, id))
                NumLines++;

            pNode = pNode->pNext;
        }
        return NumLines;

    }

    // for ISL
    bool traverse(bool (*op)(T&, int), int id, int pos, int& index)
    {
        L1Item<T>*  pNode    = _pHead;
        int         NumLines = 0;
        index = 0;

        while (pNode)
        {
            if ((*op)(pNode->data, id))
            {
                NumLines++;
                if (NumLines-1 == pos)
                    return true;
            }
                
            pNode = pNode->pNext;
            ++index;
        }
        return false;

    }
    // for RSL
    bool traverse(bool (*op)(T&, int, int), int station_id, int line_id, int& pos)
    {
        L1Item<T>*  pNode    = _pHead;
        pos = 0;

        while (pNode)
        {
            if ((*op)(pNode->data, station_id,line_id))
                return true;
                
            pNode = pNode->pNext;
            ++pos;
        }
        return false;

    }

    // position of station
    bool traverse(bool (*op)(T&, int), int id, int& pos)
    {
        
        L1Item<T>*  pNode    = _pHead;
        pos = 0;
        while (pNode)
        {
            if ((*op)(pNode->data, id))
                return true;
            ++pos;
            pNode = pNode->pNext;
        }

        return false;
        

    }

    // traverse to Find ID city
    int traverse(int (*op)(T&, string), void* _name)
    {
        L1Item<T>*   pNode    = _pHead;
        int          Id       = -1;
        string       namecity = string((char*)_name);

        while(pNode)
        {
            Id = (*op)(pNode->data,namecity);

            if (Id != -1)
                return Id;
            pNode = pNode->pNext;
        }
        return -1;
    }

    // Find Station ID
     int traverse(int (*op)(T&, int), int _cityid)
    {
        L1Item<T>*   pNode    = _pHead;
        int          Id       = -1;

        while(pNode)
        {
            Id = (*op)(pNode->data,_cityid);

            if (Id != -1)
                return Id;
            pNode = pNode->pNext;
        }
        return -1;
    }



    #pragma endregion

    #pragma region return string
    // Get string ouput
    string   traverse(string (*op)(T&, int), int city_id)
    {
        string geography = "";
        L1Item<T>* pNode = _pHead;

        while (pNode)
        {
            geography = (*op)(pNode->data, city_id);

            if (geography != "")
                return geography;

            pNode = pNode->pNext;
        }

        return "";
    } 

    #pragma endregion

    #pragma region return bool
    bool traverse(bool (*op)(T&, int, int), int _lineid, int _stationid )
    {
        L1Item<T>* pNode = _pHead;
        bool        isExist = false;

        while (pNode)
        {
            isExist = (*op)(pNode->data, _lineid, _stationid);

            if (isExist)
                return true;
            pNode =pNode->pNext;
        }
        return false;


    }

    #pragma endregion
    


};

/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::push_back(T &a) {
    L1Item<T>* _pNew = new L1Item<T>(a);

    if (_pNew == NULL)
        return -1;
    
    if (_pEnd == NULL)
        _pHead = _pEnd     = _pNew;
    else
    {
        _pEnd->pNext = _pNew;
        _pEnd =_pNew;
    }

    ++_size;
    // TODO: Your code goes here
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T &a) {
    // TODO: Your code goes here
    L1Item<T>* _pNew = new L1Item<T>(a);
    
    if (_pNew == NULL)
        return -1;
    _pNew->pNext    = _pHead;
    _pHead          = _pNew;
    
    ++_size;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead() {
    // TODO: Your code goes here
    if (_pHead == NULL)
        return -1;
    
    L1Item<T>* temp;
    temp = _pHead;
    _pHead = _pHead->pNext;

    --_size;
    delete temp;
    return 0;

}

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast() {
    // TODO: Your code goes here
    if (_pEnd == NULL)
        return -1;

    L1Item<T>* _pCurrent;
    _pCurrent = _pHead;

    while (_pCurrent->pNext != _pEnd)
        _pCurrent = _pCurrent->pNext;

    _pEnd = _pCurrent;
    delete _pEnd->pNext;
    _pEnd -> pNext = NULL;

    --_size;
    return 0;


    
}

template <class T>
T& L1List<T>::at(int i)
{
    L1Item<T>* pNode = _pHead;

    for (int index = 0; index < i; ++index)
    {
        pNode = pNode->pNext;
    }

    return pNode->data;
}

template <class T>
int L1List<T>::remove(int i){// remove an element at position i in the list. Return 0 if success, -1 otherwise.
   

    if (i < 0 || i >= _size)
        return -1;
    
    if (i == 0)
        _pHead = _pHead->pNext;
    else
    {
        L1Item<T>* pNode = _pHead;
        for (int index = 0; index < i-1 ; ++index)
            pNode = pNode->pNext;
        
        L1Item<T>* pTemp = pNode->pNext;

        //pNode->data = pNode->pNext->data;
        pNode->pNext = pNode->pNext->pNext;
        delete pTemp;
    }

    --_size;
 

    return 0;

}

template <class T>
int L1List<T>::insert(int i, T& a){

    L1Item<T>* _pNew    = new L1Item<T>(a);
    L1Item<T>* _pNode = this->_pHead;
    

    if (i < 0 || i > _size || _pNew == nullptr)
        return -1;

    // insert head
    if (i == 0)
    {
       if (_size == 0)
       {
           _pHead = _pEnd = _pNew;
           ++_size;
           return 0;
       }

       _pNew->pNext = _pHead;
       _pHead = _pNew;

       ++_size;
       return 0;

    }

    // insert End
    if (i == _size-1)
    {
        _pEnd->pNext = _pNew;
        _pEnd =_pNew;
    

        ++_size;
        // TODO: Your code goes here
        return 0;

    }

    //insert others potitions     
    
    for (int index = 0; index < i-1; ++index)
        _pNode = _pNode->pNext;
    
    _pNew->pNext     = _pNode->pNext;
    _pNode->pNext    = _pNew;
    ++_size;
    return 0;
}

#endif //DSA191_A1_DSALIB_H
