#pragma once
#include <bits/stdc++.h>

#define REP(I,X) for(ll I = 0; I < static_cast<ll>(X); ++I)
#define REP1(I,X) for(ll I = 1; I <= static_cast<ll>(X); ++I)
#define REPn(I,X) for(I = 0; I < static_cast<ll>(X); ++I)
#define ITR(IT,X) for(auto IT = X.begin(); IT != X.end(); ++IT)
#define ALL(X) X.begin(),X.end()
using LLint = long long;
using uint = unsigned int;
using ll = int64_t;
using ull = uint64_t;
using namespace std;
constexpr const int Intmax = INT_MAX;
constexpr const ll Llmax = INT64_MAX;
constexpr const char SPACE = ' ';
constexpr const char TAB = '\t';
constexpr const char NL = '\n';
auto fout = ofstream(R"(C:\Users\Yuuki\source\repos\AtCoder\out.txt)");
auto fin = ifstream(R"(C:\Users\Yuuki\source\repos\AtCoder\in.txt)");
//auto& fout = cout;
//auto& fin = cin;
inline constexpr static ll divdown(ll a, ll b) { return 0 <= a ? a / b : (a + 1) / b + (0 < b ? -1 : 1); }
inline constexpr static ll pardown(ll a, ll b) { return a - b * divdown(a, b); }
inline constexpr static ll divup(ll a, ll b) { return divdown(a + (0 < b ? b : -b) - 1, b); }
inline constexpr static ll parup(ll a, ll b) { return a - b * divup(a, b); }
inline static constexpr bool bit(ull x, ull p) { return ((x >> p) & 1) == 1; };
inline static constexpr ll ctoi(char c) { return ll(c) - '0'; };
inline static constexpr char itoc(ll x) { return char(x + '0'); };
template<typename T>
bool chmin(T& a, const T& b) { return (b < a ? a = b, true : false); }
template<typename T>
bool chmax(T& a, const T& b) { return (a < b ? a = b, true : false); }