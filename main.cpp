#include "csvhandler.h"
#include <artwork/geometry/point.hpp>
#include <artwork/logger/logger.h>

struct Info
{
    uint _gd;
    std::string _name;
    float _score;
};

#define WRITE

int main(int argc, char const *argv[])
{
    /**
     * @brief gen random point2f set
     */
    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);

    /**
     * @brief use macro 'CSV_WRITE_OFS' to write items
     */
    std::ofstream ofs("../data/point3f_ofs.csv");
    ns_log::process << "use macro 'CSV_WRITE_OFS' to write items" << ns_log::endl;
    CSV_WRITE_OFS(ofs, ps, ',', ns_geo::Point3f, x(), y(), z());
    ofs.close();

    /**
     * @brief use macro 'CSV_WRITE_FILE' to write items
     */
    ns_log::process << "use macro 'CSV_WRITE_FILE' to write items" << ns_log::endl;
    CSV_WRITE_FILE("../data/point3f_file.csv", ps, ',', ns_geo::Point3f, x(), y(), z());

    std::ifstream ifs("../data/refpoint3f.csv");
    /**
     * @brief use macro 'CSV_READ_IFS_CER' to read certain items
     */
    ns_log::process << "use macro 'CSV_READ_ITEMS' to read certain items" << ns_log::endl;
    auto rps1 = CSV_READ_IFS_CER(ifs, ',', 5, ns_geo::RefPoint3f, uint, float, float, float);
    for (const auto &elem : rps1)
        std::cout << elem << std::endl;

    /**
     * @brief use macro 'CSV_READ_IFS_ALL' to read all rest items
     */
    ns_log::process << "use macro 'CSV_READ_ALL_ITEMS' to read all rest items" << ns_log::endl;
    auto rps2 = CSV_READ_IFS_ALL(ifs, ',', ns_geo::RefPoint3f, uint, float, float, float);
    for (const auto &elem : rps2)
        std::cout << elem << std::endl;
    ifs.close();

    /**
     * @brief use macro 'CSV_READ_FILE' to read all items in the file
     */
    ns_log::process << "use macro 'CSV_READ_FILE' to read all items in the file" << ns_log::endl;
    auto info = CSV_READ_FILE("../data/info.csv", ',', Info, uint, std::string, float);
    for (const auto &elem : info)
        std::cout << elem._gd << ", " << elem._name << ", " << elem._score << std::endl;

    return 0;
}
