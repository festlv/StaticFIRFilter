//
// Created by reinis on 5/8/23.
//

#ifndef STATIC_FIR_FILTER_HPP
#define STATIC_FIR_FILTER_HPP

#include <array>
#include <optional>
#include <array>
#include "StaticCircularBuffer.hpp"

template<class T, size_t TNumTaps>
class StaticFIRFilter {
public:
    explicit StaticFIRFilter(const std::array<T, TNumTaps>& coefficients) :
        _coefficients(coefficients)
    {

    }

    /**
     * Returns the number of taps for filter
     * @return
     */
    size_t num_taps() const {
        return TNumTaps;
    }

    void init_zeros()
    {
        for (int i=0; i < TNumTaps; i++)
            _sample_history.add(0);
    }

    /**
     * Applies filter to sample. Returns a filtered sample value if enough samples for all taps have been collected
     * @param sample
     * @return
     */
    std::optional<T> apply_filter(const T& sample)
    {
        _sample_history.add(sample);
        if (_sample_history.full())
        {
            T ret = 0.0f;
            for (int i=0; i < TNumTaps; i++)
            {
                ret += _coefficients[i] * _sample_history.at(i);
            }
            return ret;
        }
        return {};
    }

private:
    const std::array<T, TNumTaps> _coefficients;
    StaticCircularBuffer<T, TNumTaps> _sample_history;
};

#endif
