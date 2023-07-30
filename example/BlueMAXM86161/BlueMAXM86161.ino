
#include <Maxm86161_hrm_system.h>
#include <Arduino.h>

int storage_hr = 0;
int storage_spo2 = 0;

Maxm86161_hrm_system m_maxm86161;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  delay(5);
  
  Serial.println("--------------------Initialize MAXM86161-------------------- ");
  if(m_maxm86161.hrm_init() != 1){
    Serial.println("------------------------fail----------------------- ");
    while(1){};
  };
  Serial.println("------------------------Success----------------------- ");

}

void loop() {
  // the code will print all the 

  m_maxm86161.hrm_loop_process();
  int cur_spo2 = m_maxm86161.hrm_get_spo2();
  int cur_hr = m_maxm86161.hrm_get_heart_rate();

  if(cur_spo2 != storage_spo2){
    Serial.print("Spo2 :");
    Serial.print(cur_spo2);
    Serial.println();
    storage_spo2 = cur_spo2;
  }

  if(cur_hr != storage_hr){
    Serial.print("HR :");
    Serial.print(cur_hr);
    Serial.println();
    storage_hr = cur_hr;
  }
  
}


