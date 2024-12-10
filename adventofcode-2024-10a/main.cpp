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
    // {1,1}, {1,-1}, {-1,1}, {-1,-1}
};

void one () {
    vector<string> a;
    string s;
    while(getline(cin, s)) {
        a.push_back(s);
    }

    int n = a.size();
    int m = a[0].size();

    ll ans=0;

    auto bfs = [&](auto si, auto sj) {
        set<pair<int,int>> was9;
        set<pair<int,int>> was;
        queue<pair<int,int>> q;
        was.emplace(si,sj);
        q.emplace(si,sj);

        while(!q.empty()) {
            auto [i,j] = q.front(); q.pop();

            if (a[i][j] == '9') {
                was9.emplace(i,j);
                continue;;
            }

            for(auto [di,dj] : dirs) {
                auto ni = i+di;
                auto nj = j+dj;

                if (ni<0 || nj<0 || ni >= n || nj >= m) continue;

                if (a[ni][nj] == a[i][j] + 1) {
                    if (was.find({ni,nj}) == was.end()) {
                        was.emplace(ni,nj);
                        q.emplace(ni,nj);
                    }
                }
            }
            
        }

        return was9.size();
    };

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if (a[i][j] == '0') {
                ans += bfs(i,j);
            }
        }
    }

    cout << ans << endl;
}
