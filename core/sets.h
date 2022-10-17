#ifndef SETS_H_
#define SETS_H_

#include "Api.h"
#include <vector>

namespace sets {

template <class T>
std::vector<std::vector<T>>
COREAPI powerSet(const std::vector<T> &set);

template <class T>
void
COREAPI permutations(long long k, T &container,  std::vector<T> &permutations);

};

#endif
