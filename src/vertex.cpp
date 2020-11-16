#include "vertex.hpp"

Vertex::Vertex(const std::string &identifier): _identifier(identifier), _color(-1), _neighbors() {}

const std::string& Vertex::identifier() const { return this->_identifier; }

int& Vertex::color() { return _color; }

nvector Vertex::neighbors() const {
    nvector returned;
    for (const auto& neighbor : this->_neighbors) returned.push_back(neighbor.second);
    return returned;
}

void Vertex::addNeighbor(Vertex* vertex) {
    const auto& it = this->_neighbors.find(vertex->identifier());
    if (it == this->_neighbors.end()) {
        this->_neighbors.insert(std::pair(vertex->identifier(), vertex));
        vertex->addNeighbor(this);
    }
}

std::ostream& operator<<(std::ostream& out, const Vertex& e) {
    out << e._identifier << "(" << e._color << ")" << std::endl << "\t";
    for (const auto& neighbor : e._neighbors) out << neighbor.second->identifier() << " ";
    return out << std::endl;
}
