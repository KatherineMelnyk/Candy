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

	friend std::ostream& operator<<(std::ostream& os, const BigNumber& BG);
	operator std::string() const;
	
	friend bool operator==(const BigNumber& left, const BigNumber&right);
	friend bool operator<(const BigNumber& left, const BigNumber&right);
	friend bool operator !=(const BigNumber& left, const BigNumber& right);
	friend bool operator <=(const BigNumber& left, const BigNumber& right);
	friend bool operator >(const BigNumber& left, const BigNumber& right);
	friend bool operator >=(const BigNumber& left, const BigNumber& right);
	
	friend BigNumber operator * (BigNumber &left, int &n);
	friend BigNumber operator / (BigNumber &left, int &n);
	friend int operator % (BigNumber &left, int &n);
	
	friend BigNumber operator + (BigNumber &left, BigNumber &right);
	friend BigNumber operator - (BigNumber &left, BigNumber &right);
	friend BigNumber operator * (BigNumber &left, BigNumber &right);
	friend BigNumber operator / (BigNumber &left, BigNumber &right);
	
	BigNumber& operator -=(BigNumber value);
	BigNumber& operator +=(BigNumber value);
	BigNumber& operator *=(BigNumber value);
	BigNumber& operator*= (int n);
	BigNumber& operator/= (int n);
	
	BigNumber operator --();
	BigNumber operator ++();
	
	BigNumber pow_(BigNumber &left);
	BigNumber Karatsuba_mul(BigNumber& left, BigNumber& right);

private:
	std::vector <int> _number;
	void remove_leading_zeroes();
	bool odd();
	bool even();
};

int to_int(BigNumber &number);
