#include <iostream>

int main()
{
    int sum = 0;
    int mass;
    while (std::cin >> mass) {
        sum += (mass / 3) - 2;
    }
    std::cout << sum << "\n";
}
