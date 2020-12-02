#ifndef INC_5_COLORATION_VERTEX_HPP
#define INC_5_COLORATION_VERTEX_HPP

#include <string>
#include <iostream>
#include <unordered_map>
#include <set>

class Vertex;
typedef std::unordered_map<std::string, Vertex*> nmap;

enum Color { vide = -1, blue = 0, red = 1, green = 2, white = 3, black = 4 };

class Vertex {

    private:
        std::string _identifier;
        Color _color;
        nmap _neighbors;

    public:
        explicit Vertex(const std::string& identifier);

        const std::string& identifier() const;
        Color& color();

        std::string printableColor() const;

        void addNeighbor(Vertex* vertex);

        void colorize();

        friend std::ostream& operator<<(std::ostream& out, const Vertex& e);
};

std::ostream& operator<<(std::ostream& out, const Vertex& e);

#endif
