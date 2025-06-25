/*All code in this file was written whitout help referencing 
to the course material on overloading operators*/
#include "WeatherObservation.h"


WeatherObservation::WeatherObservation(std::string _timeStamp, std::unordered_map<std::string, double> _temperatures)
    :   timeStamp(_timeStamp),
        temperatures(_temperatures)
{

}

std::ostream& operator<<(std::ostream& os, const WeatherObservation& dp) {
    std::string str = dp.timeStamp + " - ";
    auto it = dp.temperatures.begin();
    for (; it != dp.temperatures.end(); ++it) {
        if (std::next(it) == dp.temperatures.end()) {
            str += it->first + ": " + std::to_string(it->second);
        }
        else str += it->first + ": " + std::to_string(it->second) + ", ";
    }
    os << str;
    return os;
}