#include <cassert>
#include <deque>
#include <iostream>
#include <map>
#include <vector>

using Int = __int128;

struct IntcodeComputer {
    std::map<Int, Int> program;
    std::deque<Int> inputs;
    std::deque<Int> outputs;
    bool is_halted = false;
    Int pc = 0;
    Int relative_base = 0;

    void reset() { is_halted = false; pc = 0; }
    void run_until_output();

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

void IntcodeComputer::run_until_output()
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
                assert(!inputs.empty());
                store_parameter_mode(mode1, program[pc+1]) = inputs.front();
                inputs.pop_front();
                pc += 2;
                break;
            }
            case 4: {
                Int x = apply_parameter_mode(mode1, program[pc+1]);
                outputs.push_back(x);
                pc += 2;
                return;
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

int main() {
    std::vector<Int> program;

    long long i;
    while (std::cin >> i) {
        program.push_back(i);
        char ch;
        std::cin >> ch;
    }

    IntcodeComputer c;
    for (size_t i=0; i < program.size(); ++i) {
        c.program[i] = program[i];
    }
    c.inputs = {1};
    while (!c.is_halted) {
        c.run_until_output();
    }
    for (Int i : c.outputs) {
        std::cout << (long long)(i) << "\n";
    }
}
