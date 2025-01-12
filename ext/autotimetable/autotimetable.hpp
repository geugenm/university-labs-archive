#pragma once

#include <cstdint>

#include <utility>
#include <tuple>
#include <functional>
#include <vector>
#include <string>
#include <algorithm>

namespace autotimetable {

    using timeblock_day_t = std::uint32_t;

    using score_t = std::uint32_t;

    constexpr const std::size_t TIMEBLOCK_DAY_COUNT = 12;

    struct timeblock {
        timeblock_day_t days[TIMEBLOCK_DAY_COUNT]{}; // 0-4 = odd week, 5-9 = even week

        timeblock() {
            std::fill_n(days, TIMEBLOCK_DAY_COUNT, 0);
        }

        timeblock(const timeblock &) = default;

        timeblock(timeblock &&) = default;

        timeblock &operator=(const timeblock &) = default;

        timeblock &operator=(timeblock &&) = default;

        inline void add(const timeblock &other) noexcept {
            for (std::size_t i = 0; i < TIMEBLOCK_DAY_COUNT; ++i) {
                days[i] |= other.days[i];
            }
        }

        inline void remove(const timeblock &other) noexcept {
            for (std::size_t i = 0; i < TIMEBLOCK_DAY_COUNT; ++i) {
                days[i] &= ~other.days[i];
            }
        }

        inline bool clash(const timeblock &other) const noexcept {
            for (std::size_t i = 0; i < TIMEBLOCK_DAY_COUNT; ++i) {
                if ((days[i] & other.days[i]) != 0) {
                    return true;
                }
            }
            return false;
        }

        inline bool operator==(const timeblock &other) const noexcept {
            for (std::size_t i = 0; i < TIMEBLOCK_DAY_COUNT; ++i) {
                if (days[i] != other.days[i]) {
                    return false;
                }
            }
            return true;
        }

        inline bool operator!=(const timeblock &other) const noexcept {
            return !(*this == other);
        }
    };

    struct mod_item_choice {
        std::string name;
        timeblock timeblock1;
    };

    struct mod_item {
        std::string kind;
        std::vector<mod_item_choice> choices;
    };

    struct mod {
        std::string code;
        std::vector<mod_item> items;
    };

    struct timetable {
        timeblock timeblock1;
        std::vector<std::tuple<typename std::vector<mod>::const_iterator, typename std::vector<mod_item>::const_iterator, typename std::vector<mod_item_choice>::const_iterator>> items;
    };

    struct ConfigureScore {

        // the penalty associated with every unit of empty timetable in a day in between sessions
        score_t emptySlotPenalty;

        // the penalty associated with having at least one session in a day
        score_t travelPenalty;

        // the penalty associated with not having at least one unit of break during lunch time
        score_t noLunchPenalty;

        // the timeslots which are considered to be acceptable for lunch (bitmask)
        timeblock_day_t lunchTime;

    };

    inline ConfigureScore defaultConfig() noexcept {
        ConfigureScore result{};
        result.emptySlotPenalty = 1;
        result.travelPenalty = 8;
        result.noLunchPenalty = 6;
        result.lunchTime = (1u << 15) - (1u << 11); //1100h to 1500h
        return result;
    }

    timetable FindBest(
            std::vector<std::pair<typename std::vector<mod>::const_iterator, typename std::vector<mod_item>::const_iterator>> &&mod_its,
            const ConfigureScore &scorer = defaultConfig());

    // the main searcher function
    timetable FindBest(const std::vector<mod> &mods, const ConfigureScore &scorer = defaultConfig());

}