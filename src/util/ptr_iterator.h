#pragma once

namespace quirk::util {

template <class T> class PtrIterator {
    T it;

public:
    PtrIterator(T it) : it(it) {}

    PtrIterator operator++()
    {
        it++;
        return *this;
    }

    bool operator==(PtrIterator other) const { return it == other.it; }
    bool operator!=(PtrIterator other) const { return !(*this == other); }
    auto operator*() const { return it->second.get(); }
};

} // namespace quirk::util