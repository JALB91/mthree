#ifndef POS_H
#define POS_H

#include <functional>
#include <cstdint>

namespace mthree {

template<typename T>
class Pos
{
public:
    Pos(T x, T y):
    x(x),
    y(y)
    {}

    T x;
    T y;

public:
    bool operator>(const Pos<T>& other) const
    {
        return (this->x > other.x || (this->x == other.x && this->y > other.y));
    }

    bool operator<(const Pos<T>& other) const
    {
        return (this->x < other.x || (this->x == other.x && this->y < other.y));
    }

};

using BoardPos = Pos<uint8_t>;
using FPos = Pos<float>;

} // namespace mthree


namespace std {

template<typename T> 
struct less<mthree::Pos<T>>
{
    bool operator() (const mthree::Pos<T>& lhs, const mthree::Pos<T>& rhs) const
    {
        return lhs < rhs;
    }
};

} // namespace std

#endif /* POS_H */