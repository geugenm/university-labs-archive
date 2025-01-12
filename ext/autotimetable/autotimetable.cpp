#include <cstdint>

#include <utility>
#include <vector>
#include <algorithm>
#include <limits>
#include <iterator>
#include <type_traits>

#include "autotimetable.hpp"
#include "intrinsics.hpp"

/**
 * It appears that this algorithm is an implementation of a search algorithm, specifically a depth-first search, to find
 * the most optimal timetable based on the given constraints and score configuration. It appears to do this by iterating
 * through each module and each module item (such as a lecture or tutorial), and adding or removing the corresponding
 * timeblock to the current timetable while keeping track of the current score. It then compares the current score to
 * the current best score, and updates the best timetable and score if the current score is better. This process is
 * repeated recursively until all possible combinations of modules and module items have been considered. The algorithm
 * returns the best timetable and score found after exploring all possible combinations.
 *
 * The algorithm also includes various helper functions and optimization techniques, such as sorting and unsorting
 * elements in a sequence, and using intrinsics to quickly find the smallest or largest set bit in a mask. These
 * optimization techniques are likely used to improve the efficiency of the search algorithm.
 */

/** This code defines a number of functions and templates related to searching for the best timetable given a list of
 * modules, each with their own possible time slots (represented as timeblocks). The main function of interest is
 * find_best, which takes a list of modules, a scoring configuration, and an output timetable, and searches for the
 * combination of time slots that result in the lowest score according to the given configuration.
 *
 * The code includes a number of helper functions and templates, such as sort_single_element_towards_front and
 * unsort_single_element_from_front, which perform in-place sorting and unsorting of a single element within a range
 * of elements, respectively. There are also functions for adding and removing timeblocks from a timetable, as well as
 * functions for calculating the score of a timeblock and a timetable.
 *
 * The code also defines a search_item struct, which represents a single module and its possible time slots, as well as
 * an iterator type search_iterator_t that points to a search_item. These are used as part of the search process in find_best.
 *
 * The code includes a number of #defines that can be used to customize certain aspects of the search process, such as
 * the maximum depth of the search tree (AUTOTIMETABLE_FILTER_DEPTH).
 */

#ifndef AUTOTIMETABLE_FILTER_DEPTH
#define AUTOTIMETABLE_FILTER_DEPTH 3
#endif

namespace autotimetable {

    /**
     * Sorts a single element towards the front of a range using a user-specified comparison function.
     *
     * @tparam RandomAccessIterator The type of iterator to use for the range.
     * @tparam Compare A type that can be used to compare two elements in the range.
     * @param begin An iterator pointing to the first element in the range.
     * @param element An iterator pointing to the element to be sorted.
     * @param comp A comparison function to use for sorting.
     * @returns An iterator pointing to the sorted element.
     *
     * This function sorts a single element in a range towards the front of the range using a user-specified comparison
     * function. The range is specified by an iterator pointing to the first element in the range (begin) and an iterator
     * pointing to the element to be sorted (element). The comparison function (comp) is used to determine the order of
     * the elements in the range.
     *
     * The function works by comparing the element to be sorted with the element preceding it in the range, and if the
     * element to be sorted is "less" than the preceding element (as determined by the comparison function), the two
     * elements are swapped. This process is repeated until the element to be sorted is in the correct position in the range.
     *
     * This function can be called with any random access iterator and a comparison function that can be used to compare
     * the elements in the range. The function returns an iterator pointing to the sorted element.
     */
    template<typename RandomAccessIterator, typename Compare>
    inline RandomAccessIterator
    SortSingleElementTowardsFront(RandomAccessIterator begin, RandomAccessIterator element, Compare comp) {
        while (element > begin && comp(*element, *(element - 1))) {
            Swap(*element, *(element - 1));
            --element;
        }
        return element;
    }

    /**
     * Unsorts a single element from the front of a range.
     *
     * @tparam RandomAccessIterator The type of iterator to use for the range.
     * @param element An iterator pointing to the element to be unsorted.
     * @param target An iterator pointing to the target position of the element.
     *
     * This function moves a single element in a range from its current position towards the front of the range.
     * The range is specified by an iterator pointing to the element to be moved (element) and an iterator pointing
     * to the target position of the element (target).
     *
     * The function works by repeatedly swapping the element to be moved with the element preceding it in the range
     * until it reaches the target position.
     *
     * This function can be called with any random access iterator. The function does not return a value.
     */
    template<typename RandomAccessIterator>
    inline void UnsortSingleElementFromFront(RandomAccessIterator element, RandomAccessIterator target) {
        while (element < target) {
            Swap(*element, *(element + 1));
            ++element;
        }
    }


    /**
     * Calculates a score based on a time block and a set of scoring parameters.
     *
     * @param timeBlock A time block to be scored.
     * @param scorer A set of scoring parameters.
     * @returns The calculated score.
     *
     * This function calculates a score based on a given time block and a set of scoring parameters. The time block is
     * represented by a timeblock struct, and the scoring parameters are represented by a ConfigureScore struct.
     *
     * The function iterates over each day in the time block and applies a set of penalties based on the values in the
     * timeblock_day_t struct for that day. The penalties applied include a travel penalty, an empty slot penalty, and
     * a no lunch penalty. The values for these penalties are taken from the scorer struct.
     *
     * This function can be called with a timeblock struct and a ConfigureScore struct. The function returns a score_t
     * value representing the calculated score.
     */
    inline score_t CalculateScore(const timeblock &timeBlock, const ConfigureScore &scorer) noexcept {
        score_t answer = 0;
        for (unsigned int day: timeBlock.days) {
            if (day == 0) {
                continue;
            }
            answer += scorer.travelPenalty;

            const auto firstSet = intrinsics::find_smallest_set(day);
            const auto lastSet = intrinsics::find_largest_set(day);

            answer += (lastSet - firstSet + 1) * scorer.emptySlotPenalty;

            if (((~day) & scorer.lunchTime) == 0) {
                answer += scorer.noLunchPenalty;
            }
        }
        return answer;
    }

    /**
     * Adds a time block to another time block and updates a score based on the result.
     *
     * @param score A reference to the score to be updated.
     * @param dest A reference to the time block to which the other time block will be added.
     * @param src The time block to be added.
     * @param scorer The scoring parameters to use for recalculating the score.
     *
     * This function adds one time block (src) to another time block (dest) and updates a score based on the result.
     * The function calls the add member function of the timeblock struct to perform the addition, and then recalculates
     * the score using the CalculateScore function and the provided scoring parameters (scorer). The updated score is
     * stored in the score variable.
     */
    inline void
    AddTimeBlock(score_t &score, timeblock &dest, const timeblock &src, const ConfigureScore &scorer) noexcept {
        dest.add(src);
        score = CalculateScore(dest, scorer);
    }

    /**
     * Removes a time block from another time block and updates a score based on the result.
     *
     * @param score A reference to the score to be updated.
     * @param destination A reference to the time block from which the other time block will be removed.
     * @param source The time block to be removed.
     * @param scorer The scoring parameters to use for recalculating the score.
     *
     * This function removes one time block (source) from another time block (destination) and updates a score based
     * on the result. The function calls the remove member function of the timeblock struct to perform the removal,
     * and then recalculates the score using the CalculateScore function and the provided scoring parameters (scorer).
     * The updated score is stored in the score variable.
     */
    inline void
    RemoveTimeBlock(score_t &score, timeblock &destination, const timeblock &source,
                    const ConfigureScore &scorer) noexcept {
        destination.remove(source);
        score = CalculateScore(destination, scorer);
    }


    /**
     * A struct for storing information about a search for a specific item.
     *
     * The ItemSearcher struct is used to store information about a search for a specific item. It contains an
     * iterator pointing to the module in which the item is contained, an iterator pointing to the module item
     * being searched for, and a vector of pairs, each containing a time block and an iterator pointing to a choice
     * within that time block for the item being searched for.
     *
     * The iterators are templatized with the type mod and mod_item, respectively, to allow them to be used with
     * different types of containers. The vector of pairs is templatized with the type mod_item_choice to allow
     * it to be used with different types of choices.
     */
    struct ItemSearcher {
        /** An iterator pointing to the module in which the item is contained. */
        typename std::vector<mod>::const_iterator moduleIterator;

        /** An iterator pointing to the module item being searched for. */
        typename std::vector<mod_item>::const_iterator moduleItemIterator;

        /**
         * A vector of pairs, each containing a time block and an iterator pointing to a choice within that time block
         * for the item being searched for.
         */
        std::vector<std::pair<timeblock, typename std::vector<mod_item_choice>::const_iterator>> choices;
    };

    /**
     * Swaps the contents of two `ItemSearcher` structs.
     *
     * @param a A reference to the first `ItemSearcher` struct.
     * @param b A reference to the second `ItemSearcher` struct.
     *
     * This function swaps the contents of two ItemSearcher structs. It uses the std::swap function to swap the values
     * of the moduleIterator, moduleItemIterator, and choices members of the structs.
     */
    inline void Swap(ItemSearcher &a, ItemSearcher &b) noexcept {
        std::swap(a.moduleIterator, b.moduleIterator);
        std::swap(a.moduleItemIterator, b.moduleItemIterator);
        std::swap(a.choices, b.choices);
    }


    using search_iterator_t = typename std::vector<ItemSearcher>::iterator;


    score_t
    FindBestImplementation(search_iterator_t next, search_iterator_t end, score_t currentScore,
                           timetable &currentTimetable,
                           score_t bestScore, timetable &bestTimetable, const ConfigureScore &scorer);

    /**
     * Performs a search for the best timetable by iterating over the choices for a specific item.
     *
     * @param next An iterator pointing to the current item in the search.
     * @param end An iterator pointing to the end of the search range.
     * @param current_score A reference to the current score of the timetable being constructed.
     * @param currentTimetable A reference to the current timetable being constructed.
     * @param bestScore A reference to the best score found so far.
     * @param best_timetable A reference to the timetable with the best score found so far.
     * @param scorer The scoring parameters to use for evaluating the timetable.
     *
     * This function performs a search for the best timetable by iterating over the choices for a specific item.
     * It takes as input an iterator pointing to the current item in the search (next), an iterator pointing to
     * the end of the search range (end), a reference to the current score of the timetable being constructed
     * (current_score), a reference to the current timetable being constructed (currentTimetable), a reference to
     * the best score found so far (bestScore), a reference to the timetable with the best score found so far
     * (best_timetable), and the scoring parameters to use for evaluating the timetable (scorer).
     */
    inline void
    DoFindBestIteration(const search_iterator_t &next, const search_iterator_t &end, score_t &current_score,
                        timetable &currentTimetable, score_t &bestScore, timetable &best_timetable,
                        const ConfigureScore &scorer) {
        search_iterator_t pass_next = next;
        ++pass_next;

        for (auto it3 = next->choices.cbegin(); it3 != next->choices.cend(); ++it3) {
            if (currentTimetable.timeblock1.clash(it3->first)) {
                continue;
            }

            // Add the current choice to the current timetable
            AddTimeBlock(current_score, currentTimetable.timeblock1, it3->first, scorer);
            currentTimetable.items.emplace_back(next->moduleIterator, next->moduleItemIterator, it3->second);

            // Recursive call
            bestScore = FindBestImplementation(pass_next, end, current_score, currentTimetable, bestScore,
                                               best_timetable,
                                               scorer);

            // Remove the current choice
            currentTimetable.items.pop_back();
            RemoveTimeBlock(current_score, currentTimetable.timeblock1, it3->first, scorer);

        }
    }

    /**
     * Finds the best timetable using a recursive search algorithm.
     *
     * @param next An iterator pointing to the current item in the search.
     * @param end An iterator pointing to the end of the search range.
     * @param currentScore The current score of the timetable being constructed.
     * @param currentTimetable A reference to the current timetable being constructed.
     * @param bestScore A reference to the best score found so far.
     * @param bestTimetable A reference to the timetable with the best score found so far.
     * @param scorer The scoring parameters to use for evaluating the timetable.
     * @return The best score found.
     *
     * This function finds the best timetable using a recursive search algorithm. It takes as input an iterator pointing
     * to the current item in the search (next), an iterator pointing to the end of the search range (end), the current
     * score of the timetable being constructed (currentScore), a reference to the current timetable being constructed
     * (currentTimetable), a reference to the best score found so far (bestScore), a reference to the timetable with the
     * best score found so far (bestTimetable), and the scoring parameters to use for evaluating the timetable (scorer).
     */
    score_t FindBestImplementation(search_iterator_t next, search_iterator_t end, score_t currentScore,
                                   timetable &currentTimetable, score_t bestScore, timetable &bestTimetable,
                                   const ConfigureScore &scorer) {
        if (next == end) {
            if (currentScore < bestScore) { // We've found something better than ever!
                // Keep this better result instead of the old result
                bestTimetable = currentTimetable;
                bestScore = currentScore;
            }
            return bestScore;
        }
        // NOTE: this optimization can be done because if timetable A is a subset of timetable B, then the penalty for B must be at least equal to the penalty for A
        if (currentScore >= bestScore) {
            return bestScore;
        }

        // If we reach here, it means next < end, i.e. we have some more mod_items to place on the timetable
        // Then we will place the next item on the timetable and recursively call this function again

        if (std::distance(next, end) > (AUTOTIMETABLE_FILTER_DEPTH)) {
            search_iterator_t filterIterator = next;
            std::advance(filterIterator, AUTOTIMETABLE_FILTER_DEPTH);

            std::vector<std::pair<timeblock, typename std::vector<mod_item_choice>::const_iterator>> tmp_choices = std::move(
                    filterIterator->choices);

            filterIterator->choices.clear();
            filterIterator->choices.reserve(tmp_choices.size());

            std::copy_if(tmp_choices.cbegin(), tmp_choices.cend(), std::back_inserter(filterIterator->choices),
                         [&currentTimetable](
                                 const std::pair<timeblock, typename std::vector<mod_item_choice>::const_iterator> &choice) {
                             return !currentTimetable.timeblock1.clash(choice.first);
                         });

            auto new_filter_it = SortSingleElementTowardsFront(next, filterIterator,
                                                               [](const ItemSearcher &a, const ItemSearcher &b) {
                                                                   return a.choices.size() < b.choices.size();
                                                               });

            DoFindBestIteration(next, end, currentScore, currentTimetable, bestScore, bestTimetable, scorer);

            UnsortSingleElementFromFront(new_filter_it, filterIterator);

            filterIterator->choices = std::move(tmp_choices);

        } else {
            DoFindBestIteration(next, end, currentScore, currentTimetable, bestScore, bestTimetable, scorer);
        }

        return bestScore;
    }

    /**
     * @brief Finds the best timetable based on the provided ItemSearcher objects and ConfigureScore object.
     * @param mod_its A vector of ItemSearcher objects to be used in the search for the best timetable
     * @param scorer The ConfigureScore object that determines how the score of a timetable is calculated.
     * @return timetable The best timetable based on the provided ItemSearcher objects and ConfigureScore object.
     */
    timetable FindBest(std::vector<ItemSearcher> &&mod_its, const ConfigureScore &scorer) {

        // The answer will go here
        timetable bestTimetable;

        // The current (temp) timetable being built
        timetable currentTimetable;

        // We shall process the module-item with least choices first (it might be faster this way)
        std::sort(mod_its.begin(), mod_its.end(), [](const ItemSearcher &a, const ItemSearcher &b) {
            return a.choices.size() < b.choices.size();
        });

        FindBestImplementation(mod_its.begin(), mod_its.end(), 0, currentTimetable,
                               std::numeric_limits<score_t>::max(),
                               bestTimetable, scorer);

        return bestTimetable;
    }

    /**
     * @brief Finds the best timetable based on the provided mod objects and ConfigureScore object.
     * @param mods A vector of mod objects to be used in the search for the best timetable.
     * @param scorer The ConfigureScore object that determines how the score of a timetable is calculated.
     * @return timetable The best timetable based on the provided mod objects and ConfigureScore object.
     */
    timetable FindBest(const std::vector<mod> &mods, const ConfigureScore &scorer) {

        std::vector<ItemSearcher> modIts;

        for (auto it1 = mods.cbegin(); it1 != mods.cend(); ++it1) {
            for (auto it2 = it1->items.cbegin(); it2 != it1->items.cend(); ++it2) {
                std::vector<std::pair<timeblock, typename std::vector<mod_item_choice>::const_iterator>> tmpVec;
                tmpVec.reserve(it2->choices.size());
                for (auto it3 = it2->choices.cbegin(); it3 != it2->choices.cend(); ++it3) {
                    // the if-statement is to prevent mods with many options from making the engine slow by only taking the first of similar options
                    // it turns out that this optimization yields more than 5x increase in speed
                    if (std::find_if(tmpVec.cbegin(), tmpVec.cend(), [&tb = it3->timeblock1](
                            const std::pair<timeblock, typename std::vector<mod_item_choice>::const_iterator> &choice) {
                        return choice.first == tb;
                    }) == tmpVec.cend())
                        tmpVec.emplace_back(it3->timeblock1, it3);
                }
                tmpVec.shrink_to_fit();
                modIts.emplace_back(ItemSearcher{it1, it2, std::move(tmpVec)});
            }
        }

        // be nice to the system, don't keep memory we will never use
        modIts.shrink_to_fit();

        return FindBest(std::move(modIts), scorer);

    }

}