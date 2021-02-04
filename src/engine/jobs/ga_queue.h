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
	// Node struct for a thread safe queue
	struct node
	{
		void* _value;		// value stored by this node
		node* _next;			// next node
	};

public:
	ga_queue(int node_count);
	~ga_queue();

	void push(void* data);
	bool pop(void** data);

	int get_count() const;

private:
	unsigned int _count;	// number of elements in the queue
	node* _head;			// head node of the queue
	node* _tail;			// tail node of the queue
	std::mutex _h_lock;		// mutex to lock the head
	std::mutex _t_lock;		// mutex to lock the tail
};
