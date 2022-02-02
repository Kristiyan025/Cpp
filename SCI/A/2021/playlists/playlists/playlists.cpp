#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
#include "playlists.h"
using namespace std;

#define forVBit(m, msk, x) for(int m = msk, x = m & -m; m; m -= x, x = m & -m)
int N, K, S, cnt, fr;
double P;

bool next_combination(vector<int>& a, int n) {
    int k = (int)a.size();
    for (int i = k - 1; i >= 0; i--) {
        if (a[i] < n - k + i + 1) {
            a[i]++;
            for (int j = i + 1; j < k; j++)
                a[j] = a[j - 1] + 1;
            return true;
        }
    }
    return false;
}

vector<vector<int>> makePlaylists(int n, int k, int s, double p)
{
	N = n; K = k; S = s; P = p;
	vector<vector<int>> res(n);
	for(cnt = 1; s < n; s *= S, cnt++);
	s = S;
	fr = ceil(double(k) / cnt);
	cout <<"cnt: " <<cnt <<endl;

	vector<int> cur(cnt);
	for(int i = 0; i < cnt; i++) cur[i] = i + 1;
	for(int i = 0; i < n; i++)
	{
		cout <<"i: " <<i <<" -> ";
		for(int h : cur) cout <<h <<" "; cout <<endl;
		res[i].resize(k);
		for(int j = 0, bnd = fr, t = 0; j < cnt; j++, bnd += fr)
		{
			for(; t < bnd && t < k; t++)
			{
				res[i][t] = cur[i] - 1;
			}
		}
		cout <<"pos trans: " <<next_combination(cur, s) <<endl;
	}
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < k; j++)
			cout <<res[i][j] <<" ";
		cout <<endl;
	}
	return res;
}

int guessPlaylist()
{
	return 0;
}
/*
3 2 3 0.5
18 8 2 0.4
*/
