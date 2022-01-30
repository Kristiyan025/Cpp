#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ld = long double;
using ldld = pair<ld, ld>;
#define L first
#define R second
int n, l, w, c, r, i;
ld hws, rd, mx, mn;
ldld a[10000];
stack<int> cyc;
bool b;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	while(cin >>n >>l >>w)
	{
		hws = w * 0.5;
		hws *= hws;
		for(i = 0; i < n; i++)
		{
			cin >>c >>r;
			if(r <= hws)
			{
				a[i] = {INT_MAX, INT_MAX};
				continue;
			}
			rd = sqrt(r * r - hws);
			a[i] = {c - rd, c + rd};
			//cout <<"cyc: " <<c <<" " <<r <<" " <<rd <<"\n";
		}
		sort(a, a + n, [](const ldld& i1, const ldld& i2){ return i1.L < i2.L || (i1.L == i2.L && i1.R > i2.R);});
		//for(i = 0; i < n; i++)
		//	cout <<"cur: " <<a[i].L <<" " <<a[i].R <<"\n";
		i = 0;
		while(i < n && a[i].R <= 0.0) i++;
		if(i == n || i < n && a[i].L > 0.0)
		{
			cout <<"-1\n";
			continue;
		}
		while(cyc.size()) cyc.pop();
		//cout <<"cur: " <<a[i].L <<" " <<a[i].R <<"\n";
		cyc.push(i);
		for(++i; i < n; i++)
		{
			//cout <<"cur: " <<a[i].L <<" " <<a[i].R <<"\n";
			if(a[i].L <= a[cyc.top()].R)
			{
				b = 0;
				while(cyc.size() && a[i].L <= a[cyc.top()].R) mx = cyc.top(), cyc.pop(), b = 1;
				if(b) cyc.push(mx);
				cyc.push(i);
			}
			else break;
			if(a[cyc.top()].R >= l) break;
		}
		cout <<(a[cyc.top()].R < l ? -1 : int(cyc.size())) <<"\n";
		//cout <<"st: "; while(cyc.size()) (cout <<a[cyc.top()].L <<", " <<a[cyc.top()].R <<" "), cyc.pop(); cout <<endl;
		//cout <<(a[cyc.top()].R < l ? -1 : int(cyc.size())) <<"\n";
	}
}
