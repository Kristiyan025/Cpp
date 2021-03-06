//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")
//#pragma GCC optimization ("unroll-loops")
#include<bits/stdc++.h>
using namespace std;

using vec = vector<int>;
using vvi = vector<vec>;

inline void min(int& a, int b)
{
	a = a < b ? a : b;
}
inline void max(int& a, int b)
{
	a = a > b ? a : b;
}

int n, m, q, pp;

namespace dsu
{
	vec par;
	vec heu;

	void init()
	{
		par.resize(n);
		heu.resize(n, 0);
		for(int i = 0; i < n; i++)
			par[i] = i;
	}

	int get(int v)
	{
		return par[v] = par[v] == v ? v : get(par[v]);
	}

	void union_sets(int u, int v)
	{
		u = get(u);
		v = get(v);
		if(heu[u] < heu[v]) swap(u, v);
		par[v] = u;
		heu[u] += heu[u] == heu[v];
	}
}

namespace br
{
	vvi g;
	vector<char> vis;
	vec tin, low;
	int timer = 0;

	void init()
	{
		g.resize(n);
		vis.resize(n, false);
		tin.resize(n, 0);
		low.resize(n, 0);
		int a, b;
		while(m--)
		{
			cin >>a >>b;
			a--; b--;
			g[a].emplace_back(b);
			g[b].emplace_back(a);
		}
	}

	void dfs(int v, int p = -1)
	{
		vis[v] = true;
		tin[v] = low[v] = ++timer;
		for(int to : g[v])
		{
			if(to == p) continue;
			if(vis[to]) //not a bridge
			{
				min(low[v], low[to]);
				dsu::union_sets(v, to);
			}
			else
			{
				dfs(to, v);
				min(low[v], low[to]);
				if(low[to] <= tin[v]) //not a bridge
					dsu::union_sets(v, to);
			}
		}
	}

	void traverse(vec& par)
	{
		for(int i = 0; i < n; i++)
			if(!vis[i]) dfs(i);
		timer = 0;
		low.assign(n, -1);
		for(int i = 0; i < n; i++)
			low[par[i]] = low[par[i]] == -1 ? timer++ : low[par[i]];
		for(int i = 0; i < n; i++)
			par[i] = low[par[i]];
		n = timer;
	}
}

using ll = long long;
using pii = pair<int, int>;
using vvc = vector<vector<char>>;

namespace tree
{
	vvi tr;
	int logN;
	int root, d;
	vec comp;
	int compId = 0;
	vvi up;
	vec  a/*start*/, b/*end*/, c/*lca*/;
	#define tin br::tin
	#define tout br::low
	#define timer br::timer

	void dfs(int v, int p, int dp);
	void init(vvi& g, const vec& par)
	{
		tr.assign(n, vec());
		comp.assign(n, -1);
		a.resize(n, 0);
		b.resize(n, 0);
		c.resize(n, 0);
		for(int i = 0; i < g.size(); i++)
			for(int v : g[i])
				if(par[i] != par[v])
					tr[par[i]].emplace_back(par[v]);
		/*
		cout <<"par: "; for(int i : par) cout <<i <<" "; cout <<endl;
		for(auto& r : tr){
			for(int i : r)
				cout <<i <<" "; cout <<endl;
		}//*/
		fill(tin.begin(), tin.begin() + n, -1);
		fill(tout.begin(), tout.begin() + n, -1);
		timer = 0;
		up.resize(n);
		for(int i = 0; i < n; i++)
			if(comp[i] == -1)
		{
			root = i;
			if(tr[i].size() == 0)
			{
				comp[i] = compId++;
				continue;
			}
			dfs(i, i, 1);
			compId++;
		}
	}

	void dfs(int v, int p, int dp)
	{
		tin[v] = timer++;
		comp[v] = compId;
		logN = ceil(log2(dp)) + 1;
		up[v].resize(logN);
		up[v][0] = p;
		for(int i = 1; i < logN; i++)
			up[v][i] = up[up[v][i - 1]].size() >= i ? up[up[v][i - 1]][i - 1] : root;
		if(tr[v].size() == 1 && v != root) //leaf
		{
			tout[v] = timer++;
			return;
		}
		for(int to : tr[v])
			if(to != p)
				dfs(to, v, dp + 1);
		tout[v] = timer++;
	}

	inline bool isAnc(int u, int v) //is ancestor
	{
		return tin[u] <= tin[v] && tout[v] <= tout[u];
	}

	int lca(int u, int v)
	{
		if(isAnc(u, v)) return u;
		if(isAnc(v, u)) return v;
		for(int l = up[u].size() - 1; l >= 0; l--)
			if(!isAnc(up[u].size() > l ? up[u][l] : up[u].back(), v))
				u = up[u].size() > l ? up[u][l] : up[u].back();
		return up[u][0];
	}

	bool dfs2(int v, int p = -1)
	{
		br::vis[v] = 1;
		if(tr[v].size() == 1 && p != -1) //leaf
			return !((a[v] - c[v]) && (b[v] - c[v]));
		for(int to : tr[v])
			if(to != p)
		{
			if(!dfs2(to, v)) return false;
			a[v] += a[to];
			b[v] += b[to];
			c[v] += c[to];
		}
		//cout <<"v: " <<v <<" a: " <<a[v] <<" b: " <<b[v] <<" c: " <<c[v] <<endl;
		return !((a[v] - c[v]) && (b[v] - c[v]));
	}

	bool lastCheck()
	{
		fill(br::vis.begin(), br::vis.begin() + n, 0);
		for(int i = 0; i < n; i++)
			if(!br::vis[i])
				if(!dfs2(i))
					return false;
		return true;
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n >>m >>q;
	dsu::init();
	br::init();
	br::traverse(dsu::par);
	if(n == 1)
	{
		cout <<"Yes\n";
		return 0;
	}
	tree::init(br::g, dsu::par);

	int a, b;
	while(q--)
	{
		cin >>a >>b;
		a = dsu::par[--a];
		b = dsu::par[--b];
		if(tree::comp[a] != tree::comp[b])
		{
			cout <<"No\n";
			return 0;
		}
		tree::a[a]++;
		tree::b[b]++;
		tree::c[tree::lca(a, b)]++;
	}/*
	cout <<"up:\n";
	for(int l = 0; l < tree::logN; l++)
	{
		for(int i = 0; i < n; i++) cout <<tree::up[i][l] <<" "; cout <<endl;
	}//*/

	if(tree::lastCheck())
		cout <<"Yes\n";
	else
		cout <<"No\n";
}
/*
6 8 4
1 2
1 2
1 2
2 3
3 4
4 5
4 5
4 5

5 10 3
1 2
2 3
3 4
4 5
5 1
1 3
2 4
3 5
4 1
5 2

11 10 5
1 2
2 5
2 6
6 8
8 10
8 11
1 3
3 7
7 9
1 4

9 4
5 10
5 11
2 4
6 10
*/
