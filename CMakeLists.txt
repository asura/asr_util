cmake_minimum_required(VERSION 3.1)

project(asr_util CXX)

set(CMAKE_CXX_STANDARD 98)
set(ASR_UTIL_VERSION_MAJOR 0)
set(ASR_UTIL_VERSION_MINOR 1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#######################################
# ビルド・タイプ指定(Debug or Releaseに限定)
if(CMAKE_BUILD_TYPE)
  if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    #
  elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    #
  else()
    message(FATAL_ERROR "変数CMAKE_BUILD_TYPEにはDebugかReleaseを指定してください")
  endif()
else()
  message(FATAL_ERROR "変数CMAKE_BUILD_TYPEが定義されていません")
endif()

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3")

#######################################
# CTest有効化
enable_testing()

#######################################
# カバレッジ
option(ENABLE_COVERAGE "Enable Coverage" OFF)
if (ENABLE_COVERAGE)
  include(CodeCoverage)

  APPEND_COVERAGE_COMPILER_FLAGS()

  set(COVERAGE_GCOVR_EXCLUDES '.*/vendor/.*' '.*/test/.*')

  SETUP_TARGET_FOR_COVERAGE_GCOVR_HTML(
    NAME ctest_gcovr_html
    EXECUTABLE ctest -j ${PROCESSOR_COUNT}
  )
  message("## Enable Coverage")
endif()

#######################################
# 外部パッケージ

#######################################
# 外部プロジェクト
include(ExternalProject)

###
# Catch 1
ExternalProject_Add(
  external_catch
  GIT_REPOSITORY https://github.com/philsquared/Catch.git
  GIT_TAG v1.12.2
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/Catch
  STEP_TARGETS download
  EXCLUDE_FROM_ALL TRUE
)
###
#####

#######################################
# CppCheck対応 (要 CMake 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
if (CMAKE_CXX_CPPCHECK)
    list(
        APPEND CMAKE_CXX_CPPCHECK 
            "––project=complile_commands.json"
            "--enable=warning,performance,portability"
            "-i ${CMAKE_SOURCE_DIR}/vendor"
            "--suppressions-list=${CMAKE_CURRENT_SOURCE_DIR}/CppCheckSuppressions.txt"
    )
    message("## CMAKE_CXX_CPPCHECK: ${CMAKE_CXX_CPPCHECK}")
endif()

#######################################
# config.h
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/asr/util/config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/asr/util/config.h
)

#######################################
# 本体
add_subdirectory(src)
add_subdirectory(test)
