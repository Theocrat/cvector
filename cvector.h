/** CVECTOR
 * 
 * TODO: Write this docstring :p
 */

#ifndef __C_VECTOR_H__
#define __C_VECTOR_H__

// -- REQUIREMENTS: We need STDLIB (memory allocations), and this `new` macro --

#include <stdlib.h>
#define new(dtype, size) (dtype *)malloc(sizeof(dtype) * size)

// -- STRUCT: We define the macro for creating structs to store vectors -- 

#define vectorType(dtype) struct { \
    int size;     \
    int capacity; \
    dtype *data;  \
}

// -- FUNCTIONS: We define the four functions described in the README.md --

#define constructorMethod(vtype, dtype) { \
    vtype vec = {0, 1, NULL};  \
    vec.data = new(dtype, 1);  \
    return vec;                \
}

#define appendMethod(vtype, dtype, vector, item) { \
    vtype newVector = {vector.size + 1, vector.capacity, NULL}; \
    while (newVector.capacity < newVector.size) {              \
        newVector.capacity *= 2;                                \
    }                                                           \
                                                                \
    newVector.data = (dtype *)realloc(vector.data, newVector.capacity);  \
    newVector.data[newVector.size - 1] = item;                  \
    return newVector;                                           \
}

#define concatMethod(vtype, dtype, vec1, vec2) {     \
    vtype vec3 = {vec1.size + vec2.size, 1, NULL};   \
                                                     \
    vec3.capacity = 1;                               \
    while (vec3.capacity < vec3.size) {              \
        vec3.capacity *= 2;                          \
    }                                                \
    vec3.data = new(dtype, vec3.capacity);           \
                                                     \
    int pos = 0;                                     \
                                                     \
    for (int i = 0; i < vec1.size; i++) {            \
        vec3.data[pos] = vec1.data[i];               \
        pos++;                                       \
    }                                                \
                                                     \
    for (int i = 0; i < vec2.size; i++) {            \
        vec3.data[pos] = vec2.data[i];               \
        pos++;                                       \
    }                                                \
                                                     \
    return vec3;                                     \
}


#define sliceMethod(vtype, dtype, vec, start, stop) { \
    start = (start > vec.size) ? vec.size : start;  \
    stop = (stop > vec.size) ? vec.size : stop;     \
                                                    \
    vtype slice = {0, 1, NULL};                     \
    int length = stop - start, i, j;                \
                                                    \
    if (length < 1) {                               \
        return slice;                               \
    }                                               \
                                                    \
    slice.size = length;                            \
    while (slice.capacity < slice.size) {           \
        slice.capacity *= 2;                        \
    }                                               \
                                                    \
    slice.data = new(dtype, length);                \
    for (i = start, j = 0; i < stop; i++, j++) {    \
        slice.data[j] = vec.data[i];                \
    }                                               \
                                                    \
    return slice;                                   \
}


// -- IDIOMS: We define `iterate` and `enumerate` as discussed --

#define iterate(item, vector) \
    for (                               \
        _ = 0, item = vector.data[0];   \
        _ < vector.size;                \
        item = vector.data[_ = _ + 1]   \
    )

#define enumerate(i, v, vector) \
    for (                               \
        i = 0, v = vector.data[0];      \
        i < vector.size;                \
        v = vector.data[i = i + 1]      \
    )

int _;

#endif