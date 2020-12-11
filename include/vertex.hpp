#ifndef INC_5_COLORATION_VERTEX_HPP
#define INC_5_COLORATION_VERTEX_HPP

#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <stack>

/**
 * Enum to represent all 5 colors available for coloring
 */
enum Color { vide = -1, blue = 0, red = 1, green = 2, white = 3, black = 4 };

/**
 * Class that represent a Vertex inside the graph
 * These vertices are created with an adjacency list
 */
class Vertex {

    private:
        /**
         * The identifier of the Vertex
         */
        std::string _identifier;
        /**
         * The color of the vertex (default: vide)
         */
        Color _color;
        /**
         * A list of pointers to all the neighbors of the Vertex
         */
        std::vector<Vertex*> _neighbors;
        /**
         * (x, y) position for graphic output (default: 0)
         */
        int _x, _y;

    public:
        explicit Vertex(const std::string& identifier, const Color& color = vide);

        /**
         * Method to get the identifier
         * @return the identifier of the vertex (const reference to prevent copy)
         */
        const std::string& identifier() const;
        /**
         * Getter / Setter of the color of the vertex
         * @return A reference to the color of the Vertex
         */
        Color& color();
        /**
         * Method to get the string representation of the color of the Vertex
         * @return The color of the Vertex
         */
        std::string printableColor() const;
        /**
         * Method to get the list a neighbors of the Vertex (const reference to prevent copy)
         * @return The list of neighbors
         */
        const std::vector<Vertex*>& neighbors() const;
        /**
         * Getter / Setter of the x coordinate
         * @return A reference to the x coordinate
         */
        int& x();
        /**
        * Getter / Setter of the y coordinate
        * @return A reference to the y coordinate
        */
        int& y();

        /**
         * Method to add a Vertex to the list of neighbors
         * @param vertex A pointer to the Vertex to add
         */
        void addNeighbor(Vertex* vertex);

        /**
         * Method to check whether or not the current Vertex can reach the target Vertex on
         * the subgraph that contains all the vertices that have the same color as ourself or target,
         * and free one color by flipping all the colors of this subgraph if they can't reach one another
         * @param target The Vertex that we try to reach
         * @param ignored The Vertex that called the function (G' = G - x)
         * @return false if they can reach one another, true if they can't and the colors were flipped
         */
        bool flipIfUnreachable(Vertex* target, Vertex* ignored);
        /**
         * Method to colorize the current Vertex
         * @param ignored A list of all the vertices that must be ignored
         */
        void colorize(std::set<std::string> ignored);

        friend std::ostream& operator<<(std::ostream& out, const Vertex& e);
};

std::ostream& operator<<(std::ostream& out, const Vertex& e);

#endif
