#include <gtest/gtest.h>
#include <stdexcept>
#include "bracket_validator.h"

class BracketValidatorTest : public ::testing::Test {
protected:
    void SetUp() override {
       
    }
};

TEST_F(BracketValidatorTest, EmptyStringIsValid) {
    EXPECT_TRUE(BracketValidator::isValid(""));
}

TEST_F(BracketValidatorTest, SimpleValidSequence) {
    EXPECT_TRUE(BracketValidator::isValid("()"));
}

TEST_F(BracketValidatorTest, SimpleInvalidSequence) {
    EXPECT_FALSE(BracketValidator::isValid(")("));
}

TEST_F(BracketValidatorTest, Example1_Invalid) {
    EXPECT_FALSE(BracketValidator::isValid(")(()))"));
}

TEST_F(BracketValidatorTest, Example2_Invalid) {
    EXPECT_FALSE(BracketValidator::isValid("("));
}

TEST_F(BracketValidatorTest, Example3_Valid) {
    EXPECT_TRUE(BracketValidator::isValid("(())((()())())"));
}

TEST_F(BracketValidatorTest, ComplexValidSequence) {
    EXPECT_TRUE(BracketValidator::isValid("((()())(()))"));
}

TEST_F(BracketValidatorTest, ComplexInvalidSequence) {
    EXPECT_FALSE(BracketValidator::isValid("((()()))(()))"));
}

TEST_F(BracketValidatorTest, OnlyClosingBrackets) {
    EXPECT_FALSE(BracketValidator::isValid("))"));
}

TEST_F(BracketValidatorTest, OnlyOpeningBrackets) {
    EXPECT_FALSE(BracketValidator::isValid("((("));
}

TEST_F(BracketValidatorTest, NegativeBalanceAtEnd) {
    EXPECT_FALSE(BracketValidator::isValid("())"));
}

TEST_F(BracketValidatorTest, PositiveBalanceAtEnd) {
    EXPECT_FALSE(BracketValidator::isValid("(()"));
}


TEST_F(BracketValidatorTest, TooLongStringThrowsException) {
    std::string tooLong(101, '(');
    EXPECT_THROW(BracketValidator::isValid(tooLong), std::invalid_argument);
}

TEST_F(BracketValidatorTest, InvalidCharactersThrowException) {
    EXPECT_THROW(BracketValidator::isValid("(a)"), std::invalid_argument);
    EXPECT_THROW(BracketValidator::isValid("()[]"), std::invalid_argument);
    EXPECT_THROW(BracketValidator::isValid("( )"), std::invalid_argument);
}

TEST_F(BracketValidatorTest, StaticMethodsWork) {
    EXPECT_EQ(BracketValidator::getMaxInputLength(), 100);
    EXPECT_EQ(BracketValidator::getAllowedCharacters(), "()");
}