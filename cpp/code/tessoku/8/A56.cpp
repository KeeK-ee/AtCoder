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
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
using mint = modint998244353;

const ll INF = 1e18;
const ll MOD = 998244353;
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

/**
 * ハッシュを計算する
 * 1. 文字列を数列に(a->1, b->2...(※0始まりはダメ))
 * 2. S[0.. i]のハッシュを計算(累積和みたいなノリ)
 * 3. b進法でハッシュを計算するとしてb^iを前計算(b=100なのはアルファベットが26個だから？)
 * 4. S[x, y]のハッシュ：S[0, y]のハッシュ - S[0, x]のハッシュ*b^(y-x+1)
 * ハッシュは巨大な数になるため大きい数でmodを取る(mint使う)
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, Q; cin >> N >> Q;
    string S; cin >> S;

    vl T(N); //Sを数字に変換a->1, b->2...
    rep(i, 0, N) T[i] = (S[i]-'a')+1;

    vector<mint> U(N); // U[i]: S[0, i]のハッシュ値
    U[0]=T[0];
    rep(i, 1, N) U[i]=(U[i-1]*100)+T[i];

    vector<mint> B(N+1); // B[i]=100^iのmod998
    B[0]=1;
    rep(i, 1, N+1) B[i] = B[i-1]*100;

    auto h = [&](ll x, ll y) -> mint {
        //S[x, y]のハッシュをmod998で計算する
        mint res = 0;
        if(x-1<0) res = U[y];
        else res = U[y] - U[x-1]*B[y-x+1];
        return res.val();
    };

    rep(i, 0, Q){
        ll a, b, c, d; cin >> a >> b >> c >> d;
        a--; b--; c--; d--;
        if(h(a, b).val()==h(c, d).val()) Yes;
        else No;
    }
}

using ull = unsigned long long;
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


/**
 * ロリハ
 */
void solve2(){
    ll N, Q; cin >> N >> Q;
    string S; cin >> S;

    mt19937_64 gen(random_device{}());
    uniform_int_distribution<ull> rm(2, 1e18);
    ull r1 = rm(gen); ull r2 = rm(gen);
    RollingHash rhS(S, sz(S), 'a', r1, r2);

    rep(qi, 0, Q){
        ll a, b, c, d; cin >> a >> b >> c >> d;
        a--; b--; c--; d--;
        if(rhS.calcHash(a, b-a+1)==rhS.calcHash(c, d-c+1)) Yes;
        else No;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    solve2();

    // テストケースが複数ある場合
    // int t;
    // cin >> t;
    // while (t--) {
    //     solve();
    // }
    return 0;
}