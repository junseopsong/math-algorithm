#include <iostream>
using namespace std;


template<int mx_size, typename elem_t>
class SquareMatrix
{
	typedef SquareMatrix<mx_size, elem_t> Mx;

private:
	elem_t m[mx_size][mx_size];

public:
	SquareMatrix()
	{
		int i, j;
		for (i = 0; i < mx_size; ++i)
			for (j = 0; j < mx_size; ++j)
				m[i][j] = 0;
	}

	SquareMatrix(const elem_t _m[][mx_size])
	{
		int i, j;
		for (i = 0; i < mx_size; ++i)
			for (j = 0; j < mx_size; ++j)
				m[i][j] = _m[i][j];
	}

	friend ostream& operator<<(ostream& os, const Mx &a)
	{
		int i, j;
		for (i = 0; i < mx_size; ++i)
		{
			for (j = 0; j < mx_size; ++j) os << a.m[i][j] << ", ";
			os << endl;
		}
		return os;
	}

	Mx& operator+=(const Mx &b)
	{
		int i, j;
		for (i = 0; i < mx_size; ++i)
			for (j = 0; j < mx_size; ++j)
				m[i][j] += b.m[i][j];
		return *this;
	}

	Mx& operator-=(const Mx &b)
	{
		int i, j;
		for (i = 0; i < mx_size; ++i)
			for (j = 0; j < mx_size; ++j)
				m[i][j] -= b.m[i][j];
		return *this;
	}

	Mx operator*(const Mx &b)
	{
		int i, j, k;
		Mx ret;
		for (i = 0; i < mx_size; ++i)
		{
			for (j = 0; j < mx_size; ++j)
			{
				for (k = 0; k < mx_size; ++k) ret.m[i][j] += m[i][k] * b.m[k][j];
			}
		}
		return ret;
	}

	Mx operator+(const Mx &b) { return Mx(m) += b; }

	Mx operator-(const Mx &b) { return Mx(m) -= b; }

	Mx& operator*=(const Mx &b)
	{
		*this = (*this) * b;
		return *this;
	}

	bool operator==(const Mx &b)
	{
		int i, j;
		for (i = 0; i < mx_size; ++i)
		{
			for (j = 0; j < mx_size; ++j)
			{
				if (m[i][j] != b.m[i][j]) return 0;
			}
		}
		return 1;
	}

	bool operator!=(const Mx &b) { return !(*this == b); }

	Mx pow(unsigned int p) // power of matrix
	{
		Mx ret, a(m);
		for (int i = 0; i < mx_size; ++i) ret.m[i][i] = 1;
		while (p)
		{
			if (p & 1) ret *= a;
			a *= a;
			p >>= 1;
		}
		return ret;
	}

	Mx operator^(unsigned int p) { return (*this).pow(p); }
};