#include "utils.hpp"

std::vector<int> range(int start, int to) {
    std::vector<int> res;
    for (int i = start; i < to; ++i) { res.push_back(i); }
    return res;
}