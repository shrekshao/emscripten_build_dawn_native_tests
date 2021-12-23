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



// // -------------------------------
// // end2end BasicTests

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

// #include "tests/DawnTest.h"

// #include "utils/WGPUHelpers.h"

// class BasicTests : public DawnTest {};

// // Test adapter filter by vendor id.
// TEST_P(BasicTests, VendorIdFilter) {
//     DAWN_TEST_UNSUPPORTED_IF(!HasVendorIdFilter());

//     ASSERT_EQ(GetAdapterProperties().vendorID, GetVendorIdFilter());
// }

// // Test adapter filter by backend type.
// TEST_P(BasicTests, BackendType) {
//     DAWN_TEST_UNSUPPORTED_IF(!HasBackendTypeFilter());

//     ASSERT_EQ(GetAdapterProperties().backendType, GetBackendTypeFilter());
// }

// // Test Queue::WriteBuffer changes the content of the buffer, but really this is the most
// // basic test possible, and tests the test harness
// TEST_P(BasicTests, QueueWriteBuffer) {
//     wgpu::BufferDescriptor descriptor;
//     descriptor.size = 4;
//     descriptor.usage = wgpu::BufferUsage::CopySrc | wgpu::BufferUsage::CopyDst;
//     wgpu::Buffer buffer = device.CreateBuffer(&descriptor);

//     uint32_t value = 0x01020304;
//     queue.WriteBuffer(buffer, 0, &value, sizeof(value));

//     EXPECT_BUFFER_U32_EQ(value, buffer, 0);
// }

// // Test a validation error for Queue::WriteBuffer but really this is the most basic test possible
// // for ASSERT_DEVICE_ERROR
// TEST_P(BasicTests, QueueWriteBufferError) {
//     wgpu::BufferDescriptor descriptor;
//     descriptor.size = 4;
//     descriptor.usage = wgpu::BufferUsage::CopySrc | wgpu::BufferUsage::CopyDst;
//     wgpu::Buffer buffer = device.CreateBuffer(&descriptor);

//     uint8_t value = 187;
//     ASSERT_DEVICE_ERROR(queue.WriteBuffer(buffer, 1000, &value, sizeof(value)));
// }

// DAWN_INSTANTIATE_TEST(BasicTests,
//                       D3D12Backend(),
//                       MetalBackend(),
//                       OpenGLBackend(),
//                       OpenGLESBackend(),
//                       VulkanBackend());








// ---------------------
// unittests EnumClassBitmasksTests.cpp

// Copyright 2017 The Dawn Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "gtest/gtest.h"

#include "dawn/EnumClassBitmasks.h"

namespace dawn {

    enum class Color : uint32_t {
        R = 1,
        G = 2,
        B = 4,
        A = 8,
    };

    template <>
    struct IsDawnBitmask<Color> {
        static constexpr bool enable = true;
    };

    TEST(BitmaskTests, BasicOperations) {
        Color test1 = Color::R | Color::G;
        ASSERT_EQ(1u | 2u, static_cast<uint32_t>(test1));

        Color test2 = test1 ^ (Color::R | Color::A);
        ASSERT_EQ(2u | 8u, static_cast<uint32_t>(test2));

        Color test3 = test2 & Color::A;
        ASSERT_EQ(8u, static_cast<uint32_t>(test3));

        Color test4 = ~test3;
        ASSERT_EQ(~uint32_t(8), static_cast<uint32_t>(test4));
    }

    TEST(BitmaskTests, AssignOperations) {
        Color test1 = Color::R;
        test1 |= Color::G;
        ASSERT_EQ(1u | 2u, static_cast<uint32_t>(test1));

        Color test2 = test1;
        test2 ^= (Color::R | Color::A);
        ASSERT_EQ(2u | 8u, static_cast<uint32_t>(test2));

        Color test3 = test2;
        test3 &= Color::A;
        ASSERT_EQ(8u, static_cast<uint32_t>(test3));
    }

    TEST(BitmaskTests, BoolConversion) {
        bool test1 = Color::R | Color::G;
        ASSERT_TRUE(test1);

        bool test2 = Color::R & Color::G;
        ASSERT_FALSE(test2);

        bool test3 = Color::R ^ Color::G;
        ASSERT_TRUE(test3);

        if (Color::R & ~Color::R) {
            ASSERT_TRUE(false);
        }
    }

    TEST(BitmaskTests, ThreeOrs) {
        Color c = Color::R | Color::G | Color::B;
        ASSERT_EQ(7u, static_cast<uint32_t>(c));
    }

    TEST(BitmaskTests, ZeroOrOneBits) {
        Color zero = static_cast<Color>(0);
        ASSERT_TRUE(HasZeroOrOneBits(zero));
        ASSERT_TRUE(HasZeroOrOneBits(Color::R));
        ASSERT_TRUE(HasZeroOrOneBits(Color::G));
        ASSERT_TRUE(HasZeroOrOneBits(Color::B));
        ASSERT_TRUE(HasZeroOrOneBits(Color::A));
        ASSERT_FALSE(HasZeroOrOneBits(static_cast<Color>(Color::R | Color::G)));
        ASSERT_FALSE(HasZeroOrOneBits(static_cast<Color>(Color::G | Color::B)));
        ASSERT_FALSE(HasZeroOrOneBits(static_cast<Color>(Color::B | Color::A)));
    }

}  // namespace dawn






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

// #include "utils/ComboRenderPipelineDescriptor.h"
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

