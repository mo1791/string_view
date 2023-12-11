==========================================\
## C++ String_view

non-owning view of a contiguous character sequence.

## Purpose
string_view allows you to create a constant, non-owning view of a contiguous character sequence.
You can manipulate that view and pass it around without the need to copy the referenced data.

## Test
```c++
#include <string_view.hxx>


auto main() -> int
{

	ztd::string_view _greet("Hello World!");

    // _greet[5] = 'O'; # assignment of read-only location
    
	std::cout << _greet;
	std::cout << "size -> " << _greet.size() << std::endl;
	
    std::boolalpha(std::cout);
	std::cout << "is empty ? " << _greet.empty() << std::endl;
}
```
