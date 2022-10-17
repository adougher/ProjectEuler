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
#include "core/sets.h"

using namespace std;

int main()
{
    Timer timer;
    string baseStr("0123456789");
    std::vector<string> permutations;
    auto k = baseStr.size();
    sets::permutations(k,baseStr,permutations);
    std::sort(permutations.begin(),permutations.end());
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
