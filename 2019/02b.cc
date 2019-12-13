#include <iostream>
#include <vector>

int run(std::vector<int> program);

int main() {
    std::vector<int> program;

    int i;
    while (std::cin >> i) {
        program.push_back(i);
        char ch;
        std::cin >> ch;
    }

    for (int noun = 0; noun < 100; ++noun) {
        for (int verb = 0; verb < 100; ++verb) {
            std::vector<int> p = program;
            p[1] = noun;
            p[2] = verb;
            int output = run(p);
            if (output == 19690720) {
                printf("%d\n", 100*noun + verb);
            }
        }
    }
}

int run(std::vector<int> program)
{
    int pc = 0;
    while (true) {
        switch (program[pc]) {
            case 99: {
                return program[0];
            }
            case 1: {
                program[program[pc+3]] = program[program[pc+1]] + program[program[pc+2]];
                pc += 4;
                break;
            }
            case 2: {
                program[program[pc+3]] = program[program[pc+1]] * program[program[pc+2]];
                pc += 4;
                break;
            }
            default: assert(false);
        }
    }
}
