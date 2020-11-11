#ifndef INC_5_COLORATION_VERTEX_HPP
#define INC_5_COLORATION_VERTEX_HPP

#include <string>
#include <iostream>

class Vertex {

    private:

        std::string _identifier;
        int _color;

    public:
        explicit Vertex(const std::string& identifier);

        int& color();
        int color() const;

        bool operator==(const Vertex& other);

        friend std::ostream& operator<<(std::ostream& out, const Vertex& e);
};

std::ostream& operator<<(std::ostream& out, const Vertex& e);

#endif //INC_5_COLORATION_VERTEX_HPP
