#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> grid;
    std::string line;
    while (std::cin >> line) {
        grid.push_back(line);
    }
    int x = 0;
    int y = 0;
    int result = 0;
    while (y < grid.size()) {
        result += (grid[y][x] == '#');
        ++y;
        x = (x+3) % grid[0].size();
    }
    std::cout << result << '\n';
}
