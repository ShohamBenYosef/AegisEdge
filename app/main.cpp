// cpp_main
#include <iostream>
#include "device.h"


int main() {
    std::cout << "AegisEdge\n";
    int temperature = get_temperature();
    std::cout << "Temperature: " << temperature << "°C\n";
    
    
    return 0;
}