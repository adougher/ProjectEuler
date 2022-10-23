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
#include "core/BigFloat.h"
#include "core/sets.h"

using namespace std;

int main()
{
    Timer timer;
    long long limit=100;
    long long maxDSum=0;
    BigInt maxNum({});
    for(int a=1; a<limit; ++a) {
        for(int b=1; b<limit; ++b) {
            BigInt aToTheB = BigInt(a) ^ b;
            auto digVec = aToTheB.digitsVec();
            long long sum = 0;
            for(const auto &d : digVec) {
                sum += d;
            }
            if(maxDSum < sum) {
                maxDSum = sum;
                maxNum = aToTheB;
            }
        }
    }
    std::cout << "the maximum digital sum of " << maxDSum << " occurs for " << maxNum;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
