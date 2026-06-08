#include "map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct city {
  double min;
  double max;
  double sum;
  unsigned count;
};

int main (int argc, char *argv[]) {

  std::ifstream input{"lines.txt"};
  if(!input.is_open()){
    std::cout << "Error, lines.txt ne postoji!";
    return 1;
  }

  Map<std::string, city> map;
  for(std::string line; std::getline(input, line);){
    std::istringstream stream{line};
    std::string cityName;
    double temperature;
    std::getline(stream, cityName, ';');
    stream >> temperature;
    city* cityExists = map.find(cityName);
    if(cityExists){
      if(cityExists->min > temperature)
        cityExists->min = temperature;
      if(cityExists->max < temperature)
        cityExists->max = temperature;
      cityExists->sum += temperature;
      cityExists->count++;
    }
    else {
      city newCity{temperature, temperature, temperature, 1};
      map.insert(cityName, newCity);
    }
  }

    int option = -1;
    while(option != 3){
      std::cout << "Temperature database\n"
        << "Options:\n"
        << "1. Find city\n"
        << "2. Full report\n"
        << "3. Quit\n";
      std::cin >> option;
      if(option == 1){
        std::string cityName;
        std::cin.ignore();
        std::cout << "City: ";
        std::getline(std::cin, cityName);
        const city* foundCity = map.find(cityName);
        if(!foundCity)
          std::cout << "'" << cityName << "' is not found!\n";
        else {
          std::cout << "'" << cityName << "' is found!\n";
          std::cout << "Highest temperature: " << foundCity->max << "\n" 
            << "Lowest temperature: " << foundCity->min << std::endl 
            << "Average temperature: " << (foundCity->sum / foundCity->count) << std::endl;
        }
      }
      if(option == 2){
        std::ofstream output{"report.txt"};
        output << "Name;Max;Min;Avg\n";
        std::cout << "Generating ouput...\n";
        map.forEach([&output](const std::string& cityName, const city& cityData){
            output << cityName << ";" << cityData.max << ";" << cityData.min << ";" << (cityData.sum / cityData.count) << std::endl;
            });
        std::cout << "Generated report.txt\n";
      }
    }







  
  
  return 0;
}
