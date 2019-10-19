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
