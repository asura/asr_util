include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}/vendor/Catch2/single_include
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
)

add_test(
  NAME Tester_asr_util
  COMMAND $<TARGET_FILE:Tester_asr_util>
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
