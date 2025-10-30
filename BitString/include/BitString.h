#pragma once

#include <cstddef>
#include <initializer_list>
#include <string>

class BitString {
public:
	BitString();
	BitString(const size_t &n, unsigned char value = 0);
	BitString(const std::initializer_list<unsigned char> &bits);
	BitString(const std::string &bitString);
	BitString(const BitString &other);
	BitString(BitString &&other) noexcept;
	~BitString() noexcept;

	size_t size() const noexcept;
	unsigned char at(size_t index) const;
	std::string toString() const;

	BitString logicalAnd(const BitString &rhs) const;
	BitString logicalOr(const BitString &rhs) const;
	BitString logicalXor(const BitString &rhs) const;
	BitString logicalNot() const;

	BitString add(const BitString &rhs) const;
	BitString subtract(const BitString &rhs) const;

	BitString andAssign(const BitString &rhs) const { return logicalAnd(rhs); }
	BitString orAssign(const BitString &rhs) const { return logicalOr(rhs); }
	BitString xorAssign(const BitString &rhs) const { return logicalXor(rhs); }
	BitString notAssign() const { return logicalNot(); }
	BitString addAssign(const BitString &rhs) const { return add(rhs); }
	BitString subtractAssign(const BitString &rhs) const { return subtract(rhs); }

	bool equals(const BitString &rhs) const noexcept;
	bool lessThan(const BitString &rhs) const noexcept;
	bool greaterThan(const BitString &rhs) const noexcept { return rhs.lessThan(*this); }

private:
	unsigned char *data_;
	size_t size_;

	static void validateBit(unsigned char v);
	static size_t normalizePrefix(const unsigned char *ptr, size_t len);
	static BitString fromAligned(const unsigned char *lhs, size_t lhsLen,
	                            const unsigned char *rhs, size_t rhsLen,
	                            unsigned char (*op)(unsigned char, unsigned char));
};