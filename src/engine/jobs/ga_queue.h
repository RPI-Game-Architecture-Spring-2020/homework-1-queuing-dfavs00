#include <mutex>
#pragma once

/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

/*
** Thread-safe queue.
** https://www.research.ibm.com/people/m/michael/podc-1996.pdf
*/
class ga_queue
{
public:
	ga_queue(int node_count);
	~ga_queue();

	void push(void* data);
	bool pop(void** data);

	int get_count() const;

private:
	unsigned int count; // number of elements in queue
	node* head;			// head node of the queue
	node* tail;			// tail node of the queue
	std::mutex h_lock;	// mutex to lock the head
	std::mutex t_lock;	// mutex to lock the tail
};

/*
** Node class for the thread safe queue
*/
class node
{
public:
	void* value;		// value stored by this node
	node* next;			// next node
};

