cmake_minimum_required(VERSION 3.10)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(hello)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-fno-rtti)
# add_compile_options(-fsanitize=address)
add_link_options(-s LLD_REPORT_UNDEFINED)
# add_link_options(-v)

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



# enable_testing()



# add_compile_options(gtest_test PUBLIC -fno-rtti)
# target_compile_options(gtest_test PUBLIC -fno-rtti)

# add_subdirectory(third_party/dawn)
# add_subdirectory(third_party/dawn/src/utils)

# target_sources(gtest_test PUBLIC
#     "third_party/dawn/src/tests/unittests/validation/ValidationTest.cpp"
# )

file(GLOB all_SRCS
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/utils/SystemUtils.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/common/Log.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/common/Constants.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/common/Assert.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/common/Math.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/utils/SystemUtils.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/utils/TestUtils.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/utils/WGPUHelpers.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/utils/TextureUtils.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/utils/TestUtils.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/utils/ComboRenderBundleEncoderDescriptor.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/utils/ComboRenderPipelineDescriptor.cpp"
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/utils/TerribleCommandBuffer.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/utils/ScopedAutoreleasePool.cpp"
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/dawn_wire/client/*.cpp"
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/dawn_wire/server/*.cpp"
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/dawn_wire/*.cpp"
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/utils/WireHelper.cpp"
        
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/DawnTest.cpp"

        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/ToggleParser.cpp"
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/*.cpp"
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/wire/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/validation/ValidationTest.cpp"
        


        # # Map and Unmap issue
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/end2end/BufferTests.cpp"
        # # CreatePipelineAsync unimplemented
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/end2end/CreatePipelineAsyncTests.cpp"
        # # ok
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/end2end/CullingTests.cpp"
        # # failed and skipped
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/end2end/DepthStencilCopyTests.cpp"
        # # 19 Pass, 1 skip, texture3D fails
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/end2end/TextureViewTests.cpp"


        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/end2end/*.cpp"

        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/validation/*.cpp"

        # # GetSupportedLimits
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/validation/BufferValidationTests.cpp"
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/validation/CopyCommandsValidationTests.cpp"
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/validation/CommandBufferValidationTests.cpp"
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/validation/ComputeValidationTests.cpp"
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/validation/OverridableConstantsValidationTests.cpp"
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/validation/RenderPassDescriptorValidationTests.cpp"
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/validation/RenderPipelineValidationTests.cpp"
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/validation/SamplerValidationTests.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/validation/VertexBufferValidationTests.cpp"
        
        # "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/validation/*.cpp"
        )

list(REMOVE_ITEM all_SRCS
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/end2end/D3D12CachingTests.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/end2end/D3D12ResourceWrappingTests.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/end2end/ExternalTextureTests.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/end2end/IOSurfaceWrappingTests.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/end2end/WindowSurfaceTests.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/end2end/VideoViewsTests_gbm.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/end2end/VideoViewsTests_win.cpp"

        # absl
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/validation/Error.cpp"
        
        # External texture
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/validation/BindGroupValidationTests.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/validation/CommandEncoder.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/dawn/tests/unittests/validation/CommandBufferValidationTests.cpp"

        # native
        )

# add_executable(
#     gtest_test
#     "gtest_test.cpp"
#     )
add_executable(
    gtest_test
    
    ${all_SRCS}
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
    PRIVATE "SHELL:-s ASYNCIFY"
    PRIVATE "SHELL:-s ALLOW_MEMORY_GROWTH"
    #PRIVATE "SHELL:--closure 1"
    # PRIVATE "SHELL:-s VERBOSE=1"
    )


include_directories("${googletest_SOURCE_DIR}/include")
include_directories("${googlemock_SOURCE_DIR}/include")
# include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/")
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/include")
# include_directories("${CMAKE_CURRENT_BINARY_DIR}/gen/src")

target_include_directories(gtest_test
    PUBLIC
    
    "${googletest_SOURCE_DIR}/include"
    "${googlemock_SOURCE_DIR}/include"

    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/dawn/src/"

    # "${CMAKE_CURRENT_BINARY_DIR}/gen/src"

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
