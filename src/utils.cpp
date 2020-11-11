#include "utils.hpp"

std::vector<int> range(int start, int to) {
    std::vector<int> res;
    for (int i = start; i < to; ++i) { res.push_back(i); }
    return res;
}

int min_from(std::vector<int> values, std::vector<int> indexes) {
    int min_index = indexes.at(0);
    int min_value = values.at(indexes.at(0));

    for (const int& index : indexes) {
        if (values.at(index) < min_value) {
            min_index = index;
            min_value = values.at(index);
        }
    }
    return min_index;
}