#include <utility>
#include <cstdint>
#include <cstddef>

namespace tt
{
    namespace utilities
    {
        template <class T>
        T abs(const T& a)
        {
            return (a < 0) ? -a : a;
        }

        template <class T>
        void swap(T &a, T &b)
        {
            T c(std::move(a));
            a = std::move(b);
            b = std::move(c);
        }
        
        template <class T, size_t N>
        void swap(T (&a)[N], T (&b)[N])
        {
            for (size_t i = 0; i < N; ++i)
                swap(a[i], b[i]);
        }

        template <class T>
        const T& max(const T& a, const T& b)
        {
            return (a > b ? a : b);
        }
        
        template <class T, size_t N>
        T max(const T (&v)[N])
        {
            T e = v[0];
            for (size_t i = 1; i < N; ++i)
                e = max(e, v[i]);
            return e;
        }

        template <class T>
        const T& min(const T& a, const T& b)
        {
            return (a < b ? a : b);
        }
        
        template <class T, size_t N>
        T min(const T (&v)[N])
        {
            T e = v[0];
            for (size_t i = 1; i < N; ++i)
                e = min(e, v[i]);
            return e;
        }
    }
}