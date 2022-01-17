#include "csvhandler.h"
#include <artwork/geometry/point.hpp>
#include <artwork/logger/logger.h>

struct Info
{
    uint _gd;
    std::string _name;
    float _score;

    Info(uint grade, const std::string &name, float score)
        : _gd(grade), _name(name), _score(score) {}
};

int main(int argc, char const *argv[])
{
    std::ifstream file("../data/rps3f.csv");

    /**
     * @brief use macro 'CSV_READ_ITEMS' to read certain items
     */
    ns_log::process << "use macro 'CSV_READ_ITEMS' to read certain items" << ns_log::endl;
    auto rps1 = CSV_READ_ITEMS(file, ',', 5, ns_geo::RefPoint3f, uint, float, float, float);
    for (const auto &elem : rps1)
        std::cout << elem << std::endl;

    /**
     * @brief use macro 'CSV_READ_ALL_ITEMS' to read all rest items
     */
    ns_log::process << "use macro 'CSV_READ_ALL_ITEMS' to read all rest items" << ns_log::endl;
    auto rps2 = CSV_READ_ALL_ITEMS(file, ',', ns_geo::RefPoint3f, uint, float, float, float);
    for (const auto &elem : rps2)
        std::cout << elem << std::endl;
    file.close();

    /**
     * @brief use macro 'CSV_READ_FILE' to read all items in the file
     */
    ns_log::process << "use macro 'CSV_READ_FILE' to read all items in the file" << ns_log::endl;
    auto info = CSV_READ_FILE("../data/data.csv", ',', Info, uint, std::string, float);
    for (const auto &elem : info)
        std::cout << elem._gd << ", " << elem._name << ", " << elem._score << std::endl;

    return 0;
}
