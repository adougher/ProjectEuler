#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>
#include <set>
#include <bitset>
#include "core/timer.h"
#include "core/primes.h"
#include "core/BigInt.h"

using namespace std;

int main()
{
    Timer timer;
    std::set<long long> nums;
    std::vector<long long> factorials(10,0);
    for(long long i=100; i<=9999999; ++i) {
        auto digits = BigInt::convertToDigitsVec(i);
        long long j=0;
        for(const auto &d : digits) {
            if(factorials[d]==0) {
                factorials[d] = BigInt::factorial(d);
                qDebug() << "factorials[" << d << "]: " << factorials[d];
            }
            j = j + factorials[d];
        }
//        std::cout << "i: " << i << std::endl;
//        std::cout << "j: " << j;
        if(j == i) {
            nums.insert(j);
            std::cout << "j: " << j << std::endl;
        }
    }
    long long sum=0;
    for(const auto &n : nums) {
        sum = sum + n;
    }
    std::cout << "sum: " << sum << std::endl;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
