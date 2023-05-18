# include <iostream>
# include <vector>
# include <string>
using namespace std;

struct HP_digit {
	HP_digit* high_digit;
	HP_digit* low_digit;
	unsigned short int digit;
	HP_digit() { high_digit = NULL; low_digit = NULL; digit = 0; };
};

class HP_int {
private:
	int lenth;
	bool sign;
	HP_digit* highest_digit;
	HP_digit* lowest_digit;
	HP_digit* hot_digit;
public:
	HP_int();
	void operator=(string& s);
	void operator=(HP_int A);
	void free();
	void out();
	void del_zeros();
	HP_int add(HP_int& A);
	HP_int minus(HP_int& minus);
	HP_int operator+(HP_int& A);
};

HP_int::HP_int() {
	lenth = 0;
	sign = true;
	highest_digit = NULL;
	lowest_digit = NULL;
	hot_digit = NULL;
}

void HP_int::operator=(string& s) {
	if (lowest_digit != NULL) free();
	
	lenth = s.size();
	if (lowest_digit == NULL) {
		lowest_digit = new HP_digit;
		highest_digit = lowest_digit;
		lowest_digit->digit = s[lenth - 1] - 48;
	}
	for (int i = 1; i < lenth; i++) {
		highest_digit->high_digit = new HP_digit;
		highest_digit->high_digit->low_digit = highest_digit;
		highest_digit = highest_digit->high_digit;
		highest_digit->digit = s[lenth - 1 - i] - 48;
	}
	hot_digit = lowest_digit;
}

void HP_int::operator=(HP_int A) {
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

void HP_int::free() {
	while (lenth > 0 && lowest_digit != NULL) {
		highest_digit = highest_digit->low_digit;
		if (highest_digit != NULL) delete highest_digit->high_digit;
		else delete lowest_digit, lowest_digit = NULL, hot_digit = NULL;
		lenth -= 1;
	}
};

void HP_int::out() {
	hot_digit = highest_digit;
	for (int i = 0; i < lenth; i++) {
		cout << hot_digit->digit;
		hot_digit = hot_digit->low_digit;
	}
	hot_digit = lowest_digit;
}

void HP_int::del_zeros() {
	if (highest_digit->digit = 0) {
		hot_digit = highest_digit->low_digit;
		delete highest_digit;
		highest_digit= hot_digit;
		del_zeros();
	}
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
}

HP_int HP_int::operator+(HP_int& A) {
	HP_int ans;
	if (sign == A.sign) {							//同负 
		ans = add(A);
		ans.sign = sign;
	}
	else if (this->sign == true && A.sign == false) {					//左正 右负 
		bigger = *this;
		smaller = A;
		smaller.sign = true;
		ans = (bigger - smaller);
	}
	else {																//左负 右正 
		bigger = *this;
		smaller = A;
		bigger.sign = true;
		ans = (smaller - bigger);
	}
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