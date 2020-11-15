#ifndef INC_5_COLORATION_GRAPH_HPP
#define INC_5_COLORATION_GRAPH_HPP

#include "vertex.hpp"
#include "edge.hpp"
#include "utils.hpp"

#include <vector>
#include <algorithm>

/**
 * Class that represent a complete non-oriented graph
 */
class Graph {

    private:
        /**
         * A vector of pointers to all the vertices of the graph
         */
        std::vector<Vertex*>* _vertices;
        /**
         * A vector of pointers to all the edges of the graph
         */
        std::vector<Edge*>* _edges;

        /**
         * Method to get all vertices neighboring a vertex
         * @param e The vertex whose neighbors we want
         * @return A vector of pointers to all the vertices that are neighbors to the vertex e
         */
        std::vector<Vertex*> neighbors(const Vertex& e) const;

        /**
         * Method to colorize a vertex of the graph
         * @param vertex A pointer to the vertex to colorize
         */
        void colorize(Vertex* vertex);

public:
        /**
         * Graph constructor
         * @param vertices A reference to a vector of pointers that point to the vertices of the graph
         * @param edges A reference to a vector of pointers that point to the edges of the graph
         */
        Graph(std::vector<Vertex*>& vertices, std::vector<Edge*>& edges);

        /**
         * Method to start the 5-coloration of the graph
         */
        void solve();

        /**
        * Friend method to output the graph
        * @param out The output stream
        * @param v The current graph
        * @return The output stream which now contain the representation of the graph
        */
        friend std::ostream& operator<<(std::ostream& out, const Graph& g);
};

/**
* Friend method to output the graph
* @param out The output stream
* @param v The current graph
* @return The output stream which now contain the representation of the graph
*/
std::ostream& operator<<(std::ostream& out, const Graph& g);

#endif
