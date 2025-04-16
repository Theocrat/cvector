/** CVECTOR
 * 
 * TODO: Write this docstring :p
 */

#include <stdlib.h>
#define new(dtype, size) (dtype *)malloc(sizeof(dtype) * size)


#define vectorType(dtype) struct { \
    int size;     \
    int capacity; \
    dtype *data;  \
}

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
    vtype vec3 = {0, vec1.size + vec2.size, NULL};   \
    vec3.data = new(dtype, vec3.size);               \
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