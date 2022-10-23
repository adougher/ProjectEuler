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
    auto ni = i;
    auto t = (*this);
    bool flipSign = false;
    if(ni.nonNegative() && !t.nonNegative()) {
        t.setNonNegative(true);
        return ni - t;
    }
    else if(!ni.nonNegative() && t.nonNegative()) {
        ni.setNonNegative(true);
        return t - ni;
    }
    else if(!ni.nonNegative() && !t.nonNegative()) {
        flipSign = true;
    }
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
    auto ri = BigInt(result);
    if(flipSign) {
        ri.setNonNegative(false);
    }
    return ri;
}

BigInt
BigInt::operator -(const BigInt &i)
{
    BigInt more = *this;
    BigInt less = i;
    if(more == less) {
        return BigInt({});
    }
    if(!more.nonNegative() && less.nonNegative()) {
        more.setNonNegative(true);
        auto res = more + less;
        res.setNonNegative(false);
        return res;
    }
    else if(!more.nonNegative() && !less.nonNegative()) {
        less.setNonNegative(true);
        return less - more;
    }
    else if(more.nonNegative() && !less.nonNegative()) {
        less.setNonNegative(true);
        return less + more;
    }
    bool negative = false;
    if(more < less) {
        BigInt temp = more;
        more = less;
        less = temp;
        negative = true;
    }
    auto sz1 = more.digits();
    auto sz2 = less.digits();
    size_t maxSz = std::max(sz1,sz2);
    auto dVec1 = more.digitsVec();
    auto dVec2 = less.digitsVec();
    dVec1.resize(maxSz);
    dVec2.resize(maxSz);
    std::vector<int> result(maxSz);
    for(size_t i=0; i<maxSz; ++i) {
        if(dVec1[i] < dVec2[i]) {
            result[i] = 10 + dVec1[i] - dVec2[i];
            size_t j = i + 1;
            while(j < maxSz && dVec1[j] == 0) {
                dVec1[j] = 9;
                ++j;
            }
            if(j < maxSz) {
                dVec1[j] -= 1;
            }
        }
        else {
            result[i] = dVec1[i] - dVec2[i];
        }
    }
    while(result.back() == 0) {
        result.pop_back();
    }
    auto bi = BigInt(result);
    bi.setNonNegative(!negative);
    return bi;
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
    ret.setNonNegative((i.nonNegative() && (*this).nonNegative()) ||
                       (!i.nonNegative() && !(*this).nonNegative()));
    return ret;
}

BigInt
BigInt::operator /(const BigInt &i)
{
    if(*this < i) {
        return BigInt({0});
    }
    if(*this == i) {
        return BigInt({1});
    }
    if(BigInt({1}) == i) {
        return *this;
    }
    std::vector<int> resDig;
    BigInt dividend = *this;
    BigInt divisor = i;
    auto divVec = dividend.digitsVec();
    std::reverse(divVec.begin(),divVec.end());
    size_t index = 0;
    auto dvs = divVec.size();
    std::vector<int> vec;
    while(1) {
        if(index >= dvs) {
            break;
        }
        auto bi = BigInt(vec);
        while(vec.size() < dvs && bi < divisor) {
            vec.insert(vec.begin(),divVec[index]);
            bi = BigInt(vec);
            ++index;
        }
        int mult = 1;
        auto divCopy = divisor;
        while(divCopy * mult < bi) {
            ++mult;
        }
        if(bi < divCopy * mult) {
            --mult;
        }
        divCopy = divCopy * mult;
        resDig.push_back(mult);
        auto diff = bi - divCopy;
        if(BigInt({}) == diff) {
            vec.clear();
        }
        else {
            vec = diff.digitsVec();
        }
//        qDebug() << "vec: " << QVector<int>::fromStdVector(vec);
    }
    std::reverse(resDig.begin(),resDig.end());
    return BigInt(resDig);
}

BigInt
BigInt::operator %(const BigInt &i)
{
    auto div = (*this / i);
    if(div == 0) {
        return *this;
    }
    return (*this - (div * i));
}

bool
BigInt::operator <(const BigInt &i) const
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
        else if(dVec2[j] < dVec1[j]) {
            return false;
        }
        --j;
    }
    return false;
}

bool
BigInt::operator ==(const BigInt &i)
{
    return mDigits == i.digitsVec() &&
           mNonNegative == i.nonNegative();
}

bool
BigInt::operator !=(const BigInt &i)
{
    return mDigits != i.digitsVec() ||
           mNonNegative != i.nonNegative();
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
BigInt::operator /(const long long &i)
{
    return (*this / BigInt(i));
}

BigInt
BigInt::operator %(const long long &i)
{
    return (*this % BigInt(i));
}

BigInt
BigInt::factorial(const BigInt &i)
{
    if(BigInt({})==i) {
        return BigInt({1});
    }
    BigInt result(1);
    BigInt count(1);
    while(count < i) {
        result = result * count;
        count = count + BigInt(1);
    }
    return result * i;
}

BigInt
BigInt::base2(const long long &i)
{
    std::vector<int> digits;
    long long cp=i;
    while(cp > 0) {
        auto r = cp % 2;
        digits.push_back(r);
        cp /= 2;
    }
    std::reverse(digits.begin(),digits.end());
    return BigInt(digits);
}

long long
BigInt::factorial(const long long &i)
{
    if(i == 0) {
        return 1;
    }
    long long result=1;
    long long count=1;
    while(count < i) {
        result = result * count;
        count = count + 1;
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

long long
BigInt::digitsVecToLong(const std::vector<int> &digits)
{
    long long num=0;
    long long p=0;
    for(const auto &d : digits) {
        num += d * pow(10,p);
        ++p;
    }
    return num;
}
