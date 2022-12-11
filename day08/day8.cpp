#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int tree_score(size_t xi, size_t yi, vector<string> &f) {
    int score = 0;
    for (int x = xi-1; x >= 0; x--) {
        score++;
        if (f[yi][x] >= f[yi][xi]) { break; }
    }
    int a = 0;
    for (size_t x = xi+1; x < f[yi].length(); x++) {
        a++;
        if (f[yi][x] >= f[yi][xi]) { break; }
    }
    score *= a;
    a = 0;
    for (int y = yi-1; y >= 0; y--) {
        a++;
        if (f[y][xi] >= f[yi][xi]) { break; }
    }
    score *= a;
    a = 0;
    for (size_t y = yi+1; y < f.size(); y++) {
        a++;
        if (f[y][xi] >= f[yi][xi]) { break; }
    }
    return score * a;
}

bool check(size_t xi, size_t yi, vector<string> &f) {
    // check in every direction
    bool visible = true;
    for (int x = xi-1; x >= 0; x--) {
        if (f[yi][x] >= f[yi][xi]) { 
            visible = false;
            break; 
        }
    }
    if (visible) { return true; }
    visible = true;
    for (size_t x = xi+1; x < f[yi].length(); x++) {
        if (f[yi][x] >= f[yi][xi]) { 
            visible = false;
            break; 
        }
    }
    if (visible) { return true; }
    visible = true;
    for (int y = yi-1; y >= 0; y--) {
        if (f[y][xi] >= f[yi][xi]) { 
            visible = false;
            break; 
        }
    }
    if (visible) { return true; }
    visible = true;
    for (size_t y = yi+1; y < f.size(); y++) {
        if (f[y][xi] >= f[yi][xi]) { 
            visible = false;
            break; 
        }
    }
    return visible;
}

pair<int,int> count(vector<string> &l) {
    pair<int,int> c(0,0);
    for (size_t x = 0; x < l[0].length()-1; x++) {
        for (size_t y = 0; y < l.size(); y++) {
            c.first += check(x,y,l);
        }
    }
    
    for (size_t x = 1; x < l[0].length()-2; x++) {
        for (size_t y = 1; y < l.size()-1; y++) {
            int score = tree_score(x,y,l);
            if (score > c.second) {
                c.second = score;
            } 
        }
    }

    return c;
}

int main() {
    std::ifstream is("input");
    vector<string> l;
    for (string s; getline(is, s);) {
        l.push_back(s);
    }

    pair<int,int> c = count(l);
    cout << "A: " << c.first << endl;
    cout << "B: " << c.second << endl;
    return 0; 
}