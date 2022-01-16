#include "csvhandler.h"
#include <artwork/geometry/point.hpp>

int main(int argc, char const *argv[])
{
    using namespace ns_csv;
    ns_csv::CSVHandler handler();
    std::ifstream file("../data/rps3f.csv");

    auto ls = ns_csv::CSVHandler::read<ns_geo::RefPoint3f, uint, float, float, float>(file);
    for (const auto &elem : ls)
        std::cout << elem << std::endl;
    file.close();

    // auto rps = ns_geo::RefPointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    // rps.write("../data/rps3f.csv", std::ios::out);
    return 0;
}
