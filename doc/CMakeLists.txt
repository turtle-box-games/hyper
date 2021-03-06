# Documentation with Doxygen.
find_package(Doxygen)
option(BUILD_DOCS "Create and install API documentation (requires Doxygen)" ${DOXYGEN_FOUND})
if(BUILD_DOCS)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is required to build the documentation.")
    endif()

    # Replace variables in Doxygen config.
    set(doxyfile_in "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in")
    set(doxyfile    "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${doxyfile_in}" "${doxyfile}" @ONLY)

    # Copy static theme files to build directory.
    file(GLOB theme_files "*.html" "*.css" "*.js")
    foreach(file ${theme_files})
        get_filename_component(file "${file}" NAME)
        configure_file("${file}" "${file}" COPYONLY)
    endforeach()

    add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} "${doxyfile}"
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation"
            VERBATIM)
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html" DESTINATION share/doc)
endif()
