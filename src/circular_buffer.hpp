#ifndef CUSTOM_LIBRARY_CIRCULAR_BUFFER_HPP
#define CUSTOM_LIBRARY_CIRCULAR_BUFFER_HPP

#include <cstddef>
#include <utility>
#include <new>
#include <cstdlib>
#include <iosfwd>

namespace shino {
    template <typename T>
    class circular_buffer
    {
        T* m_data;
        std::size_t m_size;
        std::size_t m_head;
        std::size_t m_tail;
        bool m_empty;
    public:
        circular_buffer(std::size_t size):
                m_size(size),
                m_head(0),
                m_tail(0),
                m_empty(false)
        {
            m_data = (T*)malloc(size * (sizeof *m_data)); //do not construct yet
            if (m_data == nullptr)
            {
                throw std::bad_alloc();
            }
        }

        template <typename ... ArgTypes>
        void emplace(ArgTypes&& ... args)
        {
            new (m_data + m_head) T(std::forward<ArgTypes>(args)...);
            ++m_head;
            if (m_head == m_size)
            {
                m_head = 0;
            }

            m_empty = false;
        }

        void pop()
        {
            (m_data + m_tail)->~T();
            ++m_tail;
            if (m_tail == m_size)
            {
                m_tail = 0;
            }

            if (m_tail == m_head)
            {
                m_empty = true;
            }
        }

        T& head()
        {
            return m_data[m_head];
        }

        const T& head() const
        {
            return m_data[m_head];
        }

        T& tail()
        {
            return m_data[m_tail];
        }

        const T& tail() const
        {
            return m_data[m_tail];
        }

        T& operator[](std::size_t index)
        {
            return m_data[index];
        }

        const T& operator[](std::size_t index) const
        {
            return m_data[index];
        }

        std::size_t size() const
        {
            return m_size;
        }

        T* data()
        {
            return m_data;
        }

        const T* data() const
        {
            return m_data;
        }

        bool is_empty() const
        {
            return m_empty;
        }

        bool is_full() const
        {
            return m_head == m_tail && !m_empty;
        }

        ~circular_buffer()
        {
            free(m_data);
        }

        template <typename U>
        friend std::ostream& operator<<(std::ostream& os, const circular_buffer<U>& buffer);
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const circular_buffer<T>& buffer)
    {
        auto first_dest = buffer.m_head;
        if (buffer.m_tail > buffer.m_head)
        {
            first_dest = buffer.size();
        }

        for (std::size_t i = buffer.m_tail; i < first_dest; ++i)
        {
            os << buffer.m_data[i] << ' ';
        }

        if (first_dest != buffer.m_head)
        {
            for (std::size_t i = 0; i < buffer.m_head; ++i)
            {
                os << buffer.m_data[i] << ' ';
            }
        }

        return os;
    }
}
#endif //CUSTOM_LIBRARY_CIRCULAR_BUFFER_HPP
