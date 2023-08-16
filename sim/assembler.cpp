// compile: make assembler
// run: ./assembler -o ../program2/source.bin ../program2/source.s
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

vector<string> orig, inst, machine;
vector<bitset<8>> data_bss;
map<string, int> bss, label;

bitset<4> r2b(const string &s) {
    if (s[0] == 'r') return bitset<4>(stoi(s.substr(1)));
    if (s == "pc") return bitset<4>(15);
    if (s == "lr") return bitset<4>(13);
    if (s == "sp") return bitset<4>(12);
    if (s == "fp") return bitset<4>(11);
    assert(false);
}

bool is_imm(const string &s) {
    return (s[0] >= '0' && s[0] <= '9') || (s[0] == '+') || (s[0] == '-');
}

bitset<8> i2b8(const string &input) {
    int value;
    if (input.substr(0, 2) == "0x") std::istringstream(input.substr(2)) >> std::hex >> value;
    else if (input.substr(0, 2) == "0b") {
        std::bitset<8> binValue;
        std::istringstream(input.substr(2)) >> binValue;
        value = static_cast<int>(binValue.to_ulong());
    }
    else value = std::stoi(input);
    return std::bitset<8>(value);
}

bitset<5> i2b5(const string &input) {
    int value;
    if (input.substr(0, 2) == "0x") std::istringstream(input.substr(2)) >> std::hex >> value;
    else if (input.substr(0, 2) == "0b") {
        std::bitset<8> binValue;
        std::istringstream(input.substr(2)) >> binValue;
        value = static_cast<int>(binValue.to_ulong());
    }
    else value = std::stoi(input);
    return std::bitset<5>(value);
}

void preprocessing() {
    auto trim = [](string &s) {
        auto start = std::find_if_not(s.begin(), s.end(), ::isspace);
        auto end = std::find_if_not(s.rbegin(), s.rend(), ::isspace).base();
        return (start < end) ? std::string(start, end) : std::string();
    };
    auto replace = [](string &s, const string &oldWord, const string &newWord) {
        std::regex pattern("\\b" + oldWord + "\\b");
        return std::regex_replace(s, pattern, newWord);
    };
    map<string, string> macros;
    for (int i = 0; i < sz(orig); ) {
        orig[i] = orig[i].substr(0, orig[i].find("//"));
        orig[i] = trim(orig[i]);
        for (auto [k, v]: macros) orig[i] = replace(orig[i], k, v);
        istringstream iss(orig[i]);
        string ts;
        iss >> ts;
        if (ts == "#define") {
            string key, value; iss >> key >> value;
            macros[key] = value;
            orig.erase(orig.begin() + i, orig.begin() + i + 1);
            continue;
        }
        if (orig[i].empty()) {
            orig.erase(orig.begin() + i);
            continue;
        }
        auto pos = orig[i].find(':');
        if (pos != string::npos) {
            string nextline = orig[i].substr(orig[i].find(':') + 1);
            orig.insert(orig.begin() + i + 1, nextline);
            orig[i] = orig[i].substr(0, orig[i].find(':') + 1);
        }
        ++i;
    }
    for (int i = 0, idx = 1; i < sz(orig); ) {
        if (orig[i].find(':') != string::npos && orig[i][0] != '.') {
            string l = orig[i].substr(0, orig[i].find(':'));
            bitset<8> n = i2b8(orig[i+1]);
            bss[l] = idx++;
            data_bss.emplace_back(n);
            orig.erase(orig.begin() + i, orig.begin() + i + 2);
            continue;
        }
        ++i;
    }
}

void assembling() {
    auto trim = [](string s) {
        auto start = std::find_if_not(s.begin(), s.end(), ::isspace);
        auto end = std::find_if_not(s.rbegin(), s.rend(), ::isspace).base();
        return (start < end) ? std::string(start, end) : std::string();
    };
    auto opcode = [](string s, bool I) -> string {
        if (s == "add" && !I) return "00000";
        else if (s == "sub" && !I) return "00001";
        else if (s == "or" && !I) return "00010";
        else if (s == "and" && !I) return "00011";
        else if (s == "mvf" && !I) return "00100";
        else if (s == "mvt" && !I) return "00101";
        else if (s == "xor" && !I) return "00110";
        else if (s == "prt" && !I) return "00111";
        else if (s == "ldr" && !I) return "01000";
        else if (s == "str" && !I) return "01001";
        else if (s == "ceq" && !I) return "01010";
        else if (s == "clt" && !I) return "01011";
        else if (s == "norr" && !I) return "01100";
        else if (s == "b" && !I) return "01101";
        else if (s == "bt" && !I) return "01110";
        else if (s == "lsl" && !I) return "01111";
        else if (s == "add" && I) return "1000";
        else if (s == "sub" && I) return "1001";
        else if (s == "or" && I) return "1010";
        else if (s == "and" && I) return "1011";
        else if (s == "lsl" && I) return "1100";
        else if (s == "lsr" && I) return "1101";
        else if (s == "mov" && I) return "1110";
        else if (s == "xor" && I) return "1111";
        // debug(s, I)
        assert(false);
    };
    auto machinecode = [&](string s) -> string {
        istringstream iss(s);
        string op, rn; iss >> op >> rn;
        string result = opcode(op, is_imm(rn));
        // debug(rn)
        if (is_imm(rn)) result += i2b5(rn).to_string();
        else result += r2b(rn).to_string();
        return result;
    };
    if (!bss.empty()) {
        inst.emplace_back("mov 3");
        inst.emplace_back("lsl 5");
        inst.emplace_back("mvt r10");
    }
    for (int start = 0; start < sz(data_bss); start += 8) {
        int n = min(8LL, sz(data_bss) - start);
        inst.emplace_back("mvf r10");
        inst.emplace_back("add " + to_string(start + 1));
        inst.emplace_back("mvt r1");
        for (int i = start + 2; i < start + n + 1; ++i) {
            inst.emplace_back("add 1");
            inst.emplace_back("mvt r" + to_string(i - start));
        }
        for (int i = start; i < start + n; ++i) {
            inst.emplace_back("mov 0b" + data_bss[i].to_string().substr(0, 4));
            inst.emplace_back("lsl 4");
            inst.emplace_back("or 0b" + data_bss[i].to_string().substr(4, 4));
            inst.emplace_back("str r" + to_string(i - start + 1));
        }
    }
    vector<pair<string, int>> tmp;
    for (string &line: orig) {
        if (line[0] == '.') {
            string l = trim(line.substr(1, sz(line) - 2));
            label[l] = sz(inst);
            continue;
        }
        istringstream iss(line);
        string op, rn; iss >> op >> rn;
        if (op == "ldr" && rn[0] == '=') {
            bitset<8> idx = bss[rn.substr(1)];
            inst.emplace_back("mov 0b0" + idx.to_string().substr(0, 4));
            inst.emplace_back("lsl 4");
            inst.emplace_back("or 0b0" + idx.to_string().substr(4, 4));
            inst.emplace_back("add r10");
            inst.emplace_back("ldr r0");
            continue;
        }
        if (op[0] == 'b') {
            tmp.push_back({rn.substr(1), sz(inst)});
            inst.emplace_back("");
            inst.emplace_back("lsl 4");
            inst.emplace_back("");
            inst.emplace_back(op + " r0");
            continue;
        }
        inst.emplace_back(line);
    }
    for (auto [l, idx]: tmp) {
        bitset<8> offset = label[l] - idx - 3;
        inst[idx] = "mov 0b0" + offset.to_string().substr(0, 4);
        inst[idx+2] = "or 0b0" + offset.to_string().substr(4, 4);
    }
    for (string &line: inst) machine.emplace_back(machinecode(line));
}

int32_t main(int32_t argc, char *argv[]) {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    string exe_filename, source_filename;
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-o") {
            if (i+1 < argc) exe_filename = argv[++i];
            else {
                cerr << "error: no output filename" << endl;
                return 1;
            }
        }
        else source_filename = arg;
    }
    ifstream fin(source_filename);
    ofstream fout(exe_filename);

    for (string line; getline(fin, line); ) orig.emplace_back(line);
    preprocessing();
    assembling();
    for (int i = 0; i < sz(inst); ++i) cerr << hex << setw(2) << i << ": " << inst[i] << endl;
    for (auto &s: machine) fout << s << endl;

    fin.close(), fout.close();

    return 0;
}