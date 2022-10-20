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
    long long limit=10000;
    long long count=0;
    int maxItrs = 50;
    for(int i=10; i<limit; ++i) {
        BigInt num(i);
        int itrs = 0;
        while(itrs < maxItrs) {
            auto digVec = num.digitsVec();
            if(itrs > 0) {
                int ds = (int)digVec.size();
                bool palindrome = true;
                for(int j=0; j<ds/2; ++j) {
                    if(digVec[j] != digVec[ds - j - 1]) {
                        palindrome = false;
                        break;
                    }
                }
                if(palindrome) {
                    break;
                }
            }
            std::reverse(digVec.begin(),digVec.end());
            while(digVec.back() == 0) {
                digVec.pop_back();
            }
            BigInt revNum(digVec);
            num = num + revNum;
            ++itrs;
        }
        if(itrs == maxItrs) {
            ++count;
        }
    }
    qDebug() << "total Lychrel numebrs under 10000: " << count;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
