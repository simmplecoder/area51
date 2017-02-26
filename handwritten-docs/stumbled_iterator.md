#shino::stumbled_iterator

The iterator yields the same value on every dereferencing, except when it reaches it's 
limit.

##Specification:

>Given `T value` (which conforms CopyConstructible) and `std::size_t copy_count`, 
constructs an iterator that yields the same value on dereferencing `copy_count` times.
Default constructor creates end iterator, which is used in standard algorithms,
for example `std::copy<>()`.

##Usage:

The iterator should be used when range assigning is needed. It can be easily 
used with standard algorithms. It is advised  to give meaningful names to those 
iterators, since the intent might be deceptive. 

##Examples:

    std::vector<int> v(copy_count);
    shino::stumbled_iterator<int> first(num, copy_count);

    std::copy(first, shino::stumbled_iterator<int>{}, v.begin());