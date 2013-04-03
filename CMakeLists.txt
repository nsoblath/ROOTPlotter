# CMakeLists for ROOTPlotter
# Author: N. Oblath

# Minimum cmake version 2.6 required by the scripts to get Git information
cmake_minimum_required (VERSION 2.6)

# Specify the local directory for CMake modules
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


# Define the project
project (ROOTPlotter)

# Include the build script
include (PackageBuilder)

# Set the version and associated variables
rootplotter_prepare_project (0 1 0)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    list (APPEND LIBS rt)
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-as-needed")
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# ROOT
find_package (ROOT 5.28)
if (ROOT_FOUND)
    list (APPEND LIBS ${ROOT_LIBRARIES})
else (ROOT_FOUND)
    message(FATAL_ERROR "ROOT was not found!")
endif (ROOT_FOUND)
include_directories (${ROOT_INCLUDES})

# add an option to build the validation tests
option (ROOTPlotter_ENABLE_TESTING "Build the validation tests and enable CMake testing" OFF)
if (ROOTPlotter_ENABLE_TESTING)
    enable_testing ()
endif (ROOTPlotter_ENABLE_TESTING)

# Subdirectories
include_directories (
    ${PROJECT_SOURCE_DIR}/Library
)

add_subdirectory (Library)
#add_subdirectory (Validation)

# Doxygen documentation can be built with "make doc" (it's not included with the "all" make target)
# By default it builds in the source tree.
#add_subdirectory (Documentation/ReferenceGuide)


# this is apparently not the right way to run the link_dylibs script
#execute_process (COMMAND ${PROJECT_SOURCE_DIR}/Scripts/link_dylibs.sh ${PROJECT_BINARY_DIR}/lib)

install (CODE "execute_process (COMMAND ${PROJECT_SOURCE_DIR}/Scripts/link_dylibs.sh ${LIB_INSTALL_DIR})")
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/Scripts/LoadLibraries.C.in ${PROJECT_BINARY_DIR}/LoadLibraries.C)
install (FILES ${PROJECT_BINARY_DIR}/LoadLibraries.C DESTINATION ${LIB_INSTALL_DIR})
