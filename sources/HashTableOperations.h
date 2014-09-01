#ifndef HASH_TABLE_OPERATIONS_H_
#define HASH_TABLE_OPERATIONS_H_

#include "Entry.h"
#include "Hasher.h"

namespace AwesomeLibrary {

namespace Private {

template<class Key, template<class> class Hasher> class HashTableOperations: Hasher<Key> {
/*
 * Класс, реализующий операции с Хэш-таблицей в терминах записей.
 * Предполагается, что в этот класс поступают только корректные данные
 */

#ifndef __ALGORITHM_TEST__
protected:
#else
public:
#endif

	typedef Private::Entry<Key> Entry; 

	/*
	 * вставить новую запись в хэш-таблицу
	 * Принимаемые параметры:
	 * - newEntry - новая запись
	 * - hashTable - хэш-таблица, в которую следует вставить запись
	 * - hashTableSize - размер хэш-таблицы
	 */ 
	void InsertEntry(Entry* newEntry, Entry* hashTable[], int hashTableSize);

	/*
	 * найти запись в хэш-таблице
	 * Принимаемые параметры:
	 * - entry - запись, которую необходимо найти
	 * - hashTable - хэш-таблица, в которой необходимо осуществлять поиск
	 * - hashTableSize - размер хэш-таблицы
	 * Возвращаемое значение:
	 * указатель на найденную запись, или nullptr если запись не найдена
	 */
	Entry* FindEntry(Entry* entry, Entry* hashTable[], int hashTableSize) const;

	/*
	 * найти запись с минимальным ключем
	 * Принимаемые параметры:
	 * - hashTable - хэш-таблица в которой необходимо осуществлять поиск
	 * - hashTableSize - размер хэш-таблицы
	 * Возвращаемые параметры:
	 * Указатель на запись с минимальным ключем или nullptr если хэш-таблица пуста
	 */
	Entry* FindMinimum(Entry* hashTable[], int hashTableSize) const;

};//end of declaration class HashTableOperations 

template<class Key, template<class> class Hasher> void  HashTableOperations<Key, Hasher>::InsertEntry(Entry* newEntry, Entry* hashTable[], int hashTableSize) {
	int index = Hasher<Key>::Hash(newEntry->data_) % hashTableSize;

	if ( hashTable[index] == nullptr ) {
		hashTable[index] = newEntry;
		return;
	}//end of if 

	Entry* currEntry = hashTable[index];
	Entry* prevEntry = nullptr;
	do {
		if ( currEntry->data_ == newEntry->data_ ) {
			return;
		}//end of if 

		prevEntry = currEntry;
		currEntry = currEntry->next_;
	} while (currEntry != nullptr);

	prevEntry->next_ = newEntry;
}//end of template<class Key, template<class> class Hasher> void  HashTableOperations<Key, Hasher>::insertEntry()

template<class Key, template<class> class Hasher> Entry<Key>* HashTableOperations<Key, Hasher>::FindEntry(Entry* entry, Entry* hashTable[], int hashTableSize) const {
	int index = Hasher<Key>::Hash(entry->data_) % hashTableSize;

	if ( hashTable[index] == nullptr ) {
		return nullptr;
	}//end of if 

	Entry* currEntry = hashTable[index];
	do {
		if ( currEntry->data_ == entry->data_ ) {
			return currEntry;
		}//end of if 

		currEntry = currEntry->next_;
	} while ( currEntry != nullptr );

	return nullptr;
}//end of template<class Key, template<class> class Hasher> Entry* HashTableOperations<Key, Hasher>::findEntry()

template<class Key, template<class> class Hasher> Entry<Key>* HashTableOperations<Key, Hasher>::FindMinimum(Entry* hashTable[], int hashTableSize) const {
	Entry* minimum = nullptr;
	for (int i = 0; i < hashTableSize; ++i) {
		Entry* currEntry = hashTable[i];
		if ( currEntry == nullptr ) {
			continue;
		}//end of if 

		do {
			if ( ( minimum == nullptr ) || ( currEntry->data_ < minimum->data_ ) ) {
				minimum = currEntry;
			}//end of if 

			currEntry = currEntry->next_;
		} while ( currEntry != nullptr );
	}//end of for

	return minimum;
}//end of tempate<class Key, template<class> class Hasher> Entry<Key>* HashTableOperations<Key, Hasher>::FindMinimum()

} /* Private */ 

} /* AwesomeLibrary */ 

#endif /* end of include guard: HASH_TABLE_OPERATIONS_H_ */

