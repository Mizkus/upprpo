#include <gtest/gtest.h>
#include <climits>
#include "../include/bitArr.h"


TEST(BitArrayTest, Construct) {
BitArray bits(8, 255);
EXPECT_EQ(bits.size(), 8);
for (
int i = 0;
i < 8; i++) {
EXPECT_TRUE(bits[i]);
}

BitArray bits1(100, ULONG_MAX);
EXPECT_EQ(bits1.size(), 100);
for (
int i = 0;
i < sizeof(long); i++) {
if (i < sizeof(long))
EXPECT_TRUE(bits1[i]);
else EXPECT_FALSE(bits1[i]);
}
}

TEST(BitArrayTest, Empty){
BitArray bits1(0);
EXPECT_TRUE(bits1.empty());
BitArray bits2(1);
EXPECT_FALSE(bits2.empty());
}

TEST(BitArrayTest, ToString){
BitArray bits(10, 255);
EXPECT_EQ(bits.to_string(), "1111111100");
bits.resize(5);
EXPECT_EQ(bits.to_string(), "11111");
bits.resize(12, 0);
EXPECT_EQ(bits.to_string(), "111110000000");
}

TEST(BitArrayTest, Resize){
BitArray bits(10);
bits.resize(15, 1);
EXPECT_EQ(bits.to_string(), "000000000011111");
}

TEST(BitArrayTest, Clear){
BitArray bits(10);
EXPECT_FALSE(bits.empty());
bits.

clear();

EXPECT_TRUE(bits.empty());
}

TEST(BitArrayTest, Set){
BitArray bits(10);
bits.set(8, 1);
EXPECT_EQ(bits.to_string(), "0000000010");
bits.

set();

EXPECT_EQ(bits.to_string(), "1111111111");
}

TEST(BitArrayTest, PushBack){
BitArray bits(10);
bits.push_back(1);
bits.push_back(0);
bits.push_back(1);
EXPECT_EQ(bits.to_string(), "0000000000101");
bits.push_back(1);
EXPECT_EQ(bits.to_string(), "00000000001011");
}

TEST(BitArrayTest, Reset){
BitArray bits(10);
bits.set(8, 1);
bits.set(9, 1);
bits.reset(9);
EXPECT_EQ(bits.to_string(), "0000000010");
bits.

set();

bits.

reset();

EXPECT_EQ(bits.to_string(), "0000000000");
}

TEST(BitArrayTest, Any){
BitArray bits(10);
EXPECT_FALSE(bits.any());
bits.set(1, 1);
EXPECT_TRUE(bits.any());
bits.

reset();

bits.resize(1000);
EXPECT_FALSE(bits.any());
bits.set(1, 999);
EXPECT_TRUE(bits.any());
}

TEST(BitArrayTest, None){
BitArray bits(10);
EXPECT_TRUE(bits.none());
bits.set(1, 1);
EXPECT_FALSE(bits.none());
bits.

reset();

bits.resize(1000);
EXPECT_TRUE(bits.none());
bits.set(1, 999);
EXPECT_FALSE(bits.none());
}

TEST(BitArrayTest, Inverse){
BitArray bits(10);
bits = ~bits;
EXPECT_EQ(bits.to_string(), "1111111111");
bits.set(2, 0);
bits = ~bits;
EXPECT_EQ(bits.to_string(), "0010000000");
}

TEST(BitArrayTest, Count){
BitArray bits(10);
bits = ~bits;
EXPECT_EQ(bits.count(), 10);
bits.set(2, 0);
bits = ~bits;
EXPECT_EQ(bits.count(), 1);
}

TEST(BitArrayTest, OperationEq){
BitArray bits(10);
bits = ~bits;
EXPECT_EQ(bits.to_string(), "1111111111");
bits.set(2, 0);
bits = ~bits;
EXPECT_EQ(bits.to_string(), "0010000000");
}

TEST(BitArrayTest, LogicAnd){
BitArray a(10, 1);
BitArray b(9);
EXPECT_THROW(a &= b, std::runtime_error);
b.resize(10);
a &= b;
EXPECT_EQ(a.to_string(), "0000000000");
}

TEST(BitArrayTest, LogicOr){
BitArray a(10, 255);
BitArray b(9);
EXPECT_THROW(a |= b, std::runtime_error);
b.resize(10);
a |= b;
EXPECT_EQ(a.to_string(), "1111111100");
}

TEST(BitArrayTest, LogicXor){
BitArray a(10, 255);
BitArray b(9);
EXPECT_THROW(a ^= b, std::runtime_error);
b.resize(10);
a ^= b;
EXPECT_EQ(a.to_string(), "1111111100");
}


