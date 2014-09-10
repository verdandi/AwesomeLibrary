#include "../sources/RBTOperations.h"

#include "test_framework.h"

namespace AwesomeLibrary {

class RedBlackTreeOperationsTest: public ::testing::Test {
public:
	typedef RedBlackTreeOperations<int>::Node Node;

	virtual void SetUp(){}

	virtual void TearDown(){}
};//end of declaration class BinarySearchTreeOperationsTest: public ::testing::Test

TEST_F(RedBlackTreeOperationsTest, LeftRotateTest){
	Node* root = new Node(0);
	Node* copyRoot = root;
	Node* one = new Node(1);
	Node* two = new Node(2);
	Node* three = new Node(3);
	Node* four = new Node(4);
	Node* five = new Node(5);
	Node* six = new Node(6);
	root->left_ = four;
	root->right_ = one;
	one->parent_ = root;
	four->parent_ = root;
	one->left_ = two;
	one->right_ = three;
	three->parent_ = one;
	two->parent_ = one;
	three->left_ = five;
	three->right_ = six;
	six->parent_ = three;
	five->parent_ = three;

	RedBlackTreeOperations<int> treeOperations;
	treeOperations.LeftRotate(copyRoot, root);
	EXPECT_TRUE(one == root);
	EXPECT_TRUE(one->parent_ == Node::Nil());
	EXPECT_TRUE(one->left_ == copyRoot);
	EXPECT_TRUE(copyRoot->parent_ == one);
	EXPECT_TRUE(copyRoot->right_ == two);

	Node* seven = new Node(7);
	Node* eight = new Node(8);
	six->left_ = seven;
	six->right_ = eight;
	seven->parent_ = six;
	eight->parent_ = six;

	Node* newRoot = one;
	treeOperations.LeftRotate(three, one);
	EXPECT_TRUE(newRoot == one);
	EXPECT_TRUE(six->left_ == three);
	EXPECT_TRUE(three->parent_ == six);
	EXPECT_TRUE(six->parent_ == one);
	EXPECT_TRUE(three->right_ == seven);

	delete copyRoot;
	delete one;
	delete two;
	delete three;
	delete four;
	delete five;
	delete six;
	delete seven;
	delete eight;
}

TEST_F(RedBlackTreeOperationsTest, RightRotateTest){
	Node* root = new Node(0);
	Node* copyRoot = root;
	Node* one = new Node(1);
	Node* two = new Node(2);
	Node* three = new Node(3);
	Node* four = new Node(4);
	root->left_ = one;
	root->right_ = two;
	two->parent_ = root;
	one->parent_ = root;
	one->left_ = three;
	one->right_ = four;
	three->parent_ = one;
	four->parent_ = one;

	RedBlackTreeOperations<int> treeOperations;
	treeOperations.RightRotate(copyRoot, root);
	EXPECT_TRUE(one == root);
	EXPECT_TRUE(one->right_ == copyRoot);
	EXPECT_TRUE(copyRoot->parent_ == one);
	EXPECT_TRUE(copyRoot->left_ == four);
	EXPECT_TRUE(four->parent_ == copyRoot);

	Node* five = new Node(5);
	Node* six = new Node(6);
	four->left_ = five;
	four->right_ = six;
	five->parent_ = four;
	six->parent_ = four;

	treeOperations.RightRotate(copyRoot, root);
	EXPECT_TRUE(four->right_ == copyRoot);
	EXPECT_TRUE(copyRoot->parent_ == four);
	EXPECT_TRUE(copyRoot->left_ == six);
	EXPECT_TRUE(six->parent_ == copyRoot);

	delete copyRoot;
	delete one;
	delete two;
	delete three;
	delete four;
	delete five;
	delete six;
}


TEST_F(RedBlackTreeOperationsTest, InsertNodeTest){
	Node* root = Node::Nil();
	Node* node1 = new Node(2);
	Node* node2 = new Node(3);
	Node* node3 = new Node(1);
	Node* node4 = new Node(4);

	RedBlackTreeOperations<int> treeOperations;
	treeOperations.InsertNode(node1, root);
	EXPECT_TRUE(root == node1);
	EXPECT_TRUE(node1->parent_ == Node::Nil());
	EXPECT_TRUE(node1->left_ == Node::Nil());
	EXPECT_TRUE(node1->right_ == Node::Nil());
	treeOperations.InsertNode(node2, root);
	EXPECT_TRUE(node1->right_ == node2);
	EXPECT_TRUE(node1->parent_ == Node::Nil());
	EXPECT_TRUE(node1->left_ == Node::Nil());
	EXPECT_TRUE(node2->parent_ == node1);
	treeOperations.InsertNode(node3, root);
	EXPECT_TRUE(node1->parent_ == Node::Nil());
	EXPECT_TRUE(node1->left_ == node3);
	EXPECT_TRUE(node1->right_ == node2);
	treeOperations.InsertNode(node4, root);
	EXPECT_TRUE(node1->parent_ == Node::Nil());
	EXPECT_TRUE(node2->parent_ == node1);
	EXPECT_TRUE(node2->right_ == node4);
	EXPECT_TRUE(node2->left_ == Node::Nil());

	delete node1;
	delete node2;
	delete node3;
	delete node4;
}

TEST_F(RedBlackTreeOperationsTest, FindNodeTest){
	Node* root = Node::Nil();
	Node* node1 = new Node(2);
	Node* node2 = new Node(3);
	Node* node3 = new Node(1);
	Node* node4 = new Node(4);

	RedBlackTreeOperations<int> treeOperations;
	treeOperations.InsertNode(node1, root);
	treeOperations.InsertNode(node2, root);
	treeOperations.InsertNode(node3, root);
	treeOperations.InsertNode(node4, root);

	Node* findNode = treeOperations.FindNode(node1, Node::Nil());
	EXPECT_TRUE(findNode == Node::Nil());
	findNode = treeOperations.FindNode(node1, root);
	EXPECT_EQ(findNode->item_, node1->item_);
	findNode = treeOperations.FindNode(node2, root);
	EXPECT_EQ(findNode->item_, node2->item_);
	findNode = treeOperations.FindNode(node3, root);
	EXPECT_EQ(findNode->item_, node3->item_);
	findNode = treeOperations.FindNode(node4, root);
	EXPECT_EQ(findNode->item_, node4->item_);
	Node otherNode(5);
	findNode = treeOperations.FindNode(&otherNode, root);
	EXPECT_TRUE(findNode == Node::Nil());

	delete node1;
	delete node2;
	delete node3;
	delete node4;
}

TEST_F(RedBlackTreeOperationsTest, FindMinimumTest){
	Node* root = Node::Nil();
	Node* node1 = new Node(2);
	Node* node2 = new Node(3);
	Node* node3 = new Node(1);
	Node* node4 = new Node(4);

	RedBlackTreeOperations<int> treeOperations;
	treeOperations.InsertNode(node1, root);
	treeOperations.InsertNode(node2, root);
	treeOperations.InsertNode(node3, root);
	treeOperations.InsertNode(node4, root);

	Node* findNode = treeOperations.FindMinimum(root);
	EXPECT_EQ(findNode->item_, node3->item_);

	delete node1;
	delete node2;
	delete node3;
	delete node4;
}

TEST_F(RedBlackTreeOperationsTest, FindMaximumTest){
	Node* root = Node::Nil();
	Node* node1 = new Node(2);
	Node* node2 = new Node(3);
	Node* node3 = new Node(1);
	Node* node4 = new Node(4);

	RedBlackTreeOperations<int> treeOperations;
	treeOperations.InsertNode(node1, root);
	treeOperations.InsertNode(node2, root);
	treeOperations.InsertNode(node3, root);
	treeOperations.InsertNode(node4, root);

	Node* findNode = treeOperations.FindMaximum(root);
	EXPECT_EQ(findNode->item_, node4->item_);

	delete node1;
	delete node2;
	delete node3;
	delete node4;
}

TEST_F(RedBlackTreeOperationsTest, FindSuccessorTest){
	Node* root = 0;
	Node* node1 = new Node(1);
	Node* node2 = new Node(5);
	Node* node3 = new Node(2);
	Node* node4 = new Node(7);
	Node* node5 = new Node(3);
	Node* node6 = new Node(6);

	RedBlackTreeOperations<int> treeOperations;
	treeOperations.InsertNode(node1, root);
	treeOperations.InsertNode(node2, root);
	treeOperations.InsertNode(node3, root);
	treeOperations.InsertNode(node4, root);
	treeOperations.InsertNode(node5, root);
	treeOperations.InsertNode(node6, root);

	Node* findNode = treeOperations.FindSuccessor(node5);
	EXPECT_EQ(findNode->item_, node2->item_);
	findNode = treeOperations.FindSuccessor(node2);
	EXPECT_EQ(findNode->item_, node6->item_);

	delete node1;
	delete node2;
	delete node3;
	delete node4;
	delete node5;
	delete node6;
}

TEST_F(RedBlackTreeOperationsTest, FindPredecessorTest){
	Node* root = Node::Nil();
	Node* node1 = new Node(1);
	Node* node2 = new Node(5);
	Node* node3 = new Node(2);
	Node* node4 = new Node(7);
	Node* node5 = new Node(3);
	Node* node6 = new Node(6);

	RedBlackTreeOperations<int> treeOperations;
	treeOperations.InsertNode(node1, root);
	treeOperations.InsertNode(node2, root);
	treeOperations.InsertNode(node3, root);
	treeOperations.InsertNode(node4, root);
	treeOperations.InsertNode(node5, root);
	treeOperations.InsertNode(node6, root);

	Node* findNode = treeOperations.FindPredecessor(node3);
	EXPECT_EQ(findNode->item_, node1->item_);
	findNode = treeOperations.FindPredecessor(node2);
	EXPECT_EQ(findNode->item_, node5->item_);

	delete node1;
	delete node2;
	delete node3;
	delete node4;
	delete node5;
	delete node6;
}

TEST_F(RedBlackTreeOperationsTest, DeleteNodeTest){
	//удалить листовой узел, проверить качество работы функции DeleteNode
	Node* root = Node::Nil();
	Node* node1 = new Node(2);
	Node* node2 = new Node(1);
	Node* node3 = new Node(3);

	RedBlackTreeOperations<int> treeOperations;
	treeOperations.InsertNode(node1, root);
	treeOperations.InsertNode(node2, root);
	treeOperations.InsertNode(node3, root);

	Node* deletedNode = treeOperations.DeleteNode(node3, root);
	EXPECT_TRUE(root->item_ == 2);
	EXPECT_TRUE(root->left_->item_ == 1);
	EXPECT_TRUE(root->right_ == Node::Nil());
	EXPECT_TRUE(deletedNode->item_ == 3);

	deletedNode = treeOperations.DeleteNode(node2, root);
	EXPECT_TRUE(deletedNode->item_ == 1);
	EXPECT_TRUE(root->item_ == 2);
	EXPECT_TRUE(root->left_ == Node::Nil());
	EXPECT_TRUE(root->right_ == Node::Nil());

	delete node1;
	delete node2;
	delete node3;

	//удалить узел с одним правым дочерним узлом
	root = 0;
	node1 = new Node(2);
	node2 = new Node(1);
	node3 = new Node(3);
	Node* node4 = new Node(5);
	Node* node5 = new Node(6);
	Node* node6 = new Node(4);

	treeOperations.InsertNode(node1, root);
	treeOperations.InsertNode(node2, root);
	treeOperations.InsertNode(node3, root);
	treeOperations.InsertNode(node4, root);
	treeOperations.InsertNode(node5, root);
	treeOperations.InsertNode(node6, root);

	deletedNode = treeOperations.DeleteNode(node3, root);
	EXPECT_TRUE(root->item_ == 2);
	EXPECT_TRUE(root->left_->item_ == 1);
	EXPECT_TRUE(root->right_->item_ == 5);
	EXPECT_TRUE(root->right_->left_->item_ == 4);
	EXPECT_TRUE(root->right_->right_->item_ == 6);

	delete node1;
	delete node2;
	delete node3;
	delete node4;
	delete node5;
	delete node6;
}

} /* AwesomeLibrary */ 
