#include "BitString.h"

#include <algorithm>
#include <stdexcept>

namespace {
static unsigned char op_and(unsigned char a, unsigned char b) { return static_cast<unsigned char>((a & 1u) & (b & 1u)); }
static unsigned char op_or(unsigned char a, unsigned char b) { return static_cast<unsigned char>((a & 1u) | (b & 1u)); }
static unsigned char op_xor(unsigned char a, unsigned char b) { return static_cast<unsigned char>((a & 1u) ^ (b & 1u)); }
}

void BitString::validateBit(unsigned char v) {
	if (v != 0 && v != 1) {
		throw std::invalid_argument("BitString: bit must be 0 or 1");
	}
}

size_t BitString::normalizePrefix(const unsigned char *ptr, size_t len) {
	size_t i = 0;
	while (i < len && ptr[i] == 0) {
		++i;
	}
	return i;
}

BitString BitString::fromAligned(const unsigned char *lhs, size_t lhsLen,
								   const unsigned char *rhs, size_t rhsLen,
								   unsigned char (*op)(unsigned char, unsigned char)) {
	const size_t maxLen = std::max(lhsLen, rhsLen);
	BitString result(maxLen, 0);
	for (size_t i = 0; i < maxLen; ++i) {
		const size_t li = (i < maxLen - lhsLen) ? static_cast<size_t>(-1) : (i - (maxLen - lhsLen));
		const size_t ri = (i < maxLen - rhsLen) ? static_cast<size_t>(-1) : (i - (maxLen - rhsLen));
		const unsigned char lb = (li == static_cast<size_t>(-1)) ? 0 : lhs[li];
		const unsigned char rb = (ri == static_cast<size_t>(-1)) ? 0 : rhs[ri];
		result.data_[i] = op(lb, rb);
	}
	return result;
}

BitString::BitString() : data_(nullptr), size_(0) {}

BitString::BitString(const size_t &n, unsigned char value) : data_(nullptr), size_(n) {
	validateBit(value);
	if (n > 0) {
		data_ = new unsigned char[n];
		for (size_t i = 0; i < n; ++i) data_[i] = value;
	}
}

BitString::BitString(const std::initializer_list<unsigned char> &bits) : data_(nullptr), size_(bits.size()) {
	if (size_ > 0) {
		data_ = new unsigned char[size_];
		size_t i = 0;
		for (auto b : bits) {
			validateBit(b);
			data_[i++] = b;
		}
	}
}

BitString::BitString(const std::string &bitString) : data_(nullptr), size_(bitString.size()) {
	if (size_ > 0) {
		data_ = new unsigned char[size_];
		for (size_t i = 0; i < size_; ++i) {
			char c = bitString[i];
			if (c != '0' && c != '1') {
				delete[] data_;
				data_ = nullptr;
				size_ = 0;
				throw std::invalid_argument("BitString: string must contain only '0' or '1'");
			}
			data_[i] = static_cast<unsigned char>(c - '0');
		}
	}
}

BitString::BitString(const BitString &other) : data_(nullptr), size_(other.size_) {
	if (size_ > 0) {
		data_ = new unsigned char[size_];
		for (size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
	}
}

BitString::BitString(BitString &&other) noexcept : data_(other.data_), size_(other.size_) {
	other.data_ = nullptr;
	other.size_ = 0;
}

BitString::~BitString() noexcept {
	delete[] data_;
	data_ = nullptr;
	size_ = 0;
}

size_t BitString::size() const noexcept { return size_; }

unsigned char BitString::at(size_t index) const {
	if (index >= size_) throw std::out_of_range("BitString::at index out of range");
	return data_[index];
}

std::string BitString::toString() const {
	std::string s;
	s.reserve(size_);
	for (size_t i = 0; i < size_; ++i) s.push_back(static_cast<char>('0' + data_[i]));
	return s;
}

BitString BitString::logicalAnd(const BitString &rhs) const {
	return fromAligned(data_, size_, rhs.data_, rhs.size_, op_and);
}

BitString BitString::logicalOr(const BitString &rhs) const {
	return fromAligned(data_, size_, rhs.data_, rhs.size_, op_or);
}

BitString BitString::logicalXor(const BitString &rhs) const {
	return fromAligned(data_, size_, rhs.data_, rhs.size_, op_xor);
}

BitString BitString::logicalNot() const {
	BitString r(size_, 0);
	for (size_t i = 0; i < size_; ++i) r.data_[i] = static_cast<unsigned char>(data_[i] ^ 1u);
	return r;
}

BitString BitString::add(const BitString &rhs) const {
	const size_t maxLen = std::max(size_, rhs.size_);
	BitString result(maxLen + 1, 0);
	int carry = 0;
	for (size_t pos = 0; pos < maxLen; ++pos) {
		const size_t li = size_ > pos ? size_ - 1 - pos : static_cast<size_t>(-1);
		const size_t ri = rhs.size_ > pos ? rhs.size_ - 1 - pos : static_cast<size_t>(-1);
		int lb = (li == static_cast<size_t>(-1)) ? 0 : data_[li];
		int rb = (ri == static_cast<size_t>(-1)) ? 0 : rhs.data_[ri];
		int sum = lb + rb + carry;
		result.data_[result.size_ - 1 - pos] = static_cast<unsigned char>(sum & 1);
		carry = (sum >> 1) & 1;
	}
	result.data_[0] = static_cast<unsigned char>(carry);
	if (result.data_[0] == 0) {
		BitString trimmed(result.size_ - 1, 0);
		for (size_t i = 0; i < trimmed.size_; ++i) trimmed.data_[i] = result.data_[i + 1];
		return trimmed;
	}
	return result;
}

BitString BitString::subtract(const BitString &rhs) const {
	if (rhs.greaterThan(*this)) {
		throw std::invalid_argument("BitString::subtract: negative result not allowed");
	}
	const size_t maxLen = std::max(size_, rhs.size_);
	BitString result(maxLen, 0);
	int borrow = 0;
	for (size_t pos = 0; pos < maxLen; ++pos) {
		const size_t li = size_ > pos ? size_ - 1 - pos : static_cast<size_t>(-1);
		const size_t ri = rhs.size_ > pos ? rhs.size_ - 1 - pos : static_cast<size_t>(-1);
		int lb = (li == static_cast<size_t>(-1)) ? 0 : data_[li];
		int rb = (ri == static_cast<size_t>(-1)) ? 0 : rhs.data_[ri];
		int diff = lb - rb - borrow;
		if (diff >= 0) {
			result.data_[result.size_ - 1 - pos] = static_cast<unsigned char>(diff);
			borrow = 0;
		} else {
			result.data_[result.size_ - 1 - pos] = static_cast<unsigned char>(diff + 2);
			borrow = 1;
		}
	}
	size_t leading = normalizePrefix(result.data_, result.size_);
	if (leading == 0) return result;
	BitString trimmed(result.size_ - leading, 0);
	for (size_t i = 0; i < trimmed.size_; ++i) trimmed.data_[i] = result.data_[i + leading];
	return trimmed;
}

bool BitString::equals(const BitString &rhs) const noexcept {
	size_t lLead = normalizePrefix(data_, size_);
	size_t rLead = normalizePrefix(rhs.data_, rhs.size_);
	size_t lLen = size_ - lLead;
	size_t rLen = rhs.size_ - rLead;
	if (lLen != rLen) return false;
	for (size_t i = 0; i < lLen; ++i) if (data_[lLead + i] != rhs.data_[rLead + i]) return false;
	return true;
}

bool BitString::lessThan(const BitString &rhs) const noexcept {
	size_t lLead = normalizePrefix(data_, size_);
	size_t rLead = normalizePrefix(rhs.data_, rhs.size_);
	size_t lLen = size_ - lLead;
	size_t rLen = rhs.size_ - rLead;
	if (lLen != rLen) return lLen < rLen;
	for (size_t i = 0; i < lLen; ++i) {
		if (data_[lLead + i] != rhs.data_[rLead + i]) return data_[lLead + i] < rhs.data_[rLead + i];
	}
	return false;
}