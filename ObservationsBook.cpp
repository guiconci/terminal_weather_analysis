/*The code in this file was written without help*/
#include "ObservationsBook.h"
#include <unordered_map>
#include <iostream>

ObservationsBook::ObservationsBook(std::string fileName)
{
    weatherObservations = CSVReader::readCSV(fileName);
}

double ObservationsBook::firstYearOpenTemp(const std::vector<WeatherObservation>& weatherObservations, 
                                        const std::string& countryCode, 
                                        const std::string& firstYear)
{
    //calculate the previous year and turn into string
    std::string previousYear = std::to_string(std::stoi(firstYear) - 1); 
    //parse first year start and january end into correct format
    std::string yearStart = firstYear + "-01-01T00:00:00Z";
    std::string firstMonthEnd = firstYear + "-01-31T23:00:00Z";
    //initialise variables
    std::string currentTimeStamp = weatherObservations[0].getTimeStamp();
    double openTemp = 0;

    if (yearStart == currentTimeStamp) //if the first year is the first data point, there's no previous year 
                                              //so use the first month average temp.
    {
        unsigned int i = 0; //counter for the while loop
        while (true)
        {
            if (currentTimeStamp > firstMonthEnd) break; //break in the end of the first month
            openTemp += weatherObservations[i].getTemperature(countryCode); // sum temperatures for the first month
            ++i;
            currentTimeStamp = weatherObservations[i].getTimeStamp();
        }
        openTemp = openTemp/i; //calculate the mean temperature
    }
    else //if the first year is not the first data point
    {
        unsigned int j = 0; //counter for weatherObservations within the previous year

        for (unsigned int i = 0; i < weatherObservations.size(); ++i)
        {
            if (weatherObservations[i].getTimeStamp() < previousYear + "-01-01T00:00:00Z") continue; //skip entries before the previous year
            else if (weatherObservations[i].getTimeStamp() >= previousYear + "-01-01T00:00:00Z" && 
                    weatherObservations[i].getTimeStamp() <= previousYear + "-12-31T23:00:00Z") //if the entry is in the previous year
            {
                openTemp += weatherObservations[i].getTemperature(countryCode); //sum temperatures
                ++j; //counter
            }
            else if (weatherObservations[i].getTimeStamp() > previousYear + "-12-31T23:00:00Z") 
            {
                openTemp = openTemp/j; //calculate the mean temperature
                break; //break after the previous year
            }
        }
    }
    return openTemp;
}

double ObservationsBook::firstMonthOpenTemp(const std::vector<WeatherObservation>& weatherObservations, 
                                        const std::string& countryCode, 
                                        const std::string& year)
{
    //initialize variables
    std::string previousYear = std::to_string(std::stoi(year) - 1);
    std::string dataFirstYear = weatherObservations[0].getTimeStamp().substr(0,4);
    std::string yearStart = year + "-01-01T00:00:00Z";
    std::string firstMonthEnd = year + "-01-31T23:00:00Z";
    double openTemp = 0;

    //if the first year is the same as the year of the first data point
    if (year == dataFirstYear)
    {
        //calculate the first month average temperature
        unsigned int i = 0;
        while (true)
        {
            if (weatherObservations[i].getTimeStamp() > firstMonthEnd) break;
            openTemp += weatherObservations[i].getTemperature(countryCode);
            ++i;
        }
        openTemp = openTemp/i;
    }
    else //calculate average temperature december of the previous year
    {
        unsigned int j = 0;
        for (unsigned int i = 0; i < weatherObservations.size(); ++i)
        {
            if (weatherObservations[i].getTimeStamp() < previousYear + "-12-01T00:00:00Z") continue;
            else if (weatherObservations[i].getTimeStamp() >= previousYear + "-12-01T00:00:00Z" && 
                    weatherObservations[i].getTimeStamp() <= previousYear + "-12-31T23:00:00Z")
            {
                openTemp += weatherObservations[i].getTemperature(countryCode);
                ++j;
            }
            else if (weatherObservations[i].getTimeStamp() > previousYear + "-12-31T23:00:00Z")
            {
                openTemp = openTemp/j;
                break;
            }
        }
    }
    return openTemp;
}

double ObservationsBook::firstDayOpenTemp(const std::vector<WeatherObservation>& weatherObservations, 
                                        const std::string& countryCode)
{
    //calculate the average temperature of the first day
    double openTemp = 0;
    //define the first day start and end times
    std::string firstDayStart = weatherObservations[0].getTimeStamp().substr(0,10) + "T00:00:00Z"; 
    std::string firstDayEnd = weatherObservations[0].getTimeStamp().substr(0,10) + "T23:00:00Z";
    //iterate through the weather observations
    int i = 0; //counter
    for (WeatherObservation ob : weatherObservations)
    {
        if (ob.getTimeStamp() > firstDayEnd) break;
        openTemp += ob.getTemperature(countryCode);
        ++i;
    }
    openTemp = openTemp/i;
    return openTemp;
}

/*This function was used to calculate the max difference in temps to decide the range of the chart Y axis*/
const std::unordered_map<std::string, double> ObservationsBook::computeTempDifferencePerCountry(std::vector<WeatherObservation> obs)
{
    //check for every country in the observation all the lines in the book
    //store max and min temperatures for each country
    //and calculate the difference
    std::unordered_map<std::string, double> tempDiff;
    std::unordered_map<std::string, std::vector<double>> tempData;
    for (WeatherObservation ob: obs)
    {
        for (auto& tempPair : ob.getTemperaturesMap())
        {
            std::string country = tempPair.first;
            double temp = tempPair.second;

            if (tempData.find(country) == tempData.end())
            {
                tempData[country] = {temp, temp};
            }
            else
            {
                if (temp > tempData[country][0]) tempData[country][0] = temp;
                if (temp < tempData[country][1]) tempData[country][1] = temp;
            }
        }
    }
    for (auto& tempPair : tempData)
    {
        tempDiff[tempPair.first] = tempPair.second[0] - tempPair.second[1];
    }
    return tempDiff;
}
