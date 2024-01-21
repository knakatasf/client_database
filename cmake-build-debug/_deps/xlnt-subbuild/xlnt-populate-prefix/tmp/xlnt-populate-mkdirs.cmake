# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/claudio/Desktop/CS_Projects/Client_Database_Classic/cmake-build-debug/_deps/xlnt-src"
  "/Users/claudio/Desktop/CS_Projects/Client_Database_Classic/cmake-build-debug/_deps/xlnt-build"
  "/Users/claudio/Desktop/CS_Projects/Client_Database_Classic/cmake-build-debug/_deps/xlnt-subbuild/xlnt-populate-prefix"
  "/Users/claudio/Desktop/CS_Projects/Client_Database_Classic/cmake-build-debug/_deps/xlnt-subbuild/xlnt-populate-prefix/tmp"
  "/Users/claudio/Desktop/CS_Projects/Client_Database_Classic/cmake-build-debug/_deps/xlnt-subbuild/xlnt-populate-prefix/src/xlnt-populate-stamp"
  "/Users/claudio/Desktop/CS_Projects/Client_Database_Classic/cmake-build-debug/_deps/xlnt-subbuild/xlnt-populate-prefix/src"
  "/Users/claudio/Desktop/CS_Projects/Client_Database_Classic/cmake-build-debug/_deps/xlnt-subbuild/xlnt-populate-prefix/src/xlnt-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/claudio/Desktop/CS_Projects/Client_Database_Classic/cmake-build-debug/_deps/xlnt-subbuild/xlnt-populate-prefix/src/xlnt-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/claudio/Desktop/CS_Projects/Client_Database_Classic/cmake-build-debug/_deps/xlnt-subbuild/xlnt-populate-prefix/src/xlnt-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
