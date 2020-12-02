#include "graph.hpp"

int main() {

    Graph g;

    g.addVertex("A", {"B", "C", "D"});
    g.addVertex("B", {"A", "C", "D"});
    g.addVertex("C", {"A", "B", "D"});
    g.addVertex("D", {"A", "B", "C"});

    std::cout << "Before :" << std::endl << g << std::endl;

    g.solve();

    std::cout << "After :" << std::endl << g << std::endl;

    return 0;
}
