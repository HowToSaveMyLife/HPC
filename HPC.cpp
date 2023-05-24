# include <iostream>
# include <vector>
# include <string>
# include "HP_complex.h"
# include <vld.h>
using namespace std;

int main() {
	//测试用例，不支持的d = a + b + c类似的计算，会造成内存泄漏，仅能c = a + b
	string s1, s2, s3, s4;
	s1 = "54861";
	s2 = "-456218";
	s3 = "77991";
	s4 = "-4611";
	HP_int a_int, b_int, c_int;
	a_int = s1;
	b_int = s3;
	c_int = a_int + b_int;
	c_int.out();
	cout << endl;

	HP_fraction a_frac, b_frac, c_frac;
	a_frac.in(s1, s2);
	b_frac.in(s2, s4);
	c_frac = a_frac * b_frac;
	c_frac.out();
	cout << endl;
	c_frac.decimal_out(6);
	cout << endl;

	HP_complex a_comp, b_comp, c_comp;
	a_comp.in(s1, s2, s3, s4);
	b_comp.in(s3, s4, s1, s2);
	c_comp = a_comp - b_comp;
	c_comp.out();
	cout << endl;
	c_comp.decimal_out(5);
	cout << endl;

	a_int.free();
	b_int.free();
	c_int.free();
	a_frac.free();
	b_frac.free();
	c_frac.free();
	a_comp.free();
	b_comp.free();
	c_comp.free();
	return 0;
}