#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "CSVReader.h"
#include "CandleStick.h"
#include "WeatherObservation.h"
#include "ObservationsBook.h"
#include "CandleSticksColletion.h"
#include "utilityFunctions.h"
#include "formattingConstants.h"
#include "PlottingChart.h"
#include "ThermoCandle.h"
#include "WeatherPrediction.h"
#include <iomanip>

int main()
{   
    // welcome message
    std::cout << formattingConstants::BOLD_TEXT << formattingConstants::GREEN_FOREGROUND 
              << "+-+-+-+-+-+-+-+- WELCOME TO THE THERMOCANDLE APP +-+-+-+-+-+-+-+-" << std::endl
              << "LOADING CSV FILE... THIS MAY TAKE A WHILE" << formattingConstants::RESET << std::endl;

    // MerkelMain app{};
    // app.init();
    try{
        ThermoCandle app{};
        app.init();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;

    //experimental printing on terminal
    // std::cout << formattingConstants::LIGHT_GREY_BACKGROUND;
    // std::cout << " " << "\033[4;38;5;198m" << char(179) << formattingConstants::RESET << formattingConstants::LIGHT_GREY_BACKGROUND << "   " ;
    // std::cout << "\033[38;5;198m" <<  char(193) << formattingConstants::RESET << std::endl;
    // std::cout << formattingConstants::LIGHT_GREY_BACKGROUND;
    // std::cout << "\033[4;38;5;198m" <<  std::string(3, char(220)) << formattingConstants::RESET << formattingConstants::LIGHT_GREY_BACKGROUND << " ";
    // std::cout << "\033[38;5;198m" <<  std::string(3, char(219)) << formattingConstants::RESET << std::endl;
    // std::cout << formattingConstants::LIGHT_GREY_BACKGROUND;
    // std::cout << "\033[38;5;198m" <<  char(223) << "\033[4;38;5;198m" << char(223) << formattingConstants::RESET << "\033[47;38;5;198m" <<  char(223) << formattingConstants::RESET << formattingConstants::LIGHT_GREY_BACKGROUND << " " ;
    // std::cout << "\033[38;5;198m" <<  std::string(3, char(219)) << formattingConstants::RESET << std::endl;
    // std::cout << formattingConstants::LIGHT_GREY_BACKGROUND;
    // std::cout << " " << "\033[38;5;198m" <<  char(179) << formattingConstants::RESET << formattingConstants::LIGHT_GREY_BACKGROUND << "   " ;
    // std::cout << "\033[38;5;198m" <<  char(194) << formattingConstants::RESET << std::endl;
    // std::cout << " " << "\033[38;5;198m" <<  char(179) << formattingConstants::RESET << formattingConstants::LIGHT_GREY_BACKGROUND << "   " ;
    // std::cout << "\033[38;5;198m" <<  char(179) << formattingConstants::RESET << std::endl;
}




