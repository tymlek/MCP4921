/* 
 * File:   mcp4921.hpp
 * Author: pi
 *
 * Created on 12 May 2016, 17:13
 */

#ifndef MCP4921_HPP
#define	MCP4921_HPP

#include <wiringPiSPI.h>
#include <cstdint>
#include <stdexcept>

#define buffSize 2

class MCP4921 {
private:
    int32_t channel;
    int32_t speed;
    uint8_t spiData[buffSize];
    
public:
    MCP4921()
        : channel(1), speed(1000000)              // 1 MHz
    {   
        if (wiringPiSPISetup(channel,speed) < 0) {
            throw std::runtime_error("Cannot connect to spi device");
        }
    }
    
    MCP4921(int32_t channel, int32_t speed)
        : channel(channel), speed(speed)
    {
        if (wiringPiSPISetup(channel,speed) < 0) {
            throw std::runtime_error("Cannot connect to spi device");
        }
    }
    
    int32_t analogWrite(int32_t val) {
        
        spiData[0] = (0x30 | ((val >> 8) & 0x0f));
        spiData[1] = (val & 0xff);
        
        wiringPiSPIDataRW(channel,spiData,buffSize);
        
        return val;
    }
};

#endif	/* MCP4921_HPP */

