#ifndef STRING_VIEW_HXX
#define STRING_VIEW_HXX

#include <algorithm>
#include <cstddef>
#include <ranges>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <string>


////////////////////////////////////////////////////////////////////////////
/// @brief A wrapper around non-owned strings.
/// \ingroup core
////////////////////////////////////////////////////////////////////////////
template <typename CharT, typename Traits = std::char_traits<CharT>>
    class basic_string_view final
{
//  ------------------------------------------------------------------------
    // Public Member Types
//  ------------------------------------------------------------------------
public:
    using char_type               =  CharT;
    using traits_type             =  Traits;
    using size_type               =  std::size_t;
    using value_type              =  CharT;
    using reference               =  value_type &;
    using const_reference         =  const value_type &;
    using pointer                 =  value_type *;
    using const_pointer           =  const value_type *;
    using iterator                =  const CharT *;
    using const_iterator          =  const CharT *;
    using reverse_iterator        =  std::reverse_iterator<iterator>;
    using const_reverse_iterator  =  std::reverse_iterator<const_iterator>;

//  ------------------------------------------------------------------------
    // Public Members
//  ------------------------------------------------------------------------
public:
    static constexpr size_type npos = size_type(-1l);

//  ------------------------------------------------------------------------
    // Constructors
//  ------------------------------------------------------------------------
public:
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Default constructs a basic_string_view without any content
    basic_string_view() noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Constructs a basic_string_view by copying another one
    ///
    /// @param other the string view being copied
    basic_string_view(const basic_string_view &other) noexcept = default;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Constructs a basic_string_view by moving anothe rone
    ///
    /// @param other the string view being moved
    basic_string_view(basic_string_view &&other) noexcept = default;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Constructs a basic_string_view from a std::basic_string
    ///
    /// @param str the string to view
    template <typename Allocator>
    basic_string_view(const std::basic_string<CharT, Traits, Allocator> &) noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Constructs a basic_string_view from an ansi-string
    ///
    /// @param str the string to view
    basic_string_view(const_pointer str) noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Constructs a basic_string_view from an ansi string of a given size
    ///
    /// @param str the string to view
    /// @param count the size of the string
    basic_string_view(const_pointer str, size_type count) noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------


//  ------------------------------------------------------------------------
    // Assignment
//  ------------------------------------------------------------------------
public:
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Assigns a basic_string_view from an ansi-string
    ///
    /// @param view the string to view
    /// @return reference to \c (*this)
    basic_string_view &operator=(const basic_string_view &view) = default;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------


//  ------------------------------------------------------------------------
    // Capacity
//  ------------------------------------------------------------------------
public:
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Returns the length of the string, in terms of bytes
    ///
    /// @return the length of the string, in terms of bytes
    size_type size() const noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @copydoc basic_string_view::size
    size_type length() const noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief The largest possible number of char-like objects that can be
    ///        referred to by a basic_string_view.
    /// @return Maximum number of characters
    size_type max_size() const noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Returns whether the basic_string_view is empty (i.e. whether its length is 0).
    ///
    /// @return whether the basic_string_view is empty
    bool empty() const noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
    // Element Access
//  ------------------------------------------------------------------------
public:
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Gets the ansi-string of the current basic_string_view
    ///
    /// @return the ansi-string pointer constexpr
    const_pointer c_str() const noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Gets the data of the current basic_string_view
    ///
    /// \note This is an alias of #c_str
    ///
    /// @return the data this basic_string_view contains constexpr
    const_pointer data() const noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Accesses the element at index \p pos
    ///
    /// @param pos the index to access
    /// @return const reference to the character
    const_reference operator[](size_type pos) const noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Accesses the element at index \p pos
    ///
    /// @param pos the index to access
    /// @return const reference to the character
    const_reference at(size_type pos) const;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Access the first character of the string
    ///
    /// \note Undefined behavior if basic_string_view is empty
    ///
    /// @return reference to the first character of the string
    const_reference front() const noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief References the last character of the string
    ///
    /// \note Undefined behavior if basic_string_view is empty
    ///
    /// @return reference to the last character of the string
    const_reference back() const noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
    // Modifiers
//  ------------------------------------------------------------------------
public:
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Moves the start of the view forward by n characters.
    ///
    /// The behavior is undefined if n > size().
    ///
    /// @param n number of characters to remove from the start of the view
    void remove_prefix(size_type n) noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Moves the end of the view back by n characters.
    ///
    /// The behavior is undefined if n > size().
    ///
    /// @param n number of characters to remove from the end of the view
    void remove_suffix(size_type n) noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Exchanges the view with that of v.
    ///
    /// @param v view to swap with
    void swap(basic_string_view &v) noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
    // Conversions
//  ------------------------------------------------------------------------
public:
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Creates a basic_string with a copy of the content of the current view.
    ///
    /// @tparam Allocator type used to allocate internal storage
    /// @param a Allocator instance to use for allocating the new string
    ///
    /// @return A basic_string containing a copy of the characters of the current view.
    template <class Allocator = std::allocator<CharT>>
    std::basic_string<CharT, Traits, Allocator> to_string(const Allocator &a = Allocator()) const;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @copydoc basic_string_view::to_string
    template <class Allocator>
    explicit operator std::basic_string<CharT, Traits, Allocator>() const;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
    // Operations
//  ------------------------------------------------------------------------
public:
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Copies the substring [pos, pos + rcount) to the character string pointed
    ///        to by dest, where rcount is the smaller of count and size() - pos.
    ///
    /// @param dest pointer to the destination character string
    /// @param count requested substring length
    /// @param pos position of the first character
    size_type copy(pointer dest, size_type count = npos, size_type pos = 0ul) const;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Returns a substring of this viewed string
    ///
    /// @param pos the position of the first character in the substring
    /// @param len the length of the substring
    /// @return the created substring
    basic_string_view substr(size_t pos = 0ul, size_t len = npos) const;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Compares two character sequences
    ///
    /// @param v view to compare
    /// @return negative value if this view is less than the other character
    ///         sequence, zero if the both character sequences are equal,
    ///         positive value if this view is greater than the other character
    ///         sequence.
    int compare(basic_string_view v) const noexcept;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Compares two character sequences
    ///
    /// @param pos   position of the first character in this view to compare
    /// @param count number of characters of this view to compare
    /// @param v     view to compare
    /// @return negative value if this view is less than the other character
    ///         sequence, zero if the both character sequences are equal,
    ///         positive value if this view is greater than the other character
    ///         sequence.
    int compare(size_type pos, size_type count, basic_string_view v) const;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Compares two character sequences
    ///
    /// @param pos1   position of the first character in this view to compare
    /// @param count1 number of characters of this view to compare
    /// @param v      view to compare
    /// @param pos2   position of the second character in this view to compare
    /// @param count2 number of characters of the given view to compare
    /// @return negative value if this view is less than the other character
    ///         sequence, zero if the both character sequences are equal,
    ///         positive value if this view is greater than the other character
    ///         sequence.
    int compare(size_type pos1, size_type count1, basic_string_view v, size_type pos2, size_type count2) const;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Compares two character sequences
    ///
    /// @param s pointer to the character string to compare to
    /// @return negative value if this view is less than the other character
    ///         sequence, zero if the both character sequences are equal,
    ///         positive value if this view is greater than the other character
    ///         sequence.
    int compare(const_pointer s) const;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Compares two character sequences
    ///
    /// @param pos   position of the first character in this view to compare
    /// @param count number of characters of this view to compare
    /// @param s pointer to the character string to compare to
    /// @return negative value if this view is less than the other character
    ///         sequence, zero if the both character sequences are equal,
    ///         positive value if this view is greater than the other character
    ///         sequence.
    int compare(size_type pos, size_type count, const_pointer s) const;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// @brief Compares two character sequences
    ///
    /// @param pos   position of the first character in this view to compare
    /// @param count1 number of characters of this view to compare
    /// @param s pointer to the character string to compare to
    /// @param count2 number of characters of the given view to compare
    /// @return negative value if this view is less than the other character
    ///         sequence, zero if the both character sequences are equal,
    ///         positive value if this view is greater than the other character
    ///         sequence.
    int compare(size_type pos, size_type count1, const_pointer s, size_type count2) const;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    size_type find(basic_string_view v, size_type pos = 0ul) const;
    size_type find(char_type c, size_type pos = 0ul) const;
    size_type find(const_pointer s, size_type pos, size_type count) const;
    size_type find(const_pointer s, size_type pos = 0ul) const;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    size_type rfind(basic_string_view v, size_type pos = npos) const;
    size_type rfind(char_type c, size_type pos = npos) const;
    size_type rfind(const_pointer s, size_type pos, size_type count) const;
    size_type rfind(const_pointer s, size_type pos = npos) const;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    size_type find_first_of(basic_string_view v, size_type pos = 0ul) const;
    size_type find_first_of(char_type c, size_type pos = 0ul) const;
    size_type find_first_of(const_pointer s, size_type pos, size_type count) const;
    size_type find_first_of(const_pointer s, size_type pos = 0ul) const;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    size_type find_last_of(basic_string_view v, size_type pos = npos) const;
    size_type find_last_of(char_type c, size_type pos = npos) const;
    size_type find_last_of(const_pointer s, size_type pos, size_type count) const;
    size_type find_last_of(const_pointer s, size_type pos = npos) const;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    size_type find_first_not_of(basic_string_view v, size_type pos = 0ul) const;
    size_type find_first_not_of(char_type c, size_type pos = 0ul) const;
    size_type find_first_not_of(const_pointer s, size_type pos, size_type count) const;
    size_type find_first_not_of(const_pointer s, size_type pos = 0ul) const;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    size_type find_last_not_of(basic_string_view v, size_type pos = npos) const;
    size_type find_last_not_of(char_type c, size_type pos = npos) const;
    size_type find_last_not_of(const_pointer s, size_type pos, size_type count) const;
    size_type find_last_not_of(const_pointer s, size_type pos = npos) const;
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
    // Iterators
//  ------------------------------------------------------------------------
public:
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// \{
    /// @brief Retrieves the begin iterator for this basic_string_view
    ///
    /// @return the begin iterator
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    /// \}
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// \{
    /// @brief Retrieves the end iterator for this basic_string_view
    ///
    /// @return the end iterator
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    /// \}
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// \{
    /// @brief Retrieves the reverse begin iterator for this basic_string_view
    ///
    /// @return the reverse begin iterator
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;
    /// \}
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
    /// \{
    /// @brief Retrieves the reverse end iterator for this basic_string_view
    ///
    /// @return the reverse end iterator
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;
    /// \}
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  ------------------------------------------------------------------------
    // Private Member
//  ------------------------------------------------------------------------
private:
    const_pointer m_str; ///< The internal string type
    size_type m_size;       ///< The size of this string

    /// @brief Checks whether \p c is one of the characters in \p str
    ///
    /// @param c the character to check
    /// @param str the characters to compare against
    /// @return true if \p c is one of the characters in \p str
    static bool is_one_of(CharT c, basic_string_view str);
};



template <typename CharT, typename Traits>
const typename basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::npos;


//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    template <typename Allocator>
    basic_string_view<CharT, Traits>::basic_string_view(const std::basic_string<CharT, Traits, Allocator> &_str) noexcept
        : m_str(_str.c_str()), m_size(_str.size())
    {
    }


//  --------------------------------------------------------------------------
// Conversions
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    template <class Allocator>
    std::basic_string<CharT, Traits, Allocator> basic_string_view<CharT, Traits>::to_string(const Allocator &_a) const
    {
        return std::basic_string<CharT, Traits, Allocator>(m_str, m_size, _a);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    template <class Allocator>
    basic_string_view<CharT, Traits>::operator std::basic_string<CharT, Traits, Allocator>() const
    {
        return std::basic_string<CharT, Traits, Allocator>(m_str, m_size);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------


//  --------------------------------------------------------------------------
// Public Functions
//  --------------------------------------------------------------------------

    /// @brief Overload for ostream output of basic_string_view
    ///
    /// @param o   The output stream to print to
    /// @param str the string to print
    /// @return reference to the output stream
    template <typename CharT, typename Traits>
    std::basic_ostream<CharT, Traits> &operator<<(std::basic_ostream<CharT, Traits> & _output,
                                                const basic_string_view<CharT, Traits> & _str)
    {
        std::ranges::for_each(_str, [&](CharT chr) { _output << chr; });
        return _output << "\xa";
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    void swap(basic_string_view<CharT, Traits> &lhs, basic_string_view<CharT, Traits> &rhs) noexcept
    {
        lhs.swap(rhs);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------



//  --------------------------------------------------------------------------
// Comparison Functions
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator==(const basic_string_view<CharT, Traits> & _lhs, const basic_string_view<CharT, Traits> & _rhs) noexcept
    {
        return ( _lhs.compare(_rhs) == 0ul );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator==(basic_string_view<CharT, Traits> const & _lhs, const CharT *_rhs) noexcept
    {
        return ( _lhs == basic_string_view<CharT, Traits>(_rhs) );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator==(const CharT *_lhs, const basic_string_view<CharT, Traits> & _rhs) noexcept
    {
        return ( basic_string_view<CharT, Traits>(_lhs) == _rhs );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits, typename Allocator>
    inline bool operator==(const std::basic_string<CharT, Traits, Allocator> &_lhs, const basic_string_view<CharT, Traits> &_rhs)
    {
        return ( basic_string_view<CharT, Traits>(_lhs) == _rhs );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits, typename Allocator>
    inline bool operator==(const basic_string_view<CharT, Traits> &_lhs, const std::basic_string<CharT, Traits, Allocator> &_rhs)
    {
        return ( _lhs == basic_string_view<CharT, Traits>(_rhs) );
    }

//  --------------------------------------------------------------------------
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator!=(const basic_string_view<CharT, Traits> &_lhs, const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return ( _lhs.compare(_rhs) != 0ul );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator!=(const basic_string_view<CharT, Traits> &_lhs, const CharT *_rhs) noexcept
    {
        return ( _lhs != basic_string_view<CharT, Traits>(_rhs) );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator!=(const CharT *_lhs, const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return ( basic_string_view<CharT, Traits>(_lhs) != _rhs );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits, typename Allocator>
    inline bool operator!=(const std::basic_string<CharT, Traits, Allocator> &_lhs, const basic_string_view<CharT, Traits> &_rhs)
    {
        return ( basic_string_view<CharT, Traits>(_lhs) != _rhs );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits, typename Allocator>
    inline bool operator!=(const basic_string_view<CharT, Traits> &_lhs, const std::basic_string<CharT, Traits, Allocator> &_rhs)
    {
        return ( _lhs != basic_string_view<CharT, Traits>(_rhs) );
    }

//  --------------------------------------------------------------------------
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator<(const basic_string_view<CharT, Traits> &_lhs, const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return ( _lhs.compare(_rhs) < 0ul );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator<(const basic_string_view<CharT, Traits> &_lhs, const CharT *_rhs) noexcept
    {
        return ( _lhs < basic_string_view<CharT, Traits>(_rhs) );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator<(const CharT *_lhs, const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return ( basic_string_view<CharT, Traits>(_lhs) < _rhs );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits, typename Allocator>
    inline bool operator<(const std::basic_string<CharT, Traits, Allocator> &_lhs, const basic_string_view<CharT, Traits> &_rhs)
    {
        return ( basic_string_view<CharT, Traits>(_lhs) < _rhs );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits, typename Allocator>
    inline bool operator<(const basic_string_view<CharT, Traits> &_lhs, const std::basic_string<CharT, Traits, Allocator> &_rhs)
    {
        return ( _lhs < basic_string_view<CharT, Traits>(_rhs) );
    }

//  --------------------------------------------------------------------------
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator>(const basic_string_view<CharT, Traits> &_lhs, const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return ( _lhs.compare(_rhs) > 0ul );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator>(const basic_string_view<CharT, Traits> &_lhs, const CharT *_rhs) noexcept
    {
        return ( _lhs > basic_string_view<CharT, Traits>(_rhs) );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator>(const CharT *_lhs, const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return ( basic_string_view<CharT, Traits>(_lhs) > _rhs );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits, typename Allocator>
    inline bool operator>(const std::basic_string<CharT, Traits, Allocator> &_lhs, const basic_string_view<CharT, Traits> &_rhs)
    {
        return ( basic_string_view<CharT, Traits>(_lhs) > _rhs );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits, typename Allocator>
    inline bool operator>(const basic_string_view<CharT, Traits> &_lhs, const std::basic_string<CharT, Traits, Allocator> &_rhs)
    {
        return ( _lhs > basic_string_view<CharT, Traits>(_rhs) );
    }

//  --------------------------------------------------------------------------
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator<=(const basic_string_view<CharT, Traits> &_lhs, const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return ( _lhs.compare(_rhs) <= 0ul );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator<=(const basic_string_view<CharT, Traits> &_lhs, const CharT *_rhs) noexcept
    {
        return ( _lhs <= basic_string_view<CharT, Traits>(_rhs) );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator<=(const CharT *_lhs, const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return ( basic_string_view<CharT, Traits>(_lhs) <= _rhs );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits, typename Allocator>
    inline bool operator<=(const std::basic_string<CharT, Traits, Allocator> &_lhs, const basic_string_view<CharT, Traits> &_rhs)
    {
        return ( basic_string_view<CharT, Traits>(_lhs) <= _rhs );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits, typename Allocator>
    inline bool operator<=(const basic_string_view<CharT, Traits> &_lhs, const std::basic_string<CharT, Traits, Allocator> &_rhs)
    {
        return ( _lhs <= basic_string_view<CharT, Traits>(_rhs) );
    }

//  --------------------------------------------------------------------------
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator>=(const basic_string_view<CharT, Traits> &_lhs, const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return ( _lhs.compare(_rhs) >= 0ul );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator>=(const basic_string_view<CharT, Traits> &_lhs, const CharT *_rhs) noexcept
    {
        return ( _lhs >= basic_string_view<CharT, Traits>(_rhs) );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    inline bool operator>=(const CharT *_lhs, const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return ( basic_string_view<CharT, Traits>(_lhs) >= _rhs );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits, typename Allocator>
    inline bool operator>=(const std::basic_string<CharT, Traits, Allocator> &_lhs, const basic_string_view<CharT, Traits> &_rhs)
    {
        return ( basic_string_view<CharT, Traits>(_lhs) >= _rhs );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits, typename Allocator>
    inline bool operator>=(const basic_string_view<CharT, Traits> &_lhs, const std::basic_string<CharT, Traits, Allocator> &_rhs)
    {
        return ( _lhs >= basic_string_view<CharT, Traits>(_rhs) );
    }
//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  --------------------------------------------------------------------------
// Type Aliases
//  --------------------------------------------------------------------------

using string_view     =  basic_string_view<char>;
using wstring_view    =  basic_string_view<wchar_t>;
using u16string_view  =  basic_string_view<char16_t>;
using u32string_view  =  basic_string_view<char32_t>;


extern template class basic_string_view<char>;
extern template class basic_string_view<wchar_t>;
extern template class basic_string_view<char16_t>;
extern template class basic_string_view<char32_t>;



////


extern template std::basic_ostream<char> &operator<<(std::basic_ostream<char> &, const basic_string_view<char> &);
extern template std::basic_ostream<wchar_t> &operator<<(std::basic_ostream<wchar_t> &, const basic_string_view<wchar_t> &);
extern template std::basic_ostream<char16_t> &operator<<(std::basic_ostream<char16_t> &, const basic_string_view<char16_t> &);
extern template std::basic_ostream<char32_t> &operator<<(std::basic_ostream<char32_t> &, const basic_string_view<char32_t> &);

#endif