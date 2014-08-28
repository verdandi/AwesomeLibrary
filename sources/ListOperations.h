#ifndef LIST_OPERATIONS_H_
#define LIST_OPERATIONS_H_

#include "defines.h"

#include "ListNode.h"

namespace AwesomeLibrary {

namespace Private {

template<class Key> class ListOperations {
/*
Класс ListOperations реализует операции со списком в терминах узла списка.
При создании этого класса предполагается, что все данные в него поступают корректные
*/
#ifndef __ALGORITHM_TEST__
protected:
#else
public:
#endif

	typedef Private::ListNode<Key> Node;

	ListOperations () {}
	~ListOperations () {}

	/*
	Вставить узел node в начало списка c вершиной head
	Принимаемые параметры:
	newNode - вставляемый узел
	head - вершина списка
	*/
	void InsertNode(Node* newNode, Node*& head);

	/*
	найти узел с заданным ключем в списке с вершиной head
	Принимаемые параметры:
	node - узел с заданным кллючем
	head - вершина списка
	Возвращаемое значение:
	указатель на узел в списке, содержащий заданный ключ
	*/
	Node* FindNode(Node* node, Node* head) const;

	/*
	 * Найти элемент списка, содержащий минимальный ключ
	 * Принимаемые параметры:
	 * head - вершина списка
	 * Возвращаемое значение:
	 * указатель на узел с минимальным ключем
	*/
	Node* FindMinimum(Node* head) const;

	/*
	 * Найти элемент списка, содержащий максимальный ключ
	 * Принимаемые параметры:
	 * head - вершина списка
	 * Возвращаемое значение:
	 * указатель на узел с максимальным ключем
	*/
	Node* FindMaximum(Node* head) const;

	/*
	 * Найти элемент списка с ключем следующим по порядку за ключем заданного элемента
	 * Принимаемые параметры:
	 * node - заданный узел
	 * Возвращаемое значение:
	 * Найденный элемент или 0 в случае если элемент не найден.
	*/
	Node* FindSuccessor(Node* node) const;

	/*
	 * Найти элемент списка с ключем предыдущим по порядку за ключем заданного элемента
	 * Принимаемые параметры:
	 * node - заданный узел
	 * Возвращаемое значение:
	 * Найденный элемент или 0 в случае если элемент не найден.
	*/
	Node* FindPredecessor(Node* node) const;

	/*
	 * Удалить заданный элемент из списка с вершиной <head>
	 * Принимаемые параметры:
	 * - node - элемент, который необходимо удалить из списка
	 * - head - указатель на голову списка, из которого надо удалить заданный элемент
	*/
	void DeleteNode(Node* node, Node*& head);
};//end of declaration class ListOperations

template<class Key> void ListOperations<Key>::InsertNode(Node* node, Node*& head) {
#ifdef __ALGORITHM_DEBUG__
#define D_InsertNode_ 1
#else
#define D_InsertNode_ 0
#endif

	if (D_InsertNode_) {
		assert(node->next_ == 0);
		assert(node->previous_ == 0);
	}/* end of if */

	if (head == 0) {
		head = node;
		return;
	}/* end of if */

	Node* fNode = head;
	head = node;
	fNode->previous_ = head;
	head->next_ = fNode;
}//end of template<class Key> void ListOperations<Key>::InsertNode()

template<class Key> typename ListOperations<Key>::Node* ListOperations<Key>::FindNode(Node* node, Node* head) const {
#ifdef __ALGORITHM_DEBUG__
#define D_FindNode_ 1
#else
#define D_FindNode_ 0
#endif

	if (D_FindNode_) {
		assert(head != 0);
	}/* end of if */

	if (head->item_ == node->item_) {
		return head;
	}/* end of if */

	Node* curr = head;
	while ( curr->next_ != 0 ) {
		curr = curr->next_;
		if ( curr->item_ == node->item_ ) {
			return curr;
		}//end of if 
	}//end of while

	return 0;
}//end of template<class Key> typename ListOperations<Key>::Node* ListOperations<Key>::FindNode()

template<class Key> typename ListOperations<Key>::Node* ListOperations<Key>::FindMinimum(Node* head) const {
#ifdef __ALGORITHM_DEBUG__
#define D_FindMinimum_ 1
#else
#define D_FindMinimum_ 0
#endif

	if (D_FindMinimum_) {
		assert(head != 0);
	}/* end of if */

	Node* minNode = head;
	Node* node = head;

	while(node != 0) {
		if (node->item_ < minNode->item_) {
			minNode = node;
		}/* end of if */

		node = node->next_;
	}//end of while

	return minNode;
}//end of template<class Key> typename ListOperations<Key>::Node* ListOperations<Key>::FindMinimum()

template<class Key> typename ListOperations<Key>::Node* ListOperations<Key>::FindMaximum(Node* head) const {
#ifdef __ALGORITHM_DEBUG__
#define D_FindMaximum_ 1
#else
#define D_FindMaximum_ 0
#endif

	if (D_FindMaximum_) {
		assert(head != 0);
	}/* end of if */

	Node* minNode = head;
	Node* node = head;

	while(node != 0) {
		if (minNode->item_ < node->item_) {
			minNode = node;
		}/* end of if */

		node = node->next_;
	}//end of while

	return minNode;
}//end of template<class Key> typename ListOperations<Key>::Node* ListOperations<Key>::FindMaximum()

template<class Key> typename ListOperations<Key>::Node* ListOperations<Key>::FindSuccessor(Node* node) const {
#ifdef __ALGORITHM_DEBUG__
#define D_FindSuccessor_ 1
#else
#define D_FindSuccessor_ 0
#endif

	if ( D_FindSuccessor_ ) {
		assert(node != 0);
	}//end of if 

	if ( node->next_ == 0 && node->previous_ == 0 ) {
		return 0;
	}/* end of if */

	Node* successor = 0;

	Node* curr = node;
	while ( curr->next_ != 0 ) {
		curr = curr->next_;

		if ( (successor == 0) && (curr->item_ > node->item_) ) {
			successor = curr;
		}/* end of if */

		if ( (successor != 0) && (successor->item_ > curr->item_) && (curr->item_ > node->item_) ) {
			successor = curr;
		}/* end of if */
	}//end of while

	while ( curr->previous_ != 0 ) {
		curr = curr->previous_;

		if ( (successor == 0) && (curr->item_ > node->item_) ) {
			successor = curr;
		}/* end of if */

		if ( (successor != 0) && (successor->item_ > curr->item_) && (curr->item_ > node->item_) ) {
			successor = curr;
		}/* end of if */
	}//end of while

	return successor;
}//end of template<class Key> typename ListOperations<Key>::Node* ListOperations<Key>::FindSuccessor()

template<class Key> typename ListOperations<Key>::Node* ListOperations<Key>::FindPredecessor(Node* node) const {
#ifdef __ALGORITHM_DEBUG__
#define D_FindPredecessor_ 1
#else
#define D_FindPredecessor_ 0
#endif

	if ( D_FindPredecessor_ ) {
		assert(node != 0);
	}//end of if 
	if ( node->next_ == 0 && node->previous_ == 0 ) {
		return 0;
	}/* end of if */

	Node* predecessor = 0;

	Node* curr = node;
	while ( curr->next_ != 0 ) {
		curr = curr->next_;

		if ( (predecessor == 0) && (curr->item_ < node->item_) ) {
			predecessor = curr;
		}/* end of if */

		if ( (predecessor != 0) && (predecessor->item_ < curr->item_) && (curr->item_ < node->item_) ) {
			predecessor = curr;
		}/* end of if */
	}//end of while

	while ( curr->previous_ != 0 ) {
		curr = curr->previous_;

		if ( (predecessor == 0) && (curr->item_ < node->item_) ) {
			predecessor = curr;
		}/* end of if */

		if ( (predecessor != 0) && (predecessor->item_ < curr->item_) && (curr->item_ < node->item_) ) {
			predecessor = curr;
		}/* end of if */
	}//end of while

	return predecessor;
}//end of template<class Key> typename ListOperations<Key>::Node* ListOperations<Key>::FindPredecessor()

template<class Key> void ListOperations<Key>::DeleteNode(Node* node, Node*& head) {
#ifdef __ALGORITHM_DEBUG__
#define D_DeleteNode_ 1
#else
#define D_DeleteNode_ 0
#endif

	if ( D_DeleteNode_ ) {
		assert(head != 0);
		assert(node != 0);
	}//end of if 

	Node* previousNode = node->previous_;
	Node* nextNode = node->next_;
	if ( previousNode != 0 ) {
		previousNode->next_ = nextNode;
	}//end of if 

	if ( nextNode != 0 ) {
		nextNode->previous_ = previousNode;
	}//end of if 

	if ( node == head ) {
		head = head->next_;
	}//end of if 
}//end of template<class Key> typename ListOperations<Key>::Node* ListOperations<Key>::DeleteNode()

} /* Private */

} /* AwesomeLibrary */ 

#endif /* end of include guard: LIST_OPERATIONS_H_ */
