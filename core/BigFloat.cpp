#include "BigFloat.h"
#include <algorithm>
#include <iostream>
#include <QDebug>
#include <QVector>
#include "BigInt.h"

BigFloat::BigFloat()
{
    mIntegerDigits = {0};
    mFractionalDigits = {};
    mNonNegative = true;
}

BigFloat::BigFloat(const std::vector<int> &di,
                   const std::vector<int> &df,
                   bool nonneg)
{
    mIntegerDigits = di;
    mFractionalDigits = df;
    mNonNegative=nonneg;
}

BigFloat::BigFloat(const double &d)
{
    auto vecs = convertToDigitsVecs(d);
    mIntegerDigits = vecs.first;
    mFractionalDigits = vecs.second;
    mNonNegative=d>=0;
}

BigFloat::BigFloat(std::string d)
{
    if(d.size() == 0) {
        mIntegerDigits = {0};
        mFractionalDigits = {};
        mNonNegative = true;
    }
    else {
        mNonNegative=d[0] != '-';
        if(!mNonNegative) {
            d.erase(d.begin());
        }
        QString str = QString::fromStdString(d);
        if(str.contains(".")) {
            auto spl = str.split(".");
            auto splStr = spl[0].toStdString();
            auto sz = splStr.size();
            for(size_t i=0; i<sz; ++i) {
                mIntegerDigits.push_back(splStr[i] - 48);
            }
            splStr = spl[1].toStdString();
            sz = splStr.size();
            for(size_t i=0; i<sz; ++i) {
                mFractionalDigits.push_back(splStr[i] - 48);
            }
            std::reverse(mFractionalDigits.begin(),mFractionalDigits.end());
        }
        else {
            auto sz = d.size();
            for(size_t i=0; i<sz; ++i) {
                mIntegerDigits.push_back(d[i] - 48);
            }
        }
        std::reverse(mIntegerDigits.begin(),mIntegerDigits.end());
    }
}

BigFloat::BigFloat(const BigInt &i)
{
    mNonNegative=i.nonNegative();
    mIntegerDigits=i.digitsVec();
}

void
BigFloat::operator =(const BigFloat &i)
{
    mIntegerDigits = i.integerDigitsVec();
    mFractionalDigits = i.fractionalDigitsVec();
    mNonNegative = i.nonNegative();
}

bool
BigFloat::operator ==(const BigFloat &i)
{
    return mIntegerDigits == i.integerDigitsVec() &&
           mFractionalDigits == i.fractionalDigitsVec() &&
           mNonNegative == i.nonNegative();
}

BigFloat
BigFloat::operator +(const BigFloat &i)
{
    auto f1Vec = fractionalDigitsVec();
    auto f2Vec = i.fractionalDigitsVec();
    while(f1Vec.size() < f2Vec.size()) {
        f1Vec.insert(f1Vec.begin(),0);
    }
    while(f2Vec.size() < f1Vec.size()) {
        f2Vec.insert(f2Vec.begin(),0);
    }
    auto i1Vec = integerDigitsVec();
    auto i2Vec = i.integerDigitsVec();
    std::vector<int> fullVec1;
    fullVec1.insert(fullVec1.end(),f1Vec.begin(),f1Vec.end());
    fullVec1.insert(fullVec1.end(),i1Vec.begin(),i1Vec.end());
    std::vector<int> fullVec2;
    fullVec2.insert(fullVec2.end(),f2Vec.begin(),f2Vec.end());
    fullVec2.insert(fullVec2.end(),i2Vec.begin(),i2Vec.end());
    auto sum = BigInt(fullVec1) + BigInt(fullVec2);
    auto sumDigVec = sum.digitsVec();
    auto fDigits = f1Vec.size();
    std::vector<int> fractional;
    std::vector<int> integral;
    for(size_t i=0; i<fDigits; ++i) {
        fractional.push_back(sumDigVec[i]);
    }
    auto ts = sumDigVec.size();
    for(size_t i=fDigits; i<ts; ++i) {
        integral.push_back(sumDigVec[i]);
    }
    return BigFloat(integral,fractional);
}

BigFloat
BigFloat::operator -(const BigFloat &i)
{
    auto f1Vec = fractionalDigitsVec();
    auto f2Vec = i.fractionalDigitsVec();
    while(f1Vec.size() < f2Vec.size()) {
        f1Vec.insert(f1Vec.begin(),0);
    }
    while(f2Vec.size() < f1Vec.size()) {
        f2Vec.insert(f2Vec.begin(),0);
    }
    auto i1Vec = integerDigitsVec();
    auto i2Vec = i.integerDigitsVec();
    std::vector<int> fullVec1;
    fullVec1.insert(fullVec1.end(),f1Vec.begin(),f1Vec.end());
    fullVec1.insert(fullVec1.end(),i1Vec.begin(),i1Vec.end());
    std::vector<int> fullVec2;
    fullVec2.insert(fullVec2.end(),f2Vec.begin(),f2Vec.end());
    fullVec2.insert(fullVec2.end(),i2Vec.begin(),i2Vec.end());
    auto diff = BigInt(fullVec1) - BigInt(fullVec2);
    auto sumDigVec = diff.digitsVec();
    auto fDigits = f1Vec.size();
    std::vector<int> fractional;
    std::vector<int> integral;
    for(size_t i=0; i<fDigits; ++i) {
        fractional.push_back(sumDigVec[i]);
    }
    auto ts = sumDigVec.size();
    for(size_t i=fDigits; i<ts; ++i) {
        integral.push_back(sumDigVec[i]);
    }
    if(integral.size() == 0) {
        integral = {0};
    }
    auto bf = BigFloat(integral,fractional);
    bf.setNonNegative(diff.nonNegative());
    return bf;
}

BigFloat
BigFloat::operator -(const double &i)
{
    return (*this) - BigFloat(i);
}

BigFloat
BigFloat::operator *(const BigFloat &i)
{
    auto f1Vec = fractionalDigitsVec();
    auto f2Vec = i.fractionalDigitsVec();
    auto i1Vec = integerDigitsVec();
    auto i2Vec = i.integerDigitsVec();
    std::vector<int> fullVec1;
    fullVec1.insert(fullVec1.end(),f1Vec.begin(),f1Vec.end());
    fullVec1.insert(fullVec1.end(),i1Vec.begin(),i1Vec.end());
    std::vector<int> fullVec2;
    fullVec2.insert(fullVec2.end(),f2Vec.begin(),f2Vec.end());
    fullVec2.insert(fullVec2.end(),i2Vec.begin(),i2Vec.end());
    auto mult = BigInt(fullVec1) * BigInt(fullVec2);
    auto sumDigVec = mult.digitsVec();
    auto fDigits = f1Vec.size() + f2Vec.size();
    std::vector<int> fractional;
    std::vector<int> integral;
    auto sz = sumDigVec.size();
    auto m = std::min(sz,fDigits);
    for(size_t i=0; i<m; ++i) {
        fractional.push_back(sumDigVec[i]);
    }
    for(size_t i=m; i<fDigits; ++i) {
        fractional.push_back(0);
    }
    std::reverse(fractional.begin(),fractional.end());
    while(fractional.size() && fractional.back() == 0) {
        fractional.pop_back();
    }
    std::reverse(fractional.begin(),fractional.end());
    auto ts = sumDigVec.size();
    for(size_t i=fDigits; i<ts; ++i) {
        integral.push_back(sumDigVec[i]);
    }
    if(integral.size()==0) {
        integral = {0};
    }
    return BigFloat(integral,fractional);
}

BigFloat
BigFloat::operator /(const BigFloat &i)
{
    if((*this) == i) {
        return BigFloat(1.0);
    }
    auto dig1 = i.fractionalDigits();
    auto dig2 = (*this).fractionalDigits();
    auto r = reciprocal(BigFloat(i),2*std::max(dig1,dig2));
    return (*this) * r;
}

bool
BigFloat::operator <(const BigFloat &i)
{
    long long sz1 = integerDigits();
    long long sz2 = i.integerDigits();
    if(sz1 < sz2) {
        return true;
    }
    else if(sz1 > sz2) {
        return false;
    }
    auto dVec1 = integerDigitsVec();
    auto dVec2 = i.integerDigitsVec();
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
    sz1 = fractionalDigits();
    sz2 = i.fractionalDigits();
    dVec1 = fractionalDigitsVec();
    dVec2 = i.fractionalDigitsVec();
    std::reverse(dVec1.begin(),dVec1.end());
    std::reverse(dVec2.begin(),dVec2.end());
    auto sz = std::min(sz1,sz2);
    j = 0;
    while(j < sz) {
        if(dVec1[j] < dVec2[j]) {
            return true;
        }
        else if(dVec2[j] < dVec1[j]) {
            return false;
        }
        ++j;
    }
    if(sz1 < sz2) {
        return true;
    }
    return false;
}

bool
BigFloat::operator <(const BigInt &i)
{
    return (*this) < BigFloat(i);
}

void
BigFloat::operator =(const BigInt &i)
{
    (*this)=(BigFloat(i));
}

BigFloat
BigFloat::operator +(const BigInt &i)
{
    return (*this) + BigFloat(i);
}

BigFloat
BigFloat::operator -(const BigInt &i)
{
    return (*this) - BigFloat(i);
}

BigFloat
BigFloat::operator *(const BigInt &i)
{
    return (*this) * BigFloat(i);
}

BigFloat
BigFloat::operator /(const BigInt &i)
{
    return (*this) / BigFloat(i);
}

BigFloat
BigFloat::operator ^(const BigInt &i)
{
    return (*this) ^ BigFloat(i);
}

void
BigFloat::operator =(const double &i)
{
    auto ib = BigFloat(i);
    mIntegerDigits = ib.integerDigitsVec();
    mFractionalDigits = ib.fractionalDigitsVec();
    mNonNegative = ib.nonNegative();
}

std::ostream&
operator <<(std::ostream& os, const BigFloat &i)
{
    std::string stri;
    auto iVec = i.integerDigitsVec();
    auto szi = iVec.size();
    std::reverse(iVec.begin(),iVec.end());
    stri.resize(szi);
    for(size_t i=0; i<szi; ++i) {
        stri[i] = (char)(iVec[i]+48);
    }
    std::string strf;
    auto fVec = i.fractionalDigitsVec();
    auto szf = fVec.size();
    std::reverse(fVec.begin(),fVec.end());
    strf.resize(szf);
    for(size_t i=0; i<szf; ++i) {
        strf[i] = (char)(fVec[i]+48);
    }
    os << (!i.nonNegative() ? "-" : "") << stri.c_str() << (strf.size() > 0 ? "." : "") << strf.c_str() << std::endl;
    return os;
}

BigFloat
BigFloat::operator +(const double &i)
{
    return (*this + BigFloat(i));
}

BigFloat
BigFloat::operator *(const double &i)
{
    return (*this * BigFloat(i));
}

BigFloat
BigFloat::operator /(const double &i)
{
    return (*this / BigFloat(i));
}

BigFloat
BigFloat::operator ^(const long long &i)
{
    if(i == 0) {
        return BigFloat(1);
    }
    BigFloat copy = *this;
    BigFloat result = copy;
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

BigFloat
BigFloat::operator ^(const double &i)
{
    return (*this) ^ BigFloat(i);
}

BigFloat
BigFloat::operator ^(const BigFloat &i)
{
    if(BigFloat(0.0) == i) {
        return BigFloat(1.0);
    }
    return exp((*this) * log(i));
}

BigFloat
BigFloat::reciprocal(const BigFloat &i,
                     long long precision)
{
    if(BigFloat(1.0) == i) {
        return BigFloat(1.0);
    }
    bool newton = false; // not preciese enough for problem #26
    BigFloat divisor = i;
    if(newton) {
        while(BigFloat(2.0) < (divisor * i)) {
            divisor = divisor * 0.1;
        }
        int itrs = 5;
        for(int j=0; j<itrs; ++j) {
            auto num = divisor * i;
            auto num2 = BigFloat(2.0) - num;
            auto num3 = divisor * num2;
            divisor = num3;
        }
    }
    else {
        std::vector<int> fDig;
        BigFloat dividend(1.0);
        long long  fDigits = divisor.fractionalDigits();
        auto tenPow = (BigFloat(10.0)) ^ fDigits;
        if(fDigits) {
            divisor = divisor * tenPow;
        }
        int j=0;
        auto trueP = std::max(precision,(long long)30);
        while (j < trueP) {
            int zers = 0;
            while(dividend < divisor) {
                dividend = dividend * 10.0;
                ++zers;
            }
            for(int p=1; p<zers; ++p) {
                fDig.push_back(0);
                ++j;
            }
            long long count = 1;
            while(divisor*count < dividend) {
                ++count;
            }
            if((dividend - divisor*count) == BigFloat(0.0)) {
                fDig.push_back(count);
                break;
            }
            else {
                --count;
            }
            fDig.push_back(count);
            dividend = dividend - divisor * (double)count;
            ++j;
        }
        std::reverse(fDig.begin(), fDig.end());
        divisor = BigFloat({{0},fDig});
        divisor = divisor * tenPow;
    }
    return divisor;
}

BigFloat
BigFloat::log(const BigFloat &i)
{
    BigFloat xi = i;
    xi = (xi-1.0) / (xi+1.0);
    int itrs = 6;
    for(int j=1; j<itrs; ++j) {
        long long div = 2 * j + 1;
        xi = xi + reciprocal(BigFloat((double)div)) * (xi^div);
        xi.truncate(100);
    }
    xi = xi * 2.0;
    return xi;
}

BigFloat
BigFloat::exp(const BigFloat &i)
{
    auto bi = i;
    BigFloat res(1.0);
    int itrs = 20;
    for(long long j=1; j<itrs; ++j) {
        res = res + (bi^j) / BigFloat(BigInt::factorial(j));
        res.truncate(100);
    }
    return res;
}

void
BigFloat::truncate(const unsigned long long &t)
{
    auto fVec = fractionalDigitsVec();
    std::vector<int> trunc;
    std::reverse(fVec.begin(), fVec.end());
    size_t i=0;
    while(i<fVec.size() && i<t) {
        trunc.push_back(fVec[i]);
        ++i;
    }
    std::reverse(trunc.begin(), trunc.end());
    mFractionalDigits = trunc;
}

BigFloat
BigFloat::truncated(const unsigned long long &t)
{
    auto cp = (*this);
    cp.truncate(t);
    return cp;
}

std::string
BigFloat::toString() const
{
    std::string reti;
    auto szi = integerDigits();
    reti.resize(szi);
    for(size_t i=0; i<szi; ++i) {
        reti[i]=(char)(mIntegerDigits[i]+48);
    }
    std::string retf;
    auto szf = fractionalDigits();
    retf.resize(szf);
    for(size_t i=0; i<szf; ++i) {
        retf[i]=(char)(mFractionalDigits[i]+48);
    }
    std::string ret;
    ret.append(retf);
    if(szf > 0) {
        ret.append(".");
    }
    ret.append(reti);
    if(!mNonNegative) {
        ret.append("-");
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
}

std::pair<std::vector<int>,std::vector<int>>
BigFloat::convertToDigitsVecs(const double &number)
{
    if(number == 0) {
        return {{0},{}};
    }
    double tol = 1e-6;
    auto fl = (long long)floor(number + tol);
    std::vector<int> integerDigits = BigInt::convertToDigitsVec(fl);
    auto frac = number - fl;
    std::vector<int> fractionalDigits;
    int d=0;
    while(frac > tol && d < 16) {
        frac *= 10;
        fl = (long long)floor(frac + tol);
        fractionalDigits.push_back(fl);
        frac -= fl;
        ++d;
    }
    std::reverse(fractionalDigits.begin(),fractionalDigits.end());
    return {integerDigits,fractionalDigits};
}
