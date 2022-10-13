#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>
#include <set>
#include <bitset>
#include "core/timer.h"
#include "core/primes.h"
#include "core/BigFloat.h"

using namespace std;

int main()
{
    Timer timer;
    long long sum = 1;
    long long start = 1;
    long long i=1;
    long long j = 0;
    long long dim = 1001;
    while(start < dim*dim) {
        start += 2*i;
        sum += start;
        ++j;
        if(j % 4 == 0) {
            j = 0;
            ++i;
        }
    }
    qDebug() << "diagonals sum: " << sum;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
