/*
 * QMC5883L.c
 *
 *  Created on: Mar 27, 2023
 *      Author: kenichi-matsudo
 */
#include "QMC5883L.h"

uint8_t address = QMC5883L_ADDR;

void compass_WriteReg(uint8_t Reg, uint8_t val){
  uint8_t data[2] = { Reg, val };
  if(HAL_I2C_IsDeviceReady(&hi2c1, address, 3, 100));
  HAL_I2C_Master_Transmit(&hi2c1, address, data, 2, 1000);
}

void compass_init(){
	compass_WriteReg(0x02,0x00);
  //Define Set/Reset period
	HAL_Delay(20);
	compass_WriteReg(0x01,0x20);
	HAL_Delay(20);

	//compass_setMode(Mode_Continuous,ODR_200Hz,RNG_8G,OSR_512);
}

void compass_setMode(uint16_t mode,uint16_t odr,uint16_t rng,uint16_t osr){
	compass_WriteReg(0x09,mode|odr|rng|osr);
  }


void compass_softReset(){
	compass_WriteReg(0x0A,0x80);
}

void compass_read(uint16_t *x, uint16_t *y, uint16_t *z)
{
//  uint8_t reg = 0x00;
  uint8_t reg = 0x03;
  uint8_t buffer[6];

  // 0x00レジスタを指定して、計測モードに設定
  //HAL_I2C_Mem_Write(&hi2c1, address, 0x09, 1, &reg, 1, 1000);
  // データを読み取る
  HAL_I2C_Mem_Read(&hi2c1, address, reg, 1, buffer, 6, 1000);

  // 取得したデータを解析して、16ビットのx、y、z値に変換
//  *x = (int16_t)((buffer[1] << 8) | buffer[0]);
//  *y = (int16_t)((buffer[3] << 8) | buffer[2]);
//  *z = (int16_t)((buffer[5] << 8) | buffer[4]);

	  *x = (((int16_t)buffer[0]) << 8) | buffer[1];
	  *y = (((int16_t)buffer[4]) << 8) | buffer[5];
	  *z = (((int16_t)buffer[2]) << 8) | buffer[3];
}

void tout_read(uint16_t *t)
{
	uint8_t buffer[2];
	HAL_I2C_Mem_Read(&hi2c1, address, 0x07, 1, buffer, 2, 1000);
	*t = (int16_t)((buffer[1] << 8) | buffer[0]);
}

