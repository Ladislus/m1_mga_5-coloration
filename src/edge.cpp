#include "edge.hpp"

Edge::Edge(Vertex& from, Vertex& to) : _from(&from), _to(&to) {}

Vertex* Edge::from() const { return this->_from; }

Vertex* Edge::to() const { return this->_to; }

std::ostream& operator<<(std::ostream& out, const Edge& v) {
    return out << *v._from << " <==> " << *v._to;
}
