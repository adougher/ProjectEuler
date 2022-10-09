#include "sets.h"
#include <bitset>

using namespace std;

vector<vector<long long>>
sets::powerSet(const vector<long long> &set)
{
    vector<vector<long long>> pSet;
    bitset<10000> b;
    long long sz = set.size();
    long long order = (long long)pow(2,sz);
    for(int i=1; i<order; ++i) {
        vector<long long> oneSet;
        b = i;
        for(long long j=0; j<sz; ++j) {
            if(b[j]) {
                oneSet.push_back(set[j]);
            }
        }
        pSet.push_back(oneSet);
    }
    return pSet;
}
