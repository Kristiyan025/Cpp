#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int maxN = 1e6 + 1;
int n, nn, si, sj;
int lp[maxN], cnt[maxN];
vector<int> pr, ord[8];
void lin_sieve()
{
	pr.reserve(78498);
	for(int i = 2, j, ni; i <= nn; i++)
	{
		if(!lp[i])
		{
			lp[i] = i;
			cnt[i] = 1;
			pr.emplace_back(i);
		}
		ord[cnt[i]].emplace_back(i);
		for(j = 0; j < pr.size() && pr[j] <= lp[i] && (ni = pr[j] * i) <= nn; j++)
		{
			lp[ni] = pr[j];
			cnt[ni] = cnt[i] + (lp[i] != pr[j]);
		}
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >>n >>si >>sj;
    nn = n * n;
    lin_sieve();
    si = --si * n + --sj - 1;
    int i = 1;
    while(si >= ord[i].size()) si -= ord[i++].size();
    cout <<ord[i][si] <<endl;
}
