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

/**
 * やる
 */
void solve() {
    string S;
    cin >> S;
    double ans=0;
    rep(i, 1, sz(S)+1){
        //部分文字列はi文字
        rep(j, 0, sz(S)-i+1){
            //1文字目のindexはj
            //充填率を計算してansを更新
            double tmp;
            if(S[j]=='t' && S[j+i-1]=='t' && i>=3){
                int cnt=0;
                rep(k, j, j+i)if(S[k]=='t')cnt++;
                tmp = (double)(cnt-2)/(double)(i-2);
            }
            else {
                continue;
            }
            chmax(ans, tmp);
        }
    }
    cout << fixed << setprecision(15);
    out(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    solve();

    // テストケースが複数ある場合 (コメントアウトを外して使用)
    /*
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    */
    return 0;
}