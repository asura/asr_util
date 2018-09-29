include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}/vendor/Catch/single_include
  ${PROJECT_SOURCE_DIR}/vendor/fmt
  ${PROJECT_SOURCE_DIR}/vendor/plog/include
)

link_directories(
  ${link_directories}
  ${PROJECT_BINARY_DIR}/external_fmt-prefix/src/external_fmt-build/fmt
)

add_executable(
  Tester_asr_util
  Tester.cpp
  ResultTest.cpp
  VersionTest.cpp
)

target_link_libraries(
  Tester_asr_util
  asr_util
  fmt
)

add_dependencies(
  Tester_asr_util
  external_catch-download
)

add_dependencies(
  Tester_asr_util
  external_fmt-build
)

add_dependencies(
  Tester_asr_util
  external_plog-download
)

add_test(
  NAME Tester_asr_util
  COMMAND $<TARGET_FILE:Tester_asr_util>
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
