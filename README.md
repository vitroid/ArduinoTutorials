# Arduino Short Tutorial

* Nov 11, 2019起稿
* 14:00-16:00 Nov 11, 2019実施予定 B-133室

## もってきてほしいもの

* Note PC
* MicroUSB cable
* バッテリ(もしあれば)

## はじめに

* Arduino
  ![Arduino](https://upload.wikimedia.org/wikipedia/commons/thumb/0/07/A_hand-soldered_Arduino.jpg/640px-A_hand-soldered_Arduino.jpg)
* NodeMCU
  ![NodeMCU](https://upload.wikimedia.org/wikipedia/commons/thumb/e/e5/Nodemcu_amica_bot_02.png/640px-Nodemcu_amica_bot_02.png)
* Arduino Nano
  ![Arduino Nano](https://upload.wikimedia.org/wikipedia/commons/thumb/9/9b/Arduino_nano_isometr.jpg/640px-Arduino_nano_isometr.jpg)
* M5Stack
  ![M5Stack](https://images-na.ssl-images-amazon.com/images/I/41nPP2J%2Br5L._AC_.jpg)
* M5Stick-C
  ![M5Stick-C](https://images-na.ssl-images-amazon.com/images/I/71UfHfHPZKL._AC_SL1000_.jpg)

これらのマイコン(マイクロコントローラ)を開発する環境(言語)は

* Arduino (C++)
* UIFlow (MicroPython)
* Obniz (JavaScript)

などがある。それぞれ一長一短あるが、今回は最もシンプルなハードウェアを利用できるArduinoを選ぶ。(UIFlowはその名の通りUIを設計するのには適しているが画面を持たないマイコンでは有り難みが少ない。Obnizは常時インターネット接続が前提)

## Arduino IDEのインストール

* [Arduino IDE 1.8.10](https://www.arduino.cc/)をダウンロードしてインストール。(2019-11-11現在)

## ハードウェア

今回準備しているのは以下の4種類。どれもArduino IDEでプログラム開発可能。

### Arduino Nano

* [解説(英語)](https://www.theengineeringprojects.com/2018/06/introduction-to-arduino-nano.html)
* ATMega328P (Arduino互換)
* パッケージ小さい。
* Wifi/BlueTooth非搭載
* MiniUSB接続。
* [実売250円](https://www.amazon.co.jp/dp/B07VVWGW2V)

![Arduino Nano Pins](http://christianto.tjahyadi.com/wp-content/uploads/2014/11/nano.jpg)
Arduino Nanoのピン配列



### NodeMCU←今回はこれ

* [解説(英語)](https://lastminuteengineers.com/esp8266-nodemcu-arduino-tutorial/)
* ESP8266チップ
* Wifi/BlueTooth搭載
* AD端子(アナログ入力端子)が1本しかない。
* いくつかのピンがWifiチップに使われていて、ユーザーの使えるピンは少ない。(GPIO6, GPIO7, GPIO8, GPIO9, GPIO10, GPIO11は使えない)
* MicroUSB接続。
* [実売330円](https://www.amazon.co.jp/dp/B07SFF1VJR)

![NodeMCU Pins](https://lastminuteengineers.com/wp-content/uploads/2018/08/ESP-12E-Development-Board-ESP8266-NodeMCU-Pinout.jpg)
NodeMCUのピン配列


### M5StickC

* ESP32チップ
* Wifi/BlueTooth/加速度センサー/バッテリー/LCD搭載。
* Glove端子(I2C)あり
* ピン数は少ない。
* USB-C接続。
* [実売2400円](https://www.amazon.co.jp/dp/B07R1QDVWF)

![M5Stick-C Pins](https://d2l930y2yx77uc.cloudfront.net/production/uploads/images/13390502/picture_pc_c725fbd72b41c82efaf5e3de0c36f2ca.png)

M5Stick-Cのピン配置。

### ESP-01S

* ESP8266チップ
* Wifi搭載。
* ピン数はとても少ない。電源制御に特化したデバイス。
* 3.3 V出力。
* [書き込み用のUSB-Serialデバイスが別途必要。](https://solarbotics.com/product/29246/)
  ![](https://cdn.solarbotics.com/products/photos/98d4879fbb50d9abca1d3153a1cf0ed9/ftdy%20to%20esp01%20diagram.jpg?w=375)
* [実売400円(リレー付き)](https://www.amazon.co.jp/dp/B07MF6SYGQ) 

![ESP-01s Pins](https://simba-os.readthedocs.io/en/2.0.0/_images/esp01-pinout.png)
ESP-01sのピン配置。

## ハードウェアごとの設定

### 共通

マイコンとの間のデータ転送には、USB上で仮想的にシリアル通信を行う。そのためのドライバーがホストOS側にインストールされている必要がある。

* 参考: https://qiita.com/itiB_S144/items/7a232c1a31151fcb5e5b
* [CP210x USB - UART ブリッジ VCP ドライバ](https://jp.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)

### Arduino Nano

* [ht-deco](https://ht-deko.com/arduino/nano.html)を参照
* Board: "Arduino Nano"
* Processor: ATMega328P(Old Bootloader)

### NodeMCU←今回はこれ

* [Install extra library for ESP8266](https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/)
* Board: "NodeMCU 1.0 (ESP-12E Module)"
* 経験上、wdt(watchdog timer)が悪さをする。`loop()`内の処理に時間がかかりすぎると自動リセットされる!
 
### M5StickC

* [Install extra library for M5Stick-C](https://github.com/m5stack/M5StickC)
* Board: "M5Stick-C"
* Beta版のArduino IDEが要るかも。
* 書き込み時にジャンパー線でGNDとG0を直結する必要あり。
  * [Qiita](https://qiita.com/SamAkada/items/fa32d6072a832a10cd84)

### ESP-01s

* [Install extra library for ESP8266](https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/)
* フラッシュメモリの書き込みにはシリアルtoUSBデバイスが必要。[実売450円](https://www.amazon.co.jp/dp/B07VZX8SXD)
* 書き込みのために、基板上の抵抗(R1?)を1つ外す必要があった。

## ホストOS固有の設定

## プログラム開始

1. ArduinoマイコンをUSBで接続する。
2. 新しいプロジェクトをひらくと、あらかじめ`setup`と`loop`が書きこまれている。`setup`はその名の通り、Arduinoの電源が入って最初に一回だけ実行される部分、`loop`は何度も繰り返し実行される部分。
3. この2つの中に、ハードウェア(LED、外付けデバイスなど)の制御の方法をいろいろ書きこむ。
4. 「✓」を押してコンパイル→エラーがでれば3へ戻る。
5. 「→」を押してArduinoに書き込む。ここでエラーが出る場合は、通信で失敗しているか、プログラムが大きすぎて書きこめないか。
6. 無事書きおわると、Arduinoはリセットされて自動的に動きはじめる。
7. 実行状況はSerial Monitorで確認。

### LEDの点滅

Arduino NanoとNodeMCUは基板上にLEDが直付けされている。

Arduino NanoはD13、NodeMCUはD4、ESP-01Sは1。

```BlinkLED.ino
int led=D4; // NodeMCU, Blue

void setup(){                // { }内をはじめに1度だけ実行する
  Serial.begin(9600);
  pinMode(led, OUTPUT);      // ledピン(11ピン)を出力にする
}
void loop(){                 // { }内を繰り返し実行する
  Serial.println("On");
  digitalWrite(led, HIGH);   // ledピンにHIGHを出力する
  delay(1000);               // 1秒(1000ms)待つ
  Serial.println("Off");
  digitalWrite(led, LOW);    // ledピンにLOWを出力する
  delay(1000);               // 1秒(1000ms)待つ
}
// M5Stack/M5StickにはLEDがない。
```

Serial Monitorを開くと、実行状況(Arduinoからのメッセージ)を読みとれる。

明るさを調節する場合は、PWM出力で調節。(点灯と消灯を高速で繰りかえすことで明度を調節する方法) (LEDがPWM出力に対応したピンに接続されている場合)

```GradeLED.ino
int led=D4; //NodeMCU
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
```

### 外部デバイスの制御

外部デバイスの制御方法はそれぞれに作法があり、コントローラが必要なもの(ステッピングモーター類など)や回路が必要なもの、特別な通信手順に従う必要があるものなどさまざまである。だが、ほとんどのデバイスについて、Arduinoに接続する方法はインターネットをさがせば見付かる。(インターネットで情報がみつかるデバイスを選んで接続するのが良い。)

小さなサーボモーターや短いLEDテープの場合は、直結できるのでかなり手っ取り早い。(同じサーボモーターやLEDテープでも消費電力が大きい場合にはすこし工夫が必要になってくる)

#### NeoPixel LEDテープ

外付けLEDテープを光らせてみる。NeoPixel WS2812、5 V駆動。すべてのLEDの明るさを個別に指定できるLEDテープ。(ほかに、全体を同じ色で指定できるもの、色が変えられないものもある。)

* とりあえず、"NeoPixel WS2812 Arduino"で検索する。
  * Arduino IDEにNeoPixel用のライブラリを追加する。Adafruit NeoPixelライブラリが便利そう。
  * GNDと電源(+5V)と信号線の3線を、NodeMCUのGNDとVIN(+5V)とD6に接続する。ショートさせないように注意すること。
* File→スケッチ例→Adafruit NeoPixel→strandtestを読み込み、Pin番号をD6、LED数を6に設定する。

#### サーボモーター

サーボモーターは、ラジコンの制御でよく使われる、有限範囲でしか回転できないモーター。

アナログ方式のサーボモーターでは、PWMのデューティー比で角度を指定するらしい。ということは、上のLEDの明るさを段階的に変化させるプログラムをそのまま流用して、モーターを動かせるはずだ。やってみよう。

今手元にあまっているのは、SG90という型番のサーボモーター。これを"Arduino SG90"で検索すると、[日本語の解説記事](https://monoist.atmarkit.co.jp/mn/articles/1605/12/news007_2.html)もみつかる。

##### ハードウェア(結線)
茶色をGND(0V)、赤を3V3(+3.3V)、オレンジの信号線はD4端子につなぐ。

##### ソフトウェア

Servoライブラリをそのまま使うことにする。Arduino IDE→ファイル→スケッチ例→Servo(ESP8266)→Sweepを呼びだすと、以下のようなサンプルコードが表示される。

```c
/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 28 May 2015
  by Michael C. Miller
  modified 8 Nov 2013
  by Scott Fitzgerald

  http://arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards


void setup() {
  myservo.attach(D5);  // D5ピンにサーボの黄色の信号線をつなぐ。
}

void loop() {
  int pos;

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
```
ピン番号2(GPIO2)はD4端子に相当するが、ややこしいので、`attach(2)`は`attach(D4)`と書きかえておこう。

#### ステッピングモーター

ステッピングモーターは、正確に回転角を指定して回せるモーター。コントローラICを経由して制御する。

今回は省略。

### 通信(Blynkでの制御1)

[Blynk](https://blynk.io)はIoT開発者のためのライブラリ。わずかなプログラムの書換えだけで、Arduinoをスマホで制御可能にする。

1. スマホにBlynkアプリをインストール。
  1. アカウントを作成
  2. New Projectでプロジェクト作成
  3. デバイス名を選ぶ(EPS8266 or NodeMCU)。Connection TypeはWifi。
  4. Auth Token(認証符丁)がメールで送られてくる。これをArduinoのプログラムに書きこむ必要がある。
  6. 方眼紙の画面をタッチし、ボタンを1つ置く。
    * ボタン1つで200ポイント消化する。
    * 最初にもらった2000ポイントを使い切ると課金がはじまる。
  7. ボタンを押すと、細かい設定ができる。OutputをDigitalのD4(NodeMCUのOnboard LED)に設定する。
2. Arduino側の準備
  1. ArduinoにはBlynkのライブラリを追加する。(スケッチ→ライブラリをインクルード→ライブラリを管理→blynkで検索)
  2. Arduino用のプログラムは以下の通り。([Blynkのサンプル](https://examples.blynk.cc/?board=ESP8266&shield=ESP8266%20WiFi&example=GettingStarted%2FBlynkBlink))

```
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

extern char auth[],ssid[],pass[];

void setup()
{
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
``` 

(SSID, Password, AuthTokenは別ファイルで指定する)

上のプログラムには、LEDの接続されているピンの番号などの情報は全く含まれていない。`Blynk.run()`の中で、すべてが自動的に処理される。

ボタンの代わりにスライダーを置き、それをD4ピンに連結する。スライダーの値の範囲は0〜1023とする。BlynkはNodeMCUのD4ピンがPWM制御できると知っているので、スライダーの値がそのままLEDの明るさになる。

### 通信(Blynkでの制御2)

ステッピングモーターを制御する場合には、BlynkのUIでのボタンの状態やスライダーの状態をそのまま端子に渡すだけではうまくいかないので、それらの状態値をArduinoのプログラム側で読みとり、適切な信号をピンに送る必要がある。このような場合にはVirtual Pinを利用する。Virtual PinはBlynk UI側からピンのように見え、Arduino側からは変数のように見える。

新しいスライダーを設置し、仮想ピンV1に信号を出すようにする。数値の範囲は、0〜180としよう。

Arduinoプログラム側では、V1の値に応じてステッピングモーターを動かす。これはBlynkのサンプルコード(ファイル→スケッチ例→Blynk→GettingStarted→VirtualPinRead)がとても参考になる。

サーボモーターはD5ピンに接続し、仮想ピンV1の値が変化したら、その値を角度とみなして、myservo.write()でサーボモーターに書き込む。

```
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

extern char auth[],ssid[],pass[];

void setup()
{
  Blynk.begin(auth, ssid, pass);
  myservo.attach(D5);  // attaches the servo on D5 to the servo object
}

void loop()
{
  Blynk.run();
}

// コールバック関数。スマホでスライダーを動かすと、この関数が呼びだされる。
BLYNK_WRITE(V1)
{
  int angle = param.asInt(); // assigning incoming value from pin V1 to a variable
  myservo.write(angle); //サーボの角度を指定
}
```



### 通信(Blynkへの制御)

[Blynkの文書](https://blynkapi.docs.apiary.io/#reference/0/write-pin-value-via-get/write-pin-value-via-get)によれば、ピンの値はウェブブラウザからURLを通じて設定できる。例えば、

* [http://blynk-cloud.com/auth_token/update/V1?value=0](http://blynk-cloud.com/auth_token/update/V1?value=0)
* [http://blynk-cloud.com/auth_token/update/v1?value=180](http://blynk-cloud.com/auth_token/update/v1?value=180)

(`auth_token`はBlynkのAuth Token文字列におきかえる)
にアクセスすれば、スマホでスライダーを動かしたのと同じようにサーボモーターを動かすことができる。(ただしD4ピンだとうまくいかない。なぜだ!)。

### 通信(IoT)

[Blynk](https://blynk.io)は[IFTTT](https://ifttt.com)とも連携でき、[IFTTT](https://ifttt.com)はGoogle HomeやAmazon Echoと連携できるので、Blynkに対応させたデバイスは音声で制御できることになる。

詳しくは[こちら。](https://www.mgo-tec.com/blog-entry-esp32-googlehome-ifttt-webhooks-blynk.html)




