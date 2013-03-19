/*
 *  ut_std.h
 *  iMapbase
 *
 *  Created by Duan Sijiu on 10-11-4.
 *  Copyright 2010 Autonavi . All rights reserved.
 *
 */

#ifndef _UT_STD_H_
#define _UT_STD_H_

#include <stdlib.h>
///*
template <class _V>
class dsjIterator
{
public:
	dsjIterator(_V v): pre(NULL), next(NULL)
	{
		obj = v;
	}
	~dsjIterator(){}
	
	_V obj;
	dsjIterator* pre;
	dsjIterator* next;
	
	inline void operator =  (dsjIterator &A) { obj=A.obj; }
	inline bool operator == (dsjIterator &A) { return obj == A.obj; }
	inline bool operator >  (dsjIterator &A) { return obj > A.obj; }
	inline bool operator <  (dsjIterator &A) { return obj < A.obj; }
};
//*
template <class _T>
class dsjVector
{

public:
	dsjVector():begin(NULL){}
	~dsjVector(){clear();}
	dsjIterator<_T>* begin;
	
	int size()
	{
		dsjIterator<_T>* cur_it = begin;
		int s=0;
		while (cur_it!=NULL) 
		{
			s++;
			cur_it = cur_it->next;
		}
		return s;
	}
	
	void erase(dsjIterator<_T>* it)
	{
		if (it==NULL) {
		}
		else if (it==begin) {
			begin = begin->next;
			delete it;
		}
		else if(it->next==NULL){
			it->pre->next = NULL;
			delete it;
		}
		else {
			it->pre->next = it->next;
			it->next->pre = it->pre;
			delete it;
		}
	}
	
	int push(_T obj)
	{
		dsjIterator<_T> *it = new dsjIterator<_T>(obj);
		if (it==NULL) return 0;
		
		if (begin==NULL) {
			begin = it;
			return 1;
		}
		else {
			it->next=begin;
			begin->pre=it;
			begin=it;
			return 1;
		}

		/*
		dsjIterator<_T> *it = new dsjIterator<_T>(obj);
		if (it==NULL) return 0;
		
		if (begin==NULL) {
			begin = it;
			return 1;
		}
		else {
			dsjIterator<_T>* cur_it = begin;
			
			while (cur_it!=NULL) {
				if ( (*it) < (*cur_it)) {
					it->pre = cur_it->pre;
					it->next = cur_it;
					cur_it->pre = it;
					return 1;
				}
				else if( (*it) == (*cur_it) ){
					delete it;
					return 0;
				}
				
				if (cur_it->next==NULL) {
					cur_it->next = it;
					it->pre = cur_it;
					it->next = NULL;
					return 1;
				}
				
				cur_it = cur_it->next;
			}
		}
		return 0;*/
	}
	
	void clear()
	{
		dsjIterator<_T>* cur_it = begin;
		
		while (cur_it!=NULL) {
			dsjIterator<_T>* next = cur_it->next;
			delete cur_it;
			cur_it = next;
		}
		begin = NULL;
	}
};

template <class _K, class _V>
class dsjMapObj
{
public:
	dsjMapObj(_K k, _V v):key(k),value(v)
	{
		pre=NULL;
		next=NULL;
	}
	~dsjMapObj(){}
	
	dsjIterator<_K> key;
	dsjIterator<_V> value;
	
	dsjMapObj<_K,_V> *pre;
	dsjMapObj<_K,_V> *next;
	
	inline void operator =  (dsjMapObj &A) { key=A.key; value=A.value; }
	inline bool operator == (dsjMapObj &A) { return key == A.key; }
	inline bool operator >  (dsjMapObj &A) { return key > A.key; }
	inline bool operator <  (dsjMapObj &A) { return key < A.key; }
};

template <class _K, class _V>
class dsjMap
{
public:
	dsjMap():begin(NULL){}
	~dsjMap(){clear();}
	
	dsjMapObj<_K,_V>* begin;
	
	void erase(dsjMapObj<_K,_V>* it)
	{
		if (it==NULL) {
		}
		else if (it==begin) {
			begin = begin->next;
			delete it;
		}
		else if(it->next==NULL){
			it->pre->next = NULL;
			delete it;
		}
		else {
			it->pre->next = it->next;
			it->next->pre = it->pre;
			delete it;
		}
	}
	
	_V* getValue(_K key)
	{
		dsjMapObj<_K,_V>* cur_it = begin;
		
		while (cur_it!=NULL) {
			if (cur_it->key.obj == key) {
				return &(cur_it->value.obj);
			}
			
			cur_it = cur_it->next;
		}
		
		return NULL;
	}
	
	int push(_K key, _V value)
	{
		dsjMapObj<_K,_V> *it = new dsjMapObj<_K,_V>(key,value);
		if (it==NULL) return 0;
		
		if (begin==NULL) {
			begin = it;
			return 1;
		}
		else {
			it->next=begin;
			begin->pre=it;
			begin=it;
			return 1;
		}
		
		/*
		dsjMapObj<_K,_V> *it = new dsjMapObj<_K,_V>(key,value);
		if (it==NULL) return 0;
		
		if (begin==NULL) {
			begin = it;
			return 1;
		}
		else {
			dsjMapObj<_K,_V>* cur_it = begin;
			
			while (cur_it!=NULL) {
				if ( *it < *cur_it) {
					it->pre = cur_it->pre;
					it->next = cur_it;
					if (cur_it->pre!=NULL) {
						cur_it->pre->next = it;
					}
					cur_it->pre = it;
					return 1;
				}
				else if( *it == *cur_it ){
					*it = *cur_it;
					delete it;
					return 0;
				}
				
				if (cur_it->next==NULL) {
					cur_it->next = it;
					it->pre  = cur_it;
					it->next = NULL;
					return 1;
				}
				
				cur_it = cur_it->next;
			}
		}
		return 0;*/
	}
	
	void clear()
	{
		dsjMapObj<_K,_V>* cur_it = begin;
		
		while (cur_it!=NULL) {
			dsjMapObj<_K,_V>* next = cur_it->next;
			delete cur_it;
			cur_it = next;
		}
		begin = NULL;
	}
	
	
};


#endif
