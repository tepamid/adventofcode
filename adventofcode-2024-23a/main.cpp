/**
 * Copyright (c) 2024 Dmitry Petukhov AKA tepamid
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void fastio()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
}

void one();

int main() {
    fastio();
    
    one();

    return 0;
}

int s2u(string& s) {
    int x=0;
    x ^= (s[0]-'a') << 5;
    x ^= s[1]-'a';
    return x;
}

bool startWithT(int x) {
    return (x>>5) == ('t' - 'a');
}

void read(string& s, int& u, int& v) {
    string a = s.substr(0,2);
    string b = s.substr(3);

    u = s2u(a);
    v = s2u(b);
}

void one () {
    ll ans = 0;

    unordered_map<int, unordered_set<int>> g;
    set<int> all;

    string s;
    while(getline(cin, s)) {
        if(s.empty()) break;
        
        int u,v;
        read(s,u,v);

        g[u].insert(v);
        g[v].insert(u);
        all.insert(u);
        all.insert(v);
    }

    for(auto u:all) {
        for(auto v : g[u])
        for(auto w : g[u]) {
            if (v==w) continue;

            if (g[v].count(w)) {
                if (startWithT(u) || startWithT(v) || startWithT(w)) {
                    ans++;
                }
            }
        }
    }

    cout << ans/6 << endl; // 6=3! is the number of permutations of 3 elements.
}
