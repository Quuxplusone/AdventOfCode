#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <tuple>
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

struct Pos {
    int r, c;
    bool operator==(const Pos& rhs) const { return r == rhs.r && c == rhs.c; }
    bool operator!=(const Pos& rhs) const { return !(*this == rhs); }
};

int asteroids_strictly_between(const std::vector<std::string>& grid, Pos a, Pos b)
{
    int dr = (b.r - a.r);
    int dc = (b.c - a.c);
    assert(dr != 0 || dc != 0);
    int gcd = gcd_of(dr, dc);
    dr /= gcd;
    dc /= gcd;
    int count = 0;
    while (true) {
        a.r += dr;
        a.c += dc;
        if (a == b) break;
        assert(0 <= a.r && a.r < grid.size());
        assert(0 <= a.c && a.c < grid[0].size());
        if (grid[a.r][a.c] == '#') ++count;
    }
    return count;
}

double theta_of(int dr, int dc)
{
    if (dc == 0 && dr < 0) {
        return 2*M_PI;
    } else if (dc == 0 && dr > 0) {
        return M_PI;
    } else if (dc > 0) {
        assert(0 > std::atan2(-dc, -dr) && std::atan2(-dc, -dr) > -M_PI);
        return std::atan2(-dc, -dr) + 2*M_PI;
    } else {
        assert(0 < std::atan2(-dc, -dr) && std::atan2(-dc, -dr) < M_PI);
        return std::atan2(-dc, -dr);
    }
}

auto vaporized_before(const std::vector<std::string>& grid, Pos laser_pos)
{
    return [=](Pos a, Pos b) {
        assert(a != laser_pos);
        assert(b != laser_pos);
        double atheta = theta_of(a.r - laser_pos.r, a.c - laser_pos.c);
        double btheta = theta_of(b.r - laser_pos.r, b.c - laser_pos.c);
        int atrip = asteroids_strictly_between(grid, laser_pos, a);
        int btrip = asteroids_strictly_between(grid, laser_pos, b);
        return std::make_tuple(atrip, -atheta) < std::make_tuple(btrip, -btheta);
    };
}

int main()
{
    std::vector<std::string> grid;
    std::string line;
    while (std::cin >> line) {
        grid.push_back(line);
    }
    assert(std::all_of(grid.begin(), grid.end(), [&](const auto& row) { return row.size() == grid[0].size(); }));

    int best = 0;
    Pos best_pos;
    for (int r=0; r < (int)grid.size(); ++r) {
        for (int c = 0; c < (int)grid[0].size(); ++c) {
            if (grid[r][c] == '#') {
                int a = count_asteroids_from(grid, r, c);
                if (a > best) {
                    best = a;
                    best_pos = {r, c};
                }
            }
        }
    }

    std::cout << "bestpos is " << best_pos.r << " " << best_pos.c << "\n";

    std::vector<Pos> asteroids;
    for (int r=0; r < (int)grid.size(); ++r) {
        for (int c = 0; c < (int)grid[0].size(); ++c) {
            if (grid[r][c] == '#' && (best_pos != Pos{r, c})) {
                asteroids.push_back({r,c});
            }
        }
    }
    std::sort(asteroids.begin(), asteroids.end(), vaporized_before(grid, best_pos));
    std::cout << asteroids[199].c * 100 + asteroids[199].r << "\n";
}
