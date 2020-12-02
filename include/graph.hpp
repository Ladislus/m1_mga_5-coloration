#ifndef INC_5_COLORATION_GRAPH_HPP
#define INC_5_COLORATION_GRAPH_HPP

#include "vertex.hpp"
#include <vector>
#include <fstream>
#include <sstream>

/**
 * Class that represent a complete non-oriented graph
 */
class Graph {

    private:
        nmap _vertices;
        Vertex* _start;

    public:
        Graph();
        ~Graph();

        void loadFile(const std::string& filepath);
        void writeFile(const std::string& filepath);

        void addVertex(const std::string& identifier, const std::initializer_list<std::string>& nidentifiers);
        void addVertex(const std::string& identifier, const std::vector<std::string>& nidentifiers);

        void coloring();
        bool checkColoring();

        friend std::ostream& operator<<(std::ostream& out, const Graph& g);
};

std::ostream& operator<<(std::ostream& out, const Graph& g);

#endif
