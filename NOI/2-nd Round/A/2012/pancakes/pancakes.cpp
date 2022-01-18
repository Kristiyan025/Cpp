#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;

using ll = unsigned long long;
ll x;
int n;
vector<int> furn;
int maxi = INT_MIN;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >>x >>n;
    furn.resize(n);
    for(int& i : furn)
        cin >>i;
    for(int i : furn)
        if(i > maxi) maxi = i;
    ll r = x * maxi + 1, l = 1, mid;
    ll cnt;
    ll res = r - 1;
    while(r - l > 1)
    {
        mid = l + (r - l >> 1);
        cnt = 0;
        for(int i : furn)
            cnt += mid / i;
        if(cnt >= x && mid < res) res = mid;
        if(cnt >= x)
            r = mid;
        else if(cnt < x)
            l = mid;
    }
    cnt = 0;
    for(int i : furn)
        cnt += l / i;
    if(cnt >= x && l < res) res = l;
    cout <<res <<endl;
}
