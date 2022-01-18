#include<bits/stdc++.h>
using namespace std;

const int maxN = 2e6;
int n;
string s;
bitset<maxN> ex;
stack<int> br;
stack<int> wk, str;
int op, cl;
bool okToRem;

struct brackets
{
	int l, r;
	brackets() {}
	brackets(int l, int r) : l(l), r(r) {}
};
vector<brackets> prevBr;
#define weak(x) (x == '+' || x == '-')
#define strong(x) (x == '*' || x == '/')

bool lookForWeakIn(int l, int r)
{
	for(int i = l + 1; i < r; i++)
		if(weak(s[i]))
			return true;
	return false;
}

bool calc(int l, int r)
{
	vector<brackets> needed;
	for(int i = prevBr.size() - 1; i >= 0 && prevBr[i].l > l; i--)
	{ //all brackets inside (l, r)
		needed.emplace_back(prevBr[i]);
		prevBr.pop_back();
	}
	if(needed.empty())
	{
		bool b = lookForWeakIn(l, r);
		if(!b) ex[l] = ex[r] = 1;
		return b;
	}
	else
	{
		bool b = lookForWeakIn(l, needed.back().l) ||
				 lookForWeakIn(needed[0].r, r);
		if(!b)
		{
			for(int i = 1; i < needed.size(); i++)
			{
				b = b || lookForWeakIn(needed[i].r, needed[i - 1].l);
				if(b) break;
			}
		}
		if(!b)
		{
			ex[l] = ex[r] = 1;
			for(auto it = needed.rbegin(); it != needed.rend(); it++)
				prevBr.emplace_back(*it);
		}
		return b;
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>s;
	n = s.length();
	for(int i = 0; i < n; i++)
	{
		if(s[i] == '(') br.push(i);
		else if(s[i] == ')')
		{
			op = br.top();
			br.pop();
			cl = i;
			okToRem = true;
			if(op && s[op - 1] != '(') okToRem = okToRem && s[op - 1] == '+';
			if(cl < n - 1 && s[cl + 1] != ')') okToRem = okToRem && weak(s[cl + 1]);
			if(okToRem) ex[op] = ex[cl] = 1;
			else
			{
				if(op && s[op - 1] == '/')
				{
					while(prevBr.size() && prevBr.back().l > op) prevBr.pop_back();
					prevBr.push_back({op, cl}); //if not excess
				}
				else if(calc(op, cl))
					prevBr.push_back({op, cl}); //if not excess
			}
		}
		else if(s[i] != '&')
		{
			switch(s[i])
			{
			case '+':
			case '-':
				wk.push(i);
				break;
			case '*':
			case '/':
				str.push(i);
				break;
			}
		}
	}
	for(int i = 0; i < n; i++)
		if(!ex[i])
			cout <<s[i];
	cout <<endl;
}
