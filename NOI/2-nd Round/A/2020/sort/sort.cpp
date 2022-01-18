#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
int n;
vector<int> a;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	a.resize(n);
	for(int& i : a)
		cin >>i;
	for(int i = n - 1; i > 0; i--)
		a[i] = a[i] - a[i - 1];
	//for(int& i : a)
	//	cout <<i <<" "; cout <<endl;
	ll pos = 0, neg = 0, acc;
	for(int i = 1; i < n; i++)
		if(a[i] > 0)
	{
		acc = 0;
		while(i < n && a[i] > 0) acc += a[i], pos += acc, i++;//, (cout <<"acc: " <<acc <<" pos: " <<pos <<endl);
	} //cout <<"neg:\n";
	for(int i = 1; i < n; i++)
		if(a[i] < 0)
	{
		acc = 0;
		while(i < n && a[i] < 0) acc -= a[i], neg += acc, i++;//, (cout <<"acc: " <<acc <<" neg: " <<neg <<endl);
	}
	cout <<min(neg, abs(pos - neg)) <<endl;
}
