#include "class.h"
#include <algorithm>

using namespace std;

BigNumber::BigNumber() {}

BigNumber::BigNumber(std::string str) {
	if (str.length() == 0) {
		this->_number.push_back(0);
	}
	else {
		for (long long i = str.length(); i > 0; i -= 1) {
			if (i < 1)
				this->_number.push_back(atoi(str.substr(0, i).c_str()));
			else
				this->_number.push_back(atoi(str.substr(i - 1, 1).c_str()));
		}
		this->remove_leading_zeroes();
	}
}

void BigNumber::remove_leading_zeroes() {
	while (this->_number.size() > 1 && this->_number.back() == 0) {
		this->_number.pop_back();
	}
}

BigNumber::BigNumber(unsigned long long num) {
	do {
		this->_number.push_back(num%BASE);
		num /= BASE;
	} while (num != 0);
}

std::ostream& operator<<(std::ostream& os, const BigNumber& BN) {
	if (BN._number.empty())
		os << 0;
	else {
		for (long long i = static_cast <long long>(BN._number.size()) - 1; i >= 0; --i)
			os << std::setw(1) << BN._number[i];
	}
	return os;
}

BigNumber::operator std::string() const {
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

bool operator==(const BigNumber& left, const BigNumber&right) {
	if (left._number.empty()) {
		if (right._number.empty() || right._number[0]) 
			return true;
	}
	if (right._number.empty()) {
		if (left._number.empty() || left._number[0])
			return true;
	}
	if (left._number.size() != right._number.size())
		return false;
	if (left._number.size() == right._number.size()) {
		for (size_t i = 0; i < left._number.size(); ++i)
			if (left._number[i] != right._number[i])
				return false;
	}
	else
		return true;
}

bool operator<(const BigNumber& left, const BigNumber&right) {
	if (left._number.size() != right._number.size()) {
		return left._number.size() < right._number.size();
	}
	else {
		for (long long i = left._number.size(); i >= 0; --i) {
			if (left._number[i] != right._number[i])
				return left._number[i] < right._number[i];
		}
		return false;
	}
}

bool operator !=(const BigNumber& left, const BigNumber& right) {
	return !(left == right);
}

bool operator <=(const BigNumber& left, const BigNumber& right) {
	return (left < right || left == right);
}

bool operator >(const BigNumber& left, const BigNumber& right) {
	return !(left <= right);
}

bool operator >=(const BigNumber& left, const BigNumber& right) {
	return !(left < right);
}

BigNumber& BigNumber::operator +=(BigNumber value) {
	return *this = (*this + value);
}

BigNumber& BigNumber::operator -=(BigNumber value) {
	return *this = (*this - value);
}

BigNumber BigNumber::operator++() {
	return (*this) += 1;
}

BigNumber BigNumber::operator--() {
	return (*this) -= 1;
}

BigNumber& BigNumber::operator *=(BigNumber value) {
	return *this = (*this * value);
}

BigNumber& BigNumber::operator*=(int n) {
	return *this = (*this * n);
}

BigNumber& BigNumber::operator/=(int n) {
	return *this = (*this / n);
}

BigNumber operator + (BigNumber &left,BigNumber &right) {
	int carry = 0;
	for (size_t i = 0; i < std::max(left._number.size(), right._number.size()); ++i) {
		if (left._number.size() == i)
			left._number.push_back(0);
		left._number[i] += carry + right._number[i];
		carry = left._number[i] >= BASE;
		if (carry != 0)
			left._number[i] -= BASE;
	}
	return left;
}

BigNumber operator -(BigNumber &left,BigNumber &right) {
		int carry = 0;
		for (size_t i = 0; i < right._number.size(); ++i) {
			left._number[i] -= (carry + right._number[i]);
			carry = left._number[i] < 0;
			if (carry != 0)
				left._number[i] += BASE;
		}
	left.remove_leading_zeroes();
	return left;
}

BigNumber operator *(BigNumber &left, BigNumber &right) {
	BigNumber result;
	result._number.resize(left._number.size() + right._number.size());
	for (size_t i = 0; i < left._number.size(); ++i) {
		int carry = 0;
		for (size_t j = 0; j < right._number.size() || carry != 0; ++j) {
			long long current = result._number[i + j] + left._number[i] * right._number[j] + carry;
			result._number[i + j] = static_cast<int>(current%BASE);
			carry = static_cast<int>(current / BASE);
		}
	}
	result.remove_leading_zeroes();
	return result;
}

BigNumber operator / (BigNumber & left, BigNumber &right) {
	BigNumber result;
	result._number.resize(left._number.size());
	int ost = 0;
	for (int i = (result._number.size() - 1); i >= 0; --i) {
		int current = ost * BASE + left._number[i];
		ost = current % to_int(right);
		result._number[i] = current / to_int(right);
	}
	if (!result._number[result._number.size() - 1] && result._number.size() != 1)
		result._number.resize(result._number.size() - 1);
	return result;
}

BigNumber operator % (BigNumber &left, BigNumber &right) {
	BigNumber result;
	long long ost = 0;
	result._number.resize(left._number.size());
	for (int i = (result._number.size() - 1); i >= 0; --i) {
		int current = ost * BASE + left._number[i];
		result._number[i] = current / to_int(right);
		ost = current % to_int(right);
	}
	return BigNumber(ost);
}

BigNumber operator * (BigNumber&left, int &n) {
	BigNumber result;
	result._number.resize(left._number.size());
	int r = 0;
	for (int i = 0; i < result._number.size(); i++) {
		result._number[i] = left._number[i] * n + r;
		r = result._number[i] / BASE;
		result._number[i] -= r*BASE;
	}
	//if (result._number[result._number.size()])
	//	result._number.resize(result._number.size() + 1);
	return result;
}

BigNumber operator / (BigNumber&left, int &n) {
	BigNumber result;
	result._number.resize(left._number.size());
	int ost = 0; 
	for (int i = (result._number.size()-1); i >= 0; --i) {
			int current = ost * BASE + left._number[i];
			ost = current % n;
			result._number[i] = current / n;
	} 
	if (!result._number[result._number.size() - 1] && result._number.size() != 1)
		result._number.resize(result._number.size()-1);
	return result;
}

int operator % (BigNumber &left, int &n) {
	BigNumber result;
	result._number.resize(left._number.size());
	int ost = 0;
	for (int i = (result._number.size() - 1); i >= 0; --i) {
		int current = ost * BASE + left._number[i];
		result._number[i] = current / n;
		ost = current % n;
	}
	return ost;
}


BigNumber BigNumber::Karatsuba_mul(BigNumber& left, BigNumber& right) {
	auto len = max(left._number.size(), right._number.size());
	if (len < MIN_FOR_KARATSUBA) {
		return left*right;
	}
	BigNumber result;
	result._number.resize(len*2+1);
	auto k = len/2;
	BigNumber left_1, left_2;
	left_1._number.resize((len + 1) / 2);
	for (size_t i = 0; i < (len + 1)/2; ++i) {
		left_1._number[i] = left._number[i];
	}
	left_2._number.resize((len + 1) / 2);
	for (size_t i = 0; i<len/2; ++i) {
		left_2._number[i] = left._number[i + len / 2 + 1];
	}
	left_2.remove_leading_zeroes();
	BigNumber right_1, right_2;
	right_1._number.resize((len + 1) / 2);
	for (size_t i = 0; i < (len + 1) / 2; ++i) {
		right_1._number[i] = right._number[i];
	}
	right_2._number.resize((len + 1) / 2);
	for (size_t i = 0; i < len / 2; ++i) {
		right_2._number[i] = right._number[i + len / 2 + 1];
	}
	right_2.remove_leading_zeroes();
	BigNumber Num_1 = Karatsuba_mul(left_1, right_1);
	BigNumber Num_2 = Karatsuba_mul(left_2, right_2);
	BigNumber Num_3 = Karatsuba_mul(left_2+left_1, right_1 + right_2);
	long long a = pow(10, len);
	long long b = pow(10, len/2);
	result = Num_1*BigNumber(a) + (Num_3 - Num_1 - Num_2)*BigNumber(b) + Num_2;
	return result;
}
 
bool BigNumber::odd() {
	if (this->_number.size() == 0)
		return false;
	return this->_number[0] & 1;
}

bool BigNumber::even() {
	return !this->odd();
}

BigNumber BigNumber::pow_(BigNumber &left) {
	BigNumber a(*this), result(1);
	while (left != 0) {
		if (left.odd()) result *= a;
		a *= a;
		int b = 2;
		left /= b;
	}
	return result;
}

int to_int(BigNumber & number) {
	int num = 0;
	for (auto i = number._number.size(); i >= 1; --i) {
		num += number._number[i-1] * pow(10,i-1);
	}
	return num;
}

int main() {
	BigNumber b("123456789129128818");
	BigNumber c("12345");
	BigNumber d("12345");
	BigNumber f("1000");
	BigNumber h("1000");
	BigNumber e;
	int a = 2;
	cout << c.pow_(h) << endl;
	cout << f*d << endl;
	system("pause");
	return 0;
}
