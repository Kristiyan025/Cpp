#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
int n;
vector<int> xs, ys;
ull res = 0;
ll sum, sum2; //store the sum of the elements and the sum of the squares of the elements in the current prefix

void add(vector<int>& v)
{
	//res += (vi - vj)^2 = vi^2 + vj^2 - 2 * vi * vj for all i != j
	sum = v[0];
	sum2 = v[0] * v[0];
	for(int i = 1; i < n; i++)
		res += (ull)i * v[i] * v[i] + sum2 - (v[i] * sum << 1),
		sum += v[i],
		sum2 += v[i] * v[i];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	xs.resize(n);
	ys.resize(n);
	for(int i = 0; i < n; i++)
		cin >>xs[i] >>ys[i];
	add(xs); //ds(ij)^2 = dx(ij)^2 + dy(ij)^2 for all i != j
	add(ys);
	cout <<res <<endl;
}
