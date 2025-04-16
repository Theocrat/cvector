/** SAMPLE - STRINGS
 * 
 * This file contains a simple application for testing the `cvector.h` header file.
 * It works as a sample file for the capabilities of this header. Here we define
 * a vector type for `char` (character datatype, the signed byte).
 * 
 * An additional `toCharArray` method has been defined to convert the vectors into
 * C strings for printing. We use a buffer to hold the resulting string so that 
 * we can responsibly free it (of course!), and the method `to_str` converts a
 * string into a vector of `char` elements. 
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

// Here we build the `str` vector data type as discussed:

typedef vectorType(char) str;
str new_str() constructorMethod(str, char);
str add_str(str s, char c) appendMethod(str, char, s, c)
str cat_str(str s1, str s2) concatMethod(str, char, s1, s2)
str slice_str(str s, int start, int stop) sliceMethod(str, char, s, start, stop)

// Convenient methods for conversion to and from C-strings

char *toCharArray(str);
str to_str(char *);


// Main function (entry point)

int main() {
    str S1 = to_str("Hello ");
    str S2 = to_str("World!");

    str S3 = cat_str(S1, S2);
    str S4 = slice_str(S3, 3, 7);

    char *buffer;

    printf("The str object is: S1 = \"%s\"\n", buffer = toCharArray(S1));
    free(buffer);

    printf("The str object is: S2 = \"%s\"\n", buffer = toCharArray(S2));
    free(buffer);

    printf("The cat object is: S3 = \"%s\"\n", buffer = toCharArray(S3));
    free(buffer);

    printf("The slice is: S4 = \"%s\"\n\n", buffer = toCharArray(S4));
    free(buffer);

    puts("");
    return 0;
}

// Definitions of the functions


char *toCharArray(str s) {
    char c;
    char *buffer = (char *) malloc (s.size + 1);
    char *ptr = buffer;
    
    iterate(c, s) {
        *ptr = c;
        ptr++;
    }
    *ptr = '\0';

    return buffer;
}

str to_str(char *ptr) {
    str s = new_str();
    
    while (*ptr > 0) {
        s = add_str(s, *ptr);
        ptr++;
    }

    return s;
}