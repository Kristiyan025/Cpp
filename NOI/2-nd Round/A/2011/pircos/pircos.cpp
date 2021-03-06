#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
int n;
ll xOr = 0, a, b, d, c1 = 0, c2 = 0;
ll v[1000001];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	for(int i = 0; i < n; i++)
	{
		cin >>a;
		xOr ^= a;
		v[i] = a;
	} //xOr == s ^ e
	d = xOr & -xOr;
	/* If xOr = 101011000
	then d = 000001000 (equal to the first set bit in xOr(Used in Binary Indexed Trees(BIT))) */
	for(int i = 0; i < n; i++)
		if(v[i] & d) //If the single bit in d is set in v[i]
			c1 ^= v[i];
		else
			c2 ^= v[i];
	c1 ^= xOr;
	c2 ^= xOr;
	cout <<min(c1, c2) <<" " <<max(c1, c2) <<endl;
}
