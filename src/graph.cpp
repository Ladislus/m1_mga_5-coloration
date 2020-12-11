#include "graph.hpp"

Graph::Graph(): _vertices(), _start(nullptr) {}

Graph::~Graph() {
    // Free all the vertices' pointer
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

                // Get the x and y coordinates, and set them on the given vertex
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
        // Write the number of vertices
        outfile << this->_vertices.size() << std::endl;
        // For each vertex (using indexes to get them sorted by indentifier) ...
        for (size_t i = 0; i < this->_vertices.size(); i++) {
            // ... Get the Vertex ...
            Vertex* v = this->_vertices.at(std::to_string(i));
            // ... And write its identifier and color to the file
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
    // If the vertex does not already exist ...
    const auto& it = this->_vertices.find(identifier);
    if (it == this->_vertices.end()) {
        // ... Create the Vertex ...
        v = new Vertex(identifier);
        // ... And add it to the map
        this->_vertices.insert(std::pair(identifier, v));
    // ... Else get it from the map
    } else v = it->second;

    // If its the first Vertex, sets it as the starting point
    if (!this->_start) this->_start = v;

    // For each neighbor identifier ...
    for (const auto& nidentifier : nidentifiers) {
        Vertex* neighbor;
        // If the Vertex does not exist
        const auto& itNeighbor = this->_vertices.find(nidentifier);
        if (itNeighbor == this->_vertices.end()) {
            // ... Create the Vertex ...
            neighbor = new Vertex(nidentifier);
            // ... And add it to the map
            this->_vertices.insert(std::pair(nidentifier, neighbor));
        // ... Else get it from the map
        } else neighbor = itNeighbor->second;
        // Add the neighbor to the Vertex
        v->addNeighbor(neighbor);
    }
}

void Graph::coloring() {
    // If there is no Vertex in the graph, raise an error
    if (this->_start == nullptr) {
        std::cerr << "Error: No vertices were added to the graph (EMPTY_GRAPH)" << std::endl;
        exit(1);
    // Else start the coloring
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

void Graph::output() {
    // Initialise Graphviz
    GVC_t* gvc = gvContext();

    // Create a strict, undirected graph named "Graph"
    Agraph_t* g = agopen((char*)"Graph", Agstrictundirected, nullptr);

    // A list of all the pointer created (to free them at the end)
    std::vector<char*> pointers;

    // A list of all the nodes
    std::unordered_map<std::string, Agnode_t*> nodes;

    // Creation of the nodes
    for (const auto& v : this->_vertices) {
        // Because Graphviz is a C library, we must convert String to char*
        char* name = new char[v.second->identifier().length() + 1];
        char* color = new char[v.second->printableColor().length() + 1];

        strcpy(name, v.second->identifier().c_str());
        strcpy(color, v.second->printableColor().c_str());

        // Create the node inside the graph
        Agnode_t* node = agnode(g, name, 1);
        // Set its shape Circle
        agsafeset(node, (char*)"shape", (char*)"circle", (char*)"");
        // Set the style (contoured and filled)
        agsafeset(node, (char*)"style", (char*)"solid,filled", (char*)"");
        // Set the contour color to black
        agsafeset(node, (char*)"color", (char*)"black", (char*)"");
        // Set the content color with the color of the node
        agsafeset(node, (char*)"fillcolor", color, (char*)"");

        // If the node is black or blue, the text is white for better readability, else it's black
        if (v.second->color() == black || v.second->color() == blue) agsafeset(node, (char*)"fontcolor", (char*)"white", (char*)"");
        else agsafeset(node, (char*)"fontcolor", (char*)"black", (char*)"");

        // Convert the (x, y) position to char* and set it on the node
        std::string pos = std::to_string(v.second->x()).append(",").append(std::to_string(v.second->y())).append("!");
        char* c_pos = new char[pos.length() + 1];
        strcpy(c_pos, pos.c_str());
        agsafeset(node, (char*)"pos", c_pos, (char*)"");

        // Insert the node inside the node list
        nodes.insert(std::pair(v.first, node));

        // Add all pointers to the list to be free'd later
        pointers.push_back(c_pos);
        pointers.push_back(name);
        pointers.push_back(color);
    }

    // For each Vertex ...
    for (const auto& v : this->_vertices) {
        // ... For each of his neighbors ...
        for (const auto& n : v.second->neighbors()) {
            // ... Add an edge between the two node inside the graph ...
            Agedge_t* edge = agedge(g, nodes.at(v.second->identifier()), nodes.at(n->identifier()), nullptr, 1);
            // ... And set the style to "none"
            agsafeset(edge, (char*)"dir", (char*)"none", (char*)"");
        }
    }

    // Set the layout engine to "fdp"
    gvLayout(gvc, g, "fdp");
    // Write the graph to the file "out.png"
    gvRenderFilename(gvc, g, "png", "out.png");
    // Free the Layout engine
    gvFreeLayout(gvc, g);
    // Close the graph
    agclose(g);
    // Free the context of Graphviz
    gvFreeContext(gvc);

    // Free all pointers
    for (const auto& p : pointers) free(p);
}

std::ostream& operator<<(std::ostream& out, const Graph& g) {
    for (const auto& vertex : g._vertices) out << *vertex.second << std::endl;
    return out;
}