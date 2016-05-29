This is a thing I wrote to use when the regular angular.js profiler UI is not up to the task.
I had profiling data that took a couple of minutes to load and then crashed my browser when
I was trying to search through it. This one is a lot more basic, but does what I need and
is *blazingly* fast in comparison.

To build it:

    qmake
    make
    ./p6profiler-qt file.[json,html]

As usual, patches welcome. The C++ is likely pretty horrible, so patches with no functional
changes are also welcome :)
