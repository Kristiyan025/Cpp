#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

string s;
stack<char> vals;
bool beg[27];

inline bool f(bool a, bool b)
{ return !(a && b); }

bool eval()
{
	while(vals.size()) vals.pop();
	vals.push(-1);
	short i = 0;
	bool res;
	for(const char c : s)
	{
		switch(c)
		{
		case '(':
			vals.push(-1);
			break;
		case ')':
			res = vals.top(); vals.pop();
			if(vals.top() == -1) vals.top() = res;
			else  vals.top() = f(vals.top(), res);
			break;
		default:
			if(vals.top() == -1) vals.top() = beg[c - 'a'];
			else  vals.top() = f(vals.top(), beg[c - 'a']);
		}
		i++;
	}
	return vals.top();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>s;
	char a;
	unordered_set<char> uni(s.begin(), s.end());
	int n = uni.size() - uni.count('(') - uni.count(')');
	while((cin >> a) && a != '2')
	{
		beg[0] = a == '1';
		for(int i = 1; i < n; i++)
		{
			cin >>a;
			beg[i] = a == '1';
		}
		cout <<eval();
	}
	cout <<endl;
}
