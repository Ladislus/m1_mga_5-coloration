#include <algorithm>
#include "vertex.hpp"

Vertex::Vertex(const std::string& identifier): _identifier(identifier), _color(vide), _neighbors() {}

const std::string& Vertex::identifier() const { return this->_identifier; }

Color& Vertex::color() { return _color; }

void Vertex::addNeighbor(Vertex* vertex) {
    const auto& it = this->_neighbors.find(vertex->identifier());
    if (it == this->_neighbors.end()) {
        this->_neighbors.insert(std::pair(vertex->identifier(), vertex));
        vertex->addNeighbor(this);
    }
}

void Vertex::colorize() {
    std::set<int> availableColors;
    std::set<int> colors { 0, 1, 2, 3, 4 };
    std::set<int> neighborsColor;
    for (const auto& neighbor : this->_neighbors) neighborsColor.insert(neighbor.second->color());

    if (neighborsColor.size() == colors.size()) {
        std::cerr << "Error: No available color" << std::endl;
        exit(1);
    }

    std::set_difference(colors.begin(), colors.end(),
                        neighborsColor.begin(), neighborsColor.end(),
                        std::inserter(availableColors, availableColors.end()));

    this->_color = static_cast<Color>(*availableColors.begin());
    for (const auto& vertex : this->_neighbors) if (vertex.second->color() == vide) vertex.second->colorize();
}

std::ostream& operator<<(std::ostream& out, const Vertex& e) {
    out << e._identifier << "(" << e._color << ")" << std::endl << "\t";
    for (const auto& neighbor : e._neighbors) out << neighbor.second->identifier() << " ";
    return out;
}