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

#define fo(i, n) for (int i = 0; i < n; ++i)

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

ll solve(const string& s, const vector<int>& a) {
    int n = s.size();
    vector<ll> dp(n+1);
    dp[0] = 1;

    for(auto x : a) {
        vector<ll> dp2(n+1);

        for(int pi=0; pi<n; pi++) {
            for(int startI=pi == 0 ? pi : pi+1; startI<n; startI++) {
                {
                    bool ok = true;
                    for(int j=pi; j<startI; j++) {
                        if (s[j] == '#') {
                            ok = false;
                            break;
                        }
                    }
                    if (!ok) break;
                }

                if (startI + x > n) break;

                bool ok = true;
                for(int j=0; j<x; j++) {
                    if (s[startI+j] == '.') {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    dp2[startI+x] 
                        += dp[pi];
                }
            }
        }

        dp = dp2;
    }
    
    ll ans=dp[n];
    for(int i=n-1; i>=0; i--) {
        if (s[i] == '#') break;
        ans += dp[i];
    }
    return ans;
}

void one () {
    ll ans=0;

    string ss;
    while(getline(cin, ss)) {
        int ii = ss.find(' ');
        auto s = ss.substr(0, ii);

        vector<int> a;
        spliti(ss.substr(ii+1), a, ',');

        string s2;
        vector<int> a2;
        int ntimes = 5;
        while(ntimes--) {
            s2 += s;
            if (ntimes >= 1) s2 += '?';
            a2.insert(end(a2), begin(a), end(a));
        }

        auto cur = solve(s2, a2);

        ans += cur;
    }

    cout << ans << endl;
}
