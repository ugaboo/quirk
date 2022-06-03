#pragma once

#include <memory>
#include <vector>

namespace quirk::util {

template <class T> class PtrList {
    using List = std::vector<std::unique_ptr<T>>;

public:
    class Iterator {
        typename List::iterator it;

    public:
        Iterator(typename List::iterator it) : it(it) {}

        Iterator operator++()
        {
            it++;
            return *this;
        }

        bool operator==(Iterator other) const { return it == other.it; }
        bool operator!=(Iterator other) const { return !(*this == other); }
        auto operator*() const { return it->get(); }
    };

private:
    List data;

public:
    PtrList() = default;
    PtrList(PtrList&) = delete;

    void push_back(std::unique_ptr<T> item) { data.push_back(move(item)); }

    auto begin() { return Iterator(data.begin()); }

    auto end() { return Iterator(data.end()); }
};

} // namespace quirk::util