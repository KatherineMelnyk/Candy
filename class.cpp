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

const BigNumber operator + ( BigNumber &left, const BigNumber &right) {
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

int main() {
	BigNumber BG("123456789");
	BigNumber BN("123456789");
	cout << BG << endl;
	cout << BG + BN << endl;
	system("pause");
	return 0;
}