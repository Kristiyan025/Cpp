#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
double d;
int a, b;

template<typename T>
inline T sq(T g)
{
	return g * g;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>d;
	a = (int)(100 * d + 0.5);
	cin >>d;
	b = (int)(100 * d + 0.5);
	cout <<setprecision(2) <<fixed;
	cout <<(3 * a <= b ? 0 : (a + b) * sqrt(sq((double)a) - sq((double)(b - a)) / 4.0) / 20000.0) <<endl;
}
