#ifndef BIGFLOAT_H_
#define BIGFLOAT_H_

#include "Api.h"
#include <vector>
#include <string>
#include "BigInt.h"

class COREAPI BigFloat
{
    public:
        BigFloat();
        BigFloat(const std::vector<int> &di,
                 const std::vector<int> &df,
                 bool nonneg=true);
        BigFloat(const double &d);
        BigFloat(std::string d);
        BigFloat(const BigInt &d);

        void operator =(const BigFloat &i);
        BigFloat operator +(const BigFloat &i);
        BigFloat operator -(const BigFloat &i);
        BigFloat operator *(const BigFloat &i);
        BigFloat operator /(const BigFloat &i);
        BigFloat operator ^(const BigFloat &i);
        bool operator <(const BigFloat &i);
        bool operator ==(const BigFloat &i);
        void operator =(const BigInt &i);
        BigFloat operator +(const BigInt &i);
        BigFloat operator -(const BigInt &i);
        BigFloat operator *(const BigInt &i);
        BigFloat operator /(const BigInt &i);
        BigFloat operator ^(const BigInt &i);
        bool operator <(const BigInt &i);
        void operator =(const double &i);
        BigFloat operator +(const double &i);
        BigFloat operator -(const double &i);
        BigFloat operator *(const double &i);
        BigFloat operator /(const double &i);
        BigFloat operator ^(const long long &i);
        BigFloat operator ^(const double &i);
        friend COREAPI std::ostream& operator <<(std::ostream& os, const BigFloat &i);

        static BigFloat reciprocal(const BigFloat &i, long long precision=100);
        static BigFloat log(const BigFloat &i);
        static BigFloat exp(const BigFloat &i);

        size_t integerDigits() const {return mIntegerDigits.size();}
        size_t fractionalDigits() const {return mFractionalDigits.size();}
        size_t digits() const {return mIntegerDigits.size() + mFractionalDigits.size();}
        std::vector<int> integerDigitsVec() const {return mIntegerDigits;}
        std::vector<int> fractionalDigitsVec() const {return mFractionalDigits;}
        std::string toString() const;
        bool nonNegative() const {return mNonNegative;}
        void setNonNegative(const bool &b) {mNonNegative=b;}

        void truncate(const unsigned long long &);
        BigFloat truncated(const unsigned long long &);

        static std::pair<std::vector<int>,std::vector<int>> convertToDigitsVecs(const double &number);

    private:
        std::vector<int> mIntegerDigits;
        std::vector<int> mFractionalDigits;
        bool mNonNegative=true;
};

#endif

