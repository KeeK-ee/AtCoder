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
const int MOD = 1000000007;
const string LOWALP = "abcdefghijklmnopqrstuvwxyz";
const string UPALP = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

#define rep(i, a, n) for (int i = a; i < (int)(n); ++i)
#define rrep(i, a, n) for (int i = (int)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}


bool is_pal(const string& s) {
    for (size_t i = 0, j = s.size() ? s.size() - 1 : 0; i < j; ++i, --j) {
        if (s[i] != s[j]) return false;
    }
    return true;
}

/**
 * 進数変換と回文
 * 回文は前が決まれば後ろが決まるからN以下の10進回文数はsqrt(N)で列挙できる
 * あとは変換して回文か判定する
 */
void solve() {
    ll A, N; cin >> A >> N;

    auto ltoA = [&](ll x) -> string {
        string res="";
        while(x > 0){
            res = (char)(x%A + '0') + res;
            x /= A;
        }
        return res;
    };

    ll ans=0;
    // 1桁
    rep(i, 1, 10){
        if(i>N) break;
        else if(is_pal(ltoA(i))) ans += i;
    }

    // 偶数桁
    rep(i, 1, 999999+1){
        string k = to_string(i);
        string rk = k;
        reverse(all(rk));
        k = k + rk;
        ll a = stoll(k);
        if(a>N) break;
        string b = ltoA(a);
        if(is_pal(b)) ans += a;
    }

    // 奇数桁
    rep(i, 1, 99999+1){
        rep(j, 0, 10){
            string k = to_string(i);
            string rk = k;
            reverse(all(rk));
            k = k + to_string(j) + rk;
            ll a = stoll(k);
            if(a>N) break;
            string b = ltoA(a);
            if(is_pal(b)) ans += a;
        }
    }
    out(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}