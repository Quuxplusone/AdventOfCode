#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>

struct Dir {
    char direction;
    int distance;

    friend std::istream& operator>>(std::istream& in, Dir& d) {
        return in >> d.direction >> d.distance;
    }
    friend std::ostream& operator<<(std::ostream& out, Dir d) {
        return out << d.direction << d.distance;
    }
};

struct Position {
    int x, y;

    friend Position operator+(Position p, Dir d) {
        switch (d.direction) {
            case 'U': return Position{p.x + d.distance, p.y};
            case 'D': return Position{p.x - d.distance, p.y};
            case 'R': return Position{p.x, p.y + d.distance};
            case 'L': return Position{p.x, p.y - d.distance};
            default: assert(false);
        }
    }

    int manhattanMagnitude() const {
        return std::abs(x) + std::abs(y);
    }
};

struct LineSegment {
    Position a;
    Position b;
    explicit LineSegment(Position a, Position b) : a(a), b(b) {}

    bool isHorizontal() const {
        return a.x == b.x;
    }

    static bool isBetween(int a, int b, int c) {
        if (a < b && b < c) return true;
        if (c < b && b < a) return true;
        return false;
    }

    std::optional<Position> crossingWith(const LineSegment& other) const {
        if (isHorizontal() == other.isHorizontal()) return std::nullopt;
        if (isHorizontal()) {
            int myX = a.x;
            int otherY = other.a.y;
            if (isBetween(other.a.x, myX, other.b.x) && isBetween(a.y, otherY, b.y)) return Position{myX, otherY};
            return std::nullopt;
        } else {
            int myY = a.y;
            int otherX = other.a.x;
            if (isBetween(other.a.y, myY, other.b.y) && isBetween(a.x, otherX, b.x)) return Position{otherX, myY};
            return std::nullopt;
        }
    }
};

std::vector<LineSegment> splitIntoWires(std::string s)
{
    std::istringstream in(s);
    Dir d;
    Position pos = {0, 0};
    std::vector<LineSegment> wires;
    while (in >> d) {
        Position newpos = pos + d;
        wires.emplace_back(pos, newpos);
        pos = newpos;

        char comma;
        if ((in >> comma) && (comma == ',')) continue;
        break;
    }
    return wires;
}

int main()
{
    std::string s;
    std::cin >> s;
    std::vector<LineSegment> wire1 = splitIntoWires(s);
    std::cin >> s;
    std::vector<LineSegment> wire2 = splitIntoWires(s);

    int result = INT_MAX;
    for (auto& one : wire1) {
        for (auto& two : wire2) {
            std::optional<Position> crossing = one.crossingWith(two);
            if (crossing.has_value()) {
                int m = crossing->manhattanMagnitude();
                result = std::min(result, m);
            }
        }
    }
    std::cout << result << "\n";
}
