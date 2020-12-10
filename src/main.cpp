#include "graph.hpp"
#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]) {

    Graph g;

    if (argc == 1) {
        //Debug graph to test block 6
        std::cout << "Loading test data" << std::endl;
        g.addVertex("0", {"1", "2", "3", "4", "5"});
        g.addVertex("1", {"0"}, red);
        g.addVertex("2", {"0", "6"}, blue);
        g.addVertex("3", {"0"}, green);
        g.addVertex("4", {"0", "7"}, white);
        g.addVertex("5", {"0"}, black);
        g.addVertex("6", {"2", "7"}, red);
        g.addVertex("7", {"6", "4"}, blue);
        std::cout << "Test data loaded !" << std::endl;
        std::cout << g << std::endl;
    } else if (argc >= 3) {
        std::cout << "Loading from file : " << argv[1] << std::endl;
        g.loadFile(argv[1]);
        g.loadCoords(argv[2]);
    } else {
        std::cerr << "Usage: ./5_coloration ([path_to_graphe] [path_to_coords] ([path_to_output]))" << std::endl;
        exit(1);
    }

    g.coloring();
    if (!g.checkColoring()) {
        std::cerr << "Error: Coloring went wrong (SAME_COLOR_NEIGHBORS)" << std::endl;
        exit(1);
    } else {
        std::cout << "Coloring completed with success !" << std::endl;
        std::cout << g << std::endl;
        if (argc >= 4) g.writeFile(argv[2]);
        else g.writeFile(std::filesystem::current_path().string().append("/out.colors"));
    }

    return 0;
}
