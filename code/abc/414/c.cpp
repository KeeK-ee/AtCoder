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

int A;

bool isPal(string st){
    //st（10進法）A進法で回文かどうか判定
    ll llst = stoi(st);
    
}

void solve() {
    ll N;
    cin >> A >> N;
    ll ans=0;
    //N以下で10進数でもA進数でも回文のものの総和
    //10進回文数を全探索する
    //偶数桁
    rep(i, 1, 1e6+1){
        string sti = to_string(i);
        reverse(all(sti));
        string pal = to_string(i) + sti;
        if(isPal(pal) && stoi(pal)<=N)ans+=stoi(pal);
    }
    //奇数桁
    rep(i, 1, 1e6+1){
        rep(j, 0, 10){
            string sti = to_string(i);
            reverse(all(sti));
            string pal = to_string(i) + to_string(j) + sti;
            if(isPal(pal) && stoi(pal)<=N)ans+=stoi(pal);
        }
    }
    out(ans);
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