/*All code in this file was written without help, referring to cplusplus documentation*/
#include "PlottingChart.h"
#include "utilityFunctions.h"
#include "formattingConstants.h"
#include <iostream>
#include <tuple>

//All code is OWNCODE, unless otherwise stated

PlottingChart::PlottingChart(std::vector<CandleStick> _candleSticks, ChartType _chartType) 
    : candleSticks(_candleSticks), chartType(_chartType) 
{
        // Initialize the y-axis step
        yAxisTempRange = chartTempRange.second - chartTempRange.first; //calculate the temperature range
        yAxisStep = yAxisTempRange / rows;
}

void PlottingChart::plotChart() 
{
    //each row
    for (unsigned int i = 0; i < rows; ++i) {
        // Print the y-axis labels every other row
        printYaxisLabel(i);

        drawCandleSticks(i);
        std::cout << std::endl;
    }
    // Print the x-axis labels every other column
    printXaxisLabel(chartType);
}

void PlottingChart::printYaxisLabel(int rowIdx) 
{
    if (rowIdx%2 == 0) {
        UtilityFunctions::printFormattedDouble(chartTempRange.second - rowIdx * yAxisStep);
        std::cout << " " << formattingConstants::LIGHT_GREY_BACKGROUND << "  " << formattingConstants::RESET;
    } else {
        std::cout << std::string (6, ' ') 
                  << formattingConstants::WHITE_BACKGROUND 
                  << "  " << formattingConstants::RESET; //string constructor from cplusplus.com reference
    }
}

void PlottingChart::printXaxisLabel(ChartType chartType) 
{
    //offset to consider the y-axis labels
    unsigned int offset = 6;
    unsigned int offset2 = 2;
    std::string openLabel = "Open";
    std::string closeLabel = "Close";
    std::string highLabel = "High";
    std::string lowLabel = "Low";

    //checks if the chart type is yearly or monthly to print the x-axis labels
    if(chartType == ChartType::Yearly) 
    {
        //space before the x-axis labels
        std::cout << "\33[1mYear" << std::string (offset-4, ' ') 
                << formattingConstants::LIGHT_GREY_BACKGROUND 
                << std::string (2, ' ') 
                << formattingConstants::RESET;
        //print the x-axis labels          
        for (const CandleStick& cs : candleSticks)
        {
            std::cout << formattingConstants::LIGHT_GREY_BACKGROUND 
                    << formattingConstants::BOLD_TEXT << cs.getTimeStamp().substr(2, 4) 
                    << std::string (offset2, ' ') << formattingConstants::RESET;
        }
        if (offset2 + candleSticks.size() * 4 < cols) //check if the x-axis labels are shorter than the chart
        {
            std::cout << formattingConstants::LIGHT_GREY_BACKGROUND 
                    << std::string (cols - candleSticks.size() * 4, ' ') 
                    << formattingConstants::RESET;
        }
        std::cout << std::endl;
    }
    else if(chartType == ChartType::Monthly)
    {
        //space before the x-axis labels
        std::cout << "\33[1mMonth" << std::string (offset-5, ' ') 
                << formattingConstants::LIGHT_GREY_BACKGROUND 
                << std::string (offset2, ' ') 
                << formattingConstants::RESET;
        //print the x-axis labels          
        for (const CandleStick& cs : candleSticks)
        {
            std::string monthString = cs.getTimeStamp().substr(5, 2);
            std::cout << formattingConstants::LIGHT_GREY_BACKGROUND 
                    << formattingConstants::BOLD_TEXT << monthsMap.at(monthString) 
                    << std::string (1, ' ') << formattingConstants::RESET;
        }
        if (offset2 + candleSticks.size() * 4 < cols) //check if the x-axis labels are shorter than the chart
        {
            std::cout << formattingConstants::LIGHT_GREY_BACKGROUND 
                    << std::string (cols - candleSticks.size() * 4, ' ') 
                    << formattingConstants::RESET;
        }
        std::cout << std::endl;
        // line to separate the x-axis labels from the chart
        std::cout << std::string (offset, ' ');
        std::cout << formattingConstants::LIGHT_GREY_BACKGROUND << std::string (cols+offset2, '_') << formattingConstants::RESET << std::endl;
    }
    else
    {
        std::cout << "Invalid chart type" << std::endl;
    }

    //print the x-axis labels for the open, close, high, low
    //---space before OPEN LABEL
    std::cout << formattingConstants::BOLD_TEXT << openLabel << std::string (offset-openLabel.length(), ' ') 
              << formattingConstants::WHITE_BACKGROUND
              << std::string (1, ' ');
    //loop through the candlesticks
    for (const CandleStick& cs : candleSticks)
    {
        //print the open temp
        std::cout << formattingConstants::BOLD_TEXT;
        UtilityFunctions::printFormattedDoubleXAxis(cs.getOpenTemp());
        std::cout << formattingConstants::WHITE_BACKGROUND 
                  << std::string (1, ' ');
    }
    //space after the last open label
    std::cout << std::string (cols - 1 - candleSticks.size() * 4, ' ') + "  "
              << formattingConstants::RESET << std::endl;

    //---space before CLOSE LABEL
    std::cout << formattingConstants::BOLD_TEXT << closeLabel << std::string (offset-closeLabel.length(), ' ') 
              << formattingConstants::LIGHT_GREY_BACKGROUND
              << std::string (1, ' ');
    //loop through the candlesticks
    for (const CandleStick& cs : candleSticks)
    {
        //print the close temp
        std::cout << formattingConstants::BOLD_TEXT;
        UtilityFunctions::printFormattedDoubleXAxis(cs.getCloseTemp());
        std::cout << formattingConstants::LIGHT_GREY_BACKGROUND 
                  << std::string (1, ' ');
    }
    //space after the last open label
    std::cout << std::string (cols - 1 - candleSticks.size() * 4, ' ') + "  "
              << formattingConstants::RESET << std::endl;

    //---space before HIGH LABEL
    std::cout << formattingConstants::GREEN_FOREGROUND
              << formattingConstants::BOLD_TEXT << highLabel 
              << std::string (offset-highLabel.length(), ' ') 
              << formattingConstants::WHITE_BACKGROUND
              << std::string (1, ' ');
    //loop through the candlesticks
    for (const CandleStick& cs : candleSticks)
    {
        //print the high temp
        std::cout << formattingConstants::BOLD_TEXT;
        UtilityFunctions::printFormattedDoubleXAxis(cs.getHighTemp());
        std::cout << formattingConstants::WHITE_BACKGROUND 
                  << std::string (1, ' ');
    }
    //space after the last open label
    std::cout << std::string (cols - 1 - candleSticks.size() * 4, ' ') + "  "
              << formattingConstants::RESET << std::endl;
    
    //---space before LOW LABEL
    std::cout << formattingConstants::RED_FOREGROUND
              << formattingConstants::BOLD_TEXT << lowLabel << std::string (offset-lowLabel.length(), ' ') 
              << formattingConstants::LIGHT_GREY_BACKGROUND
              << std::string (1, ' ');
    //loop through the candlesticks
    for (const CandleStick& cs : candleSticks)
    {
        //print the low temp
        std::cout << formattingConstants::BOLD_TEXT;
        UtilityFunctions::printFormattedDoubleXAxis(cs.getLowTemp());
        std::cout << formattingConstants::LIGHT_GREY_BACKGROUND 
                  << std::string (1, ' ');
    }
    //space after the last open label
    std::cout << std::string (cols - 1 - candleSticks.size() * 4, ' ') + "  "
              << formattingConstants::RESET << std::endl;
}

void PlottingChart::drawCandleSticks(int rowIdx)
{
    //variables for the temperature range within the current row
    double currentTemp = chartTempRange.second - rowIdx * yAxisStep; //current temp based on the row index
    double currentMidTemp = currentTemp - yAxisStep/2; //mid temp of the current line range
    double nextTemp = currentTemp - yAxisStep; //next temp based on the row index
    int printedCols = candleSticks.size() * 4; //number of columns printed each candle is 4 spaces wide
    //set up alternating row color
    std::string rowColor;
    if (rowIdx % 2 == 0)
    {
        rowColor = formattingConstants::LIGHT_GREY_BACKGROUND;
    }
    else
    {
        rowColor = formattingConstants::WHITE_BACKGROUND;
    }
    // bool emptyLine = true; //flag for empty line

    for (unsigned int i = 0; i < candleSticks.size(); ++i)
    {
        bool isStick = false;
        //set up the red candlestick
        if(candleSticks[i].getOpenTemp() > candleSticks[i].getCloseTemp()) 
        {
            // print stick
            if (nextTemp <= candleSticks[i].getHighTemp() && nextTemp > candleSticks[i].getOpenTemp())
            {
                std::cout << rowColor;
                std::cout << " " << formattingConstants::RED_FOREGROUND << formattingConstants::CANDLESTICK << "  " << formattingConstants::RESET;
                isStick = true;
            }
            if (currentTemp >= candleSticks[i].getLowTemp() && currentTemp < candleSticks[i].getCloseTemp())
            {
                std::cout << rowColor;
                std::cout << " " << formattingConstants::RED_FOREGROUND << formattingConstants::CANDLESTICK << "  " << formattingConstants::RESET;
                isStick = true;
            }

            //print body
            if (nextTemp < candleSticks[i].getOpenTemp() && currentTemp > candleSticks[i].getCloseTemp())
            {
                if (currentMidTemp > candleSticks[i].getOpenTemp())
                {
                    std::cout << rowColor
                          << formattingConstants::RED_FOREGROUND << std::string (3, char(220)) //ascii code for low half block
                          << formattingConstants::RESET << rowColor
                          << " "
                          << formattingConstants::RESET;
                }
                else if (currentMidTemp < candleSticks[i].getCloseTemp())
                {
                    std::cout << rowColor
                          << formattingConstants::RED_FOREGROUND << std::string (3, char(223)) //ascii code for high half block
                          << formattingConstants::RESET << rowColor
                          << " "
                          << formattingConstants::RESET;
                }
                else
                {
                    std::cout << formattingConstants::RED_BACKGROUND 
                            << "   " << formattingConstants::RESET
                            << rowColor
                            << " "
                            << formattingConstants::RESET;
                }
            } else if (isStick == false)
            {
                std::cout << rowColor  //prints empty block
                        << std::string (4, ' ') 
                        << formattingConstants::RESET;
            }

        }
        else if (candleSticks[i].getOpenTemp() == candleSticks[i].getCloseTemp()) 
        {
            std::cout << rowColor  //prints empty line
                          << char(196) //prints horizontal line
                          << formattingConstants::RESET;

        }
        //set up the green candlestick
        else if (candleSticks[i].getOpenTemp() < candleSticks[i].getCloseTemp())
        {
            // print stick
            isStick = false;
            if (nextTemp <= candleSticks[i].getHighTemp() && nextTemp > candleSticks[i].getCloseTemp())
            {
                std::cout << rowColor;
                std::cout << " " << formattingConstants::GREEN_FOREGROUND << formattingConstants::CANDLESTICK << "  " << formattingConstants::RESET;
                isStick = true;
            }
            if (currentTemp >= candleSticks[i].getLowTemp() && currentTemp < candleSticks[i].getOpenTemp())
            {
                std::cout << rowColor;
                std::cout << " " << formattingConstants::GREEN_FOREGROUND <<formattingConstants::CANDLESTICK << "  " << formattingConstants::RESET;
                isStick = true;
            }

            //print body
            if (nextTemp < candleSticks[i].getCloseTemp() 
                && currentTemp >= candleSticks[i].getOpenTemp())
            {
                if (currentMidTemp > candleSticks[i].getCloseTemp())
                {
                    std::cout << rowColor
                          << formattingConstants::GREEN_FOREGROUND << std::string (3, char(220)) //ascii code for low half block
                          << formattingConstants::RESET << rowColor
                          << " "
                          << formattingConstants::RESET;
                }
                else if (currentMidTemp < candleSticks[i].getOpenTemp())
                {
                    std::cout << rowColor
                          << formattingConstants::GREEN_FOREGROUND << std::string (3, char(223)) //ascii code for high half block
                          << formattingConstants::RESET << rowColor
                          << " "
                          << formattingConstants::RESET;
                }
                else
                {
                    std::cout << formattingConstants::GREEN_BACKGROUND 
                            << "   " << formattingConstants::RESET
                            << rowColor
                            << " "
                            << formattingConstants::RESET;
                }
            }
            else if (isStick == false)
            {
                std::cout << rowColor  //prints empty block
                          << std::string (4, ' ') 
                          << formattingConstants::RESET;
            }
        }
    }
    //print remaining cols of lines
    std::cout << rowColor  //prints empty line
              << std::string (cols - printedCols, ' ') 
              << formattingConstants::RESET;
}