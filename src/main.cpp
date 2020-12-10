#include "graph.hpp"
#include <filesystem>

int main(int argc, char* argv[]) {

    Graph g;

    if (argc >= 3) {
        std::cout << "Loading from file : " << argv[1] << std::endl;
        g.loadFile(argv[1]);
        g.loadCoords(argv[2]);
    } else {
        std::cerr << "Usage: ./5_coloration [path_to_graphe] [path_to_coords]" << std::endl;
        exit(1);
    }

    g.coloring();
    if (!g.checkColoring()) {
        std::cerr << "Error: Coloring went wrong (SAME_COLOR_NEIGHBORS)" << std::endl;
        exit(1);
    } else {
        std::cout << "Coloring completed with success !" << std::endl;
        std::cout << g << std::endl;
        g.writeFile(std::filesystem::current_path().string().append("/out.colors"));
        g.output();
    }

    return 0;
}
