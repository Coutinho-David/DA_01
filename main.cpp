#include "populateGraph.h"


int main() {

    Graph<std::string> graph = populate();

    auto v = graph.getVertexSet();
   // for (auto elem : v) {
   //     std::cout << elem->getInfo() << "\n";
   //}

}
