#include "SolutionDay5.h"
#include <iostream>
#include <vector>
#include <sstream>

struct RangeMap {
public:
    RangeMap(long start, long range, long diff) : _start(start), _end(start + range), _diff(diff) {};
    [[nodiscard]] long mapsTo(long source) const {
        if (source >= _start && source < _end) {
            return source - _diff;
        }
        return -1;
    }
private:
    const long _start;
    const long _end;
    const long _diff;
};


SolutionDay5::SolutionDay5(std::ifstream input) {
    std::vector<long> seeds = {};
    std::vector<RangeMap> seedToSoilMaps = {};
    std::vector<RangeMap> soilToFertilizerMaps = {};
    std::vector<RangeMap> fertilizerToWaterMaps = {};
    std::vector<RangeMap> waterToLightMaps = {};
    std::vector<RangeMap> lightToTemperatureMaps = {};
    std::vector<RangeMap> temperatureToHumidityMaps = {};
    std::vector<RangeMap> humidityToLocationMaps = {};

    std::vector<RangeMap> *currentMaps = &seedToSoilMaps;
    std::string discard;

    for (std::string line; getline(input, line);) {
        if (!line.empty()) {
            if (line.contains("seeds:")) {
                std::istringstream is{line};
                is >> discard;
                long nextSeed = 0;
                while (is >> nextSeed) {
                    seeds.push_back(nextSeed);
                }
                continue;
            }
            if (line.contains("seed-to-soil map:")) continue;
            if (line.contains("soil-to-fertilizer map:")) {
                currentMaps = &soilToFertilizerMaps;
                continue;
            }
            if (line.contains("fertilizer-to-water map:")) {
                currentMaps = &fertilizerToWaterMaps;
                continue;
            }
            if (line.contains("water-to-light map:")) {
                currentMaps = &waterToLightMaps;
                continue;
            }
            if (line.contains("light-to-temperature map:")) {
                currentMaps = &lightToTemperatureMaps;
                continue;
            }
            if (line.contains("temperature-to-humidity map:")) {
                currentMaps = &temperatureToHumidityMaps;
                continue;
            }
            if (line.contains("humidity-to-location map:")) {
                currentMaps = &humidityToLocationMaps;
                continue;
            }

            long destination = 0;
            long source = 0;
            long range = 0;
            std::istringstream is{line};
            is >> destination;
            is >> source;
            is >> range;
            long diff = source - destination;
            currentMaps->emplace_back(source, range, diff);
        }
    }

    std::vector<std::vector<RangeMap>> orderOfConversions = {
            seedToSoilMaps,
            soilToFertilizerMaps,
            fertilizerToWaterMaps,
            waterToLightMaps,
            lightToTemperatureMaps,
            temperatureToHumidityMaps,
            humidityToLocationMaps
    };

    for (long seed : seeds) {
        long currentState = seed;
        for (auto &conversion : orderOfConversions) {
            int mapIndex = 0;
            while (mapIndex < conversion.size() - 1 && conversion[mapIndex].mapsTo(currentState) == -1) {
                mapIndex++;
            }
            long conversionValue = conversion[mapIndex].mapsTo(currentState);
            if (conversionValue != -1) {
                currentState = conversionValue;
            }
        }
        if (currentState < minDistance) {
            minDistance = currentState;
        }
    }
}

long SolutionDay5::solve1() const {
    return minDistance;
}

long SolutionDay5::solve2() const {
    return partTwoSum;
}
