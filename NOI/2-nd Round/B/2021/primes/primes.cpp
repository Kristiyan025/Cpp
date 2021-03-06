#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int prCnt = 78498;
const int maxN = 1e6 + 1;
const int S = 1e4;
int a, b;
char notPrime[S];
int pr[prCnt + 1] = {2, 3};
const int incSz = 2;
const int inc[incSz] = {4, 2};
int prSz = 2;
int bBnd;
int ai;

void seg_sieve()
{
	bBnd = b + (S - b % S) % S + 1;
	int t = 0, i;
	int bnd = min(S, b + 1);
	for(i = 5; i < bnd; i += inc[t])
	{
		if(!notPrime[i])
		{
			pr[prSz++] = i;
			for(int j = i * i; j < bnd; j += i)
				notPrime[j] = 1;
		}
		t = ++t % incSz;
	}

	int en = S << 1, p;
	for(int st = S; en < bBnd; st += S)
	{
		memset(notPrime, 0, sizeof(notPrime));
		for(int id = 2, p = pr[id]; p * p < en; id++)
		{
			p = pr[id];
			for(int j = (p - st % p) % p; j < S; j += p)
				notPrime[j] = 1;
		}
		for(i -= S; i < S; i += inc[t])
		{
			if(!notPrime[i])
				pr[prSz++] = st + i;
			t = ++t % incSz;
		}
		en += S;
	}
	while(pr[prSz - 1] > b) prSz--;
}

int len[maxN];
int pos[maxN];
void chains()
{
	ai = lower_bound(pr, pr + prSz, a) - pr;
	if(ai == prSz)
	{
		cout <<"no prime\n";
		return;
	}
	int i, j, sum;
	for(i = prSz - 1; i >= 0; i--)
	{
		sum = 0;
		for(j = i; j < prSz; j++) //max sqrt(maxN) iteration for each i
		{
			sum += pr[j];
			if(sum >= maxN) break;
			len[sum] = j - i + 1;
			pos[sum] = i;
		}
	}
	int mx = 0, ans;
	for(i = ai; i < prSz; i++)
	{
		if(mx < len[pr[i]])
		{
			mx = len[pr[i]];
			ans = pr[i];
		}
	}
	cout <<ans <<" " <<mx <<endl;
	for(int i = pos[ans]; i < mx + pos[ans]; i++)
		cout <<pr[i] <<" ";
	cout <<endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>a >>b;
	seg_sieve();
	chains();
}
