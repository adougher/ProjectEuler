#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include "core/timer.h"

using namespace std;


int main()
{
    Timer timer;
    int gridDim1 = 21;
    int gridDim2 = 21;
    vector<vector<long long>> grid(gridDim1,vector<long long>(gridDim2,0));
    int maxIndex1 = gridDim1 - 1;
    int maxIndex2 = gridDim2 - 1;
    grid[maxIndex1][maxIndex2] = -1;
    grid[maxIndex1][maxIndex2-1] = 1;
    grid[maxIndex1-1][maxIndex2] = 1;
    grid[maxIndex1-1][maxIndex2-1] = 2;
    for(int i=maxIndex1; i>-1; --i) {
        for(int j=maxIndex2; j>-1; --j) {
            auto & el = grid[i][j];
            if(el == 0) {
                if(i < maxIndex1) {
                    el += grid[i+1][j];
                }
                if(j < maxIndex2) {
                    el += grid[i][j+1];
                }
            }
        }
    }
    qDebug() << "number of routes" << grid[0][0];
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
