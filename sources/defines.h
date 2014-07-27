#ifndef DEFINES_H_
#define DEFINES_H_

#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <vector>
#include <deque>
#include <set>
#include <algorithm>
#include <iterator>
#include <string>
#include <stack>
#include <cassert>

#ifdef __ALGORITHM_DEBUG__
#include <cstdio>
#include <cstdlib>
#include <ctime>
#endif

#ifdef __ALGORITHM_TEST__
#include "gtest/gtest_prod.h"
#endif

#ifdef __ALGORITHM_DEBUG__
#define TRACE(arg) {std::cout << #arg << std::endl; arg;}
#else
#define TRACE(arg) 
#endif

#ifdef __ALGORITHM_DEBUG__
#define PRINTSEQ(seq, size) {\
	std::cout << "------------------------------\n"; \
	std::cout << "str. " << __LINE__ << ":" << "\n"; \
	for(size_t i = 0; i < (size); ++i){ \
	TRACE((seq[i])); \
	} \
	std::cout << "------------------------------\n"; \
}
#else
#define PRINTSEQ(seq, size)
#endif

#ifdef __ALGORITHM_DEBUG__
#define PRINTVAL(val) {std::cout << "str. " << __LINE__ << ": " << #val << " - " << val << "\n";}
#else
#define PRINTVAL(val)
#endif

using std::cin;

#ifdef __ALGORITHM_DEBUG__
//#define cin in
#endif

#endif /* end of include guard: DEFINES_H_ */
