// compile: g++ -o cpp cpp.cpp -DLOCAL
// run: ./cpp
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#ifdef LOCAL
#include <debug/codeforces.h>
#define debug(x...) _debug_print(#x, x);
#define Debug(x...) _debug_print_format(#x, x);
std::ifstream terminal("/dev/tty");
#define PP cerr<<"\033[1;30mpause...\e[0m",terminal.ignore();
#else
#define debug(x...)
#define Debug(x...)
#define PP
#endif
template<typename...Args> void print_(Args...args){((cout<<args<<" "),...)<<endl;}
#define rep(i,a,b) for(int i=(a);i<(int)(b);++i)
#define sz(v) ((int)(v).size())
#define print(...) print_(__VA_ARGS__);
#define FIND(a, x) ((find(a.begin(),a.end(),(x))!=a.end())?1:0)
#define cmin(x,...) x=min({(x),__VA_ARGS__})
#define cmax(x,...) x=max({(x),__VA_ARGS__})
#define INTMAX (int)(9223372036854775807)
#define INF (int)(1152921504606846976)
#define NaN (int)(0x8b88e1d0595d51d1)
#define double long double
#define int long long
#define uint unsigned long long
#define MAXN 200010
#define N 15
#define M 11

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    rep(i, 0, 1) {
        // string s; cin >> s;
        string s = "01011001101";
        vector<int> d(12);
        rep(i, 1, 12) d[i] = s[11-i] - '0';
        debug(d)
        int p8 = d[11] ^ d[10] ^ d[9] ^ d[8] ^ d[7] ^ d[6] ^ d[5];
        int p4 = d[11] ^ d[10] ^ d[9] ^ d[8] ^ d[4] ^ d[3] ^ d[2];
        int p2 = d[11] ^ d[10] ^ d[7] ^ d[6] ^ d[4] ^ d[3] ^ d[1];
        int p1 = d[11] ^ d[9] ^ d[7] ^ d[5] ^ d[4] ^ d[2] ^ d[1];
        int p0 = d[11] ^ d[10] ^ d[9] ^ d[8] ^ d[7] ^ d[6] ^ d[5] ^ d[4] ^ d[3] ^ d[2] ^ d[1] ^ p8 ^ p4 ^ p2 ^ p1;
        vector<int> high = {d[11], d[10], d[9], d[8], d[7], d[6], d[5], p8};
        vector<int> low = {d[4], d[3], d[2], p4, d[1], p2, p1, p0};
        int lowhex = 0, highhex = 0;
        rep(i, 0, 8) lowhex = lowhex * 2 + low[i];
        rep(i, 0, 8) highhex = highhex * 2 + high[i];
        debug(high, low)
        // cout << "low: " << std::setw(2) << std::setfill('0') << std::hex << lowhex << "    ";
        // cout << "high: " << std::setw(2) << std::setfill('0') << std::hex << highhex << endl;
        printf("%02llx %02llx\n", highhex, lowhex);
        // debug(high)
        // debug(low)
    }

    return 0;
}