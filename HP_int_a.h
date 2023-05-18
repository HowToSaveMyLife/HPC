template <int SIZE>
class HP_int
{
private:
	int a[SIZE], len;

public:
	HP_int()
	{
		len = 1;
		memset(a, 0, sizeof(a));
	}
	void in()
	{
		char s[SIZE];
		scanf("%s", s);
		len = strlen(s);
		for (int i = 0, j = len - 1; i < len; i++, j--)
			a[i] = s[j] - 48;
		while (len > 1 && a[len - 1] == 0)
			len--;
	}
	void out(bool Entr = true)
	{
		for (int i = len - 1; i >= 0; i--)
			putchar(a[i] + '0');
		if (Entr)
			putchar('\n');
	}
	void operator=(char* s)
	{
		len = strlen(s);
		for (int i = 0, j = len - 1; i < len; i++, j--)
			a[i] = s[j] - 48;
		while (len > 1 && a[len - 1] == 0)
			len--;
	}
	void operator=(int x)
	{
		len = 0;
		if (x == 0)
			len = 1, a[0] = 0;
		while (x > 0)
			a[len++] = x % 10, x /= 10;
	}
	void operator=(long long x)
	{
		len = 0;
		if (x == 0)
			len = 1, a[0] = 0;
		while (x > 0)
			a[len++] = x % 10, x /= 10;
	}
	friend bool operator<(HP_int a, HP_int b)
	{
		if (a.len != b.len)
			return a.len < b.len;
		for (int i = a.len - 1; i >= 0; i--)
			if (a.a[i] != b.a[i])
				return a.a[i] < b.a[i];
		return false;
	}
	friend bool operator>(HP_int a, HP_int b)
	{
		return b < a;
	}
	friend bool operator<=(HP_int a, HP_int b)
	{
		return !(a > b);
	}
	friend bool operator>=(HP_int a, HP_int b)
	{
		return !(a < b);
	}
	friend bool operator==(HP_int a, HP_int b)
	{
		return !(a > b && b < a);
	}
	friend bool operator!=(HP_int a, HP_int b)
	{
		return a < b || b < a;
	}
	friend HP_int operator+(HP_int a, HP_int b)
	{
		HP_int c;
		int lenth = max(a.len, b.len) + 1;
		for (int i = 0; i < lenth; i++)
			c.a[i] = a.a[i] + b.a[i];
		for (int i = 0; i < lenth; i++)
		{
			if (c.a[i] > 9)
				c.a[i] -= 10, c.a[i + 1]++;
		}
		while (lenth > 1 && c.a[lenth - 1] == 0)
			lenth--;
		c.len = lenth;
		return c;
	}
	friend HP_int operator-(HP_int a, HP_int b)
	{
		HP_int c;
		if (a < b)
			std::swap(a, b);
		int len = a.len;
		for (int i = 0; i < len; i++)
			c.a[i] = a.a[i] - b.a[i];
		for (int i = 0; i < len; i++)
			if (c.a[i] < 0)
				c.a[i + 1]--, c.a[i] += 10;
		while (len > 1 && c.a[len - 1] == 0)
			len--;
		c.len = len;
		return c;
	}
	friend HP_int operator*(HP_int a, HP_int b)
	{
		HP_int ans;
		int len = a.len + b.len;
		for (int i = 0; i < a.len; i++)
			for (int j = 0; j < b.len; j++)
				ans.a[i + j] += a.a[i] * b.a[j];
		for (int i = 0; i < len; i++)
			if (ans.a[i] > 9)
				ans.a[i + 1] += ans.a[i] / 10, ans.a[i] %= 10;
		while (len > 1 && ans.a[len - 1] == 0)
			len--;
		ans.len = len;
		return ans;
	}
	friend HP_int operator*(HP_int a, int x)
	{
		HP_int ans;
		int len = a.len + 20;
		for (int i = 0; i < len; i++)
			ans.a[i] = a.a[i] * x;
		for (int i = 0; i < len; i++)
			if (ans.a[i] > 9)
				ans.a[i + 1] += ans.a[i] / 10, ans.a[i] %= 10;
		while (ans.a[len - 1] == 0 && len > 1)
			len--;
		ans.len = len;
		return ans;
	}
	friend HP_int operator/(HP_int a, int b)
	{
		HP_int c;
		int d = 0, len = a.len;
		for (int i = len - 1; i >= 0; i--)
			d = d * 10 + a.a[i], c.a[i] = d / b, d = d % b;
		while (len > 1 && c.a[len - 1] == 0)
			len--;
		c.len = len;
		return c;
	}
	friend HP_int operator/(HP_int a, HP_int b)
	{
		HP_int c, d;
		int len = a.len;
		for (int i = len - 1; i >= 0; i--)
		{
			d = d * 10;
			d.a[0] = a.a[i];
			while (d >= b)
				c.a[i]++, d = d - b;
		}
		while (len > 1 && c.a[len - 1] == 0)
			len--;
		c.len = len;
		return c;
	}
	friend int operator%(HP_int a, int b)
	{
		int d = 0, len = a.len;
		for (int i = len - 1; i >= 0; i--)
			d = d * 10 + a.a[i], d = d % b;
		return d;
	}
	friend HP_int operator%(HP_int a, HP_int b)
	{
		HP_int d;
		int len = a.len;
		for (int i = len - 1; i >= 0; i--)
		{
			d = d * 10;
			d.a[0] = a.a[i];
			while (d >= b)
				d = d - b;
		}
		while (len > 1 && d.a[len - 1] == 0)
			len--;
		d.len = len;
		return d;
	}
	friend HP_int gcd(HP_int a, HP_int b)
	{
		HP_int zero;
		zero = 0;
		return b == zero ? a : gcd(b, a % b);
	}
	friend HP_int pow_mod(int a, int n, HP_int m)
	{
		HP_int ret, X;
		if (n == 0)
		{
			ret = 1;
			return ret;
		}
		X = pow_mod(a, n / 2, m);
		ret = (X * X) % m;
		if (n % 2)
			ret = (ret * a) % m;
		return ret;
	}
};