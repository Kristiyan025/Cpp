#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

int a, b;
const int N = 5e7;
const int S = 1e4;
char notPr[S];
int pr[3001134 + 1] = {2};
int prSz = 1;
int cnt = 0;

inline int cbs(int a)
{
	a |= a >> 1;
	a |= a >> 2;
	a |= a >> 4;
	a |= a >> 8;
	a |= a >> 16;
	a++;
	return __builtin_ctz(a);
}

int c, cc, l, r;
bool ok;
void check(int p)
{
	if(a <= p && p <= b)
	{
		c = cbs(p);
		l = p >> (cc = c >> 1);
		r = p & ~(l << cc);
		ok = cbs(r) == cc &&
		     *lower_bound(pr, pr + prSz, l) == l &&
			 *lower_bound(pr, pr + prSz, r) == r;
		if((c & 1) && !ok)
		{
			l = p >> ++cc;
			r = p & ~(l << cc);
			ok |= cbs(r) == cc &&
			      *lower_bound(pr, pr + prSz, l) == l &&
				  *lower_bound(pr, pr + prSz, r) == r;
		}
		cnt += ok;
	}
}

void seg_sieve()
{
	int bnd=  min(S, b + 1);
	for(int i = 3; i < bnd; i += 2)
	{
		if(!notPr[i])
		{
			check(pr[prSz++] = i);
			for(int j = i * i; j < S; j += i << 1)
				notPr[j] = 1;
		}
	}
	for(int st = S, en = S << 1; st < N && st <= b; st += S, en += S)
	{
		memset(notPr, 0, sizeof notPr);
		for(int id = 1, p = pr[id]; id < prSz && p * p <= en; p = pr[++id])
			for(int i = (p - st % p) % p; i < S; i += p)
				notPr[i] = 1;
		for(int i = 1; i < S; i += 2)
			if(!notPr[i])
				check(pr[prSz++] = i + st);
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>a >>b;
    seg_sieve();

    cout <<cnt <<endl;
}
