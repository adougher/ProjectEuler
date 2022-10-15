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
    std::vector<int> allDigits;
    for(long long i=1; i<=1000000; ++i) {
        auto digits = BigInt::convertToDigitsVec(i);
        std::reverse(digits.begin(),digits.end());
        allDigits.insert(allDigits.end(),digits.begin(),digits.end());
    }
    long long prod=1;
    for(auto i : {1,10,100,1000,10000,100000,1000000}) {
        qDebug() << "allDigits[i-1]: " << allDigits[i-1];
        prod *= allDigits[i-1];
    }
    std::cout << "product: " << prod << std::endl;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
