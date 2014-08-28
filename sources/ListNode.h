#ifndef LIST_NODE_H_
#define LIST_NODE_H_

#include "defines.h"

namespace AwesomeLibrary {

namespace Private {

template<class Key> struct ListNode {
/*
Узел списка
*/
	ListNode* previous_;
	ListNode* next_;
	Key item_;

	ListNode(const Key& newItem): previous_(0), next_(0), item_(newItem) {}
};//end of declaration ListNode

#endif /* end of include guard: LIST_NODE_H_ */

} /* Private */ 

} /* AwesomeLibrary */ 
