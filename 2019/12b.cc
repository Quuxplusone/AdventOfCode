#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

using Int = long long int;

struct Moon1D {
    int x;
    int dx;
    bool operator==(const Moon1D& o) const { return x == o.x && dx == o.dx; }
};

struct Moon {
    int x, y, z;
    int dx, dy, dz;
    Moon1D just_x() const { return Moon1D{x,dx}; }
    Moon1D just_y() const { return Moon1D{y,dy}; }
    Moon1D just_z() const { return Moon1D{z,dz}; }
};

int period_of_system(std::vector<Moon1D> original_moons)
{
    auto moons = original_moons;
    for (int t=1; true; ++t) {
        // apply gravity
        for (Moon1D& a : moons) {
            for (Moon1D& b : moons) {
                a.dx += (a.x > b.x) ? -1 : (a.x < b.x);
            }
        }
        // now apply velocity
        for (Moon1D& a : moons) {
            a.x += a.dx;
        }

        if (moons == original_moons) {
            return t;
        }
    }
}

Int gcd_of(Int x, Int y) {
    if (x < 0) return gcd_of(-x, y);
    if (y < 0) return gcd_of(x, -y);
    if (x > y) return gcd_of(y, x);
    if (x == 0) return y;
    return gcd_of(y % x, x);
}

Int lcm(Int x, Int y)
{
    return (x / gcd_of(x, y)) * y;
}

int main()
{
    std::vector<Moon> moons;

    std::string line;
    while (std::getline(std::cin, line)) {
        int x, y, z;
        int rc = sscanf(line.c_str(), "<x=%d, y=%d, z=%d>", &x, &y, &z);
        moons.push_back({x,y,z,0,0,0});
    }

    std::vector<Moon1D> temp(moons.size());
    std::transform(moons.begin(), moons.end(), temp.begin(), [](const auto& x) { return x.just_x(); });
    int px = period_of_system(temp);
    std::transform(moons.begin(), moons.end(), temp.begin(), [](const auto& x) { return x.just_y(); });
    int py = period_of_system(temp);
    std::transform(moons.begin(), moons.end(), temp.begin(), [](const auto& x) { return x.just_z(); });
    int pz = period_of_system(temp);

    std::cout << lcm(lcm(px, py), pz) << "\n";
}
