#include<bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
#define X first
#define Y second
int n;
vector<pii> v;
short s;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >>n;
    v.resize(n);
    for(int i = 0; i < n; i++)
    {
        cin >>v[i].X;
        v[i].Y = i + 1;
    }
    cin >>s;
    sort(v.begin(), v.end());
    auto it = v.end();
    pii res = {n + 1, n + 1}, cur;
    for(int i = 0; i <= it - v.begin(); i++)
    {
        auto it2 = lower_bound(v.begin() + i, it, s - v[i].X, [](const pii& p, int a){ return p.X < a; });
        if(it2 != v.end() && it2->X == s - v[i].X)
        {
            cur = {min(v[i].Y, it2->Y), max(v[i].Y, it2->Y)};
            if(cur < res) res = cur;
        }
    }
    if(res.X == n + 1 && res.Y == n + 1) res = {0, 0};
    cout <<res.X <<" " <<res.Y <<endl;
}
