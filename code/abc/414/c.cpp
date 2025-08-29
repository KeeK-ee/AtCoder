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

bool isPal(ll st){
    vl abase;
    while(st>0){
        abase.push_back(st%A);
        st/=A;
    }
    rep(i, 0, sz(abase)/2){
        if(abase[i]!=abase[sz(abase)-1-i])return false;
    }
    return true;
}

void solve() {
    ll N;
    cin >> A >> N;
    ll ans=0;
    //N以下で10進数でもA進数でも回文のものの総和
    //10進回文数を全探索する

    //1桁
    rep(i, 1, 10){
        if(i>N)break;
        if(isPal((ll)i))ans+=i;
    }
    
    //偶数桁
    rep(i, 1, 1e6){
        string sti = to_string(i);
        reverse(all(sti));
        string pal = to_string(i) + sti;
        ll palll = stoll(pal);
        if(palll>N)break;
        if(isPal(palll))ans+=palll;
    }
    //奇数桁
    rep(i, 1, 1e5){
        rep(j, 0, 10){
            string sti = to_string(i);
            reverse(all(sti));
            string pal = to_string(i) + to_string(j) + sti;
            ll palll = stoll(pal);
            if(palll>N)break;
            if(isPal(palll))ans+=palll;
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