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

So now need to implement the `serialize` member function. TODO: As an advanced document, show what the macros actually expand to.

Following the structure of Bayeux/Falaise, this tends to be separated
out from the main class interface. Doesn't seem to be required, but
gets close to the ROOT system of main interface (header/source), linkdef
(no equivalent, handled through macros), and "dictionary".
The latter in Bayeux is typically in two files:

1. The ".ipp" files each of which defines the serialize member function
   for the class (equivalent to ROOT's Streamer)
2. The "boost_io/the_serializable" file, which implements (via macros)
   instantiation of template specializations of serialize for each
   archive type known to Bayeux. If the class requires "export" (see below)
   , the appropriate macro is also here.

"Export", that is, declaration of the BOOST_CLASS_EXPORT macro in the class
header appears needed if and only if we want to add the class as a bank
in datatools::things. Likely due to the need to hold/serialize the object
via pointer-to-base-class (as described in the boost manual). If the
class will never be a "first class" bank object, then looks like we can
skip this step.

TODO: Clear some macro simplification is possible here!!
