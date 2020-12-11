#include "graph.hpp"
#include <filesystem>

int main(int argc, char* argv[]) {

    Graph g;

    // If the program has at least one parameter ...
    if (argc >= 2) {
        std::cout << "Loading from file : " << argv[1] << std::endl;
        // ... Load the graph from the given file
        g.loadFile(argv[1]);
        // If there is a second parameter, load the coordinates from the given file
        if (argc >=3) g.loadCoords(argv[2]);
    // ... Else, raise an error
    } else {
        std::cerr << "Usage: ./5_coloration [path_to_graphe] ([path_to_coords])" << std::endl;
        exit(1);
    }

    // Launch the coloration
    g.coloring();

    // Check if the coloration went well
    if (!g.checkColoring()) {
        std::cerr << "Error: Coloring went wrong (SAME_COLOR_NEIGHBORS)" << std::endl;
        exit(1);
    // If it went well, write the result to out.colors
    } else {
        std::cout << "Coloring completed with success !" << std::endl;
        g.writeFile(std::filesystem::current_path().string().append("/out.colors"));
        // If coordinates were given, write the graphic output
        if (argc >= 3) g.output();
    }

    return 0;
}
