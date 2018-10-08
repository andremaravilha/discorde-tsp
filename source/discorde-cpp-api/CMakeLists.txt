cmake_minimum_required(VERSION 3.9)


# =============================================================================
# Project info
# =============================================================================

project("Discorde C++ API")


# =============================================================================
# C++ standard and settings
# =============================================================================

set(CMAKE_CXX_STANDARD 98)


# =============================================================================
# Set path to search for hearders and libraries
# =============================================================================

include_directories(
        ${PROJECT_SOURCE_DIR}/../dependencies/
        ${PROJECT_SOURCE_DIR}/../discorde-c-api/)


# =============================================================================
# Targets
# =============================================================================

add_library(discorde_cpp discorde_cpp.cpp discorde_cpp.h)


# =============================================================================
# Install (-DCMAKE_INSTALL_PREFIX=/opt/discorde)
# =============================================================================

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/opt/discorde" CACHE PATH "default install path" FORCE)
endif()

install(TARGETS discorde_cpp DESTINATION lib)
install(FILES discorde_cpp.h DESTINATION include)

