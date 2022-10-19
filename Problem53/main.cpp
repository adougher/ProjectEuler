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
#include <QFile>

using namespace std;

int main()
{
    Timer timer;
    long long limit=100;
    long long count=0;
    BigInt aMilli(1000000);
    for(int n=1; n<=limit; ++n) {
        for(int r=1; r<=n; ++r) {
            BigInt nb(n);
            BigInt rb(r);
            auto numerator = BigInt::factorial(nb);
            auto denominator = BigInt::factorial(rb);
            denominator = denominator * BigInt::factorial(nb-rb);
            BigFloat nf(numerator);
            BigFloat df(denominator);
            nf = nf * BigFloat::reciprocal(df,200);
            if(BigFloat(aMilli) < nf) {
//                std::cout << n << " choose " << r << ": " << BigInt(nf.integerDigitsVec());
                count = count + n - 2 * r + 1;
                break;
            }
        }
    }
    qDebug() << "total: " << count;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
