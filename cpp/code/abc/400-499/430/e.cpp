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

#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using ull = unsigned long long;
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
using bint = cpp_int;

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

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
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

/**
 * ローリングハッシュ
 * - 乱数を2つ生成する(mt19937_64のとこ)
 * - コンストラクタに渡す(文字列, 長さ, 基準文字(英小文字のみ->'a', 数字->'0'), 基底1, 基底2)
 * 
 * - calcHash(begin, len) メソッドを使う
 *   - begin: 部分文字列の開始index(0-indexed)
 *   - len: 取得した部分文字列の長さ
 *   - 返り値: 2つの規定で計算されたハッシュ値のペア(pair<ull, ull>)
 * 
 * - 動的な文字の追加, 削除: 瞬時に全体のハッシュ値を更新する
 *  - rh.addCharacter('!'); // 末尾に '!' を追加 ("abracadabra!"
 *  - rh.eraseCharacter();  // 末尾の1文字を削除 ("abracadabra" に戻る)
 * 
 * https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
 */
void solve(){
    string a,b;
    cin >> a >> b;
    a += a;
    int n = b.size();

    mt19937_64 gen(random_device{}());
    uniform_int_distribution<ull> rm(2, 1e18);
    ull r1 = rm(gen); ull r2 = rm(gen);

    RollingHash rhA(a, a.size(), '0', r1, r2);
    RollingHash rhB(b, b.size(), '0', r1, r2);

    for(int i = 0; i < n; i++){
        if(rhA.calcHash(i, n) == rhB.calcHash(0, n)){
            cout << i << '\n';
            return;
        }
    }

    cout << -1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    // solve();

    // テストケースが複数ある場合
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}