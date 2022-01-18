#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> v;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	v.resize(n);
	for(int i = 0; i < n; i++)
		cin >>v[i];
	int maxi = 0, mini = n - 1, s = 0, t = 0;
	for(int i = n - 1; i >= 0; i--)
		mini = min(mini, v[i] + s),
		maxi = max(maxi, v[i] + t),
		s += v[i] == i,
		t += v[i] > 0;
	cout <<maxi <<"\n" <<mini <<"\n";
}
