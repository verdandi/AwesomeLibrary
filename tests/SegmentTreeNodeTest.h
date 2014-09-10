#include "../sources/SegmentTreeNode.h"

#include "gtest/gtest.h"

namespace AwesomeLibrary {

class SegmentTreeNodeTest: public ::testing::Test {
public:
	virtual void SetUp() {}
	virtual void TearDown() {}
};//end of declaration class SegmentTreeNodeTest

TEST_F(SegmentTreeNodeTest, EqualTest){
	SegmentTreeNode<int> n1;
	n1.SetVal(1);
	n1.SetValidation(true);

	SegmentTreeNode<int> n2;
	n2.SetVal(1);
	n2.SetValidation(true);

	EXPECT_TRUE(n1 == n2);

	n2.SetValidation(false);
	EXPECT_FALSE(n1 == n2);

	n2.SetVal(2);
	n2.SetValidation(true);
	EXPECT_FALSE(n1 == n2);
}

TEST_F(SegmentTreeNodeTest, DefaultConstructorTest){
	SegmentTreeNode<int> etalonNode;
	etalonNode.SetVal(0);
	etalonNode.SetValidation(false);

	SegmentTreeNode<int> testNode;

	EXPECT_TRUE(testNode == etalonNode);
}

TEST_F(SegmentTreeNodeTest, ConstructorTest){
	SegmentTreeNode<int> etalonNode;
	etalonNode.SetVal(1);
	etalonNode.SetValidation(true);

	SegmentTreeNode<int> testNode(1);

	EXPECT_TRUE(testNode == etalonNode);
}

TEST_F(SegmentTreeNodeTest, CopyConstructorTest){
	SegmentTreeNode<int> n1(3);
	SegmentTreeNode<int> n2(n1);
	EXPECT_TRUE(n2 == n1);
}

TEST_F(SegmentTreeNodeTest, AssignmentOperatorTest){
	SegmentTreeNode<int> n1;
	SegmentTreeNode<int> n2(3);
	n1 = n2;
	EXPECT_TRUE(n2 == n1);
}

} /* AwesomeLibrary */ 
