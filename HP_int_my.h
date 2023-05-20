# include <iostream>
# include <vector>
# include <string>
using namespace std;

//高精整形的一位
struct HP_digit {
	HP_digit* high_digit;
	HP_digit* low_digit;
	unsigned short int digit;
	HP_digit() { high_digit = NULL; low_digit = NULL; digit = 0; };
};

//一个高精整形，有长度、符号、最高位、最低位地址
class HP_int {
private:
	int lenth;
	bool sign;
	HP_digit* highest_digit;
	HP_digit* lowest_digit;
	HP_digit* hot_digit;	//便于实现各种操作的指针
public:
	HP_int();							//构造函数
	~HP_int();
	void operator=(string& s);			//用字符串为高精整形赋值
	void copy(HP_int A);				//拷贝一份，数据另存一份
	void operator=(HP_int A);			//仅赋同样的指针
	void free();						//释放所有的HP_digit
	void out();							//输出高精整形
	void del_zeros();					//删除高位的零
	bool operator>(HP_int& A);			//高精整形的比较
	bool operator<(HP_int& A);
	bool operator==(HP_int& A);
	bool operator!=(HP_int& A);
	HP_int add(HP_int& A);				//add与minus只实现数值上的加减，不考虑符号，辅助完成高精整形的+-
	HP_int minus(HP_int& minus);
	HP_int operator+(HP_int& A);		//高精整形+
	HP_int operator-(HP_int& A);		//高精整形-
	HP_int operator*(HP_int& A);		//高精整形*
	HP_int operator/(HP_int& A);		//高精整形/
};

HP_int::HP_int() {
	lenth = 0;
	sign = true;
	highest_digit = NULL;
	lowest_digit = NULL;
	hot_digit = NULL;
}

HP_int::~HP_int() {
	
}

void HP_int::operator=(string& s) {				//待完善
	if (lowest_digit != NULL) free();


	if (s[0] == '-') {
		sign = false;
		lenth = s.size() - 1;
	}
	else {
		sign = true;
		lenth = s.size();
	}
	lowest_digit = new HP_digit;
	highest_digit = lowest_digit;
	lowest_digit->digit = s[lenth - sign] - 48;

	for (int i = 1; i < lenth; i++) {
		highest_digit->high_digit = new HP_digit;
		highest_digit->high_digit->low_digit = highest_digit;
		highest_digit = highest_digit->high_digit;
		highest_digit->digit = s[lenth - sign - i] - 48;
	}
	hot_digit = lowest_digit;
	del_zeros();
}

void HP_int::copy(HP_int A) {
	free();
	lenth = A.lenth;
	sign = A.sign;

	lowest_digit = new HP_digit;
	highest_digit = lowest_digit;
	hot_digit = lowest_digit;
	lowest_digit->digit = A.lowest_digit->digit;

	A.hot_digit = A.lowest_digit;
	for (int i = 1; i < lenth; i++) {
		A.hot_digit = A.hot_digit->high_digit;

		highest_digit->high_digit = new HP_digit;
		highest_digit->high_digit->low_digit = highest_digit;
		highest_digit = highest_digit->high_digit;
		highest_digit->digit = A.hot_digit->digit;
	}
	A.hot_digit = A.lowest_digit;
}

void HP_int::operator=(HP_int A) {
	free();
	lenth = A.lenth;
	sign = A.sign;
	hot_digit = A.hot_digit;
	highest_digit = A.highest_digit;
	lowest_digit = A.lowest_digit;
}

void HP_int::free() {
	sign = false;
	while (lenth > 0 && lowest_digit != NULL) {
		highest_digit = highest_digit->low_digit;
		if (highest_digit != NULL) delete highest_digit->high_digit;
		else delete lowest_digit, lowest_digit = NULL, hot_digit = NULL;
		lenth -= 1;
	}
};

void HP_int::out() {
	if (!sign)	cout << '-';
	hot_digit = highest_digit;
	for (int i = 0; i < lenth; i++) {
		cout << hot_digit->digit;
		hot_digit = hot_digit->low_digit;
	}
	hot_digit = lowest_digit;
}

void HP_int::del_zeros() {
	if (highest_digit->digit == 0 && highest_digit->low_digit != NULL) {
		hot_digit = highest_digit->low_digit;
		delete highest_digit;
		highest_digit = hot_digit;
		highest_digit->high_digit = NULL;
		lenth--;
		del_zeros();
	}
}

bool HP_int::operator>(HP_int& A) {
	if (sign != A.sign) {
		return sign;
	}
	else {
		if (lenth > A.lenth) {
			return sign;
		}
		else if (lenth < A.lenth) {
			return !sign;
		}
		else {
			hot_digit = highest_digit;
			A.hot_digit = A.highest_digit;
			if (hot_digit->digit > A.hot_digit->digit) {
				return sign;
			}
			else if (hot_digit->digit < A.hot_digit->digit) {
				return !sign;
			}

			for (int i = 1; i < lenth; i++) {
				hot_digit = hot_digit->low_digit;
				A.hot_digit = A.hot_digit->low_digit;
				if (hot_digit->digit > A.hot_digit->digit) {
					return sign;
				}
				else if (hot_digit->digit < A.hot_digit->digit) {
					return !sign;
				}
			}
			return false;
		}
	}
}

bool HP_int::operator<(HP_int& A) {
	return A > *this;
}

bool HP_int::operator==(HP_int& A) {
	if (lenth != A.lenth || sign != A.sign) {
		return false;
	}
	else {
		hot_digit = highest_digit;
		A.hot_digit = A.highest_digit;
		if (hot_digit->digit != A.hot_digit->digit) {
			return false;
		}
		for (int i = 1; i < lenth; i++) {
			hot_digit = hot_digit->low_digit;
			A.hot_digit = A.hot_digit->low_digit;
			if (hot_digit->digit != A.hot_digit->digit) {
				return false;
			}
		}
		return true;
	}
}

bool HP_int::operator!=(HP_int& A) {
	return !(*this == A);
}

HP_int HP_int::add(HP_int& A) {
	hot_digit = lowest_digit;
	A.hot_digit = A.lowest_digit;
	HP_int result;
	result.sign = true;
	result.lenth = max(A.lenth, lenth);
	result.lowest_digit = new HP_digit;
	result.highest_digit = result.lowest_digit;
	result.hot_digit = result.lowest_digit;
	result.hot_digit->digit = hot_digit->digit + A.hot_digit->digit;
	
	for (int i = 1; i < result.lenth; i++) {
		result.highest_digit = new HP_digit;
		result.highest_digit->low_digit = result.hot_digit;
		result.hot_digit->high_digit = result.highest_digit;
		result.highest_digit->digit = result.hot_digit->digit / 10;
		result.hot_digit->digit = result.hot_digit->digit % 10;
		result.hot_digit = result.highest_digit;

		if (hot_digit->high_digit != NULL) {
			hot_digit = hot_digit->high_digit;
			result.hot_digit->digit += hot_digit->digit;
		}
		if (A.hot_digit->high_digit != NULL) {
			A.hot_digit = A.hot_digit->high_digit;
			result.hot_digit->digit += A.hot_digit->digit;
		}
	}

	if (result.hot_digit->digit / 10) {
		result.highest_digit = new HP_digit;
		result.highest_digit->low_digit = result.hot_digit;
		result.hot_digit->high_digit = result.highest_digit;
		result.highest_digit->digit = result.hot_digit->digit / 10;
		result.hot_digit->digit = result.hot_digit->digit % 10;
		result.hot_digit = result.highest_digit;
		result.lenth += 1;
	}

	A.hot_digit = A.lowest_digit;
	hot_digit = lowest_digit;
	result.hot_digit = result.lowest_digit;
	return result;
}

HP_int HP_int::minus(HP_int& A) {
	hot_digit = lowest_digit;
	A.hot_digit = A.lowest_digit;
	HP_int result;
	result.sign = true;
	result.lenth = lenth;
	result.lowest_digit = new HP_digit;
	result.highest_digit = result.lowest_digit;
	result.hot_digit = result.lowest_digit;

	unsigned short int borrow = 0;

	result.hot_digit->digit = 10 * !(hot_digit->digit - borrow >= A.hot_digit->digit) + hot_digit->digit - A.hot_digit->digit - borrow;
	borrow = !(hot_digit->digit - borrow >= A.hot_digit->digit);

	for (int i = 1; i < result.lenth; i++) {
		result.highest_digit = new HP_digit;
		result.highest_digit->low_digit = result.hot_digit;
		result.hot_digit->high_digit = result.highest_digit;
		hot_digit = hot_digit->high_digit;
		result.hot_digit = result.highest_digit;

		if (A.hot_digit->high_digit != NULL) {
			A.hot_digit = A.hot_digit->high_digit;
			result.hot_digit->digit = 10 * !(hot_digit->digit - borrow >= A.hot_digit->digit) + hot_digit->digit - A.hot_digit->digit - borrow;
			borrow = !(hot_digit->digit - borrow >= A.hot_digit->digit);
		}
		else {
			result.hot_digit->digit = 10 * !(hot_digit->digit - borrow >= 0) + hot_digit->digit - borrow;
			borrow = !(hot_digit->digit - borrow >= 0);
		}
	}

	result.del_zeros();
	hot_digit = lowest_digit;
	A.hot_digit = A.lowest_digit;
	result.hot_digit = result.lowest_digit;
	return result;
}

HP_int HP_int::operator+(HP_int& A) {
	HP_int ans;
	if (sign == A.sign) {
		ans = add(A);
		ans.sign = sign;
	}
	else {
		A.sign = sign;

		bool x = *this > A;
		if (*this == A) {
			ans.lenth = 1;
			ans.lowest_digit = new HP_digit;
			ans.highest_digit = ans.lowest_digit;
			ans.hot_digit = ans.lowest_digit;
			ans.sign = true;
		}
		else if (sign ^ x) {
			ans = A.minus(*this);
			ans.sign = x;
		}
		else {
			ans = minus(A);
			ans.sign = x;
		}
		A.sign = !sign;
	}
	return ans;
}

HP_int HP_int::operator-(HP_int& A) {
	HP_int ans;
	if (sign != A.sign) {
		ans = add(A);
		ans.sign = sign;
	}
	else {
		bool x = *this > A;
		if (*this == A) {
			ans.lenth = 1;
			ans.lowest_digit = new HP_digit;
			ans.highest_digit = ans.lowest_digit;
			ans.hot_digit = ans.lowest_digit;
			ans.sign = true;
		}
		else if (sign ^ x) {
			ans = A.minus(*this);
			ans.sign = x;
		}
		else {
			ans = minus(A);
			ans.sign = x;
		}
	}
	return ans;
}

HP_int HP_int::operator*(HP_int& A) {
	if (lenth < A.lenth) {
		return A * *this;
	}
	else {
		HP_int result;
		result.lowest_digit = new HP_digit;
		result.highest_digit = result.lowest_digit;
		result.hot_digit = result.lowest_digit;
		result.hot_digit->digit = 0;
		result.sign = (sign == A.sign) ? true : false;
		result.lenth = 1;

		HP_digit* hot = result.lowest_digit;
		A.hot_digit = A.lowest_digit;
		for (int i = 0; A.hot_digit != NULL && i < A.lenth; hot = hot->high_digit, A.hot_digit = A.hot_digit->high_digit, i++) {
			hot_digit = lowest_digit;
			result.hot_digit = hot;
			for (int j = 0; hot_digit != NULL && j < lenth; j++, hot_digit = hot_digit->high_digit) {
				result.hot_digit->digit += hot_digit->digit * A.hot_digit->digit;
				if (result.hot_digit->high_digit == NULL) {
					result.highest_digit = new HP_digit;
					result.highest_digit->low_digit = result.hot_digit;
					result.highest_digit->digit = 0;
					result.hot_digit->high_digit = result.highest_digit;
					result.lenth++;
				}
				result.hot_digit = result.hot_digit->high_digit;
				result.hot_digit->digit += result.hot_digit->low_digit->digit / 10;
				result.hot_digit->low_digit->digit = result.hot_digit->low_digit->digit % 10;
			}
		}

		result.del_zeros();
		result.hot_digit = result.lowest_digit;
		hot_digit = lowest_digit;
		A.hot_digit = A.lowest_digit;
		return result;
	}
}

HP_int HP_int::operator/(HP_int& A) {
	HP_int ans;
	HP_int dividend;
	dividend.copy(*this);
	bool A_sign = A.sign;
	dividend.sign = true;
	A.sign = true;

	if (dividend < A) {
		string a = "0";
		ans = a;
	}
	else {
		ans.sign = (sign == A_sign) ? true : false;
		ans.lowest_digit = new HP_digit;
		ans.highest_digit = ans.lowest_digit;
		ans.hot_digit = ans.lowest_digit;
		ans.lenth = lenth - A.lenth + 1;

		for (int j = lenth - A.lenth + 1; j > 0; j--) {
			string q(j, '0');
			q[0] = 9 + 48;
			HP_int quotient;
			quotient = q;
			HP_int dividend_A;
			for (; q[0] - 48 > 0; q[0]--, quotient.highest_digit->digit--) {		//此部分待优化（用减法代替乘法
				dividend_A = quotient * A;
				if (!(dividend_A > dividend)) {
					dividend = dividend - dividend_A;
					dividend_A.free();
					break;
				}
			}
			ans.hot_digit->digit = q[0] - 48;
			ans.lowest_digit = new HP_digit;
			ans.hot_digit->low_digit = ans.lowest_digit;
			ans.lowest_digit->high_digit = ans.hot_digit;
			ans.hot_digit = ans.lowest_digit;
			quotient.free();
		}
		ans.lowest_digit = ans.lowest_digit->high_digit;
		delete ans.hot_digit;
		ans.hot_digit = ans.lowest_digit;
		ans.hot_digit->low_digit = NULL;
	}
	dividend.free();
	A.sign = A_sign;
	return ans;
}
/*

class HP_int
{
private:
	vector<unsigned short int> data;
	int len;
public:
	HP_int();
	HP_int(int lenth);
	void in(string s);
	void out();
	void del_zero();
	HP_int operator+(HP_int a);
	HP_int operator-(HP_int a);
};

//构造函数
HP_int::HP_int() {
	len = 0;
}

HP_int::HP_int(int lenth) {
	len = lenth;
	data.reserve(len);
	for (int i = 0; i < len; i++) {
		data.push_back(0);
	}
}

//以string形式输入一个高精整型
void HP_int::in(string s) {
	len = s.size();
	data.reserve(len);
	for (int i = 0; i < len; i++) {
		data.push_back(s[len - i - 1] - 48);
	}

	this->del_zero();
}

//输出
void HP_int::out() {
	for (int i = len-1; i >=0; i--) {
		cout << data[i];
	}
}

//删除无用的高位的0
void HP_int::del_zero() {
	while (len > 1 && data[len - 1] == 0) {
		data.pop_back();
		len--;
	}
}

//+
HP_int HP_int::operator+(HP_int a) {
	int lenth = max(a.len, len) + 1;
	HP_int c(lenth);
	unsigned short int x, y;
	for (int i = 0; i < lenth; i++) {
		if (a.len > i) x = a.data[i];
		else x = 0;
		if (len > i) y = data[i];
		else y = 0;
		c.data[i] = x + y + c.data[i];

		if (c.data[i] > 9)
			c.data[i] -= 10, c.data[i + 1]++;
	}
	c.del_zero();
	return c;
}

//-
HP_int HP_int::operator-(HP_int a) {

}

*/