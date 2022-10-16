#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>
#include <set>
#include <bitset>
#include <deque>
#include "core/timer.h"
#include "core/primes.h"
#include "core/BigInt.h"

using namespace std;

int main()
{
    Timer timer;
    long long lim = 999999999;
    long long largest=0;
    auto primes = primes::primes(lim);
    for(const auto &p : primes) {
        auto digits = BigInt::convertToDigitsVec(p);
        std::set<long long> digitsSet;
        for(const auto &d:digits) {
            digitsSet.insert(d);
        }
        long long maxEl = *digitsSet.rbegin();
        if(digits.size() == digitsSet.size() && maxEl == (long long)digits.size() &&
           digitsSet.find(0) == digitsSet.end()) {
            largest = std::max(largest,p);
        }
    }
    std::cout << "largest pandigital prime: " << largest << std::endl;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
