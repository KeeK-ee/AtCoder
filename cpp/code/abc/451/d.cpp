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
#include <random>
using namespace std;

// #include <boost/multiprecision/cpp_int.hpp>
// using namespace boost::multiprecision;

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using ull = unsigned long long;
using int128 = __int128_t;
using ld = long double;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvpll = vector<vpll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;
using vc = vector<char>;
using vvc = vector<vc>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
using mint = modint998244353;
// using bint = cpp_int;

const ll INF = 8'000'000'000'000'000'000LL; // 8*10^18
const ll MOD = 998244353;
const ld pi = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
const int dy8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(15)
#define se second
#define fi first

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}
ll ceilDiv (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floorDiv (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

ll GetDigit(ll num){
	ll digit = 0;
	while(num != 0){
		num /= 10;
		digit++;
	}
	return digit;
}

/**
 * 1から順に見て良い整数かO(1)で判定できれば全探索可能(O(10^9)だが、、)
 * ->判定O(1)はしんどそう
 * 10^9以下だから高々9桁まで
 * 桁ごとに分類する　2冪を桁ごとのsetに入れて下の桁から1桁+i-1桁, 2桁+i-2桁というように
 * 1桁+1桁+i-2桁というパターンは考えなくてよい　なぜなら1桁+1桁の部分で2桁に存在するから
 * 計算量は見積もれない
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N; cin >> N;
    vector<set<string>> D(10);
    // 二冪
    rep(j, 0, 30){
        ll d=GetDigit((1<<j));
        if(d<=9) D[d].insert(to_string((1<<j)));
    }
    rep(i, 2, 10){
        // D[i]にinsertする
        rep(j, 1, i){
            // j桁+i-j桁
            for(auto p : D[j])for(auto q : D[i-j]){
                D[i].insert(p+q);
            }
        }
    }
    for(auto s : D){
        ll si=s.size();
        if(N<=si){
            ll i=1;
            for(auto k : s){
                if(N==i){
                    out(k); return;
                }
                else i++;
            }
        }
        else{
            N-=si; continue;
        }
    }
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