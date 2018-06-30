#include "hsm.h"

// global scope, hardcoded for demo
byte hsm_secret[] = { 
  0x1e, 0x14, 0xcd, 0x38, 0x46, 0x91, 0xa9, 0x21, 
  0x20, 0xf6, 0x70, 0x27, 0x42, 0xca, 0x0e, 0x06, 
  0x95, 0x1a, 0xee, 0xe5, 0x7e, 0x91, 0xb5, 0xe1, 
  0x37, 0x52, 0x6c, 0x0a, 0x6c, 0x08, 0x67, 0xf4
};

HDPrivateKey bip32_key;
PrivateKey node_key;

void setup() {
  // put your setup code here, to run once:
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  Serial.begin(9600);

  while(!Serial){
    ; // wait for serial port to open
  }

  bip32_key = derive_bip32_key(hsm_secret, sizeof(hsm_secret));
  Serial.println(bip32_key);

  node_key = derive_node_key(hsm_secret, sizeof(hsm_secret));
  Serial.println(node_key);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    char buf[1000];
    Serial.readBytesUntil('\n', buf, sizeof(buf));
//    oled.println("Confirm?");
    bool confirmed = !digitalRead(6);
    bool unconfirmed = !digitalRead(5);
    while(!(confirmed || unconfirmed)){
      confirmed = !digitalRead(6);
      unconfirmed = !digitalRead(5);
    }
    Serial.println("Button pressed");
    if(confirmed){
      Serial.println("Accepted");
    }else{
      Serial.println("Not accepted");
    }
  }
}
