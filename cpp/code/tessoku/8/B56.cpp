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

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using ull = unsigned long long;
using int128 = __int128_t;
using ld = long double;
using pll = pair<ll, ll>;
template <typename T> using Vec = vector<T>;
using mint = modint998244353;

const ll INF = 8'000'000'000'000'000'000LL; // 8*10^18
const ll MOD = 998244353;
const ld pi = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
const int dy8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx8[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const string dir = "URDL";

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(15)

ll ceilDiv (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floorDiv (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

template <typename T> using pq = priority_queue<T>;
template <typename T> using pq_min = priority_queue<T, vector<T>, greater<T>>; //小さい順

ll llpow(ll a, ll b) {
    ll res=1;
    rep(i, 0, b) res*=a;
    return res;
}

template <typename T>
void debug_print(const vector<T>& v) {
    for (int i = 0; i < (int)v.size(); ++i) {
        cerr << v[i] << (i == (int)v.size() - 1 ? "" : " ");
    }
    cerr << "\n";
}
template <typename T>
void debug_print(const vector<vector<T>>& v) {
    for (const auto& row : v) {
        debug_print(row);
    }
}

template<class T>
bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T>
bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

// 文字列 s の任意の連続部分文字列に対して、その RollingHash値 を返す構造体
struct RollingHash{
private:
    const ull INF = numeric_limits<ull>::max();
    const ull MASK30 = (1ULL << 30) - 1;
    const ull MASK31 = (1ULL << 31) - 1;
    const ull MASK61 = (1ULL << 61) - 1;
    const ull hashMint = MASK61;
    char baseCharacter;
    int stringLength;
    ull base1 = 998244353;
    ull base2 = 1000000007;
    vector<ull> powerBase1, powerBase2;
    vector<pair<ull, ull>> rHash;

    ull Mul(ull a, ull b){ // (a * b) % hashMint
        ull xa = a >> 31;
        ull ya = a & MASK31;
        ull xb = b >> 31;
        ull yb = b & MASK31;
        ull Ma = (xa * yb + ya * xb) >> 30;
        ull Mb = (xa * yb + ya * xb) & MASK30;

        return (2 * xa * xb + Ma + (Mb << 31) + ya * yb) % hashMint;
    }

    ull Sub(ull a, ull b){ // (a - b) % hashMint
        return (a + hashMint - b) % hashMint;
    }

    void build(string &s){
        powerBase1[0] = 1;
        powerBase2[0] = 1;
        for(int i = 1; i < stringLength + 1; i++){
            powerBase1[i] = Mul(powerBase1[i - 1], base1);
            powerBase2[i] = Mul(powerBase2[i - 1], base2);
        }

        rHash[0] = make_pair(0ULL, 0ULL);
        for(int i = 0; i < stringLength; i++){
            rHash[i + 1].first = (Mul(rHash[i].first, base1) + s[i] - baseCharacter + 1) % hashMint;
            rHash[i + 1].second = (Mul(rHash[i].second, base2) + s[i] - baseCharacter + 1) % hashMint;
        }

        return;
    };
public:
    RollingHash(){}
    RollingHash(string &s, int n, char c){ // s: 文字列, n: 文字列の長さ, c: 使われている文字の中でASCIIの値が一番小さいもの(英小文字なら 'a', 英大文字なら 'A')
        stringLength = n;
        baseCharacter = c;
        rHash.resize(stringLength + 1);
        powerBase1.resize(stringLength + 1);
        powerBase2.resize(stringLength + 1);
        build(s);
    }
    RollingHash(string &s, int n, char c, ull r1, ull r2){ // r1, r2: 任意の基底(2 <= r1, r2 <= 2^61 - 3) (デフォルトの値: r1 = 998244353, r2 = 1000000007)
        stringLength = n;
        baseCharacter = c;
        base1 = r1; base2 = r2;
        rHash.resize(stringLength + 1);
        powerBase1.resize(stringLength + 1);
        powerBase2.resize(stringLength + 1);
        build(s);
    }

    pair<ull, ull> calcHash(int begin, int len){ // begin から始まる len 文字の部分文字列のハッシュ値を返す(begin: 0-index)
        if(begin + len > stringLength){ // begin + len が文字列 s の長さを超えていたらINFを返す
            return make_pair(INF, INF);
        }
        else{
            ull hash1 = Sub(rHash[begin + len].first, Mul(rHash[begin].first, powerBase1[len]));
            ull hash2 = Sub(rHash[begin + len].second, Mul(rHash[begin].second, powerBase2[len]));
            return make_pair(hash1, hash2);
        }
    }

    void addCharacter(char c){ // 末尾に文字 c を追加する
        powerBase1.push_back(Mul(powerBase1[stringLength], base1));
        powerBase2.push_back(Mul(powerBase2[stringLength], base2));

        ull hash1 = (Mul(rHash[stringLength].first, base1) + c - baseCharacter + 1) % hashMint;
        ull hash2 = (Mul(rHash[stringLength].second, base2) + c - baseCharacter + 1) % hashMint;
        rHash.push_back({hash1, hash2});

        stringLength++;

        return;
    }

    void eraseCharacter(){ // 末尾の文字を消去する
        if(stringLength == 0) return;

        powerBase1.pop_back();
        powerBase2.pop_back();
        rHash.pop_back();
        stringLength--;

        return;
    }
};


void solve() {
    ll N, Q; cin >> N >> Q;
    string S; cin >> S;
    string rS=S;
    reverse(all(rS));

    mt19937_64 gen(random_device{}());
    uniform_int_distribution<ull> rm(2, 1e18);
    ull r1 = rm(gen); ull r2 = rm(gen);
    RollingHash rhS(S, sz(S), 'a', r1, r2);
    RollingHash rhrS(rS, sz(rS), 'a', r1, r2);

    rep(qi, 0, Q){
        ll l, r; cin >> l >> r; l--; r--;
        if((r-l+1)%2){
            // 奇数長
            if(rhS.calcHash(l, (r-l)/2)==rhrS.calcHash(N-r-1, (r-l)/2)) Yes;
            else No;
        }
        else{
            // 偶数長
            if(rhS.calcHash(l, (r-l+1)/2)==rhrS.calcHash(N-r-1, (r-l+1)/2)) Yes;
            else No;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}