#pragma once
#include "WeatherObservation.h"
#include <vector>
#include <string>

class CSVReader
{
    public:
     CSVReader();

    static std::vector<WeatherObservation> readCSV(std::string csvFile);

    /**
     * Function to separate single lines in csv file to vector of tokens, 
     * each separator divides the line into a new token
     * @param csvLine - single line from csv file,
     * @param separator - separator character
     */
    static std::vector<std::string> tokenise(std::string csvLine, char separator);

    /**
     * Convert vector of strings to DataPoint object,
     * used in readCSV function
     * @param tokens - vector of strings from tokenise function
     */
    static WeatherObservation stringsToObservationData(std::vector<std::string> tokens, 
                                        const std::vector<std::string>& countryCodes);

    /**
     * Convert vector of strings to CandleStick object,
     * used in readCSV function
     * @param tokens - vector of strings from tokenise function
     */
    // static CandleStick stringsToCandleStick(std::vector<std::string> tokens);

    /** Collects all country codes */
    static std::vector<std::string> parseCountryCodes (std::vector<std::string> tokens);
     
};