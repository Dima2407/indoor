Navigator Library
======
in progress...

authors: By Oleksiy Grechnyev & Ivan Kuvaldin

This is a remake/refactoring of `tracking_lib`.

* `src` : The library source code. Contains source files and private headers.
* `include` : The only folder to be included for user
* `lib` : This directory is for external libraries, e.g. Eigen
* `unittest` : CppUnit-based unit tests for the library
* `fun` : A sample executable

### Doxygen
`Doxyfile` is the *Doxygen* configuration file. It requires `DOT\_PATH` and
`PLANTUML\_JAR\_PATH` if you want to render UML diagrams.