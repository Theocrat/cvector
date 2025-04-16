/** SAMPLE - DOUBLE
 * 
 * This file contains a simple application for testing the `cvector.h` header file.
 * It works as a sample file for the capabilities of this header. Here we define
 * a vector type for `double` (64-bit floating point datatype).
 * 
 * These lines are from the example provided in the docstring of the header itself.
 * 
 * This file can be compiled using a standard GNU C Compiler, or the Clang compiler
 * provided by Apple in the XCode repository. If there are issues with compiling or
 * running this file, kindly reach out to me by reporting the issues at this Github
 * repository: https://github.com/Theocrat/cvector
 * 
 * PS: You can also find the `cvector.h` header file in that repository.
 */

#include <stdio.h>
#include "cvector.h"

// Define the double vector data type
typedef vectorType(double) doubleVector;

// Define the constructor "method" (technically a global function)
doubleVector newDoubleVector() constructorMethod(doubleVector, double)

// Define the append method
doubleVector appendDoubleVector(doubleVector vec, double item)
    appendMethod(doubleVector, double, vec, item)

// Define the concatenate method
doubleVector catDoubleVector(doubleVector vec1, doubleVector vec2)
    concatMethod(doubleVector, double, vec1, vec2)

// Define the slice method
doubleVector sliceDoubleVector(doubleVector vec, int start, int stop)
    sliceMethod(doubleVector, double, vec, start, stop)

int main() {
    // Initializing the vector
    doubleVector irrationals = newDoubleVector();

    // Filling it up with two elements
    irrationals = appendDoubleVector(irrationals, 2.78);
    irrationals = appendDoubleVector(irrationals, 3.14);

    // Printing the second element
    printf("The value of pi is %lf \n", irrationals.data[1]);

    // Printing the size
    printf("I know %d irrational numbers! \n", irrationals.size);

    // Iterating
    double num;
    int pos;

    // Iterating with for loop
    puts("");
    for (pos = 0; pos < irrationals.size; pos++) {
        printf("%lf is an irrational number!\n", irrationals.data[pos]);
    }

    // Iterating without indices
    puts("");
    iterate (num, irrationals) {
        printf("%lf is an irrational number!\n", num);
    }  

    // Iterating with indices
    puts("");
    enumerate (pos, num, irrationals) {
        printf("%lf is the %dth irrational number!\n", num, pos);
    }

    puts("");
    return 0;
}