#include <iostream>

#include <QDebug>
#include <QVector>
#include <QFile>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include "core/timer.h"
#include "core/BigInt.h"

using namespace std;

struct Relation {
    Relation(int i, int l, int r) {
        index=i;
        leftChild=l;
        rightChild=r;
    }
    int index;
    int leftChild;
    int rightChild;
};

static void
findMaxSum(const std::vector<int> &values,
           const Relation &relation,
           int sum,
           std::vector<int> &maxFrom)
{
    auto val = values[relation.index];
    sum += val;
    auto left = relation.leftChild;
    auto right = relation.rightChild;
    if(left == -1) {
        maxFrom[relation.index] = val;
    }
    else {
        maxFrom[relation.index] = std::max(sum+maxFrom[left],sum+maxFrom[right]);
    }
}

int main()
{
    Timer timer;
    std::vector<int> nums;
    QFile readFile("C:\\Users\\andrew\\Downloads\\p067_triangle.txt");
    if(readFile.open(QIODevice::ReadOnly)) {
        const auto &fileLines = QString(readFile.readAll()).split("\n",QString::SkipEmptyParts);
        readFile.close();
        for(const auto &line : fileLines) {
            auto numbers = line.split(" ",QString::SkipEmptyParts);
            for(const auto &n : numbers) {
                nums.push_back(n.toInt());
            }
        }
    }
    int rows = 100;
    std::vector<Relation> relations;
    for(int i=0; i<rows-1; ++i) {
        int triNum = i * (i+1) / 2;
        int nextTriNum = (i+1) * (i+2) / 2;
        int counter = nextTriNum;
        while(triNum < nextTriNum) {
            relations.push_back(Relation(triNum,counter,counter+1));
            ++counter;
            ++triNum;
        }
    }
    int triNum = rows*(rows+1)/2;
    for(int i=triNum-rows; i<triNum; ++i) {
        relations.push_back(Relation(i,-1,-1));
    }
    auto sz = nums.size();
    std::vector<int> maxFrom(sz,-1);
    for(int j=(int)sz-1; j >= 0; --j) {
        findMaxSum(nums,relations[j],0,maxFrom);
    }
    qDebug() << "max path: " << maxFrom[0];
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
