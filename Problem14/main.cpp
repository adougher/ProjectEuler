#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include "core/timer.h"

using namespace std;


int main()
{
    Timer timer;
    long long maxChainLen=0;
    long long maxChainLenNumber=0;
    std::bitset<100> bs;
    for(int i=2; i<1000000; ++i) {
        long long chainLen=0;
        long long n = i;
        bs = n;
        while(bs.count() > 1) {
            if(n % 2 == 0) {
                n /= 2;
            }
            else {
                n = 3*n + 1;
            }
            bs = n;
            ++chainLen;
        }
        int j=0;
        while(!bs[j]) {
            ++chainLen;
            ++j;
        }
        if(chainLen > maxChainLen) {
            maxChainLen = chainLen;
            maxChainLenNumber = i;
        }
    }
    qDebug() << maxChainLenNumber << " has a Collatz chain length of " << maxChainLen;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
