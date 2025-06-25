/*The code in this file was written without help*/
#include "CandleSticksColletion.h"
#include "ObservationsBook.h"
#include <iostream>

CandleSticksCollection::CandleSticksCollection()
{

};

void CandleSticksCollection::computeCandleStick(const std::vector<WeatherObservation>& weatherObservations, 
                            const std::string& countryCode, 
                            const std::string& timeRange, 
                            ChartType charType)
{
    if (charType == ChartType::Yearly) {
        candleSticks = computeYearlyCandleStick(weatherObservations, countryCode, timeRange);
    } else if (charType == ChartType::Monthly) {
        candleSticks = computeMonthlyCandleStick(weatherObservations, countryCode, timeRange);
    } else {
        // Handle invalid period argument
        throw std::invalid_argument("Invalid period argument. Must be 'yearly' or 'monthly'.");
    }

    // Set the country code
    this->countryCode = countryCode;
}

std::vector<CandleStick> CandleSticksCollection::getCandleSticks() const
{
    return candleSticks;
}

std::string CandleSticksCollection::getCountryCode() const
{
    return countryCode;
}

std::vector<CandleStick> CandleSticksCollection::computeYearlyCandleStick(const std::vector<WeatherObservation>& weatherObservations, 
                                                                 const std::string& countryCode, 
                                                                 const std::string& yearsRange)
{
    //initialise variables
    std::vector<CandleStick> candleSticks{};
    double openTemp, highTemp = -1000.0, lowTemp = 1000.0, closeTemp;
    std::string firstYear = yearsRange.substr(0,4); //transform first year into int
    std::string secondYear = yearsRange.substr(5,4); //transform first year into int
    std::string yearRangeStart, yearRangeEnd, currentYear;
    bool firstYearFlag = true; //flag for the first year    

    //parse years range into correct format
    yearRangeStart = firstYear + "-01-01T00:00:00Z";
    yearRangeEnd = secondYear + "-12-31T23:00:00Z";

    // extract data from observation points within the year range
    unsigned int i = 0; //counter to track entries in a year
    currentYear = firstYear;
    try{
        if(weatherObservations[0].getTemperaturesMap().find(countryCode) 
                           == weatherObservations[0].getTemperaturesMap().end()) //check if the country code is valid
        {
            throw std::invalid_argument("Invalid country code, country not found");
        }
        //Check if the years range is in the correct format
        int intFirstYear, intSecondYear;
        try{
            intFirstYear = std::stoi(secondYear);
            intSecondYear = std::stoi(firstYear);
        } catch (const std::exception& e){
            throw std::invalid_argument("Invalid years range, the years range must be in the format: YYYY-YYYY");
        }

        //Check if the years range is valid
        if (firstYear > secondYear)
        {
            throw std::invalid_argument("Invalid years range, the start year is greater then the end year.");
        }
        if (firstYear == secondYear)
        {
            throw std::invalid_argument("Years range is too short");
        }
        if (intFirstYear - intSecondYear > 25)
        {
            throw std::invalid_argument("25 is the maximum year range.");
        }
        if (firstYear < weatherObservations.front().getTimeStamp().substr(0,4) || 
            secondYear > weatherObservations.back().getTimeStamp().substr(0,4))
        {
            std::cout << "Data start year: " << weatherObservations.front().getTimeStamp().substr(0,4) << std::endl;
            std::cout << "Data end year: " << weatherObservations.back().getTimeStamp().substr(0,4) << std::endl;
            throw std::invalid_argument("Years range is out of data range: " + firstYear + "-" + secondYear);
        }


        //iterates through observation points
        for (WeatherObservation ob: weatherObservations)
        {
            //check if the observation point is within input years range
            if (ob.getTimeStamp() >= yearRangeStart && ob.getTimeStamp() <= yearRangeEnd)
            {
                if (ob.getTimeStamp().substr(0,4) != currentYear || 
                    ob.getTimeStamp() == yearRangeEnd) //if the year changes
                {
                    //calculate the mean temperature for the year - close temperature
                    closeTemp = closeTemp/i;

                    //create a new candlestick
                    CandleStick candleStick{currentYear, openTemp, highTemp, lowTemp, closeTemp};
                    candleSticks.push_back(candleStick); //add the candlestick to the vector

                    openTemp = candleSticks.back().getCloseTemp(); ; //when year changes, copy the previous year close temp
                    closeTemp = 0; //reset close temperature
                    highTemp = -1000.0; //reset high temperature
                    lowTemp = 1000.0; //reset low temperature
                    i = 0; //reset counter
                    currentYear = ob.getTimeStamp().substr(0,4); //set current year to the next year
                }

                //set the open temperature for candlestick
                if (firstYearFlag) //open temperature for the first year
                {
                    currentYear = firstYear; //set the current year to the first year
                    openTemp = ObservationsBook::firstYearOpenTemp(weatherObservations, countryCode, firstYear);
                    firstYearFlag = false;
                }

                //set close temperature for candlestick
                closeTemp += ob.getTemperature(countryCode); //sum temperatures

                //set high temperature
                if (ob.getTemperature(countryCode) > highTemp) highTemp = ob.getTemperature(countryCode);

                //set low temperature
                if (ob.getTemperature(countryCode) < lowTemp) lowTemp = ob.getTemperature(countryCode);

                ++i; //counter
            }
        }
    }catch(const std::invalid_argument& ia) {
        // Handle invalid argument exceptions
        throw ia;
    }catch(const std::exception& e){
        std::cout << e.what() << std::endl;  
        std::cout << "Error in CandleStick::computeYearlyCandleStick" << std::endl;     
    }

    return candleSticks;
}


std::vector<CandleStick> CandleSticksCollection::computeMonthlyCandleStick(const std::vector<WeatherObservation>& weatherObservations, 
                                                                  const std::string& countryCode, 
                                                                  const std::string& year)
{
    //initialise variables
    std::vector<CandleStick> candleSticks{};
    double openTemp, highTemp = -1000.0, lowTemp = 1000.0, closeTemp;
    int daysInMonth = 0;
    std::string currentMonth = "01";
    bool firstMonthFlag = true; //flag for the first year    
    try{
        //checks if the years length is less than 4
        if (year.length() < 4)
        {
            // std::cout << "Invalid year, the year must be in the format: YYYY" << std::endl;
            throw std::invalid_argument("Invalid year, the year must be in the format: YYYY");
        }
        //Checks if country code is valid
        if (countryCode.length() != 2)
        {
            throw std::invalid_argument("Invalid country code, the country code must be 2 characters long");
        }
        if(weatherObservations[0].getTemperaturesMap().find(countryCode) 
                            == weatherObservations[0].getTemperaturesMap().end()) //check if the country code is valid
        {
            throw std::invalid_argument("Invalid country code, country not found");
        }
        for (const WeatherObservation& ob: weatherObservations)
        {
            if (ob.getTimeStamp().substr(0,4) == year)
            {
                if (firstMonthFlag) //open temperature for the first year
                {
                    openTemp = ObservationsBook::firstMonthOpenTemp(weatherObservations, countryCode, year);
                    firstMonthFlag = false;
                }

                if (ob.getTimeStamp().substr(5,2) != currentMonth || 
                    ob.getTimeStamp() == year + "-12-31T23:00:00Z") //if the month changes
                {
                    //calculate the mean temperature for the month - close temperature
                    closeTemp = closeTemp/daysInMonth;

                    //create a new candlestick
                    CandleStick candleStick{year + "-" + currentMonth, openTemp, highTemp, lowTemp, closeTemp};
                    candleSticks.push_back(candleStick); //add the candlestick to the vector

                    openTemp = candleSticks.back().getCloseTemp(); ; //when month changes, copy the previous month close temp
                    closeTemp = 0; //reset close temperature
                    highTemp = -1000.0; //reset high temperature
                    lowTemp = 1000.0; //reset low temperature
                    daysInMonth = 0; //reset counter
                    currentMonth = ob.getTimeStamp().substr(5,2); //set current month to the next month
                }

                //set close temperature for candlestick
                closeTemp += ob.getTemperature(countryCode); //sum temperatures

                //set high temperature
                if (ob.getTemperature(countryCode) > highTemp) highTemp = ob.getTemperature(countryCode);

                //set low temperature
                if (ob.getTemperature(countryCode) < lowTemp) lowTemp = ob.getTemperature(countryCode);

                ++daysInMonth; //counter         
            }
        }
    }catch(const std::invalid_argument& ia) {
        // Handle invalid argument exceptions
        throw ia;
    }catch(const std::exception& e){
        std::cout << e.what() << std::endl;  
        std::cout << "Error in CandleStick::computeMonthlyCandleStick" << std::endl;     
    }
    return candleSticks;
}

std::vector<CandleStick> CandleSticksCollection::computeDailyCandleStick(const std::vector<WeatherObservation>& weatherObservations, 
                                                                const std::string& countryCode)
{
    //initialise variables
    std::vector<CandleStick> candleSticks{};
    double openTemp, highTemp = -1000.0, lowTemp = 1000.0, closeTemp;
    std::string currentDay = "01";
    std::string currentYearMonth;
    bool firstDayFlag = true; //flag for the first year
    int daysInMonth = 0;

    try{
        for (const WeatherObservation& ob: weatherObservations)
        {
            if (firstDayFlag) //open temperature for the first year
            {
                openTemp = ObservationsBook::firstDayOpenTemp(weatherObservations, countryCode);
                currentYearMonth = ob.getTimeStamp().substr(0,7);
                firstDayFlag = false;
            }

            if (ob.getTimeStamp().substr(8,2) != currentDay || 
                ob.getTimeStamp() == weatherObservations.back().getTimeStamp()) //if day changes or the last day in data
            {
                //calculate the mean daily temperature - close temperature
                closeTemp = closeTemp/daysInMonth;

                //create a new candlestick
                CandleStick candleStick{currentYearMonth + '-' + currentDay, openTemp, highTemp, lowTemp, closeTemp};
                candleSticks.push_back(candleStick); //add the candlestick to the vector

                openTemp = candleSticks.back().getCloseTemp(); ; //when day changes, copy the previous month close temp
                closeTemp = 0; //reset close temperature
                highTemp = -1000.0; //reset high temperature
                lowTemp = 1000.0; //reset low temperature
                daysInMonth = 0; //reset counter
                currentYearMonth = ob.getTimeStamp().substr(0,7);
                currentDay = ob.getTimeStamp().substr(8,2); //set current month to the next month
            }

            //set close temperature for candlestick
            closeTemp += ob.getTemperature(countryCode); //sum temperatures

            //set high temperature
            if (ob.getTemperature(countryCode) > highTemp) highTemp = ob.getTemperature(countryCode);

            //set low temperature
            if (ob.getTemperature(countryCode) < lowTemp) lowTemp = ob.getTemperature(countryCode);

            ++daysInMonth; //counter         
        }
    }catch(const std::exception& e){
        std::cout << e.what() << std::endl;  
        std::cout << "Error in CandleStick::computeDailyCandleStick" << std::endl;     
    }
    return candleSticks;
}



