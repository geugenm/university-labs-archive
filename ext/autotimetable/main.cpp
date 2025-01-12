// Autotimetable.cpp : Defines the entry point for the console application.
//

#include <cstdint>
#include <cstring>
#include <string>

#include <vector>
#include <iterator>
#include <utility>

#include <tuple>
#include <algorithm>
#include <iostream>

#include <fstream>
#include <iomanip>
#include <map>

#include <stdexcept>
#include <chrono>

#include <filesystem>
#include <regex>
#include <ctime>

#include "intrinsics.hpp"

#include "json.hpp"

#include "autotimetable.hpp"

/** This code is a command-line utility that generates a timetable of modules for a student given a list of required
 * modules and optional fixed modules. The utility reads in a list of all available modules from a file specified by
 * the user using the "--modulefile" command-line option. The user must also specify the required modules using the
 * "--required" option, which should be a comma-separated list of module codes.
 *
 * The utility also accepts several optional command-line arguments that allow the user to customize the timetable
 * generation process. The "--fixed" option allows the user to specify a list of fixed modules, which are modules that
 * must be included in the timetable. The "--quiet" option suppresses non-essential output. The "--empty-slot",
 * "--travel", and "--no-lunch" options allow the user to specify penalty scores for empty time slots, travel between
 * modules, and having no lunch break, respectively. The "--lunch" option allows the user to specify the start and end
 * times of the lunch break. The "--check-clash" option tells the utility to only consider timings that do not clash
 * with fixed modules or other required modules. The "--output" option specifies the file to output the timetable to.
 *
 * The code first processes the command-line arguments and initializes variables based on the user's input. It then reads
 * the list of all available modules from the file specified by the user and generates a list of the required modules.
 * The code then generates a timetable by iteratively adding required modules to the timetable, trying to minimize the
 * score based on the user-specified penalty scores. The resulting timetable is then printed to the console or written
 * to a file, depending on the user's specifications.
 */

/**
 * Searches for an argument in a list of command-line arguments.
 *
 * @param argumentCount The number of arguments in the argument vector.
 * @param argumentVector The argument vector containing the arguments.
 * @param key The key of the argument to search for.
 * @param out A reference to a string which will be set to the value of the argument if it is found.
 * @returns True if the argument was found, false otherwise.
 *
 * This function can be called with an argument vector containing command-line arguments, such as:
 * './program --key=value'
 *
 * The function will search for an argument with the key "--key" and, if found, set the value of
 * value to "value" (the string after the equals sign). If the argument is not found, value will
 * be set to nullptr.
 */
inline bool FindArgument(int argumentCount, char *argumentVector[], const char *key, char *&out) {
    const std::size_t keyLength = std::strlen(key);

    /// \note: argumentVector[0] is the program name, it won't be processed
    for (int i = 1; i < argumentCount; ++i) {
        char *parameter = argumentVector[i];
        const std::size_t parameterLength = std::strlen(parameter);

        if (!(keyLength <= parameterLength && std::equal(key, key + keyLength, parameter))) {
            continue;
        }

        if (keyLength == parameterLength) {
            out = parameter + parameterLength; // '\0'
            return true;
        } else if (parameter[keyLength] == '=') {
            out = parameter + keyLength + 1;
            return true;
        }
    }
    out = nullptr;
    return false;
}

/**
 * Reads a required command-line argument and returns its value.
 *
 * @param argumentCount The number of arguments in the argument vector.
 * @param argumentVector The argument vector containing the arguments.
 * @param key The key of the argument to search for.
 * @param failText A message to be printed if the argument is not found.
 * @param out A reference to a string which will be set to the value of the argument if it is found.
 * @returns True if the argument was found, false otherwise.
 *
 * This function works similarly to the FindArgument function, but it also prints an error message if the argument is
 * not found. It searches for an argument in the argumentVector with the specified key, and if it is found, it sets
 * the value of out to the value of the argument (as a std::string). If the argument is not found, the function prints
 * the failText message and returns false.
 *
 * If the argument is found, the value of value will be set to "value" (the string after the equals sign).
 * If the argument is not found, the function will print the error message "Error: missing required argument --key"
 * and return false.
 */
inline bool ReadRequiredParameter(int argumentCount, char *argumentVector[], const char *key, const char *failText,
                                  std::string &out) {
    char *_temporary = nullptr;
    if (FindArgument(argumentCount, argumentVector, key, _temporary)) {
        out = std::string(_temporary);
        return true;
    } else {
        std::cout << failText << std::endl;
        return false;
    }
}

/**
 * Reads an optional command-line argument and returns its value.
 *
 * @param argumentCount The number of arguments in the argument vector.
 * @param argumentVector The argument vector containing the arguments.
 * @param key The key of the argument to search for.
 * @param out A reference to a string which will be set to the value of the argument if it is found.
 * @returns True if the argument was found, false otherwise.
 *
 * This function works similarly to the FindArgument function, but it does not print an error message if the argument
 * is not found. It searches for an argument in the argumentVector with the specified key, and if it is found, it sets
 * the value of out to the value of the argument (as a std::string). If the argument is not found, the function returns
 * false without setting the value of out.
 *
 * If the argument is found, the value of value will be set to "value" (the string after the equals sign).
 * If the argument is not found, the function will return false without setting the value of value.
 */
inline bool ReadOptionalParameter(int argumentCount, char *argumentVector[], const char *key, std::string &out) {
    char *_temporary = nullptr;
    if (FindArgument(argumentCount, argumentVector, key, _temporary)) {
        out = std::string(_temporary);
        return true;
    } else {
        return false;
    }
}

/**
 * Converts a string representation of a day of the week to a numerical value.
 *
 * @param day A string containing the name of the day of the week.
 * @returns A numerical value representing the day of the week, where Monday is 0 and Sunday is 6.
 * @throws std::invalid_argument If the input string is not a valid day of the week.
 *
 * This function takes a string day representing the name of a day of the week and returns a numerical value
 * representing that day. The function compares the input string to a list of strings representing each day
 * of the week, and if a match is found, it returns the corresponding numerical value. If no match is found,
 * the function throws an std::invalid_argument exception with an error message indicating that the input
 * string is not a valid day of the week.
 *
 * This function can be called with a string representing any day of the week (e.g. "Monday", "Tuesday", "Wednesday", etc.).
 * If the input string is a valid day of the week, the function will return the corresponding numerical value. If the input
 * string is not a valid day of the week, the function will throw an std::invalid_argument exception.
 */
inline uint32_t DefineWeekDay(const std::string &day) {
    if (day == "Monday")return 0;
    if (day == "Tuesday")return 1;
    if (day == "Wednesday")return 2;
    if (day == "Thursday")return 3;
    if (day == "Friday")return 4;
    if (day == "Saturday")return 5;
    throw std::invalid_argument("Argument \"" + day + "\" not interpretable as day of week.");
}

/**
 * Enumeration for representing odd and even weeks.
 */
enum : uint32_t {
    WEEK_ODD = 1, WEEK_EVEN = 2
};

/**
 * Converts a string representation of a week type to a numerical value.
 *
 * @param week A string containing the name of the week type.
 * @returns A numerical value representing the week type, as defined by the WEEK_ODD and WEEK_EVEN enumeration.
 * @throws std::invalid_argument If the input string is not a valid week type.
 *
 * This function takes a string week representing the type of week and returns a numerical value representing that type.
 * The function compares the input string to a list of strings representing different week types, and if a match is found,
 * it returns the corresponding numerical value as defined by the WEEK_ODD and WEEK_EVEN enumeration. If no match is found,
 * the function throws an std::invalid_argument exception with an error message indicating that the input string is not a
 * valid week type.
 *
 * This function can be called with a string representing any week type (e.g. "Odd Week", "Even Week", "Every Week", etc.).
 * If the input string is a valid week type, the function will return the corresponding numerical value as defined by the
 * WEEK_ODD and WEEK_EVEN enumeration. If the input string is not a valid week type, the function will throw an
 * std::invalid_argument exception.
 */
[[maybe_unused]] inline uint32_t DefineWeekType(const std::string &week) {
    if (week == "Odd Week")return WEEK_ODD;
    if (week == "Even Week")return WEEK_EVEN;
    if (week == "Every Week")return WEEK_ODD | WEEK_EVEN;
    if (week == "0,1,2,3,4,5,6,7,8,9,10,11,12,13")return WEEK_ODD | WEEK_EVEN;
    throw std::invalid_argument("Argument \"" + week + "\" not interpretable as week type.");
}

/**
 * Converts a string representation of a week type to a numerical value, with error handling.
 *
 * @param week A string containing the name of the week type.
 * @param error A string reference which will be set to an error message if the input string is not a valid week type.
 * @returns A numerical value representing the week type, as defined by the WEEK_ODD and WEEK_EVEN enumeration. If the
 * input string is not a valid week type, the function will return the value representing every week (WEEK_ODD | WEEK_EVEN)
 * and set the error string to an appropriate message.
 *
 * This function works similarly to the DefineWeekType function, but it does not throw an exception if the input string is
 * not a valid week type. Instead, it sets an error message in the error string and returns a default value of WEEK_ODD | WEEK_EVEN
 * (representing every week).
 */
inline uint32_t DefineWeekType_soft(const std::string &week, std::string &error) noexcept {
    if (week == "Odd Week")return WEEK_ODD;
    if (week == "Even Week")return WEEK_EVEN;
    if (week == "Every Week")return WEEK_ODD | WEEK_EVEN;
    if (week == "0,1,2,3,4,5,6,7,8,9,10,11,12,13")return WEEK_ODD | WEEK_EVEN;
    error = "Argument \"" + week + "\" not interpretable as week type, will be treated as a weekly lesson.";
    return WEEK_ODD | WEEK_EVEN; // if we can't tell, just say its every week for good measure
}

/**
 * @brief Converts a JSON object into a time block object
 *
 * This function takes a JSON object representing a time block and converts it into
 * a `timeblock` object. It also takes a callback function that will be called if
 * there are any errors during the conversion process.
 *
 * @tparam Callback The type of the callback function
 * @param json_choice The JSON object representing the time block
 * @param soft_error_callback The callback function to be called in case of errors
 * @return The `timeblock` object converted from the JSON object
 * @throw std::invalid_argument If the day of the week or the time range are not valid
 */
template<typename Callback>
inline autotimetable::timeblock
SliceIntoTimeBlock(const nlohmann::json &json_choice, Callback soft_error_callback) {
    auto weekText = json_choice["WeekText"].get<std::string>();
    auto dayText = json_choice["DayText"].get<std::string>();
    auto startTimeText = json_choice["StartTime"].get<std::string>();
    auto endTimeText = json_choice["EndTime"].get<std::string>();

    std::string weekError;
    uint32_t weekMask = DefineWeekType_soft(weekText, weekError);

    if (!weekError.empty()) {
        soft_error_callback(weekError);
    }

    uint32_t weekDayNumber = DefineWeekDay(dayText);
    uint32_t startTime = static_cast<uint32_t>(std::stoul(startTimeText)) / 100;
    // round times up to the nearest hour
    uint32_t endTime = (static_cast<uint32_t>(std::stoul(endTimeText)) + 99) / 100;

    if (weekDayNumber >= (autotimetable::TIMEBLOCK_DAY_COUNT >> 1)) {
        throw std::invalid_argument("Day of week not valid.");
    }

    if (startTime >= endTime) {
        throw std::invalid_argument("Time range not valid.");
    }

    autotimetable::timeblock_day_t dayres = 0;

    for (uint32_t i = startTime; i < endTime; ++i) {
        dayres |= (1u << i);
    }

    autotimetable::timeblock result;

    if (weekMask & WEEK_ODD) {
        result.days[weekDayNumber] = dayres;
    }

    if (weekMask & WEEK_EVEN) {
        result.days[(autotimetable::TIMEBLOCK_DAY_COUNT >> 1) + weekDayNumber] = dayres;
    }

    return result;
}

/**
 * @brief Prints a header to an output stream
 *
 * This function prints a header to the specified output stream, with a range of
 * indices from `startingIndex` to `finalIndex`. The width of each index in the
 * header is specified by `width`.
 *
 * @param output The output stream to print to
 * @param startingIndex The starting index of the range to print
 * @param finalIndex The final index of the range to print
 * @param width The width of each index in the header
 */
inline void
PrintHeader(std::ostream &output, const uint32_t &startingIndex, const uint32_t &finalIndex, const uint32_t &width) {
    output << std::setw(0) << '|';

    for (uint32_t i = startingIndex; i < finalIndex; ++i) {
        output << std::right << std::setw(2) << std::setfill('0') << i << std::setw(width - 2) << std::setfill(' ')
               << "";
        output << std::setw(0) << '|';
    }

    output << std::endl;
}

/**
 * @brief Prints a spacer to an output stream
 *
 * This function prints a spacer to the specified output stream, with a range of
 * indices from `startingIndex` to `finalIndex`. The width of each index in the
 * spacer is specified by `width`.
 *
 * @param output The output stream to print to
 * @param startingIndex The starting index of the range to print
 * @param finalIndex The final index of the range to print
 * @param width The width of each index in the spacer
 */
inline void
PrintSpacer(std::ostream &output, const uint32_t &startingIndex, const uint32_t &finalIndex, const uint32_t &width) {
    output << std::setw(0) << '+';

    for (unsigned i = startingIndex; i < finalIndex; ++i) {
        output << std::left << std::setw(width) << std::setfill('-') << "";
        output << std::setw(0) << '+';
    }

    output << std::endl;
}

/**
 * @brief Prints the names of the modules in a timetable to an output stream
 *
 * This function prints the names of the modules in the specified timetable to the
 * specified output stream, for the specified day index. The range of indices to
 * print is from `startingIndex` to `finalIndex`, and the width of each index is
 * specified by `width`.
 *
 * @param out The output stream to print to
 * @param startingIndex The starting index of the range to print
 * @param finalIndex The final index of the range to print
 * @param width The width of each index in the output
 * @param timetable The timetable to print the module names from
 * @param dayIndex The index of the day to print the module names for
 */
inline void
PrintModuleName(std::ostream &out, const uint32_t &startingIndex, const uint32_t &finalIndex, const uint32_t &width,
                const autotimetable::timetable &timetable, const uint32_t &dayIndex) {
    out << std::setw(0) << '|';
    for (uint32_t i = startingIndex; i < finalIndex;) {
        auto it = std::find_if(timetable.items.cbegin(), timetable.items.cend(), [i, dayIndex](
                const std::tuple<typename std::vector<autotimetable::mod>::const_iterator, typename std::vector<autotimetable::mod_item>::const_iterator, typename std::vector<autotimetable::mod_item_choice>::const_iterator> &choice) {
            return (std::get<2>(choice)->timeblock1.days[dayIndex] & (1u << i));
        });

        if (it != timetable.items.cend()) {
            uint32_t modiend = i + 1;

            while (modiend < finalIndex && std::get<2>(*it)->timeblock1.days[dayIndex] & (1u << modiend)) {
                ++modiend;
            }

            uint32_t eff_width = (width + 1) * (modiend - i) - 1;
            out << std::left << std::setw(eff_width) << std::setfill(' ')
                << std::get<0>(*it)->code.substr(0, eff_width);
            i = modiend;
        } else {
            out << std::left << std::setw(width) << std::setfill(' ') << "";
            ++i;
        }
        out << std::setw(0) << '|';
    }
    out << std::endl;
}

/**
 * @brief Prints the types of the modules in a timetable to an output stream
 *
 * This function prints the types of the modules in the specified timetable to the
 * specified output stream, for the specified day index. The range of indices to
 * print is from `startingIndex` to `finalIndex`, and the width of each index is
 * specified by `width`.
 *
 * @param out The output stream to print to
 * @param startingIndex The starting index of the range to print
 * @param finalIndex The final index of the range to print
 * @param width The width of each index in the output
 * @param timetable The timetable to print the module types from
 * @param dayIndex The index of the day to print the module types for
 */
inline void
PrintModuleType(std::ostream &out, const uint32_t &startingIndex, const uint32_t &finalIndex, const uint32_t &width,
                const autotimetable::timetable &timetable, const uint32_t &dayIndex) {
    out << std::setw(0) << '|';
    for (uint32_t i = startingIndex; i < finalIndex;) {
        auto it = std::find_if(timetable.items.cbegin(), timetable.items.cend(), [i, dayIndex](
                const std::tuple<typename std::vector<autotimetable::mod>::const_iterator, typename std::vector<autotimetable::mod_item>::const_iterator, typename std::vector<autotimetable::mod_item_choice>::const_iterator> &choice) {
            return (std::get<2>(choice)->timeblock1.days[dayIndex] & (1u << i));
        });

        if (it != timetable.items.cend()) {
            uint32_t modiend = i + 1;
            while (modiend < finalIndex && std::get<2>(*it)->timeblock1.days[dayIndex] & (1u << modiend)) {
                ++modiend;
            }
            uint32_t eff_width = (width + 1) * (modiend - i) - 1;
            out << std::left << std::setw(eff_width) << std::setfill(' ')
                << std::get<1>(*it)->kind.substr(0, eff_width);
            i = modiend;
        } else {
            out << std::left << std::setw(width) << std::setfill(' ') << "";
            ++i;
        }
        out << std::setw(0) << '|';
    }
    out << std::endl;
}

/**
 * Prints the chosen module for the specified time range and day to the given output stream.
 *
 * @param out The output stream to which the module information will be printed.
 * @param startingIndex The index of the first time slot in the time range for which the module will be printed.
 * @param finalIndex The index of the last time slot in the time range for which the module will be printed.
 * @param width The width of the column in which the module will be printed.
 * @param timetable The timetable object containing the information about the modules.
 * @param dayIndex The index of the day for which the module will be printed.
 *
 * This function takes in an output stream, out, to which the module information will be printed. It also takes in
 * the indices of the first and last time slots in the time range for which the module will be printed, startingIndex
 * and finalIndex, respectively. The width parameter specifies the width of the column in which the module will be
 * printed. The timetable parameter is an object containing the information about the modules, and the dayIndex
 * parameter specifies the index of the day for which the module will be printed.
 *
 * The function iterates through the timetable object and finds the module that occupies the specified time range
 * and day. It then prints the name of the module to the output stream, using the specified width for the column.
 * If no module occupies the specified time range and day, the function prints an empty string to the output stream.
 */
inline void
PrintChosenModule(std::ostream &out, const uint32_t &startingIndex, const uint32_t &finalIndex, const uint32_t &width,
                  const autotimetable::timetable &timetable, const uint32_t &dayIndex) {
    out << std::setw(0) << '|';
    for (unsigned i = startingIndex; i < finalIndex;) {
        auto it = std::find_if(timetable.items.cbegin(), timetable.items.cend(), [i, dayIndex](
                const std::tuple<typename std::vector<autotimetable::mod>::const_iterator, typename std::vector<autotimetable::mod_item>::const_iterator, typename std::vector<autotimetable::mod_item_choice>::const_iterator> &choice) {
            return (std::get<2>(choice)->timeblock1.days[dayIndex] & (1u << i));
        });
        if (it != timetable.items.cend()) {
            unsigned modiend = i + 1;
            while (modiend < finalIndex && std::get<2>(*it)->timeblock1.days[dayIndex] & (1u << modiend))++modiend;
            unsigned eff_width = (width + 1) * (modiend - i) - 1;
            out << std::left << std::setw(eff_width) << std::setfill(' ')
                << std::get<2>(*it)->name.substr(0, eff_width);
            i = modiend;
        } else {
            out << std::left << std::setw(width) << std::setfill(' ') << "";
            ++i;
        }
        out << std::setw(0) << '|';
    }
    out << std::endl;
}

/**
 * Parses a fixed module string and returns the module code, name, and location.
 *
 * @param fixedModuleString The string to be parsed.
 * @param beginIndex The index of the first character in the string to be parsed.
 * @param endIndex The index of the last character in the string to be parsed.
 *
 * @return A tuple containing the module code, name, and location of the fixed module.
 *         If the string is invalid, the tuple will contain empty strings.
 *
 * This function takes in a string, fixed_mods_str, to be parsed, and the indices of the first and last characters
 * in the string to be parsed, begin and end, respectively. The string is expected to be in the format
 * "module_code:module_name:module_location".
 *
 * The function searches for the colon separators in the string and uses their indices to extract the module code,
 * name, and location from the string. It then returns these values as a tuple. If the string is invalid (e.g.,
 * if it does not contain the expected number of colon separators or if the indices are out of range), the function
 * returns a tuple containing empty strings.
 */
inline std::tuple<std::string, std::string, std::string> ParseFixedModuleString(std::string_view fixedModuleString,
                                                                                std::size_t beginIndex,
                                                                                std::size_t endIndex) {
    std::size_t firstColonIndex = fixedModuleString.find_first_of(':', beginIndex);
    if (firstColonIndex == std::string::npos) {
        return {"", "", ""};
    }

    std::size_t secondColonIndex = fixedModuleString.find_first_of(':', firstColonIndex + 1);
    if (secondColonIndex == std::string::npos) {
        return {"", "", ""};
    }

    std::size_t thirdColonIndex = fixedModuleString.find_first_of(':', secondColonIndex + 1);
    if (thirdColonIndex < endIndex) {
        return {"", "", ""};
    }
    return {std::string(fixedModuleString.substr(beginIndex, firstColonIndex - beginIndex)),
            std::string(fixedModuleString.substr(firstColonIndex + 1, secondColonIndex - (firstColonIndex + 1))),
            std::string(fixedModuleString.substr(secondColonIndex + 1, endIndex - (secondColonIndex + 1)))};
}


int main(int argumentCount, char *argumentVector[]) {
    std::string moduleFilePath;

    if (!ReadRequiredParameter(
            argumentCount,
            argumentVector,
            "--modulefile",
            "Fatal error: module file not specified.  Use \"--modulefile=<filename>\".",
            moduleFilePath)) {
        return 0;
    }


    std::string requiredModuleProperties;
    if (!ReadRequiredParameter(argumentCount,
                               argumentVector,
                               "--required",
                               "Fatal error: required modules not specified.  Use \"--required=<module code 1>,<module code 2>,...\", e.g. \"--required=CS1010,MA1101R,CS1231,BN1101,GET1002\" (without spaces).",
                               requiredModuleProperties)) {
        return 0;
    }

    std::string fixedModuleProperties;
    ReadOptionalParameter(argumentCount, argumentVector, "--fixed", fixedModuleProperties);
    for (char &symbol: fixedModuleProperties) {
        if (symbol == '-' || symbol == '_') {
            symbol = ' ';
        }
    }


    bool isQuietFlagApplied = false;
    {
        // Declare a string to store the value of the --quiet flag
        std::string quietFlagString;

        // Read the value of the --quiet flag, if it is present
        if (ReadOptionalParameter(argumentCount, argumentVector, "--quiet", quietFlagString)) {
            // Check the value of the --quiet flag
            if (quietFlagString.empty() || quietFlagString == "true" || quietFlagString == "t" ||
                quietFlagString == "1") {
                // If the value is empty or "true"/"t"/"1", set the isQuietFlagApplied flag to true
                isQuietFlagApplied = true;
            } else if (quietFlagString == "false" || quietFlagString == "f" || quietFlagString == "0") {
                // If the value is "false"/"f"/"0", set the isQuietFlagApplied flag to false
                isQuietFlagApplied = false;
            } else {
                // If the value is none of the above, print a warning message and ignore the value
                std::cout << "Warning: Cannot interpret value for --isQuietFlagApplied, ignoring it." << std::endl;
            }
        }
    }

    autotimetable::ConfigureScore scorer = autotimetable::defaultConfig();
    {
        // Declare a string to store the value of the --empty-slot flag
        std::string overrideEmptySlotPenalty;

        // Read the value of the --empty-slot flag, if it is present
        if (ReadOptionalParameter(argumentCount, argumentVector, "--empty-slot", overrideEmptySlotPenalty)) {
            // Try to convert the value of the --empty-slot flag to an unsigned long int
            try {
                // If the conversion is successful, assign the converted value to the emptySlotPenalty field of the scorer object
                scorer.emptySlotPenalty = static_cast<autotimetable::score_t>(std::stoul(overrideEmptySlotPenalty));
            }
                // If the conversion fails, print a warning message and ignore the value
            catch (...) {
                std::cout << "Warning: Cannot interpret value for --empty-slot, ignoring it." << std::endl;
            }
        }

    }
    {
        std::string overrideTravelPenalty;
        if (ReadOptionalParameter(argumentCount, argumentVector, "--travel", overrideTravelPenalty)) {
            try {
                scorer.travelPenalty = static_cast<autotimetable::score_t>(std::stoul(overrideTravelPenalty));
            }
            catch (...) {
                std::cout << "Warning: Cannot interpret value for --travel, ignoring it." << std::endl;
            }
        }
    }

    {
        // Declare a string to store the value of the --travel flag
        std::string overrideTravelPenalty;

        // Read the value of the --travel flag, if it is present
        if (ReadOptionalParameter(argumentCount, argumentVector, "--travel", overrideTravelPenalty)) {
            // Try to convert the value of the --travel flag to an unsigned long int
            try {
                // If the conversion is successful, assign the converted value to the travelPenalty field of the scorer object
                scorer.travelPenalty = static_cast<autotimetable::score_t>(std::stoul(overrideTravelPenalty));
            }
                // If the conversion fails, print a warning message and ignore the value
            catch (...) {
                std::cout << "Warning: Cannot interpret value for --travel, ignoring it." << std::endl;
            }
        }

    }

    {
        // Declare strings to store the values of the --lunch-start and --lunch-end flags
        std::string overrideLunchStart;
        std::string overrideLunchEnd;

        // Read the values of the --lunch-start and --lunch-end flags, if they are present
        bool hasLunchStart = ReadOptionalParameter(argumentCount, argumentVector, "--lunch-start", overrideLunchStart);
        bool hasLunchEnd = ReadOptionalParameter(argumentCount, argumentVector, "--lunch-end", overrideLunchEnd);

        // If the --lunch-start flag is present but the --lunch-end flag is not, print a warning message and ignore the --lunch-start flag
        if (hasLunchStart && !hasLunchEnd) {
            std::cout << "Warning: --lunch-start specified without --lunch-end, ignoring it." << std::endl;
        }
            // If the --lunch-end flag is present but the --lunch-start flag is not, print a warning message and ignore the --lunch-end flag
        else if (!hasLunchStart && hasLunchEnd) {
            std::cout << "Warning: --lunch-end specified without --lunch-start, ignoring it." << std::endl;
        }
            // If both the --lunch-start and --lunch-end flags are present, try to process them
        else if (hasLunchStart && hasLunchEnd) {
            // Try to convert the values of the --lunch-start and --lunch-end flags to unsigned long ints
            try {
                // If the conversions are successful, process the values
                auto tmpLunchStart = static_cast<autotimetable::score_t>(std::stoul(overrideLunchStart));
                auto tmpLunchEnd = static_cast<autotimetable::score_t>(std::stoul(overrideLunchEnd));
                // If either value does not end with '00', print a warning message and ignore the values
                if (tmpLunchStart % 100 || tmpLunchEnd % 100) {
                    std::cout << "Warning: --lunch-start and --lunch-end must end with '00', ignoring them."
                              << std::endl;
                }
                    // If the value of tmpLunchStart is larger than 2300, print a warning message and ignore the value
                else if (tmpLunchStart > 2300) {
                    std::cout << "Warning: --lunch-start larger than 2300, ignoring it." << std::endl;
                }
                    // If the value of tmpLunchEnd is larger than 2400, print a warning message and ignore the value
                else if (tmpLunchEnd > 2400) {
                    std::cout << "Warning: --lunch-end larger than 2400, ignoring it." << std::endl;
                }
                    // If the value of tmpLunchStart is not less than the value of tmpLunchEnd, print a warning message and ignore the values
                else if (tmpLunchStart >= tmpLunchEnd) {
                    std::cout << "Warning: --lunch-end must be later than --lunch-start, ignoring it." << std::endl;
                }
                    // If the values are valid, set the lunchTime field of the scorer object to the appropriate value
                else {
                    tmpLunchStart /= 100;
                    tmpLunchEnd /= 100;
                    scorer.lunchTime = (1u << tmpLunchEnd) - (1u << tmpLunchStart);
                }
            }
                // If the conversions fail, print a warning message and ignore the values
            catch (...) {
                std::cout << "Warning: Cannot interpret value for --lunch-start or --lunch-end, ignoring them."
                          << std::endl;
            }
        }

    }


    // Declare a vector of strings to store the required modules
    std::vector<std::string> requiredModules;

    // If the requiredModuleProperties string is not empty
    if (!requiredModuleProperties.empty()) {
        // Initialize the current and next variables to 0 and the index of the first comma in the string, respectively
        std::size_t current = 0;
        std::size_t next = requiredModuleProperties.find(',');

        // While the end of the string has not been reached
        while (true) {
            // If the next comma is not found
            if (next == std::string::npos) {
                // Add the remaining portion of the string to the requiredModules vector
                requiredModules.emplace_back(requiredModuleProperties.substr(current));
                // Break out of the loop
                break;
            }
                // If the next comma is found
            else {
                // Add the substring from the current index to the next index to the requiredModules vector
                requiredModules.emplace_back(requiredModuleProperties.substr(current, next - current));
                // Set the current index to the index after the next comma
                current = next + 1;
                // Set the next index to the index of the next comma after the current index
                next = requiredModuleProperties.find(',', current);
            }
        }
    }



    // Parse the `--fixed-module` command line argument and store the resulting data in `fixedModules`
    std::vector<std::tuple<std::string, std::string, std::string>> fixedModules;

    if (!fixedModuleProperties.empty()) {
        // Create a regular expression to match "module code:lesson type:class no"
        std::regex regex("(.+):(.+):(.+)");
        // Create an iterator to iterate over all matches of the regular expression in `fixedModuleProperties`
        std::sregex_iterator it(fixedModuleProperties.begin(), fixedModuleProperties.end(), regex);
        // Create an iterator that marks the end of the iteration
        std::sregex_iterator end;
        // Iterate over all matches
        while (it != end) {
            // Get the current match
            std::smatch match = *it;
            // Emplace a tuple containing the module code, lesson type, and class no into `fixedModules`
            fixedModules.emplace_back(match[1].str(), match[2].str(), match[3].str());
            // Move to the next match
            ++it;
        }
    }

    std::vector<autotimetable::mod> allModules;

    std::map<std::string, std::vector<autotimetable::mod>::const_iterator> moduleIndex;

    std::cout << "Loading modules..." << std::endl;
    {
        /* This code is loading data from a JSON file, processing it, and storing it in the allModules vector. The JSON file
         * contains information about modules (courses), including the code for each module, and the timetable options
         * available for each module.
         *
         * The json_data variable is used to read the contents of the JSON file and store it as a JSON object. The for_each
         * loop iterates over the modules in the JSON object and processes each module individually.
         *
         * For each module, the mod variable is created to store the processed information. The mod.code field is set to the
         * module code, which is read from the JSON object. The json_timeoptions variable stores the timetable options for
         * the module. Another for_each loop iterates over the timetable options and processes them.
         *
         * The choices variable is a map that stores the timetable options for each lesson type (e.g. lecture, tutorial).
         * For each timetable option, the mod_item_choices map stores the choice names and their corresponding mod_item_choice
         * objects. The choice object is created to store the processed timetable option data. The choice.timeblock1 field
         * is populated by calling the SliceIntoTimeBlock function, which processes the JSON data and returns a bitmask_t value.
         *
         * Finally, the code creates a map of module codes to iterators in the allModules vector, which will be used later
         * to quickly access the autotimetable::mod objects for each module.
         */
        nlohmann::json json_data;
        try {
            std::ifstream in(moduleFilePath);
            in >> json_data;
        }
        catch (std::ios_base::failure &e) {
            std::cout << "Fatal error: " << e.what() << std::endl;
            return 0;
        }
        std::for_each(std::make_move_iterator(json_data.begin()), std::make_move_iterator(json_data.end()),
                      [&allModules, isQuietFlagApplied](nlohmann::json &&json_module) {
                          autotimetable::mod mod;
                          try {
                              mod.code = json_module["ModuleCode"].get<std::string>();
                              std::map<std::string, std::map<std::string, autotimetable::mod_item_choice>> choices; // {kind, collection of {choicename, choice}}
                              nlohmann::json &json_timeoptions = json_module["Timetable"];
                              std::for_each(std::make_move_iterator(json_timeoptions.begin()),
                                            std::make_move_iterator(json_timeoptions.end()),
                                            [&choices, isQuietFlagApplied, &mod_code = mod.code](
                                                    nlohmann::json &&json_choice) {
                                                auto kind = json_choice["LessonType"].get<std::string>();
                                                std::map<std::string, autotimetable::mod_item_choice> &mod_item_choices = choices.try_emplace(
                                                        std::move(
                                                                kind) /* emplacing a default constructed object */).first->second;
                                                auto choice_name = json_choice["ClassNo"].get<std::string>();
                                                autotimetable::mod_item_choice &choice = mod_item_choices.try_emplace(
                                                        choice_name,
                                                        autotimetable::mod_item_choice{choice_name}).first->second;
                                                choice.timeblock1.add(SliceIntoTimeBlock(json_choice,
                                                                                         [isQuietFlagApplied, &mod_code](
                                                                                                 const std::string &err) {
                                                                                             if (!isQuietFlagApplied)
                                                                                                 std::cout
                                                                                                         << "Soft warning for module "
                                                                                                         << mod_code
                                                                                                         << ": "
                                                                                                         << err
                                                                                                         << std::endl;
                                                                                         }));
                                            });
                              mod.items.reserve(choices.size());
                              std::transform(std::make_move_iterator(choices.begin()),
                                             std::make_move_iterator(choices.end()), std::back_inserter(mod.items),
                                             [](std::pair<std::string, std::map<std::string, autotimetable::mod_item_choice>> &&choice_kind) {
                                                 std::vector<autotimetable::mod_item_choice> ret_choices;
                                                 ret_choices.reserve(choice_kind.second.size());
                                                 std::transform(std::make_move_iterator(choice_kind.second.begin()),
                                                                std::make_move_iterator(choice_kind.second.end()),
                                                                std::back_inserter(ret_choices),
                                                                [](std::pair<std::string, autotimetable::mod_item_choice> &&choice) {
                                                                    return std::move(choice.second);
                                                                });
                                                 return autotimetable::mod_item{std::move(choice_kind.first),
                                                                                std::move(ret_choices)};
                                             });
                          }
                          catch (const std::invalid_argument &err) {
                              if (!isQuietFlagApplied)
                                  std::cout << "Skipping module " << mod.code << " as we cannot interpret it: "
                                            << err.what() << std::endl;
                              return;
                          }
                          allModules.emplace_back(std::move(mod));
                      });
        allModules.shrink_to_fit();
    }

    std::cout << "Done loading modules." << std::endl;

    std::cout << "Building index..." << std::endl;
    for (auto it = allModules.cbegin(); it != allModules.cend(); ++it) {
        if (!moduleIndex.try_emplace(it->code, it).second) {
            std::cout << "Duplicate module " << it->code << ", module will be skipped" << std::endl;
        }
    }
    std::cout << "Done building index." << std::endl;

    std::vector<autotimetable::mod> selected_mods;
    selected_mods.reserve(requiredModules.size());

    std::cout << "Preparing parameters for autotimetable..." << std::endl;

    // Iterate through all the required modules specified by the user
    for (const std::string &mod_title: requiredModules) {
        // Find the iterator pointing to the module with the specified title in the moduleIndex map
        auto it = moduleIndex.find(mod_title);
        // If the iterator is not equal to the end of the map, add the module pointed to by the iterator to the selected_mods vector
        if (it != moduleIndex.end()) {
            selected_mods.emplace_back(*(it->second));
        }
            // If the iterator is equal to the end of the map, print a message indicating that the specified module could not be found
        else {
            std::cout << "Cannot find module " << mod_title << " as requested, module will be ignored" << std::endl;
        }
    }


    for (const std::tuple<std::string, std::string, std::string> &fix: fixedModules) {
        /*
         * This code iterates through a list of fixed modules. For each fixed module, it searches for a module with a
         * matching code in the list of selected modules. If found, it searches for an item with a matching kind in the
         * list of items for that module. If found, it searches for a choice with a matching name in the list of choices
         * for that item. If found, it deletes all the choices in the list except for the one with the matching name.
         */
        const std::string &mod_code = std::get<0>(fix);
        auto it1 = std::find_if(selected_mods.begin(), selected_mods.end(), [&mod_code](const autotimetable::mod &mod) {
            return mod.code == mod_code;
        });
        if (it1 != selected_mods.end()) {
            auto &items = it1->items;
            const std::string &mod_kind = std::get<1>(fix);
            auto it2 = std::find_if(items.begin(), items.end(), [&mod_kind](const autotimetable::mod_item &item) {
                return item.kind == mod_kind;
            });
            if (it2 != items.end()) {
                auto &choices = it2->choices;
                const std::string &mod_choice = std::get<2>(fix);
                auto it3 = std::find_if(choices.begin(), choices.end(),
                                        [&mod_choice](const autotimetable::mod_item_choice &choice) {
                                            return choice.name == mod_choice;
                                        });
                if (it3 != choices.end()) {
                    // delete all the choices except this one:
                    autotimetable::mod_item_choice choice = std::move(*it3);
                    choices.clear();
                    choices.emplace_back(std::move(choice));
                }
            }
        }
    }

    std::cout << "Done preparing." << std::endl;

    std::cout << "Running autotimetable..." << std::endl;
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    autotimetable::timetable find_result = autotimetable::FindBest(selected_mods, scorer);
    auto milliseconds_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start_time).count();
    std::cout << "Done running autotimetable..." << std::endl;

    std::cout << std::endl;

    // find the first and last hours to print
    unsigned begin_index = 24;
    for (const auto &tuple: find_result.items) {
        const auto &choice = *std::get<2>(tuple);
        for (const auto &day: choice.timeblock1.days) {
            if (day != 0) {
                begin_index = std::min(begin_index, intrinsics::find_smallest_set(day));
            }
        }
    }

    unsigned end_index = 0;
    for (const auto &tuple: find_result.items) {
        const auto &choice = *std::get<2>(tuple);
        for (const auto &day: choice.timeblock1.days) {
            if (day != 0) {
                end_index = std::max(end_index, intrinsics::find_largest_set(day));
            }
        }
    }
    end_index += 1;

    if (begin_index >= end_index) {
        std::cout << "No suitable timetable found." << std::endl;
        return 0;
    }

    // Print the result nicely
    std::cout << "Here is the result:" << std::endl;
    std::cout << std::endl;

    // Iterate through each week of the semester (12 weeks in total)
    for (unsigned i = 0; i < 12; ++i) {
        // Print the week type (odd or even) if it's the first or seventh week
        if (i == 0 || i == 6) {
            std::cout << "=== " << (i == 0 ? "Odd" : "Even") << " Week ===" << std::endl;
            PrintSpacer(std::cout, begin_index, end_index, 8); // Print a spacer line
            PrintHeader(std::cout, begin_index, end_index, 8); // Print the header line
            PrintSpacer(std::cout, begin_index, end_index, 8); // Print another spacer line
        }

        // If it's not a weekend or the module has a class on this day, print the module information for this day
        if (i % 6 != 5 || find_result.timeblock1.days[i] != 0) {
            PrintModuleName(std::cout, begin_index, end_index, 8, find_result, i); // Print the module name
            PrintModuleType(std::cout, begin_index, end_index, 8, find_result, i); // Print the module type
            PrintChosenModule(std::cout, begin_index, end_index, 8, find_result,
                              i); // Print the chosen module information
            PrintSpacer(std::cout, begin_index, end_index, 8); // Print another spacer line
        }
    }
    std::cout << std::endl;
    std::cout << "Autotimetable executed in " << milliseconds_elapsed << " ms." << std::endl;

    return 0;
}

