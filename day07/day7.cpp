#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
#include <climits>

using namespace std;

struct aoc_file
{
    bool is_dir = false;
    string name;
    long size = 0;
    aoc_file* parent;
    vector<aoc_file> contents;
} fs;

aoc_file* current_file;

void add_file(string s) {
    size_t l = s.find(' ');
    string type = s.substr(0, l);
    aoc_file f;
    if (type == "dir") {
        f.is_dir = true;
    } else {
        f.size = atoi(type.c_str());
    }
    f.name = s.substr(l+1);
    f.parent = current_file;
    current_file->contents.push_back(f);
}

void cd(string args) {
    if (args.rfind("..", 0) == 0) {
        current_file = current_file->parent;
    } else if (args.rfind("/", 0) == 0) {
        current_file = &fs;
    } else {
        for (size_t i = 0; i < current_file->contents.size(); i++) {
            aoc_file* f = &(current_file->contents[i]);
            if (f->name == args && f->is_dir) {
                current_file = f;
                return;
            }
        }
    }
}

void read() {
    std::ifstream is("input");
    bool ls = false;
    for (string s; std::getline(is, s);) {
        if (ls) {
            if (s[0] == '$') { ls = false; }
        }
        if (ls) {
            add_file(s);
        } else if (s.rfind("$ cd", 0) == 0) {
            cd(s.substr(5));
        } else if (s.rfind("$ ls", 0) == 0) {
            ls = true;
        }
    }
}

void calc_sizes(aoc_file &f) {
    for (size_t i = 0; i < f.contents.size(); i++) {
        if (f.contents[i].is_dir) {
            calc_sizes(f.contents[i]);
        }
        f.size += f.contents[i].size;
    }
}

void sum_sizes(aoc_file &f, long &sum) {
    sum += (f.size <= 100000) ? f.size : 0;
    for (aoc_file fi : f.contents) {
        if (fi.is_dir) { sum_sizes(fi, sum); }
    }
}

void print_fs(aoc_file &f, string start) {
    if (f.is_dir) {
        cout << start << "DIR  [" << f.size << "] " << f.name << endl;
    } else {
        cout << start << "FILE [" << f.size << "] " << f.name << endl;
    }
    
    for (aoc_file fi : f.contents) {
        print_fs(fi, " " + start);
    }
}

void find_min(aoc_file &f, long &min) {
    if ((fs.size - f.size) < (70000000 - 30000000) && f.size < min) {
        min = f.size;
    }
    for (aoc_file fi : f.contents) {
        if (fi.is_dir) {
            find_min(fi, min);
        }
    }
}

int main() {
    fs = {true, "/", 0, nullptr, {}};
    current_file = &fs;
    read();
    calc_sizes(fs);
    long sum = 0;
    sum_sizes(fs, sum);

    print_fs(fs, "");

    cout << "Filesum: " << sum << endl;

    long m = LONG_MAX;
    find_min(fs, m);
    cout << "Min = " << m << endl;
    return 0;
}