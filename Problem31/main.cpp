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

static void
makeChange(const std::vector<int> &denoms,
           int num,
           int maxDenom,
           int &ways)
{
    if(num == 0) {
        ++ways;
    }
    else {
        int sz = (int)denoms.size();
        for(int j=sz-1; j >= 0; --j) {
            if(denoms[j] > num || denoms[j] > maxDenom) {
                continue;
            }
            int numReduced = num - denoms[j];
            makeChange(denoms,numReduced,denoms[j],ways);
        }
    }

}

int main()
{
    Timer timer;
    std::vector<int> denoms = {1,2,5,10,20,50,100,200};
    int ways=0;
    makeChange(denoms,200,200,ways);
    qDebug() << "number of ways: " << ways;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
