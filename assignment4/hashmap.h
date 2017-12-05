// Aibek Smagulov 20142028 smagulovaybek@gmail.com

#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <math.h>
#include <typeinfo>

/** 
  * Assignment 4 for CSE221 Data Structures
  *
  * 2016. 11. 8
  *
  */

// Map element
template <class KeyType, class ValType>
class MapElem
{
public:
	typedef KeyType ktype;
	typedef ValType vtype;
	
    MapElem() {
        link = NULL;
    }

	KeyType key;
	ValType val;
	
	MapElem* link;
};

bool inline operator==(std::string a, std::string b)
{
	if((a).compare(b) == 0) return true;
	return false;
}

//
// Hash Map data structure
//
template <class HashMapElemType> 
class HashMap
{
public:
	typedef typename HashMapElemType::ktype KeyType;
	typedef typename HashMapElemType::vtype ValType;
	
	// constructor
	HashMap(unsigned int c = 1000);
	
	// destructor
	~HashMap();
	
	// Modify below functions
	int size() { return mapsize; };
	
	bool isEmpty() { return (mapsize == 0); };
	
	// ToDo
	HashMapElemType* find(const KeyType k);
	
	void insert(const KeyType k, const ValType v);
		
	bool remove(const KeyType k);
	
    unsigned int hashfunction(const std::string k);
    unsigned int hashfunction(const float k);
	
	void print();
	
private:
	// Hash Table
	HashMapElemType** ht;
	
	unsigned int mapsize, capacity, divisor;
    int findPrimeSmallerCapacity(int c);
    int stringToInt(const char* key);
};

template <class HashMapElemType>
int HashMap<HashMapElemType>::stringToInt(const char* key){
    int number = 0;
    while(*key){
        number += *key++;
        if(*key)
            number += ((int) *key++) << 8;
    }
    return number;
}

template <class HashMapElemType>
int HashMap<HashMapElemType>::findPrimeSmallerCapacity(int c){
    int resPrime = (c % 2 == 0 ? c - 1 : c);
    int primes[c], k = 0;
    bool is_prime[c + 1];

    for(int i = 2; i <= c; i++){
        if(! is_prime[i]){
            resPrime = i;
            primes[k++] = i;
        }
        for(int j = 0; j < k; j++){
            if(primes[j] * i > c) break;
            is_prime[primes[j] * i] = 1;
        }
    }
    return resPrime;
}

template <class HashMapElemType>
HashMap<HashMapElemType>::HashMap(unsigned int c) 
{
    capacity = c;
    divisor = findPrimeSmallerCapacity(c); 
    ht = new MapElem<KeyType, ValType>*[capacity];
    for(int i = 0; i < c; i++){
        ht[i] = NULL;
    }
}

// destructor
template <class HashMapElemType>
HashMap<HashMapElemType>::~HashMap() 
{
	for(int i = 0; i < capacity; i++){
        MapElem<KeyType, ValType>* ptr = ht[i];
        while(ptr != NULL){
            MapElem<KeyType, ValType>* temp_ptr = ptr->link;
            delete ptr;
            ptr = temp_ptr;        
        }
    }
    delete[] ht;
}

template <class HashMapElemType>
HashMapElemType* 
HashMap<HashMapElemType>::find(const KeyType k) 
{ 
    int key = hashfunction(k);
    MapElem<KeyType, ValType>* ptr = ht[key];
    while(ptr != NULL && ptr->key != k){
        ptr = ptr->link;
    }
    if(ptr == NULL) return NULL;
    else return ptr;
}

template <class HashMapElemType>
void 
HashMap<HashMapElemType>::insert(const KeyType k, const ValType v) 
{
    MapElem<KeyType, ValType>* ptr = find(k);
    if(ptr == NULL){
        MapElem<KeyType, ValType>* new_entry = new MapElem<KeyType, ValType>();
        new_entry->key = k;
        new_entry->val = v;
        int key = hashfunction(k);
        MapElem<KeyType, ValType>* ptr = ht[key];
        if(ptr == NULL){
            ht[key] = new_entry;
        }
        else{
            while(ptr->link != NULL){
                ptr = ptr->link;
            }
            ptr->link = new_entry;
        }
    }
    else{
        ptr->val = v; 
    }
}

template <class HashMapElemType>
bool 
HashMap<HashMapElemType>::remove(const KeyType k) 
{ 
    MapElem<KeyType, ValType>* ptr = find(k);
    if(ptr == NULL){
        return false;
    }
    else{
        int key = hashfunction(k);
        MapElem<KeyType, ValType>* par = ht[key];
        if(ht[key] == ptr){
            ht[key] = ptr->link;
            delete ptr;
        }
        else{
            while(par->link != ptr){
                par = par->link;
            }
            par->link = ptr->link;
            delete ptr;
        }
        return true;
    }
}

template <class HashMapElemType>
unsigned int HashMap<HashMapElemType>::hashfunction(const std::string k){
    return stringToInt(k.c_str()) % divisor;
}

template <class HashMapElemType>
unsigned int HashMap<HashMapElemType>::hashfunction(const float k){
    return int(k) % divisor;
}   

template <class HashMapElemType>
void 
HashMap<HashMapElemType>::print()
{
	for(int i = 0; i < capacity; i++){
        MapElem<KeyType, ValType>* ptr = ht[i];
        while(ptr != NULL){
            std::cout << ptr->key << ":" << ptr->val << std::endl;
            ptr = ptr->link;
        }
    }
}

#endif
