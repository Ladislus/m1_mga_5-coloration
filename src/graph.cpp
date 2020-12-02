#include "graph.hpp"

Graph::Graph(): _vertices(), _start(nullptr) {}

Graph::~Graph() {
    for (const auto& vertex : this->_vertices) delete vertex.second;
}

void Graph::addVertex(const std::string& identifier, const std::initializer_list<std::string>& nidentifiers) {
    Vertex* v = nullptr;
    const auto& it = this->_vertices.find(identifier);
    if (it == this->_vertices.end()) {
        v = new Vertex(identifier);
        this->_vertices.insert(std::pair(identifier, v));
    } else v = it->second;

    if (!this->_start) this->_start = v;

    for (const auto& nidentifier : nidentifiers) {
        const auto& it = this->_vertices.find(nidentifier);
        Vertex* neighbor = nullptr;
        if (it == this->_vertices.end()) {
            neighbor = new Vertex(nidentifier);
            this->_vertices.insert(std::pair(nidentifier, neighbor));
        } else neighbor = it->second;
        v->addNeighbor(neighbor);
    }
}

void Graph::solve() {

    if (this->_start == nullptr) {
        std::cerr << "Error: No vertices were added to the graph (EMPTY_GRAPH)" << std::endl;
        exit(1);
    } else this->_start->colorize();

    for (const auto& vertex : this->_vertices) {
        if (vertex.second->color() == vide) {
            std::cerr << "Error: Two neighbors have the same color" << std::endl;
            exit(1);
        }
    }
}

std::ostream& operator<<(std::ostream& out, const Graph& g) {
    for (const auto& vertex : g._vertices) out << *vertex.second << std::endl;
    return out;
}