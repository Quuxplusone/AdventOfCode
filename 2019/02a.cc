#include <iostream>
#include <vector>

int main() {
    std::vector<int> program;

    int i;
    while (std::cin >> i) {
        program.push_back(i);
        char ch;
        std::cin >> ch;
    }

    program[1] = 12;
    program[2] = 2;

    int pc = 0;
    while (true) {
        switch (program[pc]) {
            case 99: goto done;
            case 1: {
                program[program[pc+3]] = program[program[pc+1]] + program[program[pc+2]];
                break;
            }
            case 2: {
                program[program[pc+3]] = program[program[pc+1]] * program[program[pc+2]];
                break;
            }
            default: assert(false);
        }
        pc += 4;
    }

    done:
    std::cout << program[0] << "\n";
}
