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
    vector<int> a;

    for(int i=0; i<s.size(); i++) {
        int x = stoi(s.substr(i,1));

        if (i&1) {
            // space
            while(x--) {
                a.push_back(-1);
            }
        } else {
            int id = i/2;

            while(x--) {
                a.push_back(id);
            }
        }
    }

    for(int i=0; i<a.size(); i++) {
        while (i<a.size() && a[i] < 0) {
            a[i] = a.back();
            a.pop_back();
        }
    }

    ll ans = 0;
    for(int i=0; i<a.size(); i++) {
        assert(a[i] >= 0);
        ans += i*a[i];
    }

    cout << ans << endl;
}
