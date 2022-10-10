#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include "core/timer.h"
#include "core/BigInt.h"

using namespace std;

int main()
{
    Timer timer;
    int sum = 0;
    BigInt num = BigInt::factorial(BigInt(100));
    auto digits = num.digitsVec();
    auto sz = digits.size();
    for(size_t i=0; i<sz; ++i) {
        sum += digits[i];
    }
    qDebug() << "sum of digits" << sum;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
