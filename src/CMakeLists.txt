# ─────────────────────────────────────────────────────────────────────────────
# Target: c_fraction
# Alias: fraction::c_fraction
# Type: Static Library
# Dependencies: fraction::c_fraction_headers
# ─────────────────────────────────────────────────────────────────────────────
# Target definition
add_library(c_fraction STATIC)

# Target alias
add_library(fraction::c_fraction ALIAS c_fraction)

# Target sources
target_sources(c_fraction
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/c_fraction.c
)

# Target dependencies
target_link_libraries(c_fraction
    PUBLIC
        fraction::c_fraction_headers
)

# Export configuration
include(GenerateExportHeader)

if(BUILD_SHARED_LIBS)
    # Export file name for a shared build
    set(EXPORT_HEADER_FILE export_shared.h)

    # Primary target properties
    set_target_properties(c_fraction PROPERTIES
            OUTPUT_NAME c_fraction
            VERSION ${PROJECT_VERSION}
            SOVERSION ${PROJECT_VERSION_MAJOR}
            C_VISIBILITY_PRESET hidden
            VISIBILITY_INLINES_HIDDEN ON
    )

    # Define compile definitions
    target_compile_definitions(c_fraction
            PUBLIC
                $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:C_FRACTION_STATIC_DEFINE>
    )
else()
    # Export file name for a static build
    set(EXPORT_HEADER_FILE export_static.h)

    # Primary target properties
    set_target_properties(c_fraction PROPERTIES
            OUTPUT_NAME c_fraction
            VERSION ${PROJECT_VERSION}
            SOVERSION ${PROJECT_VERSION_MAJOR}
            POSITION_INDEPENDENT_CODE ON
    )

    # A static build must see the STATIC_DEFINE guard from the generated export header
    target_compile_definitions(c_fraction
            PUBLIC
                C_FRACTION_STATIC_DEFINE
    )
endif()

# Generate the export header into the build tree
generate_export_header(c_fraction
        EXPORT_FILE_NAME include/c_fraction/${EXPORT_HEADER_FILE}
)

# Make the generated export header visible to this target and its consumers
target_include_directories(c_fraction
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(NOT CMAKE_SKIP_INSTALL_RULES)
    include(GNUInstallDirs)

    # Install the library target (Conan/CMakeDeps provides the config + targets files)
    install(TARGETS c_fraction c_fraction_headers
            RUNTIME COMPONENT c_fraction
            LIBRARY COMPONENT c_fraction
            NAMELINK_COMPONENT c_fraction
            ARCHIVE COMPONENT c_fraction
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    # Install the generated export header
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/c_fraction/${EXPORT_HEADER_FILE}
            COMPONENT c_fraction
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/c_fraction)
endif()
