#pragma once

#include <any>
#include <utility>

// struct pair_hash
// {
//     template <class T1, class T2> std::size_t operator()(std::pair<T1, T2> const &pair) const
//     {
//         std::size_t h1 = std::hash<T1>()(pair.first);
//         std::size_t h2 = std::hash<T2>()(pair.second);

//         return h1 ^ h2;
//     }
// };

template <class T> inline void hash_combine(std::size_t &seed, const T &v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct pair_hash
{
    template <typename S, typename T> inline std::size_t operator()(const std::pair<S, T> &v) const
    {
        std::size_t seed = 0;
        hash_combine(seed, v.first);
        hash_combine(seed, v.second);
		
        return seed;
    }

    template <typename T> inline std::size_t operator()(const std::pair<T, std::any> &v) const
    {
        std::size_t seed = 0;
        hash_combine(seed, v.first);
        seed ^= std::size_t(&v.second);

        return seed;
    }
};