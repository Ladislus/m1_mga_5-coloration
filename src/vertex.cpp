#include "vertex.hpp"

Vertex::Vertex(const std::string& identifier): _identifier(identifier), _color(vide), _neighbors() {}

const std::string& Vertex::identifier() const { return this->_identifier; }

Color& Vertex::color() { return _color; }

const nmap& Vertex::neighbors() const { return this->_neighbors; }


std::string Vertex::printableColor() const {
    switch (this->_color) {
        case vide: return "vide";
        case blue: return "blue";
        case red: return "red";
        case green: return "green";
        case white: return "white";
        case black: return "black";
        default: return "vide";
    }
}

void Vertex::addNeighbor(Vertex* vertex) {
    const auto& it = this->_neighbors.find(vertex->identifier());
    if (it == this->_neighbors.end()) {
        this->_neighbors.insert(std::pair(vertex->identifier(), vertex));
        vertex->addNeighbor(this);
    }
}

std::set<Vertex*> Vertex::depthSearch() {
    std::set<Vertex*> seen;
    std::stack<Vertex*> todo;
    todo.push(this);

    while(!todo.empty()) {
        Vertex* v = todo.top();
        todo.pop();
        seen.insert(v);
        for (const auto& neighbor : v->neighbors())
            if (seen.find(neighbor.second) == seen.end()) todo.push(neighbor.second);
    }
    return seen;
}

void Vertex::colorize() {
    std::set<int> availableColors;
    std::set<int> colors { 0, 1, 2, 3, 4 };
    std::set<int> neighborsColor;
    for (const auto& neighbor : this->_neighbors) neighborsColor.insert(neighbor.second->color());

    if (neighborsColor.size() == colors.size()) {
        std::cerr << "Error: No available color (NO_COLOR_AVAILABLE)" << std::endl;
        exit(1);
    }

    std::set_difference(colors.begin(), colors.end(),
                        neighborsColor.begin(), neighborsColor.end(),
                        std::inserter(availableColors, availableColors.end()));

    this->_color = static_cast<Color>(*availableColors.begin());
    for (const auto& vertex : this->_neighbors) if (vertex.second->color() == vide) vertex.second->colorize();
}

std::ostream& operator<<(std::ostream& out, const Vertex& e) {
    out << e._identifier << " (" << e.printableColor() << ") [ ";
    for (const auto& neighbor : e._neighbors) out << neighbor.second->identifier() << " ";
    return out << "]";
}