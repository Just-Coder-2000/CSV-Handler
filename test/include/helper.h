//
// Created by csl on 9/6/22.
//

#ifndef CSVHANDLER_V2_HELPER_H
#define CSVHANDLER_V2_HELPER_H

#include "csv.h"
#include "gtest/gtest.h"
#define FORMAT_VECTOR
#include "artwork/logger/logger.h"

struct Info {
  int _id;
  std::string _name;
  float _score;

  friend std::ostream &operator<<(std::ostream &os, const Info &info) {
    os << "_id: " << info._id << " _name: " << info._name << " _score: " << info._score;
    return os;
  }

  bool operator==(const Info &rhs) const {
    return _id == rhs._id &&
           _name == rhs._name &&
           _score == rhs._score;
  }

};

static std::vector<Info> infoVec{
  Info{201901, "Tom", 81.1},
  Info{201902, "John", 0.0},
  Info{201903, "Jer ry", 95.3}
};

struct RefPoint3f {
  std::size_t _id;
  float _x;
  float _y;
  float _z;

  friend std::ostream &operator<<(std::ostream &os, const RefPoint3f &f) {
    os << "_id: " << f._id << " _x: " << f._x << " _y: " << f._y << " _z: " << f._z;
    return os;
  }

  bool operator==(const RefPoint3f &rhs) const {
    return _id == rhs._id &&
           _x == rhs._x &&
           _y == rhs._y &&
           _z == rhs._z;
  }

};

static std::vector<RefPoint3f> rpsVec{
  {9, 0.060564, 0.897656, 0.166507},
  {8, 0.274907, 0.477732, 0.436411},
  {7, 0.884707, 0.072685, 0.753356},
  {6, 0.982550, 0.365339, 0.756410},
  {5, 0.328234, 0.047464, 0.762198},
  {4, 0.701191, 0.653919, 0.526929},
  {3, 0.930436, 0.686773, 0.066842},
  {2, 0.007698, 0.529700, 0.034572},
  {1, 0.519416, 0.934693, 0.678865},
  {0, 0.218959, 0.458650, 0.131538}};

static std::array<std::string, 4> rpsHeader = {
  "id", "x", "y", "z"
};


#endif //CSVHANDLER_V2_HELPER_H
