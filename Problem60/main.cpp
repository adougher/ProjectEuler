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

using namespace std;

extern std::vector<std::vector<int>> matrix_mult(const std::vector<std::vector<int>> &A,
                                                 const std::vector<std::vector<int>> &B);

static
std::vector<std::vector<long long>>
collectAnswers(const std::vector<long long> &primes,
               const std::set<long long> &primesSet,
               long long &lowestSum,
               std::vector<std::vector<long long>> subAnswers={},
               bool findMin=false)
{
    std::vector<std::vector<long long>> ret;
    std::set<std::vector<long long>> alreadyFound;
    bool sub = subAnswers.size();
    auto sets = sub ? subAnswers : sets::nChoose2Indices(primes);
    auto maxPrime = (*primesSet.rbegin()) + 1;
    lowestSum = std::numeric_limits<long long>::max();
    int sz = sub ? (int)primes.size() : 2;
    for(const auto &set : sets) {
        for(int i=1; i<sz; ++i) {
            std::vector<long long> setCp;
            for(const auto &s : set) {
                setCp.push_back(sub ? s : primes[s]);
            }
            if(sub) {
                std::set<long long> setSet;
                for(const auto &s : setCp) {
                    setSet.insert(s);
                }
                auto prime = primes[i];
                if(setSet.find(prime) != setSet.end()) {
                    continue;
                }
                setCp.push_back(prime);
                std::sort(setCp.begin(),setCp.end());
                if(alreadyFound.count(setCp)) {
                    continue;
                }
                if(findMin) {
                    long long sum=0;
                    for(const auto &s : setCp) {
                        sum += s;
                    }
                    if(sum > lowestSum) {
                        continue;
                    }
                }
            }
            auto pairs = sets::nChoose2Indices(setCp);
            bool valid = true;
            for(const auto &p : pairs) {
                auto p1 = setCp[p[0]];
                auto p2 = setCp[p[1]];
                auto digVec1 = BigInt::convertToDigitsVec(p1);
                auto digVec2 = BigInt::convertToDigitsVec(p2);
                auto newVec = digVec1;
                newVec.insert(newVec.end(),digVec2.begin(),digVec2.end());
                auto num = BigInt::digitsVecToLong(newVec);
                if((num <= maxPrime && primesSet.find(num) == primesSet.end()) ||
                   (num > maxPrime && !primes::isPrime(num))) {
                    valid = false;
                    break;
                }
                newVec = digVec2;
                newVec.insert(newVec.end(),digVec1.begin(),digVec1.end());
                num = BigInt::digitsVecToLong(newVec);
                if((num <= maxPrime && primesSet.find(num) == primesSet.end()) ||
                   (num > maxPrime && !primes::isPrime(num))) {
                    valid = false;
                    break;
                }
            }
            if(sub) {
                alreadyFound.insert(setCp);
            }
            if(valid) {
                if(findMin) {
                    long long sum=0;
                    for(const auto &s : setCp) {
                        sum += s;
                    }
                    qDebug() << "one five answer: " << QVector<long long>::fromStdVector(setCp);
                    if(sum < lowestSum) {
                        lowestSum = sum;
                        qDebug() << "found a new best!!!";
                    }
                }
                else {
                    ret.push_back(setCp);
                }
            }
        }
    }
    return ret;
}

static
std::vector<std::vector<long long>>
collect2Answers(const std::vector<long long> &primes,
                const std::set<long long> &primesSet)
{
    std::vector<std::vector<long long>> ret;
    auto maxPrime = (*primesSet.rbegin()) + 1;
    int sz = (int)primes.size();
    for(int i=1; i<sz; ++i) {
        for(int j=i+1; j<sz; ++j) {
            bool valid = true;
            auto p1 = primes[i];
            auto p2 = primes[j];
            auto digVec1 = BigInt::convertToDigitsVec(p1);
            auto digVec2 = BigInt::convertToDigitsVec(p2);
            auto newVec = digVec1;
            newVec.insert(newVec.end(),digVec2.begin(),digVec2.end());
            auto num = BigInt::digitsVecToLong(newVec);
            if((num <= maxPrime && primesSet.find(num) == primesSet.end()) ||
               (num > maxPrime && !primes::isPrime(num))) {
                valid = false;
            }
            if(valid) {
                newVec = digVec2;
                newVec.insert(newVec.end(),digVec1.begin(),digVec1.end());
                num = BigInt::digitsVecToLong(newVec);
                if((num <= maxPrime && primesSet.find(num) == primesSet.end()) ||
                   (num > maxPrime && !primes::isPrime(num))) {
                    valid = false;
                }
            }
            if(valid) {
                ret.push_back({p1,p2});
            }
        }
    }
    return ret;
}

static
std::vector<std::vector<long long>>
collectAnswers(const std::set<long long> &primesSet,
               std::vector<std::vector<long long>> subAnswers)
{
    std::vector<std::vector<long long>> ret;
    std::set<std::vector<long long>> alreadyFound;
    auto maxPrime = (*primesSet.rbegin()) + 1;
    auto sz = subAnswers.size();
    for(size_t i=0; i<sz; ++i) {
        for(size_t j=i+1; j<sz; ++j) {
            std::vector<long long> candidate;
            std::set<long long> candidateSet;
            auto subi = subAnswers[i];
            auto subj = subAnswers[j];
            auto targetSize = subi.size() + subj.size();
            for(const auto &s : subi) {
                candidateSet.insert(s);
            }
            for(const auto &s : subj) {
                candidateSet.insert(s);
            }
            if(candidateSet.size() != targetSize) {
                continue;
            }
            for(const auto &s : candidateSet) {
                candidate.push_back(s);
            }
            std::sort(candidate.begin(),candidate.end());
            if(alreadyFound.count(candidate)) {
                continue;
            }
            auto pairs = sets::nChoose2Indices(candidate);
            bool valid = true;
            for(const auto &p : pairs) {
                auto p1 = candidate[p[0]];
                auto p2 = candidate[p[1]];
                auto digVec1 = BigInt::convertToDigitsVec(p1);
                auto digVec2 = BigInt::convertToDigitsVec(p2);
                auto newVec = digVec1;
                newVec.insert(newVec.end(),digVec2.begin(),digVec2.end());
                auto num = BigInt::digitsVecToLong(newVec);
                if((num <= maxPrime && primesSet.find(num) == primesSet.end()) ||
                   (num > maxPrime && !primes::isPrime(num))) {
                    valid = false;
                    break;
                }
                newVec = digVec2;
                newVec.insert(newVec.end(),digVec1.begin(),digVec1.end());
                num = BigInt::digitsVecToLong(newVec);
                if((num <= maxPrime && primesSet.find(num) == primesSet.end()) ||
                   (num > maxPrime && !primes::isPrime(num))) {
                    valid = false;
                    break;
                }
            }
            if(valid) {
                alreadyFound.insert(candidate);
                ret.push_back(candidate);
            }
        }
    }
    return ret;
}

static
std::vector<std::vector<int>>
constructAdjacencyList(const std::vector<long long> &primes,
                       const std::set<long long> &primesSet)
{
    std::vector<std::vector<int>> ret;
    auto maxPrime = (*primesSet.rbegin()) + 1;
    int sz = (int)primes.size();
    ret.resize(sz);
    for(int i=1; i<sz; ++i) {
        for(int j=i+1; j<sz; ++j) {
            bool valid = true;
            auto p1 = primes[i];
            auto p2 = primes[j];
            auto digVec1 = BigInt::convertToDigitsVec(p1);
            auto digVec2 = BigInt::convertToDigitsVec(p2);
            auto newVec = digVec1;
            newVec.insert(newVec.end(),digVec2.begin(),digVec2.end());
            auto num = BigInt::digitsVecToLong(newVec);
            if((num <= maxPrime && primesSet.find(num) == primesSet.end()) ||
               (num > maxPrime && !primes::isPrime(num))) {
                valid = false;
            }
            if(valid) {
                newVec = digVec2;
                newVec.insert(newVec.end(),digVec1.begin(),digVec1.end());
                num = BigInt::digitsVecToLong(newVec);
                if((num <= maxPrime && primesSet.find(num) == primesSet.end()) ||
                   (num > maxPrime && !primes::isPrime(num))) {
                    valid = false;
                }
            }
            if(valid) {
                ret[i].push_back(j);
                ret[j].push_back(i);
            }
        }
    }
    return ret;
}

static
bool
findCliques(const std::vector<std::vector<int>> &adjList,
            const int &index,
            const int &row,
            const int &cliqueSize,
            int pathLen,
            std::set<long long> clique,
            std::set<std::set<long long>> &cliques)
{
    if(pathLen > cliqueSize) {
        return false;
    }
    if(index == row && pathLen == cliqueSize) {
        cliques.insert(clique);
        return true;
    }
    if(index == row && pathLen > 0) {
        return false;
    }
    int sz = (int)adjList[row].size();
    bool found=false;
    for(int i=0; i<sz; ++i) {
        long long neighbor = adjList[row][i];
        if(neighbor != index && clique.find(neighbor) != clique.end()) {
            break;
        }
        bool valid = true;
        for(const auto &c : clique) {
            auto prevAdjList = adjList[c];
            if(neighbor != index && std::find(prevAdjList.begin(),prevAdjList.end(),neighbor) == prevAdjList.end()) {
                valid = false;
                break;
            }
        }
        if(!valid) {
            continue;
        }
        auto cliqueCopy = clique;
        cliqueCopy.insert(neighbor);
        if(findCliques(adjList,index,neighbor,cliqueSize,pathLen+1,cliqueCopy,cliques) && pathLen > 0) {
            found=true;
            break;
        }
    }
    return found;
}

int main()
{
    Timer timer;
    bool approachOne = false;
    long long lowestSum = std::numeric_limits<long long>::max();
    if(approachOne) {
        std::vector<std::vector<long long>> thang;
        std::vector<std::vector<long long>> primes(5);
        std::set<long long> primesSet;
        std::vector<long long> limits{10000000,10000,10000,10000,5000};
        for(int i=0; i<5; ++i) {
            if(i==0) {
                primes[i] = primes::primes(limits[i]);
                auto ps = primes[i].size();
                for(size_t j=0; j<ps; ++j) {
                    primesSet.insert(primes[i][j]);
                }
            }
            else {
                primes[i] = primes[i-1];
                while(primes[i].back() > limits[i]) {
                    primes[i].pop_back();
                }
            }
        }
        auto answers = collect2Answers(primes[4],primesSet);
        answers = collectAnswers(primesSet,answers);
        answers = collectAnswers(primes[1],primesSet,lowestSum,answers,true);
    }
    else {
        long long limit = 100000000;
        long long limit2 = 10000;
        auto primes = primes::primes(limit);
        std::set<long long> primesSet;
        for(const auto &p : primes) {
            primesSet.insert(p);
        }
        while(primes.back() > limit2) {
            primes.pop_back();
        }
        auto adj = constructAdjacencyList(primes,primesSet);
        std::set<std::set<long long>> cliques;
        int sizeToFind = 5;
        auto ps = primes.size();
        for(int i=1; i<(int)ps; ++i) {
            findCliques(adj,i,i,sizeToFind,0,{i},cliques);
        }
        for(auto it=cliques.begin(); it != cliques.end(); ++it) {
            auto clique = (*it);
            QVector<long long> cv;
            int sum=0;
            for(const auto &c : clique) {
                sum+=primes[c];
                cv.push_back(primes[c]);
            }
            if(sum < lowestSum) {
                lowestSum = sum;
            }
        }
    }
    qDebug() << "the lowest sum is " << lowestSum;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
