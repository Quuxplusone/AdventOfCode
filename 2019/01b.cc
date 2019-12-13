#include <iostream>

int fuel_of(int mass)
{
    int f = (mass / 3) - 2;
    if (f <= 0) return 0;
    return f + fuel_of(f);
}

int main()
{
    int sum = 0;
    int mass;
    while (std::cin >> mass) {
        sum += fuel_of(mass);
    }
    std::cout << sum << "\n";
}
