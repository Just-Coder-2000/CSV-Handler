//
// Created by csl on 9/6/22.
//

#ifndef CSVHANDLER_V2_WRITER_H
#define CSVHANDLER_V2_WRITER_H

#include "helper.h"

TEST(csv_write, WRITE_OFS) {
  ns_log::info("'test_CSV_WRITE_OFS'-'../data/refpoint3f.csv'");
  std::ofstream ofs("../data/refpoint3f.csv");
  ns_csv::CSVWriter::write<CSV_STRUCT(RefPoint3f, _id, _x, _y, _z) >(ofs, ',', rpsVec);
  ofs.close();
}

TEST(csv_write, WRITE_OFS_H) {
  ns_log::info("'test_CSV_WRITE_OFS_H'-'../data/refpoint3f_h.csv'");
  std::ofstream ofs("../data/refpoint3f_h.csv");
  ns_csv::CSVWriter::writeWithHeader<CSV_STRUCT(RefPoint3f, _id, _x, _y, _z) >(
    ofs, ',', {"id", "x", "y", "z"}, rpsVec
  );
  ofs.close();
}

TEST(csv_write, WRITE_FILE) {
  ns_log::info("'test_CSV_WRITE_FILE'-'../data/refpoint3f.csv'");
  ns_csv::CSVWriter::write<CSV_STRUCT(RefPoint3f, _id, _x, _y, _z) >(
    "../data/refpoint3f.csv", ',', rpsVec
  );
}

TEST(csv_write, WRITE_FILE_H) {
  ns_log::info("'test_CSV_WRITE_FILE_H'-'../data/refpoint3f_h.csv'");
  ns_csv::CSVWriter::writeWithHeader<CSV_STRUCT(RefPoint3f, _id, _x, _y, _z) >(
    "../data/refpoint3f_h.csv", ',', {"id", "x", "y", "z"}, rpsVec
  );
}

TEST(csv_write, CSVWriter_OFS) {
  ns_log::info("'test_CSVWriter_OFS'-'../data/refpoint3f_h.csv'");
  std::ofstream ofs("../data/refpoint3f_h.csv");
  ns_csv::CSVWriter::Ptr writer = ns_csv::CSVWriter::create(ofs);
  writer->writeLine(',', "id", "x", "y", "z");
  for (const auto &p: rpsVec)
    writer->writeLine(',', p._id, p._x, p._y, p._z);
  ofs.close();
}

TEST(csv_write, CSVWriter_FILE) {
  ns_log::info("'test_CSVWriter_FILE'-'../data/refpoint3f_h.csv'");
  ns_csv::CSVWriter::Ptr writer = ns_csv::CSVWriter::create("../data/refpoint3f_h.csv");
  writer->writeLine(',', "id", "x", "y", "z");
  for (const auto &p: rpsVec) {
    writer->writeLine(',', p._id, p._x, p._y, p._z);
  }
}

#endif //CSVHANDLER_V2_WRITER_H
