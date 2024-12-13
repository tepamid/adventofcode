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


using pii = pair<ll,ll>;


ll solveOk(pii A, pii B, pii P) {
    for(int i=0; i<100; i++) {
        for(int j=0; j<100; j++) {
            if (i*A.first +j*B.first == P.first) {
                if (i*A.second+j*B.second == P.second) {
                    return 3*i + j;
                }
            }
        }
    }
    return 0;
}

pii getxy(string& s, char split='+') {
    auto i = s.find(split);
    auto ic = s.find(',');
    auto ss = s.substr(ic+1);
    int j = ss.find(split);

    int x = stoi(s.substr(i+1, ic-i-1));
    int y = stoi(ss.substr(j+1, ss.size()-(j+1)));

    return make_pair(x,y);
} 

ll det(ll a11, ll a12, ll a21, ll a22) {
    return a11*a22 - a12*a21;
}

ll solve(pii A, pii B, pii P) {
    {
        if (P.first % B.first == 0)
        if (P.second % B.second == 0)
        if (P.first / B.first == P.second / B.second) {
            return P.first / B.first;
        }
    }

    {
        if (P.first % A.first == 0)
        if (P.second % A.second == 0)
        if (P.first / A.first == P.second / A.second) {
            return P.first / A.first * 3;
        }
    }

    // i*A.first  + j*B.first == P.first
    // i*A.second + j*B.second == P.second

    auto a11 = A.first;
    auto a12 = B.first;

    auto a21 = A.second;
    auto a22 = B.second;

    auto c1 = P.first;
    auto c2 = P.second;

    auto d = det(a11, a12, a21, a22);
    if (d == 0) {
        return 0;
    }

    auto i = det(c1, a12, c2, a22);
    auto j = det(a11, c1, a21, c2);

    if (i%d==0) i/=d; else return 0;
    if (j%d==0) j/=d; else return 0;

    if (i>=0 && j>=0) {
        return 3*i + j;
    } else {
        return 0;
    }
}

void one () {
    ll ans = 0;

    {
        string s;
        while(getline(cin, s)) {
            // cerr << s << "\n";
            auto A = getxy(s);
            // cerr << A.first << ' ' << A.second << "\n";
            getline(cin, s);
            auto B = getxy(s);
            getline(cin, s);
            auto P = getxy(s, '=');
            getline(cin, s);

            ll cur = solve(A,B,P);
            ans += cur;

            cerr << cur << " & " << solveOk(A,B,P) << endl;
        }
    }

    cout << ans << endl;
}
