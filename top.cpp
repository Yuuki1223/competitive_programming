#pragma once
#include <bits/stdc++.h>

#define REP(I,X) for(ll I = 0; I < static_cast<ll>(X); ++I)
#define REP1(I,X) for(ll I = 1; I <= static_cast<ll>(X); ++I)
#define REPn(I,X) for(I = 0; I < static_cast<ll>(X); ++I)
#define ITR(IT,X) for(auto IT = X.begin(); IT != X.end(); ++IT)
#define ALL(X) X.begin(),X.end()
using LLint = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using namespace std;
constexpr const int Intmax = INT32_MAX;
constexpr const ll Llmax = LLONG_MAX;
constexpr const char SPACE = ' ';
constexpr const char TAB = '\t';
constexpr const char NL = '\n';
auto fout = ofstream(R"(C:\Users\Yuuki\source\repos\AtCoder\out.txt)");
auto fin = ifstream(R"(C:\Users\Yuuki\source\repos\AtCoder\in.txt)");
inline constexpr ll divup(ll x, ll y) { return (x + y - 1) / y; };
inline constexpr bool bit(ull x, ll p) { return ((x >> p) & 1) == 1; };
inline constexpr ll ctoi(char c) { return ll(c) - '0'; };
inline constexpr char itoc(ll x) { return char(x + '0'); };
inline constexpr ll parup(ll x, ll y) { return ((x % y) + y) % y; };

template<typename T>
bool chmin(T& a, const T& b) { return (b < a ? a = b, true : false); }
template<typename T>
bool chmax(T& a, const T& b) { return (a < b ? a = b, true : false); }