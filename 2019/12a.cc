#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

struct Moon {
    int x, y, z;
    int dx, dy, dz;
};

int main()
{
    std::vector<Moon> moons;

    std::string line;
    while (std::getline(std::cin, line)) {
        int x, y, z;
        int rc = sscanf(line.c_str(), "<x=%d, y=%d, z=%d>", &x, &y, &z);
        moons.push_back({x,y,z,0,0,0});
    }

    for (int t=0; t < 1000; ++t) {
        // apply gravity
        for (Moon& a : moons) {
            for (Moon& b : moons) {
                a.dx += (a.x > b.x) ? -1 : (a.x < b.x);
                a.dy += (a.y > b.y) ? -1 : (a.y < b.y);
                a.dz += (a.z > b.z) ? -1 : (a.z < b.z);
            }
        }
        // now apply velocity
        for (Moon& a : moons) {
            a.x += a.dx;
            a.y += a.dy;
            a.z += a.dz;
        }
    }

    int total_energy = 0;
    for (Moon& a : moons) {
        int potential = abs(a.x) + abs(a.y) + abs(a.z);
        int kinetic = abs(a.dx) + abs(a.dy) + abs(a.dz);
        total_energy += potential * kinetic;
    }
    std::cout << total_energy << "\n";
}
