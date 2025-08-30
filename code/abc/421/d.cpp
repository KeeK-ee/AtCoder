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

// 座標の更新
void update(ll &x, ll &y, char d, ll dist) {
    if(d=='L') x -= dist;
    else if(d=='R') x += dist;
    else if(d=='U') y += dist;
    else if(d=='D') y -= dist;
}

void solve() {
    ll rt, ct, ra, ca;
    cin >> rt >> ct >> ra >> ca;
    ll N, M, L;
    cin >> N >> M >> L;
    vector<pair<char, ll>> S(M), T(L);
    rep(i, 0, M) cin >> S[i].first >> S[i].second;
    rep(i, 0, L) cin >> T[i].first >> T[i].second;
    ll ans=0;

    //ここから
    ll tx=ct, ty=-rt, ax=ca, ay=-ra;
    ll Sidx=0, Tidx=0;
    while(Sidx<M && Tidx<L){
        //同じスタート地点
        if(tx==ax && ty==ay){
            //同じ方向
            if(S[Sidx].first==T[Tidx].first){
                if(S[Sidx].second > T[Tidx].second){
                    ans += T[Tidx].second;
                    update(tx, ty, S[Sidx].first, T[Tidx].second);
                    update(ax, ay, T[Tidx].first, T[Tidx].second);
                    S[Sidx].second -= T[Tidx].second;
                    Tidx++;
                }
                else if(S[Sidx].second < T[Tidx].second){
                    ans += S[Sidx].second;
                    update(tx, ty, S[Sidx].first, S[Sidx].second);
                    update(ax, ay, T[Tidx].first, S[Sidx].second);
                    T[Tidx].second -= S[Sidx].second;
                    Sidx++;
                }
                else{
                    ans += S[Sidx].second;
                    update(tx, ty, S[Sidx].first, S[Sidx].second);
                    update(ax, ay, T[Tidx].first, T[Tidx].second);
                    Sidx++;
                    Tidx++;
                }
            }
            //違う方向
            else{
                if(S[Sidx].second > T[Tidx].second){
                    update(tx, ty, S[Sidx].first, T[Tidx].second);
                    update(ax, ay, T[Tidx].first, T[Tidx].second);
                    S[Sidx].second -= T[Tidx].second;
                    Tidx++;
                }
                else if(S[Sidx].second < T[Tidx].second){
                    update(tx, ty, S[Sidx].first, S[Sidx].second);
                    update(ax, ay, T[Tidx].first, S[Sidx].second);
                    T[Tidx].second -= S[Sidx].second;
                    Sidx++;
                }
                else{
                    update(tx, ty, S[Sidx].first, S[Sidx].second);
                    update(ax, ay, T[Tidx].first, T[Tidx].second);
                    Sidx++;
                    Tidx++;
                }
            }
        }
        //違うスタート地点
        else{
            //同じ方向
            if(S[Sidx].first == T[Tidx].first){
                if(S[Sidx].second > T[Tidx].second){
                    update(tx, ty, S[Sidx].first, T[Tidx].second);
                    update(ax, ay, T[Tidx].first, T[Tidx].second);
                    S[Sidx].second -= T[Tidx].second;
                    Tidx++;
                }
                else if(S[Sidx].second < T[Tidx].second){
                    update(tx, ty, S[Sidx].first, S[Sidx].second);
                    update(ax, ay, T[Tidx].first, S[Sidx].second);
                    T[Tidx].second -= S[Sidx].second;
                    Sidx++;
                }
                else{
                    update(tx, ty, S[Sidx].first, S[Sidx].second);
                    update(ax, ay, T[Tidx].first, T[Tidx].second);
                    Sidx++;
                    Tidx++;
                }
            }
            //違う方向
            else{
                //互いに近づく場合
    
            }
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