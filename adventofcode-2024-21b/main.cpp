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

#define fo(i,n) for(int i=0; i<n; i++)

using namespace std;
typedef long long ll;

void fastio()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
}

void one();
void precalc();

int main() {
    fastio();
    precalc();
    one();
    return 0;
}

size_t split2(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while (pos != std::string::npos)
    {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 2;

        pos = txt.find(ch, initialPos);
    }

    // Add the last one
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs.size();
}

vector<string> dirkp = {
    "#^A",
    "<v>"
};

vector<string> numkp = {
    "789",
    "456",
    "123",
    "#0A"
};

vector<tuple<int,int,char> > dirs = {
    {0, 1, '>'},
    {-1, 0, '^'}, 
    {1, 0, 'v'},
    {0, -1, '<'},
};
map<char,pair<int,int>> ch2dir;

void setupDirs() {
    for(auto [di,dj,ch] : dirs) { 
        ch2dir[ch] = {di,dj};
    }
}

const int NUM_STEPS = 1+25;
const vector<string>& getMap(int iStep) {
    return iStep == 0 ? numkp : dirkp;
}

vector<char> getChars(int iStep) {
    auto a = getMap(iStep);
    int n = a.size();
    int m = a[0].size();

    vector<char> ans;
    fo(i,n) {
        fo(j,m) {
            if (a[i][j] != '#') ans.push_back(a[i][j]);
        }
    }
    return ans;
}

void locateChar(int iStep, char CH, int& si, int& sj) {
    auto a = getMap(iStep);

    int n = a.size();
    int m = a[0].size();

    fo(i,n) {
        fo(j,m) {
            if (a[i][j] == CH) {
                si=i;
                sj=j;
                return;
            }
        }
    }

    assert(false);
}


bool isValidPath(const string& t, int iStep, int si, int sj) {
    auto& a = getMap(iStep);

    int i = si;
    int j = sj;

    for(auto ch : t) {
        auto [di,dj] = ch2dir[ch];
        i+=di;
        j+=dj;
        if (a[i][j] == '#') return false;
    }
    return true;
};

map<pair<char,char>, ll> dp;
ll getPathCost(const string& path) {
    ll ans=0;
    char pch = 'A';
    for(auto ch : path) {
        ans += dp[{pch,ch}];
        pch = ch;
    }
    return ans;
}

ll getCost(int iStep, char c1, char c2) {
    ll ans = -1;

    int si=-1,sj=-1;
    int fi=-1,fj=-1;
    locateChar(iStep, c1, si, sj);
    locateChar(iStep, c2, fi, fj);
    assert(si>=0);
    assert(fi>=0);
    assert(sj>=0);
    assert(fj>=0);

    string res;
    int di = fi-si;
    int dj = fj-sj;

    if (di>=0) for(int i=0; i<di; i++) res+='v';
    else for(int i=0; i<-di; i++) res+='^';
    if (dj>=0) for(int i=0; i<dj; i++) res+='>';
    else for(int i=0; i<-dj; i++) res+='<';

    sort(begin(res), end(res));

    do {
        if (isValidPath(res, iStep, si, sj)) {
            auto cur = getPathCost(res + 'A');
            ans = ans < 0 ? cur : min(ans, cur);
        }

    } while(next_permutation(begin(res), end(res)));

    assert(ans>=0);

    return ans;

}

void precalc() {
    setupDirs();

    {
        auto chs = getChars(NUM_STEPS-1);
        for(auto c1:chs) {
            for(auto c2:chs) {
                dp[{c1,c2}] = 1;
            }
        }
    }

    for(int i=NUM_STEPS-1; i>=0; i--) {
        map<pair<char,char>, ll> dp2;

        auto chs = getChars(i);
        for(auto c1:chs) {
            for(auto c2:chs) {
                dp2[{c1,c2}] = getCost(i, c1, c2);
            }
        }

        dp = dp2;
    }
}

ll solve(const string& s) {
    auto sx = s.back()=='A' ? s.substr(0, s.size()-1) : s;
    ll x = stoll(sx);
    ll len = 0;

    string p(s);
    char pch = 'A';
    for(auto ch:s) {
        len += dp[{pch,ch}];
        pch = ch;
    }

    ll ans = x * len;
    return ans;
}


void one () {
    string s;

    ll ans = 0;
    while(getline(cin, s)) {
        if(s.empty()) break;
        
        ans += solve(s);    
    }
    cout << ans << endl;
}
