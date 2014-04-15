#include <iostream>
#include <vector>
#include "Util.hpp"

using namespace std;

int main() {
    auto vec = Func::Range(20);
    // select the even numbers
    vec = Func::Filter<int>(vec, [](int v) { return v % 2 == 0; });
    // compute the square
    vec = Func::Map<int, int>(vec, [](int v) { return v * v; });
    // output
    for (auto v : vec) {
        cout << v << endl;
    }

    return 0;
}
