#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int maxN = 1e4;
int n;
short even[maxN]; //even[i] points to the first element before i that is even
int res = 0;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	int a;
	cin >>a;
	even[0] = (a & 1) == 0 ? 0 : -1;
	res = even[0] == 0;
	for(int i = 1; i < n; i++)
	{
		cin >>a;
		even[i] = (a & 1) == 0 ? i : even[i - 1];
		res += even[i] + 1;
	}
	cout <<res <<endl;
}
