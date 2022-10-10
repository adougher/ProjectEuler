#include "BigInt.h"
#include <algorithm>
#include <iostream>
#include <QDebug>

BigInt::BigInt()
{
    mDigits = {0};
    mNonNegative = true;
}

BigInt::BigInt(const std::vector<int> &d,
               bool nonneg)
{
    mDigits = d;
    mNonNegative=nonneg;
}

BigInt::BigInt(const long long &d)
{
    mDigits = convertToDigitsVec(d);
    mNonNegative=d>=0;
}

BigInt::BigInt(std::string d)
{
    if(d.size() == 0) {
        mDigits = {0};
        mNonNegative = true;
    }
    else {
        mNonNegative=d[0] != '-';
        if(!mNonNegative) {
            d.erase(d.begin());
        }
        auto sz = d.size();
        for(size_t i=0; i<sz; ++i) {
            mDigits.push_back(d[i] - 48);
        }
        std::reverse(mDigits.begin(),mDigits.end());
    }
}

void
BigInt::operator =(const BigInt &i)
{
    mDigits = i.digitsVec();
    mNonNegative = i.nonNegative();
}

BigInt
BigInt::operator +(const BigInt &i)
{
    auto sz1 = digits();
    auto sz2 = i.digits();
    size_t maxSz = std::max(sz1,sz2);
    auto dVec1 = mDigits;
    auto dVec2 = i.digitsVec();
    dVec1.resize(maxSz);
    dVec2.resize(maxSz);
    std::vector<int> result(maxSz);
    int carry = 0;
    for(size_t i=0; i<maxSz; ++i) {
        auto dig = dVec1[i] + dVec2[i] + carry;
        carry = dig / 10;
        if(carry > 0) {
            dig = dig % 10;
        }
        result[i] = dig;
    }
    if(carry > 0) {
        result.push_back(carry);
    }
    return BigInt(result);
}

BigInt
BigInt::operator *(const BigInt &i)
{
    auto sz1 = digits();
    auto sz2 = i.digits();
    auto dVec1 = mDigits;
    auto dVec2 = i.digitsVec();
    auto pSz = sz1+sz2;
    std::vector<int> polyRep(pSz,0);
    for(size_t i=0; i<sz1; ++i) {
        for(size_t j=0; j<sz2; ++j) {
            auto polyRepIndex = i+j;
            polyRep[polyRepIndex] += dVec1[i] * dVec2[j];
        }
    }
    while(polyRep.size() && polyRep.back() == 0) {
        polyRep.pop_back();
    }
    pSz = polyRep.size();
    BigInt ret(0);
    for(size_t i=0; i<pSz; ++i) {
        ret = ret + pow10Mult(BigInt(polyRep[i]),i);
    }
    return ret;
}

bool
BigInt::operator <(const BigInt &i)
{
    long long sz1 = digits();
    long long sz2 = i.digits();
    if(sz1 < sz2) {
        return true;
    }
    else if(sz1 > sz2) {
        return false;
    }
    auto dVec1 = digitsVec();
    auto dVec2 = i.digitsVec();
    int j = sz1 - 1;
    while(j >= 0) {
        if(dVec1[j] < dVec2[j]) {
            return true;
        }
        --j;
    }
    return false;
}

BigInt
BigInt::pow10Mult(const BigInt &i,const long long &power)
{
    if(power <= 0) {
        return i;
    }
    auto dVec = i.digitsVec();
    std::vector<int> zeros(power,0);
    zeros.insert(zeros.end(),dVec.begin(),dVec.end());
    return zeros;
}

void
BigInt::operator =(const long long &i)
{
    auto ib = BigInt(i);
    mDigits = ib.digitsVec();
    mNonNegative = ib.nonNegative();
}

std::ostream&
operator <<(std::ostream& os, const BigInt &i)
{
    std::string str;
    auto dVec = i.digitsVec();
    auto sz = dVec.size();
    std::reverse(dVec.begin(),dVec.end());
    str.resize(sz);
    for(size_t i=0; i<sz; ++i) {
        str[i] = (char)(dVec[i]+48);
    }
    os << (!i.nonNegative() ? "-" : "") << str.c_str() << std::endl;
    return os;
}

BigInt
BigInt::operator +(const long long &i)
{
    return (*this + BigInt(i));
}

BigInt
BigInt::operator *(const long long &i)
{
    return (*this * BigInt(i));
}

BigInt
BigInt::operator ^(const long long &i)
{
    if(i == 0) {
        return BigInt(1);
    }
    BigInt copy = *this;
    BigInt result = copy;
    if(i == 1) {
        return result;
    }
    long long pows = (long long)floor(log2(i));
    long long twoPow = 1;
    while(twoPow <= pows) {
        result = result * result;
        ++twoPow;
    }
    twoPow = (long long)pow(2,twoPow - 1);
    result = result * (copy ^ (i - twoPow));
    return result;
}

BigInt
BigInt::factorial(const BigInt &i)
{
    BigInt result(1);
    BigInt count(1);
    while(count < i) {
        result = result * count;
        count = count + BigInt(1);
    }
    return result * i;
}

std::string
BigInt::toString() const
{
    std::string ret;
    ret.resize(digits());
    auto sz = digits();
    for(size_t i=0; i<sz; ++i) {
        ret[i]=(char)(mDigits[i]+48);
    }
    if(!mNonNegative) {
        ret.append("-");
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
}

std::vector<int>
BigInt::convertToDigitsVec(const long long &number)
{
    if(number == 0) {
        return {0};
    }
    std::vector<int> digits;
    long long ds = 1;
    long long start = 1;
    while(start <= number) {
        start *= 10;
        ++ds;
    }
    --ds;
    long long reduce = number;
    if(reduce < 0) {
        reduce *= -1;
    }
    long long ds_reduce = ds;
    while(ds_reduce > 0) {
        start /= 10;
        digits.push_back((int)(reduce / start));
        reduce -= digits.back() * start;
        --ds_reduce;
    }
    std::reverse(digits.begin(),digits.end());
    return digits;
}
