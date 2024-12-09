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
    string s;
    getline(cin, s);
    
    set<pair<ll,int>> frees;
    set<tuple<ll,int,int>, greater<>> blocks;

    for(ll i=0,p=0; i<s.size(); i++) {
        int x = stoi(s.substr(i,1));

        if (i&1) {
            frees.emplace(p,x);
        } else {
            int id = i/2;
            blocks.emplace(p,x,id);
        }

        p+=x;
    }

    ll ans = 0;
    for(auto [p,sz,id] : blocks) {
        ll pp = -1;
        ll psz = -1;

        for(auto [pf, szf] : frees) {
            if (pf > p) break;

            if (sz <= szf) {
                pp = pf;
                psz = szf;
                break;
            }
        }

        if (pp >= 0) {
            frees.erase({pp, psz});

            p = pp;
            psz -= sz;
            if (psz > 0) {
                pp += sz;
                frees.emplace(pp, psz);
            }
        }

        ll checksum = (p + p + sz-1) * sz / 2;
        ans += id * checksum;
    }

    cout << ans << endl;
}
