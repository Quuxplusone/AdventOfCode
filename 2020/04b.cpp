#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <sstream>

bool valid(std::string key, std::string value)
{
    if (key == "byr") {
        int i = std::atoi(value.c_str());
        return (1920 <= i && i <= 2002);
    } else if (key == "iyr") {
        int i = std::atoi(value.c_str());
        return (2010 <= i && i <= 2020);
    } else if (key == "eyr") {
        int i = std::atoi(value.c_str());
        return (2020 <= i && i <= 2030);
    } else if (key == "hgt") {
        char *end = nullptr;
        int i = std::strtoull(value.c_str(), &end, 10);
        if (std::string(end) == "cm") {
            return (150 <= i && i <= 193);
        } else if (std::string(end) == "in") {
            return (59 <= i && i <= 76);
        }
        return false;
    } else if (key == "hcl") {
        return std::regex_match(value, std::regex("#[0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f]"));
    } else if (key == "ecl") {
        std::vector<std::string> v = { "amb", "blu", "brn", "grn", "gry", "hzl", "oth" };
        return std::binary_search(v.begin(), v.end(), value);
    } else if (key == "pid") {
        return std::regex_match(value, std::regex("[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]"));
    }
    return true;
}

bool valid2(std::string key, std::string value) {
    bool result = valid(key, value);
    if (!result) {
        std::cout << "Invalid: " << key << " " << value << "\n";
    }
    return result;
}

int main() {
    std::set<std::string> expected = {"byr", "eyr", "iyr", "hgt", "hcl", "ecl", "pid", "cid"};
    std::set<std::string> seen;
    int valid_passports = 0;

    std::string line;
    bool last = false;
    bool is_still_valid = true;
    while (std::getline(std::cin, line) || ((last = true))) {
        if (line.empty() || last) {
            if (is_still_valid) {
                seen.insert("cid");
                valid_passports += (seen == expected);
            }
            if (last) break;
            seen.clear();
            is_still_valid = true;
        } else {
            std::istringstream iss(line);
            std::string word;
            while (iss >> word) {
                int mark = word.find(':');
                auto key = word.substr(0, mark);
                auto value = word.substr(mark+1, std::string::npos);
                is_still_valid = (is_still_valid && valid2(key, value));
                seen.insert(key);
            }
        }
    }
    std::cout << valid_passports << '\n';
}
