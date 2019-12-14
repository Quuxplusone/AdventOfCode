#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

using Int = __int128;

struct IntcodeComputer {
    std::map<Int, Int> program;
    bool is_halted = false;
    Int pc = 0;
    Int relative_base = 0;

    std::function<Int()> do_input;
    std::function<void(Int)> do_output;

    void run_until_halt();

    Int apply_parameter_mode(Int m, Int value) {
        switch (m) {
            case 0: return program[value];
            case 1: return value;
            case 2: return program[value + relative_base];
            default: assert(false);
        }
    }

    Int& store_parameter_mode(Int m, Int value) {
        switch (m) {
            case 0: return program[value];
            case 1: assert(false);
            case 2: return program[value + relative_base];
            default: assert(false);
        }
    }
};

void IntcodeComputer::run_until_halt()
{
    while (true) {
        Int cell = program[pc];
        Int opcode = cell % 100;
        Int mode1 = (cell / 100) % 10;
        Int mode2 = (cell / 1000) % 10;
        Int mode3 = (cell / 10000) % 10;
        switch (opcode) {
            case 99: {
                is_halted = true;
                return;
            }
            case 1: {
                Int x = apply_parameter_mode(mode1, program[pc+1]);
                Int y = apply_parameter_mode(mode2, program[pc+2]);
                store_parameter_mode(mode3, program[pc+3]) = x + y;
                pc += 4;
                break;
            }
            case 2: {
                Int x = apply_parameter_mode(mode1, program[pc+1]);
                Int y = apply_parameter_mode(mode2, program[pc+2]);
                store_parameter_mode(mode3, program[pc+3]) = x * y;
                pc += 4;
                break;
            }
            case 3: {
                Int x = do_input();
                store_parameter_mode(mode1, program[pc+1]) = x;
                pc += 2;
                break;
            }
            case 4: {
                Int x = apply_parameter_mode(mode1, program[pc+1]);
                do_output(x);
                pc += 2;
                break;
            }
            case 5: {
                Int x = apply_parameter_mode(mode1, program[pc+1]);
                if (x) {
                    pc = apply_parameter_mode(mode2, program[pc+2]);
                } else {
                    pc += 3;
                }
                break;
            }
            case 6: {
                Int x = apply_parameter_mode(mode1, program[pc+1]);
                if (!x) {
                    pc = apply_parameter_mode(mode2, program[pc+2]);
                } else {
                    pc += 3;
                }
                break;
            }
            case 7: {
                Int x = apply_parameter_mode(mode1, program[pc+1]);
                Int y = apply_parameter_mode(mode2, program[pc+2]);
                store_parameter_mode(mode3, program[pc+3]) = (x < y);
                pc += 4;
                break;
            }
            case 8: {
                Int x = apply_parameter_mode(mode1, program[pc+1]);
                Int y = apply_parameter_mode(mode2, program[pc+2]);
                store_parameter_mode(mode3, program[pc+3]) = (x == y);
                pc += 4;
                break;
            }
            case 9: {
                Int x = apply_parameter_mode(mode1, program[pc+1]);
                relative_base += x;
                pc += 2;
                break;
            }
            default: assert(false);
        }
    }
}

struct Direction {
    int dx, dy;
    Direction turnleft() const {
        return Direction{-dy, dx};
    }
    Direction turnright() const {
        return Direction{dy, -dx};
    }
};

struct Position {
    int x, y;
    Position operator+(Direction d) const { return Position{x+d.dx, y+d.dy}; }
    struct Less {
        bool operator()(Position a, Position b) const {
            return (a.x < b.x) ? true : (a.x == b.x) ? (a.y < b.y) : false;
        }
    };
};

enum PaintColor : unsigned char { NONE, BLACK, WHITE };

using Grid = std::map<Position, PaintColor, Position::Less>;

struct Robot {
    IntcodeComputer computer;
    Position position;
    Direction direction;
    bool awaiting_paint_instruction;
    Grid grid;

    explicit Robot(const std::vector<Int>& program) {
        for (size_t i=0; i < program.size(); ++i) {
            computer.program[i] = program[i];
        }
        computer.do_input = [this]() {
            PaintColor color = grid[position];
            switch (color) {
                case NONE: return 0;
                case BLACK: return 0;
                case WHITE: return 1;
                default: assert(false);
            }
        };
        computer.do_output = [this](int value) {
            if (awaiting_paint_instruction) {
                switch (value) {
                    case 0: grid[position] = BLACK; break;
                    case 1: grid[position] = WHITE; break;
                    default: assert(false);
                }
                awaiting_paint_instruction = false;
            } else {
                switch (value) {
                    case 0: direction = direction.turnleft(); break;
                    case 1: direction = direction.turnright(); break;
                    default: assert(false);
                }
                position = position + direction;
                awaiting_paint_instruction = true;
            }
        };
        position = {0,0};
        direction = {-1,0};
        awaiting_paint_instruction = true;
    }
};

int main() {
    std::vector<Int> program;

    long long i;
    while (std::cin >> i) {
        program.push_back(i);
        char ch;
        std::cin >> ch;
    }

    Robot robot(program);
    robot.grid[{0,0}] = WHITE;
    robot.computer.run_until_halt();
    Position upleft = {INT_MAX, INT_MAX};
    Position downright = {INT_MIN, INT_MIN};
    for (auto&& kv : robot.grid) {
        upleft.x = std::min(upleft.x, kv.first.x);
        upleft.y = std::min(upleft.y, kv.first.y);
        downright.x = std::max(downright.x, kv.first.x);
        downright.y = std::max(downright.y, kv.first.y);
    }
    for (int i=upleft.x; i <= downright.x; ++i) {
        for (int j=upleft.y; j <= downright.y; ++j) {
            std::cout << (robot.grid[{i,j}] == WHITE ? '#' : ' ');
        }
        std::cout << "\n";
    }
}
