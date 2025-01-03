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

inline
void prune(ll& x) {
    x %= 16777216LL;
}
ll simulate(ll x) {
    auto res = x;
    res ^= x*64;
    prune(res);

    x = res;
    res ^= x/32;
    prune(res);

    x = res;
    res ^= x*2048;
    prune(res);

    return res;
}

const size_t DSIZE = 4;
const int NUM = 2000;
const int MOD = 10;

void one () {
    map<deque<int>, ll> dp;

    string s;
    while(getline(cin, s)) {
        if(s.empty()) break;
        
        vector<ll> a; 
        {
            ll x = stoll(s);
            a.push_back(x%MOD);

            for(int i=0; i<NUM; i++) {
                x = simulate(x);
                a.push_back(x%MOD);
            }
        }

        map<deque<int>, ll> ma;
        {
            deque<int> as;
            for(int i=1; i<a.size(); i++) {
                while (as.size() >= DSIZE) as.pop_front();
                int d = a[i] - a[i-1];
                assert(d >= -9);
                assert(d <= 9);
                as.push_back(d);
                
                assert(as.size() <= DSIZE);

                if (as.size() == DSIZE) {
                    ma.insert({as, a[i]});
                }

            }
        }

        for(auto [as,x] : ma) {
            dp[as] += x;
        }
    }

    ll ans = 0;
    for(auto [as,cur] : dp) {
        if (cur > ans) {
            ans = cur;
            cerr << cur << ": ";
            for(auto x:as) cerr << x << " "; cerr << endl;
        }
    }

    cout << ans << endl;
}
