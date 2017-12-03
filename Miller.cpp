#include "class.h"
#include <algorithm>
#include <cmath>

using namespace std;

bool even(BigNumber &left)
{
	BigNumber k("2");
	return (left % k) == 0;
}

BigNumber gcd(BigNumber &left, BigNumber &right)
{
	return (left == 0) ? right : gcd(right % left, left);
}

void transform_num(BigNumber &left, BigNumber &number, BigNumber &pow_of_two)
{
	BigNumber result = 0;
	while (even(left))
	{
		result+=1;
		left/=BigNumber(2);
	}
	pow_of_two = result;
	number = left;
}

bool Miller_Rabin(BigNumber &left, BigNumber &right) {
	if (left == 2)
		return true;
	if (left < 2 || even(left))
		return false;
	if (right < 2)
		right = 2;
	for (BigNumber g; (g = gcd(left, right)) != 1; right += 1)
		if (left > g)
			return false;
	BigNumber one("1");
	BigNumber left_d = left-one;
	BigNumber number, pow_of_two;
	transform_num(left, number, pow_of_two);
	BigNumber res = right.pow_(number)%left;
	if (res == left_d)
		return true;
	if (res == 1)
		return true;
	else
	return false;
}

int main() {
		BigNumber t("221");
		BigNumber h("137");
		cout << Miller_Rabin(t, h) << endl;
		system("pause");
		return 0;
}