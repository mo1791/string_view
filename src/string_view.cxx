#include <string_view.hxx>


/**
* Explicitly instantiate only the classes
* I want to support <char> , <wchar_t>, <char16_t> and <char32_t> with the same code.
****/
template class basic_string_view<char>;
template class basic_string_view<wchar_t>;
template class basic_string_view<char16_t>;
template class basic_string_view<char32_t>;


template auto operator<<(std::basic_ostream<char>&, const string_view&)
    -> std::basic_ostream<char>&;

template auto operator<<(std::basic_ostream<char>&, const wstring_view&)
    -> std::basic_ostream<wchar_t>&;

template auto operator<<(std::basic_ostream<char>&,
                                const u16string_view&)
    -> std::basic_ostream<char>&;

template auto operator<<(std::basic_ostream<char>&,
                                const u32string_view&)
    -> std::basic_ostream<char>&;