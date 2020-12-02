#include "graph.hpp"
#include <iostream>

int main() {

    Graph g;

    g.addVertex("A", {"B", "C", "D"});
    g.addVertex("B", {"A", "C", "D"});
    g.addVertex("C", {"A", "B", "D"});
    g.addVertex("D", {"A", "B", "C"});

    std::cout << "Before :" << std::endl << g << std::endl;

    g.coloring();
    if (!g.checkColoring()) {
        std::cerr << "Error: Coloring went wrong (SAME_COLOR_NEIGHBORS)" << std::endl;
        exit(1);
    } else {
        std::cout << "Coloring completed with success !" << std::endl;
        std::cout << g << std::endl;
    }

    return 0;
}
