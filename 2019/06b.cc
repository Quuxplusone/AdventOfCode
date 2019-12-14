#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

auto list_bodies(const std::map<std::string, std::string>& sun_of, std::string you)
{
    std::vector<std::string> result;
    while (true) {
        result.push_back(you);
        auto it = sun_of.find(you);
        if (it == sun_of.end()) break;
        you = it->second;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

int main()
{
    std::map<std::string, std::string> sun_of;

    std::string s;
    while (std::cin >> s) {
        std::string sun = s.substr(0, s.find(')'));
        std::string earth = s.substr(s.find(')') + 1);
        sun_of[earth] = sun;
    }

    auto v1 = list_bodies(sun_of, "YOU");
    auto v2 = list_bodies(sun_of, "SAN");

    auto m1m2 = std::mismatch(v1.begin(), v1.end(), v2.begin(), v2.end());
    auto m1 = m1m2.first;
    auto m2 = m1m2.second;
    int result = (v1.end() - m1) + (v2.end() - m2);
    result -= 2;  // don't count YOU or SAN in the result
    std::cout << result << "\n";
}
