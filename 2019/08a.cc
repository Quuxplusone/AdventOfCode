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
    int result = 0;
    for (int i=0; i < num_layers; ++i) {
        std::string layer = image.substr(i*size_of_layer, size_of_layer);
        int num_zeros = std::count(layer.begin(), layer.end(), '0');
        if (num_zeros < min_zeros) {
            min_zeros = num_zeros;
            result = std::count(layer.begin(), layer.end(), '1') * std::count(layer.begin(), layer.end(), '2');
        }
    }
    std::cout << result << '\n';
}
