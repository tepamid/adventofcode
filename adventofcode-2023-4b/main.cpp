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

namespace {
    vector<pair<int, int> > dirs8 = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, 
        {1,1}, {1,-1}, {-1,1}, {-1,-1}
    };

    #define GET_NEIGHBOURS_8 for(auto [di,dj] : dirs8) { auto ni = i+di; auto nj = j+dj; if (ni<0 || nj<0 || ni >= n || nj >= m) continue; 
};

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

    // a.resize(strs.size());
    // transform(strs.begin(), strs.end(), a.begin(), [](const string& w) { cerr << w<<endl; return stoi(w); });
    for(auto w:strs){
        if (!w.empty()) {
            a.push_back(stoi(w));
        }
    }
    return a.size();
}

void one () {
    ll ans = 0;

    vector<string> a;
    {
        string s;
        while(getline(cin, s)) {
            a.push_back(s);
        }
    }

    vector<ll> cnt(a.size(), 1);

    for(int i=0; i<a.size(); i++)
    {
        auto s1 = a[i];
        auto s = s1.substr(s1.find(':')+2);

        vector<int> b,c;
        spliti(s.substr(0,s.find('|')), b, ' ');
        spliti(s.substr(s.find('|')+2), c, ' ');
        set<int> sb(begin(b), end(b));

        ll x = 0;
        for(auto y:c) {
            if (sb.find(y) != sb.end()) {
                x++;
            }
        }
        
        // if (x)
        {
            ans += cnt[i];
        }
        // cerr << cnt[i] << endl;

        int j=i+1;
        while(j<a.size() && x--) {
            cnt[j++] += cnt[i];
        }
    }

    cout << ans << endl;
}
