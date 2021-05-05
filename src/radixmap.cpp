#include <cstdint>
#include "radixmap.h"
#include <stdint.h>


handycp::RadixMap::RadixMap(size_t max) {
    this->contents = new RMElement;
    this->temp = new RMElement;
    this->max = max;
    this->end = 0;
}

handycp::RadixMap::~RadixMap() {
    delete this->contents;
    delete this->temp;
    delete this;
}

#define ByteOf(x,y) (((std::uint8_t *)x)[(y)])

static inline void radix_sort(short offset, std::uint16_t max, std::uint64_t *source, std::uint64_t *dest) {
    std::uint64_t count[256] = {0};
    std::uint64_t *cp = nullptr;
    std::uint64_t *sp = nullptr;
    std::uint64_t *end = nullptr;
    std::uint64_t s = 0;
    std::uint64_t c = 0;

    for(sp=source, end=source+max; sp<end; sp++) {
        count[ByteOf(sp, offset)]++;
    }
    
    for (s = 0, cp = count, end = count + 256; cp < end; cp++) {
        c = *cp;
        *cp = s;
        s += c;
    }
   
    for (sp = source, end = source + max; sp < end; sp++) {
        cp = count + ByteOf(sp, offset);
        dest[*cp] = *sp;
        ++(*cp);
    }
}

void handycp::RadixMap::sort() {
    std::uint64_t *source = &this->contents[0].raw;
    std::uint64_t *temp = &this->temp[0].raw;

    radix_sort(0, this->end, source, temp);
    radix_sort(1, this->end, temp, source);
    radix_sort(2, this->end, source, temp);
    radix_sort(3, this->end, temp, source);
}

handycp::RMElement* handycp::RadixMap::find(std::uint32_t to_find) {
    int low = 0;
    int high = this->end - 1;
    handycp::RMElement *data = this->contents;

    while(low <= high) {
        int mid = low + (high - low)/2;
        std::uint32_t key = data[mid].data.key;

        if(to_find < key) {
            high = mid - 1;
        }
        else if (to_find > key) {
            low = mid + 1;
        }
        else {
            return &data[mid];
        }
    }
    return nullptr;
}

bool handycp::RadixMap::add(std::uint32_t key, std::uint32_t value) {
    handycp::RMElement element = {.data = {.key = key, .value = value}};
    if(!(key < UINT32_MAX) || !(this->end + 1 < this->max)) {
        goto error;
    }    
    
    this->contents[this->end++] = element;

    handycp::RadixMap::sort();

    return true;
error:
    return false;
}

bool handycp::RadixMap::del(RMElement *el) {
    if(!(this->end > 0) || !(el != nullptr)) {
        goto error;
    }
    
    el->data.key = UINT32_MAX;

    if(this->end > 1) {
        handycp::RadixMap::sort();
    }

    this->end--;

    return true;
error:
    return false;
}
