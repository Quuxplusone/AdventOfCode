#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int gcd_of(int x, int y) {
    if (x < 0) return gcd_of(-x, y);
    if (y < 0) return gcd_of(x, -y);
    if (x > y) return gcd_of(y, x);
    if (x == 0) return y;
    return gcd_of(y % x, x);
}

void block_asteroids_behind(std::vector<std::string>& grid, int r, int c, int i, int j)
{
    int dr = (i - r);
    int dc = (j - c);
    assert(dr != 0 || dc != 0);
    int gcd = gcd_of(dr, dc);
    dr /= gcd;
    dc /= gcd;
    while (true) {
        i += dr;
        j += dc;
        if (0 <= i && i < (int)grid.size() && 0 <= j && j < (int)grid[0].size()) {
            grid[i][j] = '.';
        } else {
            break;
        }
    }
}

int count_asteroids_from(std::vector<std::string> grid, int r, int c)
{
    for (size_t i=0; i < grid.size(); ++i) {
        for (size_t j=0; j < grid[0].size(); ++j) {
            if (i == r && j == c) {
                continue;
            }
            if (grid[i][j] == '#') {
                block_asteroids_behind(grid, r, c, i, j);
            }
        }
    }
    int result = std::accumulate(grid.begin(), grid.end(), 0, [](int sum, const std::string& row){
       return sum + std::count(row.begin(), row.end(), '#');
    });
    return result;
}

int main()
{
    std::vector<std::string> grid;
    std::string line;
    while (std::cin >> line) {
        grid.push_back(line);
    }
    assert(std::all_of(grid.begin(), grid.end(), [&](const auto& row) { return row.size() == grid[0].size(); }));

    int result = 0;
    for (size_t r=0; r < grid.size(); ++r) {
        for (size_t c = 0; c < grid[0].size(); ++c) {
            if (grid[r][c] == '#') {
                result = std::max(result, count_asteroids_from(grid, r, c));
            }
        }
    }
    result -= 1;  // don't detect yourself
    std::cout << result << "\n";
}
