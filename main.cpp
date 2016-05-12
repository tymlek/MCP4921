/* 
 * File:   main.cpp
 * Author: Tymoteusz Lekszycki
 *
 * Created on 12 May 2016, 17:11
 */

#include <cstdlib>
#include <iostream>

#include "mcp4921.hpp"

using namespace std;

int32_t voltsToBits(double volts, double refVoltage) {
    if (volts < 0 || volts > refVoltage) {
        return 0;
    }
    else {
        return (volts * (4096 / refVoltage));
    }
     
}

int main(int argc, char** argv) {
    MCP4921* dac;
    
    const double volts(argc >= 2 ? atof(argv[1]) : 3.29);
    const double refVoltage(argc >= 3 ? atof(argv[2]) : 3.29);   // in Volts
    
    try {
        dac = new MCP4921();
    } catch (exception& e) {
        cerr << e.what() << endl;
        exit(1);
    }
    
    cout << "Setting analog output to: " << volts << "V" << endl;
    dac->analogWrite(voltsToBits(volts,refVoltage));
    
    delete dac;
    
    return EXIT_SUCCESS;
}

