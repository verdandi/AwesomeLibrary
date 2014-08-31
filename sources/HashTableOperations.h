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
	void insertEntry(Entry* newEntry, Entry* hashTable[], int hashTableSize);

	/*
	 * найти запись в хэш-таблице
	 * Принимаемые параметры:
	 * - entry - запись, которую необходимо найти
	 * - hashTable - хэш-таблица, в которой необходимо осуществлять поиск
	 * - hashTableSize - размер хэш-таблицы
	 */
	Entry* findEntry(Entry* entry, Entry* hashTable[], int hashTableSize) const;

};//end of declaration class HashTableOperations 

template<class Key, template<class> class Hasher> void  HashTableOperations<Key, Hasher>::insertEntry(Entry* newEntry, Entry* hashTable[], int hashTableSize) {
	int index = Hasher<Key>::Hash(newEntry->data_) % hashTableSize;

	if ( hashTable[index] == nullptr ) {
		hashTable[index] = newEntry;
		return;
	}//end of if 

	Entry* currEntry = hashTable[index];
	while ( currEntry->next_ != 0 ) {
		if ( currEntry->data_ == newEntry->data_ ) {
			return;
		}//end of if 

		currEntry = currEntry->next_;
	}//end of while

	currEntry->next_ = newEntry;
}//end of template<class Key, template<class> class Hasher> void  HashTableOperations<Key, Hasher>::insertEntry()

} /* Private */ 

} /* AwesomeLibrary */ 

#endif /* end of include guard: HASH_TABLE_OPERATIONS_H_ */

