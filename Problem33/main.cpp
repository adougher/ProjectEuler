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
    std::set<long long> prodSet;
    std::vector<long long> nums;
    std::vector<long long> denoms;
    for(long long i=10; i<100; ++i) {
        for(long long j=i+1; j<100; ++j) {
            auto dvi = BigInt::convertToDigitsVec(i);
            auto dvj = BigInt::convertToDigitsVec(j);
            auto div1 = 1.0 * i / j;
            long long ii=0;
            long long jj=0;
            if(dvi[0] == dvj[0] && dvi[0] != 0) {
                ii = dvi[1];
                jj = dvj[1];
            }
            else if(dvi[0] == dvj[1] && dvi[0] != 0) {
                ii = dvi[1];
                jj = dvj[0];
            }
            else if(dvi[1] == dvj[0] && dvi[1] != 0) {
                ii = dvi[0];
                jj = dvj[1];
            }
            else if(dvi[1] == dvj[1] && dvi[1] != 0) {
                ii = dvi[0];
                jj = dvj[0];
            }
            else {
                continue;
            }
            auto div2 = 1.0 * ii / jj;
            if(std::abs(div1-div2) < 1e-4) {
                nums.push_back(i);
                denoms.push_back(j);
            }
        }
    }
    size_t sz = nums.size();
    long long numProd=1;
    long long denomProd=1;
    for(size_t i=0; i<sz; ++i) {
        numProd *= nums[i];
        denomProd *= denoms[i];
    }
    auto gcd = primes::gcd(numProd,denomProd);
    qDebug() << "denominator: " << denomProd / gcd;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
