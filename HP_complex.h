# include<string>
# include<iostream>
# include"HP_fraction.h"
using namespace std;

class HP_complex {
private:
	HP_fraction Real;
	HP_fraction Imag;
public:
	HP_complex();																			
	~HP_complex();
	void in(string real_nume, string real_deno, string imag_nume, string imag_deno);		//以string形式输入实部分数的分子、分母，虚部分数的分子分母
	void out();																				//以分数形式输出
	void decimal_out(int num);																//以小数形式输出
	void free();																			//手动释放
	HP_fraction real();																		//获取复数的实部，返回高精分数
	HP_fraction imag();																		//获取复数的虚部，返回高精分数
	HP_complex operator+(HP_complex A);
	HP_complex operator-(HP_complex A);
	HP_complex operator*(HP_complex A);
	HP_complex operator/(HP_complex A);
};

HP_complex::HP_complex() {
	Real.in("0", "1");
	Imag.in("0", "1");
}

HP_complex::~HP_complex() {

}

void HP_complex::in(string real_nume, string real_deno, string imag_nume, string imag_deno) {
	Real.in(real_nume, real_deno);
	Imag.in(imag_nume, imag_deno);
}

void HP_complex::out() {
	Real.out();
	HP_fraction zero;
	zero.in("0", "1");
	if (!(Imag < zero)) cout << '+';
	Imag.out();
	cout << 'j';
	zero.free();
}

void HP_complex::decimal_out(int num) {
	Real.decimal_out(num);
	HP_fraction zero;
	zero.in("0", "1");
	if (!(Imag < zero)) cout << '+';
	Imag.decimal_out(num);
	cout << 'j';
	zero.free();
}

void HP_complex::free() {
	Real.free();
	Imag.free();
}

HP_fraction HP_complex::real() {
	HP_fraction A;
	A.copy(Real);
	return A;
}

HP_fraction HP_complex::imag() {
	HP_fraction A;
	A.copy(Imag);
	return A;
}

HP_complex HP_complex::operator+(HP_complex A) {
	HP_complex ans;
	ans.Real = Real + A.Real;
	ans.Imag = Imag + A.Imag;
	return ans;
};

HP_complex HP_complex::operator-(HP_complex A) {
	HP_complex ans;
	ans.Real = Real - A.Real;
	ans.Imag = Imag - A.Imag;
	return ans;
};

HP_complex HP_complex::operator*(HP_complex A) {
	HP_complex ans;
	HP_fraction ans_real_1, ans_real_2, ans_imag_1, ans_imag_2;
	ans_real_1 = Real * A.Real;
	ans_real_2 = Imag * A.Imag;
	ans_imag_1 = Real * A.Imag;
	ans_imag_2 = Imag * A.Real;

	ans.Real = ans_real_1 - ans_real_2;
	ans.Imag = ans_imag_1 + ans_imag_2;
	ans_real_1.free();
	ans_real_2.free();
	ans_imag_1.free();
	ans_imag_2.free();
	return ans;
};

HP_complex HP_complex::operator/(HP_complex A) {		//实部等于ac+bd/(c^2+d^2)，虚部等于bc-ad/(c^2+d^2),(a+bj)/(c+dj)
	HP_fraction ac, bd, bc, ad, c_2, d_2,c2_d2;
	HP_complex ans;
	ac = Real * A.Real;
	bd = Imag * A.Imag;
	bc = Imag * A.Real;
	ad = Real * A.Imag;
	c_2 = A.Real * A.Real;
	d_2 = A.Imag * A.Imag;
	c2_d2 = c_2 + d_2;
	ans.Real = ac + bd;
	ans.Real = ans.Real / c2_d2;
	ans.Imag = bc - ad;
	ans.Imag = ans.Imag / c2_d2;
	ac.free();
	bd.free();
	bc.free();
	ad.free();
	c_2.free();
	d_2.free();
	c2_d2.free();
	return ans;
}