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






















struct PoolAlloc {
    // [ free stack, len == chunkCount*u32size ] [ chunks ] [ more chunks ]

    void* start = nullptr;
    u32 chunkCount = 0;

    u32* freeChunks = nullptr;
    s32 lastFree = 0;

    void* chunkStart = nullptr;
    u32 chunkSize = 0;


    PoolAlloc() { };
    PoolAlloc(u32 _chunkSize, u32 _chunkCount) :
        chunkCount(_chunkCount), chunkSize(_chunkSize) {

        this->start = malloc((chunkCount * sizeof(u32)) + (chunkSize * chunkCount));
        MTN_ASSERT(this->start);

        // initialize memory for free stack
        this->freeChunks = static_cast<u32*>(this->start);
        for (uint i = 0; i < this->chunkCount; i++) {
            this->freeChunks[i] = i; }
        this->lastFree = chunkCount-1;


        this->chunkStart = static_cast<char*>(this->start) + (chunkCount * sizeof(u32));
    };






    void clear() {

        for (uint i = 0; i < this->chunkCount; i++) {
            this->freeChunks[i] = i; }
        this->lastFree = this->chunkCount-1;
    }






    void* get() {
        u32 idx = this->freeChunks[this->lastFree];

        MTN_ASSERT(this->lastFree >= 0);
        this->lastFree--;

        return static_cast<char*>(this->chunkStart) + (idx * this->chunkSize);
    }


    void free(void* l) {

        MTN_ASSERT((this->lastFree < ((int)this->chunkCount - 1)));
        s64 diff = (static_cast<char*>(l) - static_cast<char*>(this->chunkStart));
        MTN_ASSERT((diff % this->chunkSize) == 0);
        s64 idx = (diff) / this->chunkSize;
        MTN_ASSERT(idx < this->chunkCount);
        MTN_ASSERT(idx >= 0);

        // check free list to see if this chuck exists
        // if it does, dont let it be freed again
        for(int i = this->lastFree; i >= 0; i--) {
            MTN_ASSERT(this->freeChunks[i] != idx); }


        this->lastFree++;
        this->freeChunks[this->lastFree] = (u32)idx;
    }




    ~PoolAlloc() { free(this->start); }
    void destroy(PoolAlloc* p) { this->~PoolAlloc(); }
};


#define ALLOC_POOL(pool, type) (static_cast<type*>(pool.get()))
#define NEW_POOL(pool, type) &(*(static_cast<type*>(pool.get())) = type())


