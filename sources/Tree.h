#ifndef TREE_H_
#define TREE_H_

#include "defines.h"

#include "BSTOperations.h"
#include "RBTOperations.h"

namespace AwesomeLibrary {

template<class Key, template<class> class TreeOperations> class Tree;

namespace Private {

template<class Key, template<class> class TreeOperations> class TreeIterator: public TreeOperations<Key>{
/*итератор для контейнера Tree*/
public:
#ifdef __ALGORITHM_TEST__
	friend class TreeIteratorTest;
	FRIEND_TEST(TreeIteratorTest, TreeIterator_ConstructorTest);
	FRIEND_TEST(TreeIteratorTest, TreeIterator_CopyConstructorTest);
	FRIEND_TEST(TreeIteratorTest, TreeIterator_AssignmentTest);
	FRIEND_TEST(TreeIteratorTest, TreeIterator_EqualTest);
	FRIEND_TEST(TreeIteratorTest, TreeIterator_NotEqualTest);
	FRIEND_TEST(TreeIteratorTest, TreeIterator_IncrementTest);
	FRIEND_TEST(TreeIteratorTest, TreeIterator_DecrementTest);
	FRIEND_TEST(TreeIteratorTest, TreeIterator_UnnameOperator);
	FRIEND_TEST(TreeIteratorTest, RBTIterator_ConstructorTest);
	FRIEND_TEST(TreeIteratorTest, RBTIterator_CopyConstructorTest);
	FRIEND_TEST(TreeIteratorTest, RBTIterator_AssignmentTest);
	FRIEND_TEST(TreeIteratorTest, RBTIterator_EqualTest);
	FRIEND_TEST(TreeIteratorTest, RBTIterator_NotEqualTest);
	FRIEND_TEST(TreeIteratorTest, RBTIterator_IncrementTest);
	FRIEND_TEST(TreeIteratorTest, RBTIterator_DecrementTest);
	FRIEND_TEST(TreeIteratorTest, RBTIterator_UnnameOperator);
#endif

typedef typename TreeOperations<Key>::Node Node;

	TreeIterator(): node_(Node::Nil()) {}

	TreeIterator(const TreeIterator& otherIter){
		node_ = otherIter.node_;
	}

	~TreeIterator(){}

	TreeIterator& operator=(const TreeIterator& otherIter){
		node_ = otherIter.node_;
		return *this;
	}

	bool operator==(const TreeIterator& otherIter){
		return node_ == otherIter.node_;
	}

	bool operator!=(const TreeIterator& otherIter){
		return node_ != otherIter.node_;
	}

	Key& operator*() const {
		return node_->item_;
	}//end of const T& operator*()

/*
Функция
	TreeIterator operator++();
переводит итератор на элемент дерева, ключ которого следующий по порядку за ключем элемента,
на который итератор указывает в данный момент
*/
	TreeIterator& operator++() {
		node_ = this->FindSuccessor(node_);
		return *this;
	}//end of Iterator operator++()

/*
Функция
	TreeIterator& operator--();
переводит итератор на элемент дерева, ключ которого предыдущий по порядку за ключем элемента,
на который итератор указывает в данный момент
*/
	TreeIterator& operator--() {
		node_= this->FindPredecessor(node_);
		return *this;
	}//end of Iterator& operator--()

private:
	friend class Tree<Key, TreeOperations>;
	//этим конструктором может пользоваться только класс Tree
	TreeIterator(Node* node): node_(node) {}

	Node* node_;
};

} /* Private */ 

template<class Key, template<class> class TreeOperations>
class Tree: public TreeOperations<Key> {
/*
Класс, реализующий словарную структуру "дерево":
	Key - тип элементов которые должны храниться в контейнере
Ключем может быть любой базовый тип или пользовательский, поддерживающий конструктор копирования
и оператор присваивания, а также операции "<" и "=="

	TreeOperations - класс предоставляющий базовые операции с деревом.
Этот класс должен предоставлять локальный класс Node, а также методы:
	void InsertNode(Node* node, Node*& root)
вставляет узел node в дерево с корнем root
	Node* FindNode(Node* node, Node* root)
ищет узел node в дереве с корнем root
	Node* FindMinimum(Node* root)
возвращает указатель на узел с минимальным ключем в дереве с корнем root
	Node* FindMaximum(Node* root)
возвращает указатель на узел с максимальным ключем в дереве с корнем root
	Node* FindSuccessor(Node* node)
возвращает указатель на узел с ключем, следующем за ключем в заданном узле
	Node* FindPredecessor(Node* node)
возвращает указатель на узел ключем, предышествующем ключу в заданном узле
	Node* DeleteNode(Node* node)
удаляет зааданный узел из дерева, возвращает указатель на узел, занявший позицию удаленного
*/
private:
	typedef typename TreeOperations<Key>::Node Node;

public:
#ifdef __ALGORITHM_TEST__
	friend class TreeTest;
	FRIEND_TEST(TreeTest, Tree_InsertTest);
	FRIEND_TEST(TreeTest, Tree_FindTest);
	FRIEND_TEST(TreeTest, Tree_BeginTest);
	FRIEND_TEST(TreeTest, Tree_EndTest);
	FRIEND_TEST(TreeTest, Tree_MinimumTest);
	FRIEND_TEST(TreeTest, Tree_MaximumTest);
	FRIEND_TEST(TreeTest, Tree_SuccessorTest);
	FRIEND_TEST(TreeTest, Tree_PredecessorTest);
	FRIEND_TEST(TreeTest, Tree_DeleteTest);
	FRIEND_TEST(TreeTest, RBTree_InsertTest);
	FRIEND_TEST(TreeTest, RBTree_FindTest);
	FRIEND_TEST(TreeTest, RBTree_BeginTest);
	FRIEND_TEST(TreeTest, RBTree_EndTest);
	FRIEND_TEST(TreeTest, RBTree_MinimumTest);
	FRIEND_TEST(TreeTest, RBTree_MaximumTest);
	FRIEND_TEST(TreeTest, RBTree_SuccessorTest);
	FRIEND_TEST(TreeTest, RBTree_PredecessorTest);
	FRIEND_TEST(TreeTest, RBTree_DeleteTest);
#endif

	typedef Private::TreeIterator<Key, TreeOperations> Iterator;


	Tree (): root_(Node::Nil()) {}
	~Tree ();

	/*
	функция
		void Insert(const Key& newKey);
	вставляет в дерево новый элемент, c заданным ключем
	Принимаемые параметры:
	newKey - элемент, который необходимо вставить в дерево
	*/
	void Insert(const Key& newKey);

	/*
	Функция
		Iterator Begin()
	Возвращает итератор, указывающий на элемент с минимальным ключем
	В случае если дерево пустое, возвращает итератор проинициализированный 0
	*/
	Iterator Begin() const;

	/*
	Функция
		Iterator End();
	Возвращает итератор, проинициализированный нулем
	*/
	Iterator End() const;

	/*
	Функция
		Iterator Minimum() const
	Возвращает итератор, указывающий на элемент с минимальным ключем
	В случае, если дерево пустое возвращает итератор, проинициализированный 0
	*/
	Iterator Minimum() const;

	/*
	Функция
		Iterator Maximum();
	Возвращает итератор, указывающий на элемент с максимальным ключем
	В случае, если дерево пустое возвращает итератор, проинициализированный 0
	*/
	Iterator Maximum() const;

	/*
	Функция
		Iterator Successor(const Key& key);
	Возвращает итератор на элемент дерева с ключем, который следует
	по порядку за заданным.
	В случем если такой элемент не находится или дерево пустое, возвращает итератор,
	проинициализированный 0.
	Принимаемые параметры:
	- key - заданный ключ
	*/
	Iterator Successor(const Key& key) const;

	/*
	Функция
		Iterator Predecessor(const Key& key) const;
	возвращает итератор на элемент дерева с ключем, который предшествует заданному.
	В случае если такой елемент не находится или дерево пустое, возвращает итератор,
	проинициализированный 0
	Принимаемые параметры:
	key - искомый ключ
	*/
	Iterator Predecessor(const Key& key) const;

	/*
	Функция
		void Delete(const Key& key);
	Удаляет элемент с заданным ключем из дерева.
	Принимаемые параметры:
	- key - удаляемый ключ
	*/
	void Delete(const Key& key);

	/*
	функция
		bool Find(const Key& key)
	возвращает true если обнаружит в дереве элемент item
	и false, если дерево пустое или элемент не найден
	*/
	Iterator Find(const Key& key) const;

	bool Empty() const;

private:
	Node* root_;
};//end of declaration class Tree: public TreeOperations<T>

template<class Key, template<class> class TreeOperations>
 Tree<Key, TreeOperations>::~Tree() {
	while(root_ != Node::Nil()) {
		Delete(root_->item_);
	}//end of while
}//end of  Tree<Key, TreeOperations>::~Tree()


template<class Key, template<class> class TreeOperations>
void Tree<Key, TreeOperations>::Insert(const Key& newKey) {
	Node* newNode = new Node(newKey);
	this->InsertNode(newNode, root_);
}//end of void Tree<Key, TreeOperations>::Insert()

template<class Key, template<class> class TreeOperations>
typename Tree<Key, TreeOperations>::Iterator Tree<Key, TreeOperations>::Find(const Key& key) const{
	//создаем узел с заданным ключем, а затем ищем узел таким же ключем в дереве
	if (root_ == Node::Nil()) {
		return End();
	}/* end of if */

	Node newNode(key);
	Node* foundNode = this->FindNode(&newNode, root_);
	return Iterator(foundNode);
}//end of bool Tree<Key, TreeOperations>::Find()

template<class Key, template<class> class TreeOperations>
typename Tree<Key, TreeOperations>::Iterator Tree<Key, TreeOperations>::Begin() const {
	if (root_ == Node::Nil()) {
		return Iterator();
	}/* end of if */

	Node* nodeWithMinKey = this->FindMinimum(root_);
	return Iterator(nodeWithMinKey);
}//end of typename Tree<Key, TreeOperations>::Iterator Tree<Key, TreeOperations>::Begin()

template<class Key, template<class> class TreeOperations>
typename Tree<Key, TreeOperations>::Iterator Tree<Key, TreeOperations>::End() const {
	return Iterator();
}//end of typename Tree<Key, TreeOperations>::Iterator Tree<Key, TreeOperations>::End()

template<class Key, template<class> class TreeOperations>
typename Tree<Key, TreeOperations>::Iterator Tree<Key, TreeOperations>::Minimum() const {
	if (root_ == Node::Nil()) {
		return Iterator();
	}/* end of if */

	Node* nodeWithMinKey = this->FindMinimum(root_);
	return Iterator(nodeWithMinKey);
}//end of typename Tree<Key, TreeOperations>::Iterator Tree<Key, TreeOperations>::Mi()

template<class Key, template<class> class TreeOperations>
typename Tree<Key, TreeOperations>::Iterator Tree<Key, TreeOperations>::Maximum() const {
	if (root_ == Node::Nil()) {
		return Iterator();
	}/* end of if */

	Node* nodeWithMaxKey = this->FindMaximum(root_);
	return Iterator(nodeWithMaxKey);
}//end of typename Tree<Key, TreeOperations>::Iterator Tree<Key, TreeOperations>::Maximum()

template<class Key, template<class> class TreeOperations>
typename Tree<Key, TreeOperations>::Iterator Tree<Key, TreeOperations>::Successor(const Key& key) const {
	if (root_ == Node::Nil()) {
		return Iterator();
	}/* end of if */

	Node node(key);
	Node* fNode = this->FindNode(&node, root_);
	if (fNode == Node::Nil()) {
		return Iterator();
	}/* end of if */

	Node* sNode = this->FindSuccessor(fNode);

	return Iterator(sNode);
}//end of typename Tree<Key, TreeOperations>::Iterator Tree<Key, TreeOperations>::Successor()

template<class Key, template<class> class TreeOperations>
typename Tree<Key, TreeOperations>::Iterator Tree<Key, TreeOperations>::Predecessor(const Key& key) const {
	if (root_ == Node::Nil()) {
		return Iterator();
	}/* end of if */

	Node node(key);
	Node* fNode = this->FindNode(&node, root_);
	if (fNode == Node::Nil()) {
		return Iterator();
	}/* end of if */

	Node* sNode = this->FindPredecessor(fNode);
	return Iterator(sNode);
}//end of typename Tree<Key, TreeOperations>::Iterator Tree<Key, TreeOperations>::Predecessor()

template<class Key, template<class> class TreeOperations>
void Tree<Key, TreeOperations>::Delete(const Key& key) {
	if (root_ == Node::Nil()) {
		return;
	}/* end of if */

	Node node(key);
	Node* fNode = this->FindNode(&node, root_);
	if (fNode == Node::Nil()) {
		return;
	}/* end of if */

	Node *deletedNode = this->DeleteNode(fNode, root_);
	delete deletedNode;
	deletedNode = 0;
}//end of typename Tree<Key, TreeOperations>::Iterator Tree<Key, TreeOperations>::Delete()

template<class Key, template<class> class TreeOperations>
bool Tree<Key, TreeOperations>::Empty() const {
	return root_ == 0 ? true : false;
}//end of bool Tree<Key, TreeOperations>::Empty()

} /* AwesomeLibrary */ 

#endif /* end of include guard: TREE_H_ */
