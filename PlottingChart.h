#pragma once
#include <vector>
#include "CandleStick.h"

enum class ChartType {Yearly, Monthly};

class PlottingChart {
    public:
        
        PlottingChart(std::vector<CandleStick> candleSticks, ChartType chartType);

        void plotChart();
    
    private:
        /** Initialize const number of rows (lines) and columns of the chart */
        int const rows = 40, cols = 105;

        /** Y axis variables */
        double yAxisStep, yAxisTempRange;

        /** Chart Type var */
        ChartType chartType;

        /** Range for y axis constant 
         * @param chartRange.first - minimum value
         * @param chartRange.second - maximum value
        */
        std::pair<double, double> const chartTempRange = {-40, 40};

        /** Candlestick vector */
        std::vector<CandleStick> candleSticks;

        /** Map with months and their corresponding number*/
        std::unordered_map<std::string, std::string> monthsMap = {{"01", "Jan"}, {"02", "Feb"}, {"03", "Mar"}, 
                                                                  {"04", "Apr"}, {"05", "May"}, {"06", "Jun"}, 
                                                                  {"07", "Jul"}, {"08", "Aug"}, {"09", "Sep"}, 
                                                                  {"10", "Oct"}, {"11", "Nov"}, {"12", "Dec"}};

        /** Print the y-axis labels every other row
         * @param rowIdx - row index
        */
        void printYaxisLabel(int rowIdx);

        /** Print the x-axis labels every other column*/
        void printXaxisLabel(ChartType chartType);

        /** Draw candle sticks function 
         * @param rowIdx - row index
        */
        void drawCandleSticks(int rowIdx);
        
};