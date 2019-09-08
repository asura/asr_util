include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_BINARY_DIR}/include
)

add_executable(
  Tester_asr_util
  Tester.cpp
  ResultTest.cpp
  Result2Test.cpp
  VersionTest.cpp
  string_utilsTest.cpp
)

target_link_libraries(
  Tester_asr_util
  asr_util
  Catch2::Catch2
)

add_test(
  NAME Tester_asr_util
  COMMAND $<TARGET_FILE:Tester_asr_util>
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
