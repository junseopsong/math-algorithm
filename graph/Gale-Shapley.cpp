/*
Stable matching problem - Gale-Shapley algorithm
https://www.acmicpc.net/problem/12022
*/

#include <bits/stdc++.h>
using namespace std;
#define M 1000

int n, wp[M][M], mw[M], wm[M];
queue<int> mp[M], q;

int main()
{
	int i, j, t;
	scanf("%d", &n);

	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			scanf("%d", &t);
			mp[i].push(t - 1);
		}
		q.push(i);
		mw[i] = -1;
	}

	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			scanf("%d", &t);
			wp[i][t - 1] = j;
		}
		wm[i] = -1;
	}

	while (!q.empty())
	{
		i = q.front(); q.pop();
		j = mp[i].front(); mp[i].pop();
		if (wm[j] == -1)
		{
			mw[i] = j;
			wm[j] = i;
		}
		else
		{
			if (wp[j][i] < wp[j][wm[j]])
			{
				q.push(wm[j]);
				mw[i] = j;
				wm[j] = i;
			}
			else
			{
				q.push(i);
			}
		}
	}

	for (i = 0; i < n; ++i) printf("M%d - W%d\n", i + 1, mw[i] + 1);
	return 0;
}