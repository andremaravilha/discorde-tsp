cmake_minimum_required(VERSION 3.9)


# =============================================================================
# Project info
# =============================================================================

project("Discorde C API" C)


# =============================================================================
# C standard and settings
# =============================================================================

set(CMAKE_C_STANDARD 90)


# =============================================================================
# Set path to search for hearders and libraries
# =============================================================================

include_directories(${PROJECT_SOURCE_DIR}/../dependencies/)


# =============================================================================
# Targets
# =============================================================================

add_library(discorde discorde.h discorde.c)


# =============================================================================
# Install (-DCMAKE_INSTALL_PREFIX=/opt/discorde)
# =============================================================================

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/opt/discorde" CACHE PATH "default install path" FORCE)
endif()

install(TARGETS discorde DESTINATION lib)
install(FILES discorde.h DESTINATION include)

