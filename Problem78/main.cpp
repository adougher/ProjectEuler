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

static int toMod = 100000;
static void
makeChange(const std::vector<int> &denoms,
           const int &numOrig,
           int num,
           int maxDenom,
           std::vector<std::vector<int>> &storedWays,
           int &ways)
{
    int sz = (int)denoms.size();
    for(int j=0; j < sz; ++j) {
        if(denoms[j] > maxDenom) {
            break;
        }
        if(denoms[j] == 1) {
            ways = (ways + 1) % toMod;
            continue;
        }
        int numReduced = num - denoms[j];
        if(numReduced == 0) {
            ways = (ways + 1) % toMod;
        }
        else {
            auto newDenom = std::min(denoms[j],numReduced);
            auto &stoWay = storedWays[numReduced][newDenom];
            if(stoWay > 0) {
//                qDebug() << "  found: {" << numReduced << ", " << newDenom << "}";
                ways = (ways + stoWay) % toMod;
            }
            else {
//                qDebug() << "  didn't find: {" << numReduced << ", " << newDenom << "}";
                int waysSub=0;
                makeChange(denoms,numOrig,numReduced,newDenom,storedWays,waysSub);
                stoWay = waysSub;
                ways = (ways + waysSub) % toMod;
            }
        }
    }
}

int main()
{
    Timer timer;
    int val=0;
    int search = 100000;
//    std::vector<std::vector<int>> storedWays(search+1,std::vector<int>(search+1,0));
//    for(long long i=1; i<search; ++i) {
//        std::vector<int> denoms;
//        for(int j=1; j<i; ++j) {
//            denoms.push_back(j);
//        }
//        int ways = 1;
//        makeChange(denoms,i,i,i,storedWays,ways);
//        storedWays[i][i] = ways % toMod;
//        storedWays[i][i-1] = (ways-1) % toMod;
//        std::cout << i << " coins can be separated into this many piles mod a milli: " << ways << std::endl;
//        if(ways == 0) {
//            val=i;
//            break;
//        }
//    }
    std::vector<BigInt> storedWays(search+1,0);
    for(long long i=0; i<=search; ++i) {
        if(i==0) {
            storedWays[i] = 1;
        }
        else {
            long long lower = (long long)ceil(-((sqrt(24*i + 1))-1)/6);
            long long upper = (long long)ceil(((sqrt(24*i + 1))+1)/6);
            BigInt sum({});
            for(long long k=lower; k<=upper; ++k) {
                if(k == 0) {
                    continue;
                }
                long long index = i-(k*(3*k-1))/2;
                if(index >= 0) {
                    long long exp = (long long)pow(-1,k+1);
                    if(exp < 0) {
                        sum = sum - storedWays[index];
                    }
                    else {
                        sum = sum + storedWays[index];
                    }
                }
            }
            storedWays[i] = sum;
        }
//        std::cout << i << " coins can be separated into this many piles: " << storedWays[i];
        auto digVec = storedWays[i].digitsVec();
        long long digToVerify=6;
        bool sat = true;
        for(long long i=0; i<digToVerify; ++i) {
            if(digVec[i] != 0) {
                sat = false;
                break;
            }
        }
        if(sat) {
            val=i;
            break;
        }
    }
    qDebug() << "least value: " << val;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
