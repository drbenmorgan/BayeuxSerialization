#ifndef SNDATA_HIT_BOOST_IO_IPP
#define SNDATA_HIT_BOOST_IO_IPP

#include "sndata/hit.h"

// Serialization support
#include <boost/serialization/nvp.hpp>

// Streamers for any types our class contains and serializes
#include <bayeux/datatools/i_serializable.ipp>

namespace sndata {
namespace core {

/// Streamer for writing/reading to/from supplied Archive
template <class Archive>
void hit::serialize(Archive& ar, const unsigned int /*version*/) {
  // hit inherits from i_serializable, so must stream that first
  ar& DATATOOLS_SERIALIZATION_I_SERIALIZABLE_BASE_OBJECT_NVP;

  // Now Name-Value-Pairs for each persistent data member
  ar& boost::serialization::make_nvp("id", id_);
  ar& boost::serialization::make_nvp("type", type_);
}

}  // namespace core
}  // namespace sndata

#endif  // SNDATA_HIT_BOOST_IO_IPP
