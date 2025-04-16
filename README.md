# C Vectors

This repository contains definitions for macros in C, that allow users to create structures and functions for implementing the vector data structure that is used in C++.

## Introduction

### Macros in C

In the C programming language, the programmer can write _macros_, which are code templates that have a name. Once the template has been written, it can be inserted anywhere in the C code using the name of the macro.

Basically, any place in the C code where the macro name is used, the macro name is substituted by the template code. The GNU C Compiler manual has an excellent 
[instruction page](https://gcc.gnu.org/onlinedocs/cpp/Macros.html) on the topic of
macros. The links below the brief explanation expand into discursive pages with 
simple examples and copious technical explanation.

In particular, in this work we are using _Function-like macros_, which are macros
that accept arguments and modify the template based on the arguments they receive.

### Vectors

While arrays in C provide a great way to store multiple variables in the RAM such that they can be tagged by their index – their position in the array – they have a common problem. Suppose we do not know how many elements we need to store – may be as small as three and may be as many as a million – how large should our arrays be?

We might think of dynamically allocating an array and making it the size of our data type.
