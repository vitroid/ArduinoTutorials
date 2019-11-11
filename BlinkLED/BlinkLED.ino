
//int led=D4; // NodeMCU, Blue https://lowvoltage.github.io/2017/07/09/Onboard-LEDs-NodeMCU-Got-Two
//int led=LED_BUILTIN;
int led=10; //G10, M5Stick-C

void setup(){                // { }内をはじめに1度だけ実行する
  Serial.begin(9600);
  pinMode(led, OUTPUT);      // ledピン(11ピン)を出力にする
}
void loop(){                 // { }内を繰り返し実行する
  Serial.println(M5_LED);
  Serial.println(G10);
  digitalWrite(led, HIGH);   // ledピンにHIGHを出力する
  delay(1000);               // 1秒(1000ms)待つ
  Serial.println("Off");
  digitalWrite(led, LOW);    // ledピンにLOWを出力する
  delay(1000);               // 1秒(1000ms)待つ
}
