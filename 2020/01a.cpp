#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> v;
    std::copy(std::istream_iterator<int>(std::cin), {}, std::back_inserter(v));
    std::sort(v.begin(), v.end());
    int i = 0;
    int j = v.size() - 1;
    while (i < j) {
        int product = v[i] + v[j];
        if (product > 2020) --j;
        else if (product < 2020) ++i;
        else {
            std::cout << (v[i] * v[j]) << '\n';
            break;
        }
    }    
}
