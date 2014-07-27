#include "../sources/SegmentTree.h"

#include "test_framework.h"

namespace AwesomeLibrary {

class SegmentTreeTest: public ::testing::Test {
public:
	std::vector<int> array;

	virtual void SetUp(){
		array.push_back(1);
		array.push_back(4);
		array.push_back(0);
		array.push_back(-2);
		array.push_back(2);
	}

	virtual void TearDown(){}

};//end of declaration class SegmentTreeTest

TEST_F(SegmentTreeTest, BuildTreeTest){
	SegmentTree<int, Amount> tree;
	bool isOK = tree.Build(array);
	EXPECT_EQ(isOK, true);

	std::vector<SegmentTreeNode<int> > resultTree(16);
	resultTree[1] = SegmentTreeNode<int>(5);
	resultTree[2] = SegmentTreeNode<int>(3);
	resultTree[3] = SegmentTreeNode<int>(2);
	resultTree[4] = SegmentTreeNode<int>(5);
	resultTree[5] = SegmentTreeNode<int>(-2);
	resultTree[6] = SegmentTreeNode<int>(2);
	resultTree[8] = SegmentTreeNode<int>(1);
	resultTree[9] = SegmentTreeNode<int>(4);
	resultTree[10] = SegmentTreeNode<int>(0);
	resultTree[11] = SegmentTreeNode<int>(-2);
	resultTree[12] = SegmentTreeNode<int>(2);

	EXPECT_TRUE(ContainersIsEqual(tree.storage_, resultTree));
}

TEST_F(SegmentTreeTest, SecondCallOfFunctionBuildTest){
	SegmentTree<int, Amount> tree;

	std::vector<SegmentTreeNode<int> > resultTree(16);
	resultTree[1] = SegmentTreeNode<int>(5);
	resultTree[2] = SegmentTreeNode<int>(3);
	resultTree[3] = SegmentTreeNode<int>(2);
	resultTree[4] = SegmentTreeNode<int>(5);
	resultTree[5] = SegmentTreeNode<int>(-2);
	resultTree[6] = SegmentTreeNode<int>(2);
	resultTree[8] = SegmentTreeNode<int>(1);
	resultTree[9] = SegmentTreeNode<int>(4);
	resultTree[10] = SegmentTreeNode<int>(0);
	resultTree[11] = SegmentTreeNode<int>(-2);
	resultTree[12] = SegmentTreeNode<int>(2);

	bool isOK = tree.Build(array);
	EXPECT_EQ(isOK, true);
	EXPECT_TRUE(ContainersIsEqual(tree.storage_, resultTree));

	std::vector<int> testArray;
	testArray.push_back(1);
	testArray.push_back(2);
	isOK = tree.Build(testArray);
	EXPECT_EQ(isOK, false);
	EXPECT_TRUE(ContainersIsEqual(tree.storage_, resultTree));
}

TEST_F(SegmentTreeTest, ErrorInputDataForFunctionBuild){
	//передадим функции SegmentTree::Build() пустой массив
	SegmentTree<int, Amount> tree;
	std::vector<int> testArray;
	bool isOK = tree.Build(testArray);
	EXPECT_EQ(isOK, false);
}

TEST_F(SegmentTreeTest, ReleaseTest){
	SegmentTree<int, Amount> tree;
	bool isOK = tree.Build(array);
	EXPECT_EQ(isOK, true);

	tree.Release();
	isOK = tree.Build(array);
	EXPECT_EQ(isOK, true);
}

TEST_F(SegmentTreeTest, EmptyTest){
	SegmentTree<int, Amount> tree;
	bool isEmpty = tree.Empty();
	EXPECT_EQ(isEmpty, true);

	tree.Build(array);
	isEmpty = tree.Empty();
	EXPECT_EQ(isEmpty, false);
}

TEST_F(SegmentTreeTest, GetSumTest){
	SegmentTree<int, Amount> tree(array);

	//проверим значение суммы 1-3 элементов массива array
	EXPECT_EQ(2, tree.GetSum(1, 3)); 

	//проверим значение суммы 2-4 элементов массива array
	EXPECT_EQ(0, tree.GetSum(2, 4)); 

	//проверим значение суммы 4-4 элементов массива array
	EXPECT_EQ(2, tree.GetSum(4, 4)); 

	//проверим значение суммы 2-2 элементов массива array
	EXPECT_EQ(0, tree.GetSum(2, 2)); 

	//проверим значение суммы 0-4 элементов массива array
	EXPECT_EQ(5, tree.GetSum(0, 4)); 
}

TEST_F(SegmentTreeTest, ErrorInputDataForFunctionGetSum){
	SegmentTree<int, Amount> tree(array);

	EXPECT_EQ(tree.GetSum(1, 3), tree.GetSum(3, 1));

	EXPECT_EQ(int(), tree.GetSum(-1, 4));

	EXPECT_EQ(int(), tree.GetSum(0, 7));

	EXPECT_EQ(int(), tree.GetSum(-3, 5));
}

TEST_F(SegmentTreeTest, SetElemTest){
	SegmentTree<int, Amount> tree(array);
	bool isOK = tree.SetElem(0, 2);
	EXPECT_TRUE(isOK);
	EXPECT_EQ(6, tree.GetSum(0, 4));
}

TEST_F(SegmentTreeTest, ErrorInputDataForFunctionSetElem){
	SegmentTree<int, Amount> tree(array);
	bool isOK = tree.SetElem(5, 3);
	EXPECT_FALSE(isOK);
}

} /* AwesomeLibrary */ 
