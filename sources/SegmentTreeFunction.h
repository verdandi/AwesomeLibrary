#ifndef SEGMENT_TREE_FUNCTION_H_
#define SEGMENT_TREE_FUNCTION_H_

namespace AwesomeLibrary {

template<class T> class Amount {
public:
	Amount () {}

	T Result(const T& lhs, const T& rhs) const;

protected:
	~Amount () {}
};//end of declaration class Amount

template<class T> T Amount<T>::Result(const T& lhs, const T& rhs) const {
	return lhs + rhs;
}//end of template<class T> const T& Amount<T>::Result()

template<class T> class Minimum {
public:
	Minimum (){}

	T Result(const T& lhs, const T& rhs);

protected:
	~Minimum (){}
};//end of declaration class Minimum

template<class T> T Minimum<T>::Result(const T& lhs, const T& rhs) {
	if (lhs < rhs) {
		return lhs;
	}/* end of if */

	return rhs;
}//end of template<class T> const T& Minimum<T>::Result()

} /* AwesomeLibrary */ 

#endif /* end of include guard: SEGMENT_TREE_FUNCTION_H_ */

