#include "sets.h"
#include <bitset>

using namespace std;

template <class T>
vector<vector<T>>
sets::powerSet(const vector<T> &set)
{
    vector<vector<T>> pSet;
    bitset<10000> b;
    long long sz = set.size();
    long long order = (long long)pow(2,sz);
    for(int i=1; i<order; ++i) {
        vector<T> oneSet;
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

template <class T>
void
sets::permutations(long long k, T &container,  std::vector<T> &permutations)
{
    if(k == 1) {
        permutations.push_back(container);
    }
    else {
        for(long long i=0; i<k; ++i) {
            sets::permutations(k - 1, container, permutations);
            long long swap = k % 2 == 0 ? i : 0;
            auto temp = container[swap];
            container[swap] = container[k-1];
            container[k-1] = temp;
        }
    }
}


template
vector<vector<long long>>
COREAPI sets::powerSet<long long>(const vector<long long> &set);

template
void
COREAPI sets::permutations<string>(long long k, string &container, std::vector<string> &permutations);

template
void
COREAPI sets::permutations<std::vector<long long>>(long long k, std::vector<long long> &container,
                                                   std::vector<std::vector<long long>> &permutations);

template
void
COREAPI sets::permutations<std::vector<int>>(long long k, std::vector<int> &container,
                                             std::vector<std::vector<int>> &permutations);
