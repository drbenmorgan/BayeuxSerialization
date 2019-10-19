#include "catch.hpp"

#include <iostream>
#include "sndata/hit.h"

TEST_CASE("Basic hit construction", "") {
  sndata::core::hit h;
  std::cout << h.get_serial_tag() << std::endl;
}
