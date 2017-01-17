#pragma once

#include <algorithm>
#include <assert.h>

namespace geometrize
{

namespace util
{

/**
 * @brief The Random class is a little utility for generating random numbers.
 * @author Sam Twidale (http://samcodes.co.uk/)
 */
class Random {
public:
    /**
     * @brief seed Seeds the random number generator.
     * @param seed The seed.
     */
    inline static void seed(const int seed)
    {
        m_seed = seed;
    }

    /**
     * @brief fastRand A fast implementation of the rand() function from the C library.
     * @return A random integer.
     */
    inline static int fastRand()
    {
        m_seed = (214013 * m_seed + 2531011);
        return (m_seed >> 16) & 0x7FFF;
    }

    /**
     * @brief randomRange Returns a random integer in the range, inclusive.
     * @param min The lower bound.
     * @param max The upper bound.
     * @return The random integer in the range.
     */
    inline static int randomRange(const int min, const int max)
    {
        assert(min <= max);
        return fastRand() % (max + 1 - min) + min; // Note this is biased
    }

private:
    static unsigned int m_seed; ///< Random seed
};

unsigned int Random::m_seed = 0;

/**
 * Clamps a value within a range.
 * @param value The value to clamp.
 * @param lower The lower bound of the range.
 * @param upper The upper bound of the range.
 * @return The clamped value.
 */
template<typename T> T clamp(const T& value, const T& lower, const T& upper)
{
    return std::max(lower, std::min(value, upper));
}

}

}
