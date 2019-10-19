#ifndef SNDATA_HIT_H
#define SNDATA_HIT_H

#include <string>
#include <bayeux/datatools/i_serializable.h>

namespace sndata {
// An additional namespace is added so that we can demonstrate how
// to handle class name/space changes for backward compatibility
namespace core {

// To be stored in `datatools::things`, the class must inherit from
// `datatools::i_serializable`
class hit : public datatools::i_serializable {
 public:
  hit() = default;
  hit(int id, std::string type);

  virtual ~hit() = default;

  hit(const hit&) = default;
  hit& operator=(const hit&) = default;

  hit(hit&&) = default;
  hit& operator=(hit&&) = default;

 private:
  int id_ = 0;
  std::string type_{"none"};

  // This macro expands to the needed declaration for
  // the i_serializable member constants and functions
  DATATOOLS_SERIALIZATION_SERIAL_TAG_DECLARATION()
};

} // namespace core
} // namespace sndata

#endif // SNDATA_HIT_H

