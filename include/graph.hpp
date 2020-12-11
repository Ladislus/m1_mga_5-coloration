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
        /**
         * A map to store all the vertices of the graph
         */
        std::unordered_map<std::string, Vertex*> _vertices;
        /**
         * The first vertex to colorize (starting point)
         */
        Vertex* _start;

    public:
        Graph();
        ~Graph();

        /**
         * Method to load a graph from a .graphe file
         * @param filepath The path to the .graphe file
         */
        void loadFile(const std::string& filepath);
        /**
         * Method to load Vertice's coordiantes from a .coords file
         * @param filepath The path to the .coords file
         */
        void loadCoords(const std::string& filepath);
        /**
         * Method to write the graph to a .colors file
         * @param filepath The path to the .colors file
         */
        void writeFile(const std::string& filepath);

        /**
         * Method to add a Vertex to the graph
         * @param identifier The name of the Vertex
         * @param nidentifiers A list of the neighbors' names
         */
        void addVertex(const std::string& identifier, const std::vector<std::string>& nidentifiers);

        /**
         * Method to colorize the graph with 5 colors
         */
        void coloring();
        /**
         * Method to check whether or not the coloration is a valid 5-coloration
         * (No Vertex without color, or two neighbors with the same color)
         * @return true if the coloration is valid, false otherwise
         */
        bool checkColoring();
        /**
         * Method to output the graph to a png file using Graphviz
         */
        void output();

        friend std::ostream& operator<<(std::ostream& out, const Graph& g);
};

std::ostream& operator<<(std::ostream& out, const Graph& g);

#endif
