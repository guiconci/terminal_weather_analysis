#pragma once
//Used Merkel Main file as a template
#include "ObservationsBook.h"
#include "WeatherObservation.h"

class ThermoCandle {
    public:
        ThermoCandle();
        /** Call this to start the sim */
        void init();

    private:
        void printMenu();
        void printHelp();
        void analyzeMonthlyWeather();
        void analyzeYearlyWeather();
        void makeWeatherPrediction();
        void exit();
        void processUserOption(int userOption);
        int getUserOption();

        ObservationsBook observationBook;



};