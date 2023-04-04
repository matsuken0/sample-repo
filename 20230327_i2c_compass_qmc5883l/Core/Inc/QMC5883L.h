/*
 * QMC5883L.h
 *
 *  Created on: Mar 27, 2023
 *      Author: kenichi-matsudo
 */

#ifndef INC_QMC5883L_H_
#define INC_QMC5883L_H_

#include "stm32f3xx_hal.h"
// #define QMC5883L_ADDR 0x0D//The default I2C address is 0D: 0001101
#define QMC5883L_ADDR 0x1E<<1
//#define QMC5883L_ADDR 0x0D<<1
extern I2C_HandleTypeDef hi2c1;


//Registers Control //0x09

#define Mode_Standby    0b00000000
#define Mode_Continuous 0b00000001

#define ODR_10Hz        0b00000000
#define ODR_50Hz        0b00000100
#define ODR_100Hz       0b00001000
#define ODR_200Hz       0b00001100

#define RNG_2G          0b00000000
#define RNG_8G          0b00010000

#define OSR_512         0b00000000
#define OSR_256         0b01000000
#define OSR_128         0b10000000
#define OSR_64          0b11000000

extern uint8_t address;

extern void compass_init();
extern void compass_setMode(uint16_t mode,uint16_t odr,uint16_t rng,uint16_t osr);
extern void compass_softReset();
extern void compass_read(uint16_t* x,uint16_t* y,uint16_t* z);
//extern void read(int* x,int* y,int* z);
extern void compass_WriteReg(uint8_t Reg,uint8_t val);
extern void tout_read(uint16_t *t);


#endif /* INC_QMC5883L_H_ */
