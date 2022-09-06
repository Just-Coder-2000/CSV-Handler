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
#include "artwork/pretty-table/prettytable.hpp"
#include "csv.h"


int main(int argc, char const *argv[]) {
  ns_pretab::PrettyTable tab;
  tab.addRowGrids(
    0, 1, 0, 1, ns_pretab::Align::CENTER,
    "name", "version", "author");
  tab.addRowGrids(
    1, 1, 0, 1, ns_pretab::Align::CENTER,
    "lib-csv", "2.0", "ulong2");
  std::cout << tab << std::endl;
  return 0;
}
