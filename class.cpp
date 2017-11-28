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
		char old_fill = os.fill('0');
		for (long long i = static_cast <long long>(BN._number.size()) - 1; i >= 0; --i)
			os << std::setw(1) << BN._number[i];
		os.fill(old_fill);
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

BigNumber operator + (BigNumber &left,BigNumber &right) {
	int carry = 0;
	for (size_t i = 0; i < std::max(left._number.size(), right._number.size()); ++i) {
		if (left._number.size() == i)
			left._number.push_back(0);
		left._number[i] += carry + (i < right._number.size() ? right._number[i] : 0);
		carry = left._number[i] >= BASE;
		if (carry != 0)
			left._number[i] -= BASE;
	}
	return left;
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

BigNumber& BigNumber::operator *=(BigNumber value) {
	return *this = (*this * value);
}

BigNumber operator -(BigNumber &left,BigNumber &right) {
	if (left == right) {
		for (size_t i = 0; i < right._number.size(); ++i) {
			left._number[i]=0;
		}
	}
	left.remove_leading_zeroes();
	return left;
	if (left > right) {
		int carry = 0;
		for (size_t i = 0; i < right._number.size(); ++i) {
			left._number[i] -= (carry + (i < right._number.size() ? right._number[i] : 0));
			carry = left._number[i] < 0;
			if (carry != 0)
				left._number[i] += BASE;
		}
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
			long long current = result._number[i + j] + left._number[i] * 1LL * (j < right._number.size() ? right._number[j] : 0) + carry;
			result._number[i + j] = static_cast<int>(current%BASE);
			carry = static_cast<int>(current / BASE);
		}
	}
	result.remove_leading_zeroes();
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
...
}



int main() {
	//BigNumber a("123456789129128818");
	BigNumber b("123456789129128818");
	BigNumber c("12345");
	BigNumber d("12345");
	BigNumber f("1000");
	BigNumber h("1000");
	long long g = 100000000000000;
	BigNumber e;
	int a = 2;
	cout << b / a  << endl;
	cout << d % a << endl;
	cout << c*d << endl;
	/*cout << h / f << endl;*/
	cout << e.Karatsuba_mul(c,d) << endl;
	//cout << a << endl;
	//cout << a + c << endl;
	//cout << b - d << endl;
	//cout << c - d << endl;
	//cout << f*h << endl;
	/*cout << c * d << endl;*/
	cout << BigNumber(g) << endl;
	/*cout << c * BigNumber(g) << endl;*/
	system("pause");
	return 0;
}
