#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include "core/timer.h"
#include "core/primes.h"
#include "core/BigInt.h"

using namespace std;

int main()
{
    Timer timer;
    int sum = 0;
    int range = 28123;
    std::vector<long long> abundantNums;
    for(long long i=2; i<=range; ++i) {
        auto properDiv = primes::properDivisors(i);
        int sumD = 0;
        for(const auto &p : properDiv) {
            sumD += p;
        }
        if(sumD > i) {
            abundantNums.push_back(i);
        }
    }
    std::vector<bool> found(range+1,false);
    auto sz = abundantNums.size();
    for(size_t i=0; i<sz; ++i) {
        for(size_t j=i; j<sz; ++j) {
            auto aSum = abundantNums[i] + abundantNums[j];
            if(aSum <= range) {
                found[aSum] = true;
            }
        }
    }
    for(long long i=0; i<=range; ++i) {
        if(!found[i]) {
            sum += i;
        }
    }
    qDebug() << "sum numbers which cannot be written as the sum of two abundant numbers: " << sum;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
