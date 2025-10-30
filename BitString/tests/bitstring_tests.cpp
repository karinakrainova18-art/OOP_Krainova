#include <gtest/gtest.h>
#include "BitString.h"

TEST(BitStringCpp_Basic, ConstructAndToString) {
	BitString a{"10101"};
	EXPECT_EQ(a.toString(), std::string("10101"));
	BitString b(5, 1);
	EXPECT_EQ(b.toString(), std::string("11111"));
}

TEST(BitStringCpp_Access, AtAndBounds) {
	BitString a{"01"};
	EXPECT_EQ(a.at(0), 0);
	EXPECT_EQ(a.at(1), 1);
	EXPECT_THROW(a.at(2), std::out_of_range);
}

TEST(BitStringCpp_Logic, AndOrXorNot) {
	BitString a{"10101"};
	BitString b{"00111"};
	EXPECT_EQ(a.logicalAnd(b).toString(), std::string("00101"));
	EXPECT_EQ(a.logicalOr(b).toString(),  std::string("10111"));
	EXPECT_EQ(a.logicalXor(b).toString(), std::string("10010"));
	EXPECT_EQ(a.logicalNot().toString(),  std::string("01010"));
}

TEST(BitStringCpp_Logic, DifferentSizesAlignLeftPad) {
	BitString a{"1"};
	BitString b{"0011"};
	EXPECT_EQ(a.logicalAnd(b).toString(), std::string("0001"));
}

TEST(BitStringCpp_Arith, AddSubtract) {
	BitString a{"10101"};
	BitString b{"00111"};
	EXPECT_EQ(a.add(b).toString(), std::string("11100"));
	EXPECT_EQ(a.subtract(b).toString(), std::string("1110"));
}

TEST(BitStringCpp_Compare, IgnoreLeadingZeros) {
	BitString a{"000101"};
	BitString b{"101"};
	EXPECT_TRUE(a.equals(b));
	EXPECT_FALSE(a.lessThan(b));
	EXPECT_FALSE(a.greaterThan(b));
}

TEST(BitStringCpp_Exceptions, InvalidString) {
	EXPECT_THROW(BitString("10a01"), std::invalid_argument);
}

TEST(BitStringCpp_Immutability, MethodsReturnNewObjects) {
	BitString a{"101"};
	auto b = a.logicalNot();
	EXPECT_EQ(a.toString(), std::string("101"));
	EXPECT_EQ(b.toString(), std::string("010"));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}