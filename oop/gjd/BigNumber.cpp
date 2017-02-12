//
// This part should be completed by yourself
// ps. You can generate the definitions in the header file
// Just click on yellow background functions and use the bulb appeared on the left
//

#include <iostream>
#include <cctype>
#include <algorithm>
#include <utility>
#include "BigNumber.h"

BigNumber::BigNumber()
{
    m_symbol = ZERO;
}

BigNumber::BigNumber(const std::string &numStr)
{
    auto length = numStr.length();
    if (length == 0)
    {
        m_symbol = ZERO;
        return;
    }
    int pos = 0;
    if (numStr[pos] == '-')
    {
        m_symbol = NEGATIVE;
        pos++;
    }
    else m_symbol = POSITIVE;
    for (int i = (int) length - 1; i >= pos; i--)
    {
        if (isdigit(numStr[i]))m_digits.push_back((digit_t) (numStr[i] - '0'));
        else throw BigNumberParseException();
    }
    trim();
}

BigNumber::BigNumber(int64_t num)
{
    if (num == 0)
    {
        m_symbol = ZERO;
        return;
    }
    if (num < 0)
    {
        num = -num;
        m_symbol = NEGATIVE;
    }
    else m_symbol = POSITIVE;
    while (num > 0)
    {
        m_digits.push_back(num % 10);
        num /= 10;
    }
}

BigNumber::BigNumber(const BigNumber &that)
{
    m_digits = that.m_digits;
    m_symbol = that.m_symbol;
}

BigNumber::~BigNumber()
{

}

std::string BigNumber::toString() const
{
    if (length() == 0)return "0";
    std::string str = m_symbol == NEGATIVE ? "-" : "";
    std::for_each(m_digits.crbegin(), m_digits.crend(), [&str](const digit_t digit) -> void
    {
        str.push_back(digit + '0');
    });
    return str;
}

size_t BigNumber::length() const
{
    return m_digits.size();
}

BigNumber::SYMBOL BigNumber::symbol() const
{
    return m_symbol;
}

BigNumber::digit_t BigNumber::operator[](size_t index) const
{
    if (index < 0 || index >= length())throw BigNumberBoundaryException();
    return m_digits[length() - 1 - index];
}

bool BigNumber::operator==(const BigNumber &that) const
{
    return m_digits == that.m_digits;
}

bool BigNumber::operator!=(const BigNumber &that) const
{
    return !(*this == that);
}

bool BigNumber::operator<(const BigNumber &that) const
{
    return !(that <= *this);
}

bool BigNumber::operator<=(const BigNumber &that) const
{
    if (m_symbol != that.m_symbol)return m_symbol < that.m_symbol;
    if (m_symbol == ZERO)return true;
    if (length() != that.length())return (m_symbol == POSITIVE) == length() < that.length();
    else if (m_symbol == POSITIVE)
    {
        for (int i = (int) length() - 1; i >= 0; i--)
            if (m_digits[i] != that.m_digits[i])return m_digits[i] < that.m_digits[i];
    }
    else
    {
        for (int i = (int) length() - 1; i >= 0; i--)
            if (that.m_digits[i] != m_digits[i])return that.m_digits[i] < m_digits[i];
    }
    return true;
}

bool BigNumber::operator>(const BigNumber &that) const
{
    return that < *this;
}

bool BigNumber::operator>=(const BigNumber &that) const
{
    return that <= *this;
}

const BigNumber &BigNumber::operator=(const std::string &numStr)
{
    return *this = numStr;
}

const BigNumber &BigNumber::operator=(const int64_t &num)
{
    return *this = num;
}

BigNumber BigNumber::operator+() const
{
    return BigNumber(*this);
}

BigNumber BigNumber::operator+(const BigNumber &that) const
{
    return add(this, &that);
}

const BigNumber &BigNumber::operator+=(const BigNumber &that)
{
    return *this = *this + that;
}

BigNumber &BigNumber::operator++()
{
    *this += BigNumber("1");
    return *this;
}

const BigNumber BigNumber::operator++(int)
{
    BigNumber oldNum = *this;
    ++*this;
    return oldNum;
}

BigNumber BigNumber::operator-() const
{
    BigNumber newNum = *this;
    newNum.m_symbol = (SYMBOL) -m_symbol;
    return newNum;
}

BigNumber BigNumber::operator-(const BigNumber &that) const
{
    return add(this, &that, NEGATIVE);
}

const BigNumber &BigNumber::operator-=(const BigNumber &that)
{
    return *this = *this - that;
}

BigNumber &BigNumber::operator--()
{
    *this -= BigNumber("1");
    return *this;
}

const BigNumber BigNumber::operator--(int)
{
    BigNumber oldNum = *this;
    --*this;
    return oldNum;
}

BigNumber BigNumber::operator*(const BigNumber &that) const
{
    BigNumber newNum;
    newNum.m_digits = std::vector<digit_t>(length() + that.length(), 0);
    newNum.m_symbol = SYMBOL((int) m_symbol * (int) that.m_symbol);
    for (int i = 0; i < length(); i++)
    {
        for (int j = 0; j < that.length(); j++)
        {
            newNum.m_digits[i + j] += m_digits[i] * that.m_digits[j];
            if (newNum.m_digits[i + j] > 10)
            {
                newNum.m_digits[i + j + 1] += newNum.m_digits[i + j] / 10;
                newNum.m_digits[i + j] %= 10;
            }
        }
    }
    newNum.trim();
    return newNum;
}

const BigNumber &BigNumber::operator*=(const BigNumber &that)
{
    return *this = *this * that;
}

BigNumber BigNumber::operator/(const BigNumber &that) const
{
    return divide(*this, that).first;
}

const BigNumber &BigNumber::operator/=(const BigNumber &that)
{
    return *this = *this / that;
}

BigNumber BigNumber::operator%(const BigNumber &that) const
{
    return divide(*this, that).second;
}

const BigNumber &BigNumber::operator%=(const BigNumber &that)
{
    return *this = *this % that;
}

void BigNumber::trim()
{
    while (length() > 0 && m_digits.back() == 0)
    {
        m_digits.pop_back();
    }
    if (length() == 0)m_symbol = ZERO;
}

BigNumber BigNumber::add(const BigNumber *numA, const BigNumber *numB, SYMBOL symbolB)
{
    if (numA->length() == numB->length() && numA->length() == 0)return BigNumber("0");
    auto symbolA = numA->m_symbol;
    symbolB = SYMBOL((int) symbolB * (int) numB->m_symbol);
    if (numB->length() > numA->length())
    {
        std::swap(numA, numB);
        std::swap(symbolA, symbolB);
    }
    BigNumber newNum;
    for (auto digit:numA->m_digits)newNum.m_digits.push_back(digit * symbolA);
    for (int i = 0; i < numB->length(); i++)newNum.m_digits[i] += numB->m_digits[i] * symbolB;
    digit_t shift = 0;
    for (int i = 0; i < newNum.length(); i++)
    {
        if (newNum.m_digits[i] >= 10)
        {
            shift = newNum.m_digits[i] / 10;
            newNum.m_digits[i] %= 10;
        }
        else if (newNum.m_digits[i] < 0)
        {
            shift = newNum.m_digits[i] / 10 - 1;
            newNum.m_digits[i] = (newNum.m_digits[i] % 10 + 10) % 10;
        }
        else continue;
        if (i < newNum.length() - 1)
        {
            newNum.m_digits[i + 1] += shift;
            shift = 0;
        }
    }
    if (shift != 0)newNum.m_digits.push_back(shift);
    if (newNum.m_digits.back() < 0)
    {
        newNum.m_digits[0] = 10 - newNum.m_digits[0];
        for (int i = 1; i < newNum.length() - 1; i++)newNum.m_digits[i] = 9 - newNum.m_digits[i];
        newNum.m_digits[newNum.length() - 1] = -newNum.m_digits[newNum.length() - 1] - 1;
        newNum.m_symbol = NEGATIVE;
    }
    else
    {
        newNum.m_symbol = POSITIVE;
    };
    newNum.trim();
    return newNum;
}

std::pair<BigNumber, BigNumber> BigNumber::divide(const BigNumber &divider, const BigNumber &divisor)
{
    if (divisor.m_symbol == ZERO)throw BigNumberDivideZeroException();
    BigNumber ans;
    if (divider.m_symbol == ZERO)return std::pair<BigNumber, BigNumber>(ans, ans);
    ans.m_symbol = SYMBOL((int) divider.m_symbol * (int) divisor.m_symbol);
    BigNumber div = divisor, mod = divider;
    long zeros = divider.length() - divisor.length();
    if (zeros < 0)return std::pair<BigNumber, BigNumber>(ans, mod);
    div.m_symbol = mod.m_symbol = POSITIVE;
    if (zeros > 0)
    {
        div.m_digits.insert(div.m_digits.begin(), zeros, 0);
    }
    for (; zeros >= 0; zeros--)
    {
        digit_t digit = 0;
        while (mod >= div)
        {
            digit++;
            mod -= div;
        }
        div.m_digits.erase(div.m_digits.begin());
        ans.m_digits.push_back(digit);
    }
    std::reverse(ans.m_digits.begin(), ans.m_digits.end());
    ans.trim();
    mod.m_symbol = divider.m_symbol;
    return std::pair<BigNumber, BigNumber>(ans, mod);
}
