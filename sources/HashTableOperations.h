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

	/*
	 * найти запись с максимальным ключем
	 * Принимаемые параметры:
	 * - hashTable - хэш-таблица в которой необходимо осуществлять поиск
	 * - hashTableSize - размер хэш-таблицы
	 * Возвращаемые параметры:
	 * Указатель на запись с максимальным ключем или nullptr если хэш-таблица пуста
	 */
	Entry* FindMaximum(Entry* hashTable[], int hashTableSize) const;

	/* найти запись с ключем, следующим по порядку за ключем заданной записи
	 * Принимаемые параметры:
	 * - entry - заданная запись
	 * - hashTable - хэш-таблица, в которой необходимо осуществлять поиск
	 * - hashTableSize - размер хэш-таблицы
	 * Возвращаемые параметры:
	 * указатель на найденную запись или nullptr
	 * Примечание:
	 * поиск будет осуществляться даже если заданная запись не пренадлежит хэш-таблице
	 */
	Entry* FindSuccessor(Entry* entry, Entry* hashTable[], int hashTableSize) const;

	/* найти запись с ключем, предшествующимм по порядку ключу заданной записи
	 * Принимаемые параметры:
	 * - entry - заданная запись
	 * - hashTable - хэш-таблица, в которой необходимо осуществлять поиск
	 * - hashTableSize - размер хэш-таблицы
	 * Возвращаемые параметры:
	 * указатель на найденную запись или nullptr
	 * Примечание:
	 * поиск будет осуществляться даже если заданная запись не пренадлежит хэш-таблице
	 */
	Entry* FindPredecessor(Entry* entry, Entry* hashTable[], int hashTableSize) const;

	void DeleteEntry(Entry* entry, Entry* hashTable[], int hashTableSize);


};//end of declaration class HashTableOperations 

template<class Key, template<class> class Hasher>
void  HashTableOperations<Key, Hasher>::InsertEntry(Entry* newEntry, Entry* hashTable[], int hashTableSize) {
	int index = Hasher<Key>::Hash(newEntry->data_) % hashTableSize;

	if ( hashTable[index] == nullptr ) {
		hashTable[index] = newEntry;
		return;
	}//end of if 

	Entry* currEntry = hashTable[index];
	Entry* prevEntry = nullptr;
	do {
		if ( currEntry->data_ == newEntry->data_ && !currEntry->deleted_ ) {
			return;
		}//end of if 

		prevEntry = currEntry;
		currEntry = currEntry->next_;
	} while (currEntry != nullptr);

	prevEntry->next_ = newEntry;
}//end of template<class Key, template<class> class Hasher> void  HashTableOperations<Key, Hasher>::insertEntry()

template<class Key, template<class> class Hasher>
Entry<Key>* HashTableOperations<Key, Hasher>::FindEntry(Entry* entry, Entry* hashTable[], int hashTableSize) const {
	int index = Hasher<Key>::Hash(entry->data_) % hashTableSize;

	if ( hashTable[index] == nullptr ) {
		return nullptr;
	}//end of if 

	Entry* currEntry = hashTable[index];
	do {
		if ( currEntry->data_ == entry->data_  && !currEntry->deleted_) {
			return currEntry;
		}//end of if 

		currEntry = currEntry->next_;
	} while ( currEntry != nullptr );

	return nullptr;
}//end of template<class Key, template<class> class Hasher> Entry* HashTableOperations<Key, Hasher>::findEntry()

template<class Key, template<class> class Hasher>
Entry<Key>* HashTableOperations<Key, Hasher>::FindMinimum(Entry* hashTable[], int hashTableSize) const {
	Entry* minimum = nullptr;
	for (int i = 0; i < hashTableSize; ++i) {
		Entry* currEntry = hashTable[i];
		if ( currEntry == nullptr ) {
			continue;
		}//end of if 

		do {
			if ( ( minimum == nullptr ||  currEntry->data_ < minimum->data_ )  && !currEntry->deleted_  ) {
				minimum = currEntry;
			}//end of if 

			currEntry = currEntry->next_;
		} while ( currEntry != nullptr );
	}//end of for

	return minimum;
}//end of tempate<class Key, template<class> class Hasher> Entry<Key>* HashTableOperations<Key, Hasher>::FindMinimum()

template<class Key, template<class> class Hasher>
Entry<Key>* HashTableOperations<Key, Hasher>::FindMaximum(Entry* hashTable[], int hashTableSize) const {
	Entry* maximum = nullptr;
	for (int i = 0; i < hashTableSize; ++i) {
		Entry* currEntry = hashTable[i];
		if ( currEntry == nullptr ) {
			continue;
		}//end of if 

		do {
			if ( ( maximum == nullptr  ||  currEntry->data_ > maximum->data_ ) && !currEntry->deleted_) {
				maximum = currEntry;
			}//end of if 

			currEntry = currEntry->next_;
		} while ( currEntry != nullptr );
	}//end of for

	return maximum;
}//end of template<class Key, template<class> class Hasher> Entry<Key>* HashTableOperations<Key, Hasher>::FindMaximum()

template<class Key, template<class> class Hasher>
Entry<Key>* HashTableOperations<Key, Hasher>::FindSuccessor(Entry* entry, Entry* hashTable[], int hashTableSize) const {
	Entry* successor = nullptr;
	for (int i = 0; i < hashTableSize; ++i) {
		Entry* currEntry = hashTable[i];
		if	( currEntry == nullptr ) {
			continue;
		}
		
		do {
			if ( ( successor == nullptr && currEntry->data_ > entry->data_ ) && !currEntry->deleted_ ) {
				successor = currEntry;
			}//end of if
			if ( ( successor != nullptr ) && ( currEntry->data_ > entry->data_ ) &&
				( currEntry->data_ < successor->data_ ) && !currEntry->deleted_ ) {
				successor = currEntry;
			}

			currEntry = currEntry->next_;
		} while ( currEntry != nullptr );
	}//end of for

	return successor;
}//end of template<class Key, template<class> class Hasher> Entry<Key>* HashTableOperations<Key, Hasher>::FindSuccessor()

template<class Key, template<class> class Hasher>
Entry<Key>* HashTableOperations<Key, Hasher>::FindPredecessor(Entry* entry, Entry* hashTable[], int hashTableSize) const {
	Entry* predecessor = nullptr;
	for (int i = 0; i < hashTableSize; ++i) {
		Entry* currEntry = hashTable[i];
		if	( currEntry == nullptr ) {
			continue;
		}
		
		do {
			if ( ( predecessor == nullptr ) && ( currEntry->data_ < entry->data_ ) && !currEntry->deleted_ ) {
				predecessor = currEntry;
			}//end of if
			if ( ( predecessor != nullptr ) && ( currEntry->data_ < entry->data_ ) &&
				( currEntry->data_ > predecessor->data_ ) && !currEntry->deleted_ ) {
				predecessor = currEntry;
			}

			currEntry = currEntry->next_;
		} while ( currEntry != nullptr );
	}//end of for

	return predecessor;
}//end of template<class Key, template<class> class Hasher> Entry<Key>* HashTableOperations<Key, Hasher>::FindPredecessor()

template<class Key, template<class> class Hasher>
void HashTableOperations<Key, Hasher>::DeleteEntry(Entry* entry, Entry* hashTable[], int hashTableSize) {
	int index = Hasher<Key>::Hash(entry->data_) % hashTableSize;

	if ( hashTable[index] == nullptr ) {
		return;
	}//end of if 

	Entry* currEntry = hashTable[index];
	do {
		if ( currEntry->data_ == entry->data_ && !currEntry->deleted_ ) {
			currEntry->deleted_ = true;
			return;
		}//end of if 

		currEntry = currEntry->next_;
	} while (currEntry != nullptr);
}//end of template<class Key, template<class> class Hasher> void HashTableOperations<Key, Hasher>::DeleteEntry()

} /* Private */ 

} /* AwesomeLibrary */ 

#endif /* end of include guard: HASH_TABLE_OPERATIONS_H_ */
