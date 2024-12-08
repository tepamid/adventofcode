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

using pii = pair<int,int>;
pii findAntinode(pii xy1, pii xy2) {
    auto [x1,y1] = xy1;
    auto [x2,y2] = xy2;

    int dx = x2-x1;
    int dy = y2-y1;

    return {x2+dx, y2+dy};
}

void one () {
    vector<string> a;
    string s;
    while(getline(cin, s)) {
        a.push_back(s);
    }

    int n = a.size();
    int m = a[0].size();

    map<char, vector<pair<int,int>>> ma;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) {
            if (a[i][j] == '.') continue;

            ma[a[i][j]].emplace_back(i,j);
        }
    }

    set<pair<int,int>> se;

    for(const auto& [c,ijs]: ma) { 

        for(int i=0; i<ijs.size(); i++) {
            for(int j=0; j<ijs.size(); j++) {
                if (i == j) continue;
                auto [x,y] = findAntinode(ijs[i], ijs[j]);

                if (x<0 || y<0 || x >= n || y >= m) continue;

                se.emplace(x,y);
            }
        }
    }

    cout << se.size() << endl;
}
