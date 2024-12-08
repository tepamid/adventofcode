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

        if  (ijs.size() < 2) continue;

        for(int i=0; i<ijs.size(); i++) {
            auto [x,y] = ijs[i];
            se.emplace(x,y);
        }

        for(int i=0; i<ijs.size(); i++) {
            for(int j=0; j<ijs.size(); j++) {
                if (i == j) continue;

                auto [x1,y1] = ijs[i];
                auto [x2,y2] = ijs[j];

                int dx = x2-x1;
                int dy = y2-y1;

                auto x = x2+dx;
                auto y = y2+dy;
                while(!(x<0 || y<0 || x >= n || y >= m)) {
                    se.emplace(x,y);                
                    x += dx;
                    y += dy;
                }
            }
        }
    }

    cout << se.size() << endl;
}
