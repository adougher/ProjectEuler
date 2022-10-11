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
#include <QFile>

using namespace std;

static void
allPermutations(long long k, string &str, std::set<string> &permutations)
{
    if(k == 1) {
        permutations.insert(str);
    }
    else {
        for(long long i=0; i<k; ++i) {
            allPermutations(k - 1, str, permutations);
            int swap = k % 2 == 0 ? i : 0;
            auto temp = str[swap];
            str[swap] = str[k-1];
            str[k-1] = temp;
        }
    }
}

int main()
{
    Timer timer;
    string baseStr("0123456789");
    std::set<string> permutations;
    auto k = baseStr.size();
    allPermutations(k,baseStr,permutations);
    int i=1;
    for(auto it=permutations.begin(); it != permutations.end(); ++it) {
        baseStr = *it;
        if(i == 1000000) {
            break;
        }
        ++i;
    }
    qDebug() << "millionth lexicographic permutation: " << QString::fromStdString(baseStr);
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
