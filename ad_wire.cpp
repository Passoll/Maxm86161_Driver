#include "Arduino.h"
#include "ad_wire.h"

I2C_TransferReturn_TypeDef I2CSPM_Transfer(I2C_TransferSeq_TypeDef *seq) {
  Wire.beginTransmission(seq->addr);
  
  for(size_t i = 0; i < seq->buf[0].len; i++) {
    Wire.write(seq->buf[0].data[i]);
  }
  
  if(Wire.endTransmission() != 0) {
    return I2C_TRANSFER_ERROR;
  }
  
  if(seq->flags == I2C_FLAG_WRITE_READ) {
    Wire.requestFrom(seq->addr, seq->buf[1].len);
    for(size_t i = 0; i < seq->buf[1].len; i++) {
      
      uint8_t limit = 0;
      //debug
      //Serial.print("Request send");
      while(!Wire.available()) { 
        //Serial.print("."); 
        limit++;
        if(limit > 400) {
          Serial.println("Timeout");
          return I2C_TRANSFER_TIMEOUT;
        }
      }
      //Serial.print("Success");
      seq->buf[1].data[i] = Wire.read();
    }
  }
  return I2C_TRANSFER_OK;
}
