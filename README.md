# C Vectors

This repository contains the file __cvector.h__, which has definitions for macros in C, that allow users to create structures and functions for implementing the vector data structure that is used in C++.

## Introduction

### Macros in C

In the C programming language, the programmer can write _macros_, which are code templates that have a name. Once the template has been written, it can be inserted anywhere in the C code using the name of the macro.

Any place in the C code where the macro name is used, the macro name is substituted by the template code. The GNU C Compiler manual has an excellent [instruction page](https://gcc.gnu.org/onlinedocs/cpp/Macros.html) on the topic of macros. The links below the brief explanation in that page expand into discursive pages with simple examples and detailed technical explanation.

In particular, in this work we are using _Function-like macros_, which are macros
that accept arguments and modify the template based on the arguments they receive.

### Vectors

While arrays in C provide a great way to store multiple variables in the RAM such that they can be tagged by their index – their position in the array – they have a common problem. Suppose we do not know how many elements we need to store – may be as small as three and may be as many as a million – how large should our arrays be?

We might think of dynamically allocating an array and making it the size of our data. But what if we don't know how many data items there are going to be? We then have two choices: to use a linked list and to keep pushing to it one element at a time, or to use the `realloc` method to resize the array every once in a while.

#### The Problem with Linked Lists

Using the Linked List seems like a simple approach. We define a node struct that stores one item and a pointer to the next node struct. The nodes are dynamically allocated. We keep building new nodes as more and more items are read it. In theory, the problem is solved perfectly.

In practice, two problems arise. The first, of course, is efficiency: every node contains a pointer, which requires space in RAM but does not contribute to the storage of items we set out to store. This is a general problem with non-contiguous memory allocation.

The second problem is more complicated. It has to do with the order-complexity of operations. For instance, to get to the 100th member of an array, you would simply need to calculate the memory location of the 100th member (location of the first member plus 99 times the size of each member) and then read the data at that location. But in a linked list, you will need to use the pointers to _traverse_ the entire linked list from the first item to the hundredth. This sort of traversal has to be done each time.

For a linked list with ten million items, a couple of lookups can take forever!

#### The Challenge of Reallocate

Suppose you have an `int` pointer (named `ptr`) pointing to a dynamically allocated array of length five. Suppose we want to increase the size of this array to six, so that we can store another item in it. When we invoke the reallocate function, it works something like this: 

```c
ptr = (int *) realloc( ptr, sizeof(int) * 6 );
```

When this line is executed, it actually does several things. 
  1. A new memory store of six-integer capacity is allocated in the RAM. 
  2. All the first five integers are copied from the original location, the one with the five-integer capacity. 
  3. The address of the six-integer array is fed back into the pointer.

Here are two problems with this sequence: the first step is always slow, since the operating system has to be politely asked to lease the RAM, so we want to run run this reallocation request as sparsely as we can; and the second step will take a different amount of time depending on how much memory we are copying.

It is all fine and dandy to copy five integers, but what if we have a million integers and we have to read in the next? We will bog the RAM down in the task of copying a million integers.

Now let us say we have a hundred more integers to go after we have reached a million? For each of them, we will need to copy a million integers! Essentially, we shall have run more than a hundred million integer copying operations, which takes a perceptible fraction of a second to run even when the processor is giving the program its complete resources. Typically, the processor has to share resources among running programs, so a program that copies a hundred million integers will take several seconds to run. Several seconds to read in a hundred numbers.

If these numbers are being read from a while, then we can do the math and notice that a simple file with two megabytes will take forever to be read, and quite possibly crash the computer.

#### The Solution: Vectors

Vectors are a data structure, the way linked lists are. But unlike linked lists, vectors store memory contiguously, using dynamically allocated arrays. What they also do is reallocate those arrays _sparingly_.

The strategy is that a vector has three properties: size, __capacity__, and data. The size is an integer which keeps note of how many items are currently stored. The data field is just a pointer which points to the dynamically allocated array. The trick has to do with the capacity.

The capacity stores the length of the array, and is _different from the size_. When the vector is initialized, the size is zero, the capacity is __one__, and the data field is initialized to an array of just one element. 

As new items are read in, we first check if the size of the vector is equal to the capacity. If not, we increment the size variable, write the new item to the location (size - 1), and that's it. If the size is equal to (or somehow exceeds) the capacity? We _double the capacity_, and then we reallocate the array.

This means that the capacity grows exponentially. This means, the number of `realloc` calls is a logarithmic function of the number of items we need to read in. For reading in two million items, we need somewhere in the ball-park of twenty-one `realloc` calls only!

### C++ Vectors

In the C++ programming language, which extends the functionality of C by introducing
classes and objects, there is a standard library named __vector__. This library introduces a template named `vector`, which can be used to create objects of vector
classes. Each vector class is made by providing the template with a data type. For
instance, an integer vector class is created from this template using `vector <int>`.

To create a new vector of integers named `vec`, add in elements 2, 3, and 5 into it, this is the code C++ would use:

```cpp
vector <int> vec;
vec.push_back(2);
vec.push_back(3);
vec.push_back(5);
```

#### Porting Vectors to C: Challenges

We can build a struct to store such a vector of integers in C. It will take some effort, but not too much. The issue is, we will have to build it again if we want a vector of some other data type. We will need to write this data structure (and its associated functions) every time we need to build vectors for a data type.

This is a problem because data types are a dime a dozen in C. Every struct is a new data type. Are we going to write an entire header file to define vectors for every single struct?

We can, of course, speed up this process with boiler-plate. But boiler-plate is the death of good code. No, we need something more elegant and true to the principles of good programming and the C language.

#### Porting Vectors to C: Approach

Let us use macros!

Macros allow us to define many lines of C code using a single token, which can then expand to cover an entire boiler-plate. This is the method employed here. 

We identify the key structs, functions, and idioms we need to define the vector for each data type, and we wrap each of them up inside a macro. Let's begin by listing those structs, functions, and idioms.

## Components

### Structures

We will need a single structure to contain the three fields of a vector: its `size`, its `capacity`, and its `data` pointer. This is a struct, and one for each vector data structure (that is, one for each data type).

Of these, the size and capacity are always integers (or `long`). The `data` is a pointer to the specific data type that we want to build a vector for.

### Functions

We need four functions:
  1. A constructor, to initialize vector objects.
  2. An append function, to add new items to vectors.
  3. A concatenate function, to merge two vectors into one.
  4. A slice function, to copy a section of a vector and make another vector

### Idioms

Iterating a vector can be done using a loop, but we prefer using certain idioms. Python's `range` and the iterable for loop in C++ have introduced them, and the clarity they provide is worth the additional complexity of adding these two idioms.

Accordingly, we will have the following two idioms: `iterate` and `enumerate`.

#### Iterate

This allows us to iterate over the entire length of the vector, using a for loop. But the idiom hides the ugliness of the underlying for loop. Instead, it does the heavy-lifting for us and gives us just the individual member elements, one at a time.

```c
iterate(fp, open_files) {
    fclose(fp);
}
```

Here, we get to iterate over a vector of file pointers named `open_files`, and each one is presented to us as `fp`. As the modern iteration idiom goes, we do not need the index position of the file pointers and it is therefore hidden from us. Many programmers today find it a lot less distracting to have fewer variables.

#### Enumerate

Sometimes we want to have the index position of the elements as well. This idiom is for those occassions. For instance, suppose we have a vector named `values` and we want to find the _argmax_ of the vector: the index of its largest element.

Clearly, since we are looking for an index, we will need to know the indices of the elements we are working with. Hence `enumerate` iterates over the elements of `values`, and for each element, the element itself is presented in a variable `v` while its position is presented in the variable `i`.

```c
enumerate(i, v, values) {
  if (v > tentative_maximum) {
    tentative_maximum = v;
    tentative_argmax = i;
  }
}
```

## Philosphy and Design Decisions

These macros will read in arguments for both data types, and the names of variables that need to be used as arguments in the functions etc. I have decided the ordering of the arguments in the macros to be like I describe here.

The arguments for any macro are of three kinds:
  - Vector data type
  - Element data type
  - Argument name

For instance, consider a macro for defining the functions that append new elements to a vector. This function will need to know (1) the data type of the vector, the data type of the elements of the vector, and the variable name used for the item being appended to the vector, which is normally an argument to the append function.

 If the macro expands into the body of a function, we will need to know what names those arguments were assigned in the name. The user must supply all of these. 
 
 The ordering of the arguments in the macros must be:
  1. Name of the vector data type.
  2. Name of the element data type.
  3. Names of the arguments to the functions, in order

  