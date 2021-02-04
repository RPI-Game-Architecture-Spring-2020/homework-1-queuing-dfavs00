/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_queue.h"

ga_queue::ga_queue(int node_count)
{
	// TODO:
	// Initialize the queue.
	// For extra credit, preallocate 'node_count' elements (instead of
	// allocating on push).
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf

	// create node in heap memory
	node* new_node = new node;
	new_node->_next = NULL;

	_head = new_node;
	_tail = new_node;

	// mutexes are unlocked by default

	// original count is zero since this first node is only a dummy node
	_count = 0;
}

ga_queue::~ga_queue()
{
	// TODO:
	// Free any resources held by the queue.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf

	// cycle through nodes in the queue starting
	// from tail until reaching head
	node* current = _head;
	while (current != NULL) 
	{

		// delete current node but keep track of next node
		node* temp = current->_next;
		delete current;
		current = temp;
	}
}

void ga_queue::push(void* data)
{
	// TODO:
	// Push 'data' onto the queue in a thread-safe manner.
	// If you preallocated 'node_count' elements, and if the queue is full when
	// this function is called, you must block until another thread pops an
	// element off the queue.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf

	node* new_node = new node;
	new_node->_value = data;
	new_node->_next = NULL;
	
	_t_lock.lock();			// lock tail
	_tail->_next = new_node;	// current tails next set to new node
	_tail = new_node;		// new tail set to current node
	_count += 1;
	_t_lock.unlock();		// unlock tail
}

bool ga_queue::pop(void** data)
{
	// TODO:
	// Pop one element off the queue in a thread-safe manner and place it in
	// the memory pointed to by 'data'.
	// If the queue is empty when this function is called, return false.
	// Otherwise return true.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
	
	_h_lock.lock();	// lock head since it will be accessed
	node* temp_head_node = _head;
	node* new_head = temp_head_node->_next;
	// check if the queue is empty
	if (new_head == NULL) 
	{
		_h_lock.unlock();
		return false;
	}
	
	// point data at the memory location stored by _value in head
	*data = new_head->_value;
	_head = new_head;
	_count -= 1;
	_h_lock.unlock();	// unlock head no longer needed

	delete temp_head_node;
	return true;
}

int ga_queue::get_count() const
{
	// TODO:
	// Get the number of elements currently in the queue.
	return _count;
}
