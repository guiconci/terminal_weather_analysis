#pragma once
#include <string>
#include <iostream>
//Escpe sequences and character codes were taken from
//https://en.wikipedia.org/wiki/ANSI_escape_code
//https://www.asciitable.com/
//https://www.ascii-code.com/

namespace formattingConstants 
{   
    const std::string RESET = "\033[0m";
    const std::string RED_BACKGROUND = "\033[101m";
    const std::string LIGHT_GREY_BACKGROUND = "\033[47m";
    const std::string WHITE_BACKGROUND = "\033[107m";
    const std::string GREEN_BACKGROUND = "\033[102m";
    const std::string RED_FOREGROUND = "\033[91m";
    const std::string GREEN_FOREGROUND = "\033[92m";
    const std::string LIGHT_BLUE_FOREGROUND = "\33[94m";
    const std::string BOLD_TEXT = "\033[1m";
    const std::string UNDERLINE_TEXT = "\033[4m";
    const std::string CANDLESTICK = "|"; // Candlestick representation
}