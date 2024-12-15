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

typedef tuple<int,int,int,int> ti;

pair<int,int> read2(string&& s) {
    auto ss = s.substr(2);
    int i = ss.find(',');
    return {
        stoi(ss.substr(i+1)),
        stoi(ss.substr(0,i))
    };
}

ti read(string& s) {
    int mi  = s.find(' ');
    auto [i,j] = read2(s.substr(0,mi));
    auto [di,dj] = read2(s.substr(mi+1));
    return {i,j,di,dj};
}

void one () {
    vector<string> a;
    string s;
    while(getline(cin, s)) {
        if(s.empty()) break;
        a.push_back(s);
    }

    int n = a.size();
    int m = a[0].size();

    int ri=-1,rj=-1;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++){
            if(a[i][j]=='@'){
                ri=i;
                rj=j;
            }
        }
    }
    assert(ri>=0);
    assert(rj>=0);
    
    auto move = [&](int di, int dj) {
        int i=ri;
        int j=rj;
        while(1) {
            i+=di;
            j+=dj;
            if (i<0 || j<0 || i >= n || j >= m) return;
            if (a[i][j]=='#') return;
            if (a[i][j]=='.') break;
        }

        di*=-1;
        dj*=-1;
        while(1) {
            int ni=i+di;
            int nj=j+dj;
            swap(a[i][j], a[ni][nj]);
            if (ni==ri && nj==rj) break;
            i=ni;
            j=nj;
        }

        ri=i;
        rj=j;
    };

    map<char,pair<int,int>> dirs;
    dirs['^'] = {-1,0};
    dirs['v'] = {1,0};
    dirs['>'] = {0,1};
    dirs['<'] = {0,-1};

    while(getline(cin, s)) {
        for(auto ch:s){
            auto [di,dj]= dirs[ch];
            move(di,dj);
            // for(int i=0; i<n; i++) cerr << a[i]<<endl;
        }
    }

    ll ans=0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++){
            if(a[i][j]=='O'){
                ans += i*100 + j;
            }
        }
    }

    cout << ans << endl;
}
