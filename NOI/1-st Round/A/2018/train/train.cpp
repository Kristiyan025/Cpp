#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> p;
stack<int> a, b; //a + rev(b) is always increasing

bool possible()
{
	a = b = {};
	for(int i = n - 1; i >= 0; i--)
		a.push(i);
	for(int i = 0; i < n; i++)
	{
		if(a.size() && a.top() <= p[i])
		{
			while(a.top() < p[i])
				b.push(a.top()),
				a.pop();
			a.pop();
		}
		else if(b.size())
		{
			if(b.top() == p[i]) b.pop();
			else return false;
		}
	}
	return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	p.resize(n);
	for(int t = 0; t < 5; t++)
	{
		for(int i = 0; i < n; i++)
			(cin >>p[i]),
			p[i]--;
		cout <<possible();
	}
	cout <<endl;
}
