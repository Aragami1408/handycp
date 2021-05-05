#pragma once

#include <cstdint>

namespace handycp {
    struct data {
        std::uint32_t key;
        std::uint32_t value;
    };

    union RMElement {
        std::uint64_t raw;
        struct {
            std::uint32_t key;
            std::uint32_t value;
        } data;
    };    

    class RadixMap {
    private:
        size_t max;
        size_t end;
        std::uint32_t counter;
        RMElement *contents;
        RMElement *temp;
    public:
        RadixMap(size_t max);
        ~RadixMap();
        void sort();
        RMElement *find(std::uint32_t to_find);
        bool add(std::uint32_t key, std::uint32_t value);
        bool del(RMElement *el);
    };
};

