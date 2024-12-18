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

vector<pair<int, int> > dirs = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}, 
};



void one () {
    string s;
    int n, m;
    {
        getline(cin, s);
        n = stoi(s);
        m = n;
    }

    vector<pair<int,int>> xys;


    auto can = [&]() {

        vector<vector<int>> a(n, vector<int>(m,INT_MAX));
        for(auto [x,y] : xys) a[y][x] = -1;

        queue<pair<int,int>> q;
        q.emplace(0,0);
        a[0][0] = 0;

        while (!q.empty())
        {
            auto [i,j] = q.front(); q.pop();
            // cerr << i << "," << j << endl;
            
            for(auto [di,dj] : dirs) {
                auto ni = i+di;
                auto nj = j+dj;

                if (ni<0 || nj<0 || ni >= n || nj >= m) continue;

                if (a[ni][nj] == INT_MAX) {
                    q.emplace(ni, nj);
                    a[ni][nj] = a[i][j]+1;
                }
            }

        }
        
        // cout << a[n-1][m-1] << endl;
        return a[n-1][m-1] != INT_MAX;
    };
    
    while(getline(cin, s)) {
        if(s.empty()) break;
        
        vector<int> xy;
        spliti(s, xy, ',');
        int x = xy[0];
        int y = xy[1];
        xys.emplace_back(x,y);

        if (!can()) {
            cout << x <<','<< y << endl;
            return;
        }
    }


}
