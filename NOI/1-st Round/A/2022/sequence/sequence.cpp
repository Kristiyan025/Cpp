#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const short maxN = 162 + 1;
short sqr[maxN];
const vector<short> cyc = { 4, 16, 37, 58, 89, 145, 42, 20 };
const unordered_set<short> cyc1(cyc.begin(), cyc.end());

inline char sq(char a)
{ return a * a; }

int nxt(int a)
{
	static int res; res = 0;
	while(a)
	{
		res += sq(a % 10);
		a /= 10;
	}
	return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	for(int i = 0, j; i < maxN; i++)
		sqr[i] = nxt(i);
	int t, a, v, n, cnt;
	cin >>t;
	while(t--)
	{
		cin >>a >>v >>n;
		cnt = 0;
		while(n && a >= maxN)
		{
			cnt += v == a;
			n--;
			a = nxt(a);
		}
		if(v >= maxN)
			cout <<cnt <<"\n";
		else
		{
			while(n && a != 1 && !cyc1.count(a))
				n--,
				cnt += v == a,
				a = sqr[a];
			if(n == 0)
				cout <<cnt <<"\n";
			else if(a == 1)
				cout <<(v == 1 ? cnt + n : cnt) <<"\n";
			else if(v == 1)
				cout <<cnt <<"\n";
			else if(!cyc1.count(v))
				cout <<cnt <<"\n";
			else
			{
				while(n && a != v)
					n--,
					a = sqr[a];
				cout <<cnt + 1 + (--n) / cyc.size() <<"\n";
			}
		}
	}
}
