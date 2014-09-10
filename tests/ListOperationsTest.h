#include "../sources/ListOperations.h"

#include "test_framework.h"

namespace AwesomeLibrary {

namespace Private {

class ListOperationsTest: public ::testing::Test {
public:
	typedef ListOperations<int>::Node Node;

	virtual void SetUp() {}

	virtual void TearDown() {}
};//end of declaration class ListOperationsTest: public ::testing::Test

TEST_F(ListOperationsTest, InsertNodeTest){
	Node* head = 0;
	Node* n1 = new Node(1);
	ListOperations<int> listOperations;
	listOperations.InsertNode(n1, head);
	EXPECT_TRUE(head == n1);
	EXPECT_TRUE(head->previous_ == 0);
	EXPECT_TRUE(head->next_ == 0);
	EXPECT_TRUE(head->item_ == n1->item_);

	Node* n2 = new Node(2);
	listOperations.InsertNode(n2, head);
	EXPECT_TRUE(head == n2);
	EXPECT_TRUE(head->previous_ == 0);
	EXPECT_TRUE(head->next_->item_ == n1->item_);
	EXPECT_TRUE(head->item_ == n2->item_);
	EXPECT_TRUE(n1->previous_ == head);

	delete n1;
	delete n2;
}

TEST_F(ListOperationsTest, FindNode){
	Node* head = 0;
	Node* n1 = new Node(0);
	Node* n2 = new Node(-3);
	Node* n3 = new Node(10);
	ListOperations<int> listOperations;
	listOperations.InsertNode(n1, head);
	listOperations.InsertNode(n2, head);
	listOperations.InsertNode(n3, head);

	Node* fNode = listOperations.FindNode(n1, head);
	EXPECT_TRUE(fNode->item_ == n1->item_);

	fNode = listOperations.FindNode(n2, head);
	EXPECT_TRUE(fNode->item_ == n2->item_);

	fNode = listOperations.FindNode(n3, head);
	EXPECT_TRUE(fNode->item_ == n3->item_);

	Node* n4 = new Node(4);
	fNode = listOperations.FindNode(n4, head);
	EXPECT_TRUE(fNode == 0);

	delete n1;
	delete n2;
	delete n3;
	delete n4;
}

TEST_F(ListOperationsTest, FindMinimumTest){
	Node* head = 0;
	Node* n1 = new Node(0);
	Node* n2 = new Node(-3);
	Node* n3 = new Node(10);
	ListOperations<int> listOperations;
	listOperations.InsertNode(n1, head);
	listOperations.InsertNode(n2, head);
	listOperations.InsertNode(n3, head);

	Node* fNode = listOperations.FindMinimum(head);
	EXPECT_EQ(-3, fNode->item_);

	delete n1;
	delete n2;
	delete n3;
}

TEST_F(ListOperationsTest, FindMaximumTest){
	Node* head = 0;
	Node* n1 = new Node(0);
	Node* n2 = new Node(-3);
	Node* n3 = new Node(10);
	ListOperations<int> listOperations;
	listOperations.InsertNode(n1, head);
	listOperations.InsertNode(n2, head);
	listOperations.InsertNode(n3, head);

	Node* fNode = listOperations.FindMaximum(head);
	EXPECT_EQ(10, fNode->item_);

	delete n1;
	delete n2;
	delete n3;
}

TEST_F(ListOperationsTest, FindSuccessor){
	Node* head = 0;
	Node* n1 = new Node(0);
	Node* n2 = new Node(-3);
	Node* n3 = new Node(10);
	ListOperations<int> listOperations;
	listOperations.InsertNode(n1, head);
	listOperations.InsertNode(n2, head);
	listOperations.InsertNode(n3, head);

	Node* fNode = listOperations.FindSuccessor(n2);
	EXPECT_EQ(fNode->item_, 0);
	fNode = listOperations.FindSuccessor(n1);
	EXPECT_EQ(fNode->item_, 10);
	fNode = listOperations.FindSuccessor(n3);
	EXPECT_TRUE(fNode == 0);

	Node* n4 = new Node(5);

	fNode = listOperations.FindSuccessor(n4);
	EXPECT_TRUE(fNode == 0);


	delete n1;
	delete n2;
	delete n3;
	delete n4;
}

TEST_F(ListOperationsTest, FindPredecessor){
	Node* head = 0;
	Node* n1 = new Node(0);
	Node* n2 = new Node(-3);
	Node* n3 = new Node(10);
	ListOperations<int> listOperations;
	listOperations.InsertNode(n1, head);
	listOperations.InsertNode(n2, head);
	listOperations.InsertNode(n3, head);

	Node* fNode = listOperations.FindPredecessor(n3);
	EXPECT_EQ(fNode->item_, 0);
	fNode = listOperations.FindPredecessor(n1);
	EXPECT_EQ(fNode->item_, -3);
	fNode = listOperations.FindPredecessor(n2);
	EXPECT_TRUE(fNode == 0);

	Node* n4 = new Node(5);

	fNode = listOperations.FindPredecessor(n4);
	EXPECT_TRUE(fNode == 0);


	delete n1;
	delete n2;
	delete n3;
	delete n4;
}

TEST_F(ListOperationsTest, DeleteNode){
	Node* head = 0;
	Node* n1 = new Node(0);
	Node* n2 = new Node(-3);
	Node* n3 = new Node(10);
	ListOperations<int> listOperations;
	listOperations.InsertNode(n1, head);
	listOperations.InsertNode(n2, head);
	listOperations.InsertNode(n3, head);

	listOperations.DeleteNode(n1, head);
	EXPECT_TRUE(head->previous_ == 0);
	EXPECT_TRUE(head == n3);
	EXPECT_TRUE(head->next_ == n2);
	EXPECT_TRUE(n2->next_ == 0);
	EXPECT_TRUE(n2->previous_ == head);

	listOperations.DeleteNode(n3, head);
	EXPECT_TRUE(head == n2);
	EXPECT_TRUE(head->previous_ == 0);
	EXPECT_TRUE(head->next_ == 0);

	listOperations.DeleteNode(n2, head);
	EXPECT_TRUE(head == 0);
}

} /* Private */ 

} /* AwesomeLibrary */ 
