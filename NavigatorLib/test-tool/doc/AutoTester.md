# AutoTester Mini-User Guide

__AutoTester__ (formerly Unit) is the full-auto version of _Tester_. It runs a bunch of tests stored as subdirectories of
the test directory. It then checks if max delta (see _Tester_) is smaller than the specified 
delta allowance. If so, the test is regarded as _passed_. 

Note: _AutoTester_ requires the library _CppUnit_ to build.

## Usage:

autotester <test\_directory> <delta\_allowance>

## Example:

autotester ../tools/TESTS  0.05

_AutoTester_ scans all subdirectories of _<test\_directory>_ (except for those which start with '.') and tries
to run _Tester_ engine in each subdirectory. For the input file format: see _Tester_. The only result
is the max delta which is written as file _autotester\_maxdelta.txt_ in each respective subdirectory.
The test is passed if the max delta is smaller than <delta\_allowance>.

The test results are printed in the _CppUnit_ format. If run within TeamCity (environment variable 
_TEAMCITY\_PROJECT\_NAME_ is set), the output will be in the TeamCity-compatible format.

## Test examples

See the directory _TESTS_ in the docs. The identical tests _GOBLIN_, _ORC_ have max delta about 
0.03, while _OGRE_ has max deta about 0.08 (I corrupted the route file a bit on purpose). Have fun!
