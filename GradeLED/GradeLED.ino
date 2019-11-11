
int led=D4; // NodeMCU, Blue https://lowvoltage.github.io/2017/07/09/Onboard-LEDs-NodeMCU-Got-Two
//int led=LED_BUILTIN; //Arduino 

void setup(){                // { }内をはじめに1度だけ実行する
  Serial.begin(9600);
  pinMode(led, OUTPUT);      // ledピン(11ピン)を出力にする
}

int brightness = 0;
void loop(){                 // { }内を繰り返し実行する
  Serial.println(brightness);
  analogWrite(led, brightness);   // ledピンにHIGHを出力する
  delay(100);               // 1秒(1000ms)待つ
  brightness = (brightness + 100) % 1000;
}

// Arduino Nanoでは中間調出ない。
// M5Stack/M5StickにはLEDがない。
