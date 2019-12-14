#include <cassert>
#include <deque>
#include <iostream>
#include <vector>

struct IntcodeComputer {
    std::vector<int> program;
    std::deque<int> inputs;
    std::deque<int> outputs;
    bool is_halted = false;
    int pc = 0;

    void reset() { is_halted = false; pc = 0; }
    void run_until_output();

    int apply_parameter_mode(int m, int value) {
        switch (m) {
            case 0: return program[value];
            case 1: return value;
            default: assert(false);
        }
    }
};

void IntcodeComputer::run_until_output()
{
    while (true) {
        int cell = program[pc];
        int opcode = cell % 100;
        int mode1 = (cell / 100) % 10;
        int mode2 = (cell / 1000) % 10;
        int mode3 = (cell / 10000) % 10;
        switch (opcode) {
            case 99: {
                is_halted = true;
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
                return;
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
    std::vector<int> perm = {5,6,7,8,9};
    do {
        IntcodeComputer amp[5];
        for (int i=0; i < 5; ++i) {
            amp[i].program = program;
            amp[i].inputs = {perm[i]};
        }
        amp[0].inputs.push_back(0);
        int current_volume_to_thrusters = INT_MIN;
        while (true) {
            for (int i=0; i < 5; ++i) {
                amp[i].run_until_output();
                if (amp[i].is_halted) goto done;
                int volume = amp[i].outputs.front();
                amp[i].outputs.pop_front();
                amp[(i+1) % 5].inputs.push_back(volume);
            }
            current_volume_to_thrusters = amp[0].inputs.back();
        }
        done:;
        max_volume = std::max(current_volume_to_thrusters, max_volume);
    } while (std::next_permutation(perm.begin(), perm.end()));

    std::cout << max_volume << "\n";
}
