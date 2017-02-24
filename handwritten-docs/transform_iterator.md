#transform_iterator<>

The iterator is object version of the `std::transform<>()`. It stores a functor and underlying iterator.

    *iterator = value;
    
In the above expression, `value` is not written directly to the underlying iterator, but first went through functor supplied by the user.

##Usage:

>Given `Functor functor` (which is `Callable`) and `Iterator iterator` (which is `OutputIterator`), iterator is created that behaves the same as underlying iterator, except it applies a functor to the incoming data and then passes the result into underlying iterator.

As can be seen from template declaration, `Functor` and `Iterator` types has to be supplied, but they can be deduced starting from C++17. There is also `transformer<>()` function, which should make creation of iterator easier to use.

To get better understanding of how things work, lets consider some parts of the code:

    template <typename U>
    proxy &operator=(U&& value)
    {
        *iterator = f(std::forward<U>(value));
        return *this;
    }
    
As can be seen from above, `Functor` must be a `Callable`, and have only one parameter. For the call site, `U` has to be implicitly convertible to functor's input parameter. Also, the result of the functor must be valid for expression `*iterator = result`, e.g. implicitly convertible to needed type.

    class proxy
    {
        Iterator &iterator;
        Functor &f;
        
The `proxy` class stores both `iterator` and `functor` by reference, so that no copying of the functor will happen when it is used as a result of dereference:

    proxy operator*()
    {
        return proxy(iterator, functor);
    }
    

##Examples:

```
#include "../src/transform_iterator.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

void convert_strings_to_ints()
{
    std::vector<std::string> v{"23", "25", "27"}; //just random numbers
    std::vector<int> output(v.size());

    auto string_to_int = [](const std::string& x)
    {
        return std::stoi(x);
    };

//    shino::transform_iterator<decltype(string_to_int),
//            std::vector<int>::iterator> conversion_iterator(string_to_int, output.begin());

    auto conversion_iterator = shino::transformer(string_to_int, output.begin());
    std::copy(v.begin(), v.end(), conversion_iterator);

    std::cout << "Output after converting v to vector of ints\n";

    for (const auto& element: output)
    {
        std::cout << element << '\n';
    }


}

int main()
{
    convert_strings_to_ints();
}
```