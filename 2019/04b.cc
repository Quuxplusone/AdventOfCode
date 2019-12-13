#include <algorithm>
#include <iostream>
#include <string>

int digits_are_sorted(int i) {
    std::string s = std::to_string(i);
    return std::is_sorted(s.begin(), s.end());
}

int has_exactly_digit_pair(int i) {
    std::string s = std::to_string(i);
    int counts[10] = {};
    for (char ch : s) ++counts[ch - '0'];
    return std::find(counts, counts + 10, 2) != counts + 10;
}

int has_repeating_digit_pair(int i) {
    std::string s = std::to_string(i);
    return std::unique(s.begin(), s.end()) != s.end();
}

int main()
{
    std::string range;
    std::cin >> range;
    int lo = std::stoi(range.substr(0, range.find('-')));
    int hi = std::stoi(range.substr(range.find('-') + 1));
    int result = 0;
    for (int i = lo; i <= hi; ++i) {
        if (!digits_are_sorted(i)) continue;
        if (!has_exactly_digit_pair(i)) continue;
        ++result;
    }
    std::cout << result << "\n";
}
