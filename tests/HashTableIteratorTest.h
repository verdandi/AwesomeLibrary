#ifndef HASH_TABLE_ITERATOR_TEST_H_
#define HASH_TABLE_ITERATOR_TEST_H_

#include "../sources/HashTableIterator.h"

#include "test_framework.h"

namespace AwesomeLibrary {

namespace Private {

class HashTableIteratorTest: public ::testing::Test {
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

};//end of declaration class HashTableIteratorTest: public ::testing::Test

TEST_F(HashTableIteratorTest, should_move_iterator_to_next_entry){
	HashTableIterator<int, Hasher> it(testHashTable_[1], testHashTable_, SIZE);
	EXPECT_EQ(testHashTable_[1]->data_, *it);

	++it;
	EXPECT_EQ(testHashTable_[1]->next_->data_, *it);

	++it;
	EXPECT_EQ(testHashTable_[3]->data_, *it);
}

} /* Private */ 

} /* AwesomeLibrary */ 

#endif /* end of include guard: HASH_TABLE_ITERATOR_H_ */

