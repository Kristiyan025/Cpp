#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxN = 1e6 + 1;
int n;
int lp[maxN];
int pr[78498];
int prSz = 0;
int phi[maxN];

void lin_sieve()
{
	phi[1] = 1;
	int i, j, p, f, k;
	for(i = 2; i < maxN; i++)
	{
		if(lp[i] == 0)
		{
			lp[i] = i;
			phi[i] = i - 1;
			pr[prSz++] = i;
		}
        else
        {
            if (lp[i] == lp[i / lp[i]])
                phi[i] = phi[i / lp[i]] * lp[i];
            else
                phi[i] = phi[i / lp[i]] * (lp[i] - 1);
        }
		for(j = 0, p = pr[j]; j < prSz && p <= lp[i] && i * p <= maxN; j++, p = pr[j])
			lp[i * p] = p;
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    lin_sieve();
	cin >>n;
	ll res = 0;
	for(int i = 1; i <= n; i++)
		res += phi[i];
	cout <<res <<endl;
}
