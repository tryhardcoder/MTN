#pragma once

#include "buildConfig.h"
#include "utils.h"
#include <malloc.h>




struct BumpAlloc {
    void* start = nullptr;
    void* offset = nullptr;
    u64 reserved = 0;


    BumpAlloc() { }

    BumpAlloc(u64 size) {
        this->reserved = size;
        this->start = calloc(1, size);
        this->offset = this->start;
    }



    ~BumpAlloc() {
        this->reserved = 0;
        free(this->start);
        this->start = nullptr;
        this->offset = 0;
    }
    void destroy() { this->~BumpAlloc(); }




    void clear() { this->offset = this->start; }
    void* get(u64 size) {

        char* o = static_cast<char*>(this->offset);
        MTN_ASSERT(o + size < static_cast<char*>(this->start) + this->reserved);

        this->offset = o+size;
        return o;
    }

    void pop(u64 size) {

        char* o = static_cast<char*>(this->offset);
        MTN_ASSERT(o - size >= static_cast<char*>(this->start));
        this->offset = o-size;
    }
};



#define ALLOC_BUMP(bump, type) (static_cast<type*>(bump.get(sizeof(type))))
//nice
#define ALLOC_NEW_BUMP(bump, type) &(*(ALLOC_BUMP(bump, type)) = type())

#define ALLOC_ARR_BUMP(bump, count, type) static_cast<type*>(bump.get(sizeof(type) * (count)))
