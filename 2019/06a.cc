#include <iostream>
#include <map>
#include <string>

int indirect_orbits(const std::map<std::string, std::string>& sun_of, std::string earth)
{
    auto it = sun_of.find(earth);
    if (it == sun_of.end()) return 0;
    return 1 + indirect_orbits(sun_of, it->second);
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

    int result = 0;
    for (auto&& kv : sun_of) {
        result += indirect_orbits(sun_of, kv.first);
    }
    std::cout << result << "\n";
}
