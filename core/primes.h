#ifndef PRIMES_H_
#define PRIMES_H_

#include "Api.h"
#include "BigInt.h"
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

long long
COREAPI lcm(const long long &num1,
            const long long &num2);

long long
COREAPI gcd(const long long &num1,
            const long long &num2);

BigInt
COREAPI gcd(const BigInt &num1,
            const BigInt &num2);

std::vector<long long>
COREAPI expand(const std::vector<std::pair<long long,long long>> &pfac);

bool
COREAPI isPrime(const long long &num);

};

#endif
