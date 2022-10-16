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
#include <QFile>

using namespace std;

int main()
{
    Timer timer;
    std::set<long long> triangleNumSet;
    for(long long i=1; i<1000000; ++i) {
        triangleNumSet.insert(i*(i+1)/2);
    }
    long long count=0;
    QFile readFile("C:\\Users\\andrew\\Downloads\\p042_words.txt");
    if(readFile.open(QIODevice::ReadOnly)) {
        const auto &fileString = QString(readFile.readAll());
        readFile.close();
        set<string> strs;
        const auto names = fileString.split(",");
        for(auto name : names) {
            name.remove(0,1);
            name.remove(name.size() - 1,1);
            strs.insert(name.toStdString());
        }
        for(auto it=strs.begin(); it!=strs.end(); ++it) {
            long long nameSum=0;
            for(const auto &c : (*it)) {
                nameSum += (long long)c - 64;
            }
            if(triangleNumSet.find(nameSum) != triangleNumSet.end()) {
                ++count;
            }
        }
    }
    qDebug() << "triangle names: " << count;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
