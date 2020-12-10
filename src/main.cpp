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
        g.addVertex("0", {"1", "2", "3", "4", "5"});
        g.addVertex("1", {"0"}, red);
        g.addVertex("2", {"0"}, blue);
        g.addVertex("3", {"0"}, green);
        g.addVertex("4", {"0"}, white);
        g.addVertex("5", {"0"}, black);
        std::cout << "Test data loaded !" << std::endl;
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
