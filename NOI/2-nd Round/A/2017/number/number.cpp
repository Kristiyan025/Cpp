#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const short maxLen = 202;
string m, n;
struct bigNum
{
	vector<char> num;
	bool sign = 0;
	bigNum(short len = 0) { num.reserve(maxLen); num.resize(len, 0); }
	bigNum(const string& s) {
		num.resize(s.length(), 0);
		for(int i = 0; i < s.length(); i++) num[i] = s[s.length() - i - 1] - '0';
	}
	bigNum(const string&& s) {
		num.resize(s.length(), 0);
		for(int i = 0; i < s.length(); i++) num[i] = s[s.length() - i - 1] - '0';
	}
	bigNum(const bigNum& a) { num.assign(a.num.begin(), a.num.end()); sign = a.sign; }
};
void print(bigNum a);
bool operator <(bigNum a, bigNum b)
{
	if(a.num.size() < b.num.size()) return 1;
	if(a.num.size() > b.num.size()) return 0;
	for(int i = a.num.size() - 1; i >= 0; i--)
		if(a.num[i] < b.num[i]) return 1;
		else if(a.num[i] > b.num[i]) return 0;
	return 0;
}
bool operator ==(bigNum a, bigNum b)
{
	if(a.sign != b.sign) return 0;
	if(a.num.size() - b.num.size()) return 0;
	for(int i = 0; i < a.num.size(); i++)
		if(a.num[i] != b.num[i])
			return 0;
	return 1;
}
bigNum operator +(bigNum a, bigNum b)
{
	static char carry; carry = 0;
	if(a.num.size() < b.num.size()) swap(a, b);
	bigNum res(a);
	res.num.emplace_back(0);
	b.num.resize(res.num.size(), 0);
	for(int i = 0; i < b.num.size(); i++)
	{
		res.num[i] += carry + b.num[i];
		carry = res.num[i] / 10;
		res.num[i] %= 10;
	}
	while(res.num.size() > 1 && !res.num.back()) res.num.pop_back();
	return res;
}
bigNum operator -(bigNum a, bigNum b)
{
	if(a.sign)
	{
		a.sign = 0;
		if(b.sign)
			b.sign = 0,
			swap(a, b);
		else
		{
			bigNum res = a + b;
			res.sign = 1;
			return res;
		}
	}
	else if(b.sign)
	{
		bigNum res = a + b;
		res.sign = 0;
		return res;
	}
	if(a < b)
	{
		bigNum res = b - a;
		res.sign = 1;
		return res;
	}
	static char carry; carry = 0;
	for(int i = 0; i < b.num.size() || carry; i++)
	{
		a.num[i] -= carry + (i < b.num.size() ? b.num[i] : 0);
		if((carry = a.num[i] < 0)) a.num[i] += 10;
	}
	while(a.num.size() > 1 && !a.num.back()) a.num.pop_back();
	return a;
}
bigNum operator *(bigNum a, bigNum b)
{
	static int carry, cur; carry = 0;
	bigNum res(a.num.size() + b.num.size());
	a.num.resize(res.num.size(), 0);
	b.num.resize(res.num.size(), 0);
	for(int i = 0; i < res.num.size(); i++)
	{
		cur = carry;
		for(int j = 0; j <= i; j++)
			cur += a.num[j] * b.num[i - j];
		carry = cur / 10;
		res.num[i] = cur % 10;
	}
	while(res.num.size() > 1 && !res.num.back()) res.num.pop_back();
	return res;
}
bigNum operator /(bigNum a, int b)
{
	if(a.num.size() == 1 && a.num[0] == 0) return a;
	static int c, id, cnt; c = cnt = 0; ;
	bigNum res(a.num.size());
	for(int id = a.num.size() - 1; id >= 0; id--)
	{
		c = c * 10 + a.num[id];
		if(c >= b)
			res.num[id] = (c / b), c %= b;
	}
	while(res.num.size() > 1 && !res.num.back()) res.num.pop_back();
	return res;
}

bigNum subtr;
inline bigNum f(bigNum a)
{ return a * a - subtr; }

#define b(x) bigNum(x)
const bigNum one("1");
bigNum bin_search(bigNum a)
{
	if(a.num.size() == 1 && a.num[0] == 1) return a;
	subtr = a;
	bigNum l("0"), r(a), mid, fm;
	while(one < r - l)
	{
		mid = (l + r) / 2;
		fm = f(mid);
		if(fm.num.empty()) return mid;
		if(fm.sign) l = mid;
		else r = mid;
	}
	if((l + one) * (l + one) == a) l = l + one;
	return l;
}
void print(bigNum a)
{
	if(a.sign) cout <<"-";
	for(int i = a.num.size() - 1; i >= 0; i--)
		cout <<int(a.num[i]); cout <<endl;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>m >>n;
	bigNum lw(m), up(n);
	lw = lw * b("4") + b("1");
	up = up * b("4") + b("1");
	bigNum sqrtLW = bin_search(lw);
	bigNum sqrtUP = bin_search(up);
	if(!(sqrtLW * sqrtLW == lw)) sqrtLW = sqrtLW + one;
	if((sqrtLW.num[0] & 1) == 0) sqrtLW = sqrtLW + one;
	if((sqrtUP.num[0] & 1) == 0) sqrtUP = sqrtUP - one;
	if(sqrtUP < sqrtLW)
	{
		cout <<"0\n";
		return 0;
	}
	sqrtUP = (sqrtUP - sqrtLW) / 2 + one;
	print(sqrtUP);
}
