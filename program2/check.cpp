// compile: make check
// run: ./check mem.in mem.out
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

int32_t main(int32_t argc, char *argv[]) {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    string mem_in = string(argv[1]), mem_out = string(argv[2]);
    ifstream fina(mem_in), finb(mem_out);
    for (int i = 0; i < 30; i += 2) {
        string t, a, b;
        fina >> a;
        finb >> t; finb >> b;
        fina >> t; a = t + a;
        finb >> t; finb >> t; b = t + b;
        stringstream ss(b); uint x; ss >> hex >> x;
        b = bitset<16>(x).to_string();

        if (a[0] == '1') assert(b[0] == '1');
        else {
            assert(a.substr(0, 2) == b.substr(0, 2));
            assert(a.substr(5, 11) == b.substr(5, 11));
        }
    }

    return 0;
}