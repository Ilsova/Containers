# Containers

The goal of this project is to develop a C++ library of template container classes adhering to the standards and guidelines of the Standard Template Library (STL). This project is a part of School21 curriculum. 

## Specifications

- **Template Classes**: All classes are implemented as template classes.
- **Iterators**: Iterators are used throughout the implementation.
- **Namespace**: All classes are implemented within the `s21` namespace.
- **Unit Testing**: Full coverage of container classes methods is provided with unit tests using the GTest library.
- **STL Logic**: The logic of the Standard Template Library (STL) is followed in terms of checks and behavior in abnormal situations.

## Implementation of s21_containers.h Library

The `s21_containers.h` library includes classes for main containers: `array`,`list`, `map`, `queue`, `set`, `stack`, and `vector`. The library is designed as a header file `s21_containers.h`, which includes separate header files with implementations of each container (`s21_list.h`, `s21_map.h`, etc.). The implementation adheres to the STL logic while providing flexibility in choosing the final implementations.

### Features
- Header-only library for easy inclusion in projects.
- Follows STL logic with custom implementations.
- Makefile provided for testing the library.

## Project Contributors

|Contributor|Containers|
|---	|---	|
|queeju	|Map, Set, Vector	|
|[ilsova](https://github.com/Ilsova)	|Array, Lits, Stack, Queue	|

## Usage

To use the Containers library in your project:
1. Clone the repository to your local machine.
2. Include the necessary header files in your project.
3. Make sure to set up the GCC compiler environment.
4. Use the provided Makefile to test the library and ensure proper functionality.
5. Enjoy the flexibility and power of the Containers library for your C++ projects.


