/* Code written with help from cplusplus.com and stackoverflow.com
Referenced from:
- https://stackoverflow.com/questions/5907031/printing-the-correct-number-of-decimal-places-with-cout
- https://stackoverflow.com/questions/12560291/set-back-default-floating-point-print-precision-in-c
- https://cplusplus.com/reference/ios/fixed/
- https://cplusplus.com/reference/ios/ios_base/precision/
- https://cplusplus.com/reference/iomanip/setw/
 */

#include "utilityFunctions.h"
#include <iostream> 
#include <iomanip> // std::setw, std::setfill and std::setprecision

void UtilityFunctions::printFormattedDouble(double value) 
{
    double absValue = std::abs(value);
    // handles the negative sign for values < 10
    if (value < 0 && std::abs(value) < 10) {
        std::cout << "-";
        value = std::abs(value);
    }
    else if (value >= 0) std::cout << " "; // Add a space for positive values and zero
    //Save current precision
    std::streamsize ss = std::cout.precision();
    // Set precision
    std::cout << std::fixed << std::setprecision(1);
    // Ensure leading zeros for values less than 10
    std::cout << std::setw(4) << std::setfill('0') << value;
    //Restore previous precision
    std::cout << std::setprecision(ss);
}

void UtilityFunctions::printFormattedDoubleXAxis(double value) 
{
    double absValue = std::abs(value);
    // handles the negative sign for values < 10
    if (value < 0 && std::abs(value) < 10) {
        std::cout << "-";
        value = std::abs(value);
    }
    else if (value >= 0) std::cout << " "; // Add a space for positive values and zero
    //Save current precision
    std::streamsize ss = std::cout.precision();
    // Set precision
    std::cout << std::fixed << std::setprecision(0);
    // Ensure leading zeros for values less than 10
    std::cout << std::setw(2) << std::setfill(' ') << value;
    //Restore previous precision
    std::cout << std::setprecision(ss);
}