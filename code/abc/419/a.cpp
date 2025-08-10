#include <iostream>
#include <vector>
#include <numeric> // std::accumulate を使うために必要

int main() {
    // C++の標準入出力を高速化するための設定
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // 整数の個数 N を受け取る
    int n;
    std::cin >> n;

    // N個の整数を格納するためのvector(動的配列)を用意
    std::vector<int> a(n);

    // forループを使ってN個の整数を順番に受け取る
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // 合計値を格納する変数。オーバーフローを防ぐためlong long型で宣言
    long long sum = 0;

    // std::accumulate を使って vector a の全要素の合計を計算
    // 第3引数の 0LL は、計算を long long 型で行うための初期値
    sum = std::accumulate(a.begin(), a.end(), 0LL);

    // 計算結果を出力
    std::cout << sum << std::endl;

    return 0;
}