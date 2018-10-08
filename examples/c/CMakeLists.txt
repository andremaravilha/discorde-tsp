cmake_minimum_required(VERSION 3.9)


# =============================================================================
# Project info
# =============================================================================

project("Discorde C API - Example" C)


# =============================================================================
# C standard and settings
# =============================================================================

set(CMAKE_C_STANDARD 90)


# =============================================================================
# External dependencies
# =============================================================================

# CPLEX (path and libraries)
set(CPLEX_PATH "/opt/ibm/ILOG/CPLEX_Studio1271/cplex/lib/x86-64_linux/static_pic")
set(CPLEX_LIBRARY ilocplex cplex)

# Concert API for CPLEX (path and libraries)
set(CONCERT_PATH "/opt/ibm/ILOG/CPLEX_Studio1271/concert/lib/x86-64_linux/static_pic")
set(CONCERT_LIBRARY concert)

# Concorde solver (path and library)
set(CONCORDE_PATH "/opt/concorde")
set(CONCORDE_LIBRARY concorde)

# =============================================================================
# Set path to search for hearders and libraries
# =============================================================================

include_directories(
        ${PROJECT_SOURCE_DIR}/../discorde/include)

link_directories(
        ${PROJECT_SOURCE_DIR}/../discorde/lib
        ${CPLEX_PATH}
        ${CONCERT_PATH}
        ${CONCORDE_PATH})

# =============================================================================
# Targets
# =============================================================================

add_executable(c_example src/main.c)
target_link_libraries(c_example discorde ${CONCORDE_LIBRARY} ${CONCERT_LIBRARY} ${CPLEX_LIBRARY} m pthread)
