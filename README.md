# Demos
## cpp/ C++ language features
* cpp_rvo.cpp - demo of return-value-optimization
* destruct-parent.cpp - parent and field destructors are called on exception thrown from within the  constructor
* except-wrap.cpp - exception-safe wrapper for I/O functions
* atomic-unsigned-overflow.cpp - unsigned integer overflow is not UB even in atomics
* lifetime.cpp - demo of various (unsorted) aspects of c++ object lifetime
* boost-log-extra-obj.cpp - boost log does not create extra objects when not necessary
* no-alignment.cpp - g++/clang++ intrinsics do not align on x86
* no-destruct.cpp - g++/clang++ do not unwind stack if no matching handler is found for exception
* 5.3.5-5 - UB on incomplete destruction
## golang/ GO language features
* slice-modify-underlying.co -  Appending to a slice modifies underlying array
## java/ Java language features
* CalendarEquality.java - calendar equality includes milliseconds
* TestReordering.jaba - demo of operation reordering without sync
## python/ Python language features
* partial-format.py - you can format string partially
## unix/ UNIX features
* gettimeofday.c - gettimeofday() granylarity and non-monotonicity
* printf-twice.c - stdout buffer flush after fork
* sigbus.c - generate SIGBUS which might be not easy
* fork.c - Copy-on-write on fork() of MAP_PRIVATE regions
* throw-in-signal.cpp - do no throw from within a signal handler
