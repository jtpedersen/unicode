CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(Unicode)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_library(
  common
  src/common.c
  )

ADD_EXECUTABLE(
  codepointToUtf8

  src/codepointToUtf8.c
  )

target_link_libraries(codepointToUtf8 common)


ADD_EXECUTABLE(
  utf8ToCodepoint

  src/utf8ToCodepoint.c
  )
target_link_libraries(utf8ToCodepoint common)

ADD_EXECUTABLE(
  utf8ToPuny

  src/utf8ToPuny.c
  )

target_link_libraries(utf8ToPuny common)

enable_testing()

add_test(
  ruski
  ../scripts/roundtrip.sh
  ./bin/utf8ToCodepoint
  ./bin/codepointToUtf8
  ../res/ruski.txt
  )

add_test(
  kurdish
  ../scripts/roundtrip.sh
  ./bin/utf8ToCodepoint
  ./bin/codepointToUtf8
  ../res/kurdish.txt
  )

add_test(
  puny
  ../scripts/compare.sh
  ./bin/utf8ToPuny
  ../res/puny-in.txt
  ../res/puny-out.txt
  )