#include "graph.hpp"

int main() {

    Vertex v1("A");
    Vertex v2("B");
    Vertex v3("C");
    Vertex v4("D");

    std::vector<Vertex*> vertices;
    vertices.push_back(&v1);
    vertices.push_back(&v2);
    vertices.push_back(&v3);
    vertices.push_back(&v4);

    Edge e1_2(v1, v2);
    Edge e1_3(v1, v3);
    Edge e1_4(v1, v4);
    Edge e2_3(v2, v3);
    Edge e2_4(v2, v4);
    Edge e3_4(v3, v4);

    std::vector<Edge*> edges;
    edges.push_back(&e1_2);
    edges.push_back(&e1_3);
    edges.push_back(&e1_4);
    edges.push_back(&e2_3);
    edges.push_back(&e2_4);
    edges.push_back(&e3_4);

    Graph g = Graph(vertices, edges);
    std::cout << g << std::endl;

    g.solve();
    std::cout << std::endl << g << std::endl;
}
