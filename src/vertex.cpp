#include "vertex.hpp"

Vertex::Vertex(const std::string& identifier) : _identifier(identifier), _color(-1) {}

int Vertex::color() const { return this->_color; }

int& Vertex::color() { return this->_color; }

std::ostream& operator<<(std::ostream& out, const Vertex& e) {
    return out << e._identifier << "(" << e._color << ")";
}

bool Vertex::operator==(const Vertex& other) { return this->_identifier == other._identifier; }
