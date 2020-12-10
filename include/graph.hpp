#ifndef INC_5_COLORATION_GRAPH_HPP
#define INC_5_COLORATION_GRAPH_HPP

#include "vertex.hpp"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <graphviz/gvc.h>

/**
 * Class that represent a complete non-oriented graph
 */
class Graph {

    private:
        std::unordered_map<std::string, Vertex*> _vertices;
        Vertex* _start;

    public:
        Graph();
        ~Graph();

        void loadFile(const std::string& filepath);
        void loadCoords(const std::string& filepath);
        void writeFile(const std::string& filepath);

        void addVertex(const std::string& identifier, const std::vector<std::string>& nidentifiers);

        void coloring();
        bool checkColoring();
        void output();

        friend std::ostream& operator<<(std::ostream& out, const Graph& g);
};

std::ostream& operator<<(std::ostream& out, const Graph& g);

#endif
