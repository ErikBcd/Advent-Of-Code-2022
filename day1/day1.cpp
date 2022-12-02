#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream is("input");

    uint32_t max_calories = 0;
    uint32_t max_cal_2    = 0;
    uint32_t max_cal_3    = 0;
    uint32_t current_calc = 0;
    for (std::string s; std::getline(is, s);) {
        if (s == "") {
            if (current_calc > max_calories) { 
                max_cal_3 = max_cal_2;
                max_cal_2 = max_calories;
                max_calories = current_calc; 
            } else if (current_calc > max_cal_2) {
                max_cal_3 = max_cal_2;
                max_cal_2 = current_calc;
            } else if (current_calc > max_cal_3) {
                max_cal_3 = current_calc;
            }
            current_calc = 0;
        } else {
            current_calc += atoi(s.c_str());
        }
    }

    if (current_calc > max_calories) { 
        max_cal_3 = max_cal_2;
        max_cal_2 = max_calories;
        max_calories = current_calc; 
    } else if (current_calc > max_cal_2) {
        max_cal_3 = max_cal_2;
        max_cal_2 = current_calc;
    } else if (current_calc > max_cal_3) {
        max_cal_3 = current_calc;
    }
    
    std::cout << "1: " << max_calories << std::endl;
    std::cout << "2: " << max_cal_2 << std::endl;
    std::cout << "3: " << max_cal_3 << std::endl;

    std::cout << "Total: " << (max_calories + max_cal_2 + max_cal_3) << std::endl;
    return 0;
}