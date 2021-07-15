/*
 * Copyright (C) 2020  Anthony Doud & Joel Baranick
 * All rights reserved
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "sdkconfig.h"
#include <unity.h>
#include "sensors/EchelonData.h"
#include "test.h"

// Data from session w/ Assioma Uno pedals
static uint8_t t0[]  = {0xf0, 0xd0, 0x01, 0x01, 0xc2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0x00, 0x00};
static uint8_t t1[]  = {0xf0, 0xd2, 0x01, 0x02, 0xc5};
static uint8_t t2[]  = {0xf0, 0xd2, 0x01, 0x03, 0xc6};
static uint8_t t3[]  = {0xf0, 0xd2, 0x01, 0x04, 0xc7};
static uint8_t t4[]  = {0xf0, 0xd1, 0x11, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0x00, 0x00};
static uint8_t t5[]  = {0xf0, 0xd2, 0x01, 0x05, 0xc8};
static uint8_t t6[]  = {0xf0, 0xd2, 0x01, 0x06, 0xc9};
static uint8_t t7[]  = {0xf0, 0xd2, 0x01, 0x1E, 0xca};
static uint8_t t8[]  = {0xf0, 0xd2, 0x01, 0x1F, 0xcb};
static uint8_t t9[]  = {0xf0, 0xd1, 0x11, 0x00, 0x69, 0x00, 0x00, 0x00, 0x00, 0x19, 0x5a, 0x00, 0x00};
static uint8_t t10[] = {0xf0, 0xd2, 0x01, 0x0f, 0xd2};
static uint8_t t11[] = {0xf0, 0xd1, 0x09, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x14, 0x00, 0x3a, 0x00, 0x49};

void test_echelonData::test_parses_cadence(void) {
  EchelonData sensor = EchelonData();
  // Pre parse state
  TEST_ASSERT_TRUE(sensor.hasCadence());
  TEST_ASSERT_EQUAL_INT(NAN, sensor.getCadence());
  // try line without cadence
  sensor.decode(t1, sizeof(t1));
  TEST_ASSERT_EQUAL_INT(NAN, sensor.getCadence());
  // try a junk line
  sensor.decode(t0, sizeof(t0));
  TEST_ASSERT_EQUAL_INT(NAN, sensor.getCadence());
  // try line with Cadence
  sensor.decode(t4, sizeof(t4));
  TEST_ASSERT_EQUAL_INT(90, sensor.getCadence());
  // try line with Cadence
  sensor.decode(t11, sizeof(t11));
  TEST_ASSERT_EQUAL_INT(58, sensor.getCadence());
}

void test_echelonData::test_parses_heartrate(void) {
  // No heart rate data, confirm
  EchelonData sensor = EchelonData();
  TEST_ASSERT_FALSE(sensor.hasHeartRate());
  TEST_ASSERT_EQUAL_INT(INT_MIN, sensor.getHeartRate());
}

void test_echelonData::test_parses_speed(void) {
  // No speed data, confirm
  EchelonData sensor = EchelonData();
  TEST_ASSERT_FALSE(sensor.hasSpeed());
  TEST_ASSERT_EQUAL_FLOAT(NAN, sensor.getSpeed());
}

void test_echelonData::test_parses_power(void) {
  EchelonData sensor = EchelonData();
  // Pre parse state
  TEST_ASSERT_TRUE(sensor.hasPower());
  TEST_ASSERT_EQUAL_INT(INT_MIN, sensor.getPower());

  // Testing Power
  sensor.decode(t9, sizeof(t9));
  TEST_ASSERT_TRUE(sensor.hasPower());
  TEST_ASSERT_EQUAL_INT(0, sensor.getPower());

  sensor.decode(t10, sizeof(t10));
  TEST_ASSERT_TRUE(sensor.hasPower());
  TEST_ASSERT_EQUAL_INT(98, sensor.getPower());

  sensor.decode(t11, sizeof(t11));
  TEST_ASSERT_EQUAL_INT(63, sensor.getPower());

  sensor.decode(t2, sizeof(t2));
  TEST_ASSERT_EQUAL_INT(22, sensor.getPower());

  sensor.decode(t3, sizeof(t3));
  TEST_ASSERT_EQUAL_INT(24, sensor.getPower());

  sensor.decode(t9, sizeof(t9));
  TEST_ASSERT_EQUAL_INT(40, sensor.getPower());

  sensor.decode(t4, sizeof(t4));
  TEST_ASSERT_EQUAL_INT(40, sensor.getPower());

  sensor.decode(t5, sizeof(t5));
  TEST_ASSERT_EQUAL_INT(43, sensor.getPower());

  sensor.decode(t6, sizeof(t6));
  TEST_ASSERT_EQUAL_INT(47, sensor.getPower());

  sensor.decode(t7, sizeof(t7));
  TEST_ASSERT_EQUAL_INT(378, sensor.getPower());

  sensor.decode(t8, sizeof(t8));
  TEST_ASSERT_EQUAL_INT(412, sensor.getPower());
}
