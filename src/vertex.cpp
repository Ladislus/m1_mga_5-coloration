#include "vertex.hpp"

Vertex::Vertex(const std::string& identifier, const Color& color): _identifier(identifier), _color(color), _neighbors(), _x(0), _y(0) {}

const std::string& Vertex::identifier() const { return this->_identifier; }

Color& Vertex::color() { return _color; }

const std::vector<Vertex*>& Vertex::neighbors() const { return this->_neighbors; }

int& Vertex::x() { return this->_x; }

int& Vertex::y() { return this->_y; }

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
    for (const auto& neighbor : this->_neighbors) if (neighbor->_identifier == vertex->_identifier) return;
    this->_neighbors.push_back(vertex);
}

bool Vertex::flipIfUnreachable(Vertex* target, Vertex* ignored) {
    bool reached = false;
    std::set<Vertex*> seen;
    std::stack<Vertex*> todo;
    todo.push(this);

    // Depth Search
    while(!todo.empty()) {
        Vertex* v = todo.top();
        todo.pop();
        seen.insert(v);
        for (const auto& neighbor : v->neighbors()) {
            if (neighbor->identifier() == target->identifier())
                reached = true;
            if (seen.find(neighbor) == seen.end() &&
                neighbor->identifier() != ignored->identifier() &&
                (neighbor->color() == target->color() || neighbor->color() == this->_color))
                todo.push(neighbor);
        }
    }

    if (reached) return false;

    ignored->color() = this->_color;

    for (const auto& v : seen)
        if (v->color() == target->color()) v->color() = this->color();
        else v->color() = target->color();

    return true;
}

void Vertex::colorize(std::set<std::string> ignored) {

    ignored.insert(this->_identifier);
    for (const auto& neighbor : this->_neighbors)
        if (ignored.find(neighbor->_identifier) == ignored.end() && neighbor->_color == vide)
            neighbor->colorize(ignored);

    std::set<int> availableColors;
    std::set<int> colors { 0, 1, 2, 3, 4 };
    std::set<int> neighborsColor;
    for (const auto& neighbor : this->_neighbors)
//        if (ignored.find(neighbor->_identifier) == ignored.end())
        if (neighbor->_color != vide)
            neighborsColor.insert(neighbor->color());

    if (neighborsColor.size() == colors.size()) {
        if (!this->_neighbors.at(0)->flipIfUnreachable(this->_neighbors.at(2), this))
            if (!this->_neighbors.at(1)->flipIfUnreachable(this->_neighbors.at(3), this)) {
                std::cerr << "Error: Flipping does not resolve the problem (FLIP_INEFFECTIVE)" << std::endl;
                std::cerr << "Debug: " << this->_identifier << std::endl;
                exit(1);
            }
    } else {
        std::set_difference(colors.begin(), colors.end(),
                            neighborsColor.begin(), neighborsColor.end(),
                            std::inserter(availableColors, availableColors.end()));

        this->_color = static_cast<Color>(*availableColors.begin());
    }
}

std::ostream& operator<<(std::ostream& out, const Vertex& e) {
    out << e._identifier << " { " << e._x << ", " << e._y << " } (" << e.printableColor() << ") [ ";
    for (const auto& neighbor : e._neighbors) out << neighbor->identifier() << " ";
    return out << "]";
}