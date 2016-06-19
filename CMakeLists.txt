CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(Unicode)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


ADD_EXECUTABLE(
  codepointToUtf8

  src/codepointToUtf8.c
  )


ADD_EXECUTABLE(
  utf8ToCodepoint

  src/utf8ToCodepoint.c
  )


enable_testing()

add_test(
  ruski
  ../scripts/compare.sh
  ./bin/utf8ToCodepoint
  ./bin/codepointToUtf8
  ../res/ruski.txt
  )

add_test(
  Kurdish
  ../scripts/compare.sh
  ./bin/utf8ToCodepoint
  ./bin/codepointToUtf8
  ../res/kurdish.txt
  )