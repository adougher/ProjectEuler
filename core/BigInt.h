#ifndef BIGINT_H_
#define BIGINT_H_

#include "Api.h"
#include <vector>
#include <string>

class COREAPI BigInt
{
    public:
        BigInt();
        BigInt(const std::vector<int> &d,
               bool nonneg=true);
        BigInt(const long long &d);
        BigInt(std::string d);

        void operator =(const BigInt &i);
        BigInt operator +(const BigInt &i);
        BigInt operator -(const BigInt &i);
        BigInt operator *(const BigInt &i);
        bool operator <(const BigInt &i) const;
        bool operator ==(const BigInt &i);
        void operator =(const long long &i);
        BigInt operator +(const long long &i);
        BigInt operator -(const long long &i);
        BigInt operator *(const long long &i);
        BigInt operator ^(const long long &i);

        friend COREAPI std::ostream& operator <<(std::ostream& os, const BigInt &i);

        size_t digits() const {return mDigits.size();}
        std::vector<int> digitsVec() const {return mDigits;}
        std::string toString() const;
        bool nonNegative() const {return mNonNegative;}
        void setNonNegative(const bool &b) {mNonNegative=b;}

        static BigInt factorial(const BigInt &i);
        static long long factorial(const long long &i);
        static std::vector<int> convertToDigitsVec(const long long &number);

    private:
        BigInt pow10Mult(const BigInt &i,const long long &power);
        std::vector<int> mDigits;
        bool mNonNegative=true;
};

#endif

