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
    // If vertex is already a neighbor, skip
    for (const auto& neighbor : this->_neighbors) if (neighbor->_identifier == vertex->_identifier) return;
    // Else add vertex to the list of neighbors
    this->_neighbors.push_back(vertex);
}

bool Vertex::flipIfUnreachable(Vertex* target, Vertex* ignored) {
    // Variable to store whether or not the target has been reached
    bool reached = false;
    std::set<Vertex*> seen;
    // LIFO structure for depth search
    std::stack<Vertex*> todo;
    todo.push(this);

    // Depth Search
    while(!todo.empty()) {
        Vertex* v = todo.top();
        todo.pop();
        seen.insert(v);
        // For all the neighbors of the current Vertex
        for (const auto& neighbor : v->neighbors()) {
            // If the neighbor is the target, set reached to trye
            if (neighbor->identifier() == target->identifier())
                reached = true;
            // If the neighbor has not already been seen, is part of the correct subgraph, and is not ignored, add it to the todo list
            if (seen.find(neighbor) == seen.end() &&
                neighbor->identifier() != ignored->identifier() &&
                (neighbor->color() == target->color() || neighbor->color() == this->_color))
                todo.push(neighbor);
        }
    }

    // If the two vertices can reach one another, return false
    if (reached) return false;

    // Else, set the caller's color to the color that is going to be free'd
    ignored->color() = this->_color;

    // For each element in the depth search, swap the colors (block 3)
    for (const auto& v : seen)
        if (v->color() == target->color()) v->color() = this->color();
        else v->color() = target->color();

    // Return true
    return true;
}

void Vertex::colorize(std::set<std::string> ignored) {
    // Add itself to the ignored list for leaves vertices
    ignored.insert(this->_identifier);
    // Recursive call for all leaves neighbors that are not already colored
    for (const auto& neighbor : this->_neighbors)
        if (ignored.find(neighbor->_identifier) == ignored.end() && neighbor->_color == vide)
            neighbor->colorize(ignored);

    std::set<int> availableColors;
    std::set<int> colors { 0, 1, 2, 3, 4 };
    std::set<int> neighborsColor;
    // Get the colors of the neighbors
    for (const auto& neighbor : this->_neighbors)
        if (neighbor->_color != vide)
            neighborsColor.insert(neighbor->color());

    // If all 5 colors are already used by the neighbors ...
    if (neighborsColor.size() == colors.size()) {
        // ... Try block 6 with a and c ...
        if (!this->_neighbors.at(0)->flipIfUnreachable(this->_neighbors.at(2), this))
            // ... If it failed, try block 6 with b and d ...
            if (!this->_neighbors.at(1)->flipIfUnreachable(this->_neighbors.at(3), this)) {
                // ... If both failed, there is a problem, raise an error
                std::cerr << "Error: Flipping does not resolve the problem (FLIP_INEFFECTIVE)" << std::endl;
                std::cerr << "Debug: " << this->_identifier << std::endl;
                exit(1);
            }
    // If there are less than 5 colors used
    } else {
        // Compute the complement of the available colors with the colors used
        std::set_difference(colors.begin(), colors.end(),
                            neighborsColor.begin(), neighborsColor.end(),
                            std::inserter(availableColors, availableColors.end()));

        // Set the color of the Vertex to the first color available
        this->_color = static_cast<Color>(*availableColors.begin());
    }
}

std::ostream& operator<<(std::ostream& out, const Vertex& e) {
    out << e._identifier << " { " << e._x << ", " << e._y << " } (" << e.printableColor() << ") [ ";
    for (const auto& neighbor : e._neighbors) out << neighbor->identifier() << " ";
    return out << "]";
}