/*All code in this file was written whitout help referencing 
to the course material on overloading operators*/
#pragma once
#include <string>
#include <unordered_map>

class WeatherObservation
{
    public:
        /**  Constructor for single DataPoint class*/
        WeatherObservation(std::string _timeStamp, std::unordered_map<std::string, double> _temperatures);

        //Access functions
        /**  Function to get the timestamp of the DataPoint instance*/
        std::string getTimeStamp() const {return timeStamp;};

        /**  Function to get the temperature of a specific country of the DataPoint instance*/
        double getTemperature(const std::string& countryCode) const {return temperatures.at(countryCode);};

        /**  Function to get the temperatures map of the DataPoint instance*/
        const std::unordered_map<std::string, double>& getTemperaturesMap() const {return temperatures;}    
    private:
        /**  Variables for DataPoint class*/
        std::string timeStamp;

        /** include all country codes as keys for the map*/
        std::unordered_map<std::string, double> temperatures;

        /** Overload << operator to print DataPoint instances*/ 
        friend std::ostream& operator<<(std::ostream& os, const WeatherObservation& dp);
};