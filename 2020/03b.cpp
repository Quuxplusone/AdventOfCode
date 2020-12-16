#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> grid;

long long count(int dx, int dy) {
    int x = 0;
    int y = 0;
    int result = 0;
    while (y < grid.size()) {
        result += (grid[y][x] == '#');
        y += dy;
        x = (x+dx) % grid[0].size();
    }
    return result;
}

int main() {
    std::string line;
    while (std::cin >> line) {
        grid.push_back(line);
    }
    long long result = count(1,1) * count(3,1) * count(5,1) * count(7,1) * count(1,2);
    std::cout << result << '\n';
}
