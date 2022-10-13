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
    std::vector<long long> nums;
    for(long long a=2; a<=999999; ++a) {
        auto digs = BigInt::convertToDigitsVec(a);
        long long pSum = 0;
        for(const auto &d : digs) {
            pSum += pow(d,5);
        }
        if(pSum == a) {
            nums.push_back(a);
        }
    }
    long long sum = 0;
    for(const auto &n : nums) {
        sum += n;
    }
    qDebug() << "sum: " << sum;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
