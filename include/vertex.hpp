#ifndef INC_5_COLORATION_VERTEX_HPP
#define INC_5_COLORATION_VERTEX_HPP

#include <string>
#include <iostream>
#include <unordered_map>
#include <set>

class Vertex;
typedef std::unordered_map<std::string, Vertex*> nmap;

class Vertex {

    private:
        std::string _identifier;
        int _color;
        nmap _neighbors;

    public:
        explicit Vertex(const std::string& identifier);

        const std::string& identifier() const;
        int& color();

        void addNeighbor(Vertex* vertex);

        void colorize();

        friend std::ostream& operator<<(std::ostream& out, const Vertex& e);
};

std::ostream& operator<<(std::ostream& out, const Vertex& e);

#endif
