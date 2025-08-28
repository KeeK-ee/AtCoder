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

void solve() {
    int N, M;
    cin >> N >> M;
    vector<string> S(N);
    rep(i, 0, N) cin >> S[i];
    vector<int> A(N);//得点

    rep(i, 0, M){
        //i回目の投票において
        int cnt0=0;
        rep(j, 0, N){
            if(S[j][i]=='0') cnt0++;
        }
        if(cnt0==0 || cnt0==N){
            rep(j, 0, N) A[j]+=1;
        }
        else if(cnt0<N-cnt0){
            rep(j, 0, N){
                if(S[j][i]=='0') A[j]+=1;
            }
        }
        else{
            rep(j, 0, N){
                if(S[j][i]=='1') A[j]+=1;
            }
        }
    }
    int mx=0;
    rep(i, 0, N) chmax(mx, A[i]);
    rep(i, 0, N){
        if(A[i]==mx) cout << (i+1) << " ";
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