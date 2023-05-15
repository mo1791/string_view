#include <string_view.hxx>


//  ------------------------------------------------------------------------
    // Constructor
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    basic_string_view<CharT, Traits>::basic_string_view() noexcept
        : m_str(nullptr)
        , m_size(0ul)
    {
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    basic_string_view<CharT, Traits>::basic_string_view(const char_type *_str) noexcept
        : m_str(_str)
        , m_size(traits_type::length(_str))
    {
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    basic_string_view<CharT, Traits>::basic_string_view(const char_type *_str, size_type _count) noexcept
        : m_str(_str)
        , m_size(_count)
    {
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  --------------------------------------------------------------------------
    // Capacity
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::size() const noexcept
        -> typename basic_string_view::size_type
    {
        return m_size;
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::length() const noexcept
        -> typename basic_string_view::size_type
    {
        return size();
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::max_size() const noexcept
        -> typename basic_string_view::size_type
    {
        return ( npos - 1ul );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    bool basic_string_view<CharT, Traits>::empty() const noexcept
    {
        return ( m_size == 0ul );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  --------------------------------------------------------------------------
    // Element Access
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::c_str() const noexcept
        -> typename basic_string_view::const_pointer
    {
        return m_str;
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::data() const noexcept
        -> typename basic_string_view::const_pointer
    {
        return m_str;
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::operator[](size_type _pos) const noexcept
        -> typename basic_string_view::const_reference
    {
        return m_str[_pos];
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::at(size_type _pos) const
        -> typename basic_string_view::const_reference
    {
        return _pos < m_size 
				? m_str[_pos]
                : throw std::out_of_range("Input out of range in basic_string_view::at"), m_str[_pos];
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::front() const noexcept
        -> typename basic_string_view::const_reference
    {
        return *m_str;
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::back() const noexcept
        -> typename basic_string_view::const_reference
    {
        return m_str[m_size - 1ul];
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  --------------------------------------------------------------------------
    // Modifiers
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    void basic_string_view<CharT, Traits>::remove_prefix(size_type _n) noexcept
    {
        m_str += _n, m_size -= _n;
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits> 
    void basic_string_view<CharT, Traits>::remove_suffix(size_type _n) noexcept
    {
        m_size -= _n;
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits> 
    void basic_string_view<CharT, Traits>::swap(basic_string_view &_v) noexcept
    {
        using std::swap;
        swap(m_size, _v.m_size);
        swap(m_str, _v.m_str);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------



//  --------------------------------------------------------------------------
    // String Operations
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::copy(char_type *_dest,size_type _count,size_type _pos) const
        -> typename basic_string_view::size_type
    {
        if (_pos >= m_size)
        {
            throw std::out_of_range("Index out of range in basic_string_view::copy");
        }

        const size_type _rcount = std::min(m_size - _pos, _count + 1ul);
        std::copy( ( m_str + _pos ), ( m_str + _pos + _rcount ), _dest);

        return _rcount;
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::substr(size_type _pos, size_type _len) const -> basic_string_view
    {
        const size_type _max_length = _pos > m_size ? 0ul : ( m_size - _pos );

        if (_pos > size())
        {
            throw std::out_of_range("Index out of range in basic_string_view::substr");
        }

        return basic_string_view( ( m_str + _pos ), std::min(_len, _max_length));
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  --------------------------------------------------------------------------
    //  comparaison
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    int basic_string_view<CharT, Traits>::compare(basic_string_view v) const noexcept
    {
        const size_type rlen  = std::min(m_size, v.m_size);
        const int compare     = Traits::compare(m_str, v.m_str, rlen);

        return ( compare ? compare : ( m_size < v.m_size ? -1 : ( m_size > v.m_size ? 1 : 0 ) ) );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    int basic_string_view<CharT, Traits>::compare(size_type pos, size_type count, basic_string_view v) const
    {
        return substr(pos, count).compare(v);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    int basic_string_view<CharT, Traits>::compare(size_type pos1, size_type count1, basic_string_view v, size_type pos2,
                                                size_type count2) const
    {
        return substr(pos1, count1).compare(v.substr(pos2, count2));
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    int basic_string_view<CharT, Traits>::compare(const char_type *s) const
    {
        return compare(basic_string_view<CharT, Traits>(s));
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    int basic_string_view<CharT, Traits>::compare(size_type pos, size_type count, const char_type *s) const
    {
        return substr(pos, count).compare(basic_string_view<CharT, Traits>(s));
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    int basic_string_view<CharT, Traits>::compare(size_type pos, size_type count1, const char_type *s,
                                                size_type count2) const
    {
        return substr(pos, count1).compare(basic_string_view<CharT, Traits>(s, count2));
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  --------------------------------------------------------------------------
    // search
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find(basic_string_view v, size_type pos) const
        -> typename basic_string_view::size_type
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

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find(char_type c, size_type pos) const
        -> typename basic_string_view::size_type
    {
        return find(basic_string_view<CharT, Traits>(&c, 1ul), pos);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find(const char_type *s, size_type pos,size_type count) const
        -> typename basic_string_view::size_type
    {
        return find(basic_string_view<CharT, Traits>(s, count), pos);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find(const char_type *s, size_type pos) const
        -> typename basic_string_view::size_type
    {
        return find(basic_string_view<CharT, Traits>(s), pos);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::rfind(basic_string_view v, size_type pos) const
        -> typename basic_string_view::size_type
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

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::rfind(char_type c, size_type pos) const
        -> typename basic_string_view::size_type
    {
        return rfind(basic_string_view<CharT, Traits>(&c, 1ul), pos);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::rfind(const char_type *s,size_type pos,size_type count) const
        -> typename basic_string_view::size_type
    {
        return rfind(basic_string_view<CharT, Traits>(s, count), pos);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::rfind(const char_type *s, size_type pos) const
        -> typename basic_string_view::size_type
    {
        return rfind(basic_string_view<CharT, Traits>(s), pos);
    }

//  --------------------------------------------------------------------------
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find_first_of(basic_string_view v, size_type pos) const
        -> typename basic_string_view::size_type
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

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find_first_of(char_type c, size_type pos) const
        -> typename basic_string_view::size_type
    {
        return find_first_of(basic_string_view<CharT, Traits>(&c, 1ul), pos);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find_first_of(const char_type *s, size_type pos, size_type count) const
        -> typename basic_string_view::size_type
    {
        return find_first_of(basic_string_view<CharT, Traits>(s, count), pos);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find_first_of(const char_type *s, size_type pos) const
        -> typename basic_string_view::size_type
    {
        return find_first_of(basic_string_view<CharT, Traits>(s), pos);
    }

//  --------------------------------------------------------------------------
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find_last_of(basic_string_view v, size_type pos) const
        -> typename basic_string_view::size_type
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

//  --------------------------------------------------------------------------
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find_last_of(char_type c,size_type pos) const
        -> typename basic_string_view::size_type
    {
        return find_last_of(basic_string_view<CharT, Traits>(&c, 1ul), pos);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find_last_of(const char_type *s, size_type pos, size_type count) const
        -> typename basic_string_view::size_type
    {
        return find_last_of(basic_string_view<CharT, Traits>(s, count), pos);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find_last_of(const char_type *s,size_type pos) const
        -> typename basic_string_view::size_type
    {
        return find_last_of(basic_string_view<CharT, Traits>(s), pos);
    }

//  --------------------------------------------------------------------------
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find_first_not_of(basic_string_view v, size_type pos) const
        -> typename basic_string_view::size_type
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

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find_first_not_of(char_type c, size_type pos) const
        -> typename basic_string_view::size_type
    {
        return find_first_not_of(basic_string_view<CharT, Traits>(&c, 1ul), pos);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find_first_not_of(const char_type *s, size_type pos, size_type count) const
        -> typename basic_string_view::size_type
    {
        return find_first_not_of(basic_string_view<CharT, Traits>(s, count), pos);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find_first_not_of(const char_type *s, size_type pos) const
        -> typename basic_string_view::size_type
    {
        return find_first_not_of(basic_string_view<CharT, Traits>(s), pos);
    }

//  ------------------------------------------------------------------------
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find_last_not_of(basic_string_view v, size_type pos) const
        -> typename basic_string_view::size_type
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

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find_last_not_of(char_type c, size_type pos) const
        -> typename basic_string_view::size_type
    {
        return find_last_not_of(basic_string_view<CharT, Traits>(&c, 1ul), pos);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find_last_not_of(const char_type *s, size_type pos, size_type count) const
        -> typename basic_string_view::size_type
    {
        return find_last_not_of(basic_string_view<CharT, Traits>(s, count), pos);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::find_last_not_of(const char_type *s, size_type pos) const
        -> typename basic_string_view::size_type
    {
        return find_last_not_of(basic_string_view<CharT, Traits>(s), pos);
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

//  --------------------------------------------------------------------------
    // Iterator
//  --------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::begin() const noexcept
        -> typename basic_string_view::const_iterator
    {
        return m_str;
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::cbegin() const noexcept
        -> typename basic_string_view::const_iterator
    {
        return begin();
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::end() const noexcept
        -> typename basic_string_view::const_iterator
    {
        return ( m_str + m_size );
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::cend() const noexcept
        -> typename basic_string_view::const_iterator
    {
        return cend();
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::rbegin() const noexcept
        -> typename basic_string_view::const_reverse_iterator
    {
        return const_reverse_iterator{end()};
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::crbegin() const noexcept
        -> typename basic_string_view::const_reverse_iterator
    {
        return rbegin();
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::rend() const noexcept
        -> typename basic_string_view::const_reverse_iterator
    {
        return const_reverse_iterator{begin()};
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    auto basic_string_view<CharT, Traits>::crend() const noexcept
        -> typename basic_string_view::const_reverse_iterator
    {
        return crend();
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------

    template <typename CharT, typename Traits>
    bool basic_string_view<CharT, Traits>::is_one_of(CharT c, basic_string_view str)
    {
        for (auto s : str)
        {
            if (c == s)
            {
                return true;
            }
        }

        return false;
    }

//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------



template class basic_string_view<char>;
template class basic_string_view<wchar_t>;
template class basic_string_view<char16_t>;
template class basic_string_view<char32_t>;


/////


template auto operator<<(std::basic_ostream<char> &,     const basic_string_view<char> &) -> std::basic_ostream<char> &;
template auto operator<<(std::basic_ostream<wchar_t> &,  const basic_string_view<wchar_t> &) -> std::basic_ostream<wchar_t> &;
template auto operator<<(std::basic_ostream<char16_t> &, const basic_string_view<char16_t> &) -> std::basic_ostream<char16_t> &;
template auto operator<<(std::basic_ostream<char32_t> &, const basic_string_view<char32_t> &) -> std::basic_ostream<char32_t> &;
