// Define Arduino Library
#ifndef __Arduino__
	#include <Arduino.h>
#endif

// Battery Structure
typedef struct {
	float IV;
	float T;
	float IC;
	float SOC;
	uint16_t FB;
	uint16_t IB;
	uint8_t Charge;
} Battery_Struct;

// Pressure Structure
typedef struct {
	float Instant;
	float Min;
	float Max;
	float Average;
	float Deviation;
	float Slope;
	uint16_t DataCount;
} Pressure_Struct;

// Pressure Structure
typedef struct {
    uint8_t Manufacturer;
    uint8_t Model;
    uint16_t Firmware_1;
    uint16_t Firmware_2;
    uint16_t Firmware_3;
    char * IMEI;
    uint32_t Serial;
    char * ICCID;
} GSM_Init_Struct;
