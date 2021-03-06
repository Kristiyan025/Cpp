#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int maxN = 2e5 + 1;
int n;
vector<int> tr[maxN];
bool know[maxN];
int tin[maxN], tout[maxN], d[maxN] = {-1};
int eu[maxN];
int timer = 0;

void dfs(int v = 1, int p = 0)
{
	eu[timer] = v;
	tin[v] = timer++;
	d[v] = d[p] + 1;
	if(tr[v].empty())
	{
		tout[v] = timer;
		return;
	}
	for(int to : tr[v])
		dfs(to, v);
	tout[v] = timer;
}

namespace treap
{
	struct nd
	{
		int X, Y;
		int sz = 1;
		nd *l, *r;
		nd(int x) : X(x), Y(rand()), l(nullptr), r(nullptr) {}
		nd(int x, nd* _l, nd* _r) : nd(x)
		{
			l = _l;
			r = _r;
			if(l) sz += l->sz;
			if(r) sz += r->sz;
		}
	};
	typedef nd* pnd;

	inline int cnt(pnd t)
	{ return t ? t->sz : 0; }
	inline void upd_cnt(pnd t)
	{ if(t) t->sz = cnt(t->l) + cnt(t->r) + 1; }
	void split(pnd t, int x, pnd& l, pnd& r)
	{
		if(!t){
			l = r = NULL;
			return;
		}
		if(t->X <= x)
			split(t->r, x, t->r, r), l = t;
		else
			split(t->l, x, l, t->l), r = t;
	}
	pnd merge(pnd t1, pnd t2)
	{
		if(!t1 || !t2)
			return t1 ? t1 : t2;
		if(t1->Y >= t2->Y)
		{
			t1->r = merge(t1->r, t2);
			return t1;
		}
		else
		{
			t2->l = merge(t1, t2->l);
			return t2;
		}
	}
	void insert(int x, pnd& t)
	{
		if(!t)
		{
			t = new nd(x);
			return;
		}
		if(t->X >= x)
			insert(x, t->l);
		else
			insert(x, t->r);
	}
	void erase(int x, pnd& t)
	{
		if(!t) return;
		if(t->X == x)
		{
			pnd tm = t;
			t = merge(t->l, t->r);
			delete tm;
		}
		if(t->X >= x)
			erase(x, t->l);
		else
			erase(x, t->r);
	}
	pnd unite(pnd t1, pnd t2)
	{
		if(!t1 || !t2)
			return t1 ? t1 : t2;
		if(t1->Y < t2->Y) swap(t1, t2);
		pnd t2l, t2r;
		split(t2, t1->X, t2l, t2r);
		t1->l = unite(t1->l, t2l);
		t1->r = unite(t1->r, t2r);
		return t1;
	}
	pnd build(vector<int>& xs)
	{
		pnd t;
		for(int x : xs)
			insert(x, t);
		return t;
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n;
	int a, b;
	char c;
	for(int i = 1; i < n; i++)
	{
		cin >>a >>b;
		tr[a].emplace_back(b);
	}
	for(int i = 1; i <= n; i++)
	{
		cin >>c;
		know[i] = c == '1';
	}
	dfs();
	cout <<"eu: "; for(int i = 0; i < n; i++) cout <<eu[i] <<" "; cout <<endl;
	for(int i = 1; i <= n; i++)
	{
		cout <<i <<" -> " <<"tin: " <<tin[i] <<" tout: " <<tout[i] <<" d: " <<d[i] <<endl;
	}
}
