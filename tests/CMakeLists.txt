# ── Settings ─────────────────────────────────────────────────────────────────
enable_language(CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Google Test ──────────────────────────────────────────────────────────────
include(GoogleTest)
enable_testing()

# ───────────────────────────────────────────────────────────────────────────── 
# Target: c_fraction_test
# Alias: c_fraction::c_fraction_test
# Type: Executable
# Dependencies: GTest::gtest_main,
#               GTest::gmock_main,
#               fraction::c_fraction_headers
# ─────────────────────────────────────────────────────────────────────────────
# Target definition
add_executable(c_fraction_test)

# Target alias
add_executable(c_fraction::c_fraction_test
    ALIAS c_fraction_test
)

# Target sources
target_sources(c_fraction_test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/fraction.c
        ${CMAKE_CURRENT_SOURCE_DIR}/fraction_test.cpp
)

# Target dependencies
target_link_libraries(c_fraction_test
    PRIVATE
        c_fraction::c_fraction_headers
        GTest::gtest_main
        GTest::gmock_main
)

# Test discovery
gtest_discover_tests(c_fraction_test)
