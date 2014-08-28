#include "../sources/List.h"

#include "test_framework.h"

namespace AwesomeLibrary {

class ListTest: public ::testing::Test {
public:
	List<int, Private::ListOperations> testList;
	virtual void SetUp() {
		testList.Insert(-3);
		testList.Insert(0);
		testList.Insert(6);
		testList.Insert(10);
	}

	virtual void TearDown() {}
};//end of declaration class ListTest: public ::testing::Test

TEST_F(ListTest, Insert){
	List<int, Private::ListOperations> list;
	EXPECT_TRUE(list.head_ == 0);
	list.Insert(0);
	EXPECT_TRUE(list.head_->item_ == 0);
	EXPECT_TRUE(list.head_->next_ == 0);
	EXPECT_TRUE(list.head_->previous_ == 0);

	list.Insert(-3);
	EXPECT_TRUE(list.head_->item_ == -3);
	EXPECT_TRUE(list.head_->next_->item_ == 0);
	EXPECT_TRUE(list.head_->next_->previous_ == list.head_);

	list.Insert(10);
	EXPECT_TRUE(list.head_->item_ == 10);
	EXPECT_TRUE(list.head_->next_->next_->item_ == 0);
	EXPECT_TRUE(list.head_->next_->item_ == -3);
	EXPECT_TRUE(list.head_->next_->next_->previous_->item_ == -3);
	EXPECT_TRUE(list.head_->next_->previous_ == list.head_);
}

TEST_F(ListTest, Begin){
	List<int, Private::ListOperations>::Iterator it = testList.Begin();
	EXPECT_TRUE(*it == 10);
}

TEST_F(ListTest, End){
	List<int, Private::ListOperations>::Iterator endIt;
	List<int, Private::ListOperations>::Iterator it = testList.End();
	EXPECT_TRUE(endIt == it);
}

TEST_F(ListTest, Minimum){
	List<int, Private::ListOperations>::Iterator it = testList.Minimum();
	EXPECT_TRUE(*it == -3);
}

TEST_F(ListTest, Maximum){
	List<int, Private::ListOperations>::Iterator it = testList.Maximum();
	EXPECT_TRUE(*it == 10);
}

TEST_F(ListTest, Successor){
	List<int, Private::ListOperations>::Iterator it = testList.Successor(5);
	EXPECT_TRUE(it == testList.End());

	it = testList.Successor(6);
	EXPECT_TRUE(*it == 10);

	it = testList.Successor(10);
	EXPECT_TRUE(it == testList.End());
}

TEST_F(ListTest, Predecessor){
	List<int, Private::ListOperations>::Iterator it = testList.Predecessor(0);
	EXPECT_TRUE(*it == -3);

	it = testList.Predecessor(-3);
	EXPECT_TRUE(it == testList.End());
}

TEST_F(ListTest, Delete){
	testList.Delete(6);
	List<int, Private::ListOperations>::Iterator it = testList.Begin();
	EXPECT_TRUE(*it == 10);
	++it;
	EXPECT_TRUE(*it == 0);
	++it;
	EXPECT_TRUE(*it == -3);
	++it;
	EXPECT_TRUE(it == testList.End());

	testList.Delete(-3);
	it = testList.Begin();
	EXPECT_TRUE(*it == 10);
	++it;
	EXPECT_TRUE(*it == 0);
	++it;
	EXPECT_TRUE(it == testList.End());

	testList.Delete(10);
	it = testList.Begin();
	EXPECT_TRUE(*it == 0);
	++it;
	EXPECT_TRUE(it == testList.End());

	testList.Delete(0);
	it = testList.Begin();
	EXPECT_TRUE(it == testList.End());
}

TEST_F(ListTest, Find){
	List<int, Private::ListOperations>::Iterator it = testList.Find(6);
	EXPECT_TRUE(*it == 6);

	it = testList.Find(5);
	EXPECT_TRUE(it == testList.End());
}

TEST_F(ListTest, Destructor){
	List<int, Private::ListOperations>::Node* head = 0;
	List<int, Private::ListOperations>::Node* n1 = new List<int, Private::ListOperations>::Node(0);
	List<int, Private::ListOperations>::Node* n2 = new List<int, Private::ListOperations>::Node(-3);
	List<int, Private::ListOperations>::Node* n3 = new List<int, Private::ListOperations>::Node(10);
	Private::ListOperations<int> listOperations;
	listOperations.InsertNode(n1, head);
	listOperations.InsertNode(n2, head);
	listOperations.InsertNode(n3, head);

	{
		List<int, Private::ListOperations> list;
		list.head_ = head;
	}

	std::ifstream in("test_log.txt");
	std::string testStr;
	std::getline(in, testStr);
	EXPECT_STREQ("delete10delete-3delete0", testStr.c_str());
}

} /* AwesomeLibrary */ 
