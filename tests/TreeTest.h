#include "../sources/Tree.h"

#include "test_framework.h"

namespace AwesomeLibrary {

namespace Private{

class TreeIteratorTest: public ::testing::Test {
public:
	typedef BinarySearchTreeOperations<int>::Node Node;
	typedef Tree<int, BinarySearchTreeOperations> BSTree;
	typedef BSTree::Iterator Iterator;
	typedef RedBlackTreeOperations<int>::Node RBNode;
	typedef Tree<int, RedBlackTreeOperations> RBTree;
	typedef RBTree::Iterator RBTIterator;

	virtual void SetUp () {}
	virtual void TearDown () {}
};//end of declaration class TestTree: public ::testing::Test


TEST_F(TreeIteratorTest, TreeIterator_ConstructorTest){
	Node* node1 = new Node(1);
	Iterator it(node1);
	EXPECT_TRUE(it.node_ == node1);
	Iterator it1;
	EXPECT_TRUE(it1.node_ == Node::Nil());

	delete node1;
}

TEST_F(TreeIteratorTest, TreeIterator_CopyConstructorTest){
	Node* node1 = new Node(1);
	Iterator it1(node1);
	Iterator it2 = it1;
	EXPECT_TRUE(it1.node_ == node1);
	EXPECT_TRUE(it2.node_ == it1.node_);

	delete node1;
}

TEST_F(TreeIteratorTest, TreeIterator_AssignmentTest){
	Node* node1 = new Node(1);
	Node* node2 = new Node(2);
	Iterator it1(node1);
	Iterator it2(node2);
	EXPECT_TRUE(it1.node_ == node1);
	EXPECT_TRUE(it2.node_ == node2);
	it1 = it2;
	EXPECT_TRUE(it1.node_ == it2.node_);

	delete node1;
	delete node2;
}

TEST_F(TreeIteratorTest, TreeIterator_EqualTest){
	Node* node1 = new Node(1);
	Node* node2 = new Node(2);
	Iterator it1(node1);
	Iterator it2(node2);
	Iterator it3(node1);
	EXPECT_FALSE(it1 == it2);
	EXPECT_TRUE(it1 == it3);

	delete node1;
	delete node2;
}

TEST_F(TreeIteratorTest, TreeIterator_NotEqualTest){
	Node* node1 = new Node(1);
	Node* node2 = new Node(2);
	Iterator it1(node1);
	Iterator it2(node2);
	Iterator it3(node1);
	EXPECT_TRUE(it1 != it2);
	EXPECT_FALSE(it1 != it3);

	delete node1;
	delete node2;
}

TEST_F(TreeIteratorTest, TreeIterator_UnnameOperator){
	Node* node1 = new Node(1);
	Iterator it1(node1);
	EXPECT_EQ(*it1, 1);
}

TEST_F(TreeIteratorTest, TreeIterator_IncrementTest){
	//создаем небольшое дерево
	Node* root = Node::Nil();
	Node* node1 = new Node(2);
	Node* node2 = new Node(3);
	Node* node3 = new Node(1);
	Node* node4 = new Node(4);

	BinarySearchTreeOperations<int> treeOperations;
	treeOperations.InsertNode(node1, root);
	treeOperations.InsertNode(node2, root);
	treeOperations.InsertNode(node3, root);
	treeOperations.InsertNode(node4, root);

	//пробуем вызывать operator++ и проверяем значение члена node_ класса Iterator
	Iterator it(node3);
	++it;
	EXPECT_TRUE(it.node_ == node1);
	++it;
	EXPECT_TRUE(it.node_ == node2);
	++it;
	EXPECT_TRUE(it.node_ == node4);
	++it;
	EXPECT_TRUE(it.node_ == Node::Nil());

	delete node1;
	delete node2;
	delete node3;
	delete node4;
}

TEST_F(TreeIteratorTest, TreeIterator_DecrementTest){
	//создаем небольшое дереве
	Node* root = Node::Nil();
	Node* node1 = new Node(2);
	Node* node2 = new Node(3);
	Node* node3 = new Node(1);
	Node* node4 = new Node(4);

	BinarySearchTreeOperations<int> treeOperations;
	treeOperations.InsertNode(node1, root);
	treeOperations.InsertNode(node2, root);
	treeOperations.InsertNode(node3, root);
	treeOperations.InsertNode(node4, root);

	//пробуем вызывать operator-- и проверяем значение члена node_ класса Iterator
	Iterator it(node4);
	--it;
	EXPECT_TRUE(it.node_ == node2);
	--it;
	EXPECT_TRUE(it.node_ == node1);
	--it;
	EXPECT_TRUE(it.node_ == node3);
	--it;
	EXPECT_TRUE(it.node_ == Node::Nil());

	delete node1;
	delete node2;
	delete node3;
	delete node4;
}

TEST_F(TreeIteratorTest, RBTIterator_ConstructorTest){
	RBNode* node1 = new RBNode(1);
	RBTIterator it(node1);
	EXPECT_TRUE(it.node_ == node1);
	RBTIterator it1;
	EXPECT_TRUE(it1.node_ == RBNode::Nil());

	delete node1;
}

TEST_F(TreeIteratorTest, RBTIterator_CopyConstructorTest){
	RBNode* node1 = new RBNode(1);
	RBTIterator it1(node1);
	RBTIterator it2 = it1;
	EXPECT_TRUE(it1.node_ == node1);
	EXPECT_TRUE(it2.node_ == it1.node_);

	delete node1;
}

TEST_F(TreeIteratorTest, RBTIterator_AssignmentTest){
	RBNode* node1 = new RBNode(1);
	RBNode* node2 = new RBNode(2);
	RBTIterator it1(node1);
	RBTIterator it2(node2);
	EXPECT_TRUE(it1.node_ == node1);
	EXPECT_TRUE(it2.node_ == node2);
	it1 = it2;
	EXPECT_TRUE(it1.node_ == it2.node_);

	delete node1;
	delete node2;
}

TEST_F(TreeIteratorTest, RBTIterator_EqualTest){
	RBNode* node1 = new RBNode(1);
	RBNode* node2 = new RBNode(2);
	RBTIterator it1(node1);
	RBTIterator it2(node2);
	RBTIterator it3(node1);
	EXPECT_FALSE(it1 == it2);
	EXPECT_TRUE(it1 == it3);

	delete node1;
	delete node2;
}

TEST_F(TreeIteratorTest, RBTIterator_NotEqualTest){
	RBNode* node1 = new RBNode(1);
	RBNode* node2 = new RBNode(2);
	RBTIterator it1(node1);
	RBTIterator it2(node2);
	RBTIterator it3(node1);
	EXPECT_TRUE(it1 != it2);
	EXPECT_FALSE(it1 != it3);

	delete node1;
	delete node2;
}

TEST_F(TreeIteratorTest, RBTIterator_UnnameOperator){
	RBNode* node1 = new RBNode(1);
	RBTIterator it1(node1);
	EXPECT_EQ(*it1, 1);
}

TEST_F(TreeIteratorTest, RBTIterator_IncrementTest){
	//создаем небольшое дерево
	RBNode* root = RBNode::Nil();
	RBNode* node1 = new RBNode(2);
	RBNode* node2 = new RBNode(3);
	RBNode* node3 = new RBNode(1);
	RBNode* node4 = new RBNode(4);

	RedBlackTreeOperations<int> treeOperations;
	treeOperations.InsertNode(node1, root);
	treeOperations.InsertNode(node2, root);
	treeOperations.InsertNode(node3, root);
	treeOperations.InsertNode(node4, root);

	//пробуем вызывать operator++ и проверяем значение члена node_ класса Iterator
	RBTIterator it(node3);
	++it;
	EXPECT_TRUE(it.node_ == node1);
	++it;
	EXPECT_TRUE(it.node_ == node2);
	++it;
	EXPECT_TRUE(it.node_ == node4);
	++it;
	EXPECT_TRUE(it.node_ == RBNode::Nil());

	delete node1;
	delete node2;
	delete node3;
	delete node4;
}

TEST_F(TreeIteratorTest, RBTIterator_DecrementTest){
	//создаем небольшое дереве
	RBNode* root = RBNode::Nil();
	RBNode* node1 = new RBNode(2);
	RBNode* node2 = new RBNode(3);
	RBNode* node3 = new RBNode(1);
	RBNode* node4 = new RBNode(4);

	RedBlackTreeOperations<int> treeOperations;
	treeOperations.InsertNode(node1, root);
	treeOperations.InsertNode(node2, root);
	treeOperations.InsertNode(node3, root);
	treeOperations.InsertNode(node4, root);

	//пробуем вызывать operator-- и проверяем значение члена node_ класса Iterator
	RBTIterator it(node4);
	--it;
	EXPECT_TRUE(it.node_ == node2);
	--it;
	EXPECT_TRUE(it.node_ == node1);
	--it;
	EXPECT_TRUE(it.node_ == node3);
	--it;
	EXPECT_TRUE(it.node_ == RBNode::Nil());

	delete node1;
	delete node2;
	delete node3;
	delete node4;
}

} /* Private */


class TreeTest: public ::testing::Test {
public:
	typedef BinarySearchTreeOperations<int>::Node BSTNode;
	typedef Tree<int, BinarySearchTreeOperations> BSTree;
	typedef BSTree::Iterator Iterator;
	typedef RedBlackTreeOperations<int>::Node RBTNode;
	typedef Tree<int, RedBlackTreeOperations> RBTree;
	typedef RBTree::Iterator RBIterator;

	virtual void SetUp () {}
	virtual void TearDown () {}
};//end of declaration class TestTree: public ::testing::Test


TEST_F(TreeTest, Tree_InsertTest){
	//создать объект класса Tree<int, BinarySearchTree>
	BSTree t;
	EXPECT_TRUE(t.root_ == BSTNode::Nil());

	//вставить несколько новых элементов в дерево и проверить, что дерево формируется правильно
	t.Insert(2);
	EXPECT_TRUE(t.root_ != BSTNode::Nil());
	EXPECT_TRUE(t.root_->left_ == BSTNode::Nil());
	EXPECT_TRUE(t.root_->right_ == BSTNode::Nil());
	EXPECT_EQ(t.root_->item_, 2);

	t.Insert(1);
	EXPECT_EQ(t.root_->left_->item_, 1);

	t.Insert(3);
	EXPECT_EQ(t.root_->right_->item_, 3);

	t.Insert(4);
	EXPECT_EQ(t.root_->right_->right_->item_, 4);

	//delete t.root_->right_->right_;
	//delete t.root_->right_;
	//delete t.root_->left_;
	//delete t.root_;
}

TEST_F(TreeTest, Tree_FindTest){
	//создать объект класса Tree<int, BinarySearchTree>
	BSTree t;

	//проверяем, что функция Tree<>::Find()
	//возвращает false для пустого дерева
	EXPECT_TRUE(t.Find(4) == t.End());

	//вставить несколько новых элементов в дерево
	t.Insert(2);
	t.Insert(1);
	t.Insert(3);
	t.Insert(4);

	//осуществить поиск элементов, которые есть в дереве
	EXPECT_TRUE(*t.Find(2) == 2);
	EXPECT_TRUE(*t.Find(1) == 1);
	EXPECT_TRUE(*t.Find(4) == 4);
	EXPECT_TRUE(*t.Find(3) == 3);

	//осуществить поиск элементов, которых нет в дереве
	EXPECT_TRUE(t.Find(5) == t.End());
}

TEST_F(TreeTest, Tree_BeginTest){
	//содать объект класса Tree<int, BinarySearchTree>
	BSTree t;

	//проверить, что для пустого дереве операция Tree<>::Begin()
	//возвращает указатель, проинициализированный 0
	Iterator it;
	Iterator it1 = t.Begin();
	EXPECT_TRUE(it1 == it);
	
	//вставить один элемент в дерево
	//проверить, что функция Tree<>::Begin()
	//возвращает итератор, указывающий на него
	t.Insert(2);
	it = t.Begin();
	EXPECT_EQ(*it, 2);

	//вставить еще несколько элементов в дерево
	t.Insert(1);
	t.Insert(3);
	t.Insert(4);
	
	//убедиться, что функция Tree<>::Begin() возвращает
	//итератор на элемент с наименьшим ключем
	BSTree::Iterator it2 = t.Begin();
	EXPECT_EQ(*it2, 1);
	
	//очистить ресурсы
	//delete t.root_->right_->right_;
	//delete t.root_->right_;
	//delete t.root_->left_;
	//delete t.root_;
}

TEST_F(TreeTest, Tree_EndTest){
	//содать объект класса Tree<int, BinarySearchTree>
	BSTree t;
	
	//вставить несколько элементов в дерево
	t.Insert(2);
	t.Insert(1);
	t.Insert(3);
	t.Insert(4);
	
	//убедиться, что функция Tree<>::End() возвращает
	//итератор проинициализированный нулем
	BSTree::Iterator it = t.End();
	BSTree::Iterator it1;
	EXPECT_TRUE(it == it1);
	
	//очистить ресурсы
	//delete t.root_->right_->right_;
	//delete t.root_->right_;
	//delete t.root_->left_;
	//delete t.root_;
}

TEST_F(TreeTest, Tree_MinimumTest){
	//содать объект класса Tree<int, BinarySearchTree>
	//проверить, что функция Tree<>::Minimum(),
	//возвращает итератор, проинициализированный 0
	BSTree t;
	BSTree::Iterator it1 = t.Minimum();
	EXPECT_TRUE(it1 == t.End());
	
	//вставить один элемент в дерево и проверить, что
	//функция Tree<>::Minimum(), возвращает указатель на него
	t.Insert(2);
	it1 = t.Minimum();
	EXPECT_EQ(*it1, 2);

	//вставить еще несколько элементов в дерево
	t.Insert(1);
	t.Insert(3);
	t.Insert(4);
	
	//убедиться, что функция Tree<>::Minimum() возвращает
	//итератор, указывающий на элемент с минимальным ключем
	BSTree::Iterator it = t.Minimum();
	EXPECT_EQ(*it, 1);
	
	//очистить ресурсы
	//delete t.root_->right_->right_;
	//delete t.root_->right_;
	//delete t.root_->left_;
	//delete t.root_;
}

TEST_F(TreeTest, Tree_MaximumTest){
	//содать объект класса Tree<int, BinarySearchTree>
	//проверить, что функция Tree<>::Maximum(),
	//возвращает итератор, проинициализированный 0
	BSTree t;
	BSTree::Iterator it1 = t.Maximum();
	EXPECT_TRUE(it1 == t.End());

	//вставить 1 элемент в дерево и убедиться, что 
	//функция Tree<>::Maximum() возвращает
	//итератор, указывающий на этот элемент
	t.Insert(2);
	it1 = t.Maximum();
	EXPECT_EQ(*it1, 2);

	//вставить еще несколько элементов в дерево
	t.Insert(1);
	t.Insert(3);
	t.Insert(4);
	
	//убедиться, что функция Tree<>::Maximum() возвращает
	//итератор, указвающий на элемент с максимальным ключем
	BSTree::Iterator it = t.Maximum();
	EXPECT_EQ(*it, 4);
	
	//очистить ресурсы
	//delete t.root_->right_->right_;
	//delete t.root_->right_;
	//delete t.root_->left_;
	//delete t.root_;
}

TEST_F(TreeTest, Tree_SuccessorTest){
	//создать объект класса Tree<int, BinarySearchTree>
	//проверить, что функция Tree<>::Successor(), 
	//возвращает итератор, проинициализированный 0
	BSTree t;
	BSTree::Iterator it = t.Successor(2);
	EXPECT_TRUE(it == t.End());

	//вставить один элемент в дерево. Проверить,
	//что фукнция Tree<>::Successor() возвращает
	//итератор проинициализированный 0
	t.Insert(4);
	it = t.Successor(4);
	EXPECT_TRUE(it == t.End());

	//Вставить еще несколько элементов в дерево.
	//Убедаться, что функция Tree<>::Successor() 
	//возвращает итератор, указывающий на элемент с подходящим ключем
	t.Insert(2);
	t.Insert(3);
	t.Insert(6);
	t.Insert(5);
	t.Insert(7);
	it = t.Successor(2);
	EXPECT_EQ(*it, 3);
	it = t.Successor(3);
	EXPECT_EQ(*it, 4);
	it = t.Successor(4);
	EXPECT_EQ(*it, 5);

	//очистить ресурсы
	//delete t.root_->right_->right_;
	//delete t.root_->right_->left_;
	//delete t.root_->right_;
	//delete t.root_->left_->right_;
	//delete t.root_->left_;
	//delete t.root_;
}

TEST_F(TreeTest, Tree_PredecessorTest){
	//создать объект класса Tree<int, BinarySearchTree>
	//проверить, что функция Tree<>::Predecessor(), 
	//возвращает итератор, проинициализированный 0
	BSTree t;
	BSTree::Iterator it = t.Predecessor(2);
	EXPECT_TRUE(it == t.End());

	//вставить один элемент в дерево. Проверить,
	//что фукнция Tree<>::Predecessor() возвращает
	//итератор проинициализированный 0
	t.Insert(4);
	it = t.Predecessor(4);
	EXPECT_TRUE(it == t.End());

	//Вставить еще несколько элементов в дерево.
	//Убедаться, что функция Tree<>::Predecessor() 
	//возвращает итератор, указывающий на элемент с подходящим ключем
	t.Insert(2);
	t.Insert(3);
	t.Insert(6);
	t.Insert(5);
	t.Insert(7);
	it = t.Predecessor(7);
	EXPECT_EQ(*it, 6);
	it = t.Predecessor(6);
	EXPECT_EQ(*it, 5);
	it = t.Predecessor(5);
	EXPECT_EQ(*it, 4);

	//очистить ресурсы
	//delete t.root_->right_->right_;
	//delete t.root_->right_->left_;
	//delete t.root_->right_;
	//delete t.root_->left_->right_;
	//delete t.root_->left_;
	//delete t.root_;
}

TEST_F(TreeTest, Tree_DeleteTest){
	BSTree t;
	t.Insert(2);
	t.Insert(3);
	t.Delete(3);
	BSTree::Iterator it = t.Begin();
	EXPECT_TRUE(*it == 2);
	++it;
	EXPECT_TRUE(it == t.End());
	//вставить еще несколько элементов. Проверить, что функция
	//Tree<>::Delete правильно обрабатывает их удаление
	t.Insert(1);
	t.Insert(3);
	t.Insert(4);

	t.Delete(3);
	EXPECT_EQ(t.root_->item_, 2);
	EXPECT_EQ(t.root_->right_->item_, 4);

	t.Delete(2);
	EXPECT_EQ(t.root_->item_, 4);
	EXPECT_TRUE(t.root_->right_ == BSTNode::Nil());
	EXPECT_EQ(t.root_->left_->item_, 1);

	t.Delete(1);
	EXPECT_EQ(t.root_->item_, 4);
	EXPECT_TRUE(t.root_->left_ == BSTNode::Nil());

	t.Delete(4);
	EXPECT_TRUE(t.root_ == BSTNode::Nil());
}

TEST_F(TreeTest, RBTree_InsertTest){
	//создать объект класса Tree<int, BinarySearchTree>
	RBTree t;
	EXPECT_TRUE(t.root_ == RBTNode::Nil());

	//вставить несколько новых элементов в дерево и проверить, что дерево формируется правильно
	t.Insert(2);
	EXPECT_TRUE(t.root_ != RBTNode::Nil());
	EXPECT_TRUE(t.root_->left_ == RBTNode::Nil());
	EXPECT_TRUE(t.root_->right_ == RBTNode::Nil());
	EXPECT_EQ(t.root_->item_, 2);

	t.Insert(1);
	EXPECT_EQ(t.root_->left_->item_, 1);

	t.Insert(3);
	EXPECT_EQ(t.root_->right_->item_, 3);

	t.Insert(4);
	EXPECT_EQ(t.root_->right_->right_->item_, 4);

	//delete t.root_->right_->right_;
	//delete t.root_->right_;
	//delete t.root_->left_;
	//delete t.root_;
}

TEST_F(TreeTest, RBTree_FindTest){
	//создать объект класса Tree<int, BinarySearchTree>
	RBTree t;

	//проверяем, что функция Tree<>::Find()
	//возвращает false для пустого дерева
	EXPECT_TRUE(t.Find(4) == t.End());

	//вставить несколько новых элементов в дерево
	t.Insert(2);
	t.Insert(1);
	t.Insert(3);
	t.Insert(4);

	//осуществить поиск элементов, которые есть в дереве
	EXPECT_TRUE(*t.Find(2) == 2);
	EXPECT_TRUE(*t.Find(1) == 1);
	EXPECT_TRUE(*t.Find(4) == 4);
	EXPECT_TRUE(*t.Find(3) == 3);

	//осуществить поиск элементов, которых нет в дереве
	EXPECT_TRUE(t.Find(5) == t.End());
}

TEST_F(TreeTest, RBTree_BeginTest){
	//содать объект класса Tree<int, BinarySearchTree>
	RBTree t;

	//проверить, что для пустого дереве операция Tree<>::Begin()
	//возвращает указатель, проинициализированный 0
	RBIterator it;
	RBIterator it1 = t.Begin();
	EXPECT_TRUE(it1 == it);
	
	//вставить один элемент в дерево
	//проверить, что функция Tree<>::Begin()
	//возвращает итератор, указывающий на него
	t.Insert(2);
	it = t.Begin();
	EXPECT_EQ(*it, 2);

	//вставить еще несколько элементов в дерево
	t.Insert(1);
	t.Insert(3);
	t.Insert(4);
	
	//убедиться, что функция Tree<>::Begin() возвращает
	//итератор на элемент с наименьшим ключем
	RBTree::Iterator it2 = t.Begin();
	EXPECT_EQ(*it2, 1);
	
	//очистить ресурсы
	//delete t.root_->right_->right_;
	//delete t.root_->right_;
	//delete t.root_->left_;
	//delete t.root_;
}

TEST_F(TreeTest, RBTree_EndTest){
	//содать объект класса Tree<int, BinarySearchTree>
	RBTree t;
	
	//вставить несколько элементов в дерево
	t.Insert(2);
	t.Insert(1);
	t.Insert(3);
	t.Insert(4);
	
	//убедиться, что функция Tree<>::End() возвращает
	//итератор проинициализированный нулем
	RBTree::Iterator it = t.End();
	RBTree::Iterator it1;
	EXPECT_TRUE(it == it1);
	
	//очистить ресурсы
	//delete t.root_->right_->right_;
	//delete t.root_->right_;
	//delete t.root_->left_;
	//delete t.root_;
}

TEST_F(TreeTest, RBTree_MinimumTest){
	//содать объект класса Tree<int, BinarySearchTree>
	//проверить, что функция Tree<>::Minimum(),
	//возвращает итератор, проинициализированный 0
	RBTree t;
	RBTree::Iterator it1 = t.Minimum();
	EXPECT_TRUE(it1 == t.End());
	
	//вставить один элемент в дерево и проверить, что
	//функция Tree<>::Minimum(), возвращает указатель на него
	t.Insert(2);
	it1 = t.Minimum();
	EXPECT_EQ(*it1, 2);

	//вставить еще несколько элементов в дерево
	t.Insert(1);
	t.Insert(3);
	t.Insert(4);
	
	//убедиться, что функция Tree<>::Minimum() возвращает
	//итератор, указывающий на элемент с минимальным ключем
	RBTree::Iterator it = t.Minimum();
	EXPECT_EQ(*it, 1);
	
	//очистить ресурсы
	//delete t.root_->right_->right_;
	//delete t.root_->right_;
	//delete t.root_->left_;
	//delete t.root_;
}

TEST_F(TreeTest, RBTree_MaximumTest){
	//содать объект класса Tree<int, BinarySearchTree>
	//проверить, что функция Tree<>::Maximum(),
	//возвращает итератор, проинициализированный 0
	RBTree t;
	RBTree::Iterator it1 = t.Maximum();
	EXPECT_TRUE(it1 == t.End());

	//вставить 1 элемент в дерево и убедиться, что 
	//функция Tree<>::Maximum() возвращает
	//итератор, указывающий на этот элемент
	t.Insert(2);
	it1 = t.Maximum();
	EXPECT_EQ(*it1, 2);

	//вставить еще несколько элементов в дерево
	t.Insert(1);
	t.Insert(3);
	t.Insert(4);
	
	//убедиться, что функция Tree<>::Maximum() возвращает
	//итератор, указвающий на элемент с максимальным ключем
	RBTree::Iterator it = t.Maximum();
	EXPECT_EQ(*it, 4);
	
	//очистить ресурсы
	//delete t.root_->right_->right_;
	//delete t.root_->right_;
	//delete t.root_->left_;
	//delete t.root_;
}

TEST_F(TreeTest, RBTree_SuccessorTest){
	//создать объект класса Tree<int, BinarySearchTree>
	//проверить, что функция Tree<>::Successor(), 
	//возвращает итератор, проинициализированный 0
	RBTree t;
	RBTree::Iterator it = t.Successor(2);
	EXPECT_TRUE(it == t.End());

	//вставить один элемент в дерево. Проверить,
	//что фукнция Tree<>::Successor() возвращает
	//итератор проинициализированный 0
	t.Insert(4);
	it = t.Successor(4);
	EXPECT_TRUE(it == t.End());

	//Вставить еще несколько элементов в дерево.
	//Убедаться, что функция Tree<>::Successor() 
	//возвращает итератор, указывающий на элемент с подходящим ключем
	t.Insert(2);
	t.Insert(3);
	t.Insert(6);
	t.Insert(5);
	t.Insert(7);
	it = t.Successor(2);
	EXPECT_EQ(*it, 3);
	it = t.Successor(3);
	EXPECT_EQ(*it, 4);
	it = t.Successor(4);
	EXPECT_EQ(*it, 5);

	//очистить ресурсы
	//delete t.root_->right_->right_;
	//delete t.root_->right_->left_;
	//delete t.root_->right_;
	//delete t.root_->left_->right_;
	//delete t.root_->left_;
	//delete t.root_;
}

TEST_F(TreeTest, RBTree_PredecessorTest){
	//создать объект класса Tree<int, BinarySearchTree>
	//проверить, что функция Tree<>::Predecessor(), 
	//возвращает итератор, проинициализированный 0
	RBTree t;
	RBTree::Iterator it = t.Predecessor(2);
	EXPECT_TRUE(it == t.End());

	//вставить один элемент в дерево. Проверить,
	//что фукнция Tree<>::Predecessor() возвращает
	//итератор проинициализированный 0
	t.Insert(4);
	it = t.Predecessor(4);
	EXPECT_TRUE(it == t.End());

	//Вставить еще несколько элементов в дерево.
	//Убедаться, что функция Tree<>::Predecessor() 
	//возвращает итератор, указывающий на элемент с подходящим ключем
	t.Insert(2);
	t.Insert(3);
	t.Insert(6);
	t.Insert(5);
	t.Insert(7);
	it = t.Predecessor(7);
	EXPECT_EQ(*it, 6);
	it = t.Predecessor(6);
	EXPECT_EQ(*it, 5);
	it = t.Predecessor(5);
	EXPECT_EQ(*it, 4);

	//очистить ресурсы
	//delete t.root_->right_->right_;
	//delete t.root_->right_->left_;
	//delete t.root_->right_;
	//delete t.root_->left_->right_;
	//delete t.root_->left_;
	//delete t.root_;
}

TEST_F(TreeTest, RBTree_DeleteTest){
	RBTree t;
	t.Insert(2);
	t.Insert(3);
	t.Delete(3);
	RBTree::Iterator it = t.Begin();
	EXPECT_TRUE(*it == 2);
	++it;
	EXPECT_TRUE(it == t.End());
	//вставить еще несколько элементов. Проверить, что функция
	//Tree<>::Delete правильно обрабатывает их удаление
	t.Insert(1);
	t.Insert(3);
	t.Insert(4);

	t.Delete(3);
	EXPECT_EQ(t.root_->item_, 2);
	EXPECT_EQ(t.root_->right_->item_, 4);

	t.Delete(2);
	EXPECT_EQ(t.root_->item_, 4);
	EXPECT_TRUE(t.root_->right_ == RBTNode::Nil());
	EXPECT_EQ(t.root_->left_->item_, 1);

	t.Delete(1);
	EXPECT_EQ(t.root_->item_, 4);
	EXPECT_TRUE(t.root_->left_ == RBTNode::Nil());

	t.Delete(4);
	EXPECT_TRUE(t.root_ == RBTNode::Nil());
}

} /* AwesomeLibrary */ 
