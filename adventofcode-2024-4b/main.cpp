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

    vector<pair<string,string>> opts = {
        {"MAS","MAS"},
        {"SAM","MAS"},
        {"MAS","SAM"},
        {"SAM","SAM"},
    };

    function<bool(int,int,int,int,int,const string&)> start = [&](int i, int j, int k, int di, int dj, const string& word) {
        if (word[k] != a[i][j]) {
            return false;
        }

        if (k+1 >= word.size()) {
            return true;
        }

        int ni = i+di;
        int nj = j+dj;

        if (ni<0 || nj<0 || ni >= n || nj >= m) {
            // 
        } else {
            auto r = start(ni,nj,k+1,di,dj,word);
            return r;
        }

        return false;
    };

    function<int(int,int )> start2 = [&](int i, int j) {
        for(auto [s1,s2] : opts) {
            if (start(i-1,j-1,0,1,1,s1)) {
                if (start(i-1,j+1,0,1,-1,s2))
                {
                    return 1;
                }
            }
        }

        return 0;

    };

    ll ans = 0;
    for(int i=1; i+1<n; i++) {
        for(int j=1; j+1<m; j++) {
            if (a[i][j]=='A') {
                ans += start2(i,j);
            }
        }
    }
    cout << ans << endl;
}
