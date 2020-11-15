#ifndef INC_5_COLORATION_EDGE_HPP
#define INC_5_COLORATION_EDGE_HPP

#include "vertex.hpp"

/**
 * Class representing an edge linking two vertices in a non-oriented graph
 */
class Edge {

    private:
        /**
         * Represent the source vertex (because it's an non-oriented graph, it can also be considered the destination vertex)
         */
        Vertex* _from;
        /**
         * Represent the destination vertex (because it's an non-oriented graph, it can also be considered the source vertex)
         */
        Vertex* _to;

    public:
        /**
         * Edge constructor
         * @param from A reference to the source vertex
         * @param to  A reference to the destination vertex
         */
        Edge(Vertex& from, Vertex& to);

        /**
         * Getter for the source vertex
         * @return A pointer to the source vertex
         */
        Vertex* from() const;
        /**
         * Getter for the destination vertex
         * @return A pointer to the destination vertex
         */
        Vertex* to() const;

        /**
         * Friend method to output the edge
         * @param out The output stream
         * @param v The current edge
         * @return The output stream which now contain the representation of the edge
         */
        friend std::ostream& operator<<(std::ostream& out, const Edge& v);
};

/**
 * Friend method to output the edge
 * @param out The output stream
 * @param v The current edge
 * @return The output stream which now contain the representation of the edge
 */
std::ostream& operator<<(std::ostream& out, const Edge& v);

#endif
