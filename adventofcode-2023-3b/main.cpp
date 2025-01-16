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

void one () {
    vector<string> a;
    {
        string s;
        while(getline(cin, s)) {
            a.push_back(s);
        }
    }

    int n = a.size();
    int m = a[0].size();

    cerr << n << " " << m << endl;

    vector<vector<int>> b(n, vector<int>(m));

    map<pair<int,int>, vector<ll>> ma;

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if (a[i][j] == '.') continue;
            if ('0' <= a[i][j] && a[i][j] <= '9') continue;
            if (b[i][j]) continue;

            {
                queue<pair<int,int>> q;
                q.emplace(i,j);
                b[i][j] = 1;

                while(!q.empty()) {
                    auto [i,j] = q.front(); q.pop();

                    GET_NEIGHBOURS_8
                        if (b[ni][nj]) continue;
                        if ('0' <= a[ni][nj] && a[ni][nj] <= '9') {
                            b[ni][nj] = 1;
                            q.emplace(ni,nj);
                        }
                    }
                }
            }
        }
    }

    for(int i=0; i<n; i++) {
        string s;
        queue<pair<int,int>> q;

        auto bfs = [&]() {
            if (s.empty()) return;

            set<pair<int,int>> se;
            ll x = stoll(s);
            s.clear(); 

            while(!q.empty()) {
                auto [i,j] = q.front(); q.pop();

                GET_NEIGHBOURS_8
                    if (a[ni][nj] == '*') {
                        se.insert({ni,nj});
                    }
                }
            }

            for(auto [ni,nj]:se) ma[{ni,nj}].push_back(x);
        };

        for(int j=0; j<m; j++) {
            if (b[i][j] && '0' <= a[i][j] && a[i][j] <= '9') {
                s += a[i][j];
                q.emplace(i,j);
            } else {
                bfs();
            }
        }
        bfs();
    }

    ll ans = 0;
    for(auto [ij, vx] : ma) {
        if (vx.size() == 2) {
            ans += vx[0]*vx[1];
        }
    } 

    cout << ans << endl;
}
