//
// Created by csl on 9/6/22.
//

#include "helper.h"

#ifndef CSVHANDLER_V2_READER_H
#define CSVHANDLER_V2_READER_H


TEST(csv_read, READ_IFS_ALL) {
  ns_log::info("'test_READ_IFS_ALL'-'../data/info.csv'");
  std::ifstream ifs("../data/info.csv");
  auto data = ns_csv::CSVReader::read<CSV_STRUCT(Info, _id, _name, _score) >(ifs, ',');
  ifs.close();
  EXPECT_EQ(data.size(), infoVec.size());
  for (int i = 0; i < data.size(); ++i) {
    EXPECT_EQ(data[i], infoVec[i]);
  }
}


TEST(csv_read, READ_IFS_ALL_H) {
  ns_log::info("'test_READ_IFS_ALL_H'-'../data/refpoint3f_h.csv'");
  std::ifstream ifs("../data/refpoint3f_h.csv");
  auto [header, data] = ns_csv::CSVReader::readWithHeader<CSV_STRUCT(RefPoint3f, _id, _x, _y, _z) >(ifs, ',');
  ifs.close();
  EXPECT_EQ(data.size(), rpsVec.size());
  for (int i = 0; i < data.size(); ++i) {
    EXPECT_EQ(data[i], rpsVec[i]);
  }
  for (int i = 0; i < header.size(); ++i) {
    EXPECT_EQ(header[i], rpsHeader[i]);
  }
}

TEST(csv_read, READ_IFS_CER) {
  ns_log::info("'test_READ_IFS_CER'-'../data/info.csv'");
  std::ifstream ifs("../data/info.csv");
  auto data = ns_csv::CSVReader::read<CSV_STRUCT(Info, _id, _name, _score) >(ifs, ',', 2);
  ifs.close();
  EXPECT_EQ(data.size(), 2);
  for (int i = 0; i < data.size(); ++i) {
    EXPECT_EQ(data[i], infoVec[i]);
  }
}

TEST(csv_read, READ_IFS_CER_H) {
  ns_log::info("'test_READ_IFS_CER_H'-'../data/refpoint3f_h.csv'");
  std::ifstream ifs("../data/refpoint3f_h.csv");
  auto [header, data] = ns_csv::CSVReader::readWithHeader<CSV_STRUCT(RefPoint3f, _id, _x, _y, _z) >(ifs, ',', 4);
  ifs.close();
  EXPECT_EQ(data.size(), 4);
  for (int i = 0; i < data.size(); ++i) {
    EXPECT_EQ(data[i], rpsVec[i]);
  }
  for (int i = 0; i < header.size(); ++i) {
    EXPECT_EQ(header[i], rpsHeader[i]);
  }
}

TEST(csv_read, READ_FILE_ALL) {
  ns_log::info("'test_READ_FILE_ALL'-'../data/info.csv'");
  auto data =
    ns_csv::CSVReader::read<CSV_STRUCT(Info, _id, _name, _score) >("../data/info.csv", ',');
  EXPECT_EQ(data.size(), infoVec.size());
  for (int i = 0; i < data.size(); ++i) {
    EXPECT_EQ(data[i], infoVec[i]);
  }
}

TEST(csv_read, READ_FILE_ALL_H) {
  ns_log::info("'test_READ_FILE_ALL_H'-'../data/refpoint3f_h.csv'");
  auto [header, data] =
    ns_csv::CSVReader::readWithHeader<CSV_STRUCT(RefPoint3f, _id, _x, _y, _z) >(
      "../data/refpoint3f_h.csv", ','
    );
  EXPECT_EQ(data.size(), rpsVec.size());
  for (int i = 0; i < data.size(); ++i) {
    EXPECT_EQ(data[i], rpsVec[i]);
  }
  for (int i = 0; i < header.size(); ++i) {
    EXPECT_EQ(header[i], rpsHeader[i]);
  }
}

TEST(csv_read, CSVReader_IFS) {
  ns_log::info("'test_CSVReader_IFS'''../data/info.csv'");
  std::ifstream ifs("../data/info.csv");
  ns_csv::CSVReader::Ptr readerIFS = ns_csv::CSVReader::create(ifs);
  Info info{};
  int idx = 0;
  while (readerIFS->readLine(',', info._id, info._name, info._score)) {
    EXPECT_EQ(infoVec[idx++], info);
  }
  ifs.close();
}


TEST(csv_read, CSVReader_FILE) {
  ns_log::info("'test_CSVReader_FILE'-'../data/info.csv'");
  ns_csv::CSVReader::Ptr reader = ns_csv::CSVReader::create("../data/info.csv");
  Info info{};
  int idx = 0;
  while (reader->readLine(',', info._id, info._name, info._score)) {
    EXPECT_EQ(infoVec[idx++], info);
  }
}

TEST(csv_read, CSVReader_StringVec) {
  ns_log::info("'test_CSVReader_FILE'-'../data/info.csv'");
  ns_csv::CSVReader::Ptr reader = ns_csv::CSVReader::create("../data/info.csv");
  std::vector<std::string> strVec;
  while (reader->readLine(',', strVec)) {
    LOG_VAR(strVec);
  }
}


#endif //CSVHANDLER_V2_READER_H
