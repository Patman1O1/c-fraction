# ─────────────────────────────────────────────────────────────────────────────
# Target: test_package
# Type: Executable
# Dependencies: c_fraction::c_fraction
# ─────────────────────────────────────────────────────────────────────────────
# Target definition
add_executable(test_package)

# Target sources
target_sources(test_package
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c
)

# Target dependencies
target_link_libraries(test_package
    PRIVATE
        c_fraction::c_fraction
)
