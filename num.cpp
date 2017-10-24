#include<iostream>
#include<string>
#include<cmath>
static const int BASE = 10;

using namespace std;

class Number {
public:
	unsigned long int size, Maxsize;
	int *Coef;
	Number();
	Number(unsigned long MAXLEN);
	Number(const Number& num);
	~Number();

	void zero();

	Number& operator=(const Number& num);
	operator long();
};

Number::Number() {
	Maxsize = size = 0;
	Coef = NULL;
}

Number::Number(unsigned long MAXLEN) {
	Coef = new int[MAXLEN];
	Maxsize = MAXLEN;
	size = 0;
}

Number::Number(const Number& num) {
	Maxsize = num.Maxsize;
	size = num.size;
	Coef = new int[Maxsize];
	for (unsigned long i = 0; i < Maxsize; i++)
		Coef[i] = num.Coef[i];

}

Number::~Number() {
	delete Coef;
}

void Number::zero() {
	for (unsigned int i = 0; i < Maxsize; i++)
		Coef[i] = 0;
	size = 1; 
}

Number::operator long() {
	long tmp = 0;
	for (unsigned short i = 0; i < size; i++)
		tmp += Coef[i] * (long)pow(BASE, i);
	return tmp;
}

inline Number&Number:: operator= (const Number &Num) {
	int *num = Num.Coef;
	if (this == &Num) return *this;
	if (Maxsize < Num.size) {
		if (Coef) delete Coef;
		Coef = new int[Num.size];
		Maxsize = size = Num.size;
	}else size = Num.size;
	for (unsigned long i = 0; i < size; i++)
		Coef[i] = num[i];
	return *this;
}

void Add(const Number&A, const Number&B, Number&C) {
	unsigned long int temp;
	const int *a = A.Coef, *b=B.Coef;
	int *c = C.Coef, carry = 0;
	if (A.size < B.size) {
		Add(B, A, C);
		return;
	}
	for (unsigned int i = 0; i < B.size; i++) {
		temp = a[i] + b[i] + carry;
		if (temp >= BASE) {
			c[i] = temp - BASE;
			carry = 1;
		}
		else {
			c[i] = temp;
			carry = 0;
		}
	}
	for (unsigned int i = 0; i < A.size; i++) {
		temp = a[i] + carry;
		if (temp >= BASE) {
			c[i] = temp - BASE;
			carry = 1;
		}
		else {
			c[i] = temp;
			carry = 0;
		}
		if (carry) {
			c[i] = carry;
			C.size = A.size + 1;
		}
		else C.size = A.size;
	}
}

int no_of_errors;
double error(const char*s) {
	cerr << "Error:" << s << "\n";
	no_of_errors++;
	return 1;
}

int Sub(const Number&A, const Number&B, Number&C) {
	unsigned long int temp;
	const int *a = A.Coef, *b = B.Coef;
	int *c = C.Coef, carry = 0;
	if (A.size < B.size) error("Big submision : size error");
	for (unsigned int i = 0; i<B.size; i++) {
		temp = a[i] - b[i] + carry;
		if (temp < 0) {
			c[i] = temp + BASE;
			carry = -1;
		}
		else {
			c[i] = temp;
			carry = 0;
		}
	}
	for (unsigned int i = 0; i<A.size; i++) {
		temp = a[i] + carry;
		if (temp < 0) {
			c[i] = temp + BASE;
			carry = -1;
		}
		else {
			c[i] = temp;
			carry = 0;
		}
	}
	unsigned int i = A.size - 1;
	while ((i>0) && (c[i] == 0)) i--;
	C.size = i + 1;
	return carry;
}

void Mul(const Number &A, const Number &B, Number &C) {
	unsigned long int i, j, temp, carry;
	const int *a = A.Coef, *b = B.Coef;
	int *c = C.Coef;
	for (i = 0; i <= A.size + B.size; ++i)
		c[i] = 0;
	for (i = 0; i = A.size; ++i) {
		carry = 0;
		for (j = 0; j < B.size; ++j) {
			temp = a[i] * b[j] + c[i + j] + carry;
			carry = temp / BASE;
			c[i + j] = temp - carry*BASE;
		}
		c[i + j] = carry;
	}
	i = A.size + B.size - 1;
	if (c[i] == 0) i--;
	C.size = i + 1;
}

void Div(const Number&A, const int B, Number &Q, int&R) {
	unsigned long int i, temp;
	int r = 0;
	const int *a = A.Coef;
	int *q = Q.Coef;
	for (i = A.size - 1; i >= 0; --i) {
		temp = r*BASE + a[i];
		q[i] = temp / B;
		r = temp - q[i] * B;
	}
	R = r;
	i = A.size - 1;
	while ((i > 0) && (q[i] == 0)) i--;
	Q.size = i + 1;}
