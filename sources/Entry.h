#ifndef ENTRY_H_
#define ENTRY_H_

/*
 * developer: Kuksov P.A.
 * mail: aimed.fire@gmail.com
*/

namespace AwesomeLibrary {

namespace Private {

template<class T> struct Entry {
/*
 * Структура, реализующая запись в хэш-таблицу
 */
	T data_;
	Entry* next_;
	bool deleted_;

	explicit Entry (const T& newData): data_(newData), next_(nullptr), deleted_(false) {}
	~Entry () {}
};//end of declaration class Entry

} /* Private */ 

} /* AwesomeLibrary */ 

#endif /* end of include guard: ENTRY_H_ */

