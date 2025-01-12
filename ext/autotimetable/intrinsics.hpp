#pragma once

#include <cstdint>

#if defined(_MSC_VER)

#include <intrin.h>

/**
    @file intrinsics.hpp
    @brief Contains inline functions that use processor-specific instructions to perform common bit manipulation tasks faster.
    This file contains inline functions that use processor-specific instructions to perform common bit manipulation tasks faster.
    The functions are defined in the intrinsics namespace.
*/
namespace intrinsics {

    /**
    @brief Finds the index of the largest set bit in the given mask.
    @param mask The mask to search.
    @return The index of the largest set bit in the mask.
    This function finds the index of the largest set bit in the given mask using the _BitScanReverse processor instruction.
    The function assumes that there is at least one set bit in the mask.
    */
    inline std::uint32_t find_largest_set(std::uint32_t mask) {
        unsigned long res;
        _BitScanReverse(&res, static_cast<unsigned long>(mask));
        return static_cast<std::uint32_t>(res);
    }

    /**
    @brief Finds the index of the smallest set bit in the given mask.
    @param mask The mask to search.
    @return The index of the smallest set bit in the mask.
    This function finds the index of the smallest set bit in the given mask using the _BitScanForward processor instruction.
    The function assumes that there is at least one set bit in the mask.
    */
    inline std::uint32_t find_smallest_set(std::uint32_t mask) {
        unsigned long res;
        _BitScanForward(&res, static_cast<unsigned long>(mask));
        return static_cast<std::uint32_t>(res);
    }
}

#elif defined(__GNUC__)

/**
 * @namespace intrinsics
 * @brief Contains functions that use intrinsic functions or compiler-specific built-ins to optimize performance.
 */
namespace intrinsics {
	/**
     * @brief Finds the position of the largest set bit in a given mask.
     *
     * This function uses the __builtin_clz function, which is a compiler-specific built-in function that returns the number of leading zero bits in a word.
     *
     * @param mask The mask to find the largest set bit in.
     * @return The position of the largest set bit, with the least significant bit being position 0.
     *
     * @pre At least one bit in the mask must be set.
     */
	inline std::uint32_t find_largest_set(std::uint32_t mask) {
		return 31u - static_cast<std::uint32_t>(__builtin_clz(mask));
	}

	/**
     * @brief Finds the position of the smallest set bit in a given mask.
     *
     * This function uses the __builtin_ctz function, which is a compiler-specific built-in function that returns the number of trailing zero bits in a word.
     *
     * @param mask The mask to find the smallest set bit in.
     * @return The position of the smallest set bit, with the least significant bit being position 0.
     *
     * @pre At least one bit in the mask must be set.
     */
	inline std::uint32_t find_smallest_set(std::uint32_t mask) {
		return static_cast<std::uint32_t>(__builtin_ctz(mask));
	}

}

#endif

