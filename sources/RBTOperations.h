#ifndef Red_BLACK_TREE_OPERATIONS_H_
#define Red_BLACK_TREE_OPERATIONS_H_

#include "defines.h"

namespace AwesomeLibrary {

namespace Private {

template<class Key> struct RedBlackTreeNode {
	static const int RED = 0;
	static const int BLACK = 1;
	RedBlackTreeNode* left_;
	RedBlackTreeNode* right_;
	RedBlackTreeNode* parent_;
	Key item_;
	int color_;

	RedBlackTreeNode(): left_(this), right_(this), parent_(this), item_(Key()), color_(BLACK) {}

	explicit RedBlackTreeNode(const Key& item): left_(Nil()), right_(Nil()), parent_(Nil()), item_(item), color_(RED) {}

	static bool Equal(const RedBlackTreeNode* lhs, const RedBlackTreeNode* rhs) {
		return lhs->item_ == rhs->item_;
	}//end of static bool Equal()

	static bool Less(const RedBlackTreeNode* lhs, const RedBlackTreeNode* rhs) {
		return lhs->item_ < rhs->item_;
	}//end of static bool Less()

	static RedBlackTreeNode* Nil() {
		static RedBlackTreeNode nil;
		return &nil;
	}//end of static RedBlackTreeNode* Nil()
};//end of declaration class RedBlackTreeNode

} /* Private */ 

template<class Key> class RedBlackTreeOperations {
/*
класс, содержащий базовые операции красно-черного дерева в контексте узлов дерева
При разработке методов данного класса полагается, что в них поступают только верные данные
*/
#ifdef __ALGORITHM_TEST__
public:
	friend class RedBlackTreeOperationsTest;
	FRIEND_TEST(RedBlackTreeOperationsTest, LeftRotateTest);
	FRIEND_TEST(RedBlackTreeOperationsTest, RightRotateTest);
	FRIEND_TEST(RedBlackTreeOperationsTest, InsertNodeTest);
	FRIEND_TEST(RedBlackTreeOperationsTest, DeleteNodeTest);
#endif

#ifndef __ALGORITHM_TEST__
protected:
#else
public:
#endif
	RedBlackTreeOperations () {}
	~RedBlackTreeOperations() {}

typedef Private::RedBlackTreeNode<Key> Node;

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
	Node* FindPRedecessor(Node* node, Node* root) const;
ищет узел предыдущий по порядку за данным
Принимаемые параметры:
node - заданный узел
Возвращаемые параметры:
указатель на позицию узла в дереве или 0
*/
	Node* FindPredecessor(Node* node) const;

/*
Функция
	void DeleteNode(Node* node, Node* root);
удаляет из дерева заданный узел
Принимаемые параметры:
node - заданый узел
root - корень дерева из которого надо удалить узел
Возвращаемые параметры:
указатель на узел, занявший позицию удаленного. При этом 0 возвращается только если узел был листовым или последним в дереве
*/
	Node* DeleteNode(Node* node, Node*& root);

private:
	/*
	выполнить левый поворот в узле node дерева с корнем root
	Принимаемые параметры:
	- node - узел, относительно которого выполняется поворот
	- root - корень дерева
	*/
	void LeftRotate(Node* node, Node*& root);

	/*
	выполнить правый поворот в узле node дерева с корнем root
	Принимаемые параметры:
	- node - узел, относительно которого выполняется поворот
	- root - корень дерева
	*/
	void RightRotate(Node* node, Node*& root);

	/*
	восстановить красно-черные свойства дерева после вставки
	*/
	void InsertFixup(Node* node, Node*& root);

	/*
	восстановить красно-черные свойства дерева после удаления
	*/
	void DeleteFixup(Node* node, Node*& root);
};//end of declaration class RedBlackTreeOperations

template<class Key> void RedBlackTreeOperations<Key>::InsertNode(Node* node, Node*& root) {
	if (root == 0) {
		root = Node::Nil();
	}/* end of if */

	Node* parent = Node::Nil();
	Node* current = root;
	while(current != Node::Nil()) {
		parent = current;
		if (Node::Less(node, current)) {
			current = current->left_;
		}/* end of if */
		else {
			current = current->right_;
		}//end of if
	}//end of while

	node->parent_ = parent;
	if (parent == Node::Nil()) {
		root = node;
	}/* end of if */
	else {
		if (Node::Less(node, parent)) {
			parent->left_ = node;
		}/* end of if */
		else {
			parent->right_ = node;
		}//end of if
	}//end of if

	node->left_ = Node::Nil();
	node->right_ = Node::Nil();
	node->color_ = Node::RED;
	InsertFixup(node, root);
}//end of template<class Key> void RedBlackTreeOperations<Key>::Insert()

template<class Key> typename RedBlackTreeOperations<Key>::Node* RedBlackTreeOperations<Key>::FindNode(Node* node, Node* root) const {
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

	return Node::Nil();//чтобы компилятор не ругался
}//end of template<class Key> typename RedBlackTreeOperations<Key>::Node* RedBlackTreeOperations<Key>::FindNode()

template<class Key> typename RedBlackTreeOperations<Key>::Node* RedBlackTreeOperations<Key>::FindMinimum(Node* root) const {
	Node* minNode = root;
	while(minNode->left_ != Node::Nil()) {
		minNode = minNode->left_;
	}//end of while

	return minNode;
}//end of template<class Key> typename RedBlackTreeOperations<Key>::Node* RedBlackTreeOperations<Key>::FindMinimum()

template<class Key> typename RedBlackTreeOperations<Key>::Node* RedBlackTreeOperations<Key>::FindMaximum(Node* root) const {
	Node* maxNode = root;
	while(maxNode->right_ != Node::Nil()) {
		maxNode = maxNode->right_;
	}//end of while

	return maxNode;
}//end of template<class Key> typename RedBlackTreeOperations<Key>::Node* RedBlackTreeOperations<Key>::FindMaximum()

template<class Key> typename RedBlackTreeOperations<Key>::Node* RedBlackTreeOperations<Key>::FindSuccessor(Node* node) const {
	if (node->right_ != Node::Nil()) {
		return FindMinimum(node->right_);
	}/* end of if */

	Node* parentNode = node->parent_;
	while(parentNode != Node::Nil() && node == parentNode->right_) {
		node = parentNode;
		parentNode = parentNode->parent_;
	}//end of while

	return parentNode;
}//end of template<class Key> typename RedBlackTreeOperations<Key>::Node* RedBlackTreeOperations<Key>::FindSuccessor()

template<class Key> typename RedBlackTreeOperations<Key>::Node* RedBlackTreeOperations<Key>::FindPredecessor(Node* node) const {
	if (node->left_ != Node::Nil()) {
		return FindMaximum(node->left_);
	}/* end of if */

	Node* parentNode = node->parent_;
	while(parentNode != Node::Nil() && node == parentNode->left_) {
		node = parentNode;
		parentNode = parentNode->parent_;
	}//end of while

	return parentNode;
}//end of template<class Key> typename RedBlackTreeOperations<Key>::Node* RedBlackTreeOperations<Key>::FindPredecessor()

template<class Key> typename RedBlackTreeOperations<Key>::Node* RedBlackTreeOperations<Key>::DeleteNode(Node* node, Node*& root) {
	Node* y = Node::Nil();
	if (node->left_ == Node::Nil() || node->right_ == Node::Nil()) {
		y = node;
	}/* end of if */
	else {
		y = FindPredecessor(node);
	}//end of if

	Node* x = Node::Nil();
	if (y->left_ != Node::Nil()) {
		x = y->left_;
	}/* end of if */
	else {
		x = y->right_;
	}//end of if

	x->parent_ = y->parent_;

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

	if (y->color_ == Node::BLACK) {
		DeleteFixup(x, root);
	}/* end of if */

	return y;
}//end of template<class Key> void RedBlackTreeOperationsTest<Key>::DeleteNode()

template<class Key> void RedBlackTreeOperations<Key>::LeftRotate(Node* node, Node*& root) {
	Node* right = node->right_;
	node->right_ = right->left_;
	if (right->left_ != Node::Nil()) {
		right->left_->parent_ = node;
	}/* end of if */

	right->parent_ = node->parent_;

	if (node->parent_ == Node::Nil()) {
		root = right;
	}/* end of if */
	else if (node == node->parent_->left_) {
		node->parent_->left_ = right;
	}//end of if
	else {
		node->parent_->right_ = right;
	}//end of if

	right->left_ = node;
	node->parent_ = right;
}//end of template<class Key> void RedBlackTreeOperations<Key>::LeftRotate()

template<class Key> void RedBlackTreeOperations<Key>::RightRotate(Node* node, Node*& root) {
	Node* left = node->left_;
	node->left_ = left->right_;
	if (left->right_ != Node::Nil()) {
		left->right_->parent_ = node;
	}/* end of if */

	left->parent_ = node->parent_;

	if (node->parent_ == Node::Nil()) {
		root = left;
	}/* end of if */
	else if (node == node->parent_->left_) {
		node->parent_->left_ = left;
	}//end of if
	else {
		node->parent_->right_ = left;
	}//end of if

	left->right_ = node;
	node->parent_ = left;
}//end of template<class Key> void RedBlackTreeOperations<Key>::RightRotate()

template<class Key> void RedBlackTreeOperations<Key>::InsertFixup(Node* node, Node*& root) {
	//grandparent(n) - родитель родителя n
	//uncle(n) - второй дочерний узел дедушки узла n
	while(node != root && node->parent_->color_ == Node::RED) {
		if (node->parent_ == node->parent_->parent_->left_) {
			Node* uncle = node->parent_->parent_->right_;
			if (uncle->color_ == Node::RED) {
				node->parent_->color_ = Node::BLACK;
				uncle->color_ = Node::BLACK;
				node->parent_->parent_->color_ = Node::RED;
				node = node->parent_->parent_;
			}/* end of if */
			else{
				if (node == node->parent_->right_) {
					node = node->parent_;
					LeftRotate(node, root);
				}//end of if

				node->parent_->color_ = Node::BLACK;
				node->parent_->parent_->color_ = Node::RED;
				RightRotate(node->parent_->parent_, root);
			}//end of if
		}/* end of if */
		else{
			Node* uncle = node->parent_->parent_->left_;
			if (uncle->color_ == Node::RED) {
				node->parent_->color_ = Node::BLACK;
				uncle->color_ = Node::BLACK;
				node->parent_->parent_->color_ = Node::RED;
				node = node->parent_->parent_;
			}/* end of if */
			else{
				if (node == node->parent_->left_) {
					node = node->parent_;
					RightRotate(node, root);
				}//end of if

				node->parent_->color_ = Node::BLACK;
				node->parent_->parent_->color_ = Node::RED;
				LeftRotate(node->parent_->parent_, root);
			}//end of if
		}
	}//end of while

	root->color_ = Node::BLACK;
}//end of template<class Key> void RedBlackTreeOperations<Key>::InsertFixup()

template<class Key> void RedBlackTreeOperations<Key>::DeleteFixup(Node* node, Node*& root) {
	while(node != root && node->color_ == Node::BLACK) {
		if (node == node->parent_->left_) {
			Node* w = node->parent_->right_;
			if (w->color_ == Node::RED) {
				w->color_ = Node::BLACK;
				node->parent_->color_ = Node::RED;
				LeftRotate(node->parent_, root);
				w = node->parent_->right_;
			}/* end of if */
			
			if (w->left_->color_ == Node::BLACK && w->right_->color_ == Node::BLACK) {
				w->color_ = Node::RED;
				node = node->parent_;
			}/* end of if */
			else {
				if (w->right_->color_ == Node::BLACK) {
					w->left_->color_ = Node::BLACK;
					w->color_ = Node::RED;
					RightRotate(w, root);
					w = node->parent_->right_;
				}/* end of if */
				else {
					w->color_ = node->parent_->color_;
					node->parent_->color_ = Node::BLACK;
					w->right_->color_ = Node::BLACK;
					LeftRotate(node->parent_, root);
					node = root;
				}//end of if
			}//end of if
		}/* end of if */
		else {
			Node* w = node->parent_->left_;
			if (w->color_ == Node::RED) {
				w->color_ = Node::BLACK;
				node->parent_->color_ = Node::RED;
				LeftRotate(node->parent_, root);
				w = node->parent_->left_;
			}/* end of if */
			
			if (w->right_->color_ == Node::BLACK && w->left_->color_ == Node::BLACK) {
				w->color_ = Node::RED;
				node = node->parent_;
			}/* end of if */
			else {
				if (w->left_->color_ == Node::BLACK) {
					w->right_->color_ = Node::BLACK;
					w->color_ = Node::RED;
					LeftRotate(w, root);
					w = node->parent_->left_;
				}/* end of if */
				else {
					w->color_ = node->parent_->color_;
					node->parent_->color_ = Node::BLACK;
					w->left_->color_ = Node::BLACK;
					RightRotate(node->parent_, root);
					node = root;
				}//end of if
			}//end of if
		}//end of if
	}//end of while
}//end of template<class Key> void RedBlackTreeOperations<Key>::DeleteFixup()

} /* AwesomeLibrary */ 

#endif /* end of include guard: RED_BLACK_TREE_OPERATIONS_H_ */
