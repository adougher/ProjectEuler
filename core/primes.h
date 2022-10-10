#ifndef PRIMES_H_
#define PRIMES_H_

#include "Api.h"
#include <vector>

namespace primes {

std::vector<long long>
COREAPI primes(const long long &limit);

std::vector<std::pair<long long,long long>>
COREAPI primeFactors(const long long &num);

std::vector<long long>
COREAPI divisors(const long long &num);

std::vector<long long>
COREAPI properDivisors(const long long &num);

};

#endif
