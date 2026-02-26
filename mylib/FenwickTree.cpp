#include <vector>
#include <cassert>

template <class T>
struct fenwick_tree {
    int _n;
    // 内部的には 1-indexed で管理するためサイズは n + 1
    std::vector<T> data;

    // コンストラクタ: 長さ n の配列を 0 で初期化
    fenwick_tree(int n) : _n(n), data(n + 1, 0) {}

    // a[p] += x を行う (p は 0-indexed)
    // 計算量: O(log N)
    void add(int p, T x) {
        assert(0 <= p && p < _n);
        p++; // 1-indexed に変換
        while (p <= _n) {
            data[p] += x;
            p += p & -p; // LSB (Least Significant Bit) を足す
        }
    }

    // 区間 [0, r) の和を求める (r は 0-indexed)
    // 計算量: O(log N)
    T sum(int r) const {
        assert(0 <= r && r <= _n);
        T s = 0;
        while (r > 0) {
            s += data[r];
            r -= r & -r; // LSB を引く
        }
        return s;
    }

    // 区間 [l, r) の和を求める (l, r は 0-indexed)
    // 計算量: O(log N)
    T sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }
};