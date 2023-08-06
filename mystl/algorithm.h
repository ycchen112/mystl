#pragma once

namespace mystl {

    template <class BidirectionalIterator1, class BidirectionalIterator2>
    BidirectionalIterator2 copy(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result) {
        while (first != last) {
            *result++ = *first++;
        }
        return result;
    }

    template <class BidirectionalIterator1, class BidirectionalIterator2>
    BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result) {
        while (first != last) {
            *--result = *--last;
        }
        return result;
    }

    // POD等可以用=直接复制
    template <class ForwardIterator, class T>
    void fill(ForwardIterator first, ForwardIterator last, const T& value) {
        for(; first != last; first++) {
            *first = value;
        }
    }

    template <class OutputIterator, class size, class T>
    OutputIterator fill_n(OutputIterator position, size n, const T& value) {
        for(; n != 0; n--, position++) {
            *position = value;
        }
        return position;
    }

}