#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ii = pair<int, int>;
int n, k, acc = 0, fst, mul, add, mod;
deque<ii> q;
ull ans = 0;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n >>k >>fst >>mul >>add >>mod;
	for(int i = 0, j = fst; i < n; i++, j = (ull(j) * mul + add) % mod)
	{
		while(q.size() && q.back().first < j) q.pop_back();
		q.push_back({j, i});
		ans += q.front().first;
		while(q.size() && q.front().second < i - k + 2) q.pop_front();
	}
	cout <<ans <<endl;
}
