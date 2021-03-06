#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
/* All losing positions: (3k + 1, 3k + 1), (3k + 2, 3k + 2), (k, 3k), (3k, k)
bool col[101];
void test(){
    bool b;
	for(int i = 0; i < 30; i++)
	{
		b = 0;
		for(int j = 0; j < 30; j++)
		{
			if(i == 3 * j || j == 3 * i) {
				cout <<"0 ";
				b = col[j] = 1;
			}
			else if(col[j]) cout <<"1 ";
			else if(b) cout <<"1 ";
			else {
				cout <<"0 ";
				b = col[j] = 1;
			}
		}
		cout <<endl;
	}
}//*/
inline void solve()
{
	static ull p, q;
	cin >>p >>q;
	if(p == q && p % 3 != 0 ||
	   p == 3 * q || q == 3 * p) { cout <<"0\n"; return; }
	if(p == q) { cout <<"1 " <<p / 3 * 2 <<"\n"; return; }
	if(p > q && q % 3 != 0) { cout <<"1 " <<p - q <<"\n"; return; }
	if(p > q) { cout <<"1 " <<p - q / 3 <<"\n"; return; }
	if(p % 3 != 0) { cout <<"2 " <<q - p <<"\n"; return; }
	cout <<"2 " <<q - p / 3 <<"\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	//test();
	for(int i = 0; i < 3; i++)
		solve();
}
