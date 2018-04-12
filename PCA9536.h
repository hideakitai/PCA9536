#pragma once
#ifndef PCA9536_H
#define PCA9536_H

#ifdef TEENSYDUINO
#include <i2c_t3.h>
#else
#include <Wire.h>
#endif

namespace EmbeddedDevices
{
    class PCA9536
    {
        static const uint8_t I2C_ADDR = 0x41;
        static const uint8_t REG_SIZE = 0x04;
        static const uint8_t PORT_SIZE = 0x04;

        uint8_t ioex_reg_status[REG_SIZE] {0xFF};

    public:

        enum class REG
        {
            INPUT_PORT = 0x00,
            OUTPUT_PORT,
            INVERT,
            CONFIG
        };

        enum class DIR
        {
            OUT = 0x00,
            IN = 0x01,
            OUTPUT_ALL = 0xF0,
            INPUT_ALL = 0xFF
        };

        enum class LEVEL
        {
            L = 0x00,
            H = 0x01,
            L_ALL = 0x00,
            H_ALL = 0x0F
        };

        void setup()
        {
            Wire.begin();
            for (size_t i = 0; i < REG_SIZE; ++i) setIO(DIR::OUT);
        }

        void setIO(const DIR dir)
        {
            Wire.beginTransmission(I2C_ADDR);
            Wire.write((uint8_t)REG::CONFIG);
            if (dir == DIR::OUT) Wire.write((uint8_t)DIR::OUTPUT_ALL);
            else                 Wire.write((uint8_t)DIR::INPUT_ALL);
            Wire.endTransmission();

            read(REG::CONFIG);
        }

        void output(const LEVEL level)
        {
            Wire.beginTransmission(I2C_ADDR);
            Wire.write((uint8_t)REG::OUTPUT_PORT);
            if (level == LEVEL::H) Wire.write((uint8_t)LEVEL::H_ALL);
            else                   Wire.write((uint8_t)LEVEL::L_ALL);
            Wire.endTransmission();

            read(REG::OUTPUT_PORT);
        }

        void output(const uint8_t bits)
        {
            Wire.beginTransmission(I2C_ADDR);
            Wire.write((uint8_t)REG::OUTPUT_PORT);
            Wire.write((uint8_t)bits);
            Wire.endTransmission();

            read(REG::OUTPUT_PORT);
        }

        void output(const uint8_t port, const LEVEL level)
        {
            if (port >= PORT_SIZE) return;
            Wire.beginTransmission(I2C_ADDR);
            Wire.write((uint8_t)REG::OUTPUT_PORT);
            Wire.write((uint8_t)((uint8_t)level << port));
            Wire.endTransmission();

            read(REG::OUTPUT_PORT);
        }

        void read(const REG reg)
        {
            Wire.beginTransmission(I2C_ADDR);
            Wire.write((uint8_t)reg);
            Wire.endTransmission();

            Wire.requestFrom(I2C_ADDR, 1, true);  // blocking read (request 256 bytes)

            while(Wire.available()) ioex_reg_status[(uint8_t)reg] = Wire.read();
        }

        void read()
        {
            for (size_t i = 0; i < REG_SIZE; ++i) read((REG)i);
        }

        // void print(const REG reg) const
        // {
        //     Serial.printf("IOEX REG %d : %02x\n", reg, ioex_reg_status[reg]);
        // }

        // void print() const
        // {
        //     for (size_t i = 0; i < REG_SIZE; ++i) print((IOEX_REG)i);
        // }
    };

}

using PCA9536 = EmbeddedDevices::PCA9536;

#endif // PCA9536_H
