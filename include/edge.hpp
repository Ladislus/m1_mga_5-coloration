#ifndef INC_5_COLORATION_EDGE_HPP
#define INC_5_COLORATION_EDGE_HPP

#include "vertex.hpp"

class Edge {

    private:

        Vertex* _from;
        Vertex* _to;

    public:
        Edge(Vertex& from, Vertex& to);

        Vertex* from() const;
        Vertex* to() const;

        friend std::ostream& operator<<(std::ostream& out, const Edge& v);
};

std::ostream& operator<<(std::ostream& out, const Edge& v);

#endif //INC_5_COLORATION_EDGE_HPP
