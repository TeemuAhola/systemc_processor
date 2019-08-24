cmake_minimum_required (VERSION 2.6)

project (TestProcessor)

add_library(SystemC::systemc SHARED IMPORTED) # or STATIC instead of SHARED
set_target_properties(SystemC::systemc PROPERTIES
  IMPORTED_LOCATION "/home/teemu/Documents/Projects/systemc/systemc-2.3.3/lib-linux64/libsystemc.so"
  INTERFACE_INCLUDE_DIRECTORIES "/home/teemu/Documents/Projects/systemc/systemc-2.3.3/include/"
)

add_executable(TestProcessor TestProcessor.cpp memory.cpp)
target_link_libraries (TestProcessor SystemC::systemc)
