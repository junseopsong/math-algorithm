#include <cmath>
using namespace std;

int modInverse(int a, int mod)
{
	int m0 = mod, x0 = 0, x1 = 1, t, q;
	if (mod == 1) return 1;
	a %= m0;
	if (a < 0) a += m0;
	while (a > 1)
	{
		t = mod; q = a / mod; mod = a % mod; a = t;
		t = x0; x0 = x1 - q * x0; x1 = t;
	}
	if (x1 < 0) x1 += m0;
	return x1;
}

int gcd(int a, int b)
{
	int t;
	while (b)
	{
		t = a; a = b; b = t % b;
	}
	return abs(a);
}

long long lcm(int a, int b)
{
	return (long long)a / gcd(a, b) * b;
}