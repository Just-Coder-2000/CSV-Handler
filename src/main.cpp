/**
 * @file main.cpp
 * @author shlchen (3079625093@qq.com)
 * @brief 
 * @version 0.2
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "artwork/logger/logger.h"
#include "csv.h"

#pragma region helpers

struct Info {
  int _id;
  std::string _name;
  float _score;
};
std::ostream &operator<<(std::ostream &os, const Info &obj) {
  os << '{';
  os << "'id': " << obj._id << ", 'name': " << obj._name << ", 'score': " << obj._score;
  os << '}';
  return os;
}

struct RefPoint3f {
  std::size_t _id;
  float _x;
  float _y;
  float _z;
};
std::ostream &operator<<(std::ostream &os, const RefPoint3f &obj) {
  os << '{';
  os << "'id': " << obj._id << ", 'x': " << obj._x << ", 'y': " << obj._y
     << ", 'z': " << obj._z;
  os << '}';
  return os;
}
static std::vector<RefPoint3f> ps{
    {9, 0.0605643, 0.897656, 0.166507},
    {8, 0.274907, 0.477732, 0.436411},
    {7, 0.884707, 0.0726859, 0.753356},
    {6, 0.98255, 0.365339, 0.75641},
    {5, 0.328234, 0.0474645, 0.762198},
    {4, 0.701191, 0.653919, 0.526929},
    {3, 0.930436, 0.686773, 0.0668422},
    {2, 0.00769819, 0.5297, 0.0345721},
    {1, 0.519416, 0.934693, 0.678865},
    {0, 0.218959, 0.45865, 0.131538}};

template <typename ElemType>
void vecOutput(const std::vector<ElemType> &vec) {
  for (const auto &elem : vec)
    std::cout << elem << '\n';
}

#pragma endregion

void test_READ_IFS_ALL() {
  ns_log::info("'test_READ_IFS_ALL'-'../data/info.csv'");
  std::ifstream ifs("../data/info.csv");
  auto data = ns_csv::CSVReader::read<CSV_STRUCT(Info, _id, _name, _score)>(ifs, ',');
  vecOutput(data);
  ifs.close();
}

void test_READ_IFS_ALL_H() {
  ns_log::info("'test_READ_IFS_ALL_H'-'../data/refpoint3f_h.csv'");
  std::ifstream ifs("../data/refpoint3f_h.csv");
  auto data = ns_csv::CSVReader::readWithHeader<CSV_STRUCT(RefPoint3f, _id, _x, _y, _z)>(ifs, ',');

  ns_log::info("header: ", data.first.at(0), ',', data.first.at(1), ',',
               data.first.at(2), ',', data.first.at(3));
  vecOutput(data.second);
  ifs.close();
}

void test_READ_IFS_CER() {
  ns_log::info("'test_READ_IFS_CER'-'../data/info.csv'");
  std::ifstream ifs("../data/info.csv");
  auto data = ns_csv::CSVReader::read<CSV_STRUCT(Info, _id, _name, _score)>(ifs, ',', 4);
  vecOutput(data);
  ifs.close();
}

void test_READ_IFS_CER_H() {
  ns_log::info("'test_READ_IFS_CER_H'-'../data/refpoint3f_h.csv'");
  std::ifstream ifs("../data/refpoint3f_h.csv");
  auto data = ns_csv::CSVReader::readWithHeader<CSV_STRUCT(RefPoint3f, _id, _x, _y, _z)>(ifs, ',', 4);

  ns_log::info("header: ", data.first.at(0), ',', data.first.at(1), ',',
               data.first.at(2), ',', data.first.at(3));
  vecOutput(data.second);
  ifs.close();
}

void test_READ_FILE_ALL() {
  ns_log::info("'test_READ_FILE_ALL'-'../data/info.csv'");
  auto data = ns_csv::CSVReader::read<CSV_STRUCT(Info, _id, _name, _score)>("../data/info.csv", ',');
  vecOutput(data);
}

void test_READ_FILE_ALL_H() {
  ns_log::info("'test_READ_FILE_ALL_H'-'../data/refpoint3f_h.csv'");
  auto data = ns_csv::CSVReader::readWithHeader<CSV_STRUCT(RefPoint3f, _id, _x, _y, _z)>("../data/refpoint3f_h.csv", ',');
  ns_log::info("header: ", data.first.at(0), ',', data.first.at(1), ',',
               data.first.at(2), ',', data.first.at(3));
  vecOutput(data.second);
}

void test_CSV_WRITE_OFS() {
  ns_log::info("'test_CSV_WRITE_OFS'-'../data/refpoint3f.csv'");
  std::ofstream ofs("../data/refpoint3f.csv");
  ns_csv::CSVWriter::write<CSV_STRUCT(RefPoint3f, _id, _x, _y, _z)>(ofs, ',', ps);
  ofs.close();
}

void test_CSV_WRITE_OFS_H() {
  ns_log::info("'test_CSV_WRITE_OFS_H'-'../data/refpoint3f_h.csv'");
  std::ofstream ofs("../data/refpoint3f_h.csv");
  ns_csv::CSVWriter::writeWithHeader<CSV_STRUCT(RefPoint3f, _id, _x, _y, _z)>(ofs, ',', {"id", "x", "y", "z"}, ps);
  ofs.close();
}

void test_CSV_WRITE_FILE() {
  ns_log::info("'test_CSV_WRITE_FILE'-'../data/refpoint3f.csv'");
  ns_csv::CSVWriter::write<CSV_STRUCT(RefPoint3f, _id, _x, _y, _z)>("../data/refpoint3f.csv", ',', ps);
}

void test_CSV_WRITE_FILE_H() {
  ns_log::info("'test_CSV_WRITE_FILE_H'-'../data/refpoint3f_h.csv'");
  ns_csv::CSVWriter::writeWithHeader<CSV_STRUCT(RefPoint3f, _id, _x, _y, _z)>("../data/refpoint3f_h.csv", ',', {"id", "x", "y", "z"}, ps);
}

void test_CSVReader_IFS() {
  ns_log::info("'test_CSVReader_IFS'''../data/info.csv'");
  std::ifstream ifs("../data/info.csv");
  ns_csv::CSVReader::Ptr readerIFS = ns_csv::CSVReader::create(ifs);
  Info i{};
  while (readerIFS->readLine(',', i._id, i._name, i._score)) {
    std::cout << i << std::endl;
  }
  ifs.close();
}

void test_CSVReader_FILE() {
  ns_log::info("'test_CSVReader_FILE'-'../data/info.csv'");
  ns_csv::CSVReader::Ptr reader = ns_csv::CSVReader::create("../data/info.csv");
  Info i{};
  while (reader->readLine(',', i._id, i._name, i._score)) {
    std::cout << i << std::endl;
  }
}

void test_CSVWriter_OFS() {
  ns_log::info("'test_CSVWriter_OFS'-'../data/refpoint3f_h.csv'");
  std::ofstream ofs("../data/refpoint3f_h.csv");
  ns_csv::CSVWriter::Ptr writer = ns_csv::CSVWriter::create(ofs);
  writer->writeLine(',', "id", "x", "y", "z");
  for (const auto &p : ps)
    writer->writeLine(',', p._id, p._x, p._y, p._z);
  ofs.close();
}

void test_CSVWriter_FILE() {
  ns_log::info("'test_CSVWriter_FILE'-'../data/refpoint3f_h.csv'");
  ns_csv::CSVWriter::Ptr writer = ns_csv::CSVWriter::create("../data/refpoint3f_h.csv");
  writer->writeLine(',', "id", "x", "y", "z");
  for (const auto &p : ps) {
    writer->writeLine(',', p._id, p._x, p._y, p._z);
  }
}

int main(int argc, char const *argv[]) {
  ::test_READ_IFS_ALL();
  ::test_READ_IFS_ALL_H();
  ::test_READ_IFS_CER();
  ::test_READ_IFS_CER_H();
  ::test_READ_FILE_ALL();
  ::test_READ_FILE_ALL_H();

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
