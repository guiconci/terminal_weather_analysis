//Used Merkel Main file as a template
/*Reference to user ipnut check in the getUserOption
- https://stackoverflow.com/questions/12721911/c-how-to-verify-if-the-data-input-is-of-the-correct-datatype
 Reference to the std::string::compare
 - https://cplusplus.com/reference/string/string/compare/ */

#include "ThermoCandle.h"
#include "PlottingChart.h"
#include "CandleSticksColletion.h"
#include "formattingConstants.h"
#include "WeatherPrediction.h"
#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <iomanip> // std::setw

ThermoCandle::ThermoCandle() 
: observationBook{"weather_data_EU_1980-2019_temp_only.csv"}
{

}

void ThermoCandle::init() 
{
    int input;

     while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void ThermoCandle::printMenu() {
    std::cout << formattingConstants::BOLD_TEXT;
    std::cout << "__________________________________" << std::endl;
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 analyze monthly weather
    std::cout << "2: Analyze Monthly Weather" << std::endl;
    // 3 analyze yearly weather
    std::cout << "3: Analyze Yearly Weather" << std::endl;
    // 4 make weather prediction
    std::cout << "4: Make Weather Prediction" << std::endl;
    // 5 exit
    std::cout << "5: Exit " << std::endl;
    std::cout << "__________________________________" << std::endl;
    std::cout << formattingConstants::RESET;
}

void ThermoCandle::printHelp() {
    //print help for weather analysis app
    std::cout << formattingConstants::BOLD_TEXT << formattingConstants::LIGHT_BLUE_FOREGROUND
              << "Help - This program allows you to analyze monthly and yearly weather data and make predictions. " 
              << std::endl 
              << "For the following countries:" << std::endl;
    const std::unordered_map<std::string, double>& obsEntry = observationBook.
                                                               getWeatherObservations()[0].getTemperaturesMap();
    int i = 1; //counter for the loop
    for (const std::pair<std::string, double>& element : obsEntry) {
        std::cout << std::setw(3) << element.first; //format width for countries but not first in line
        if (i % 6 == 0 && i > 0) std::cout << std::endl;
        i++;
    }
    std::cout << formattingConstants::RESET << std::endl;
}

void ThermoCandle::analyzeMonthlyWeather() {
    //analyze monthly weather data
    std::string inputYear;
    std::string inputCountry;
    std::string input;
    bool yearFound;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line - from Topic 4 example
    while(true)
    {
        try {
            std::cout << formattingConstants::BOLD_TEXT << formattingConstants::LIGHT_BLUE_FOREGROUND 
            << "Enter a year in the format YYYY. Exemple: 1993" <<std::endl
            << "Enter 0 to return to menu at any time." << formattingConstants::RESET <<std::endl;

            std::getline(std::cin, inputYear); // Get the user input
            if(inputYear == "0") {std::cout << formattingConstants::RESET; return;} //return to menu

            //check if the input is a valid year
            if(inputYear.length() != 4)
            {
                std::cout << formattingConstants::RED_FOREGROUND 
                            << "Please enter a valid year." << formattingConstants::RESET << std::endl;
                continue;
            }
            //check if the year is in the range of the data
            yearFound = false;
            for(const WeatherObservation& obs : observationBook.getWeatherObservations())
            {
                if(obs.getTimeStamp().substr(0,4).compare(inputYear) == 0) //used cplusplus reference
                {
                    yearFound = true; // Matching year found
                    break;
                }
            }
            if(!yearFound)
            {
                std::cout << formattingConstants::RED_FOREGROUND 
                        << "Year not in range" << formattingConstants::RESET << std::endl;
                continue;
            }

            //handles country code input
            std::cout << formattingConstants::BOLD_TEXT << formattingConstants::LIGHT_BLUE_FOREGROUND 
                << "Enter a country code with two letters. Example: NL" << std::endl;

            std::getline(std::cin, inputCountry); // Get the user input
            if(inputCountry == "0") {std::cout << formattingConstants::RESET; return;} //return to menu

            //compute monthly candlestick
            CandleSticksCollection csCollect;
            csCollect.computeCandleStick(observationBook.getWeatherObservations(), inputCountry, inputYear, ChartType::Monthly);
            std::vector<CandleStick> w = csCollect.getCandleSticks();
            //loop menu
            while(true)
            {
                //select the type of data to print
                std::cout << formattingConstants::BOLD_TEXT << formattingConstants::LIGHT_BLUE_FOREGROUND 
                        << std::endl << "Type 1 to print data table." << std::endl
                        << "Type 2 to print chart." << std::endl
                        << "Type 0 to back to menu." << std::endl << std::endl << formattingConstants::RESET;
            
            
                std::getline(std::cin, input); // Get the user input
            
                if (input == "1") std::cout << w << std::endl;
                else if (input == "2") 
                {
                        //display chart info
                        std::cout<< std::string(30, ' ') << formattingConstants::BOLD_TEXT 
                                                        <<"Displaying month0ly temperatures chart for " 
                                                        << csCollect.getCountryCode() <<std::endl;
                        //plot the chart
                        PlottingChart pc(w, ChartType::Monthly);
                        pc.plotChart();
                } 
                else if (input == "0") return;
                else std::cout << formattingConstants::BOLD_TEXT << formattingConstants::RED_FOREGROUND 
                               << "Invalid input. Please enter 1, 2 or 3." << std::endl;
            }
        }catch(const std::invalid_argument& ia){
            std::cout << formattingConstants::BOLD_TEXT << formattingConstants::RED_FOREGROUND 
                    <<"Invalid argument: " << ia.what() << formattingConstants::RESET << std::endl;
        }catch(const std::exception& e){}
    }
}

void ThermoCandle::analyzeYearlyWeather() {
    std::string inputCountry;
    std::string inputYear;
    std::string input;

    //handles year input
    std::cout << formattingConstants::BOLD_TEXT << formattingConstants::LIGHT_BLUE_FOREGROUND 
              << "Enter a range of years in the format YYYY-YYY. Exemple: 1993-2000" << std::endl
              << "Enter 0 to return to menu at any time." << formattingConstants::RESET <<std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
    while (true)
    {
        try{
            std::getline(std::cin, inputYear); // Get the user input
            //validates the input year range
            if(inputYear == "0") {std::cout << formattingConstants::RESET; return;} //return to menu
            else if (inputYear.length() < 9)
            {
                std::cout << formattingConstants::BOLD_TEXT << formattingConstants::RED_FOREGROUND
                        << "Invalid years range, the years range must be in the format: YYYY-YYYY, try again." 
                        << formattingConstants::RESET << std::endl;
                continue;
            }
            else if(inputYear.length() == 9)
            {
                //checks if the years range is valid
                if(inputYear[4] != '-')
                {
                    std::cout << formattingConstants::BOLD_TEXT << formattingConstants::RED_FOREGROUND 
                            << "Invalid years range, the years range must be in the format: YYYY-YYYY, try again."  
                            << formattingConstants::RESET <<std::endl;
                    continue;
                }
            // }
            // break;
            }
            //handles country code input
            std::cout << formattingConstants::BOLD_TEXT << formattingConstants::LIGHT_BLUE_FOREGROUND 
                    << "Enter a country code with two letters. Example: NL" << std::endl;
            std::getline(std::cin, inputCountry); // Get the user input
            if(inputCountry == "0") {std::cout << formattingConstants::RESET; return;} //return to menu
            //Checks if country code is valid
            if (inputCountry.length() != 2)
            {
                std::cout << formattingConstants::BOLD_TEXT << formattingConstants::RED_FOREGROUND 
                          << "Invalid country code, the country code must be 2 characters long"
                          << formattingConstants::RESET <<std::endl;
                std::cout << formattingConstants::BOLD_TEXT << formattingConstants::LIGHT_BLUE_FOREGROUND 
                          << "Enter a range of years in the format YYYY-YYY. Exemple: 1993-2000" << std::endl
                          << "Enter 0 to return to menu at any time." << formattingConstants::RESET <<std::endl;
                continue;
            }

            //compute yearly candlestick
            CandleSticksCollection csCollect;
            csCollect.computeCandleStick(observationBook.getWeatherObservations(), inputCountry, inputYear, ChartType::Yearly);
            std::vector<CandleStick> w = csCollect.getCandleSticks();


            
            while(true)
            {
                //select the type of data to print
                std::cout << formattingConstants::BOLD_TEXT << formattingConstants::LIGHT_BLUE_FOREGROUND 
                        << std::endl << "Type 1 to print data table." << std::endl
                        << "Type 2 to print chart." << std::endl
                        << "Type 0 to back to menu." << std::endl << std::endl << formattingConstants::RESET;

                std::getline(std::cin, input); // Get the user input

                if (input == "1") std::cout << w << std::endl;
                else if (input == "2") 
                {
                    //display chart info
                    std::cout<< std::string(30, ' ') << formattingConstants::BOLD_TEXT 
                                                    <<"Displaying yearly temperatures chart for " 
                                                    << csCollect.getCountryCode() <<std::endl;
                    //plot the chart
                    PlottingChart pc(w, ChartType::Yearly);
                    pc.plotChart();
                } 
                else if (input == "0") return;
                else std::cout << formattingConstants::BOLD_TEXT << formattingConstants::RED_FOREGROUND 
                               << "Invalid input. Please enter 1, 2 or 3." << std::endl;
            }
        }catch(const std::invalid_argument& ia){
            std::cout << formattingConstants::BOLD_TEXT << formattingConstants::RED_FOREGROUND 
                    <<"Invalid argument: " << ia.what() << formattingConstants::RESET <<std::endl;
            std::cout << formattingConstants::BOLD_TEXT << formattingConstants::LIGHT_BLUE_FOREGROUND 
              << "Enter a range of years in the format YYYY-YYY. Exemple: 1993-2000" << std::endl
              << "Enter 0 to return to menu at any time." << formattingConstants::RESET <<std::endl;
        }
    }
}

void ThermoCandle::makeWeatherPrediction() {
    //make weather prediction
    std::cout << formattingConstants::BOLD_TEXT << formattingConstants::LIGHT_BLUE_FOREGROUND 
              << "Making Weather Prediction" << std::endl;
    //initialize input variables;
    std::string inputCountry;
    std::string inputDate;
    std::string input;
    std::string lastDateonData = observationBook.getWeatherObservations().back().getTimeStamp();

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
    //checks date input
    while(true)
    {
        try{
            std::cout << formattingConstants::BOLD_TEXT << formattingConstants::LIGHT_BLUE_FOREGROUND 
              << "To predict te weather for a certain day in a country," << std::endl
              << "enter a date in the format YYYY-MM-DD. Exemple: 2024-07-01" << std::endl
              << "Enter 0 to return to menu at any time." << formattingConstants::RESET <<std::endl;

            //get the date input
            std::getline(std::cin, inputDate); // Get the user input
            if(inputDate == "0") {std::cout << formattingConstants::RESET; return;} //return to menu

            //check if the input is a valid date
            if(inputDate.length() != 10)
            {
                std::cout << formattingConstants::RED_FOREGROUND 
                        << "Please enter a valid date." << formattingConstants::RESET << std::endl;
                continue;
            }
            //check if prediction is above the last date in the data set
            if (inputDate < lastDateonData)
            {
                std::cout << formattingConstants::RED_FOREGROUND 
                          << "Prediction date must be above: " + lastDateonData.substr(0, 10) + ", the last date in the data set"
                          << formattingConstants::RESET << std::endl;
                continue;
            }
            //tokenize the date to check if it is a valid date
            std::vector<std::string> tokens = CSVReader::tokenise(inputDate, '-');
            if (tokens.size() != 3)
            {
                std::cout << formattingConstants::RED_FOREGROUND 
                        << "Please enter a valid date." << formattingConstants::RESET << std::endl;
                continue;
            }
            //check if the date is valid
            if (tokens[0].length() != 4 || tokens[1].length() != 2 || tokens[2].length() != 2)
            {
                std::cout << formattingConstants::RED_FOREGROUND 
                        << "Please enter a valid date." << formattingConstants::RESET << std::endl;
                continue;
            }


            //handles country code input
            std::cout << formattingConstants::BOLD_TEXT << formattingConstants::LIGHT_BLUE_FOREGROUND 
                      << "Enter a country code with two letters. Example: NL" 
                      << formattingConstants::RESET <<std::endl;

            std::getline(std::cin, inputCountry); // Get the user input
            if(inputDate == "0") {std::cout << formattingConstants::RESET; return;} //return to menu

            //check if the country code is valid
            if (inputCountry.length() != 2)
            {
                std::cout << formattingConstants::RED_FOREGROUND 
                        << "Please enter a valid country code." << formattingConstants::RESET << std::endl;
                std::cin.clear(); // Clear the error flags
                continue;
            }
            //checks if the country code is in the data set
            if (observationBook.getWeatherObservations()[0].getTemperaturesMap().find(inputCountry) == 
                observationBook.getWeatherObservations()[0].getTemperaturesMap().end())
            {
                std::cout << formattingConstants::RED_FOREGROUND 
                        << "Country code not in data set." << formattingConstants::RESET << std::endl;
                        std::cin.clear(); // Clear the error flags
                continue;
            }


            //make the prediction
            WeatherPrediction wp(observationBook.getWeatherObservations(), inputCountry);
            bool dataMatch = wp.predictWeather(inputDate);
            if(dataMatch)
            {
                std::cout << formattingConstants::BOLD_TEXT << formattingConstants::LIGHT_BLUE_FOREGROUND << std::endl 
                        << "Weather prediction for " << inputDate << " in " << inputCountry << std::endl
                        << "Open temperature: " << wp.getOpenTempPrediction() << std::endl
                        << "High temperature: " << wp.getHighTempPrediction() << std::endl
                        << "Low temperature: " << wp.getLowTempPrediction() << std::endl
                        << "Close temperature: " << wp.getCloseTempPrediction() << std::endl << formattingConstants::RESET;
                        return;
            }
            else
            {
                std::cout << formattingConstants::BOLD_TEXT << formattingConstants::RED_FOREGROUND 
                        << "No data found for " << inputDate << " in " << inputCountry 
                        << formattingConstants::RESET << std::endl;
                std::cin.clear(); // Clear the error flags
            }
        }catch(const std::exception& e){
            std::cout << formattingConstants::BOLD_TEXT << formattingConstants::RED_FOREGROUND 
                    <<"Exception thrown: " << e.what() << formattingConstants::RESET <<std::endl;
        }
    }


    
}

void ThermoCandle::exit() {
    //exit the program
    std::cout << "Exiting Program" << std::endl;
    std::exit(0);
}

int ThermoCandle::getUserOption() {
    int userOption;

    std::cout << "Enter an option: ";
    std::cin >> userOption;
    /*This part was written referencing to stack overflow*/
    if (std::cin.fail()) { // Check if the input operation failed from stackoverflow reference above
            std::cin.clear(); // Clear the error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
            std::cout << "Invalid input. Please enter a number." << std::endl;
            return 0;
    } else return userOption; // Return the valid input
    /*End part written with help*/
}

void ThermoCandle::processUserOption(int userOption) {
    std::map<int, void(ThermoCandle::*)()> menu; //own code from class example
    //connects 1 to help
    menu[1] = printHelp;
    //connects 2 to analyzeMonthlyWeather
    menu[2] = analyzeMonthlyWeather;
    //connects 3 to analyzeYearlyWeather
    menu[3] = analyzeYearlyWeather;
    //connects 4 to makeWeatherPrediction
    menu[4] = makeWeatherPrediction;
    //connects 5 to exit
    menu[5] = exit;

    // call the function that corresponds to the userOption
	if (menu.count(userOption) > 0) {
		(this->*menu[userOption])();
	}
	else {
		std::cout << formattingConstants::BOLD_TEXT << formattingConstants::RED_FOREGROUND 
                  << "=========== Invalid option. Choose 1-5 ==========="
                  << formattingConstants::RESET << std::endl;
	}
}