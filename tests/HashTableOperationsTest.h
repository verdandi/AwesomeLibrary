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

	Entry<int>** testHashTable_;

	virtual void SetUp() {
		testEntry1_ = new Entry<int>(1);
		testEntry2_ = new Entry<int>(5);
		testEntry3_ = new Entry<int>(3);

		testHashTable_ = new Entry<int>*[SIZE];
		std::fill(testHashTable_, testHashTable_+SIZE, nullptr);
		testHashTable_[1] = testEntry1_;
		testHashTable_[1]->next_ = testEntry2_;
		testHashTable_[3] = testEntry3_;
	}

	virtual void TearDown() {
		delete testHashTable_;
		delete testEntry1_;
		delete testEntry2_;
		delete testEntry3_;
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

	hto.insertEntry(&newEntry1, hashTable, size);
	hto.insertEntry(&newEntry2, hashTable, size);
	hto.insertEntry(&newEntry3, hashTable, size);
	Hasher<int> hasher;
	int index = hasher.Hash(newEntry1.data_) % 4;

	ASSERT_TRUE(hashTable[index] != nullptr);
	EXPECT_TRUE(hashTable[index] == &newEntry1);
	EXPECT_TRUE(hashTable[index]->next_ == &newEntry2);
	EXPECT_TRUE(hashTable[index]->next_->next_ == nullptr);

	delete[] hashTable;
}

TEST_F(HashTableOperationsTest, should_find_entry){
	HashTableOperations<int, Hasher> hto;

	Entry<int> entry1(1);
	Entry<int>* fEntry = hto.findEntry(&entry1, testHashTable_, SIZE);
	EXPECT_TRUE(fEntry == testEntry1_);


	Entry<int> entry2(5);
	fEntry = hto.findEntry(&entry2, testHashTable_, SIZE);
	EXPECT_TRUE(fEntry == testEntry2_);

	Entry<int> entry3(3);
	fEntry = hto.findEntry(&entry3, testHashTable_, SIZE);
	EXPECT_TRUE(fEntry == testEntry3_);

	Entry<int> entry4(4);
	fEntry = hto.findEntry(&entry4, testHashTable_, SIZE);
	EXPECT_TRUE(fEntry == nullptr);
}

} /* Private */ 

} /* AwesomeLibrary */ 

