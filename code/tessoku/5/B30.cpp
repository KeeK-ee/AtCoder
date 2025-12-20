#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <functional>
#include <ranges>
#include <cctype>
#include <iomanip>
using namespace std;

//#include "../../../ac-library-master/atcoder/dsu.hpp"
//#include <atcoder/all>
//using namespace atcoder;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;

const ll INF = 1e18;
const ll MOD = 1000000007;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

#define rep(i, a, n) for (ll i = a; i < (int)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(10)

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

// a の b 乗を m で割った余りを返す関数
// 変数 a は a^1 → a^2 → a^4 → a^8 → a^16 → ･･･ と変化
ll Power(ll a, ll b, ll m) {
	ll p = a, Answer = 1;
	for (int i = 0; i < 30; i++) {
		int wari = (1 << i);
		if ((b / wari) % 2 == 1) {
			Answer = (Answer * p) % m; // 「a の 2^i 乗」が掛けられるとき
		}
		p = (p * p) % m;
	}
	return Answer;
}

// a ÷ b を m で割った余りを返す関数
ll Division(ll a, ll b, ll m) {
	return (a * Power(b, m - 2, m)) % m;
}

// nCr mod 1000000007 を返す関数
ll ncr(int n, int r) {
	const long long M = 1000000007;

	// 手順 1: 分子 a を求める
	long long a = 1;
	for (int i = 1; i <= n; i++) a = (a * i) % M;

	// 手順 2: 分母 b を求める
	long long b = 1;
	for (int i = 1; i <= r; i++) b = (b * i) % M;
	for (int i = 1; i <= n - r; i++) b = (b * i) % M;

	// 手順 3: 答えを求める
	return Division(a, b, M);
}

/**
 * nCr(組み合わせ, combination)を求めるセット
 */
void solve() {
	ll H, W;
	cin >> H >> W;
	cout << ncr(H + W - 2, W - 1) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    solve();

    // テストケースが複数ある場合
    // int t;
    // cin >> t;
    // while (t--) {
    //     solve();
    // }
    return 0;
}