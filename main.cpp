/**
 * @file main.cpp
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2022-01-19
 * 
 * @copyright Copyright (c) 2022
 */

#include "csv.h"
#include <artwork/geometry/point.hpp>
#include <artwork/logger/logger.h>

#pragma region Info struct
struct Info
{
private:
    /**
     * @brief the members
     */
    uint _grade;
    std::string _name;
    float _score;

public:
    /**
     * @brief construct a new Info object
     */
    Info(const uint &grade, const std::string &name, const float &score)
        : _grade(grade), _name(name), _score(score) {}

    inline uint &grade() { return this->_grade; }
    inline const uint &grade() const { return this->_grade; }

    inline std::string &name() { return this->_name; }
    inline const std::string &name() const { return this->_name; }

    inline float &score() { return this->_score; }
    inline const float &score() const { return this->_score; }
};
/**
 * @brief override operator '<<' for type 'Info'
 */
std::ostream &operator<<(std::ostream &os, const Info &obj)
{
    os << '{';
    os << "'grade': " << obj.grade() << ", 'name': " << obj.name() << ", 'score': " << obj.score();
    os << '}';
    return os;
}
#pragma endregion

#pragma region test functions

void csv_write_ofs()
{
    /**
     * @brief use macro 'CSV_WRITE_OFS' to write items
     */
    ns_log::process << "use macro 'CSV_WRITE_OFS' to write items to file 'point3f.csv'" << ns_log::endl;

    /**
     * @brief gen random point2f set
     */
    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    std::ofstream ofs("../data/point3f.csv");

    CSV_WRITE_OFS(ofs, ps, ',', ns_geo::Point3f, x(), y(), z());

    ofs.close();
}

void csv_write_ofs_h()
{
    /**
     * @brief use macro 'CSV_WRITE_OFS' to write items
     */
    ns_log::process << "use macro 'CSV_WRITE_OFS_H' to write header and items to file 'point3f_h.csv'" << ns_log::endl;

    std::ofstream ofs("../data/point3f_h.csv");
    /**
     * @brief gen random point2f set
     */
    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);

    CSV_WRITE_OFS_H(ofs, CSV_HEADER("x", "y", "z"), ps, ',', ns_geo::Point3f, x(), y(), z());

    ofs.close();
}

void csv_write_file()
{
    /**
     * @brief use macro 'CSV_WRITE_FILE' to write items
     */
    ns_log::process << "use macro 'CSV_WRITE_FILE' to write items to file 'point3f.csv'" << ns_log::endl;

    /**
     * @brief gen random point2f set
     */
    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);

    CSV_WRITE_FILE("../data/point3f.csv", ps, ',', ns_geo::Point3f, x(), y(), z());
}

void csv_write_file_h()
{
    /**
     * @brief use macro 'CSV_WRITE_FILE' to write items
     */
    ns_log::process << "use macro 'CSV_WRITE_FILE_H' to write herader and items to file 'point3f_h.csv'" << ns_log::endl;

    /**
     * @brief gen random point2f set
     */
    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    CSV_WRITE_FILE_H("../data/point3f_h.csv", CSV_HEADER("x", "y", "z"), ps, ',', ns_geo::Point3f, x(), y(), z());
}

void csv_read_ifs()
{
    /**
     * @brief use macro 'CSV_READ_IFS_CER' to read certain items
     */
    ns_log::process << "use macro 'CSV_READ_IFS_CER' to read certain items from file 'info.csv'" << ns_log::endl;

    std::ifstream ifs("../data/info.csv");
    auto rps1 = CSV_READ_IFS_CER(ifs, ',', 5, Info, uint, std::string, float);

    for (const auto &elem : rps1)
        std::cout << elem << std::endl;

    /**
     * @brief use macro 'CSV_READ_IFS_ALL' to read all rest items
     */
    ns_log::process << "use macro 'CSV_READ_IFS_ALL' to read all rest items from file 'info.csv'" << ns_log::endl;

    auto rps2 = CSV_READ_IFS_ALL(ifs, ',', Info, uint, std::string, float);

    for (const auto &elem : rps2)
        std::cout << elem << std::endl;

    ifs.close();
}

void csv_read_ifs_h()
{
    ns_log::process << "use macro 'CSV_READ_IFS_ALL_H' to read all rest items from file 'refpoint3f.csv'" << ns_log::endl;

    std::ifstream ifs1("../data/refpoint3f.csv", std::ios::in);
    auto rps_1 = CSV_READ_IFS_ALL_H(ifs1, ',', ns_geo::RefPoint3f, uint, float, float, float);

    std::cout << "header : ";
    for (const auto &label : rps_1.first)
        ns_log::info << label << ' ';
    std::cout << std::endl;

    for (const auto &elem : rps_1.second)
        std::cout << elem << std::endl;

    ifs1.close();

    ns_log::process << "use macro 'CSV_READ_IFS_CER_H' to read all rest items from file 'refpoint3f.csv'" << ns_log::endl;

    std::ifstream ifs2("../data/refpoint3f.csv", std::ios::in);
    auto rps_2 = CSV_READ_IFS_CER_H(ifs2, ',', 4, ns_geo::RefPoint3f, uint, float, float, float);

    std::cout << "header : ";
    for (const auto &label : rps_2.first)
        ns_log::info << label << ' ';
    std::cout << std::endl;

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
        std::cout << elem << std::endl;
}

void csv_read_file_h()
{
    /**
     * @brief use macro 'CSV_READ_FILE_H' to read all items in the file
     */
    ns_log::process << "use macro 'CSV_READ_FILE_H' to read all items from file 'refpoint3f.csv'" << ns_log::endl;

    auto rps = CSV_READ_FILE_H("../data/refpoint3f.csv", ',', ns_geo::RefPoint3f, uint, float, float, float);

    std::cout << "header : ";
    for (const auto &label : rps.first)
        ns_log::info << label << ' ';
    std::cout << std::endl;

    for (const auto &elem : rps.second)
        std::cout << elem << std::endl;
}

void CSVReader()
{
    ns_log::process << "using 'CSVReader[fileName]' to read items in the file 'info.csv'" << ns_log::endl;

    ns_csv::CSVReader reader("../data/info.csv");

    while (reader.hasNext())
    {
        auto items = reader.next();
        Info obj(std::stoi(items.at(0)), items.at(1), std::stof(items.at(2)));
        std::cout << obj << std::endl;
    }

    ns_log::process << "using 'CSVReader[ifstream]' to read items in the file 'info.csv'" << ns_log::endl;

    std::ifstream ifs("../data/info.csv");
    ns_csv::CSVReader readerIFS(ifs);

    while (readerIFS.hasNext())
    {
        auto items = readerIFS.next();
        Info obj(std::stoi(items.at(0)), items.at(1), std::stof(items.at(2)));
        std::cout << obj << std::endl;
    }

    ifs.close();
}

void CSVWriter()
{
    ns_log::process << "using 'CSVWriter[fileName]' to write items to the file 'point3f.csv'" << ns_log::endl;
    
    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    ns_csv::CSVWriter writer("../data/point3f.csv");
    
    for (const auto &p : ps)
        writer.writeItems(',', p.x(), p.y(), p.z());

    ns_log::process << "using 'CSVWriter[ofstream]' to write items to the file 'point3f.csv'" << ns_log::endl;
    
    std::ofstream ofs("../data/point3f.csv");
    ns_csv::CSVWriter writerOFS(ofs);
    
    for (const auto &p : ps)
        writerOFS.writeItems(',', p.x(), p.y(), p.z());

    ofs.close();
}

#pragma endregion

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
    CSVReader();
    CSVWriter();
    return 0;
}
