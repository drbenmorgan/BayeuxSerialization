#include "sndata/hit.h"

// Macro that expands to the needed implementation of i_serializable's
// get_serial_tag member function and statics.
// First argument should be the fully qualified typename.
// Second argument is the "tag" for the type that the serialization
// system will use to map the type to a data block. Theoretically can
// be anything you like, but cleanest and clearest to us the fully
// qualified typename.
DATATOOLS_SERIALIZATION_IMPLEMENTATION(sndata::core::hit, "sndata::core::hit")

// Remainder of class implementation follows

namespace sndata {
namespace core {

hit::hit(int id, std::string type) : datatools::i_serializable(), id_{id}, type_{std::move(type)}{}

} // namespace core
} // namespace sndata
