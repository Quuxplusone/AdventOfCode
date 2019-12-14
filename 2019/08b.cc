#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

int main()
{
    std::string image;
    std::cin >> image;
    int size_of_layer = 25 * 6;
    assert(image.size() % size_of_layer == 0);
    int num_layers = image.size() / size_of_layer;
    int min_zeros = INT_MAX;
    auto result = std::string(size_of_layer, '2');
    for (int i=0; i < num_layers; ++i) {
        std::string layer = image.substr(i*size_of_layer, size_of_layer);
        for (int j=0; j < size_of_layer; ++j) {
            if (result[j] == '2') result[j] = layer[j];
        }
    }
    for (int i=0; i < 6; ++i) {
        auto row = result.substr(i*25, 25);
        std::replace(row.begin(), row.end(), '0', ' ');
        std::cout << row << '\n';
    }
}
