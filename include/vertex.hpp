#ifndef INC_5_COLORATION_VERTEX_HPP
#define INC_5_COLORATION_VERTEX_HPP

#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <stack>

enum Color { vide = -1, blue = 0, red = 1, green = 2, white = 3, black = 4 };

class Vertex {

    private:
        std::string _identifier;
        Color _color;
        std::vector<Vertex*> _neighbors;

    public:
        explicit Vertex(const std::string& identifier);
        //DEBUG
        Vertex(const std::string& identifier, const Color& color);

        const std::string& identifier() const;
        Color& color();
        std::string printableColor() const;
        const std::vector<Vertex*>& neighbors() const;

        void addNeighbor(Vertex* vertex);

        bool flipIfUnreachable(Vertex* target, Vertex* ignored);
        void colorize(std::set<std::string> ignored);

        friend std::ostream& operator<<(std::ostream& out, const Vertex& e);
};

std::ostream& operator<<(std::ostream& out, const Vertex& e);

#endif
