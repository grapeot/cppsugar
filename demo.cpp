#include <iostream>
#include <vector>
#include "Util.hpp"

using namespace std;
using namespace func;

int main() {
    auto vec = Range(20);
    // select the even numbers
    vec = Filter<int>(vec, [](int v) { return v % 2 == 0; });
    // compute x * (20 - x)
    vec = Map<int, int>(vec, [](int v) { return v * (20 - v); });
    for (auto v : vec) cout << v << endl;
    // unique!
    cout << endl;
    for (auto v : Unique(vec)) cout << v << endl;
    // min/max/sum
    cout << endl
        << "The minimum element is: " << Min(vec) << endl
        << "The sum is: " << Sum(vec) << endl
        << "The max of square is: " << Max<int, int>(vec, [](int x) { return x * x; }) << endl;
    
    return 0;
}
