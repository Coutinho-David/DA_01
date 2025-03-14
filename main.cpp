#include "readLocations.h"
#include "readDistances.h"


int main() {

    std::vector<distance> distances = readDistances("Distances.csv");
    std::vector<location> locations = readLocations("Locations.csv");

    for (distance elem : distances) {
        std::cout << "CODE1 : " << elem.CODE1 <<
           " CODE2 :  " << elem.CODE2 << 
           " Driving : " << elem.Driving <<
           " Walking : " << elem.Walking << std::endl;
    }

    for (location elem : locations) {
        std::cout << "Location : " << elem.location <<
            " Id : " << elem.Id << 
            " Code : " << elem.CODE <<
            " Parking : " << elem.parking << std::endl;
    }

    return 0;
}

