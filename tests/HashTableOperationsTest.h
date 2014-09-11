#include "../sources/HashTableOperations.h"

#include "test_framework.h"

#include <algorithm>

namespace AwesomeLibrary {

namespace Private {

class HashTableOperationsTest: public ::testing::Test {
public:
	static const int SIZE = 4;
	Entry<int>* testEntry1_;
	Entry<int>* testEntry2_;
	Entry<int>* testEntry3_;
	Entry<int>* testEntry4_;

	Entry<int>** testHashTable_;

	virtual void SetUp() {
		testEntry1_ = new Entry<int>(1);
		testEntry2_ = new Entry<int>(5);
		testEntry3_ = new Entry<int>(3);
		testEntry4_ = new Entry<int>(9);

		testHashTable_ = new Entry<int>*[SIZE];
		std::fill(testHashTable_, testHashTable_+SIZE, nullptr);
		testHashTable_[1] = testEntry1_;
		testHashTable_[1]->next_ = testEntry2_;
		testHashTable_[1]->next_->next_ = testEntry4_;
		testHashTable_[3] = testEntry3_;
		testHashTable_[1]->next_->next_->deleted_ = true;
	}

	virtual void TearDown() {
		delete testHashTable_;
		delete testEntry1_;
		delete testEntry2_;
		delete testEntry3_;
		delete testEntry4_;
	}

};//end of declaration class HashTableOperationsTest: public ::testing::Test

TEST_F(HashTableOperationsTest, should_add_new_entry_in_hash_table){
	HashTableOperations<int, Hasher> hto;
	int size = 4;
	Entry<int>** hashTable = new Entry<int>*[size];
	std::fill(hashTable, hashTable+size, nullptr);

	Entry<int> newEntry1(1);
	Entry<int> newEntry2(5);
	Entry<int> newEntry3(1);

	hto.InsertEntry(&newEntry1, hashTable, size);
	hto.InsertEntry(&newEntry2, hashTable, size);
	hto.InsertEntry(&newEntry3, hashTable, size);
	Hasher<int> hasher;
	int index = hasher.Hash(newEntry1.data_) % 4;

	ASSERT_TRUE(hashTable[index] != nullptr);
	EXPECT_TRUE(hashTable[index] == &newEntry1);
	EXPECT_TRUE(hashTable[index]->next_ == &newEntry2);
	EXPECT_TRUE(hashTable[index]->next_->next_ == nullptr);

	hashTable[index]->deleted_ = true;
	hto.InsertEntry(&newEntry3, hashTable, size);
	EXPECT_TRUE(hashTable[index]->next_->next_ == &newEntry3);

	delete[] hashTable;
}

TEST_F(HashTableOperationsTest, should_find_entry){
	HashTableOperations<int, Hasher> hto;

	Entry<int> entry1(1);
	Entry<int>* fEntry = hto.FindEntry(&entry1, testHashTable_, SIZE);
	EXPECT_TRUE(fEntry == testEntry1_);


	Entry<int> entry2(5);
	fEntry = hto.FindEntry(&entry2, testHashTable_, SIZE);
	EXPECT_TRUE(fEntry == testEntry2_);

	Entry<int> entry3(3);
	fEntry = hto.FindEntry(&entry3, testHashTable_, SIZE);
	EXPECT_TRUE(fEntry == testEntry3_);

	Entry<int> entry4(4);
	fEntry = hto.FindEntry(&entry4, testHashTable_, SIZE);
	EXPECT_TRUE(fEntry == nullptr);

	Entry<int> entry5(9);
	fEntry = hto.FindEntry(&entry5, testHashTable_, SIZE);
	EXPECT_TRUE(fEntry == nullptr);
}

TEST_F(HashTableOperationsTest, should_find_entry_with_minimal_key){
	HashTableOperations<int, Hasher> hto;
	Entry<int>* fEntry = hto.FindMinimum(testHashTable_, SIZE);
	EXPECT_EQ(1, fEntry->data_);

	testHashTable_[1]->deleted_ = true;
	fEntry = hto.FindMinimum(testHashTable_, SIZE);
	EXPECT_EQ(3, fEntry->data_);
}

TEST_F(HashTableOperationsTest, should_find_entry_with_maximal_key){
	HashTableOperations<int, Hasher> hto;
	Entry<int>* fEntry = hto.FindMaximum(testHashTable_, SIZE);
	EXPECT_TRUE(fEntry->data_ == 5);
}

TEST_F(HashTableOperationsTest, should_find_successor){
	HashTableOperations<int, Hasher> hto;
	Entry<int> entry1(1);
	Entry<int>* successor = hto.FindSuccessor(&entry1, testHashTable_, SIZE);
	EXPECT_TRUE(successor->data_ == 3);

	successor = hto.FindSuccessor(successor, testHashTable_, SIZE);
	EXPECT_TRUE(successor->data_ == 5);

	successor = hto.FindSuccessor(successor, testHashTable_, SIZE);
	EXPECT_TRUE(successor == nullptr);
}

TEST_F(HashTableOperationsTest, should_find_predecessor){
	HashTableOperations<int, Hasher> hto;
	Entry<int> entry1(5);
	Entry<int>* successor = hto.FindPredecessor(&entry1, testHashTable_, SIZE);
	EXPECT_TRUE(successor->data_ == 3);

	successor = hto.FindPredecessor(successor, testHashTable_, SIZE);
	EXPECT_TRUE(successor->data_ == 1);

	successor = hto.FindPredecessor(successor, testHashTable_, SIZE);
	EXPECT_TRUE(successor == nullptr);
}

} /* Private */ 

} /* AwesomeLibrary */ 

