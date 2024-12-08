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

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while (pos != std::string::npos)
    {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    // Add the last one
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs.size();
}

ll concatenation(ll x, ll y) {
    ll pp=1;
    ll z = y;
    while(z>0) {
        z/=10;
        pp*=10;
    }

    return x*pp + y;
}

ll solve(ll res, const vector<ll>& a) {
    unordered_set<ll> dp;
    dp.insert(0);
    for(auto x : a) {
        unordered_set<ll> dp2;

        for(auto p:dp) {
            for(auto y : {p+x, p*x, concatenation(p,x)}) {
                if (y <= res) { 
                    dp2.insert(y);
                }
            }
        }

        dp = dp2;
    }

    for(auto p:dp) {
        if (res==p) return p;
    }

    return 0;
}

void one () {
    ll ans = 0;

    string s;
    while(getline(cin, s)) {
        auto i = find(begin(s), end(s), ':') - s.begin();

        auto ssr = s.substr(0,i);
        auto res = stoll(ssr);
        auto ss = s.substr(i+2);
        
        vector<string> ws;
        split(ss, ws, ' ');
        
        vector<ll> a(ws.size());
        transform(ws.begin(), ws.end(), a.begin(), [](const string& w) { return stoll(w); });
        ans += solve(res, a);
    }

    cout << ans << endl;
}
