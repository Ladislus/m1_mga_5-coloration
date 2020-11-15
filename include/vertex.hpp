#ifndef INC_5_COLORATION_VERTEX_HPP
#define INC_5_COLORATION_VERTEX_HPP

#include <string>
#include <iostream>

/**
 * Class representing a vertex in a non-oriented graph
 */
class Vertex {

    private:
        /**
         * A string representing the identifier (or the name) of the vertex
         */
        std::string _identifier;

        /**
         * An integer representing the color of the current vertex (-1 means it's not colored)
         */
        int _color;

    public:
        /**
         * Vertex constructor (Set the color to the default value -1)
         * @param identifier The identifier of the vertex
         */
        explicit Vertex(const std::string& identifier);

        /**
         * Getter for the color
         * @return A reference to the color of the vertex
         */
        int& color();

        /**
         * Constant getter for the color
         * @return The color of the vertex
         */
        int color() const;

        /**
         * Overload of the equality operator between two vertices
         * @param other A constant reference to vertex to be compared with
         * @return
         */
        bool operator==(const Vertex& other);

        /**
        * Friend method to output the vertex
        * @param out The output stream
        * @param v The current vertex
        * @return The output stream which now contain the representation of the vertex
        */
        friend std::ostream& operator<<(std::ostream& out, const Vertex& e);
};

/**
* Friend method to output the vertex
* @param out The output stream
* @param v The current vertex
* @return The output stream which now contain the representation of the vertex
*/
std::ostream& operator<<(std::ostream& out, const Vertex& e);

#endif
