/*
 * Copyright (C) 2020  Anthony Doud & Joel Baranick
 * All rights reserved
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "sensors/EchelonData.h"

bool EchelonData::hasHeartRate() { return false; }

bool EchelonData::hasCadence() { return !std::isnan(this->cadence); }

bool EchelonData::hasPower() { return this->cadence >= 0 && this->resistance >= 0; }

bool EchelonData::hasSpeed() { return false; }

int EchelonData::getHeartRate() { return INT_MIN; }

float EchelonData::getCadence() { return this->cadence; }

int EchelonData::getPower() { return this->power; }

float EchelonData::getSpeed() { return nanf(""); }

void EchelonData::decode(uint8_t *data, size_t length) {
  switch (data[1]) {
    // Cadence notification
    case 0xD1:
      this->cadence = static_cast<uint8_t>(data[10]);
      break;
    // Resistance notification
    case 0xD2:
      this->resistance = static_cast<uint8_t>(data[3]);
      break;
  }
  if (std::isnan(this->cadence) || this->resistance < 0) {
    return;
  }
  if (this->cadence == 0 || this->resistance == 0) {
    this->power = 0;
  } else {
    //Credit to @marklogan and @cagnulein for their code below from qdomyos-zwift
    //this->power = pow(1.090112, this->resistance) * pow(1.015343, cadence) * 7.228958;
    const double Epsilon = 4.94065645841247E-324;
    const int wattTableFirstDimension = 33;
    const int wattTableSecondDimension = 11;
    double wattTable[wattTableFirstDimension][wattTableSecondDimension] = {
        {Epsilon, 1.0, 2.2, 4.8, 9.5, 13.6, 16.7, 22.6, 26.3, 29.2, 47.0},
        {Epsilon, 1.0, 2.2, 4.8, 9.5, 13.6, 16.7, 22.6, 26.3, 29.2, 47.0},
        {Epsilon, 1.3, 3.0, 5.4, 10.4, 14.5, 18.5, 24.6, 27.6, 33.5, 49.5},
        {Epsilon, 1.5, 3.7, 6.7, 11.7, 15.9, 19.6, 26.1, 30.8, 35.2, 51.2},
        {Epsilon, 1.6, 4.7, 7.5, 13.7, 17.6, 22.6, 29.0, 36.9, 42.6, 57.2},
        {Epsilon, 1.8, 5.2, 8.0, 14.8, 19.1, 23.5, 32.5, 37.5, 50.8, 61.8},
        {Epsilon, 1.9, 5.7, 8.7, 15.6, 20.2, 25.5, 33.5, 39.6, 52.1, 65.3},
        {Epsilon, 2.0, 6.2, 9.5, 16.8, 21.8, 28.1, 37.0, 42.8, 57.8, 68.4},
        {Epsilon, 2.1, 6.8, 10.8, 18.2, 23.6, 29.5, 40.0, 47.6, 60.5, 72.1},
        {Epsilon, 2.2, 7.3, 11.5, 19.3, 26.3, 33.5, 45.3, 51.8, 66.7, 76.8},
        {Epsilon, 2.4, 7.9, 12.7, 20.8, 29.8, 37.6, 52.2, 56.2, 73.5, 83.6},
        {Epsilon, 2.6, 8.5, 13.5, 23.5, 33.6, 41.9, 55.1, 59.0, 78.6, 89.7},
        {Epsilon, 2.7, 9.1, 14.2, 25.6, 35.4, 45.3, 57.3, 62.8, 81.3, 95.0},
        {Epsilon, 2.9, 9.6, 16.8, 29.1, 37.5, 49.6, 62.5, 69.0, 84.7, 99.3},
        {Epsilon, 3.0, 10.0, 22.3, 31.2, 40.3, 51.8, 65.0, 70.0, 92.6, 108.2},
        {Epsilon, 3.2, 10.4, 24.0, 36.6, 42.5, 56.3, 74.0, 85.0, 98.2, 123.5},
        {Epsilon, 3.5, 10.9, 25.1, 38.5, 47.6, 65.4, 83.0, 93.0, 114.8, 136.8},
        {Epsilon, 3.7, 11.5, 26.0, 41.0, 53.2, 71.6, 90.0, 100.0, 121.7, 149.2},
        {Epsilon, 4.0, 12.1, 27.5, 43.6, 56.0, 82.3, 101.0, 113.6, 143.0, 162.8},
        {Epsilon, 4.2, 12.7, 29.7, 46.7, 64.2, 87.9, 109.2, 128.9, 154.0, 172.3},
        {Epsilon, 4.5, 13.7, 32.0, 50.0, 71.8, 95.6, 113.8, 135.6, 165.0, 185.0},
        {Epsilon, 4.7, 14.9, 34.5, 54.2, 77.0, 100.7, 127.0, 147.6, 180.0, 200.0},
        {Epsilon, 5.0, 15.8, 36.5, 58.3, 83.4, 110.1, 136.0, 168.1, 196.0, 213.5},
        {Epsilon, 5.6, 17.0, 39.5, 64.3, 88.8, 123.4, 154.0, 182.0, 210.0, 235.0},
        {Epsilon, 6.1, 18.2, 44.0, 70.7, 99.9, 133.3, 166.0, 198.0, 230.0, 253.5},
        {Epsilon, 6.8, 19.4, 49.0, 79.0, 108.8, 147.2, 185.0, 217.0, 255.2, 278.0},
        {Epsilon, 7.6, 22.0, 54.8, 88.0, 127.0, 167.0, 212.0, 244.0, 287.0, 305.0},
        {Epsilon, 8.7, 26.0, 62.0, 100.0, 145.0, 190.0, 242.0, 281.0, 315.1, 350.0},
        {Epsilon, 9.2, 30.0, 71.0, 114.4, 161.6, 215.1, 275.1, 317.0, 358.5, 390.0},
        {Epsilon, 9.8, 36.0, 82.5, 134.5, 195.3, 252.5, 313.7, 360.0, 420.3, 460.0},
        {Epsilon, 10.5, 43.0, 95.0, 157.1, 228.4, 300.1, 374.1, 403.8, 487.8, 540.0},
        {Epsilon, 12.5, 48.0, 99.3, 162.2, 232.9, 310.4, 400.3, 435.5, 530.5, 589.0},
        {Epsilon, 13.0, 53.0, 102.0, 170.3, 242.0, 320.0, 427.9, 475.2, 570.0, 625.0}};

    int level = this->resistance;
    if (level < 0) {
        level = 0;
    }
    if (level >= wattTableFirstDimension) {
        level = wattTableFirstDimension - 1;
    }
    double *watts_of_level = wattTable[level];
    int watt_setp = (this->cadence / 10.0);
    if (watt_setp >= 10) {
        this->power = (((double)this->cadence) / 100.0) * watts_of_level[wattTableSecondDimension - 1];
        return;
    }
    double watt_base = watts_of_level[watt_setp];
    this->power = (((watts_of_level[watt_setp + 1] - watt_base) / 10.0) * ((double)(((int)(this->cadence)) % 10))) +
           watt_base;
  }
}
