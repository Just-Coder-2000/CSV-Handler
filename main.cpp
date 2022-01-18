#include "csvhandler.h"
#include <artwork/geometry/point.hpp>
#include <artwork/logger/logger.h>

struct Info
{
    uint _gd;
    std::string _name;
    float _score;
};

void csv_write_ofs()
{
    /**
     * @brief gen random point2f set
     */
    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);

    /**
     * @brief use macro 'CSV_WRITE_OFS' to write items
     */
    std::ofstream ofs("../data/point3f.csv");
    ns_log::process << "use macro 'CSV_WRITE_OFS' to write items to file 'point3f.csv'" << ns_log::endl;
    CSV_WRITE_OFS(ofs, ps, ',', ns_geo::Point3f, x(), y(), z());
    ofs.close();
}

void csv_write_ofs_h()
{
    /**
     * @brief gen random point2f set
     */
    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);

    /**
     * @brief use macro 'CSV_WRITE_OFS' to write items
     */
    std::ofstream ofs("../data/point3f_h.csv");
    ns_log::process << "use macro 'CSV_WRITE_OFS_H' to write header and items to file 'point3f_h.csv'" << ns_log::endl;
    CSV_WRITE_OFS_H(ofs, CSV_HEADER("x", "y", "z"), ps, ',', ns_geo::Point3f, x(), y(), z());
    ofs.close();
}

void csv_write_file()
{
    /**
     * @brief gen random point2f set
     */
    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);

    /**
     * @brief use macro 'CSV_WRITE_FILE' to write items
     */
    ns_log::process << "use macro 'CSV_WRITE_FILE' to write items to file 'point3f.csv'" << ns_log::endl;
    CSV_WRITE_FILE("../data/point3f.csv", ps, ',', ns_geo::Point3f, x(), y(), z());
}

void csv_write_file_h()
{
    /**
     * @brief gen random point2f set
     */
    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);

    /**
     * @brief use macro 'CSV_WRITE_FILE' to write items
     */
    ns_log::process << "use macro 'CSV_WRITE_FILE_H' to write herader and items to file 'point3f_h.csv'" << ns_log::endl;
    CSV_WRITE_FILE_H("../data/point3f_h.csv", CSV_HEADER("x", "y", "z"), ps, ',', ns_geo::Point3f, x(), y(), z());
}

void csv_read_ifs()
{
    std::ifstream ifs("../data/info.csv");
    /**
     * @brief use macro 'CSV_READ_IFS_CER' to read certain items
     */
    ns_log::process << "use macro 'CSV_READ_IFS_CER' to read certain items from file 'info.csv'" << ns_log::endl;
    auto rps1 = CSV_READ_IFS_CER(ifs, ',', 5, Info, uint, std::string, float);
    for (const auto &elem : rps1)
        std::cout << elem._gd << ',' << elem._name << ',' << elem._score << std::endl;

    /**
     * @brief use macro 'CSV_READ_IFS_ALL' to read all rest items
     */
    ns_log::process << "use macro 'CSV_READ_IFS_ALL' to read all rest items from file 'info.csv'" << ns_log::endl;
    auto rps2 = CSV_READ_IFS_ALL(ifs, ',', Info, uint, std::string, float);
    for (const auto &elem : rps2)
        std::cout << elem._gd << ',' << elem._name << ',' << elem._score << std::endl;
    ifs.close();
}

void csv_read_ifs_h()
{
    std::ifstream ifs1("../data/refpoint3f.csv", std::ios::in);
    ns_log::process << "use macro 'CSV_READ_IFS_ALL_H' to read all rest items from file 'refpoint3f.csv'" << ns_log::endl;
    auto rps_1 = CSV_READ_IFS_ALL_H(ifs1, ',', ns_geo::RefPoint3f, uint, float, float, float);
    ns_log::info << "header : ";
    for (const auto &label : rps_1.first)
        ns_log::info << label << ' ';
    ns_log::info << ns_log::endl;
    for (const auto &elem : rps_1.second)
        std::cout << elem << std::endl;
    ifs1.close();

    std::ifstream ifs2("../data/refpoint3f.csv", std::ios::in);
    ns_log::process << "use macro 'CSV_READ_IFS_CER_H' to read all rest items from file 'refpoint3f.csv'" << ns_log::endl;
    auto rps_2 = CSV_READ_IFS_CER_H(ifs2, ',', 4, ns_geo::RefPoint3f, uint, float, float, float);
    ns_log::info << "header : ";
    for (const auto &label : rps_2.first)
        ns_log::info << label << ' ';
    ns_log::info << ns_log::endl;
    for (const auto &elem : rps_2.second)
        std::cout << elem << std::endl;
    ifs2.close();
}

void csv_read_file()
{
    /**
     * @brief use macro 'CSV_READ_FILE' to read all items in the file
     */
    ns_log::process << "use macro 'CSV_READ_FILE' to read all items in the file" << ns_log::endl;
    auto info = CSV_READ_FILE("../data/info.csv", ',', Info, uint, std::string, float);
    for (const auto &elem : info)
        std::cout << elem._gd << ',' << elem._name << ',' << elem._score << std::endl;
}

void csv_read_file_h()
{
    /**
     * @brief use macro 'CSV_READ_FILE_H' to read all items in the file
     */
    ns_log::process << "use macro 'CSV_READ_FILE_H' to read all items from file 'refpoint3f.csv'" << ns_log::endl;
    auto rps = CSV_READ_FILE_H("../data/refpoint3f.csv", ',', ns_geo::RefPoint3f, uint, float, float, float);
    ns_log::info << "header : ";
    for (const auto &label : rps.first)
        ns_log::info << label << ' ';
    ns_log::info << ns_log::endl;
    for (const auto &elem : rps.second)
        std::cout << elem << std::endl;
}

int main(int argc, char const *argv[])
{
    csv_write_ofs();
    csv_write_ofs_h();
    csv_write_file();
    csv_write_file_h();
    csv_read_ifs();
    csv_read_ifs_h();
    csv_read_file();
    csv_read_file_h();
    return 0;
}
