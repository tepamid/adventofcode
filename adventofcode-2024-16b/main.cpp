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

typedef tuple<int,int,int,int> ti4;

vector<pair<int, int> > dirs = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}, 
};

void one () {
    vector<string> a;
    string s;
    while(getline(cin, s)) {
        if(s.empty()) break;
        a.push_back(s);
    }

    int n = a.size();
    int m = a[0].size();

    int si=-1,sj=-1;
    int fi=-1,fj=-1;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++){
            if(a[i][j]=='S') {
                si=i;
                sj=j;
                a[i][j]='.';
            }
            if(a[i][j]=='E') {
                fi=i;
                fj=j;
                a[i][j]='.';
            }
        }
    }
    assert(si>=0);
    assert(sj>=0);
    assert(fi>=0);
    assert(fj>=0);

    auto dijkstra = [&](map<ti4, ll>& d, const vector<ti4>& start, int coeff, int FI, int FJ) {

        set<pair<ll,ti4>> se;
        for(auto sp : start) {
            se.insert({0,sp});
            d[sp] = 0;
        }

        ll ans = 1e9;

        while(!se.empty()) {
            auto [D, pos] = *se.begin();
            se.erase(se.begin());
            auto [i,j,DI,DJ] = pos;

            if (i==FI && j==FJ && ans==1e9) {
                ans = D;
                continue;
            }

            if (D > d[pos]) continue;

            for(auto [di,dj] : dirs) {
                auto ni = i;
                auto nj = j;

                ll add = 1000;

                if (di==DI && dj==DJ) {
                    add = 1;
                    ni+=di * coeff;
                    nj+=dj * coeff;
                } else {
                    add = 1000;
                }

                if (ni<0 || nj<0 || ni >= n || nj >= m) continue;

                if (a[ni][nj] != '.') continue;

                auto cur = D + add;

                ti4 npos = {ni,nj,di,dj};

                if (d.find(npos) == d.end() || d[npos] > cur) {
                    d[npos] = cur;
                    se.insert({cur,npos});
                }
            }
        }

        return ans;
    };


    map<ti4, ll> d1;
    vector<ti4> start1 = {{si,sj,0,1}};

    auto ans1 = dijkstra(d1, start1, 1, fi, fj);
    
    map<ti4, ll> d2;
    vector<ti4> start2;
    for(auto [di,dj] : dirs) {
        start2.emplace_back(fi,fj,di,dj);
    }

    auto ans2 = dijkstra(d2, start2, -1, si, sj);

    // cerr << ans1 << " == " << ans2 << endl;

    int cnt=0;

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            for(auto [di,dj] : dirs) {
                ti4 pos = {i,j,di,dj};
                if (d1[pos] + d2[pos] == ans1) {
                    cnt++;
                    // a[i][j]='O';
                    break;
                }
            }
        }
    }

    // for(int i=0; i<n; i++) cerr << a[i] << endl;

    cout << cnt << endl;
}
