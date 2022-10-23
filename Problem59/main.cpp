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

static int
charValueToInt(const char &c)
{
    if(c == '2') {
        return 1;
    }
    if(c == '3') {
        return 2;
    }
    if(c == '4') {
        return 3;
    }
    if(c == '5') {
        return 4;
    }
    if(c == '6') {
        return 5;
    }
    if(c == '7') {
        return 6;
    }
    if(c == '8') {
        return 7;
    }
    if(c == '9') {
        return 8;
    }
    if(c == 'T') {
        return 9;
    }
    if(c == 'J') {
        return 10;
    }
    if(c == 'Q') {
        return 11;
    }
    if(c == 'K') {
        return 12;
    }
    if(c == 'A') {
        return 13;
    }
    return 13;
}

static long long
scoreHand(const std::map<int,int> &valsToCounts,
          const std::map<QCharRef,int> &suitsToCounts)
{
    long long toPow = 14;
    long long high = 0;
    for(auto it=valsToCounts.begin(); it!=valsToCounts.end(); ++it) {
        if((*it).second == 1) {
            high = (*it).first;
        }
    }
    int i = 0;
    int val=0;
    bool straight = true;
    for(auto it=valsToCounts.begin(); it!=valsToCounts.end(); ++it) {
        if(i>0 && (*it).first - val != 1) {
            straight = false;
            break;
        }
        val=(*it).first;
        ++i;
    }
    straight = straight && i == 5;
    if(straight && suitsToCounts.size() == 1) {
        if((*valsToCounts.begin()).first == 9) {
            return pow((long long)toPow,(long long)11);
        }
        else {
            return high*pow((long long)toPow,(long long)10);
        }
    }
    else if(valsToCounts.size() == 2 &&
       ((*valsToCounts.begin()).second == 4 || (*valsToCounts.rbegin()).second == 4)) {
        if((*valsToCounts.begin()).second == 4) {
            return (*valsToCounts.begin()).first * pow((long long)toPow,(long long)9) + high;
        }
        else {
            return (*valsToCounts.rbegin()).second * pow((long long)toPow,(long long)9) + high;
        }
    }
    else if(valsToCounts.size() == 2 &&
       ((*valsToCounts.begin()).second == 3 || (*valsToCounts.rbegin()).second == 3)) {
        if((*valsToCounts.begin()).second == 3) {
            return (*valsToCounts.begin()).first * pow((long long)toPow,(long long)8) +
                   (*valsToCounts.rbegin()).first * pow((long long)toPow,(long long)7);
        }
        else {
            return (*valsToCounts.rbegin()).first * pow((long long)toPow,(long long)8) +
                   (*valsToCounts.begin()).first * pow((long long)toPow,(long long)7);
        }
    }
    else if(suitsToCounts.size() == 1) {
        return pow((long long)toPow,(long long)6) + high;
    }
    else if(straight) {
        return pow((long long)toPow,(long long)5) + high;
    }
    else if(valsToCounts.size() == 3) {
        for(auto it=valsToCounts.begin(); it!=valsToCounts.end(); ++it) {
            if((*it).second == 3) {
                return (*it).first * pow((long long)toPow,(long long)4) + high;
            }
        }
        long long sum = high;
        long long expo = 3;
        for(auto it=valsToCounts.begin(); it!=valsToCounts.end(); ++it) {
            if((*it).second == 2) {
                sum += (*it).first * pow((long long)toPow,(long long)expo);
                --expo;
            }
        }
        return sum;
    }
    else if(valsToCounts.size() == 4) {
        for(auto it=valsToCounts.begin(); it!=valsToCounts.end(); ++it) {
            if((*it).second == 2) {
                return (*it).first * (long long)toPow + high;
            }
        }
    }
    return high;
}

int main()
{
    Timer timer;
    QFile readFile("C:\\Users\\andrew\\Downloads\\p059_cipher.txt");
    QString decrypted;
    if(readFile.open(QIODevice::ReadOnly)) {
        const auto &fileString = QString(readFile.readAll());
        readFile.close();
        auto chars = fileString.split(",",QString::SkipEmptyParts);
        qDebug() << "chars: " << chars;
        bool foundThe = false;
        for(int i=97; i<=122; ++i) {
            for(int j=97; j<=122; ++j) {
                for(int k=97; k<=122; ++k) {
                    auto cs = chars.size();
                    for(int c=0; c<cs; c+=3) {
                        decrypted.push_back((char)(chars[c].toInt()) ^ i);
                        if(c+1 < cs) {
                            decrypted.push_back((char)(chars[c+1].toInt()) ^ j);
                            if(c+2 < cs) {
                                decrypted.push_back((char)(chars[c+2].toInt()) ^ k);
                            }
                        }
                    }
                    if(decrypted.contains("the",Qt::CaseInsensitive) && decrypted.contains("and",Qt::CaseInsensitive) &&
                       decrypted.contains("to",Qt::CaseInsensitive) && decrypted.contains("of",Qt::CaseInsensitive) &&
                       decrypted.contains("in",Qt::CaseInsensitive) && decrypted.contains("that",Qt::CaseInsensitive)) {
                        foundThe=true;
                        break;
                    }
                    decrypted.clear();
                }
                if(foundThe) {
                    break;
                }
            }
            if(foundThe) {
                break;
            }
        }
    }
    int sum = 0;
    int sz = decrypted.size();
    for(int i=0; i<sz; ++i) {
        sum += (char)decrypted[i].toLatin1();
    }
    qDebug() << "decrypted: " << decrypted;
    qDebug() << "sum of chars: " << sum;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
