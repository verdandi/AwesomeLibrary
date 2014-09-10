#include "../sources/BSTOperations.h"

#include "test_framework.h"

namespace AwesomeLibrary {

class BinarySearchTreeOperationsTest: public ::testing::Test {
public:
	typedef BinarySearchTreeOperations<int>::Node Node;

	virtual void SetUp(){}

	virtual void TearDown(){}
};//end of declaration class BinarySearchTreeOperationsTest: public ::testing::Test


TEST_F(BinarySearchTreeOperationsTest, BinarySearchTreeOperationsTest_InsertNodeTest){
	Node* root = Node::Nil();
	Node* node1 = new Node(2);
	Node* node2 = new Node(3);
	Node* node3 = new Node(1);
	Node* node4 = new Node(4);

	BinarySearchTreeOperations<int> treeOperations;
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

TEST_F(BinarySearchTreeOperationsTest, BinarySearchTreeOperationsTest_FindNodeTest){
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

TEST_F(BinarySearchTreeOperationsTest, BinarySearchTreeOperationsTest_FindMinimumTest){
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

	Node* findNode = treeOperations.FindMinimum(root);
	EXPECT_EQ(findNode->item_, node3->item_);

	delete node1;
	delete node2;
	delete node3;
	delete node4;
}

TEST_F(BinarySearchTreeOperationsTest, BinarySearchTreeOperationsTest_FindMaximumTest){
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

	Node* findNode = treeOperations.FindMaximum(root);
	EXPECT_EQ(findNode->item_, node4->item_);

	delete node1;
	delete node2;
	delete node3;
	delete node4;
}

TEST_F(BinarySearchTreeOperationsTest, BinarySearchTreeOperationsTest_FindSuccessorTest){
	Node* root = Node::Nil();
	Node* node1 = new Node(1);
	Node* node2 = new Node(5);
	Node* node3 = new Node(2);
	Node* node4 = new Node(7);
	Node* node5 = new Node(3);
	Node* node6 = new Node(6);

	BinarySearchTreeOperations<int> treeOperations;
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

TEST_F(BinarySearchTreeOperationsTest, BinarySearchTreeOperationsTest_FindPredecessorTest){
	Node* root = Node::Nil();
	Node* node1 = new Node(1);
	Node* node2 = new Node(5);
	Node* node3 = new Node(2);
	Node* node4 = new Node(7);
	Node* node5 = new Node(3);
	Node* node6 = new Node(6);

	BinarySearchTreeOperations<int> treeOperations;
	treeOperations.InsertNode(node1, root);
	treeOperations.InsertNode(node2, root);
	treeOperations.InsertNode(node3, root);
	treeOperations.InsertNode(node4, root);
	treeOperations.InsertNode(node5, root);
	treeOperations.InsertNode(node6, root);

	Node* findNode = treeOperations.FindPredecessor(node3);
	EXPECT_EQ(findNode->item_, root->item_);
	findNode = treeOperations.FindPredecessor(node2);
	EXPECT_EQ(findNode->item_, node5->item_);

	delete node1;
	delete node2;
	delete node3;
	delete node4;
	delete node5;
	delete node6;
}

TEST_F(BinarySearchTreeOperationsTest, DeleteNodeTest){
	//удалить листовой узел, проверить качество работы функции DeleteNode
	Node* root = Node::Nil();
	Node* node1 = new Node(2);
	Node* node2 = new Node(1);
	Node* node3 = new Node(3);

	BinarySearchTreeOperations<int> treeOperations;
	treeOperations.InsertNode(node1, root);
	treeOperations.InsertNode(node2, root);
	treeOperations.InsertNode(node3, root);

	Node* deletedNode = treeOperations.DeleteNode(node3, root);
	EXPECT_TRUE(root->item_ == 2);
	EXPECT_TRUE(root->left_->item_ == 1);
	EXPECT_TRUE(deletedNode->item_ == 3);

	//deletedNode = treeOperations.DeleteNode(node2, root);
	//EXPECT_TRUE(deletedNode->item_ == 1);
	//EXPECT_TRUE(root->item_ == 2);
	//EXPECT_TRUE(root->left_ == 0);
	//EXPECT_TRUE(root->right_ == 0);

	//delete node1;
	//delete node2;
	//delete node3;

	////удалить узел с одним правым дочерним узлом
	//root = 0;
	//node1 = new Node(2);
	//node2 = new Node(1);
	//node3 = new Node(3);
	//Node* node4 = new Node(5);
	//Node* node5 = new Node(6);
	//Node* node6 = new Node(4);

	//treeOperations.InsertNode(node1, root);
	//treeOperations.InsertNode(node2, root);
	//treeOperations.InsertNode(node3, root);
	//treeOperations.InsertNode(node4, root);
	//treeOperations.InsertNode(node5, root);
	//treeOperations.InsertNode(node6, root);

	//deletedNode = treeOperations.DeleteNode(node3, root);
	//EXPECT_TRUE(root->item_ == 2);
	//EXPECT_TRUE(root->left_->item_ == 1);
	//EXPECT_TRUE(root->right_->item_ == 5);
	//EXPECT_TRUE(root->right_->left_->item_ == 4);
	//EXPECT_TRUE(root->right_->right_->item_ == 6);

	//delete node1;
	//delete node2;
	//delete node3;
	//delete node4;
	//delete node5;
	//delete node6;

	////удалить узел с одним левым дочерним узлом
	//root = 0;
	//node1 = new Node(9);
	//node2 = new Node(6);
	//node3 = new Node(4);
	//node4 = new Node(3);
	//node5 = new Node(5);

	//treeOperations.InsertNode(node1, root);
	//treeOperations.InsertNode(node2, root);
	//treeOperations.InsertNode(node3, root);
	//treeOperations.InsertNode(node4, root);
	//treeOperations.InsertNode(node5, root);

	//deletedNode = treeOperations.DeleteNode(node2, root);
	//EXPECT_TRUE(root->item_ == 9);
	//EXPECT_TRUE(root->left_->item_ == 4);
	//EXPECT_TRUE(root->left_->right_->item_ == 5);
	//EXPECT_TRUE(root->left_->left_->item_ == 3);

	//delete node1;
	//delete node2;
	//delete node3;
	//delete node4;
	//delete node5;

	////удалить узел с двумя дочерними узлами
	//root = 0;
	//node1 = new Node(8);
	//node2 = new Node(7);
	//node3 = new Node(3);
	//node4 = new Node(1);
	//node5 = new Node(6);
	//node6 = new Node(4);
	//Node* node7 = new Node(5);

	//treeOperations.InsertNode(node1, root);
	//treeOperations.InsertNode(node2, root);
	//treeOperations.InsertNode(node3, root);
	//treeOperations.InsertNode(node4, root);
	//treeOperations.InsertNode(node5, root);
	//treeOperations.InsertNode(node6, root);
	//treeOperations.InsertNode(node7, root);

	//deletedNode = treeOperations.DeleteNode(node3, root);
	//EXPECT_TRUE(root->item_ == 8);
	//EXPECT_TRUE(root->left_->item_ == 7);
	//EXPECT_TRUE(root->left_->left_->item_ == 4);
	//EXPECT_TRUE(root->left_->left_->left_->item_ == 1);
	//EXPECT_TRUE(root->left_->left_->right_->item_ == 6);
	//EXPECT_TRUE(root->left_->left_->right_->left_->item_ == 5);
	//EXPECT_TRUE(root->left_->left_->right_->left_->left_ == 0);

	//delete node1;
	//delete node2;
	//delete node3;
	//delete node4;
	//delete node5;
	//delete node6;
	//delete node7;

	////удалить корневой узел без дочерних узлов
	//root = 0;
	//node1 = new Node(1);
	//treeOperations.InsertNode(node1, root);

	//deletedNode = treeOperations.DeleteNode(node1, root);
	//EXPECT_TRUE(deletedNode->item_ == 1);
	//EXPECT_TRUE(root == 0);

	//delete node1;

	////удалить корневой узел с одним дочерним узлом
	//root = 0;
	//node1 = new Node(1);
	//node2 = new Node(2);

	//treeOperations.InsertNode(node1, root);
	//treeOperations.InsertNode(node2, root);

	//deletedNode = treeOperations.DeleteNode(node1, root);
	//EXPECT_TRUE(root->item_ = 1);
	//EXPECT_TRUE(root->left_ == 0);
	//EXPECT_TRUE(root->right_ == 0);

	//delete node1;
	//delete node2;

	////удалить корневой узел с двумя дочерними узлами
	//root = 0;
	//node1 = new Node(2);
	//node2 = new Node(1);
	//node3 = new Node(3);

	//treeOperations.InsertNode(node1, root);
	//treeOperations.InsertNode(node2, root);
	//treeOperations.InsertNode(node3, root);

	//deletedNode = treeOperations.DeleteNode(node1, root);
	//EXPECT_TRUE(deletedNode->item_ == 3);
	//EXPECT_TRUE(root->item_ == 3);
	//EXPECT_TRUE(root->left_->item_ == 1);
	//EXPECT_TRUE(root->right_ == 0);

	//delete node1;
	//delete node2;
	//delete node3;
}

} /* AwesomeLibrary */ 
