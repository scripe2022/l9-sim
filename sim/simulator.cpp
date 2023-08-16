// compile: make simulator
// run: ./simulator ../program3/source.bin --mem ../program3/mem.in
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
#define MAXN 512

bitset<8> operator+(bitset<8> a, bitset<8> b) {
    bitset<8> c = 0, s;
    for (int i = 0; i < 8; ++i) {
        s[i] = a[i] ^ b[i] ^ c[i];
        c[i + 1] = (a[i] & b[i]) | (a[i] & c[i]) | (b[i] & c[i]);
    }
    return s;
}

bitset<8> operator-(bitset<8> a, bitset<8> b) {
    bitset<8> c = 1, s;
    b = ~b;
    for (int i = 0; i < 8; ++i) {
        s[i] = a[i] ^ b[i] ^ c[i];
        c[i + 1] = (a[i] & b[i]) | (a[i] & c[i]) | (b[i] & c[i]);
    }
    return s;
}

bitset<8> operator<<(bitset<8> a, bitset<8> b) {
    int num = b.to_ullong();
    return a << num;
}

uint n = 0;
vector<bitset<9>> inst(MAXN);
vector<bitset<8>> r(16), mem(MAXN);

void ADD(int rn) {r[0] = r[0] + r[rn]; r[15] = r[15] + 1; }
void SUB(int rn) {r[0] = r[0] - r[rn]; r[15] = r[15] + 1; }
void MVF(int rn) {r[0] = r[rn]; r[15] = r[15] + 1; }
void MVT(int rn) {r[rn] = r[0]; r[15] = r[15] + 1; }
void OR(int rn) {r[0] = r[0] | r[rn]; r[15] = r[15] + 1; }
void AND(int rn) {r[0] = r[0] & r[rn]; r[15] = r[15] + 1; }
void XOR(int rn) {r[0] = r[0] ^ r[rn]; r[15] = r[15] + 1; }
void PRT(int rn) {r[0] = r[rn].count() & 1; r[15] = r[15] + 1; }
void LDR(int rn) {r[0] = mem[r[rn].to_ullong()]; r[15] = r[15] + 1; }
void STR(int rn) {mem[r[rn].to_ullong()] = r[0]; r[15] = r[15] + 1; }
void CEQ(int rn) {r[14] = (r[0] == r[rn]) ? 1 : 0; r[15] = r[15] + 1; }
void CLT(int rn) {r[14] = (r[0] - r[rn]).test(7); r[15] = r[15] + 1; }
// void CLE(int rn) {r[14] = ((r[0] - r[rn]).test(7) || (r[0] == r[rn])) ? 1 : 0; r[15] = r[15] + 1; }
void NORR(int rn) {r[0] = (r[rn] == 0) ? 1 : 0; r[15] = r[15] + 1; }
void B(int rn) {r[15] = r[15] + r[rn]; }
void BT(int rn) {r[15] = r[14].test(0) ? (r[15] + r[rn]) : (r[15] + 1); }
// void BF(int rn) {r[15] = (!r[14].test(0)) ? (r[15] + r[rn]) : (r[15] + 1); }
void LSL(int rn) {r[0] = r[0] << r[rn] ; r[15] = r[15] + 1; }

void ADDI(bitset<8> imm) {r[0] = r[0] + imm; r[15] = r[15] + 1; }
void SUBI(bitset<8> imm) {r[0] = r[0] - imm; r[15] = r[15] + 1; }
void ORI(bitset<8> imm) {r[0] = r[0] | imm; r[15] = r[15] + 1; }
void ANDI(bitset<8> imm) {r[0] = r[0] & imm; r[15] = r[15] + 1; }
void LSLI(bitset<8> imm) {r[0] = r[0] << imm.to_ullong(); r[15] = r[15] + 1; }
void LSRI(bitset<8> imm) {r[0] = r[0] >> imm.to_ullong(); r[15] = r[15] + 1; }
void MVI(bitset<8> imm) {r[0] = imm; r[15] = r[15] + 1; }
void XORI(bitset<8> imm) {r[0] = r[0] ^ imm; r[15] = r[15] + 1; }
// void BI(bitset<8> imm) {r[15] = r[15] + imm; }

void read(string fn) {
    if (fn == "") {
        fill(mem.begin(), mem.end(), bitset<8>(0));
        return;
    }
    ifstream f(fn);
    for (int it = 0; it < 60; ++it) {
        string ch; f >> ch;
        mem[it] = stoi(ch, nullptr, 2);
    }
}

void write() {
    for (int i = 0; i < 60; ++i) {
        auto num = mem[i].to_ullong();
        printf("%lld: %02x\n", i, (unsigned char)num);
    }
}

void DEBUG(int reg) {
    stringstream res; res << hex << r[reg].to_ullong();
    debug(reg, r[reg], res.str(), r[reg].to_ullong());
    r[15] = r[15] + 1;
}

int32_t main(int32_t argc, char *argv[]) {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    string mem_filename = "", source_filename = "";
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--mem") {
            if (i+1 < argc) mem_filename = argv[++i];
            else {
                cerr << "error: no mem file" << endl;
                return 1;
            }
        }
        else source_filename = arg;
    }
    assert(source_filename != "");
    read(mem_filename);
    ifstream fin(source_filename);
    for (string line; getline(fin, line); ++n) {
        assert(line.size() == 9);
        inst[n] = bitset<9>(line);
    }
    // int cnt = 0;
    for (r[15] = 0; r[15].to_ullong() < n; ) {
        // debug(r[15].to_ullong(), r[8].to_ullong(), r[0].to_ullong())
        // if (cnt++ > 400) break;
        bitset<9> &i = inst[r[15].to_ullong()];
        if (i[8] == 0) {
            int opcode = i.to_ullong() >> 4;
            int rn = i.to_ullong() & 0b1111;
            switch (opcode) {
                case 0b00000:
                    ADD(rn);
                    break;
                case 0b00001:
                    SUB(rn);
                    break;
                case 0b00010:
                    OR(rn);
                    break;
                case 0b00011:
                    AND(rn);
                    break;
                case 0b00100:
                    MVF(rn);
                    break;
                case 0b00101:
                    MVT(rn);
                    break;
                case 0b00110:
                    XOR(rn);
                    break;
                case 0b00111:
                    PRT(rn);
                    break;
                case 0b01000:
                    LDR(rn);
                    break;
                case 0b01001:
                    STR(rn);
                    break;
                case 0b01010:
                    CEQ(rn);
                    break;
                case 0b01011:
                    CLT(rn);
                    break;
                case 0b01100:
                    NORR(rn);
                    break;
                case 0b01101:
                    B(rn);
                    break;
                case 0b01110:
                    BT(rn);
                    break;
                case 0b01111:
                    LSL(rn);
                    break;
            }
        }
        else if (i[8] == 1) {
            int opcode = i.to_ullong() >> 5;
            bitset<8> imm = (i.to_ullong() & 0b11111) | (i.test(4) ? 0b11100000 : 0b00000000);
            bitset<8> uimm = (i.to_ullong() & 0b11111);
            switch (opcode) {
                case 0b1000:
                    ADDI(uimm);
                    break;
                case 0b1001:
                    SUBI(uimm);
                    break;
                case 0b1010:
                    ORI(uimm);
                    break;
                case 0b1011:
                    ANDI(uimm);
                    break;
                case 0b1100:
                    LSLI(uimm);
                    break;
                case 0b1101:
                    LSRI(uimm);
                    break;
                case 0b1110:
                    MVI(imm);
                    break;
                case 0b1111:
                    XORI(imm);
                    // DEBUG(i.to_ullong() & 0b1111);
                    break;
            }
        }
    }
    write();

    return 0;
}