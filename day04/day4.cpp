#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define RANGE pair<int, int>

RANGE to_range(string in) {
    RANGE first(0,0);
    first.first = atoi(in.substr(0, in.find('-')).c_str());
    first.second = atoi(in.substr(in.find('-')+1, in.length()).c_str());

    return first;
}

pair<RANGE, RANGE> get_ranges(string in) {
    RANGE first = to_range(in.substr(0, in.find(',')));
    RANGE second = to_range(in.substr(in.find(',')+1, in.length()));
    return pair<RANGE,RANGE>(first, second);
}

bool in_range(int a, RANGE b) {
    return a >= b.first && a <= b.second;
}

int partly_contains_range(RANGE a, RANGE b) {
    if (in_range(a.first, b) || in_range(a.second, b)) {
        return 1;
    } else if (in_range(b.first, a) || in_range(b.second, a)) {
        return 2;
    }
    return 0;
}

int partly_contains_range(pair<RANGE, RANGE> in) {
    return partly_contains_range(in.first, in.second);
}

int fully_contains_range(RANGE a, RANGE b) {
    if (a.first <= b.first && a.second >= b.second) {
        return 1;
    } else if (b.first <= a.first && b.second >= a.second) {
        return 2;
    }

    return 0;
}

int fully_contains_range(pair<RANGE, RANGE> in) {
    return fully_contains_range(in.first, in.second);
}

int main() {
    std::ifstream is("input");
    int containing_a = 0;
    int containing_b = 0;
    for (string s; std::getline(is, s);) {
        pair<RANGE, RANGE> ranges = get_ranges(s);
        int ca = fully_contains_range(ranges);
        int cb = partly_contains_range(ranges);
        if (ca) {
            containing_a++;
        }
        if (cb) {
            containing_b++;
        }
    }

    cout << "(A) Containing things: " << containing_a << endl;
    cout << "(B) Containing things: " << containing_b << endl;
    return 0;
}