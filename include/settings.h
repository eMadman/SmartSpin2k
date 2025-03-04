/*
 * Copyright (C) 2020  Anthony Doud & Joel Baranick
 * All rights reserved
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#pragma once

#include "SS2KLog.h"

// Update firmware on boot?
#define AUTO_FIRMWARE_UPDATE true

// Default Bluetooth WiFi and MDNS Name
#define DEVICE_NAME "SmartSpin2K"

// Default WiFi Password
#define DEFAULT_PASSWORD "password"

// default URL To get Updates From.
// If changed you'll also need to get a root certificate from the new server
// and put it in /include/cert.h
#define FW_UPDATEURL "https://raw.githubusercontent.com/doudar/OTAUpdates/main/"

// File that contains Version info
#define FW_VERSIONFILE "version.txt"

// Path to the latest Firmware
#define FW_BINFILE "firmware.bin"

// Data directory Source
#define DATA_UPDATEURL "https://raw.githubusercontent.com/doudar/SmartSpin2k/develop/data"

#define DATA_FILELIST "/list.json"

// name of local file to save configuration in LittleFS
#define configFILENAME "/config.txt"

// name of local file to save Physical Working Capacity in LittleFS
#define userPWCFILENAME "/userPWC.txt"

// name of the local file to save the torque table. 
#define TORQUE_TABLE_FILENAME "/TorqueTable.txt"

// Default Incline Multiplier.
// Incline multiplier is the multiple required to convert incline received from the remote client (percent grade*100)
// into actual stepper steps that move the stepper motor. It takes 2,181.76 steps to rotate the knob 1 full revolution. with hardware version 1.
// Incline_Multiplier may be able to be removed in the future by dividing ShiftSteps by ~200 to get this value but we're not quite ready
// to make that commitment yet.
#define INCLINE_MULTIPLIER 5.0

// Minumum value for power correction factor user setting
#define MIN_PCF .5

// Maximum value for power correction factor user setting
#define MAX_PCF 2.5

// Default Stepper Power.
// Stepper peak current in ma. This is hardware restricted to a maximum of 2000ma on the TMC2225. RMS current is less.
#define DEFAULT_STEPPER_POWER 900

// Default Shift Step. The amount to move the stepper motor for a shift press.
#define DEFAULT_SHIFT_STEP 1200

// Stepper Acceleration in steps/s^2
#define STEPPER_ACCELERATION 3000

// Stepper Max Speed in steps/s
#define DEFAULT_STEPPER_SPEED 1500

// Default ERG Sensitivity. Predicated on # of Shifts (further defined by shift steps) per 30 watts of resistance change.
// I.E. If the difference between ERG target and Current watts were 30, and the Shift step is defined as 600 steps,
// and ERG_Sensitivity were 1.0, ERG mode would move the stepper motor 600 steps to compensate. With an ERG_Sensitivity of 2.0, the stepper
// would move 1200 steps to compensate, however ERG_Sensitivity values much different than 1.0 imply shiftStep has been improperly configured.
#define ERG_SENSITIVITY 5.0

// Number of watts per shift expected by ERG mode for it's calculation. The user should target this number by adjusting Shift Step until WATTS_PER_SHIFT
// is obtained as closely as possible during each shift.
#define WATTS_PER_SHIFT 30

// Amount to change watt target per shift in ERG mode.
#define ERG_PER_SHIFT 10

//Pass all of the FTMS commands sent to SS2k down to a connected FTMS device. 
#define FTMS_PASSTHROUGH false

// Use internal ERG control on external FTMS Trainer.
//#define INTERNAL_ERG_4EXT_FTMS

//Minimum cadence where ERG mode stops.
#define MIN_ERG_CADENCE 30

// Default Min Watts to stop stepper.
// This is used to set the lower travel limit for the motor.
#define DEFAULT_MIN_WATTS 50

// Default Max Watts that the brake on the spin bike can absorb from the user.
// This is used to set the upper travel limit for the motor.
#define DEFAULT_MAX_WATTS 1400

// Minimum resistance on a Peloton Bike.
// This is used to set the lower travel limit for the motor.
#define MIN_PELOTON_RESISTANCE 5

// Maximum resistance on a Peloton Bike.
// This is used to set the upper travel limit for the motor.
#define MAX_PELOTON_RESISTANCE 98

// Minimum resistance on a Peloton Bike.
// This is used to set the lower travel limit for the motor.
#define MIN_ECHELON_RESISTANCE 5

// Maximum resistance on a Peloton Bike.
// This is used to set the upper travel limit for the motor.
#define MAX_ECHELON_RESISTANCE 30

// Resistance range when no bike with resistance is connected.
#define DEFAULT_RESISTANCE_RANGE 2000

// Default +- Stepper Travel Limit
// This is used until the TorqueTable has enough data to compute travel limits
#define DEFAULT_STEPPER_TRAVEL 200000000

// Default debounce delay for shifters. Increase if you have false shifts. Decrease if shifting takes too long.
#define DEBOUNCE_DELAY 400

// Hardware Revision check pin
#define REV_PIN 34

//////////// Defines for hardware Revision 1 ////////////

// Board Name
#define r1_NAME "Revision One"

// ID Voltage on pin 34. Values are 0-4095 (0-3.3v)
#define r1_VERSION_VOLTAGE 0

// Hardware pin for Shift Up
#define r1_SHIFT_UP_PIN 19

// Hardware pin for Shift Down
#define r1_SHIFT_DOWN_PIN 18

// Hardware pin for stepper Enable
#define r1_ENABLE_PIN 13

// Hardware pin for stepper step
#define r1_STEP_PIN 25

// Hardware pin for stepper dir
#define r1_DIR_PIN 33

// TMC2208/TMC2224 SoftwareSerial receive pin
#define r1_STEPPER_SERIAL_RX 14

// TMC2208/TMC2224 SoftwareSerial transmit pin
#define r1_STEPPER_SERIAL_TX 12

// Reduce current setting by this divisor (0-31)
#define r1_PWR_SCALER 31
////////////////////////////////////////////////////////
//////////// Defines for hardware Revision 2 ////////////

// Board Name
#define r2_NAME "Revision Two"

// ID Voltage on pin 34. Values are 0-4095 (0-3.3v)
#define r2_VERSION_VOLTAGE 4095

// Hardware pin for Shift Up
#define r2_SHIFT_UP_PIN 26

// Hardware pin for Shift Down
#define r2_SHIFT_DOWN_PIN 32

// Hardware pin for stepper Enable
#define r2_ENABLE_PIN 27

// Hardware pin for stepper step
#define r2_STEP_PIN 25

// Hardware pin for stepper dir
#define r2_DIR_PIN 33

// TMC2209 SoftwareSerial receive pin
#define r2_STEPPER_SERIAL_RX 18

// TMC2209 SoftwareSerial transmit pin
#define r2_STEPPER_SERIAL_TX 19

// TMC2209 SoftwareSerial receive pin
#define r2_AUX_SERIAL_RX 22

// TMC2209 SoftwareSerial transmit pin
#define r2_AUX_SERIAL_TX 21

// Reduce current setting by this divisor (0-31)
#define r2_PWR_SCALER 12
////////////////////////////////////////////////////////

// TMC2208/TMC2224 HardwareSerial port
#define SERIAL_PORT stepperSerial

// Match to your driver
#define R_SENSE 0.11f

// Hardware pin for indicator LED *note* internal LED on esp32 Dev board is pin
// 2
#define LED_PIN 2

// Max tries that BLE client will perform on reconnect
#define MAX_RECONNECT_TRIES 3

// loop speed for the SmartSpin2k BLE communications
#define BLE_NOTIFY_DELAY 503

// loop speed for the SmartSpin2k BLE Client reconnect
#define BLE_CLIENT_DELAY 101

// Number of devices that can be connected to the Client (myBLEDevices size)
#define NUM_BLE_DEVICES 4

// loop speed for the Webserver
#define WEBSERVER_DELAY 7

// Name of default Power Meter. any connects to anything, none connects to
// nothing.
#define CONNECTED_POWER_METER "any"

// Name of default heart monitor. any connects to anything, none connects to
// nothing.
#define CONNECTED_HEART_MONITOR "any"

// Name of default remote. any connects to anything, none connects to
// nothing.
#define CONNECTED_REMOTE "none"

// number of main loops the shifters need to be held before a BLE scan is
// initiated.
#define SHIFTERS_HOLD_FOR_SCAN 2

// stealthChop enabled by default
#define STEALTHCHOP true

// how long to try STA mode before falling back to AP mode
#define WIFI_CONNECT_TIMEOUT 10

// Max size of userconfig
#define USERCONFIG_JSON_SIZE 1524 + DEBUG_LOG_BUFFER_SIZE

#define RUNTIMECONFIG_JSON_SIZE 512 + DEBUG_LOG_BUFFER_SIZE

/* Number of entries in the ERG Torque Lookup Table
 This is currently maintained as to keep memory usage lower and reduce the print output of the table.
 It can be depreciated in the future should we decide to remove logging of the torque table. Then it should be calculated in ERG_Mode.cpp
 by dividing userConfig->getMaxWatts() by TORQUETABLE_INCREMENT.  */
#define TORQUETABLE_SIZE 20

// Size of increments (in Nm) for the ERG Lookup Table. Needs to be one decimal place for proper calculations
#define TORQUETABLE_INCREMENT 5.31

// Number of similar torque samples to take before writing to the Torque Table
#define TORQUE_SAMPLES 5

// The Array position of the most reliable Torque Table stepper position according to testing data.
#define MOST_DEPENDABLE_TORQUE_ENTRY 2

// How often in ms to save the torque table if no new data is added and user is pedaling.
#define TORQUE_TABLE_SAVE_INTERVAL 240000

// Normal cadence value (used in torque table and other areas)
#define NORMAL_CAD 90

// Temperature of the ESP32 at which to start reducing the power output of the stepper motor driver.
#define THROTTLE_TEMP 85

// Size of the Aux Serial Buffer for Peloton
#define AUX_BUF_SIZE 10

// Interrogate Peloton bike for data?
#define PELOTON_TX true

// If not receiving Peloton Messages, how long to wait before next TX attempt is
#define TX_CHECK_INTERVAL 20

// If ble devices are both setup, how often to attempt a reconnect.
#define BLE_RECONNECT_INTERVAL 1

// Interval for polling ble battery updates
#define BATTERY_UPDATE_INTERVAL_MILLIS 300000 

// Initial and web scan duration.
#define DEFAULT_SCAN_DURATION 5

// BLE automatic reconnect duration. Set this low to avoid interruption.
#define BLE_RECONNECT_SCAN_DURATION 5

//Task Stack Sizes
#define MAIN_STACK 4500
#define ERG_STACK 6500
#define HTTP_STACK 6000
#define BLE_COMM_STACK 6000
#define BLE_CLIENT_STACK 5000
#define STEPPER_STACK 1700

// Uncomment to enable stack size debugging info
// #define DEBUG_STACK

// Uncomment to enable sending Telegram debug messages back to the chat
// specified in telegram_token.h
// #define USE_TELEGRAM

// Uncomment to enable HR->PWR debugging info. Always displays HR->PWR
// Calculation. Never sets userConfig->setSimulatedPower();
// #define DEBUG_HR_TO_PWR

// Uncomment to enable HR->PWR enhanced torquetable debugging.
// #define DEBUG_TORQUETABLE

#ifdef USE_TELEGRAM
// Max number of telegram messages to send per session
#define MAX_TELEGRAM_MESSAGES 1
// Filler definitions for if telegram_token.h is not included (because it has
// sensitive information). Do not change these as this file is tracked and
// therefore public. Enter your own Telegram info into telegram_token.h
#if __has_include("telegram_token.h")
#include "telegram_token.h"
#else
#define TELEGRAM_TOKEN   "1234567890:ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghi"
#define TELEGRAM_CHAT_ID "1234567890"
#endif
#endif
