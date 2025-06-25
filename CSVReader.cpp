#include "CSVReader.h"
#include <iostream>
#include <fstream>

CSVReader::CSVReader()
{

}

std::vector<WeatherObservation> CSVReader::readCSV(std::string csvFilename)
{
    std::vector<WeatherObservation> entries;
    std::vector<std::string> countryCodes;

    std::ifstream csvFile{csvFilename};
    std::string line;
    bool isFirstLine = true; 
    int iteration = 0;
    if (csvFile.is_open())
    {
        while(std::getline(csvFile, line))
        {
            try {
                if (isFirstLine) { //*own code check if it is the first line
                    // Process the header here
                    countryCodes = parseCountryCodes(tokenise(line, ','));
                    isFirstLine = false; // Mark that the header has been processed
                    continue; // Skip the rest of this iteration
                }
                WeatherObservation ob = stringsToObservationData(tokenise(line, ','), countryCodes);
                entries.push_back(ob);
            }catch(const std::exception& e)
            {
                std::cout << "CSVReader::readCSV bad data"  << std::endl;
                std::cout << e.what() << std::endl;
                throw;
            }
        }// end of while
    } 

    std::cout << "CSVReader::readCSV read " << entries.size() << " entries"  << std::endl;
    return entries; 
}


std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
   std::vector<std::string> tokens;
   signed int start, end;
   std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    do{
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end) break;
        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
    start = end + 1;
    }while(end > 0);

   return tokens; 
}

WeatherObservation CSVReader::stringsToObservationData(std::vector<std::string> tokens, const std::vector<std::string>& countryCodes)
{
    std::unordered_map<std::string, double> tempData;
    for (unsigned int i = 1; i < tokens.size(); ++i)
    {
        try {
            tempData[countryCodes[i-1]] = std::stod(tokens[i]); //initialise the map with country codes and temperatures, i-1 because the first token is the timestamp
        }catch(const std::exception& e){
            std::cout << "CSVReader::stringsToDataPoint Bad float! " << tokens[i]<< std::endl;
            throw;        
        }
    }
    return WeatherObservation{tokens[0], tempData};
}

std::vector<std::string> CSVReader::parseCountryCodes (std::vector<std::string> tokens) //**own code addepted from tokenise function
{
    signed int start, end;
    std::string token;
    std::vector<std::string> codes;
    for (unsigned int i = 1; i < tokens.size(); ++i)
    {
        do{
        start = tokens[i].find_first_not_of("_", 0);
        end = tokens[i].find_first_of("_", start);
        if (start == tokens[i].length() || start == end) break; //check if the token is empty
        if (end >= 0) token = tokens[i].substr(start, end - start); 
        else token = tokens[i].substr(start, tokens[i].length() - start); //if token is not empty parse the coutry code
        codes.push_back(token);
        }while(end < 2);
    }
    return codes;
}
     