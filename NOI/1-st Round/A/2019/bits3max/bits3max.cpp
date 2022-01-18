#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int maxN = 2000;
string s;
int n, a, b;
bool num[maxN];
int rem3 = 0;

bool rec(int pos, int ones)
{
	if(pos == n)
	{
		if(rem3 == 0)
		{
			for(int i = 0; i < n; i++)
				cout <<num[i];
			cout <<endl;
		}
		return rem3 == 0;
	}
	if(ones == 0)
	{
		if(rem3 == 0)
		{
			for(int i = 0; i < pos; i++)
				cout <<num[i];
			for(int i = pos; i < n; i++)
				cout <<0;
			cout <<endl;
		}
		return rem3 == 0;
	}
	if(n - pos == ones)
	{
		rem3 = (rem3 + ((n - pos) & 1)) % 3;
		if(rem3 == 0)
		{
			for(int i = 0; i < pos; i++)
				cout <<num[i];
			for(int i = pos; i < n; i++)
				cout <<1;
			cout <<endl;
			return true;
		}
		rem3 = (rem3 + 3 - ((n - pos) & 1)) % 3;
		return false;
	}
	if(pos == 0 || (pos > 0 && num[pos - 1] == 0))
	{
		num[pos] = 1;
		rem3 = (rem3 + 1 + ((n - pos - 1) & 1)) % 3;
		if(rec(pos + 1, ones - 1)) return true;
		rem3 = (rem3 + 2 - ((n - pos - 1) & 1)) % 3;
	}
	num[pos] = 0;
	return rec(pos + 1, ones);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>s;
	n = s.length();
	for(int i = 0; i < n; i++)
		a += s[i] == '1';
	b = n - a;
	if(a == 0)
	{
		cout <<string(n, '0') <<"\n";
		return 0;
	}
	if(b < a - 1)
	{
		cout <<"NO\n";
		return 0;
	}
	int ab, ba;
	if(a == 1 || (b < a && a % 3 != 0))
	{
		cout <<"NO\n";
		return 0;
	}
	switch(a % 3)
	{
	case 0:
		ab = a;
		ba = 0;
		break;
	case 1:
		ab = a - 2;
		ba = 2;
		break;
	case 2:
		ab = a - 1;
		ba = 1;
	}
	for(int i = 0; i < ab - 1; i++)
		cout <<"10";
	if(a % 3 == 0 && b + 1 == a)
	{
		cout <<"1\n";
		return 0;
	}
	cout <<"10";
	for(int i = 0; i < ba; i++)
		cout <<"01";
	cout <<string(b - a, '0') <<"\n";
}
