#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int maxN = 1e4 + 1;
short b, n;
string s;
char m[maxN], res[maxN];
short ri;

short divide(int dvs)
{
	memset(res, 0, n * sizeof(res[0]));
	short rem = 0, i = 0; ri = n - 1;
	while(i < n)
	{
		if(i < n && rem < dvs) rem = rem * b + m[i++];
		while(i < n && rem < dvs) rem = rem * b + m[i++], res[ri--] = 0;
		res[ri--] = rem / dvs;
		rem %= dvs;
	}
	if(!res[(ri = n) - 1]) ri--;
	return rem;
}

void add()
{
	short i = 0;
	while(i < ri)
	{
		res[i]++;
		res[i + 1] += res[i] / b;
		res[i++] %= b;
	}
	if(res[ri]) res[ri++]++;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>b;
	for(int t = 0; t < 4; t++)
	{
		cin >>s;
		n = s.length();
		for(int i = n - 1; i >= 0; i--)
			m[i] = '0' <= s[i] && s[i] <= '9' ? s[i] - '0' : s[i] - 'A' + 10;
		if(divide(b - 1))
		{
			cout <<"0\n";
		}
		else
		{
			add();
			cout <<"1";
			for(int i = ri - 1; i >= 0; i--)
				cout <<char(res[i] < 10 ? res[i] + '0' : res[i] - 10 + 'A');
			cout <<"\n";
		}
	}
}
