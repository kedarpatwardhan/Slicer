#
# OS: Ubuntu 9.04  2.6.28-19-generic
# Hardware: x86_64 GNU/Linux
# GPU: NA

# Note: The specific version and processor type of this machine should be reported in the 
# header above. Indeed, this file will be send to the dashboard as a NOTE file. 

cmake_minimum_required(VERSION 2.8.2)

#
# For additional information, see http://www.slicer.org/slicerWiki/index.php/Slicer4:_Dashboard_Setup
#

#
# Dashboard properties
#
set(MY_OPERATING_SYSTEM   "Linux") # Windows, Linux, Darwin... 
set(MY_COMPILER           "g++4.4.3")
set(MY_QT_VERSION         "4.7")
set(QT_QMAKE_EXECUTABLE   "$ENV{HOME}/Dashboards/Support/qtsdk-2010.05/qt/bin/qmake")
set(CTEST_SITE            "karakoram.kitware") # for example: mymachine.kitware, mymachine.bwh.harvard.edu, ...
set(CTEST_DASHBOARD_ROOT  "$ENV{HOME}/Dashboards/")
set(CTEST_CMAKE_COMMAND   "$ENV{HOME}/Dashboards/Support/cmake-2.8.3-rc3-Linux-i386/bin/cmake")
# Open a shell and type in "cmake --help" to obtain the proper spelling of the generator
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")

#
# Dashboard options
#
set(WITH_KWSTYLE FALSE)
set(WITH_MEMCHECK FALSE)
set(WITH_COVERAGE FALSE)
set(WITH_DOCUMENTATION FALSE)
#set(DOCUMENTATION_ARCHIVES_OUTPUT_DIRECTORY ) # for example: $ENV{HOME}/Projects/Doxygen
set(CTEST_BUILD_CONFIGURATION "Release")
set(CTEST_TEST_TIMEOUT 100)
set(CTEST_BUILD_FLAGS "-j4") # Use multiple CPU cores to build

# experimental: 
#     - run_ctest() macro will be called *ONE* time
#     - binary directory will *NOT* be cleaned
# continuous: 
#     - run_ctest() macro will be called EVERY 5 minutes ... 
#     - binary directory will *NOT* be cleaned
#     - configure/build will be executed *ONLY* if the repository has been updated
# nightly: 
#     - run_ctest() macro will be called *ONE* time
#     - binary directory *WILL BE* cleaned
set(SCRIPT_MODE "nightly") # "experimental", "continuous", "nightly"

# You could invoke the script with the following syntax:
#  ctest -S karakoram_Slicer4_nightly.cmake -V

#
# Additional CMakeCache options
#
set(ADDITIONAL_CMAKECACHE_OPTION "
  Slicer_USE_QT:BOOL=ON
  Slicer_USE_PYTHONQT:BOOL=ON
  Slicer_USE_PYTHONQT_WITH_TCL:BOOL=ON
  Slicer_BUILD_CLI:BOOL=OFF
")

# Update the following variable to match the chosen build options. This variable is used to 
# generate both the build directory and the build name.
# See http://www.cdash.org/CDash/index.php?project=Slicer4 for examples
set(BUILD_OPTIONS_STRING "QT${MY_QT_VERSION}-PythonQt-With-Tcl-NoCLI") 

#
# Project specific properties
#
set(CTEST_SOURCE_DIRECTORY "${CTEST_DASHBOARD_ROOT}/Slicer4")
set(CTEST_BINARY_DIRECTORY "${CTEST_DASHBOARD_ROOT}/Slicer-build-${BUILD_OPTIONS_STRING}-${CTEST_BUILD_CONFIGURATION}-${SCRIPT_MODE}")

# List of test that should be explicitly disabled on this machine
set(TEST_TO_EXCLUDE_REGEX "")

# set any extra environment variables here
if(UNIX)
  set(ENV{DISPLAY} ":0")
endif()

find_program(CTEST_COVERAGE_COMMAND NAMES gcov)
find_program(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)
find_program(CTEST_SVN_COMMAND NAMES svn)

##########################################
# WARNING: DO NOT EDIT BEYOND THIS POINT #
##########################################

set(CTEST_NOTES_FILES "${CTEST_SCRIPT_DIRECTORY}/${CTEST_SCRIPT_NAME}")

#
# Project specific properties
#
set(CTEST_PROJECT_NAME "Slicer4")
set(CTEST_BUILD_NAME "${MY_OPERATING_SYSTEM}-${MY_COMPILER}-${BUILD_OPTIONS_STRING}-${CTEST_BUILD_CONFIGURATION}")

#
# Display build info
#
message("site name: ${CTEST_SITE}")
message("build name: ${CTEST_BUILD_NAME}")
message("script mode: ${SCRIPT_MODE}")
message("coverage: ${WITH_COVERAGE}, memcheck: ${WITH_MEMCHECK}")

#
# Convenient macro allowing to download a file
#
MACRO(downloadFile url dest)
  FILE(DOWNLOAD ${url} ${dest} STATUS status)
  LIST(GET status 0 error_code)
  LIST(GET status 1 error_msg)
  IF(error_code)
    MESSAGE(FATAL_ERROR "error: Failed to download ${url} - ${error_msg}")
  ENDIF()
ENDMACRO()

#
# Download and include dashboard driver script 
#
set(url http://svn.slicer.org/Slicer4/trunk/CMake/SlicerDashboardDriverScript.cmake)
set(dest ${CTEST_SCRIPT_DIRECTORY}/${CTEST_SCRIPT_NAME}.driver)
downloadFile(${url} ${dest})
INCLUDE(${dest})