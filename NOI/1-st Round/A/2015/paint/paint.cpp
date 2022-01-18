#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using pii = pair<int, int>;
#define X first
#define Y second

ull rev(ull hor, ull nf)
{
    if(hor & 1) hor = (hor + nf - 1) >> 1;
    else hor >>= 1;
    return hor + nf - 1;
}

void findId(ull n)
{
    n++;
    ull nf = 1ULL << (ull)floor(log2(n));
    ull hor = n - nf;
    hor = (hor << 1);
    if(hor > nf - 1) hor -= nf - 1;
    cout <<rev(hor >> 1, nf >> 1) <<endl;
    cout <<rev(hor << 1, nf << 1) <<" " <<rev(hor << 1 | 1, nf << 1) <<endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ull n;
    cin >>n;
    findId(n);
}
