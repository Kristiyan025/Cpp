#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
const int maxA = 3e6 + 1;
int n;
vector<int> a;
bool is[maxA];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	a.resize(n);
	for(int& i : a)
		(cin >>i),
		is[i] = 1;
	ull res = 0;
	for(int i : a)
	{
		for(int j = i << 1; j < maxA; j += i)
			if(is[j])
				for(int k = j << 1; k < maxA; k += j)
					res += is[k];
	}
	cout <<res <<endl;
}
