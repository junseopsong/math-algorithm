#include <vector>
#include <cmath>
using namespace std;

bool isPrime(int n)
{
	int maxK = sqrt((double)n) + 1;
	if (n == 2 || n == 3 || n == 5) return 1;
	if (n < 2 || !(n & 1) || !(n % 3)) return 0;
	for (int k = 6; k <= maxK; k += 6)
	{
		if (n % (k - 1) == 0 || n % (k + 1) == 0) return 0;
	}
	return 1;
}

bool isPrime(long long n)
{
	if (n == 2 || n == 3 || n == 5) return 1;
	if (n < 2 || !(n & 1) || !(n % 3)) return 0;
	for (long long k = 6LL; k <= n / k + 1; k += 6LL)
	{
		if (n % (k - 1) == 0 || n % (k + 1) == 0) return 0;
	}
	return 1;
}

vector<int> generatePrime(int maxLimit)
{
	vector<bool> isPr(maxLimit + 1, 1);
	vector<int> prList;
	int i, j, maxI;

	isPr[0] = isPr[1] = 0;
	if (maxLimit < 2) return prList;

	prList.push_back(2); isPr[2] = 1;
	for (i = 4; i <= maxLimit; i += 2) isPr[i] = 0;

	maxI = sqrt((double)maxLimit + 1);
	for (i = 3; i <= maxI; i += 2)
	{
		if (isPr[i])
		{
			prList.push_back(i);
			for (j = i << 1; j <= maxLimit; j += i) isPr[j] = 0;
		}
	}

	for (; i <= maxLimit; i += 2)
	{
		if (isPr[i]) prList.push_back(i);
	}
	return prList;
}

vector<pair<int, int>> primeFactorization(int n)
{
	vector<pair<int, int>> pe;
	int i, j;
	if (n <= 1) return pe;

	for (i = 2; i <= n; ++i)
	{
		j = 0;
		while (n%i == 0)
		{
			n /= i;
			++j;
		}
		if (j) pe.emplace_back(i, j);
	}
	return pe;
}