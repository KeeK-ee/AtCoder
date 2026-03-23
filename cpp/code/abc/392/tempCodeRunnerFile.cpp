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

struct UnionFind {
    std::vector<int> parent_or_size;

    UnionFind(int n) : parent_or_size(n, -1) {}

    int leader(int a) {
        if (parent_or_size[a] < 0) {
            return a;
        }
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int merge(int a, int b) {
        int x = leader(a);
        int y = leader(b);
        if (x == y) return x;
        
        if (-parent_or_size[x] < -parent_or_size[y]) {
            std::swap(x, y);
        }
        
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    int size(int a) {
        return -parent_or_size[leader(a)];
    }

    std::vector<std::vector<int>> groups() {
        int n = parent_or_size.size();
        std::vector<int> leader_buf(n), group_size(n);
        for (int i = 0; i < n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        
        std::vector<std::vector<int>> result(n);
        for (int i = 0; i < n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        
        std::vector<std::vector<int>> final_result;
        for (int i = 0; i < n; i++) {
            if (!result[i].empty()) {
                final_result.push_back(std::move(result[i]));
            }
        }
        return final_result;
    }
};

void solve() {
    ll N, M; cin >> N >> M;
    dsu d(N);
    // extra: {ケーブル番号, 残す端, 引っこ抜く端}
    vector<tuple<int, int, int>> extra; 

    // 1. 余りケーブルの仕分け
    for (int i = 1; i <= M; i++) {
        ll u, v; cin >> u >> v;
        u--; v--; // 0-indexed
        if (d.same(u, v)) {
            // u を残して v を引っこ抜く、というルールで保存 (1-indexed)
            extra.push_back({i, u + 1, v + 1}); 
        } else {
            d.merge(u, v);
        }
    }

    // 2. 孤島の代表者をリストアップ
    vector<int> roots;
    for (int i = 0; i < N; i++) {
        if (d.leader(i) == i) roots.push_back(i + 1); // 1-indexed
    }

    // 3. 繋ぎ変えを出力
    int K = roots.size() - 1;
    cout << K << endl;
    for (int i = 0; i < K; i++) {
        auto [id, keep_node, remove_node] = extra[i];
        
        // id: ケーブル番号
        // remove_node: 引っこ抜く前のサーバー番号
        // roots[i + 1]: 繋ぎ変えた後のサーバー番号
        cout << id << " " << remove_node << " " << roots[i + 1] << "\n";
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