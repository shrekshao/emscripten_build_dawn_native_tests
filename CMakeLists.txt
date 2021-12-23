cmake_minimum_required(VERSION 3.10)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(hello)
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

# if(NOT EMSCRIPTEN)
#     add_subdirectory("third_party/dawn" EXCLUDE_FROM_ALL)
# endif()

if(EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

add_executable(hello
    "main.cpp"
    )

add_executable(tests
    "tests.cpp"
    )

if(EMSCRIPTEN)
    set_target_properties(hello PROPERTIES
        SUFFIX ".html")
    target_link_options(hello
        PRIVATE "SHELL:-gsource-map"
        PRIVATE "SHELL:--source-map-base https://kai.graphics/webgpu-cross-platform-demo/out/web/"
        PRIVATE "SHELL:-s USE_WEBGPU=1"
        PRIVATE "SHELL:-s ASSERTIONS=1"
        PRIVATE "SHELL:-s SAFE_HEAP=1"
        #PRIVATE "SHELL:--closure 1"
        #PRIVATE "SHELL:-s VERBOSE=1"
        )

    set_target_properties(tests PROPERTIES
        SUFFIX ".html")
    target_link_options(tests
        PRIVATE "SHELL:-gsource-map"
        PRIVATE "SHELL:--source-map-base https://kai.graphics/webgpu-cross-platform-demo/out/web/"
        PRIVATE "SHELL:-s USE_WEBGPU=1"
        PRIVATE "SHELL:-s ASSERTIONS=1"
        PRIVATE "SHELL:-s SAFE_HEAP=1"
        #PRIVATE "SHELL:--closure 1"
        #PRIVATE "SHELL:-s VERBOSE=1"
        )
else()
    target_link_libraries(hello
        dawn_headers
        dawncpp
        dawn_native
        dawn_proc
        )
endif()



enable_testing()

add_executable(
  gtest_test
  "gtest_test.cpp"
)

set_target_properties(gtest_test PROPERTIES
        SUFFIX ".html")
target_link_options(gtest_test
    # PRIVATE "SHELL:-gsource-map"
    # PRIVATE "SHELL:--source-map-base https://kai.graphics/webgpu-cross-platform-demo/out/web/"
    PRIVATE "SHELL:-s USE_WEBGPU=1"
    PRIVATE "SHELL:-s ASSERTIONS=1"
    PRIVATE "SHELL:-s SAFE_HEAP=1"
    #PRIVATE "SHELL:--closure 1"
    #PRIVATE "SHELL:-s VERBOSE=1"
    )


include_directories("${googletest_SOURCE_DIR}/include")
include_directories("${googlemock_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/include")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/gen/src")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/gen/src/include")

target_include_directories(gtest_test
    PUBLIC
    
    "${googletest_SOURCE_DIR}/include"
    "${googlemock_SOURCE_DIR}/include"

    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/"
    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/include"

    "${CMAKE_CURRENT_BINARY_DIR}/gen/src"
    "${CMAKE_CURRENT_BINARY_DIR}/gen/src/include"

    # "_deps/googletest-src/googletest/include/"
)

# target_link_libraries(gtest_test
#   gtest
# )
target_link_libraries(gtest_test
  gtest_main
  gmock_main
)

# include(GoogleTest)
# gtest_discover_tests(gtest_test)