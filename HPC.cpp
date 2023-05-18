# include <iostream>
# include <vector>
# include <string>
using namespace std;

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
};

//构造函数，构造一个为0的高精整形
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

void HP_int::out() {
	for (int i = len - 1; i >= 0; i--) {
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


int main() {
	HP_int a, b;
	string s1 = "999", s2 = "9999";
	a.in(s1);
	b.in(s2);
	HP_int c = a + b;
	HP_int* d = &c;
	d->out();
	int x = true;
	int y = 10;
	cout << x;
	cout << "123";
	return 0;
}