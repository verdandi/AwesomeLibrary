#ifndef HASH_TABLE_ITERATOR_H_
#define HASH_TABLE_ITERATOR_H_

/*
 * developed by: Kuksov Pavel
 * mail: aimed.fire@gmail.com
 */

#include "HashTableOperations.h"

namespace AwesomeLibrary {

namespace Private {

template<class Key, template<class, template<class> class> class HashTableOperations> class HashTable;

template<class Key, template<class> class Hasher> class HashTableIterator: Hasher<Key> {
/*
 * Класс, реализующий итератор для хэш-таблицы.
 * Шаблонные параметры:
 * - T - тип ключей хранящихся в хэш-таблице
 * - Entry - запись в хэш-таблице
 * Примечание:
 * при создании класса предполагается, что передаются только валидные данные.
 */
public:
#ifdef __ALGORITHM_TEST__
	friend class HashTableIteratorTest;
	FRIEND_TEST(HashTableIteratorTest, should_move_iterator_to_next_entry);
#endif

typedef typename HashTableOperations<Key, Hasher>::Entry Entry;

	~HashTableIterator () {}

	HashTableIterator(const HashTableIterator& other) {
		currEntry_ = other.currEntry_;
		hashTable_ = other.hashTable_;
		hashTableSize_ = other.hashTableSize_;
		currIndex_ = other.currIndex_;
	}

	HashTableIterator& operator=(const HashTableIterator& other) {
		currEntry_ = other.currEntry_;
		hashTable_ = other.hashTable_;
		hashTableSize_ = other.hashTableSize_;
		currIndex_ = other.currIndex_;

		return *this;
	}//end of HashTableIterator& operator=()

	bool operator==(const HashTableIterator& other) {
		return currEntry_ == other.currEntry_;
	}//end of bool operator==()

	bool operator!=(const HashTableIterator& other) {
		return currEntry_ != other.currEntry_;
	}//end of bool operator!=()

	Key& operator*() const {
		return currEntry_->data_;
	}//end of Key& operator*()

	HashTableIterator& operator++() {
		//перебираем цепочку в конкретном индексе
		while ( currEntry_->next_ != nullptr ) {
			currEntry_ = currEntry_->next_;
			if ( currEntry_->deleted_ == true ) {
				continue;
			}//end of if 

			return *this;
		}//end of while 

		//ищем следующую не удаленную запись в хэш-таблице
		for (int i = currIndex_ + 1; i <= hashTableSize_; ++i) {
			if ( hashTable_[i] == nullptr ) { continue; }//end of if 

			currEntry_ = hashTable_[i];
			do {
				if ( currEntry_->deleted_ != true ) {
					currIndex_ = i;
					return *this;
				}//end of if 
			} while ( currEntry_->next_ != nullptr);
		}//end of for

		//если не нашли, возвращаем признак конца таблицы
		currEntry_ = Entry::Nil();
		return *this;
	}//end of HashTableIterator& operator++()

private:
	friend class HashTable<Key, HashTableOperations>;

	HashTableIterator(Entry* entry, Entry* hashTable[], int hashTableSize): // этим конструктором может пользоваться только класс HashTable
		currEntry_(entry),
		hashTable_(hashTable),
		hashTableSize_(hashTableSize),
		currIndex_(Hasher<Key>::Hash(entry->data_))
	{
		assert(currEntry_ != nullptr);
		assert(hashTable_ != nullptr);
	}//end of HashTableIterator()

	Entry* currEntry_; // указатель на запись в хэш-таблице. Класс HashTableIterator не владеет данным указателем.
	Entry** hashTable_; // хэш-таблица
	int hashTableSize_; // размер хэш-таблицы
	int currIndex_; // индекс текущей записи в хэш-таблице
};//end of declaration class HashTableIterator

} /* Private */ 

} /* AwesomeLibrary */ 

#endif /* end of include guard: HASH_TABLE_ITERATOR_H_ */

