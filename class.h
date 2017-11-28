#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>


static const int BASE = 10;

class BigNumber {
public:
	BigNumber();
	BigNumber(std::string str);
	BigNumber(unsigned long long num);
	void remove_leading_zeroes();

	friend std::ostream& operator<<(std::ostream& os, const BigNumber& BG);
	operator std::string() const;
	
	BigNumber& operator -=(BigNumber value);
	BigNumber& operator +=(BigNumber value);
	BigNumber& operator *=(BigNumber value);
	
	friend bool operator==(const BigNumber& left, const BigNumber&right);
	friend bool operator<(const BigNumber& left, const BigNumber&right);
	friend bool operator !=(const BigNumber& left, const BigNumber& right);
	friend bool operator <=(const BigNumber& left, const BigNumber& right);
	friend bool operator >(const BigNumber& left, const BigNumber& right);
	friend bool operator >=(const BigNumber& left, const BigNumber& right);
	
	friend BigNumber operator + (BigNumber &left, BigNumber &right);
	friend BigNumber operator - (BigNumber &left, BigNumber &right);
	friend BigNumber operator * (BigNumber &left, BigNumber &right);
	friend BigNumber operator * (BigNumber &left, int &n);
	friend BigNumber operator / (BigNumber &left, int &n);
	friend int operator % (BigNumber &left, int &n);
	
	BigNumber Karatsuba_mul(BigNumber& left, BigNumber& right);

private:
	std::vector <int> _number;
};
