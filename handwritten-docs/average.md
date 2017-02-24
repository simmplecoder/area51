#shino::average<>()

Very simple algorithm that computes average of the elements denoted by iterator range `[first, last)`. It relies on `std::distance<>()` and `std::accumulate<>()`, so the code is very simple.

##Usage:

The usage is the same as for `accumulate<>()`, except the result is divided by result of the `std::distance<>()`. It might cause problems when average of integers is wanted, so to prevent narrowing due to `int/int`, it is recommended to pass initial value of type double, for example:
 
    shino::average(v.begin(), v.end(), 0.0);