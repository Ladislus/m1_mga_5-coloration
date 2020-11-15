#include "graph.hpp"

Graph::Graph(std::vector<Vertex*>& vertices, std::vector<Edge*>& edges) : _edges(&edges), _vertices(&vertices) {}

std::vector<Vertex*> Graph::neighbors(const Vertex& e) const {
    std::vector<Vertex*> neighbors;

    for (const Edge* edge : *this->_edges) {
        if (*edge->from() == e) { neighbors.push_back(edge->to()); }
        else if (*edge->to() == e) { neighbors.push_back(edge->from()); }
    }

    return neighbors;
}

void Graph::solve() {

    if (!this->_vertices->empty()) {
        colorize(this->_vertices->at(0));
    } else {
        std::cout << "ERROR, Graph is empty" << std::endl << "EXITING" << std::endl;
        exit(1);
    }
}

void Graph::colorize(Vertex* vertex) {
    std::vector<int> colors = range(0, 5);
    std::vector<Vertex*> neighbors = this->neighbors(*vertex);


    std::vector<int> neighbors_colors;
    for (const Vertex* neighbor : neighbors) if (neighbor->color() >= 0) neighbors_colors.push_back(neighbor->color());

    std::vector<int> available_colors;
    if (!neighbors_colors.empty()) std::sort(neighbors_colors.begin(), neighbors_colors.end());
    std::set_difference(colors.begin(), colors.end(),
                        neighbors_colors.begin(), neighbors_colors.end(),
                        std::back_inserter(available_colors));

    if (available_colors.empty()) {
        std::cout << "ERROR, no available colors" << std::endl << "EXITING" << std::endl;
        exit(1);
    }

    int selected_color = *std::min_element(available_colors.begin(), available_colors.end());
    vertex->color() = selected_color;

    for (Vertex* leaf : neighbors) {
        if (leaf->color() < 0) {
            colorize(leaf);
        }
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



