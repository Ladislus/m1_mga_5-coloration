#include "graph.hpp"
#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]) {

    Graph g;

    if (argc > 1) {
        std::cout << "Loading from file : " << argv[1] << std::endl;
        g.loadFile(argv[1]);
    } else {
        std::cout << "Loading test data" << std::endl;
        g.addVertex("A", {"B", "C", "D"});
        g.addVertex("B", {"A", "C", "D"});
        g.addVertex("C", {"A", "B", "D"});
        g.addVertex("D", {"A", "B", "C"});
        g.addVertex("E", {"A"});
        std::cout << "Loading test loaded !" << std::endl;
        std::cout << g << std::endl;
    }

    g.coloring();
    if (!g.checkColoring()) {
        std::cerr << "Error: Coloring went wrong (SAME_COLOR_NEIGHBORS)" << std::endl;
        exit(1);
    } else {
        std::cout << "Coloring completed with success !" << std::endl;
        std::cout << g << std::endl;
        if (argc > 2) g.writeFile(argv[2]);
        else g.writeFile(std::filesystem::current_path().string().append("/out.colors"));
    }

    return 0;
}
