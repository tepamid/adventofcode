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

vector<pair<int, int> > dirs = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}, 
};
vector<pair<int, int> > dirs2 = {
    {0, -1}, {0, -1}, {-1, 0}, {-1, 0}, 
};

void one () {
    ll ans = 0;
    vector<string> a;
    string s;
    while(getline(cin, s)) {
        a.push_back(s);
    }

    int n = a.size();
    int m = a[0].size();

    vector<vector<int>> was(n, vector<int>(m));

    auto inField = [&](int i, int j) {
        if (i<0 || j<0 || i >= n || j >= m) return false;
        return true;
    };

    auto hasFence = [&](int i, int j, int di, int dj) {
        if (i<0 || j<0 || i >= n || j >= m) return false;

        auto ni = i+di;
        auto nj = j+dj;

        if (ni<0 || nj<0 || ni >= n || nj >= m) {
            return true;
        }

        return (a[i][j] != a[ni][nj]);
    };

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if (was[i][j]) continue;

            queue<pair<int,int>> q;
            q.emplace(i,j);

            was[i][j] = 1;
            int sq=1;
            int pp=0;
            
            while(!q.empty()) {
                auto [i,j] = q.front(); q.pop();
            
                for(int id=0; id<dirs.size(); id++) {
                    auto [di,dj] = dirs[id];
                
                    auto ni = i+di;
                    auto nj = j+dj;

                    {
                        auto [di2,dj2] = dirs2[id];
                        int pi = i+di2;
                        int pj = j+dj2;

                        auto putFence = hasFence(i,j,di,dj); 
                        
                        if (inField(pi,pj) && a[i][j] == a[pi][pj] && hasFence(pi,pj,di,dj)) {
                            putFence = false;
                        }

                        if (putFence) {
                            pp++;
                        }
                    }

                    if (ni<0 || nj<0 || ni >= n || nj >= m) {
                        continue;
                    }

                    if (a[i][j] == a[ni][nj]) {
                        if (!was[ni][nj]) {
                            q.emplace(ni,nj);
                            was[ni][nj] = 1;
                            sq++;
                        }
                    }

                }
            }

            cerr << a[i][j] << " " << sq << " * " << pp << endl;
            ans += sq*pp;
        }
    }

    cout << ans << endl;
}
