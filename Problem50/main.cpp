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
#include "core/sets.h"
#include <QFile>

using namespace std;

int main()
{
    Timer timer;
    long long thaNumber=0;
    long long longestChain=0;
    long long longestChainStart=0;
    long long limit=1000000;
    auto primes = primes::primes(limit);
    long long maxChainLen=1000;
    long long pastLongestChain = 10;
    long long ps = (long long)primes.size();
    std::vector<std::vector<long long>> lut(ps,std::vector<long long>(maxChainLen,0));
    for(long long p=0; p<ps; ++p) {
        auto pr = primes[p];
        for(long long chainLen=longestChain; chainLen<longestChain+pastLongestChain; ++chainLen) {
            bool breakIt = false;
            for(long long i=0; i<ps-chainLen; ++i) {
                long long sum=lut[i][chainLen];
                if(sum == 0) {
                    for(long long j=i; j<i+chainLen; ++j) {
                        sum += primes[j];
                    }
                    lut[i][chainLen] = sum;
                }
                if(sum == pr) {
                    if(chainLen > longestChain) {
                        longestChain = chainLen;
                        longestChainStart = primes[i];
                        thaNumber = pr;
//                        qDebug() << "new longest chain for " << thaNumber << ", length " << longestChain;
                    }
                }
                else if(i==0 && sum > pr) {
                    breakIt = true;
                    break;
                }
                else if(sum > pr) {
                    break;
                }
            }
            if(breakIt) {
                break;
            }
        }
    }
    QString chain;
    for(long long i=longestChainStart; i<longestChainStart+longestChain; ++i) {
        chain += QString::number(primes[i]) + "+";
    }
    chain.remove(chain.size()-1,1);
    qDebug() << thaNumber << " has the longest chain of length " << longestChain;
//    qDebug() << "longest chain: " << chain;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
