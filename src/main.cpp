#include "graph.hpp"
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdbool.h>

int main() {

    Graph g;

    g.addVertex("A", {"B", "C", "D"});
    g.addVertex("B", {"A", "C", "D"});
    g.addVertex("C", {"A", "B", "D"});
    g.addVertex("D", {"A", "B", "C"});

    std::cout << "Before :" << std::endl << g << std::endl;

    g.solve();

    std::cout << "After :" << std::endl << g << std::endl;

    Graph t;

    std::ifstream infile("/home/tom/Documents/Master/M1/Modelisation Graphe et Algo/JoliGraphe10.graphe");

    bool premiere_ligne = false;
    std::string line;
    while (std::getline(infile, line))
    {
      //std::cout << premiere_ligne << '\n';
      if (premiere_ligne) {
        std::string vertice = line.substr(0,line.find(':')); // nom du point point
        //std::cout << vertice << '\n';
        std::string test = line.substr(4,line.size()); // récupération de la liste d'ajacence du point sans le 1ier [
        std::string list_adjacence_sans_crochet = test.substr(0,test.size()-1); // sans le 2iem ]

        std::vector<std::string> liste_adjacence_final; // vecteur qui va recevoir la liste d'adjacence du fichier lu
        // pour tous les caractères de la liste d'acjacence
        for (size_t i = 0; i < list_adjacence_sans_crochet.size(); i++) {
          // Récupération des voisins du point de la ligne et ajout dans le vecteur d'adjacence
          liste_adjacence_final.push_back(list_adjacence_sans_crochet.substr(list_adjacence_sans_crochet.find(',')-1,1));
          //std::cout << list_adjacence_sans_crochet.substr(list_adjacence_sans_crochet.find(',')-1,1) << '\n';
          // Suppression du voisin mis dans le vecteur d'adjacence et de la virgule + espace
          list_adjacence_sans_crochet.erase(list_adjacence_sans_crochet.find(',')-1,3);
        }
        //std::cout << list_adjacence_sans_crochet << '\n';
        // Ajout dans le vecteur d'adjacence le dernier voisin du point de la ligne
        liste_adjacence_final.push_back(list_adjacence_sans_crochet);
        //t.addVertex(vertice, liste_adjacence_final);
      }
      premiere_ligne=true;
    }



    return 0;
}
