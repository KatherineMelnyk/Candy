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
	
	const BigNumber operator +() const;
	const BigNumber operator -() const;
	
	BigNumber& operator -=(BigNumber value);
	BigNumber& operator +=(BigNumber value);
	BigNumber& operator *=(BigNumber value);
	
	friend bool operator==(const BigNumber& left, const BigNumber&right);
	friend bool operator<(const BigNumber& left, const BigNumber&right);
	friend bool operator !=(const BigNumber& left, const BigNumber& right);
	friend bool operator <=(const BigNumber& left, const BigNumber& right);
	friend bool operator >(const BigNumber& left, const BigNumber& right);
	friend bool operator >=(const BigNumber& left, const BigNumber& right);
	
	friend const BigNumber operator + (BigNumber &left, BigNumber &right);
	friend const BigNumber operator - (BigNumber &left, BigNumber &right);
	friend const BigNumber operator * (BigNumber &left, BigNumber &right);
	
	BigNumber Karatsuba_mul(BigNumber& left, BigNumber& right);

private:
	std::vector <int> _number;
};
