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
           const std::vector<Relation> &relations,
           const Relation &relation,
           int sum,
           int &maxSum)
{
    sum += values[relation.index];
    auto left = relation.leftChild;
    auto right = relation.rightChild;
    if(left == -1) {
        maxSum = std::max(sum,maxSum);
    }
    else {
        findMaxSum(values,relations,relations[left],sum,maxSum);
    }
    if(right == -1) {
        maxSum = std::max(sum,maxSum);
    }
    else {
        findMaxSum(values,relations,relations[right],sum,maxSum);
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
    int rows = 30;
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
    int maxSum = 0;
    findMaxSum(nums,relations,relations[0],0,maxSum);
    qDebug() << "max sum: " << maxSum;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
