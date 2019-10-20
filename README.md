# BayeuxSerialization

A simple project to test and demonstrate serialization and schema
evolution with Bayeux/Boost.

- Test minimum infrastructure needed to bind a C++ class to allow
  it to be stored in a `datatools::things` and serialized by Bayeux/Boost
- Test serialization/deserialization for basic and brio writer/readers
- Test schema evolution with version mechanism
  - Minimum requirements to ensure backward compatibility
  - Can/Cannot rules
- Test schema evolution when class name changes (directly, or via
  namespace). NB: looks like macros/interfaces only allow this once.

# Notes
Edited through development to track observations/oddities etc

Seem to always want serialization types to inherit from `i_serializable`.
Not clear this is a hard requirement, other than only concrete classes
of `i_serializable` can be stored in `datatools::things`

TODO: Can we serialize a type not inheriting from `i_serializable`? NB:
look at Geomtools for example as that can serialize CLHEP objects.

Minimal `i_serializable` structure is:

```
// foo.h
namespace ns {
class foo : public datatools::i_serializable {
  DATATOOLS_SERIALIZATION_SERIAL_TAG_DECLARATION()
};
}

// foo.cc
#include "foo.h"
DATATOOLS_SERIALIZATION_SERIAL_TAG_IMPLEMENTATION(ns::foo, "ns::foo")

// other ns::foo implementation ...
```

This gets us to a compilable, constructible class which oddly can then
be serialized, just with no data being there. This is likely due to the
underlying serialization of i_serializable being used (slicing). In fact,
the **correct** macros to use are:

```
// foo.h
namespace ns {
class foo : public datatools::i_serializable {
  DATATOOLS_SERIALIZATION_DECLARATION()
};
}

// foo.cc
#include "foo.h"
DATATOOLS_SERIALIZATION_IMPLEMENTATION(ns::foo, "ns::foo")

// other ns::foo implementation ...
```

This now fails to link when trying to serialize the class:

```
Undefined symbols for architecture x86_64:
  "void sndata::core::hit::serialize<boost::archive::xml_oarchive>(boost::archive::xml_oarchive&, unsigned int)", referenced from:
      boost::archive::detail::oserializer<boost::archive::xml_oarchive, sndata::core::hit>::save_object_data(boost::archive::detail::basic_oarchive&, void const*) const in hit_t.cc.o
  "void sndata::core::hit::serialize<boost::archive::text_oarchive>(boost::archive::text_oarchive&, unsigned int)", referenced from:
      boost::archive::detail::oserializer<boost::archive::text_oarchive, sndata::core::hit>::save_object_data(boost::archive::detail::basic_oarchive&, void const*) const in hit_t.cc.o
  "void sndata::core::hit::serialize<boost::archive::portable_oarchive>(boost::archive::portable_oarchive&, unsigned int)", referenced from:
      boost::archive::detail::oserializer<boost::archive::portable_oarchive, sndata::core::hit>::save_object_data(boost::archive::detail::basic_oarchive&, void const*) const in hit_t.cc.o
ld: symbol(s) not found for architecture x86_64
```

So now need to implement the `serialize` member function. TODO: As an advanced document, show what
the macros actually expand to.
