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

const int NUM_STEPS = 3;
vector<string>& getMap(int iStep) {
    return iStep == 0 ? numkp : dirkp;
}

vector<tuple<int,int,char> > dirs = {
    {0, -1, '<'}, 
    {1, 0, 'v'},
    {0, 1, '>'}, 
    {-1, 0, '^'}, 
};

map<char,pair<int,int>> ch2dir;
void setupDirs() {
    for(auto [di,dj,ch] : dirs) { 
        ch2dir[ch] = {di,dj};
    }
}

vector<string> makePath2(char startCh, const string& s, int iStep) {
    const vector<string>& a = getMap(iStep);

    int n = a.size();
    int m = a[0].size();

    int si,sj;
    fo(i,n) {
        fo(j,m) {
            if (a[i][j] == startCh) {
                si=i;
                sj=j;
            }
        }
    }

    vector<string> ans;
    for(auto ch : s) {
        vector<string> singleCharOptions;

        auto bfs = [&]() {
            int dist = -1;
            queue<tuple<int,int,string>> q;
            q.emplace(si, sj, ""s);
            while(!q.empty()) {
                auto [i,j,t] = q.front(); q.pop();

                if (a[i][j] == ch) {
                    si = i;
                    sj = j;
                    
                    t += 'A';
                    if (dist < 0) {
                        dist = t.size();
                    } else {
                        if (t.size() > dist) return;
                    }
                    singleCharOptions.push_back(t);
                    continue;
                }

                for(auto [di,dj,ch2] : dirs) {
                    auto ni = i+di;
                    auto nj = j+dj;

                    if (ni<0 || nj<0 || ni >= n || nj >= m) continue;

                    if (a[ni][nj] == '#') continue;

                    q.emplace(ni,nj,t+ch2);
                }
            }
        };

        bfs();

        vector<string> ans2;
        if (ans.empty()) {
            ans2 = singleCharOptions;
        } else {
            for(auto& beg : ans) {
                for(auto& ending:singleCharOptions) {
                    ans2.push_back(beg + ending);
                }
            }
        }

        ans = ans2;
    }

    return ans;
}

map<string, string> solutions;

void precalc() {
    setupDirs();

    for(auto ch : {'A','0','1','2','3','4','5','6','7','8','9'}) {
        string s;
        s += ch;

        for(auto pCh : {'A','0','1','2','3','4','5','6','7','8','9'}) {
            vector<string> ps = { s };
            for(int i=0; i<NUM_STEPS; i++) {
                vector<string> ps2;
                for(auto p : ps) {
                    auto startCh = i==0 ? pCh : 'A';
                    auto pp2 = makePath2(startCh, p, i);
                    ps2.insert(end(ps2), begin(pp2), end(pp2));
                }

                size_t minLen = ps2[0].size();
                for(auto& t:ps2) {
                    minLen = min(minLen,t.size());
                }
                ps.clear();
                for(auto& t:ps2) {
                    if (t.size()==minLen) ps.push_back(t);
                }
            }

            string key; key += pCh; key += s;
            solutions[key] = ps[0];
            for(auto p:ps) {
                if (p.size() < solutions[key].size()) {
                    solutions[key] = p;
                }
            }

            cerr << key << " -> " << solutions[key] << endl;
        }
    }
}

void locateChar(const vector<string>& a, char CH, int& si, int& sj) {
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

string runPath(const string& s, int iStep) {
    auto a = getMap(iStep);

    int i,j;
    locateChar(a, 'A', i, j);

    string t;
    for(auto ch : s) {
        if (ch == 'A') {
            t += a[i][j];
            continue;
        }

        auto [di,dj] = ch2dir[ch];
        i += di;
        j += dj;
    }

    return t;
}

ll solve(const string& s) {
    string p;
    for(int i=0; i<s.size(); i++) {
        string key;
        if (i==0) key += 'A';
        else key += s[i-1];
        key += s[i];
        p += solutions[key];
    }

    auto sx = s.back()=='A' ? s.substr(0, s.size()-1) : s;
    ll x = stoll(sx);
    cerr << s << " > " << x << "*" << p.size() << endl;
    cerr << p << endl;

    ll ans = x * p.size();

    for(int i=NUM_STEPS-1; i>=0; i--) {
        p = runPath(p, i);
        cerr << p << endl;
    }

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
