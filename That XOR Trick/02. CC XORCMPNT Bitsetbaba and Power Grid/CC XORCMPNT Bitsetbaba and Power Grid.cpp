#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int maxK = 30;
int k, m, x;
int basis[maxK];
int sz;

void addBasis(int msk)
{
	if(!msk) return;
	for(int i = 0; i < k; i++)
	{
		if(msk & 1 << i)
		{
			if(basis[i] == 0)
			{
				basis[i] = msk;
				sz++;
				return;
			}
			msk ^= basis[i];
		}
	}
	if(msk) basis[sz++] = msk;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int t;
	cin >>t;
	while(t--)
	{
		cin >>k >>m;
		memset(basis, 0, sizeof(basis));
		sz = 0;
		while(m--)
		{
			cin >>x;
			addBasis(x);
		}
		cout <<(1 << k - sz) <<"\n";
	}
}
