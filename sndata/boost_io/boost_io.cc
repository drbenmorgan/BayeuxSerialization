#include <datatools/archives_instantiation.h>

// Headers for all streamers defined in this library
#include <sndata/boost_io/hit.ipp>

// This ensures instantiation of ClassName::serialize<Archive>
// specializations for all Archive types known to Bayeux.
DATATOOLS_SERIALIZATION_CLASS_SERIALIZE_INSTANTIATE_ALL(sndata::core::hit)
