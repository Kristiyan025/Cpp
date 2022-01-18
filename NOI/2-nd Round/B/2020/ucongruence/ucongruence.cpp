#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxU = 61;
int n, u, cnt = 0, m;
ll no;
vector<char> v;
unsigned long long mask = 0;
char pos[maxU];
vector<char> F;
vector<char> ord;
char id[maxU];
char pat[maxU];
ll P[maxU][maxU];
char lw[maxU];
char up[maxU];
char leader[maxU + 1];
vector<char> res;

/*
The function does the following operations:
	It Calculates the values of the coefficients
	P(n, k) for 1 <= k, n, <= u, which represent the number
	of strictly increasing sequences of n elements, each one of which is
	in the range [1, k].
	It relies heavily on the following formula:
		P(n, k) = P(n, k - 1) + P(n - 1, k - 1)
	The formula can be explained by the choice of the last element in the sequence:
	1) if it is k, then the rest of the n - 1 elements are in the range [1, k - 1]
	2) if it is not k, then all n elements are in the range [1, k - 1]
	Then the base cases of the recursion are:
	P(1, K) = K
	P(I, I) = 1
*/
void precalc()
{
	for(int i = 1; i <= u; i++)
		P[1][i] = i;
	for(int i = 2; i <= u; i++)
	{
		P[i][i] = 1;
		for(int j = i + 1; j <= u; j++)
			P[i][j] = P[i][j - 1] + P[i - 1][j - 1];
	}
}

/*
The function does the following operations:
	Let the original sequence v has m unique elements
	(1 <= m < maxU by the statement of the problem.
	Then, we create a new sequence C with n elements, such that each one of them is >= 1 and <= m,
	which is U-congruent to v. C will be the representative of the family of sequences, congruent to v,
	because it is the first in that family in lexicographic order.
	Now, we build a new sequence F with m elements, by going over C from left to right and,
	when we meet a value that we haven't seen before, we add it to F, else we continue to the next value in C.
	After that, we build a new sequence ord with n elements, which are the indices of the values of C in F.
	For example:
		v<7, 60> = 6 3 8 9 3 9 2
		C<7, 60> = 3 2 4 5 2 5 1
		v<7, 60> ~= C<7, 60>
		F = 3 2 4 5 1
		ord = 0 1 2 3 1 3 4
	For the solution of the problem we only need F and ord,
	so we can skip the creation of C with some clever insights.
	In the function below, you can think of the bits of mask as an array of type bool
*/
void compress()
{
	ord.resize(n);
	F.reserve(maxU);
	for(int i : v)
		mask |= 1ULL << i;
	for(int i = 1; i < maxU; i++)
		if(mask & 1ULL << i)
			pos[i] = ++cnt;
	/*
		Until here, there only m bits of mask that are set and
		they correspond to the unique elements of v. The array pos
		is used in the compression step from the values of v to the range [1, m].
	*/
	mask = 0;
	for(int i = 0; i < n; i++)
	{
		if((mask & 1ULL << pos[v[i]]) == 0)
		{
			mask |= 1ULL << pos[v[i]];
			id[pos[v[i]]] = F.size();
			F.emplace_back(pos[v[i]]);
		}
		ord[i] = F[pos[v[i]]];
	}
	m = F.size();
	no = P[m][u] + 1 >> 1;
	for(int i = 0; i < n; i++)
		ord[i] = id[pos[v[i]]];
	/*
		The array id[i] holds the index of the value i in the array F
		and is used for the calculation of the array ord.
	*/
}

inline ll check(ll x) { return x == 0 ? 1LL : x; }

/*
The function does the following operations:
	Given the beginning of sequence pat it find
	how many sequences in the family of F begin that way.
	Using mask we create disjoint union of open segments, which,
	when united with all elements found so far, gives the interval [1, k].
	Then, we go through each of those segments, about which
	we know the endpoints and how many of the remaining elements should be in it. Thus,
	using that information and the coefficients P[N][K],
	we can calculate the number sequences in the family of F that begin this
	way by multiplying the coefficient for each segment together.
	Of course, we have to watch for the special case, when a certain segment
	doesn't contain any elements. Then, we gust multiply the result val by 1,
	not by 0 (the meaning of ll check(ll x)).
		P.S.: The operations in the function resemble the second step of
		finding the union of several segments.
*/
ll val;
void calc()
{
	val = 1;
	int st = 1;
	while(st <= u + 1 && mask & 1ULL << st) st++;
	st--;
	for(int i = st + 2; i <= u + 1; i++)
	{
		if((mask & 1ULL << i) == 0 &&
		   (mask & 1ULL << i - 1))
		    st = i - 1;
		if((mask & 1ULL << i) &&
		   (mask & 1ULL << i - 1) == 0)
			val *= check(P[leader[i] - leader[st] - 1][i - st - 1]);
	}
}

/*
The function does the following operations:
	By given position of the sequence no in the family, it finds the sequence pat.
	The search resembles a binary search:
	If we have the beginning of the sequence upto position i,
	we can find the element at position i + 1 by checking          (*)
	each possible value and some conditions:
	1) The value must be in [1, k];
	2) The value should not be equal to any of the values we have found so far.
	3) The family order should be maintained.
	So, if all of these conditions are preserved, then
	we count all possible continuations of the sequence
	with the information we have so far and with the help of
	the coefficients P[N][K].
	In the process described above we use the auxiliary arrays lw[i] and up[i], which
	hold the endpoints of the domain of the element i in F. Also we use the
	bitmask mask as an auxiliary bool array, which tracks the already found elements.
	The array leader hold the real equivalents of the elements from the
	sequence we want to build in F (used for (*)).
	At the end we use the resulting sequence pat consisting of m elements
	(the no-th sequence in the family of F) to reconstruct
	the sequence that is the answer of the problem using the ord array, found before.
*/
int cur;
void solve()
{
	mask = 1ULL | 1ULL << u + 1;
	memset(leader, -1, (maxU + 1) * sizeof(leader[0]));
	leader[0] = 0;
	leader[u + 1] = m + 1;
	/*
		Preparing leader and mask
		by setting the position right before the first and
		right after the last possible value.
	*/
	for(int i = 1; i <= m; i++)
	{
		lw[i] = i;
		up[i] = u - m + i;
	}
	/*
		The values lw[i] and up[i] are the endpoints of the range of possible
		values for each of the m unique values of the answer sequence we have to build.
	*/
	for(int t = 1, i; t <= m; t++)
	{
		cur = F[t - 1]; /*  Going through each position in the sequence we want to find  */
		for(i = lw[cur]; i <= up[cur]; i++)
		{
			mask |= 1ULL << i;
			leader[i] = cur;
			/*  Make the element at position t equal to i  */
			calc(); /*  Calculate how many sequences end that way  */
			if(no <= val) break;
			/*
				If it is less than the position no in the family,
				we have found the element and break the cycle.
			*/
			mask &= ~(1ULL << i);
			leader[i] = -1;
			no -= val;
			/*
				Else, we unmark i as the element at position t and
				continue to the next possible value by subtracting
				the found count of sequences from no.
			*/
		}
		pat[t - 1] = max(min(i, (int)up[cur]), (int)lw[cur]); /*  Ensuring we stay in the domain  */
		for(char j = cur - 1, dif = 1; j > 0; j--, dif++)
			up[j] = min((int)up[j], max(pat[t - 1] - dif, (int)lw[j]));
		for(int j = cur + 1, dif = 1; j <= m; j++, dif++)
			lw[j] = max((int)lw[j], min(pat[t - 1] + dif, (int)up[j]));
		/*  Updating the domain of all other elements.  */
	}
	for(int i = 0; i < n; i++)
		res[i] = pat[ord[i]]; /*  Constructing the answer to the problem  */
	for(auto it = res.begin(); it != res.end(); it++)
		cout <<(int)*it <<" "; /*  Printing the answer  */
	cout <<endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	cin >>n >>u;
	precalc();
	v.resize(n);
	res.resize(n);
	short inp;
	for(auto it = v.begin(); it != v.end(); it++)
	{
		cin >>inp;
		*it = inp;
	}
	compress();
	solve();
}
/*
7 60
6 3 8 9 3 9 2

3 5
2 3 1
*/
