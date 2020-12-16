#include <iostream>
#include <set>
#include <string>
#include <sstream>

int main() {
    std::set<std::string> expected = {"byr", "eyr", "iyr", "hgt", "hcl", "ecl", "pid", "cid"};
    std::set<std::string> seen;
    int valid_passports = 0;

    std::string line;
    bool last = false;
    while (std::getline(std::cin, line) || ((last = true))) {
        if (line.empty() || last) {
            seen.insert("cid");
            valid_passports += (seen == expected);
            seen.clear();
            if (last) break;
        } else {
            std::istringstream iss(line);
            std::string word;
            while (iss >> word) {
                word.resize(word.find(':'));
                seen.insert(word);
            }
        }
    }
    std::cout << valid_passports << '\n';
}
