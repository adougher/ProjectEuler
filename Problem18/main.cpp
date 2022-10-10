#include <iostream>

#include <QDebug>
#include <QVector>
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
    std::vector<int> nums={75,
                           95, 64,
                           17, 47, 82,
                           18, 35, 87, 10,
                           20, 04, 82, 47, 65,
                           19, 01, 23, 75, 03, 34,
                           88, 02, 77, 73, 07, 63, 67,
                           99, 65, 04, 28, 06, 16, 70, 92,
                           41, 41, 26, 56, 83, 40, 80, 70, 33,
                           41, 48, 72, 33, 47, 32, 37, 16, 94, 29,
                           53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,
                           70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,
                           91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,
                           63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,
                           04, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 04, 23};
    int rows = 15;
//    std::vector<int> nums={3,
//                           7, 4,
//                           2, 4, 6,
//                           8, 5, 9, 3};
//    int rows = 4;
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
