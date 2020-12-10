#include "graph.hpp"

Graph::Graph(): _vertices(), _start(nullptr) {}

Graph::~Graph() {
    for (const auto& vertex : this->_vertices) delete vertex.second;
}

void Graph::loadFile(const std::string& filepath) {

    std::ifstream infile(filepath, std::ios::in);
    bool firstLine = true;
    std::string line;

    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            if (!firstLine) {
                // Get the first identifier (the vertex)
                std::string vertex = line.substr(0, line.find(':'));

                // Get the list of neighbors (without the '[]')
                std::string neighborsString = line.substr(line.find('[') + 1, line.size());
                neighborsString = neighborsString.substr(0, neighborsString.size() - 1);

                // Split by comma and remove spaces
                std::vector<std::string> neighbors;
                std::stringstream ss(neighborsString);
                while (ss.good()) {
                    std::string sub;
                    // Split beginning of the current line by comma, and add it inside 'sub'
                    getline(ss, sub, ',');
                    // Remove trailing spaces
                    sub.erase(std::remove(sub.begin(), sub.end(), ' '), sub.end());
                    // Add identifier to neighbors list
                    neighbors.push_back(sub);
                }
                // Added current vertex with his neighbors to the graph
                this->addVertex(vertex, neighbors);
            } else firstLine = false;
        }
        infile.close();
        std::cout << "File loaded !" << std::endl;
    } else {
        std::cerr << "Error: Couldn't open file " << filepath << " (CANNOT_OPEN_FILE)" << std::endl;
        exit(1);
    }
}

void Graph::loadCoords(const std::string &filepath) {

    std::ifstream infile(filepath, std::ios::in);
    bool firstLine = true;
    std::string line;

    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            if (!firstLine) {
                // Get the first identifier (the vertex)
                std::string vertex = line.substr(0, line.find(':'));
                this->_vertices.at(vertex)->x() = std::stoi(line.substr(line.find('(') + 1, line.find(',')));
                this->_vertices.at(vertex)->y() = std::stoi(line.substr(line.find(',') + 2, line.find(')')));
            } else firstLine = false;
        }
        infile.close();
        std::cout << "Coords loaded !" << std::endl;
    } else {
        std::cerr << "Error: Couldn't open file " << filepath << " (CANNOT_OPEN_FILE)" << std::endl;
        exit(1);
    }
}

void Graph::writeFile(const std::string& filepath) {
    std::ofstream outfile(filepath, std::ios::trunc);

    if (outfile.is_open()) {
        outfile << this->_vertices.size() << std::endl;
        for (size_t i = 0; i < this->_vertices.size(); i++) {
            Vertex* v = this->_vertices.at(std::to_string(i));
            outfile << v->identifier() << ": " << v->printableColor() << std::endl;
        }
        outfile.close();
        std::cout << "File written !" << std::endl;
    } else {
        std::cerr << "Error: Couldn't open file " << filepath << " (CANNOT_OPEN_FILE)" << std::endl;
        exit(1);
    }
}

void Graph::addVertex(const std::string& identifier, const std::vector<std::string>& nidentifiers) {
    Vertex* v;
    const auto& it = this->_vertices.find(identifier);
    if (it == this->_vertices.end()) {
        v = new Vertex(identifier);
        this->_vertices.insert(std::pair(identifier, v));
    } else v = it->second;

    if (!this->_start) this->_start = v;

    for (const auto& nidentifier : nidentifiers) {
        Vertex* neighbor;
        const auto& itNeighbor = this->_vertices.find(nidentifier);
        if (itNeighbor == this->_vertices.end()) {
            neighbor = new Vertex(nidentifier);
            this->_vertices.insert(std::pair(nidentifier, neighbor));
        } else neighbor = itNeighbor->second;
        v->addNeighbor(neighbor);
    }
}

//DEBUG
void Graph::addVertex(const std::string& identifier, const std::initializer_list<std::string>& nidentifiers, const Color& color) {
    Vertex* v;
    const auto& it = this->_vertices.find(identifier);
    if (it == this->_vertices.end()) {
        v = new Vertex(identifier, color);
        this->_vertices.insert(std::pair(identifier, v));
    } else {
        v = it->second;
        v->color() = color;
    }

    if (!this->_start) this->_start = v;

    for (const auto& nidentifier : nidentifiers) {
        Vertex* neighbor;
        const auto& itNeighbor = this->_vertices.find(nidentifier);
        if (itNeighbor == this->_vertices.end()) {
            neighbor = new Vertex(nidentifier);
            this->_vertices.insert(std::pair(nidentifier, neighbor));
        } else neighbor = itNeighbor->second;
        v->addNeighbor(neighbor);
    }
}

void Graph::addVertex(const std::string& identifier, const std::initializer_list<std::string>& nidentifiers) {
    this->addVertex(identifier, std::vector(nidentifiers));
}

void Graph::coloring() {
    if (this->_start == nullptr) {
        std::cerr << "Error: No vertices were added to the graph (EMPTY_GRAPH)" << std::endl;
        exit(1);
    } else {
        std::cout << "Starting coloring !" << std::endl;
        this->_start->colorize(std::set<std::string>());
    }
}

bool Graph::checkColoring() {
    // For each vertex in the graph ...
    for (const auto& vertex : this->_vertices) {
        // ... If the current vertex has no color, return false
        if (vertex.second->color() == vide) {
            std::cerr << "Debug: No color given to " << vertex.first << std::endl;
            return false;
        }
        // ... For each neighbor of the current vertex ...
        for (const auto& neighbor : vertex.second->neighbors()) {
            // ... If the current vertex has the same color has the neighbor, return false
            if (vertex.second->color() == neighbor->color()) {
                std::cerr << "DEBUG: " << vertex.first << " and " << neighbor->identifier() << " have the same color (" << neighbor->printableColor() << ")" << std::endl;
                return false;
            }
        }
    }
    // If everything went fine, return true;
    return true;
}

std::ostream& operator<<(std::ostream& out, const Graph& g) {
    for (const auto& vertex : g._vertices) out << *vertex.second << std::endl;
    return out;
}