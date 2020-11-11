#include "graph.hpp"

Graph::Graph(std::vector<Vertex*>& vertices, std::vector<Edge*>& edges) : _edges(&edges), _vertices(&vertices) {}

std::vector<Vertex> Graph::neighbors(const Vertex& e) const {
    std::vector<Vertex> neighbors;

    for (const Edge* edge : *this->_edges) {
        if (edge->from() == e) { neighbors.push_back(edge->to()); }
        else if (edge->to() == e) { neighbors.push_back(edge->from()); }
    }

    return neighbors;
}

void Graph::solve(int k) {

    std::vector<int> color_count(k, 0);

    for (Vertex* vertex : *this->_vertices) {

        std::vector<int> colors = range(0, k);

        std::vector<int> neighbors_colors;
        for (const Vertex& neighbor : this->neighbors(*vertex)) if (neighbor.color() >= 0) neighbors_colors.push_back(neighbor.color());

        std::vector<int> available_colors;
        if (!neighbors_colors.empty()) std::sort(neighbors_colors.begin(), neighbors_colors.end());
        std::set_difference(colors.begin(), colors.end(),
                            neighbors_colors.begin(), neighbors_colors.end(),
                            std::back_inserter(available_colors));

        if (available_colors.empty()) {
            std::cout << "ERROR, no available colors" << std::endl << "EXITING" << std::endl;
            exit(1);
        }

        int selected_color = min_from(color_count, available_colors);
        vertex->color() = selected_color;
        ++color_count.at(selected_color);
    }
}

std::ostream& operator<<(std::ostream& out, const Graph& g) {
    out << "[ ";
    for (const Vertex* vertex : *g._vertices) {
        out << *vertex << " ";
    }
    out << "]" << std::endl;
    for (const Edge* edge : *g._edges) {
        out << "\t" << *edge << std::endl;
    }
    return out;
}



