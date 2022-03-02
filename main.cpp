/**
 * @file main.cpp
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2022-01-19
 *
 * @copyright Copyright (c) 2022
 */

#include "artwork/geometry/point.hpp"
#include "artwork/logger/logger.h"
#include "csv.h"

#pragma region helpers

struct Info {
private:
  /**
   * @brief the members
   */
  int _id;
  std::string _name;
  float _score;

public:
  /**
   * @brief construct a new Info object
   */
  Info(const int &id, const std::string &name, const float &score)
      : _id(id), _name(name), _score(score) {}

  inline int &id() { return this->_id; }
  inline const int &id() const { return this->_id; }

  inline std::string &name() { return this->_name; }
  inline const std::string &name() const { return this->_name; }

  inline float &score() { return this->_score; }
  inline const float &score() const { return this->_score; }
};
/**
 * @brief override operator '<<' for type 'Info'
 */
std::ostream &operator<<(std::ostream &os, const Info &obj) {
  os << '{';
  os << "'id': " << obj.id() << ", 'name': " << obj.name()
     << ", 'score': " << obj.score();
  os << '}';
  return os;
}

template <typename ElemType>
void vecOutput(const std::vector<ElemType> &vec) {
  for (const auto &elem : vec)
    std::cout << elem << '\n';
}

#pragma endregion

void test_CSV_READ_IFS_ALL() {
  ns_log::info("test the macro 'CSV_READ_IFS_ALL', file '../data/info.csv'");
  std::ifstream ifs("../data/info.csv");
  auto data = CSV_READ_IFS_ALL(ifs, ',', Info, int, std::string, float);
  vecOutput(data);
  ifs.close();
}

void test_CSV_READ_IFS_ALL_H() {
  ns_log::info("test the macro 'CSV_READ_IFS_ALL_H', file '../data/refpoint3f.csv'");
  std::ifstream ifs("../data/refpoint3f.csv");
  auto data = CSV_READ_IFS_ALL_H(ifs, ',', ns_geo::RefPoint3f, uint, float,
                                 float, float);
  ns_log::info("header: ", data.first.at(0), ',', data.first.at(1), ',',
               data.first.at(2), ',', data.first.at(3));
  vecOutput(data.second);
  ifs.close();
}

void test_CSV_READ_IFS_CER() {
  ns_log::info("test the macro 'CSV_READ_IFS_CER', file '../data/info.csv'");
  std::ifstream ifs("../data/info.csv");
  auto data = CSV_READ_IFS_CER(ifs, ',', 4, Info, int, std::string, float);
  vecOutput(data);
  ifs.close();
}

void test_CSV_READ_IFS_CER_H() {
  ns_log::info("test the macro 'CSV_READ_IFS_CER_H', file '../data/refpoint3f.csv'");
  std::ifstream ifs("../data/refpoint3f.csv");
  auto data = CSV_READ_IFS_CER_H(ifs, ',', 4, ns_geo::RefPoint3f, uint, float,
                                 float, float);
  ns_log::info("header: ", data.first.at(0), ',', data.first.at(1), ',',
               data.first.at(2), ',', data.first.at(3));
  vecOutput(data.second);
  ifs.close();
}

void test_CSV_READ_FILE() {
  ns_log::info("test the macro 'CSV_READ_FILE', file '../data/info.csv'");
  auto data =
      CSV_READ_FILE("../data/info.csv", ',', Info, int, std::string, float);
  vecOutput(data);
}

void test_CSV_READ_FILE_H() {
  ns_log::info("test the macro 'CSV_READ_FILE_H', file '../data/refpoint3f.csv'");
  auto data = CSV_READ_FILE_H("../data/refpoint3f.csv", ',', ns_geo::RefPoint3f,
                              uint, float, float, float);
  ns_log::info("header: ", data.first.at(0), ',', data.first.at(1), ',',
               data.first.at(2), ',', data.first.at(3));
  vecOutput(data.second);
}

void test_CSV_WRITE_OFS() {
  ns_log::info("test the macro 'CSV_WRITE_OFS', file '../data/point3f.csv'");
  auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f,
                                                0.0f, 1.0f);
  std::ofstream ofs("../data/point3f.csv");
  CSV_WRITE_OFS(ofs, ps, ',', CSV_ELEM(x()) * CSV_ELEM(z()),
                CSV_ELEM(x()) + CSV_ELEM(y()), CSV_ELEM(y()) - CSV_ELEM(z()),
                CSV_ELEM(z()) * CSV_ELEM(y()));
  ofs.close();
}

void test_CSV_WRITE_OFS_H() {
  ns_log::info("test the macro 'CSV_WRITE_OFS_H', file '../data/point3f.csv'");
  auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f,
                                                0.0f, 1.0f);
  std::ofstream ofs("../data/point3f.csv");
  CSV_WRITE_OFS_H(ofs, CSV_HEADER("x+z", "x+y", "y-z", "z-y"), ps, ',',
                  CSV_ELEM(x()) * CSV_ELEM(z()), CSV_ELEM(x()) + CSV_ELEM(y()),
                  CSV_ELEM(y()) - CSV_ELEM(z()), CSV_ELEM(z()) * CSV_ELEM(y()));
  auto header = CSV_HEADER("x+z", "x+y", "y-z", "z-y");
  ofs.close();
}

void test_CSV_WRITE_FILE() {
  ns_log::info("test the macro 'CSV_WRITE_FILE', file '../data/point3f.csv'");
  auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f,
                                                0.0f, 1.0f);
  CSV_WRITE_FILE("../data/point3f.csv", ps, ',', CSV_ELEM(x()) * CSV_ELEM(z()),
                 CSV_ELEM(x()) + CSV_ELEM(y()), CSV_ELEM(y()) - CSV_ELEM(z()),
                 CSV_ELEM(z()) * CSV_ELEM(y()));
}

void test_CSV_WRITE_FILE_H() {
  ns_log::info("test the macro 'CSV_WRITE_FILE_H', file '../data/point3f.csv'");
  auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f,
                                                0.0f, 1.0f);
  CSV_WRITE_FILE_H(
      "../data/point3f.csv", CSV_HEADER("x+z", "x+y", "y-z", "z-y"), ps, ',',
      CSV_ELEM(x()) * CSV_ELEM(z()), CSV_ELEM(x()) + CSV_ELEM(y()),
      CSV_ELEM(y()) - CSV_ELEM(z()), CSV_ELEM(z()) * CSV_ELEM(y()));
}

void test_CSVReader_IFS() {
  ns_log::info("test the ns_csv::CSVReader[IFS], file '../data/info.csv'");

  std::ifstream ifs("../data/info.csv");
  ns_csv::CSVReader readerIFS(ifs);

  int id;
  std::string name;
  float score;
  while (readerIFS.readLine(',', id, name, score)) {
    std::cout << Info(id, name, score) << std::endl;
  }
  ifs.close();
}

void test_CSVReader_FILE() {
  ns_log::info("test the ns_csv::CSVReader[FILE], file '../data/info.csv'");

  ns_csv::CSVReader reader("../data/info.csv");
  int id;
  std::string name;
  float score;
  while (reader.readLine(',', id, name, score)) {
    std::cout << Info(id, name, score) << std::endl;
  }
}

void test_CSVWriter_OFS() {
  ns_log::info("test the ns_csv::CSVWriter[OFS], file '../data/info.csv'");

  auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f,
                                                0.0f, 1.0f);

  std::ofstream ofs("../data/point3f.csv");
  ns_csv::CSVWriter writer(ofs);

  writer.writeItems(',', "x+z", "x+y", "y-z", "z-y");

  for (const auto &p : ps)
    writer.writeItems(',', p.x(), p.y(), p.z());

  ofs.close();
}

void test_CSVWriter_FILE() {
  ns_log::info("test the ns_csv::CSVWriter[FILE], file '../data/info.csv'");

  auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f,
                                                0.0f, 1.0f);
  ns_csv::CSVWriter writer("../data/point3f.csv");

  writer.writeItems(',', "x+z", "x+y", "y-z", "z-y");

  for (const auto &p : ps)
    writer.writeItems(',', p.x(), p.y(), p.z());
}

int main(int argc, char const *argv[]) {
  ::test_CSV_READ_IFS_ALL();
  ::test_CSV_READ_IFS_ALL_H();
  ::test_CSV_READ_IFS_CER();
  ::test_CSV_READ_IFS_CER_H();
  ::test_CSV_READ_FILE();
  ::test_CSV_READ_FILE_H();
  ::test_CSV_WRITE_OFS();
  ::test_CSV_WRITE_OFS_H();
  ::test_CSV_WRITE_FILE();
  ::test_CSV_WRITE_FILE_H();
  ::test_CSVReader_IFS();
  ::test_CSVReader_FILE();
  ::test_CSVWriter_OFS();
  ::test_CSVWriter_FILE();
  return 0;
}
