#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

const int maxN = 1502;
const int maxNN = maxN * maxN;
struct shVec : public vector<int>
{ shVec() : vector<int>() {this->reserve(4);}};
short n, m;
int g[maxNN];
int hashG[maxN][maxN];
shVec gr[maxNN];
bool vis[maxNN];
int tout[maxNN], d[maxNN];
int timer, hu, hv, s, f, ps;
bool tr[maxNN];
int id[maxNN], pos[maxNN];
bool in[maxNN];
bool isExit;
int eSz = 0, nSz = 0;

inline int hashV(short i, short j)
{ return i * maxN + j; }
inline int next(short i, short j, char c)
{
	switch(c)
	{
		case '^': i--; break;
		case '>': j++; break;
		case 'v': i++; break;
		case '<': j--;
	}
	return hashG[i][j];
}
inline bool IsExit(int v)
{ return (hu = v / maxN) == 0 || hu == n + 1 || (hu = v % maxN) == 0 || hu == m + 1; }

struct tree
{
	int strt, n;
	tree(int st, bool isE = 1)
	{
		strt = st;
		isExit = isE;
		timer = 0;
		dfs(st);
	}
	void dfs(int v);
	inline bool isAncestor(int u, int v)
	{ return pos[u] <= pos[v] && tout[v] <= tout[u]; }
	inline int cycSt() { return g[strt]; }
};
vector<tree> ex;
void tree::dfs(int v)
{
	vis[v] = 1;
	tr[v] = isExit;
	id[v] = eSz;
	pos[v] = timer++;
	d[v] = timer == 1 ? 0 : d[g[v]] + 1;
	for(int to : gr[v])
		if(!vis[to])
			dfs(to);
	tout[v] = timer;
}
stack<int> forBuilding;
struct cycTree
{
	vector<int> _cyc;
	cycTree(int st)
	{ //Tortoise & Hare Alg
		s = f = st;
		do {
			s = g[s];
			f = g[g[f]];
		} while(s != f);
		_cyc.emplace_back(s); in[s] = 1;
		pos[s] = ps = 0;
		id[s] = nSz;
		s = g[s];
		while(s != f)
		{
			id[s] = nSz;
			pos[s] = ++ps;
			_cyc.emplace_back(s); in[s] = 1;
			s = g[s];
		}
		for(int i : _cyc)
		{
			vis[i] = 1;
			for(int j : gr[i])
				if(!in[j])
					ex.emplace_back(j, 0), eSz++;
		}

	}
	inline bool isInCyc(int v) { return id[v] == id[_cyc[0]] && in[v]; }
	inline int n() { return _cyc.size(); }
};
vector<cycTree> nex;
inline void constructTree(int v) { ex.emplace_back(v); eSz++; }
inline void constructCycTree(int v) { nex.emplace_back(v); nSz++; }
void readAndConstruct()
{
	cin >>n >>m;
	int hsh;
	char c;
	for(short i = 0; i < n + 2; i++)
		for(short j = 0; j < m + 2; j++)
			hashG[i][j] = hashV(i, j);
	for(short i = 1; i <= n; i++)
		for(short j = 1; j <= m; j++)
	{
		cin >>c;
		g[hsh = hashG[i][j]] = next(i, j, c);
		gr[g[hsh]].emplace_back(hsh);
	}
	for(short i = 1; i <= n; i++)
		if(gr[hsh = hashG[i][0]].size())
			constructTree(hsh);
	for(short i = 1; i <= n; i++)
		if(gr[hsh = hashG[i][m + 1]].size())
			constructTree(hsh);
	for(short i = 1; i <= m; i++)
		if(gr[hsh = hashG[0][i]].size())
			constructTree(hsh);
	for(short i = 1; i <= m; i++)
		if(gr[hsh = hashG[n + 1][i]].size())
			constructTree(hsh);
	for(short i = 1; i <= n; i++)
		for(short j = 1; j <= m; j++)
			if(!vis[hsh = hashG[i][j]])
				constructCycTree(hsh);
}

int path;
int isReachable(int cv, int sv)
{
	if(IsExit(sv)) return -1;
	path = 0;
	if(tr[sv])
	{
		tree& cur = ex[id[sv]];
		if(tr[cv] && id[sv] == id[cv] && cur.isAncestor(cv, sv))
			return d[sv] - d[cv];
		return -1;
	}
	else if(id[sv] < nex.size() && nex[id[sv]].isInCyc(sv))
	{
		cycTree& cur = nex[id[sv]];
		if(id[sv] == id[cv] && id[cv] < nex.size() && nex[id[cv]].isInCyc(cv))
			return (pos[cv] - pos[sv] + cur.n()) % cur.n();
		return -1;
	}
	else
	{
		tree& cur = ex[id[sv]];
		if(id[cv] == id[sv] && !tr[cv] &&
		  (id[cv] < nex.size() && !nex[id[cv]].isInCyc(cv) || id[cv] >= nex.size()))
		{
			if(cur.isAncestor(cv, sv))
				return d[sv] - d[cv];
			return -1;
		}
		else if(nex[id[cur.cycSt()]].isInCyc(cv))
		{
			path = d[sv] + 1;
			sv = cur.cycSt();
			cycTree& ncur = nex[id[cur.cycSt()]];
			path += (pos[cv] - pos[sv] + ncur.n()) % ncur.n();
			return path;
		}
		return -1;
	}
}
void answer()
{
	int q, si, sj, ci, cj, sv, cv, cn, ans;
	char c;
	cin >>q;
	while(q--)
	{
		cin >>si >>sj >>ci >>cj >>c;
		sv = hashG[si][sj];
		cv = hashG[ci][cj];
		cn = next(ci, cj, c);
		if(sv == cv)
		{
			if(g[cn] == cv)
				cout <<"0\n";
			else if(~isReachable(cv, cn))
				cout <<"0\n";
			else if(tr[cn])
				cout <<d[cn] + 1 <<"\n";
			else if(IsExit(cn))
				cout <<"1\n";
			else
				cout <<"0\n";
		}
		else if(~(ans = isReachable(cv, sv)))
		{
			if(g[cn] == cv)
				cout <<"0\n";
			else if(~isReachable(cv, cn))
				cout <<"0\n";
			else if(tr[cn])
				cout <<ans + 1 + d[cn] <<"\n";
			else if(IsExit(cn))
				cout <<ans + 1 <<"\n";
			else
				cout <<"0\n";
		}
		else if(tr[sv])
			cout <<d[sv] <<"\n";
		else
			cout <<"0\n";
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	readAndConstruct();
	answer();
}
