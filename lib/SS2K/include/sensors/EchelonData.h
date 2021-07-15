/*
 * Copyright (C) 2020  Anthony Doud & Joel Baranick
 * All rights reserved
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#pragma once

#include "SensorData.h"

class EchelonData : public SensorData {
 public:
  EchelonData() : SensorData("ECH") {}

  bool hasHeartRate();
  bool hasCadence();
  bool hasPower();
  bool hasSpeed();
  int getHeartRate();
  float getCadence();
  int getPower();
  float getSpeed();
  void decode(uint8_t *data, size_t length);

 private:
  uint8_t cadence    = 0;
  uint8_t resistance = 0;
  int power          = INT_MIN;
};
