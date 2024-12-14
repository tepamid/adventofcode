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
    int n, m;

    ll a[2][2] = {{0,0},{0,0}};
    
    auto move = [&](ti& p) {
        auto [i,j,di,dj] = p;
        get<0>(p) = (i+di+n)%n;
        get<1>(p) = (j+dj+m)%m;
    };

    {
        string s;
        getline(cin, s); n = stoi(s);
        getline(cin, s); m = stoi(s);

        while(getline(cin, s)) {
            auto p = read(s);
           
            int t = 100;
            while(t--) {
                move(p);
            }
            
            auto [i,j,di,dj] = p;

            int mi = n/2;
            int mj = m/2;
            if (i==mi || j==mj) continue;
            a[i/(mi+1)][j/(mj+1)]++;
        }

    }
    
    ll ans = a[0][0] * a[0][1] * a[1][0] * a[1][1];

    cout << ans << endl;
}
