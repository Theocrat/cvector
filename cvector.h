/** CVECTOR
 * 
 * This header file defines macros in C, that allow users to create structures 
 * and functions for implementing the vector data structure that is used in 
 * C++.
 * 
 * Users are recommended to visit the repository at:
 * https://github.com/Theocrat/cvector
 * 
 * Further, the repository has an extensive README.md file at:
 * https://github.com/Theocrat/cvector/blob/main/README.md
 * 
 * This readme is part of the repo, so if you have come across this file as 
 * part of the repository, then you will be able to find the readme file in
 * the same repository as well.
 * 
 * Since it is possible that the README is not accessible, this documentation
 * will provide a sufficient description of this file and what it does.
 * 
 * 
 * 1. STATUATORY WARNINGS
 *    ===================
 *      
 *      This header is meant to be used seamlessly by users of high-level
 *      languages. This seamlessness cannot be achieved by restricting literals
 *      to long, ungainly names. Hence, I have taken the liberty to name two 
 *      of my macros `iterate` and `enumerate`. 
 * 
 *      Of course, these may clash with the names of your methods. In case 
 *      they do, and you absolutely cannot change the names of those methods,
 *      use a local copy of this header for the project and rename the macros
 *      in that local copy.
 *      
 * 
 * 2. TOKENS DEFINED
 *    ==============
 *      
 *      The following tokens have been defined in this header file, and may
 *      collide with tokens of similar name if they occur in any other section
 *      of the codebase or the included headers (or external Assembly objects).
 *   
 *      (A) _mallocate_dynamically: Macro wrapper for malloc. Its pretty handy.
 *      (B) __hidden_iterator: Iterator variable, used internally.
 *      (C) iterate: Macro for iterating a vector object.
 *      (D) enumerate: Macro for iterating a vector object, but with indices.
 *      
 *      (E) vectorType: Macro for defining new vector types
 *      (F) contructorMethod: Macro for defining constructors for vectors.
 *      (G) appendMethod: Macro for defining methods to append vectors.
 *      (H) concatMethod: Macro for defining methods to concatenate vectors.
 *      (I) sliceMethod: Macro for defining methods to slice vectors.
 * 
 * 3. SAMPLE USAGE
 *    ============
 * 
 *      I have tried to think up ingenious ways to lucidly explain the usage
 *      of this header with general language, but I am sorry to say that I 
 *      cannot simplify it. It remains abstract, philosophical, and dry.
 * 
 *      Hence, I am using an example here. Suppose you want to create a vector
 *      of `double` variables (`double` is the name for C data type that stores
 *      sixty-four bit floating point numbers), this is how to go about it:
 * 
 *      SETTING UP THE STRUCT AND ITS METHODS
 *      -------------------------------------
 *  
 *      // Define the vector data type
 *      typedef vectorType() doubleVector; <─── Semicolon needed
 * 
 *      // Define the constructor
 *      doubleVector newDoubleVector() 
 *          constructorMethod(doubleVector, double)  <───────────────┐
 *                                                                   │
 *         macro expands into the body: no semicolon is required! ───┘
 * 
 *      // Likewise, define the append, concat, and slice methods
 * 
 *      doubleVector appendDoubleVector(doubleVector vec, double item)
 *          appendMethod(doubleVector, double, vec, item)  <───┐
 *                       ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^       │
 *      (*) Arguments to the macro: vector type, element type, ┘
 *          arguments of the function in the order they appear in the
 *          function's argument signature.
 *      
 *      doubleVector catDoubleVector(doubleVector vec1, doubleVector vec2)
 *          concatMethod(doubleVector, double, vec1, vec2)
 * 
 *      doubleVector sliceDoubleVector(doubleVector vec, int start, int stop)
 *          sliceMethod(doubleVector, double, vec, start, stop)
 * 
 *      Remember that the order in which the arguments appear in the function
 *      signature has to be correct, as per the order in this header file.
 * 
 *      INSTANTIATING VECTORS, ACCESSING AND ITERATING MEMBERS
 *      ------------------------------------------------------     
 *      
 *      Once the vector data type is defined, you can instantiate it with
 *      objects and fill them up with elements:
 * 
 *          doubleVector irrationals = newDoubleVector();
 *          irrationals = appendDoubleVector(irrationals, 2.78);
 *          irrationals = appendDoubleVector(irrationals, 3.14);
 *          ^^^^^^^
 *          // Observe here that the value returned by this method must
 *          // be assigned back to the variable, otherwise it is lost. 
 *      
 *      To access the members of the vector, use the `data` field:
 *          
 *          print("The value of pi is %lf \n", irrationals.data[1]);
 * 
 *      To access the size of the vector, use the `size` field:
 *          
 *          print("I know %d irrational numbers! \n", irrationals.size);
 * 
 *      To iterate over all the elements in the vector, you have three options:
 *        1. Use a regular `for` loop – this is a good option, but ugly:
 *        2. Use the `iterate` macro provided here
 *        3. Use the `enumerate` macro provided here if you also need the indices
 * 
 *          // With for loop
 *          int i;
 *          for (i = 0; i < irrationals.size; i++) { 
 *              printf("%lf is an irrational number!\n", irrationals.data[i]);
 *          }
 * 
 *          // With iterate
 *          int num;
 *          iterate (num, irrationals) {
 *              printf("%lf is an irrational number!\n", num);
 *          }                                            
 * 
 *          // With enumerate
 *          int i, num;
 *          enumerate(i, num, irrationals) {
 *              printf("%lf is the %dth irrational number!\n", i, num);
 *          }
 *          
 */     

#ifndef __C_VECTOR_H__
#define __C_VECTOR_H__

// -- REQUIREMENTS: We need STDLIB (memory allocations), and this `new` macro --

#include <stdlib.h>
#define _mallocate_dynamically(dtype, size) (dtype *)malloc(sizeof(dtype) * size)
// -- STRUCT: We define the macro for creating structs to store vectors -- 

#define vectorType(dtype) struct { \
    int size;     \
    int capacity; \
    dtype *data;  \
}

// -- FUNCTIONS: We define the four functions described in the README.md --

#define constructorMethod(vtype, dtype) { \
    vtype vec = {0, 1, NULL};  \
    vec.data = _mallocate_dynamically(dtype, 1);  \
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
    vec3.data = _mallocate_dynamically(dtype, vec3.capacity);\
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
    slice.data = _mallocate_dynamically(dtype, length); \
    for (i = start, j = 0; i < stop; i++, j++) {    \
        slice.data[j] = vec.data[i];                \
    }                                               \
                                                    \
    return slice;                                   \
}


// -- IDIOMS: We define `iterate` and `enumerate` as discussed --

#define iterate(item, vector) \
    for (  \
        __hidden_iterator = 0, item = vector.data[0];   \
        __hidden_iterator < vector.size;                \
        item = vector.data[                             \
            __hidden_iterator = __hidden_iterator + 1   \
        ]                                               \
    )

#define enumerate(i, v, vector) \
    for (                               \
        i = 0, v = vector.data[0];      \
        i < vector.size;                \
        v = vector.data[i = i + 1]      \
    )

int __hidden_iterator;

#endif