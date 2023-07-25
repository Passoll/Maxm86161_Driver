#pragma once

#include "Wire.h"
#include "Arduino.h"


#define I2C_FLAG_WRITE 0
#define I2C_FLAG_WRITE_READ 1

typedef struct {
  uint8_t *data;
  size_t len;
} I2C_TransferBuf_TypeDef;

typedef struct {
  uint8_t addr;
  uint8_t flags;
  I2C_TransferBuf_TypeDef buf[2];
} I2C_TransferSeq_TypeDef;

/*-----------------------Status-----------------------*/
typedef enum {
    I2C_TRANSFER_OK,
    I2C_TRANSFER_ERROR,
    I2C_TRANSFER_TIMEOUT
} I2C_TransferReturn_TypeDef;


I2C_TransferReturn_TypeDef I2CSPM_Transfer(I2C_TransferSeq_TypeDef *seq);
