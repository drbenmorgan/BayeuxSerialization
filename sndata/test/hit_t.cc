#include "catch.hpp"

#include <iostream>
#include <bayeux/datatools/io_factory.h>

#include "sndata/hit.h"

TEST_CASE("Basic hit construction", "") {
  sndata::core::hit h;

  // Serial tags should all be equal to typename
  REQUIRE(h.get_serial_tag() == "sndata::core::hit");
  REQUIRE(sndata::core::hit::serial_tag() == "sndata::core::hit");
  REQUIRE(sndata::core::hit::SERIAL_TAG == "sndata::core::hit");
}

TEST_CASE("Direct TXT De/Serialization", "") {
  sndata::core::hit h;

  datatools::data_writer serializer("sndata_hit.txt",
                                    datatools::using_multiple_archives);
  serializer.store(h);
}

TEST_CASE("Direct XML De/Serialization", "") {
  sndata::core::hit h;

  datatools::data_writer serializer("sndata_hit.xml",
                                    datatools::using_multiple_archives);
  serializer.store(h);
}
