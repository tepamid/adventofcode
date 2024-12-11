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


size_t spliti(const std::string &txt, std::vector<int> &a, char ch)
{
    std::vector<std::string> strs;

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

    a.resize(strs.size());
    transform(strs.begin(), strs.end(), a.begin(), [](const string& w) { return stoi(w); });
    return a.size();
}

map<pair<ll,int>, ll> cache;

ll solve(ll x, int ntry) {
    if (!ntry) return 1;
    ntry--;
    if (cache.find({x,ntry}) != cache.end()) {
        return cache[{x, ntry}];
    }

    assert (x >= 0);

    ll ans = 0;

    auto s = to_string(x);
    if (x == 0) {
        ans = solve(1, ntry);
    } else if (s.size() % 2 == 0) { 
        auto s1 = s.substr(0, s.size()/2);
        auto s2 = s.substr(s.size()/2);
        ans = solve(stoll(s1), ntry) + solve(stoll(s2), ntry);
    } else {
        ans = solve(x*2024, ntry);
    }

    cache[{x, ntry}] = ans;
    return ans;
}

ll solve(const string& s, int ntry) {
    // cerr << s << endl;

    ll ans = 0;
    vector<int> a;
    spliti(s, a, ' ');

    for(auto x : a) {
        // cerr << " x = " << x << endl;
        ans += solve(x, ntry);
    }
    return ans;
}

void one () {
    ll ans = 0;

    string s;
    getline(cin, s);
    
    ans += solve(s, 75);

    cout << ans << endl;
}
