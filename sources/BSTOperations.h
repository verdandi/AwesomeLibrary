#ifndef TREE_OPERATIONS_H_
#define TREE_OPERATIONS_H_

#include "defines.h"

namespace AwesomeLibrary {

namespace Private {

template<class Key> struct Node {
/*
узел бинарного дерева поиска
*/
	Node* parent_;
	Node* left_;
	Node* right_;
	Key item_;

	explicit Node(const Key& item): parent_(Nil()), left_(Nil()), right_(Nil()), item_(item) {}

	Node(): parent_(this), left_(this), right_(this), item_(Key()) {}

	static bool Less(const Node* lhs, const Node* rhs) {
		return lhs->item_ < rhs->item_;
	}//end of static bool Less()

	static bool Equal(const Node* lhs, const Node* rhs) {
		return lhs->item_ == rhs->item_;
	}//end of static bool Equal()

	static Node* Nil(){
		static Node nil;
		return &nil;
	}
};//end of declaration Node

} /* Private */ 

template<class Key> class BinarySearchTreeOperations {
/*
класс, содержащий базовые операции бинарного дерева поиска в контексте узлов дерева
При разработке методов данного класса полагается, что в них поступают только верные данные
*/

#ifndef __ALGORITHM_TEST__
protected:
#else
public:
#endif
	BinarySearchTreeOperations () {}
	~BinarySearchTreeOperations() {}

typedef Private::Node<Key> Node;

/*
Функция
	void InsertNode(const Node<Key>* newNode, const Node<Key>* root);
вставляет узел в дерево в надлежащем месте
Принимаемые параметры:
newNode - новый вставляемый узел
root - корневой узел дерева в которое необходимо вставить новый узел
*/
	void InsertNode(Node* newNode, Node*& root);

/*
Функция
	Node* FindNode(Node* node, Node* root);
ищет узел с заданными пользовательскими данными и возвращает указатель на его позицию в дереве
Принимаемые параметры:
node - искомый узел с заданными данными
root - корень дерева, в котором надо искать узел
Возвращаемые параметры:
указатель на позицию узла в дереве или 0
*/
	Node* FindNode(Node* node, Node* root) const;

/*
Функция
	Node* FindMinimum(Node* root) const;
ищет минимальный элемент в дереве
Принимаемые параметры:
root - корень дерева где необходимо производить поиск
Возвращаемое значение:
указатель на позицию в дереве, которую занимает минимальный эелемент
*/
	Node* FindMinimum(Node* root) const;

/*
Функция
	Node* FindMaximum(Node* root) const;
ищет максимальный элемент в дереве
Принимаемые параметры:
root - корень дерева где необходимо производить поиск
Возвращаемое значение:
указатель на позицию в дереве, которую занимает максимальный элемент
*/
	Node* FindMaximum(Node* root) const;

/*
функиция
	Node* FindSuccessor(Node* node, Node* root) const;
ищет узел следующий по порядку за данным
Принимаемые параметры:
node - заданный узел
Возвращаемые параметры:
указатель на позицию узла в дереве или 0
*/
	Node* FindSuccessor(Node* node) const;

/*
функиция
	Node* FindPredecessor(Node* node, Node* root) const;
ищет узел предыдущий по порядку за данным
Принимаемые параметры:
node - заданный узел
Возвращаемые параметры:
указатель на позицию узла в дереве или 0
*/
	Node* FindPredecessor(Node* node) const;

/*
Функция
	void DeleteNode(Node* node, Node*& root);
удаляет из дерева заданный узел
Принимаемые параметры:
node - заданый узел
root - корень дерева из которого надо удалить узел
Возвращаемые параметры:
указатель на удаленный узел.
*/
	Node* DeleteNode(Node* node, Node*& root);
};//end of declaration class BinarySearchTreeOperations

template<class Key>
void BinarySearchTreeOperations<Key>::InsertNode(BinarySearchTreeOperations<Key>::Node* newNode,
												BinarySearchTreeOperations<Key>::Node*& root) {
#ifdef __ALGORITHM_DEBUG__
#define D_InsertNode_ 1
#else
#define D_InsertNode_ 0
#endif

		if (D_InsertNode_) {
			assert(newNode->right_ == Node::Nil());
			assert(newNode->left_ == Node::Nil());
		}/* end of if */

	if (root == Node::Nil()) {
		root = newNode;
		return;
	}/* end of if */

	if (Node::Less(root, newNode) && root->right_ == Node::Nil()) {
		root->right_ = newNode;
		newNode->parent_ = root;
		return;
	}/* end of if */

	if (Node::Less(newNode, root) && root->left_ == Node::Nil()) {
		root->left_ = newNode;
		newNode->parent_ = root;
		return;
	}/* end of if */

	if (Node::Less(root, newNode) && root->right_ != Node::Nil()) {
		InsertNode(newNode, root->right_);
		return;
	}/* end of if */

	if (Node::Less(newNode, root) && root->left_ != Node::Nil()) {
		InsertNode(newNode, root->left_);
		return;
	}/* end of if */
}//end of template<class Key> void BinarySearchTreeOperations<Key>::InsertNode()

template<class Key>
typename BinarySearchTreeOperations<Key>::Node*
BinarySearchTreeOperations<Key>::FindNode(BinarySearchTreeOperations<Key>::Node* node,
								BinarySearchTreeOperations<Key>::Node* root) const {
#ifdef __ALGORITHM_DEBUG__
#define D_FindNode_ 1
#else
#define D_FindNode_ 0
#endif

	if (D_FindNode_) {
		assert(node != Node::Nil());
	}/* end of if */

	if (root == Node::Nil()) {
		return Node::Nil();
	}/* end of if */

	if (Node::Equal(node, root)) {
		return root;
	}/* end of if */

	if (Node::Less(root, node)) {
		return FindNode(node, root->right_);
	}/* end of if */

	if (Node::Less(node, root)) {
		return FindNode(node, root->left_);
	}/* end of if */

	return 0;//чтобы компилятор не ругался
}//end of template<class Key> Node* BinarySearchTreeOperations<Key>::FindNode()

template<class Key>
typename BinarySearchTreeOperations<Key>::Node*
BinarySearchTreeOperations<Key>::FindMinimum(BinarySearchTreeOperations<Key>::Node* root) const {
#ifdef __ALGORITHM_DEBUG__
#define D_FindMinimum_ 1
#else
#define D_FindMinimum_ 0
#endif

	if (D_FindMinimum_) {
		assert(root != Node::Nil());
	}/* end of if */

	Node* minNode = root;
	while(minNode->left_ != Node::Nil()) {
		minNode = minNode->left_;
	}//end of while

	return minNode;
}//end of template<class Key> typename BinarySearchTreeOperations<Key>::Node* BinarySearchTreeOperations<Key>::FindMinimum()

template<class Key>
typename BinarySearchTreeOperations<Key>::Node*
BinarySearchTreeOperations<Key>::FindMaximum(BinarySearchTreeOperations<Key>::Node* root) const {
#ifdef __ALGORITHM_DEBUG__
#define D_FindMaximum_ 1
#else
#define D_FindMaximum_ 0
#endif

	if (D_FindMaximum_) {
		assert(root != Node::Nil());
	}/* end of if */

	Node* maxNode = root;
	while(maxNode->right_ != Node::Nil()) {
		maxNode = maxNode->right_;
	}//end of while

	return maxNode;
}//end of template<class Key> typename BinarySearchTreeOperations<Key>::Node* BinarySearchTreeOperations<Key>::FindMaximum()

template<class Key>
typename BinarySearchTreeOperations<Key>::Node*
BinarySearchTreeOperations<Key>::FindSuccessor(BinarySearchTreeOperations<Key>::Node* node) const {
#ifdef __ALGORITHM_DEBUG__
#define D_FindSuccessor_ 1
#else
#define D_FindSuccessor_ 0
#endif

	if (D_FindSuccessor_) {
		assert(node != Node::Nil());
	}/* end of if */

	if (node->right_ != Node::Nil()) {
		return FindMinimum(node->right_);
	}/* end of if */

	Node* parentNode = node->parent_;
	while(parentNode != Node::Nil() && node == parentNode->right_) {
		node = parentNode;
		parentNode = parentNode->parent_;
	}//end of while

	return parentNode;
}//end of template<class Key> BinarySearchTreeOperations<Key>::Node* BinarySearchTreeOperations<Key>::FindSuccessor()

template<class Key>
typename BinarySearchTreeOperations<Key>::Node*
BinarySearchTreeOperations<Key>::FindPredecessor(BinarySearchTreeOperations<Key>::Node* node) const {
#ifdef __ALGORITHM_DEBUG__
#define D_FindPredecessor_ 1
#else
#define D_FindPredecessor_ 0
#endif

	if (D_FindPredecessor_) {
		assert(node != Node::Nil());
	}/* end of if */

	if (node->left_ != Node::Nil()) {
		return FindMaximum(node->left_);
	}/* end of if */

	Node* parentNode = node->parent_;
	while(parentNode != Node::Nil() && node == parentNode->left_) {
		node = parentNode;
		parentNode = parentNode->parent_;
	}//end of while

	return parentNode;
}//end of template<class Key> BinarySearchTreeOperations<Key>::Node* BinarySearchTreeOperations<Key>::FindPredecessor()

template<class Key>
typename BinarySearchTreeOperations<Key>::Node* BinarySearchTreeOperations<Key>::DeleteNode(Node* node, Node*& root) {
	Node* y = Node::Nil();
	if (node->left_ == Node::Nil() || node->right_ == Node::Nil()) {
		y = node;
	}/* end of if */
	else {
		y = FindSuccessor(node);
	}//end of if

	Node* x = Node::Nil();
	if (y->left_ != Node::Nil()) {
		x = y->left_;
	}/* end of if */
	else {
		x = y->right_;
	}//end of if

	if (x != Node::Nil()) {
		x->parent_ = y->parent_;
	}/* end of if */

	if (y->parent_ == Node::Nil()) {
		root = x;
	}/* end of if */
	else {
		if (y == y->parent_->left_) {
			y->parent_->left_ = x;
		}/* end of if */
		else {
			y->parent_->right_ = x;
		}//end of if
	}//end of if

	if (y != node) {
		node->item_ = y->item_;
	}// end of if

	return y;
}//end of template<class Key> typename BinarySearchTreeOperations<Key>::Node* BynarySearchTreeOperations<Key>::DeleteNode()

} /* AwesomeLibrary */ 

#endif /* end of include guard: TREE_OPERATIONS_H_ */
