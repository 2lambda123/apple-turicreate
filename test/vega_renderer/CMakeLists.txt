project(Turi)

if(APPLE AND NOT TC_BUILD_IOS)

    # sets XCTest_LIBRARIES
    include(FindXCTest)
    include_directories(${XCTest_INCLUDE_DIRS})

    find_library( WEBKIT WebKit )
    message( STATUS "WebKit found at ${WEBKIT}")

    add_definitions(-DPROJECT_DIR=${CMAKE_CURRENT_SOURCE_DIR})

    make_library(vega_renderer_test_utils OBJECT
        SOURCES
            base_fixture.mm
            vega_js_test_fixture.mm
            vega_webkit_renderer.mm
        REQUIRES
            vega_renderer
            ${WEBKIT}
            ${XCTest_LIBRARIES}
    )
    target_compile_options(vega_renderer_test_utils PUBLIC "-fobjc-arc")
    add_dependencies(vega_renderer_test_utils vega_renderer)

if(NOT TC_DISABLE_OBJECT_BUILDS)
    set(source_object_deps
        $<TARGET_OBJECTS:vega_renderer>
        $<TARGET_OBJECTS:vega_renderer_test_utils>
    )
else()
    set(source_deps
        vega_renderer
        vega_renderer_test_utils
    )
endif()

    set(target_deps
        vega_renderer
        ${WEBKIT}
        ${XCTest_LIBRARIES}
        ${FOUNDATION}
        ${APPKIT}
        ${CORE_GRAPHICS}
        ${JAVASCRIPT_CORE}
    )

    make_boost_test(vega_js_unit_tests.cxx ${source_object_deps} REQUIRES ${target_deps} ${source_deps})
    make_boost_test(vega_example_tests.cxx ${source_object_deps} REQUIRES ${target_deps} ${source_deps})
    make_boost_test(vega_lite_example_tests.cxx ${source_object_deps} REQUIRES ${target_deps} ${source_deps})
    make_boost_test(turicreate_example_tests.cxx ${source_object_deps} REQUIRES ${target_deps} ${source_deps})
    make_boost_test(log_proxy_tests.cxx log_proxy_tests_impl.mm ${source_object_deps} REQUIRES ${target_deps} ${source_deps})
    target_compile_options(log_proxy_tests.cxxtest PUBLIC "-fobjc-arc")

    # loop through files in turicreate
    file(GLOB_RECURSE VEGA_JSON_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.json)
    file(GLOB_RECURSE VEGA_JS_TESTS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.js)
    set(XXD_INPUT ${VEGA_JSON_FILES} ${VEGA_JS_TESTS})

    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vega_js_tests)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/examples/turicreate)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/examples/vega)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/examples/vega_lite)

    include_directories(${CMAKE_CURRENT_BINARY_DIR})

    foreach(SOURCE_FILE ${XXD_INPUT})
        string(
            REGEX REPLACE
            "(.json|.js)$"
            ".h"
            GENERATED_FILE
            ${CMAKE_CURRENT_BINARY_DIR}/${SOURCE_FILE}
        )

        add_custom_command(
            OUTPUT ${GENERATED_FILE}
            COMMAND xxd -i ${SOURCE_FILE} > ${GENERATED_FILE}
            MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FILE}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating ${GENERATED_FILE}"
            VERBATIM
        )

        string(
            MAKE_C_IDENTIFIER
            ${SOURCE_FILE}
            TARGET_NAME
        )

        add_custom_target(
            Generate_${TARGET_NAME}
            DEPENDS
            ${GENERATED_FILE}
        )

        add_dependencies(vega_renderer_test_utils Generate_${TARGET_NAME})
    endforeach(SOURCE_FILE)

endif()
