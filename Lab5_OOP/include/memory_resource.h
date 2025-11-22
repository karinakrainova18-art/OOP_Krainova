#pragma once
#include <memory_resource>
#include <vector>

class HeapTrackingResource : public std::pmr::memory_resource {
public:
    HeapTrackingResource() = default;
    
    ~HeapTrackingResource() override {
        for (auto& block_info : allocated_blocks) {
            ::operator delete(block_info.ptr, std::align_val_t(block_info.alignment));
        }
    }

    HeapTrackingResource(const HeapTrackingResource&) = delete;
    HeapTrackingResource& operator=(const HeapTrackingResource&) = delete;

protected:
    void* do_allocate(size_t bytes, size_t alignment) override {
        for (auto it = free_blocks.begin(); it != free_blocks.end(); ++it) {
            if (it->size >= bytes && it->alignment == alignment) {
                void* ptr = it->ptr;
                allocated_blocks.push_back(*it);
                free_blocks.erase(it);
                return ptr;
            }
        }

        void* ptr = ::operator new(bytes, std::align_val_t(alignment));
        allocated_blocks.push_back({ptr, bytes, alignment});
        return ptr;
    }

    void do_deallocate(void* p, size_t bytes, size_t alignment) override {
        for (auto it = allocated_blocks.begin(); it != allocated_blocks.end(); ++it) {
            if (it->ptr == p) {
                free_blocks.push_back(*it);
                allocated_blocks.erase(it);
                return;
            }
        }
    }

    bool do_is_equal(const memory_resource& other) const noexcept override {
        return this == &other;
    }

private:
    struct BlockInfo {
        void* ptr;
        size_t size;
        size_t alignment;
    };
    
    std::vector<BlockInfo> allocated_blocks;
    std::vector<BlockInfo> free_blocks;
};