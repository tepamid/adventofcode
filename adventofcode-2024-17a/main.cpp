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
    int mi = s.find(' ');
    auto [i,j] = read2(s.substr(0,mi));
    auto [di,dj] = read2(s.substr(mi+1));
    return {i,j,di,dj};
}

void readReg(int& x) {
    string s; 
    getline(cin, s);
    int i = s.find(':');
    s = s.substr(i+2);
    x = stoi(s);
}

size_t spliti(const std::string &txt, std::vector<int> &a, char ch)
{
    std::vector<std::string> strs;

    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while (pos != std::string::npos)
    {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    // Add the last one
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    a.resize(strs.size());
    transform(strs.begin(), strs.end(), a.begin(), [](const string& w) { return stoi(w); });
    return a.size();
}

#define literal(x) x

void one () {
    vector<int> r(3);
    readReg(r[0]);
    readReg(r[1]);
    readReg(r[2]);

    int& A = r[0];
    int& B = r[1];
    int& C = r[2];
    
    vector<int> ans;
    vector<int> ops;
    {
        string P; 
        getline(cin, P); // empty line
        getline(cin, P);
        int i = P.find(':');
        P = P.substr(i+2);

        spliti(P, ops, ',');
    }

    auto combo = [&](int x) {
        if (0<=x && x<=3) {
            return x;
        }  
        assert(x<7);
        return r[x-4];
    };
    
    int n = ops.size();
    for(int i=0; i<n; i++) {
        // cerr << A << " " << B << " " << C << endl;
        // cerr << i << " " << ops[i] << endl;

        switch (ops[i])
        {
            case 0: {
                int x = combo(ops[++i]);
                A = A >> x;
                break;
            }
            case 1: {
                int x = literal(ops[++i]);
                B = B ^ x;
                break;
            }
            case 2: {
                int x = combo(ops[++i]);
                B = x % 8;
                break;
            }
            case 3: {
                int x = literal(ops[++i]);
                if (A == 0) {
                    // nothing
                } else {
                    i = x;
                    i--;
                }
                break;
            }
            case 4: {
                int ignores = combo(ops[++i]);
                B = B ^ C;
                break;
            }
            case 5: {
                int x = combo(ops[++i]) % 8;
                ans.push_back(x);
                break;
            }
            case 8: {
                int x = combo(ops[++i]);
                ans.push_back(x);
                break;
            }
            case 6: {
                int x = combo(ops[++i]);
                B = A >> x;
                break;
            }
            case 7: {
                int x = combo(ops[++i]);
                C = A >> x;
                break;
            }
            default:
                assert(false);
                break;
        }
    }

    for(int i=0; i<ans.size(); i++) cout << ans[i] << ",\n"[i+1==ans.size()];
}
