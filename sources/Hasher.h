#ifndef HASHER_H_
#define HASHER_H_

/*
 * developer: Kuksov P.A.
 * mail: aimed.fire@gmail.com
*/

#include "defines.h"

namespace AwesomeLibrary {

namespace Private {

template <class Key> class Hasher;

template<> class Hasher<int> {
/*
 * стратегия реализации хэш-функции для целых чисел
 */
public:
	unsigned int Hash(int key) const;
};//end of declaration class Hasher<int>

unsigned int Hasher<int>::Hash(int key) const {
	return key;
}//end of unsigned int Hasher<int>::Hash()

} /* Private */ 

} /* AwesomeLibrary */ 

#endif /* end of include guard: HASHER_H_ */

