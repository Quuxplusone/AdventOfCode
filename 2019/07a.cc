#include <cassert>
#include <deque>
#include <iostream>
#include <vector>

struct IntcodeComputer {
    std::vector<int> program;
    std::deque<int> inputs;
    std::vector<int> outputs;

    void run();

    int apply_parameter_mode(int m, int value) {
        switch (m) {
            case 0: return program[value];
            case 1: return value;
            default: assert(false);
        }
    }
};

void IntcodeComputer::run()
{
    int pc = 0;
    while (true) {
        int cell = program[pc];
        int opcode = cell % 100;
        int mode1 = (cell / 100) % 10;
        int mode2 = (cell / 1000) % 10;
        int mode3 = (cell / 10000) % 10;
        switch (opcode) {
            case 99: {
                return;
            }
            case 1: {
                int x = apply_parameter_mode(mode1, program[pc+1]);
                int y = apply_parameter_mode(mode2, program[pc+2]);
                assert(mode3 == 0);
                program[program[pc+3]] = x + y;
                pc += 4;
                break;
            }
            case 2: {
                int x = apply_parameter_mode(mode1, program[pc+1]);
                int y = apply_parameter_mode(mode2, program[pc+2]);
                assert(mode3 == 0);
                program[program[pc+3]] = x * y;
                pc += 4;
                break;
            }
            case 3: {
                assert(!inputs.empty());
                program[program[pc+1]] = inputs.front();
                inputs.pop_front();
                pc += 2;
                break;
            }
            case 4: {
                int x = apply_parameter_mode(mode1, program[pc+1]);
                outputs.push_back(x);
                pc += 2;
                break;
            }
            case 5: {
                int x = apply_parameter_mode(mode1, program[pc+1]);
                if (x) {
                    pc = apply_parameter_mode(mode2, program[pc+2]);
                } else {
                    pc += 3;
                }
                break;
            }
            case 6: {
                int x = apply_parameter_mode(mode1, program[pc+1]);
                if (!x) {
                    pc = apply_parameter_mode(mode2, program[pc+2]);
                } else {
                    pc += 3;
                }
                break;
            }
            case 7: {
                int x = apply_parameter_mode(mode1, program[pc+1]);
                int y = apply_parameter_mode(mode2, program[pc+2]);
                assert(mode3 == 0);
                program[program[pc+3]] = (x < y);
                pc += 4;
                break;
            }
            case 8: {
                int x = apply_parameter_mode(mode1, program[pc+1]);
                int y = apply_parameter_mode(mode2, program[pc+2]);
                assert(mode3 == 0);
                program[program[pc+3]] = (x == y);
                pc += 4;
                break;
            }
            default: assert(false);
        }
    }
}

int main() {
    std::vector<int> program;

    int i;
    while (std::cin >> i) {
        program.push_back(i);
        char ch;
        std::cin >> ch;
    }

    int max_volume = INT_MIN;
    std::vector<int> perm = {0,1,2,3,4};
    do {
        int volume = 0;
        for (int i=0; i < 5; ++i) {
            IntcodeComputer amp = { program, {perm[i], volume}, {} };
            amp.run();
            volume = amp.outputs.front();
        }
        max_volume = std::max(volume, max_volume);
    } while (std::next_permutation(perm.begin(), perm.end()));

    std::cout << max_volume << "\n";
}
