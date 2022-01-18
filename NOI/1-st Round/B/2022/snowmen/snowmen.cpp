#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int maxN = 1e6 + 1;
int n;
int a[maxN];
int pre[maxN]; //pre[i] points to the index with the second ball from the top of snowman i
int top[maxN]; //pre[i] points to the index with the first ball from the top of snowman i
int balls[maxN];
unsigned long long sum = 0;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	int p, m;
	for(int i = 1; i <= n; i++)
	{
		cin >>p >>m;
		balls[i] = m;
		if(m)
			a[i] = a[p] + m,
			top[i] = i,
			pre[i] = p;
		else
			a[i] = a[p] - balls[top[p]],
			top[i] = pre[p],
			pre[i] = pre[pre[p]];
		sum += a[i];
	}
	cout <<sum <<endl;
}
