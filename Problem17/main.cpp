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

static string
getOnesString(int num)
{
    if(num==0) {
        return "";
    }
    if(num==1) {
        return "one";
    }
    if(num==2) {
        return "two";
    }
    if(num==3) {
        return "three";
    }
    if(num==4) {
        return "four";
    }
    if(num==5) {
        return "five";
    }
    if(num==6) {
        return "six";
    }
    if(num==7) {
        return "seven";
    }
    if(num==8) {
        return "eight";
    }
    if(num==9) {
        return "nine";
    }
    return "";
}

static string
getTensString(int num)
{
    if(num < 10) {
        return getOnesString(num);
    }
    if(num==10) {
        return "ten";
    }
    if(num==11) {
        return "eleven";
    }
    if(num==12) {
        return "twelve";
    }
    if(num==13) {
        return "thirteen";
    }
    if(num==14) {
        return "fourteen";
    }
    if(num==15) {
        return "fifteen";
    }
    if(num==16) {
        return "sixteen";
    }
    if(num==17) {
        return "seventeen";
    }
    if(num==18) {
        return "eighteen";
    }
    if(num==19) {
        return "nineteen";
    }
    if(num>=20 && num < 30) {
        return "twenty"+getOnesString(num%10);
    }
    if(num>=30 && num < 40) {
        return "thirty"+getOnesString(num%10);
    }
    if(num>=40 && num < 50) {
        return "forty"+getOnesString(num%10);
    }
    if(num>=50 && num < 60) {
        return "fifty"+getOnesString(num%10);
    }
    if(num>=60 && num < 70) {
        return "sixty"+getOnesString(num%10);
    }
    if(num>=70 && num < 80) {
        return "seventy"+getOnesString(num%10);
    }
    if(num>=80 && num < 90) {
        return "eighty"+getOnesString(num%10);
    }
    if(num>=90 && num < 100) {
        return "ninety"+getOnesString(num%10);
    }
    return "";
}

static string
getHundredsString(int num)
{
    if(num % 100 == 0) {
        return getOnesString(num / 100) + "hundred";
    }
    else {
        return getOnesString(num / 100) + "hundredand" + getTensString(num % 100);
    }
    return "";
}

static string
getString(int num)
{
    if(num < 10) {
        return getOnesString(num);
    }
    if(num < 100) {
        return getTensString(num);
    }
    if(num < 1000) {
        return getHundredsString(num);
    }
    return "onethousand";
}

int main()
{
    Timer timer;
    string str;
    for(int i=1; i<=1000; ++i) {
        str += getString(i);
    }
    qDebug() << "string length: " << str.size();
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
