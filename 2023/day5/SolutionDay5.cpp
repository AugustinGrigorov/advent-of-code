#include "SolutionDay5.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stack>

struct Filter{
public:
    Filter(long start, long finish, long adjustment) : start(start), finish(finish), adjustment(adjustment) {}
    long start = 0;
    long finish = 0;
    long adjustment = 0;
};

std::vector<std::pair<long, long>> applyFilter (const std::vector<std::pair<long, long>>& seedRanges, const std::vector<Filter>& currentFilters) {
    std::vector<std::pair<long, long>> updatedSeedRanges = {};
    for (auto seedRange: seedRanges) {
        std::stack<std::pair<long, long>> remainingSeedRanges = {};
        remainingSeedRanges.push(seedRange);
        while (!remainingSeedRanges.empty()) {
            auto remainingSeedRange = remainingSeedRanges.top();
            remainingSeedRanges.pop();
            bool hasMatched = false;
            for (auto filter: currentFilters) {

                long r2_s = std::max(filter.start, remainingSeedRange.first);
                long r2_e = std::min(filter.finish, remainingSeedRange.second);
                if (r2_s < r2_e) {
                    hasMatched = true;
                    updatedSeedRanges.emplace_back(r2_s - filter.adjustment, r2_e - filter.adjustment);
                } else {
                    continue;
                }

                long r1_s = remainingSeedRange.first;
                long r1_e = filter.start - 1;
                if (r1_s < r1_e) {
                    remainingSeedRanges.emplace(r1_s, r1_e);
                }

                long r3_s = filter.finish + 1;
                long r3_e = remainingSeedRange.second;
                if (r3_s < r3_e) {
                    remainingSeedRanges.emplace(r3_s, r3_e);
                }
            }
            if (!hasMatched) {
                updatedSeedRanges.emplace_back(remainingSeedRange);
            }
        }
    }

    return updatedSeedRanges;
}

SolutionDay5::SolutionDay5(std::ifstream input) {
    std::vector<std::pair<long, long>> seedRanges = {};

    std::string discard;
    std::vector<Filter> currentFilters = {};

    for (std::string line; getline(input, line);) {
        if (!line.empty()) {
            if (line.contains("seeds:")) {
                std::istringstream is{line};
                is >> discard;
                long seedRangeStart = 0;
                long seedRange = 0;
                while (is >> seedRangeStart && is >> seedRange) {
                    seedRanges.emplace_back(seedRangeStart, seedRangeStart + seedRange);
                }
                continue;
            }
            if (line.contains("seed-to-soil map:")) continue;
            if (line.contains("soil-to-fertilizer map:")) {
                seedRanges = applyFilter(seedRanges, currentFilters);
                currentFilters = {};
                continue;
            }
            if (line.contains("fertilizer-to-water map:")) {
                seedRanges = applyFilter(seedRanges, currentFilters);
                currentFilters = {};
                continue;
            }
            if (line.contains("water-to-light map:")) {
                seedRanges = applyFilter(seedRanges, currentFilters);
                currentFilters = {};
                continue;
            }
            if (line.contains("light-to-temperature map:")) {
                seedRanges = applyFilter(seedRanges, currentFilters);
                currentFilters = {};
                continue;
            }
            if (line.contains("temperature-to-humidity map:")) {
                seedRanges = applyFilter(seedRanges, currentFilters);
                currentFilters = {};
                continue;
            }
            if (line.contains("humidity-to-location map:")) {
                seedRanges = applyFilter(seedRanges, currentFilters);
                currentFilters = {};
                continue;
            }

            long destination = 0;
            long startRange = 0;
            long range = 0;

            std::istringstream is{line};

            is >> destination;
            is >> startRange;
            is >> range;

            long endRange = startRange + range;
            long diff = startRange - destination;
            currentFilters.emplace_back(startRange, endRange, diff);
        }
    }
    seedRanges = applyFilter(seedRanges, currentFilters);
    for (auto seedRange : seedRanges) {
        partTwoSum = std::min(seedRange.first, partTwoSum);
    }
}

long SolutionDay5::solve1() const {
    return minDistance;
}

long SolutionDay5::solve2() const {
    return partTwoSum;
}
