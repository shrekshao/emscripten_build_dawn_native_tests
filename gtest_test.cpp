
// #ifdef __EMSCRIPTEN__
#include <webgpu/webgpu_cpp.h>

#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/html5_webgpu.h>
// #endif  // __EMSCRIPTEN__

#undef NDEBUG
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <memory>

// #define VALIDATION_TEST

#ifndef VALIDATION_TEST
#define END2END_TEST
#else
#undef END2END_TEST
#endif

// #include <gtest/gtest.h>
// // #include "out/web/_deps/googletest-src/googletest/include/gtest/gtest.h"  // temp

// // Demonstrate some basic assertions.
// TEST(HelloTest, BasicAssertions) {
//   // Expect two strings not to be equal.
//   EXPECT_STRNE("hello", "world");
//   // Expect equality.
//   EXPECT_EQ(7 * 6, 42);
//   // EXPECT_EQ(41, 42);
// }


#ifdef END2END_TEST
// // -------------------------------
// // end2end BasicTests
// #include "tests/DawnTest.h"

// #include "utils/WGPUHelpers.h"

// class BasicTests : public DawnTest {};

// // // Test adapter filter by vendor id.
// // TEST_P(BasicTests, VendorIdFilter) {
// //     DAWN_TEST_UNSUPPORTED_IF(!HasVendorIdFilter());

// //     ASSERT_EQ(GetAdapterProperties().vendorID, GetVendorIdFilter());
// // }

// // // Test adapter filter by backend type.
// // TEST_P(BasicTests, BackendType) {
// //     DAWN_TEST_UNSUPPORTED_IF(!HasBackendTypeFilter());

// //     ASSERT_EQ(GetAdapterProperties().backendType, GetBackendTypeFilter());
// // }

// // Test Queue::WriteBuffer changes the content of the buffer, but really this is the most
// // basic test possible, and tests the test harness
// TEST_P(BasicTests, QueueWriteBuffer) {
//     wgpu::BufferDescriptor descriptor;
//     descriptor.size = 4;
//     descriptor.usage = wgpu::BufferUsage::CopySrc | wgpu::BufferUsage::CopyDst;
//     // descriptor.usage = wgpu::BufferUsage::MapRead | wgpu::BufferUsage::CopyDst;
//     wgpu::Buffer buffer = device.CreateBuffer(&descriptor);

//     uint32_t value = 0x01020304;
//     queue.WriteBuffer(buffer, 0, &value, sizeof(value));

//     EXPECT_BUFFER_U32_EQ(value, buffer, 0);
// }

// // // Test a validation error for Queue::WriteBuffer but really this is the most basic test possible
// // // for ASSERT_DEVICE_ERROR
// // TEST_P(BasicTests, QueueWriteBufferError) {
// //     wgpu::BufferDescriptor descriptor;
// //     descriptor.size = 4;
// //     descriptor.usage = wgpu::BufferUsage::CopySrc | wgpu::BufferUsage::CopyDst;
// //     wgpu::Buffer buffer = device.CreateBuffer(&descriptor);

// //     uint8_t value = 187;
// //     ASSERT_DEVICE_ERROR(queue.WriteBuffer(buffer, 1000, &value, sizeof(value)));
// // }

// DAWN_INSTANTIATE_TEST(BasicTests,
//                       // D3D12Backend(),
//                       // MetalBackend(),
//                       // OpenGLBackend(),
//                       // OpenGLESBackend(),
//                       // WebGPUBackend(),
//                       VulkanBackend());




// ------------------------------------
// end2end tests: BufferTests


// #include "tests/DawnTest.h"

// #include <array>
// #include <cstring>

// class BufferMappingTests : public DawnTest {
//   protected:
//     void MapAsyncAndWait(const wgpu::Buffer& buffer,
//                          wgpu::MapMode mode,
//                          size_t offset,
//                          size_t size) {
//         bool done = false;
//         buffer.MapAsync(
//             mode, offset, size,
//             [](WGPUBufferMapAsyncStatus status, void* userdata) {
//                 ASSERT_EQ(WGPUBufferMapAsyncStatus_Success, status);
//                 *static_cast<bool*>(userdata) = true;
//             },
//             &done);

//         while (!done) {
//             WaitABit();
//         }
//     }

//     wgpu::Buffer CreateMapReadBuffer(uint64_t size) {
//         wgpu::BufferDescriptor descriptor;
//         descriptor.size = size;
//         descriptor.usage = wgpu::BufferUsage::MapRead | wgpu::BufferUsage::CopyDst;
//         return device.CreateBuffer(&descriptor);
//     }

//     wgpu::Buffer CreateMapWriteBuffer(uint64_t size) {
//         wgpu::BufferDescriptor descriptor;
//         descriptor.size = size;
//         descriptor.usage = wgpu::BufferUsage::MapWrite | wgpu::BufferUsage::CopySrc;
//         return device.CreateBuffer(&descriptor);
//     }
// };

// void CheckMapping(const void* actual, const void* expected, size_t size) {
//     EXPECT_NE(actual, nullptr);
//     if (actual != nullptr) {
//         EXPECT_EQ(0, memcmp(actual, expected, size));
//     }
// }

// // // Test that the simplest map read works
// // TEST_P(BufferMappingTests, MapRead_Basic) {
// //     wgpu::Buffer buffer = CreateMapReadBuffer(4);

// //     uint32_t myData = 0x01020304;
// //     constexpr size_t kSize = sizeof(myData);
// //     queue.WriteBuffer(buffer, 0, &myData, kSize);

// //     MapAsyncAndWait(buffer, wgpu::MapMode::Read, 0, 4);
// //     CheckMapping(buffer.GetConstMappedRange(), &myData, kSize);
// //     // CheckMapping(buffer.GetConstMappedRange(0, kSize), &myData, kSize);
// //     buffer.Unmap();
// // }

// // // Test map-reading a zero-sized buffer.
// // TEST_P(BufferMappingTests, MapRead_ZeroSized) {
// //     wgpu::Buffer buffer = CreateMapReadBuffer(0);

// //     MapAsyncAndWait(buffer, wgpu::MapMode::Read, 0, wgpu::kWholeMapSize);
// //     ASSERT_NE(buffer.GetConstMappedRange(), nullptr);
// //     buffer.Unmap();
// // }

// // // Test map-reading with a non-zero offset
// // TEST_P(BufferMappingTests, MapRead_NonZeroOffset) {
// //     wgpu::Buffer buffer = CreateMapReadBuffer(12);

// //     uint32_t myData[3] = {0x01020304, 0x05060708, 0x090A0B0C};
// //     queue.WriteBuffer(buffer, 0, &myData, sizeof(myData));

// //     MapAsyncAndWait(buffer, wgpu::MapMode::Read, 8, 4);
// //     ASSERT_EQ(myData[2], *static_cast<const uint32_t*>(buffer.GetConstMappedRange(8)));
// //     buffer.Unmap();
// // }

// // Test that the simplest map write works.
// TEST_P(BufferMappingTests, MapWrite_Basic) {
//     wgpu::Buffer buffer = CreateMapWriteBuffer(4);

//     uint32_t myData = 2934875;
//     MapAsyncAndWait(buffer, wgpu::MapMode::Write, 0, 4);
//     ASSERT_NE(nullptr, buffer.GetMappedRange());
//     ASSERT_NE(nullptr, buffer.GetConstMappedRange());
//     memcpy(buffer.GetMappedRange(), &myData, sizeof(myData));
//     buffer.Unmap();

//     EXPECT_BUFFER_U32_EQ(myData, buffer, 0);
// }

// // // Test that the simplest map write works with a range.
// // TEST_P(BufferMappingTests, MapWrite_BasicRange) {
// //     wgpu::Buffer buffer = CreateMapWriteBuffer(4);

// //     uint32_t myData = 2934875;
// //     MapAsyncAndWait(buffer, wgpu::MapMode::Write, 0, 4);
// //     ASSERT_NE(nullptr, buffer.GetMappedRange(0, 4));
// //     ASSERT_NE(nullptr, buffer.GetConstMappedRange(0, 4));
// //     memcpy(buffer.GetMappedRange(), &myData, sizeof(myData));
// //     buffer.Unmap();

// //     EXPECT_BUFFER_U32_EQ(myData, buffer, 0);
// // }

// DAWN_INSTANTIATE_TEST(BufferMappingTests,
//                       // D3D12Backend(),
//                       // MetalBackend(),
//                       // OpenGLBackend(),
//                       // OpenGLESBackend(),
//                       // WebGPUBackend(),
//                       VulkanBackend());












// //--------------------------------
// // end2end tests: CullingTests.cpp

// #include "tests/DawnTest.h"

// #include "utils/ComboRenderPipelineDescriptor.h"
// #include "utils/WGPUHelpers.h"

// class CullingTest : public DawnTest {
//   protected:
//     wgpu::RenderPipeline CreatePipelineForTest(wgpu::FrontFace frontFace, wgpu::CullMode cullMode) {
//         utils::ComboRenderPipelineDescriptor pipelineDescriptor;

//         // Draw two triangles with different winding orders:
//         // 1. The top-left one is counterclockwise (CCW)
//         // 2. The bottom-right one is clockwise (CW)
//         pipelineDescriptor.vertex.module = utils::CreateShaderModule(device, R"(
//             [[stage(vertex)]]
//             fn main([[builtin(vertex_index)]] VertexIndex : u32) -> [[builtin(position)]] vec4<f32> {
//                 var pos = array<vec2<f32>, 6>(
//                     vec2<f32>(-1.0,  1.0),
//                     vec2<f32>(-1.0,  0.0),
//                     vec2<f32>( 0.0,  1.0),
//                     vec2<f32>( 0.0, -1.0),
//                     vec2<f32>( 1.0,  0.0),
//                     vec2<f32>( 1.0, -1.0));
//                 return vec4<f32>(pos[VertexIndex], 0.0, 1.0);
//             })");

//         // FragCoord of pixel(x, y) in framebuffer coordinate is (x + 0.5, y + 0.5). And we use
//         // RGBA8 format for the back buffer. So (FragCoord.xy - vec2(0.5)) / 255 in shader code
//         // will make the pixel's R and G channels exactly equal to the pixel's x and y coordinates.
//         pipelineDescriptor.cFragment.module = utils::CreateShaderModule(device, R"(
//             [[stage(fragment)]]
//             fn main([[builtin(position)]] FragCoord : vec4<f32>) -> [[location(0)]] vec4<f32> {
//                 return vec4<f32>(
//                     (FragCoord.xy - vec2<f32>(0.5, 0.5)) / vec2<f32>(255.0, 255.0),
//                     0.0, 1.0);
//             })");

//         // Set culling mode and front face according to the parameters
//         pipelineDescriptor.primitive.frontFace = frontFace;
//         pipelineDescriptor.primitive.cullMode = cullMode;

//         return device.CreateRenderPipeline(&pipelineDescriptor);
//     }

//     wgpu::Texture Create2DTextureForTest(wgpu::TextureFormat format) {
//         wgpu::TextureDescriptor textureDescriptor;
//         textureDescriptor.dimension = wgpu::TextureDimension::e2D;
//         textureDescriptor.format = format;
//         textureDescriptor.usage =
//             wgpu::TextureUsage::RenderAttachment | wgpu::TextureUsage::CopySrc;
//         textureDescriptor.mipLevelCount = 1;
//         textureDescriptor.sampleCount = 1;
//         textureDescriptor.size = {kSize, kSize, 1};
//         return device.CreateTexture(&textureDescriptor);
//     }

//     void DoTest(wgpu::FrontFace frontFace,
//                 wgpu::CullMode cullMode,
//                 bool isCCWTriangleCulled,
//                 bool isCWTriangleCulled) {
//         wgpu::Texture colorTexture = Create2DTextureForTest(wgpu::TextureFormat::RGBA8Unorm);

//         utils::ComboRenderPassDescriptor renderPassDescriptor({colorTexture.CreateView()});
//         renderPassDescriptor.cColorAttachments[0].clearColor = {0.0, 0.0, 1.0, 1.0};
//         renderPassDescriptor.cColorAttachments[0].loadOp = wgpu::LoadOp::Clear;

//         wgpu::CommandEncoder commandEncoder = device.CreateCommandEncoder();
//         wgpu::RenderPassEncoder renderPass = commandEncoder.BeginRenderPass(&renderPassDescriptor);
//         renderPass.SetPipeline(CreatePipelineForTest(frontFace, cullMode));
//         renderPass.Draw(6);
//         renderPass.EndPass();
//         wgpu::CommandBuffer commandBuffer = commandEncoder.Finish();
//         queue.Submit(1, &commandBuffer);

//         const RGBA8 kBackgroundColor = RGBA8::kBlue;
//         const RGBA8 kTopLeftColor = RGBA8::kBlack;
//         constexpr RGBA8 kBottomRightColor = RGBA8(3, 3, 0, 255);

//         RGBA8 kCCWTriangleTopLeftColor = isCCWTriangleCulled ? kBackgroundColor : kTopLeftColor;
//         EXPECT_PIXEL_RGBA8_EQ(kCCWTriangleTopLeftColor, colorTexture, 0, 0);

//         RGBA8 kCWTriangleBottomRightColor =
//             isCWTriangleCulled ? kBackgroundColor : kBottomRightColor;
//         EXPECT_PIXEL_RGBA8_EQ(kCWTriangleBottomRightColor, colorTexture, kSize - 1, kSize - 1);
//     }

//     static constexpr uint32_t kSize = 4;
// };

// TEST_P(CullingTest, CullNoneWhenCCWIsFrontFace) {
//     DoTest(wgpu::FrontFace::CCW, wgpu::CullMode::None, false, false);
// }

// // TEST_P(CullingTest, CullFrontFaceWhenCCWIsFrontFace) {
// //     DoTest(wgpu::FrontFace::CCW, wgpu::CullMode::Front, true, false);
// // }

// // TEST_P(CullingTest, CullBackFaceWhenCCWIsFrontFace) {
// //     DoTest(wgpu::FrontFace::CCW, wgpu::CullMode::Back, false, true);
// // }

// // TEST_P(CullingTest, CullNoneWhenCWIsFrontFace) {
// //     DoTest(wgpu::FrontFace::CW, wgpu::CullMode::None, false, false);
// // }

// // TEST_P(CullingTest, CullFrontFaceWhenCWIsFrontFace) {
// //     DoTest(wgpu::FrontFace::CW, wgpu::CullMode::Front, false, true);
// // }

// // TEST_P(CullingTest, CullBackFaceWhenCWIsFrontFace) {
// //     DoTest(wgpu::FrontFace::CW, wgpu::CullMode::Back, true, false);
// // }

// DAWN_INSTANTIATE_TEST(CullingTest,
//                     //   D3D12Backend(),
//                     //   MetalBackend(),
//                     //   OpenGLBackend(),
//                     //   OpenGLESBackend(),
//                       VulkanBackend());



#endif










#ifdef VALIDATION_TEST



// // ---------------------
// // unittests EnumClassBitmasksTests.cpp

// // Copyright 2017 The Dawn Authors
// //
// // Licensed under the Apache License, Version 2.0 (the "License");
// // you may not use this file except in compliance with the License.
// // You may obtain a copy of the License at
// //
// //     http://www.apache.org/licenses/LICENSE-2.0
// //
// // Unless required by applicable law or agreed to in writing, software
// // distributed under the License is distributed on an "AS IS" BASIS,
// // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// // See the License for the specific language governing permissions and
// // limitations under the License.

// #include "gtest/gtest.h"

// #include "dawn/EnumClassBitmasks.h"

// namespace dawn {

//     enum class Color : uint32_t {
//         R = 1,
//         G = 2,
//         B = 4,
//         A = 8,
//     };

//     template <>
//     struct IsDawnBitmask<Color> {
//         static constexpr bool enable = true;
//     };

//     TEST(BitmaskTests, BasicOperations) {
//         Color test1 = Color::R | Color::G;
//         ASSERT_EQ(1u | 2u, static_cast<uint32_t>(test1));

//         Color test2 = test1 ^ (Color::R | Color::A);
//         ASSERT_EQ(2u | 8u, static_cast<uint32_t>(test2));

//         Color test3 = test2 & Color::A;
//         ASSERT_EQ(8u, static_cast<uint32_t>(test3));

//         Color test4 = ~test3;
//         ASSERT_EQ(~uint32_t(8), static_cast<uint32_t>(test4));
//     }

//     TEST(BitmaskTests, AssignOperations) {
//         Color test1 = Color::R;
//         test1 |= Color::G;
//         ASSERT_EQ(1u | 2u, static_cast<uint32_t>(test1));

//         Color test2 = test1;
//         test2 ^= (Color::R | Color::A);
//         ASSERT_EQ(2u | 8u, static_cast<uint32_t>(test2));

//         Color test3 = test2;
//         test3 &= Color::A;
//         ASSERT_EQ(8u, static_cast<uint32_t>(test3));
//     }

//     TEST(BitmaskTests, BoolConversion) {
//         bool test1 = Color::R | Color::G;
//         ASSERT_TRUE(test1);

//         bool test2 = Color::R & Color::G;
//         ASSERT_FALSE(test2);

//         bool test3 = Color::R ^ Color::G;
//         ASSERT_TRUE(test3);

//         if (Color::R & ~Color::R) {
//             ASSERT_TRUE(false);
//         }
//     }

//     TEST(BitmaskTests, ThreeOrs) {
//         Color c = Color::R | Color::G | Color::B;
//         ASSERT_EQ(7u, static_cast<uint32_t>(c));
//     }

//     TEST(BitmaskTests, ZeroOrOneBits) {
//         Color zero = static_cast<Color>(0);
//         ASSERT_TRUE(HasZeroOrOneBits(zero));
//         ASSERT_TRUE(HasZeroOrOneBits(Color::R));
//         ASSERT_TRUE(HasZeroOrOneBits(Color::G));
//         ASSERT_TRUE(HasZeroOrOneBits(Color::B));
//         ASSERT_TRUE(HasZeroOrOneBits(Color::A));
//         ASSERT_FALSE(HasZeroOrOneBits(static_cast<Color>(Color::R | Color::G)));
//         ASSERT_FALSE(HasZeroOrOneBits(static_cast<Color>(Color::G | Color::B)));
//         ASSERT_FALSE(HasZeroOrOneBits(static_cast<Color>(Color::B | Color::A)));
//     }

// }  // namespace dawn






// // -------------------------------------------------------------
// // unittests WriteBufferTests.cpp

// // Copyright 2021 The Dawn Authors
// //
// // Licensed under the Apache License, Version 2.0 (the "License");
// // you may not use this file except in compliance with the License.
// // You may obtain a copy of the License at
// //
// //     http://www.apache.org/licenses/LICENSE-2.0
// //
// // Unless required by applicable law or agreed to in writing, software
// // distributed under the License is distributed on an "AS IS" BASIS,
// // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// // See the License for the specific language governing permissions and
// // limitations under the License.

// #include "tests/unittests/validation/ValidationTest.h"

// // #include "utils/ComboRenderPipelineDescriptor.h"
// #include "utils/WGPUHelpers.h"

// namespace {

//     class WriteBufferTest : public ValidationTest {
//       public:
//         wgpu::Buffer CreateWritableBuffer(uint64_t size) {
//             wgpu::BufferDescriptor desc;
//             desc.usage = wgpu::BufferUsage::CopyDst;
//             desc.size = size;
//             return device.CreateBuffer(&desc);
//         }

//         wgpu::CommandBuffer EncodeWriteBuffer(wgpu::Buffer buffer,
//                                               uint64_t bufferOffset,
//                                               uint64_t size) {
//             std::vector<uint8_t> data(size);
//             wgpu::CommandEncoder encoder = device.CreateCommandEncoder();
//             encoder.WriteBuffer(buffer, bufferOffset, data.data(), size);
//             return encoder.Finish();
//         }
//     };

//     // Tests that the buffer offset is validated to be a multiple of 4 bytes.
//     TEST_F(WriteBufferTest, OffsetAlignment) {
//         wgpu::Buffer buffer = CreateWritableBuffer(64);
//         EncodeWriteBuffer(buffer, 0, 4);
//         EncodeWriteBuffer(buffer, 4, 4);
//         EncodeWriteBuffer(buffer, 60, 4);
//         ASSERT_DEVICE_ERROR(EncodeWriteBuffer(buffer, 1, 4));
//         ASSERT_DEVICE_ERROR(EncodeWriteBuffer(buffer, 2, 4));
//         ASSERT_DEVICE_ERROR(EncodeWriteBuffer(buffer, 3, 4));
//         ASSERT_DEVICE_ERROR(EncodeWriteBuffer(buffer, 5, 4));
//         ASSERT_DEVICE_ERROR(EncodeWriteBuffer(buffer, 11, 4));
//     }

//     // Tests that the buffer size is validated to be a multiple of 4 bytes.
//     TEST_F(WriteBufferTest, SizeAlignment) {
//         wgpu::Buffer buffer = CreateWritableBuffer(64);
//         EncodeWriteBuffer(buffer, 0, 64);
//         EncodeWriteBuffer(buffer, 4, 60);
//         EncodeWriteBuffer(buffer, 40, 24);
//         ASSERT_DEVICE_ERROR(EncodeWriteBuffer(buffer, 0, 63));
//         ASSERT_DEVICE_ERROR(EncodeWriteBuffer(buffer, 4, 1));
//         ASSERT_DEVICE_ERROR(EncodeWriteBuffer(buffer, 4, 2));
//         ASSERT_DEVICE_ERROR(EncodeWriteBuffer(buffer, 40, 23));
//     }

//     // Tests that the buffer size and offset are validated to fit within the bounds of the buffer.
//     TEST_F(WriteBufferTest, BufferBounds) {
//         wgpu::Buffer buffer = CreateWritableBuffer(64);
//         EncodeWriteBuffer(buffer, 0, 64);
//         EncodeWriteBuffer(buffer, 4, 60);
//         EncodeWriteBuffer(buffer, 40, 24);
//         ASSERT_DEVICE_ERROR(EncodeWriteBuffer(buffer, 0, 68));
//         ASSERT_DEVICE_ERROR(EncodeWriteBuffer(buffer, 4, 64));
//         ASSERT_DEVICE_ERROR(EncodeWriteBuffer(buffer, 60, 8));
//         ASSERT_DEVICE_ERROR(EncodeWriteBuffer(buffer, 64, 4));
//     }

//     // Tests that the destination buffer's usage is validated to contain CopyDst.
//     TEST_F(WriteBufferTest, RequireCopyDstUsage) {
//         wgpu::BufferDescriptor desc;
//         desc.usage = wgpu::BufferUsage::CopySrc;
//         desc.size = 64;
//         wgpu::Buffer buffer = device.CreateBuffer(&desc);

//         ASSERT_DEVICE_ERROR(EncodeWriteBuffer(buffer, 0, 64));
//     }

//     // Tests that the destination buffer's state is validated at submission.
//     TEST_F(WriteBufferTest, ValidBufferState) {
//         wgpu::BufferDescriptor desc;
//         desc.usage = wgpu::BufferUsage::CopyDst;
//         desc.size = 64;
//         desc.mappedAtCreation = true;
//         wgpu::Buffer buffer = device.CreateBuffer(&desc);

//         wgpu::CommandBuffer commands = EncodeWriteBuffer(buffer, 0, 64);
//         ASSERT_DEVICE_ERROR(device.GetQueue().Submit(1, &commands));

//         commands = EncodeWriteBuffer(buffer, 0, 64);
//         buffer.Unmap();
//         device.GetQueue().Submit(1, &commands);
//     }

// }  // namespace





#include "common/Constants.h"
#include "tests/unittests/validation/ValidationTest.h"
#include "utils/WGPUHelpers.h"

// TODO(cwallez@chromium.org): Add a regression test for Disptach validation trying to acces the
// input state.

class ComputeValidationTest : public ValidationTest {
  protected:
    void SetUp() override {
        ValidationTest::SetUp();

        wgpu::ShaderModule computeModule = utils::CreateShaderModule(device, R"(
            [[stage(compute), workgroup_size(1)]] fn main() {
            })");

        // Set up compute pipeline
        wgpu::PipelineLayout pl = utils::MakeBasicPipelineLayout(device, nullptr);

        wgpu::ComputePipelineDescriptor csDesc;
        csDesc.layout = pl;
        csDesc.compute.module = computeModule;
        csDesc.compute.entryPoint = "main";
        pipeline = device.CreateComputePipeline(&csDesc);
    }

    void TestDispatch(uint32_t x, uint32_t y, uint32_t z) {
        wgpu::CommandEncoder encoder = device.CreateCommandEncoder();
        wgpu::ComputePassEncoder pass = encoder.BeginComputePass();
        pass.SetPipeline(pipeline);
        pass.Dispatch(x, y, z);
        pass.EndPass();
        encoder.Finish();
    }

    wgpu::ComputePipeline pipeline;
};

// Check that 1x1x1 dispatch is OK.
TEST_F(ComputeValidationTest, PerDimensionDispatchSizeLimits_SmallestValid) {
    TestDispatch(1, 1, 1);
}

// // Check that the largest allowed dispatch is OK.
// TEST_F(ComputeValidationTest, PerDimensionDispatchSizeLimits_LargestValid) {
//     const uint32_t max = GetSupportedLimits().limits.maxComputeWorkgroupsPerDimension;
//     TestDispatch(max, max, max);
// }

// // Check that exceeding the maximum on the X dimension results in validation failure.
// TEST_F(ComputeValidationTest, PerDimensionDispatchSizeLimits_InvalidX) {
//     const uint32_t max = GetSupportedLimits().limits.maxComputeWorkgroupsPerDimension;
//     ASSERT_DEVICE_ERROR(TestDispatch(max + 1, 1, 1));
// }

// // Check that exceeding the maximum on the Y dimension results in validation failure.
// TEST_F(ComputeValidationTest, PerDimensionDispatchSizeLimits_InvalidY) {
//     const uint32_t max = GetSupportedLimits().limits.maxComputeWorkgroupsPerDimension;
//     ASSERT_DEVICE_ERROR(TestDispatch(1, max + 1, 1));
// }

// // Check that exceeding the maximum on the Z dimension results in validation failure.
// TEST_F(ComputeValidationTest, PerDimensionDispatchSizeLimits_InvalidZ) {
//     const uint32_t max = GetSupportedLimits().limits.maxComputeWorkgroupsPerDimension;
//     ASSERT_DEVICE_ERROR(TestDispatch(1, 1, max + 1));
// }

// // Check that exceeding the maximum on all dimensions results in validation failure.
// TEST_F(ComputeValidationTest, PerDimensionDispatchSizeLimits_InvalidAll) {
//     const uint32_t max = GetSupportedLimits().limits.maxComputeWorkgroupsPerDimension;
//     ASSERT_DEVICE_ERROR(TestDispatch(max + 1, max + 1, max + 1));
// }







// #include "common/Constants.h"
// #include "tests/unittests/validation/ValidationTest.h"
// #include "utils/WGPUHelpers.h"

// class ComputePipelineOverridableConstantsValidationTest : public ValidationTest {
//   protected:
//     void SetUpShadersWithDefaultValueConstants() {
//         computeModule = utils::CreateShaderModule(device, R"(
// [[override]] let c0: bool = true;      // type: bool
// [[override]] let c1: bool = false;      // default override
// [[override]] let c2: f32 = 0.0;         // type: float32
// [[override]] let c3: f32 = 0.0;         // default override
// [[override]] let c4: f32 = 4.0;         // default
// [[override]] let c5: i32 = 0;           // type: int32
// [[override]] let c6: i32 = 0;           // default override
// [[override]] let c7: i32 = 7;           // default
// [[override]] let c8: u32 = 0u;          // type: uint32
// [[override]] let c9: u32 = 0u;          // default override
// [[override(1000)]] let c10: u32 = 10u;  // default

// [[stage(compute), workgroup_size(1)]] fn main() {
//     // make sure the overridable constants are not optimized out
//     _ = u32(c0);
//     _ = u32(c1);
//     _ = u32(c2);
//     _ = u32(c3);
//     _ = u32(c4);
//     _ = u32(c5);
//     _ = u32(c6);
//     _ = u32(c7);
//     _ = u32(c8);
//     _ = u32(c9);
//     _ = u32(c10);
// })");
//     }

//     void SetUpShadersWithUninitializedConstants() {
//         computeModule = utils::CreateShaderModule(device, R"(
// [[override]] let c0: bool;              // type: bool
// [[override]] let c1: bool = false;      // default override
// [[override]] let c2: f32;               // type: float32
// [[override]] let c3: f32 = 0.0;         // default override
// [[override]] let c4: f32 = 4.0;         // default
// [[override]] let c5: i32;               // type: int32
// [[override]] let c6: i32 = 0;           // default override
// [[override]] let c7: i32 = 7;           // default
// [[override]] let c8: u32;               // type: uint32
// [[override]] let c9: u32 = 0u;          // default override
// [[override(1000)]] let c10: u32 = 10u;  // default

// [[stage(compute), workgroup_size(1)]] fn main() {
//     // make sure the overridable constants are not optimized out
//     _ = u32(c0);
//     _ = u32(c1);
//     _ = u32(c2);
//     _ = u32(c3);
//     _ = u32(c4);
//     _ = u32(c5);
//     _ = u32(c6);
//     _ = u32(c7);
//     _ = u32(c8);
//     _ = u32(c9);
//     _ = u32(c10);
// })");
//     }

//     void TestCreatePipeline(const std::vector<wgpu::ConstantEntry>& constants) {
//         wgpu::ComputePipelineDescriptor csDesc;
//         csDesc.compute.module = computeModule;
//         csDesc.compute.entryPoint = "main";
//         csDesc.compute.constants = constants.data();
//         csDesc.compute.constantCount = constants.size();
//         wgpu::ComputePipeline pipeline = device.CreateComputePipeline(&csDesc);
//     }

//     wgpu::ShaderModule computeModule;
//     wgpu::Buffer buffer;
// };

// // Basic constants lookup tests
// TEST_F(ComputePipelineOverridableConstantsValidationTest, ConstantsIdentifierLookUp) {
//     SetUpShadersWithDefaultValueConstants();
//     {
//         // Valid: no constants specified
//         std::vector<wgpu::ConstantEntry> constants;
//         TestCreatePipeline(constants);
//     }
//     {
//         // Valid: find by constant name
//         std::vector<wgpu::ConstantEntry> constants{{nullptr, "c0", 0}};
//         TestCreatePipeline(constants);
//     }
//     {
//         // Error: set the same constant twice
//         std::vector<wgpu::ConstantEntry> constants{
//             {nullptr, "c0", 0},
//             {nullptr, "c0", 1},
//         };
//         ASSERT_DEVICE_ERROR(TestCreatePipeline(constants));
//     }
//     {
//         // Valid: find by constant numeric id
//         std::vector<wgpu::ConstantEntry> constants{{nullptr, "1000", 0}};
//         TestCreatePipeline(constants);
//     }
//     {
//         // Error: constant numeric id not specified
//         std::vector<wgpu::ConstantEntry> constants{{nullptr, "9999", 0}};
//         ASSERT_DEVICE_ERROR(TestCreatePipeline(constants));
//     }
//     {
//         // Error: constant name doesn't exit
//         std::vector<wgpu::ConstantEntry> constants{{nullptr, "c99", 0}};
//         ASSERT_DEVICE_ERROR(TestCreatePipeline(constants));
//     }
// }

// // Test that it is invalid to leave any constants uninitialized
// TEST_F(ComputePipelineOverridableConstantsValidationTest, UninitializedConstants) {
//     SetUpShadersWithUninitializedConstants();
//     {
//         // Error: uninitialized constants exist
//         std::vector<wgpu::ConstantEntry> constants;
//         ASSERT_DEVICE_ERROR(TestCreatePipeline(constants));
//     }
//     {
//         // Error: uninitialized constants exist
//         std::vector<wgpu::ConstantEntry> constants{
//             {nullptr, "c0", false},
//             {nullptr, "c2", 1},
//             // c5 is missing
//             {nullptr, "c8", 1},
//         };
//         ASSERT_DEVICE_ERROR(TestCreatePipeline(constants));
//     }
//     {
//         // Valid: all constants initialized
//         std::vector<wgpu::ConstantEntry> constants{
//             {nullptr, "c0", false},
//             {nullptr, "c2", 1},
//             {nullptr, "c5", 1},
//             {nullptr, "c8", 1},
//         };
//         TestCreatePipeline(constants);
//     }
//     {
//         // Error: duplicate initializations
//         std::vector<wgpu::ConstantEntry> constants{
//             {nullptr, "c0", false}, {nullptr, "c2", 1}, {nullptr, "c5", 1},
//             {nullptr, "c8", 1},     {nullptr, "c2", 2},
//         };
//         ASSERT_DEVICE_ERROR(TestCreatePipeline(constants));
//     }
// }

// // Test that only explicitly specified numeric ID can be referenced
// TEST_F(ComputePipelineOverridableConstantsValidationTest, ConstantsIdentifierExplicitNumericID) {
//     SetUpShadersWithDefaultValueConstants();
//     {
//         // Error: constant numeric id not explicitly specified
//         // But could be impliciltly assigned to one of the constants
//         std::vector<wgpu::ConstantEntry> constants{{nullptr, "0", 0}};
//         ASSERT_DEVICE_ERROR(TestCreatePipeline(constants));
//     }
//     {
//         // Error: constant numeric id not explicitly specified
//         // But could be impliciltly assigned to one of the constants
//         std::vector<wgpu::ConstantEntry> constants{{nullptr, "1", 0}};
//         ASSERT_DEVICE_ERROR(TestCreatePipeline(constants));
//     }
//     {
//         // Error: constant numeric id not explicitly specified
//         // But could be impliciltly assigned to one of the constants
//         std::vector<wgpu::ConstantEntry> constants{{nullptr, "2", 0}};
//         ASSERT_DEVICE_ERROR(TestCreatePipeline(constants));
//     }
//     {
//         // Error: constant numeric id not explicitly specified
//         // But could be impliciltly assigned to one of the constants
//         std::vector<wgpu::ConstantEntry> constants{{nullptr, "3", 0}};
//         ASSERT_DEVICE_ERROR(TestCreatePipeline(constants));
//     }
// }

// // Test that identifiers are unique
// TEST_F(ComputePipelineOverridableConstantsValidationTest, ConstantsIdentifierUnique) {
//     SetUpShadersWithDefaultValueConstants();
//     {
//         // Valid: constant without numeric id can be referenced with variable name
//         std::vector<wgpu::ConstantEntry> constants{{nullptr, "c0", 0}};
//         TestCreatePipeline(constants);
//     }
//     {
//         // Error: constant with numeric id cannot be referenced with variable name
//         std::vector<wgpu::ConstantEntry> constants{{nullptr, "c10", 0}};
//         ASSERT_DEVICE_ERROR(TestCreatePipeline(constants));
//     }
// }


#endif







// // #include "unittests/validation/ValidationTest.h"
// #include "tests/unittests/validation/ValidationTest.h"

// #include <gtest/gtest.h>

// int main(int argc, char** argv) {
//     InitDawnValidationTestEnvironment(argc, argv);
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }