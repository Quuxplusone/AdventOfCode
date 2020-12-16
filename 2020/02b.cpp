#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

int main() {
    std::string line;
    int lo, hi;
    std::string lettercolon;
    std::string password;
    int result = 0;
    while (std::cin >> lo >> hi >> lettercolon >> password) {
        assert(lettercolon.size() == 2);
        assert(hi < 0);
        char letter = lettercolon[0];
        result += (password[lo-1] == letter) ^ (password[-hi-1] == letter);
    }
    std::cout << result << '\n';
}
