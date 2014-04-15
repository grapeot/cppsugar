#include <iostream>
#include <vector>
#include "Util.hpp"

using namespace std;
using namespace func;

int main() {
    auto vec = Range(20);
    // select the even numbers
    vec = Filter<int>(vec, [](int v) { return v % 2 == 0; });
    // compute the square
    vec = Map<int, int>(vec, [](int v) { return v * v; });
    // output
    for (auto v : vec) {
        cout << v << endl;
    }

    return 0;
}
