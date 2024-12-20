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

void one () {
    int D_DIFF = 0;
    int MAX_MANH = 0;
    vector<string> a;
    string s;
    {
        getline(cin,s);
        D_DIFF = stoi(s);
        assert(D_DIFF > 0);
    }
    {
        getline(cin,s);
        MAX_MANH = stoi(s);
        assert(MAX_MANH > 0);
    }
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

    int ans = 0;

    vector<vector<int>> df(n, vector<int>(m));

    auto bfs = [&]() {
        set<pair<int,int>> was;
        queue<tuple<int,int,int>> q;
        was.emplace(fi,fj);
        q.emplace(fi,fj,0);

        while(!q.empty()) {
            auto [i,j,d] = q.front(); q.pop();
            df[i][j] = d;

            for(auto [di,dj] : dirs) {
                auto ni = i+di;
                auto nj = j+dj;

                if (ni<0 || nj<0 || ni >= n || nj >= m) continue;

                if (a[i][j] == '#') continue;

                if (was.find({ni,nj}) == was.end()) {
                    was.emplace(ni,nj);
                    q.emplace(ni,nj,d+1);
                }            
            }
        }

        return df[si][sj];
    };

    cerr << "D_DIFF = " << D_DIFF << endl;
    cerr << "MAX_MANH = " << MAX_MANH << endl;

    auto baseDist = bfs();
    cerr << "baseDist = " << baseDist << endl;

    auto bfs2 = [&](int SI, int SJ, int D, int maxd) {
        // Moving along '#'
        set<pair<int,int>> was;
        queue<tuple<int,int,int>> q;
        was.emplace(SI,SJ);;
        q.emplace(SI,SJ,0);

        while(!q.empty()) {
            auto [i,j,d] = q.front(); q.pop();

            if (d >= maxd) continue;

            for(auto [di,dj] : dirs) {
                auto ni = i+di;
                auto nj = j+dj;

                if (ni<0 || nj<0 || ni >= n || nj >= m) continue;

                if (was.find({ni,nj}) != was.end()) continue;
                was.emplace(ni,nj);

                if (a[ni][nj] == '.') 
                {
                    auto fullDist = D + d + df[ni][nj];
                    if (fullDist <= baseDist - D_DIFF) {
                        ans++;
                    }
                    // continue;
                }

                q.emplace(ni,nj,d+1);                        
            }
        }
    };

    // BFS from {si,sj}
    {
        set<pair<int,int>> was;
        queue<tuple<int,int,int>> q;
        was.emplace(si,sj);
        q.emplace(si,sj,0);

        while(!q.empty()) {
            auto [i,j,d] = q.front(); q.pop();
            
            for(auto [di,dj] : dirs) {
                auto ni = i+di;
                auto nj = j+dj;

                if (ni<0 || nj<0 || ni >= n || nj >= m) continue;

                if (a[ni][nj] == '#') 
                {
                    continue;
                }

                if (was.find({ni,nj}) == was.end()) {
                    was.emplace(ni,nj);
                    q.emplace(ni,nj,d+1);
                }            
            }

            bfs2(i,j, d, MAX_MANH);
        }
    };

    cout << ans << endl;
}
