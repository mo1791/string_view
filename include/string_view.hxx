/***********************************************
** @Copyright (C) 2018 - 2019 Mohammed ELomari.
** @brief A wrapper around non-owned strings.
************************************************/
#ifndef STRING_VIEW_HXX
#define STRING_VIEW_HXX


#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <ranges>
#include <stdexcept>
#include <string>

namespace ztd {

    template <typename CharT, typename Traits = std::char_traits<CharT>>
    class basic_string_view final
    {

    // Public Member Types
    public:
        using char_type   = CharT;
        using traits_type = Traits;
        using size_type   = std::size_t;
        using value_type  = CharT;
        using reference   = typename std::add_lvalue_reference<CharT>::type;
        using const_reference = typename std::add_lvalue_reference<typename std::add_const<CharT>::type>::type;
        using pointer         = typename std::add_pointer<CharT>::type;
        using const_pointer   = typename std::add_pointer<typename std::add_const<CharT>::type>::type;
        using iterator        = pointer;
        using const_iterator   = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Public Members
    public:
        static constexpr size_type npos = size_type(-1L);


    // Constructors
    public:
        /***
        * @brief Default constructs a basic_string_view without any content
        ****/
        constexpr basic_string_view() noexcept : m_str(nullptr) , m_size(0UL) {}


        /***
        * @brief Constructs a basic_string_view by copying another one
        * @param other the string view being copied
        ****/
        constexpr basic_string_view(const basic_string_view &other) noexcept = default;


        /***
        * @brief Constructs a basic_string_view by moving anothe rone
        * @param other the string view being moved
        ****/
        constexpr basic_string_view(basic_string_view &&other) noexcept = default;


        /***
        * @brief Constructs a basic_string_view from a std::basic_string
        * @param str the string to view
        ****/
        template <typename Allocator>
        constexpr basic_string_view(
            const std::basic_string<CharT, Traits, Allocator>& str) noexcept
                : m_str(str.c_str())
                , m_size(str.size())
        {
        }


        /***
        * @brief Constructs a basic_string_view from an ansi-string
        * @param str the string to view
        ****/
        constexpr basic_string_view(const_pointer str) noexcept
            : m_str(str)
            , m_size(traits_type::length(str))
        {
        }

        /***
        * @brief Constructs a basic_string_view from an ansi string of a given size
        * @param str the string to view
        * @param count the size of the string
        ****/
        constexpr basic_string_view(const_pointer str, size_type count) noexcept
            : m_str(str)
            , m_size(count)
        {
        }


    // Assignment
    public:
        /***
        * @brief Assigns a basic_string_view from an ansi-string
        * @param view the string to view
        * @return reference to \c (*this)
        ****/
        constexpr basic_string_view &operator=(const basic_string_view &view) = default;



    // Capacity
    public:
        /***
        * @brief Returns the length of the string, in terms of bytes
        * @return the length of the string, in terms of bytes
        ****/
        constexpr size_type size() const noexcept { return m_size; }

        /***
        * @copydoc basic_string_view::size
        ****/
        constexpr size_type length() const noexcept { return m_size; }


        /***
        * @brief The largest possible number of char-like objects that can be
        *        referred to by a basic_string_view.
        * @return Maximum number of characters
        ****/
        size_type max_size() const noexcept { return ( npos - 1UL ); }

        /***
        * @brief Returns whether the basic_string_view is empty (i.e. whether its length is 0).
        * @return whether the basic_string_view is empty
        ****/
        constexpr bool empty() const noexcept { return ( m_size == 0UL ); }



    // Element Access
    public:
        /***
        * @brief Gets the ansi-string of the current basic_string_view
        * @return the ansi-string pointer constexpr
        ****/
        constexpr const_pointer c_str() const noexcept { return m_str; }

        /***
        * @brief Gets the data of the current basic_string_view
        * \note This is an alias of #c_str
        * @return the data this basic_string_view contains constexpr
        ****/
        constexpr const_pointer data() const noexcept { return m_str; }

        /***
        * @brief Accesses the element at index \p pos
        * @param pos the index to access
        * @return const reference to the character
        ****/
        constexpr const_reference operator[](size_type pos) const noexcept { return *( m_str + pos ); }

        /***
        * @brief Accesses the element at index \p pos
        * @param pos the index to access
        * @return const reference to the character
        ****/
        constexpr const_reference at(size_type pos) const
        {
            if ( pos >= m_size ) {
                throw std::out_of_range("Index out of range in string_view::at");
            }
            return *( m_str + pos );
        }

        /***
        * @brief Access the first character of the string
        * \note Undefined behavior if basic_string_view is empty
        * @return reference to the first character of the string
        ****/
        constexpr const_reference front() const noexcept { return *m_str; }

        /***
        * @brief References the last character of the string
        * \note Undefined behavior if basic_string_view is empty
        * @return reference to the last character of the string
        ****/
        constexpr const_reference back() const noexcept { return *( m_str + ( m_size - 1UL) ); }


    // Modifiers
    public:
        /***
        * @brief Moves the start of the view forward by n characters.
        * \note  The behavior is undefined if n > size().
        * @param n number of characters to remove from the start of the view
        ****/
        void remove_prefix(size_type n) noexcept { m_str += n, m_size -= n; }

        /***
        * @brief Moves the end of the view back by n characters.
        * \note The behavior is undefined if n > size().
        * @param n number of characters to remove from the end of the view
        ****/
        void remove_suffix(size_type n) noexcept { m_size -= n; }

        /***
        * @brief Exchanges the view with that of v.
        * @param v view to swap with
        ****/
        void swap(basic_string_view &v) noexcept
        {
            std::swap(m_str, v.m_str);
            std::swap(m_size, v.m_size);
        }


    // Conversions
    public:
        /***
        * @brief Creates a basic_string with a copy of the content of the current view.
        * @tparam Allocator type used to allocate internal storage
        * @param a Allocator instance to use for allocating the new string
        * @return A basic_string containing a copy of the characters of the current view.
        ****/
        template <class Allocator = std::allocator<CharT>>
        constexpr std::basic_string<CharT, Traits, Allocator> to_string(
            const Allocator &a = Allocator()) const
        {
            return std::basic_string<CharT, Traits, Allocator>(m_str, m_size, a);
        }

        /***
        * @copydoc basic_string_view::to_string
        ****/
        template <class Allocator>
        explicit constexpr operator std::basic_string<CharT, Traits, Allocator>()
            const
        {
            return std::basic_string<CharT, Traits, Allocator>(m_str, m_size);
        }


        
    // Operations
    public:
        /***
        * @brief Copies the substring [pos, pos + rcount) to the character string
        *        pointed to by dest, where rcount is the smaller of count and size() - pos.
        * @param dest pointer to the destination character string
        * @param count requested substring length
        * @param pos position of the first character
        ****/
        constexpr size_type copy(pointer dest, size_type count = npos,
                                size_type pos = 0ul) const
        {
            if (pos >= m_size)
            {
                throw std::out_of_range("Index out of range in string_view::copy");
            }

            const size_type rcount = std::min(( m_size - pos ), ( count + 1ul ));
            std::copy( ( m_str + pos ), ( m_str + pos + rcount ), dest);

            return rcount;
        }

        /***
        * @brief Returns a substring of this viewed string
        * @param pos the position of the first character in the substring
        * @param len the length of the substring
        * @return the created substring
        ****/
        constexpr basic_string_view substr(size_t pos = 0ul,
                                        size_t len = npos) const
        {
            const size_type max_len = ( pos > m_size ) ? 0ul : ( m_size - pos );

            if (pos > size())
            {
                throw std::out_of_range("Index out of range in basic_string_view::substr");
            }

            return basic_string_view( ( m_str + pos ), std::min(len, max_len));
        }

        /***
        * @brief Compares two character sequences
        * @param v view to compare
        * @return negative value if this view is less than the other character
        *         sequence, zero if the both character sequences are equal,
        *         positive value if this view is greater than the other character
        *         sequence.
        ****/
        constexpr int compare(basic_string_view v) const noexcept
        {
            const size_type rlen  = std::min(m_size, v.m_size);
            const int compare     = Traits::compare(m_str, v.m_str, rlen);

            return (compare
                    ? compare
                    : ((m_size < v.m_size) ? -1 : ((m_size > v.m_size) ? 1 : 0)));
        }

        /***
        * @brief Compares two character sequences
        * @param pos   position of the first character in this view to compare
        * @param count number of characters of this view to compare
        * @param v     view to compare
        * @return negative value if this view is less than the other character
        *         sequence, zero if the both character sequences are equal,
        *         positive value if this view is greater than the other character
        *         sequence.
        ****/
        constexpr int compare(size_type pos, size_type count,
                            basic_string_view v) const
        {
            return substr(pos, count).compare(v);
        }

        /***
        * @brief Compares two character sequences
        * @param pos1   position of the first character in this view to compare
        * @param count1 number of characters of this view to compare
        * @param v      view to compare
        * @param pos2   position of the second character in this view to compare
        * @param count2 number of characters of the given view to compare
        * @return negative value if this view is less than the other character
        *         sequence, zero if the both character sequences are equal,
        *         positive value if this view is greater than the other character
        *         sequence.
        ****/
        constexpr int compare(size_type pos1, size_type count1, basic_string_view v,
                            size_type pos2, size_type count2) const
        {
            return substr(pos1, count1).compare(v.substr(pos2, count2));
        }

        /***
        * @brief Compares two character sequences
        * @param s pointer to the character string to compare to
        * @return negative value if this view is less than the other character
        *         sequence, zero if the both character sequences are equal,
        *         positive value if this view is greater than the other character
        *         sequence.
        ****/
        constexpr int compare(const_pointer s) const { return compare(basic_string_view<CharT, Traits>(s)); }

        /***
        * @brief Compares two character sequences
        * @param pos   position of the first character in this view to compare
        * @param count number of characters of this view to compare
        * @param s pointer to the character string to compare to
        * @return negative value if this view is less than the other character
        *         sequence, zero if the both character sequences are equal,
        *         positive value if this view is greater than the other character
        *         sequence.
        ****/
        constexpr int compare(size_type pos, size_type count,
                            const_pointer s) const
        {
            return substr(pos, count).compare(basic_string_view<CharT, Traits>(s));
        }

        /***
        * @brief Compares two character sequences
        * @param pos   position of the first character in this view to compare
        * @param count1 number of characters of this view to compare
        * @param s pointer to the character string to compare to
        * @param count2 number of characters of the given view to compare
        * @return negative value if this view is less than the other character
        *         sequence, zero if the both character sequences are equal,
        *         positive value if this view is greater than the other character
        *         sequence.
        ****/
        constexpr int compare(size_type pos, size_type count1, const_pointer s,
                            size_type count2) const
        {
            return substr(pos, count1).compare(basic_string_view<CharT, Traits>(s, count2));
        }

    // SEARCH
    public:
        /**
        * @brief  find characters in the view.
        ***/
        constexpr size_type find(basic_string_view v, size_type pos = 0ul) const
        {
            // Can't find a substring if the substring is bigger than this
            if (pos > size())
            {
                return npos;
            }

            if ((pos + v.size()) > size())
            {
                return npos;
            }

            const auto offset      = pos;
            const auto increments  = size() - v.size();

            for (auto i = 0ul; i <= increments; ++i)
            {
                const auto j = i + offset;

                if (substr(j, v.size()) == v)
                {
                    return j;
                }
            }

            return npos;
        }

        constexpr size_type find(char_type c, size_type pos = 0ul) const
        {
            return find(basic_string_view<CharT, Traits>(std::addressof(c), 1ul), pos);
        }

        constexpr size_type find(const_pointer s, size_type pos,
                                size_type count) const
        {
            return find(basic_string_view<CharT, Traits>(s, count), pos);
        }

        constexpr size_type find(const_pointer s, size_type pos = 0ul) const
        {
            return find(basic_string_view<CharT, Traits>(s), pos);
        }


        /**
        * @brief find the last occurrence of a substring.
        ***/
        constexpr size_type rfind(basic_string_view v, size_type pos = npos) const
        {
            if (empty())
            {
                return v.empty() ? 0ul : npos;
            }

            if (v.empty())
            {
                return std::min(size() - 1ul, pos);
            }

            if (v.size() > size())
            {
                return npos;
            }

            auto i = std::min(pos, (size() - v.size()));

            while (i != npos)
            {
                if (substr(i, v.size()) == v)
                {
                    return i;
                }
                --i;
            }

            return npos;
        }

        constexpr size_type rfind(char_type c, size_type pos = npos) const
        {
            return rfind(basic_string_view<CharT, Traits>(std::addressof(c), 1ul), pos);
        }

        constexpr size_type rfind(const_pointer s, size_type pos,
                                size_type count) const
        {
            return rfind(basic_string_view<CharT, Traits>(s, count), pos);
        }

        constexpr size_type rfind(const_pointer s, size_type pos = npos) const
        {
            return rfind(basic_string_view<CharT, Traits>(s), pos);
        }


        /**
        * @brief find first occurrence of characters.
        ***/
        constexpr size_type find_first_of(basic_string_view v,
                                        size_type pos = 0ul) const
        {
            const auto max_index = size();

            for (auto i = pos; i < max_index; ++i)
            {
                if (is_one_of(m_str[i], v))
                {
                    return i;
                }
            }

            return npos;
        }

        constexpr size_type find_first_of(char_type c, size_type pos = 0ul) const
        {
            return find_first_of(basic_string_view<CharT, Traits>(std::addressof(c), 1ul), pos);
        }

        constexpr size_type find_first_of(const_pointer s, size_type pos,
                                        size_type count) const
        {
            return find_first_of(basic_string_view<CharT, Traits>(s, count), pos);
        }

        constexpr size_type find_first_of(const_pointer s,
                                        size_type pos = 0ul) const
        {
            return find_first_of(basic_string_view<CharT, Traits>(s), pos);
        }

        /**
        * @brief find last occurrence of characters.
        ***/
        constexpr size_type find_last_of(basic_string_view v,
                                        size_type pos = npos) const
        {
            if (empty())
            {
                return npos;
            }

            const auto max_index = std::min(size() - 1ul, pos);

            for (auto i = 0ul; i <= max_index; ++i)
            {
                const auto j = max_index - i;

                if (is_one_of(m_str[j], v))
                {
                    return j;
                }
            }

            return npos;
        }

        constexpr size_type find_last_of(char_type c, size_type pos = npos) const
        {
            return find_last_of(basic_string_view<CharT, Traits>(std::addressof(c), 1ul), pos);
        }

        constexpr size_type find_last_of(const_pointer s, size_type pos,
                                        size_type count) const
        {
            return find_last_of(basic_string_view<CharT, Traits>(s, count), pos);
        }

        constexpr size_type find_last_of(const_pointer s,
                                        size_type pos = npos) const
        {
            return find_last_of(basic_string_view<CharT, Traits>(s), pos);
        }

        /**
        * @brief find first absence of characters.
        ***/
        constexpr size_type find_first_not_of(basic_string_view v,
                                            size_type pos = 0ul) const
        {
            const auto max_index = size();

            for (auto i = pos; i < max_index; ++i)
            {
                if (!is_one_of(m_str[i], v))
                {
                    return i;
                }
            }

            return npos;
        }

        constexpr size_type find_first_not_of(char_type c,
                                            size_type pos = 0ul) const
        {
            return find_first_not_of(basic_string_view<CharT, Traits>(std::addressof(c), 1ul), pos);
        }

        constexpr size_type find_first_not_of(const_pointer s, size_type pos,
                                            size_type count) const
        {
            return find_first_not_of(basic_string_view<CharT, Traits>(s, count), pos);
        }

        constexpr size_type find_first_not_of(const_pointer s,
                                            size_type pos = 0ul) const
        {
            return find_first_not_of(basic_string_view<CharT, Traits>(s), pos);
        }
        
        /**
        * @brief find last absence of characters.
        ***/
        constexpr size_type find_last_not_of(basic_string_view v,
                                            size_type pos = npos) const
        {
            if (empty())
            {
                return npos;
            }

            const auto max_index = std::min(size() - 1ul, pos);

            for (auto i = 0ul; i <= max_index; ++i)
            {
                const auto j = max_index - i;

                if (!is_one_of(m_str[j], v))
                {
                    return j;
                }
            }

            return npos;
        }

        constexpr size_type find_last_not_of(char_type c,
                                            size_type pos = npos) const
        {
            return find_last_not_of(basic_string_view<CharT, Traits>(std::addressof(c), 1ul), pos);
        }

        constexpr size_type find_last_not_of(const_pointer s, size_type pos,
                                            size_type count) const
        {
            return find_last_not_of(basic_string_view<CharT, Traits>(s, count), pos);
        }

        constexpr size_type find_last_not_of(const_pointer s,
                                            size_type pos = npos) const
        {
            return find_last_not_of(basic_string_view<CharT, Traits>(s), pos);
        }



    // Iterators
    public:
        /***
        * @brief Retrieves the begin iterator for this basic_string_view
        * @return the begin iterator
        ****/
        constexpr const_iterator  begin() const noexcept { return m_str; }
        constexpr const_iterator cbegin() const noexcept { return m_str; }

        /***
        * @brief Retrieves the end iterator for this basic_string_view
        * @return the end iterator
        ****/
        constexpr const_iterator  end() const noexcept { return ( m_str + m_size ); }
        constexpr const_iterator cend() const noexcept { return ( m_str + m_size ); }

        /***
        * @brief Retrieves the reverse begin iterator for this basic_string_view
        * @return the reverse begin iterator
        ****/
        constexpr const_reverse_iterator  rbegin() const noexcept { return const_reverse_iterator{end()}; }
        constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator{end()}; }

        /***
        * @brief Retrieves the reverse end iterator for this basic_string_view
        * @return the reverse end iterator
        ****/
        constexpr const_reverse_iterator  rend() const noexcept { return const_reverse_iterator{begin()}; }
        constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator{begin()}; }

        
    // Private Member
    private:
        /***
        * @brief Checks whether \p c is one of the characters in \p str
        * @param c the character to check
        * @param str the characters to compare against
        * @return true if \p c is one of the characters in \p str
        ****/
        static bool is_one_of(CharT c, basic_string_view str)
        {
            for ( CharT chr: str ) if ( chr == c ) return true;

            return false;
        }

    
    private:
        const CharT *m_str;  // The internal string type
        std::size_t m_size;  // The size of this string
    };

    /***
    * @brief
    * @tparam CharT
    * @tparam Traits
    ****/
    template <typename CharT, typename Traits>
    const typename basic_string_view<CharT, Traits>::size_type basic_string_view<CharT, Traits>::npos;



    // Public Functions

    /***
    * @brief Overload for ostream output of basic_string_view
    * @param o   The output stream to print to
    * @param str the string to print
    * @return reference to the output stream
    ****/
    template <typename CharT, typename Traits>
    auto operator<<(std::basic_ostream<CharT, Traits> &_output,
                    const basic_string_view<CharT, Traits> &_str)
        -> std::basic_ostream<CharT, Traits> &
    {
        std::ranges::copy(_str, std::ostream_iterator<CharT>(_output));
        return _output << "\xa";
    }

    template <typename CharT, typename Traits>
    void swap(basic_string_view<CharT, Traits> &lhs,
            basic_string_view<CharT, Traits> &rhs) noexcept
    {
        lhs.swap(rhs);
    }

    // Comparison Functions

    template <typename CharT, typename Traits>
    inline constexpr bool operator==(
        const basic_string_view<CharT, Traits> &_lhs,
        const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return (_lhs.compare(_rhs) == 0ul);
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator==(basic_string_view<CharT, Traits> const &_lhs,
                                    const CharT *_rhs) noexcept
    {
        return (_lhs == basic_string_view<CharT, Traits>(_rhs));
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator==(
        const CharT *_lhs, const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return (basic_string_view<CharT, Traits>(_lhs) == _rhs);
    }

    template <typename CharT, typename Traits, typename Allocator>
    inline constexpr bool operator==(
        const std::basic_string<CharT, Traits, Allocator> &_lhs,
        const basic_string_view<CharT, Traits> &_rhs)
    {
        return (basic_string_view<CharT, Traits>(_lhs) == _rhs);
    }

    template <typename CharT, typename Traits, typename Allocator>
    inline constexpr bool operator==(
        const basic_string_view<CharT, Traits> &_lhs,
        const std::basic_string<CharT, Traits, Allocator> &_rhs)
    {
        return (_lhs == basic_string_view<CharT, Traits>(_rhs));
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator!=(
        const basic_string_view<CharT, Traits> &_lhs,
        const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return (_lhs.compare(_rhs) != 0ul);
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator!=(const basic_string_view<CharT, Traits> &_lhs,
                                    const CharT *_rhs) noexcept
    {
        return (_lhs != basic_string_view<CharT, Traits>(_rhs));
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator!=(
        const CharT *_lhs, const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return (basic_string_view<CharT, Traits>(_lhs) != _rhs);
    }

    template <typename CharT, typename Traits, typename Allocator>
    inline constexpr bool operator!=(
        const std::basic_string<CharT, Traits, Allocator> &_lhs,
        const basic_string_view<CharT, Traits> &_rhs)
    {
        return (basic_string_view<CharT, Traits>(_lhs) != _rhs);
    }

    template <typename CharT, typename Traits, typename Allocator>
    inline constexpr bool operator!=(
        const basic_string_view<CharT, Traits> &_lhs,
        const std::basic_string<CharT, Traits, Allocator> &_rhs)
    {
        return (_lhs != basic_string_view<CharT, Traits>(_rhs));
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator<(
        const basic_string_view<CharT, Traits> &_lhs,
        const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return (_lhs.compare(_rhs) < 0ul);
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator<(const basic_string_view<CharT, Traits> &_lhs,
                                    const CharT *_rhs) noexcept
    {
        return (_lhs < basic_string_view<CharT, Traits>(_rhs));
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator<(
        const CharT *_lhs, const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return (basic_string_view<CharT, Traits>(_lhs) < _rhs);
    }

    template <typename CharT, typename Traits, typename Allocator>
    inline constexpr bool operator<(
        const std::basic_string<CharT, Traits, Allocator> &_lhs,
        const basic_string_view<CharT, Traits> &_rhs)
    {
        return (basic_string_view<CharT, Traits>(_lhs) < _rhs);
    }

    template <typename CharT, typename Traits, typename Allocator>
    inline constexpr bool operator<(
        const basic_string_view<CharT, Traits> &_lhs,
        const std::basic_string<CharT, Traits, Allocator> &_rhs)
    {
        return (_lhs < basic_string_view<CharT, Traits>(_rhs));
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator>(
        const basic_string_view<CharT, Traits> &_lhs,
        const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return (_lhs.compare(_rhs) > 0ul);
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator>(const basic_string_view<CharT, Traits> &_lhs,
                                    const CharT *_rhs) noexcept
    {
        return (_lhs > basic_string_view<CharT, Traits>(_rhs));
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator>(
        const CharT *_lhs, const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return (basic_string_view<CharT, Traits>(_lhs) > _rhs);
    }

    template <typename CharT, typename Traits, typename Allocator>
    inline constexpr bool operator>(
        const std::basic_string<CharT, Traits, Allocator> &_lhs,
        const basic_string_view<CharT, Traits> &_rhs)
    {
        return (basic_string_view<CharT, Traits>(_lhs) > _rhs);
    }

    template <typename CharT, typename Traits, typename Allocator>
    inline constexpr bool operator>(
        const basic_string_view<CharT, Traits> &_lhs,
        const std::basic_string<CharT, Traits, Allocator> &_rhs)
    {
        return (_lhs > basic_string_view<CharT, Traits>(_rhs));
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator<=(
        const basic_string_view<CharT, Traits> &_lhs,
        const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return (_lhs.compare(_rhs) <= 0ul);
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator<=(const basic_string_view<CharT, Traits> &_lhs,
                                    const CharT *_rhs) noexcept
    {
        return (_lhs <= basic_string_view<CharT, Traits>(_rhs));
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator<=(
        const CharT *_lhs, const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return (basic_string_view<CharT, Traits>(_lhs) <= _rhs);
    }

    template <typename CharT, typename Traits, typename Allocator>
    inline constexpr bool operator<=(
        const std::basic_string<CharT, Traits, Allocator> &_lhs,
        const basic_string_view<CharT, Traits> &_rhs)
    {
        return (basic_string_view<CharT, Traits>(_lhs) <= _rhs);
    }

    template <typename CharT, typename Traits, typename Allocator>
    inline constexpr bool operator<=(
        const basic_string_view<CharT, Traits> &_lhs,
        const std::basic_string<CharT, Traits, Allocator> &_rhs)
    {
        return (_lhs <= basic_string_view<CharT, Traits>(_rhs));
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator>=(
        const basic_string_view<CharT, Traits> &_lhs,
        const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return (_lhs.compare(_rhs) >= 0ul);
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator>=(const basic_string_view<CharT, Traits> &_lhs,
                                    const CharT *_rhs) noexcept
    {
        return (_lhs >= basic_string_view<CharT, Traits>(_rhs));
    }

    template <typename CharT, typename Traits>
    inline constexpr bool operator>=(
        const CharT *_lhs, const basic_string_view<CharT, Traits> &_rhs) noexcept
    {
        return (basic_string_view<CharT, Traits>(_lhs) >= _rhs);
    }

    template <typename CharT, typename Traits, typename Allocator>
    inline constexpr bool operator>=(
        const std::basic_string<CharT, Traits, Allocator> &_lhs,
        const basic_string_view<CharT, Traits> &_rhs)
    {
        return (basic_string_view<CharT, Traits>(_lhs) >= _rhs);
    }

    template <typename CharT, typename Traits, typename Allocator>
    inline constexpr bool operator>=(
        const basic_string_view<CharT, Traits> &_lhs,
        const std::basic_string<CharT, Traits, Allocator> &_rhs)
    {
        return (_lhs >= basic_string_view<CharT, Traits>(_rhs));
    }

    // Type Aliases

    using string_view    = basic_string_view<char>;
    using wstring_view   = basic_string_view<wchar_t>;
    using u16string_view = basic_string_view<char16_t>;
    using u32string_view = basic_string_view<char32_t>;

}
#endif