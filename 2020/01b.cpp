#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> v;
    std::copy(std::istream_iterator<int>(std::cin), {}, std::back_inserter(v));
    std::sort(v.begin(), v.end());
    for (auto it = v.begin(); it != v.end(); ++it) {
        for (auto jt = it+1; jt != v.end(); ++jt) {
            int target = 2020 - *it - *jt;
            if (std::binary_search(jt+1, v.end(), target)) {
                std::cout << (*it * *jt * target) << '\n';
                return 0;
            }
        }
    }
}
