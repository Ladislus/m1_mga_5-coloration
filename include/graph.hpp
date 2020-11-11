#ifndef INC_5_COLORATION_GRAPH_HPP
#define INC_5_COLORATION_GRAPH_HPP

#include "vertex.hpp"
#include "edge.hpp"
#include "utils.hpp"

#include <vector>
#include <algorithm>

class Graph {

    private:

        std::vector<Vertex*>* _vertices;
        std::vector<Edge*>* _edges;

        std::vector<Vertex> neighbors(const Vertex& e) const;

    public:

        Graph(std::vector<Vertex*>& vertices, std::vector<Edge*>& edges);

        void solve(int k);

        friend std::ostream& operator<<(std::ostream& out, const Graph& g);
};

std::ostream& operator<<(std::ostream& out, const Graph& g);

#endif //INC_5_COLORATION_GRAPH_HPP
