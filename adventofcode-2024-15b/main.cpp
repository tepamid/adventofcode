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
        if(s.empty()) break;
        string t;
        for(auto c:s) {
            if (c=='#') t+="##";
            if (c=='.') t+="..";
            if (c=='O') t+="[]";
            if (c=='@') t+="@.";
        }
        a.push_back(t);
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
    
    auto getNext = [&](int i, int j, int di, int dj, set<pair<int,int>>& ijs2) {
        int ni = i+di;
        int nj = j+dj;

        set<pair<int,int>> ijs;
        if (dj==0) {
            if (a[ni][nj]!='.') ijs.insert({ni,nj});
            if (a[ni][nj]=='[') ijs.insert({ni,nj+1});
            if (a[ni][nj]==']') ijs.insert({ni,nj-1});
        } else {
            
            if (dj > 0) {
                if (a[ni][nj]=='[') {
                    ijs.insert({ni,nj+dj});
                    ijs2.insert({ni,nj});
                } else if (a[ni][nj]==']') {
                    assert(false);
                } else {
                    ijs.insert({ni,nj});
                }
            } else {
                if (a[ni][nj]==']') {
                    ijs.insert({ni,nj+dj});
                    ijs2.insert({ni,nj});
                } else if (a[ni][nj]=='[') {
                    assert(false);
                } else {
                    ijs.insert({ni,nj});
                }
            }
        }
        return ijs;
    };

    auto move = [&](int di, int dj) {
        
        stack<set< pair<int,int> >> st;
        stack<set< pair<int,int> >> st2;
        {
            st.push({{ri,rj}});
            st2.push({});
        }

        while(1) {
            bool ok = true;
            set<pair<int,int>> ijs;
            set<pair<int,int>> ijs2;
            {
                for(auto [i,j] : st.top()) {

                    set<pair<int,int>> ijsExtra;
                    auto nextijs = getNext(i,j,di,dj, ijsExtra);

                    for(auto [ni,nj] : ijsExtra) {
                        ijs2.insert({ni,nj});
                    }

                    for(auto [ni,nj] : nextijs) {
                        ijs.insert({ni,nj});

                        if(a[ni][nj] == '#') {
                            // cerr << "obstacle" << endl;
                            return;
                        } else if(a[ni][nj] != '.') {
                            ok = false;
                        }
                    }
                }
            }

            if (ok) break;
            st.push(ijs);
            st2.push(ijs2);
        }

        while(!st.empty()) {
            for(auto [i,j] : st.top()) {
                int ni = i+di;
                int nj = j+dj;

                swap(a[ni][nj], a[i][j]);
            }
            st.pop();

            for(auto [i,j] : st2.top()) {
                int ni = i+di;
                int nj = j+dj;

                swap(a[ni][nj], a[i][j]);
            }
            st2.pop();
        }

        ri+=di;
        rj+=dj;
    };

    for(int i=0; i<n; i++) cerr << a[i] << endl; cerr<<endl;

    map<char,pair<int,int>> dirs;
    dirs['^'] = {-1,0};
    dirs['v'] = {1,0};
    dirs['>'] = {0,1};
    dirs['<'] = {0,-1};

    while(getline(cin, s)) {
        for(auto ch:s) {
            auto [di,dj] = dirs[ch];
            assert(di+dj!=0);
            move(di,dj);
        }
    }

    for(int i=0; i<n; i++) cerr << a[i] << endl;cerr<<endl;

    ll ans = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(a[i][j]=='[') {
                ans += i*100 + j;
            }
        }
    }

    cout << ans << endl;
}
