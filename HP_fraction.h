# include<iostream>
# include<string>
# include"HP_int.h"
using namespace std;

class HP_fraction {
private:
	HP_int numerator;
	HP_int denominator;
public:
	HP_fraction();								//分子初始化为0，分母为1
	~HP_fraction();								//析构函数为空，需要用free()手动释放
	void out();									//以分数形式输出
	void decimal_out(int num);					//以小数形式输出
	void in(string nume,string denom);			//用两个string给高精分数的分子、分母赋值，方式同高精整形
	void free();								//手动释放
	void reduction();							//对分数进行约分
	HP_int gcd();								//求最大公约数
	void copy(HP_fraction A);					//高精分数的拷贝，另存
	void operator=(HP_fraction A);				// = 指向同一份内存、数据
	bool operator>(HP_fraction A);				//有符号逻辑运算
	bool operator<(HP_fraction A);
	bool operator==(HP_fraction A);
	bool operator!=(HP_fraction A);
	HP_fraction operator+(HP_fraction A);		//分数四则运算
	HP_fraction operator-(HP_fraction A);
	HP_fraction operator*(HP_fraction A);
	HP_fraction operator/(HP_fraction A);
};

HP_fraction::HP_fraction() {
	numerator = "0";
	denominator = "1";
}

HP_fraction::~HP_fraction() {

}

void HP_fraction::out() {
	numerator.out();
	cout << '/';
	denominator.out();
}

void HP_fraction::decimal_out(int num) {
	HP_int quotient;
	quotient = numerator / denominator;
	quotient.out();
	cout << '.';
	HP_int remainder;
	remainder = denominator * quotient;
	remainder = numerator - remainder;
	remainder.sign = denominator.sign;
	quotient = remainder.decimal(denominator, num);
	quotient.out();
	quotient.free();
	remainder.free();
}

void HP_fraction::in(string nume, string denom) {
	numerator = nume;
	denominator = denom;
	reduction();
}

void HP_fraction::free() {
	numerator.free();
	denominator.free();
}

void HP_fraction::reduction() {
	HP_int temp;
	bool sign;
	temp = "0";
	if (numerator == temp) {
		denominator = "1";
		temp.free();
		return;
	}

	if (numerator.sign == denominator.sign) sign = true;
	else sign = false;

	temp = gcd();
	denominator = denominator / temp;
	numerator = numerator / temp;
	numerator.sign = sign;
	denominator.sign = true;
	temp.free();
}

HP_int HP_fraction::gcd() {			//最大公约数仅正数
	HP_int a, b, temp, zero;
	zero = "0";
	a.copy(numerator);
	a.sign = true;
	b.copy(denominator);
	b.sign = true;
	temp = a % b;
	while (temp != zero) {
		a.copy(b);
		b.copy(temp);
		temp = a % b;
	}
	a.free();
	temp.free();
	zero.free();
	return b;
}

void HP_fraction::copy(HP_fraction A) {
	numerator.copy(A.numerator);
	denominator.copy(A.denominator);
}

void HP_fraction::operator=(HP_fraction A) {
	numerator = A.numerator;
	denominator = A.denominator;
}

bool HP_fraction::operator>(HP_fraction A) {
	HP_int a, b;
	bool ans;
	a = numerator * A.denominator;
	b = denominator * A.numerator;
	if (a > b) ans = true;
	else ans = false;
	a.free();
	b.free();
	return ans;
}

bool HP_fraction::operator<(HP_fraction A) {
	return A > *this;
}

bool HP_fraction::operator==(HP_fraction A) {
	HP_int a, b;
	bool ans;
	a = numerator * A.denominator;
	b = denominator * A.numerator;
	if (a == b) ans = true;
	else ans = false;
	a.free();
	b.free();
	return ans;
}

bool HP_fraction::operator!=(HP_fraction A) {
	return !(*this == A);
}

HP_fraction HP_fraction::operator+(HP_fraction A) {
	HP_fraction ans;
	ans.denominator = A.denominator * denominator;
	HP_int numerator_1, numerator_2;
	numerator_1 = numerator * A.denominator;
	numerator_2 = A.numerator * denominator;
	ans.numerator = numerator_1 + numerator_2;
	numerator_1.free();
	numerator_2.free();
	ans.reduction();
	return ans;
}

HP_fraction HP_fraction::operator-(HP_fraction A) {
	HP_fraction ans;
	ans.denominator = A.denominator * denominator;
	HP_int numerator_1, numerator_2;
	numerator_1 = numerator * A.denominator;
	numerator_2 = A.numerator * denominator;
	ans.numerator = numerator_1 - numerator_2;
	numerator_1.free();
	numerator_2.free();
	ans.reduction();
	return ans;
}

//乘除待优化，先约分，再乘除

HP_fraction HP_fraction::operator*(HP_fraction A) {
	HP_fraction ans;
	ans.denominator = A.denominator * denominator;
	ans.numerator = numerator * A.numerator;
	ans.reduction();
	return ans;
}

HP_fraction HP_fraction::operator/(HP_fraction A) {
	HP_fraction ans;
	ans.denominator = A.numerator * denominator;
	ans.numerator = numerator * A.denominator;
	ans.reduction();
	return ans;
}