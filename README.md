[TOC]

# Arduino Short Tutorial

* Nov 11, 2019起稿
* 14:00-16:00 Nov 11, 2019実施予定 B-133室

## もってきてほしいもの

* Note PC
* MicroUSB cable
* バッテリ(もしあれば)

## 注意

* 電気接点が露出しています。ショートに気をつけて下さい。感電することはまずありませんが、回路を焼く可能性があります。
* 長時間、人のいないところで稼動させる場合には、絶縁をしっかり行って下さい。

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

これらのマイコン(マイクロコントローラ)を開発する環境は

* Arduino
* UIFlow
* Obniz

などがある。それぞれ一長一短あるが、今回は最もシンプルなハードウェアを利用できるArduinoを選ぶ。(UIFlowはその名の通りUIを設計するのには適しているが画面を持たないマイコンでは有り難みが少ない。Obnizは常時インターネット接続が前提)

|IDE|Arduino IDE| UIFlow    | Obniz    |
|---|-----------|-----------|----------|
|言語|C++        |MicroPython|JavaScript|
|開発時Network| 不要 | 必要 | 必要 |
|運用時Network| 不要 | 不要 | 必要 |
|リアルタイム制御| ◎ | ○ | △ |
|Webとの親和性| △ | △ | ◎ |


## Arduino IDEのインストール

* [Arduino IDE 1.8.10](https://www.arduino.cc/)をダウンロードしてインストール。(2019-11-11現在)

## ハードウェア

以下のマイコンはどれも[Arduino IDE](https://www.arduino.cc/)でプログラム開発可能。

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
* Wifi搭載
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
* 値段は他に比べれば高いが、いろいろ快適。

![M5Stick-C Pins](https://d2l930y2yx77uc.cloudfront.net/production/uploads/images/13390502/picture_pc_c725fbd72b41c82efaf5e3de0c36f2ca.png)

M5Stick-Cのピン配置。

### ESP-01S

* ESP8266チップ
* Wifi搭載。
* ピン数はとても少ない。電源制御に特化したデバイス。単体で100 Vの開閉ができる。
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

ピンの番号はマイコンによって違う。Arduino NanoはD13、NodeMCUはD4、ESP-01Sは1 (GPIO1)、M5Stack-Cは10 (GPIO10)。

"D4"はマイコンに刻印されているピン名を指している。だいたいピンの並び順で番号が振られている「物理順序」。

"GPIOx"はチップ内部から見た、インターフェイスの呼び名。「論理順序」

これらの対応は、前節のピン配置図を見て確認してほしい。

```c++
int led=D4; // NodeMCU, Blue
//int led=10; //G10, M5Stick-C, Red

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
```

Serial Monitorを開くと、実行状況(Arduinoからのメッセージ)を読みとれる。

明るさは、[PWM出力](https://circuits4you.com/2017/12/21/esp8266-pwm-example/)で調節。(点灯と消灯を高速で繰りかえすことで明度を調節する方法) デューティー比(全時間に対する、消灯時間の割合)を0〜1023の間で調節すると、見た目の明るさが変化する。LEDの配線のしかたにより、0で消灯する場合と1023で消灯する場合がある。

```c++
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
// M5Stack/M5StickではanalogWriteがない。
```

### 外部デバイスの制御

外部デバイスの接続方法はいろいろあるが、基本的には1本の電源線(+5 Vまたは+3.3 V)と1本の接地線(0 V)と1本1以上の信号線で接続するものがほとんどである。プログラムで信号線に適切な信号を送ったり、逆に信号を読みとったりすることで外部デバイスを制御する。

また、外部デバイスの制御方法もそれぞれに作法があり、コントローラICが必要なもの(ステッピングモーター類など)や回路が必要なもの、特別な通信手順に従う必要があるものなどさまざまである。だが、ほとんどのデバイスについて、Arduinoに接続する方法はインターネットをさがせば見付かる。

Arduinoが持つ接続ピンにもいろいろ種類がある。

* GPIO: 汎用Input/Output端子。デジタル信号を出すことも読むこともできる。D0, D1あるいはG10といったラベルがついている。
* AD: Arduino内部のA/D変換器に接続されており、電圧を読みとれる。ラベルはA1, A2, ... .
* SPI, I2C, Grove: デバイスとの間の通信に使える。
* VIN: 電源入力用端子。USB以外の外部電源から電気をとりいれる場合に使用。電気をとりだすことはできない。
* GND: 接地。0 V。信号電圧の基準点
* 3V3: 3.3 Vの端子。外部デバイスの電源にも使える。

それぞれのデバイスをつなぐことができるピンは決まっている。無線カードリーダー(ICOCA)はSPI端子につなぎ、マイクはAD端子につながなければ機能しない。ESP-01sのようにSPI端子もAD端子ももたないマイコンではこれらのデバイスは使えないので、試作段階ではできるだけ多機能なマイコンを使うのが良い。

#### NeoPixel LEDテープ

外付けLEDテープを光らせてみる。NeoPixel WS2812、5 V駆動。すべてのLEDの明るさを個別に指定できるLEDテープ。(ほかに、全体を同じ色で指定できるもの、色が変えられないものもある。)

* とりあえず、"NeoPixel WS2812 Arduino"で検索する。
  * Arduino IDEにNeoPixel用のライブラリを追加する。Adafruit NeoPixelライブラリが便利そう。
  * GNDと電源(+5V)と信号線の3線を、NodeMCUのGNDとVIN(+5V)とD6に接続する。ショートさせないように注意すること。
* File→スケッチ例→Adafruit NeoPixel→strandtestを読み込み、Pin番号をD6、LED数を6に設定する。

#### サーボモーター

サーボモーターは、ラジコンの制御でよく使われる、有限範囲でしか回転できないモーター。

アナログ方式のサーボモーターでは、PWMのデューティー比で角度を指定するらしい。ということは、上のLEDの明るさを段階的に変化させるプログラムをそのまま流用して、モーターを動かせるはずだ。やってみよう。

今手元にあるのは、SG90という型番のサーボモーター。これを"Arduino SG90"で検索すると、[日本語の解説記事](https://monoist.atmarkit.co.jp/mn/articles/1605/12/news007_2.html)もみつかる。

##### ハードウェア(結線)
茶色をGND(0V)、赤を3V3(+3.3V)、オレンジの信号線はD5端子につなぐ。

##### ソフトウェア

Servoライブラリをそのまま使うことにする。Arduino IDE→ファイル→スケッチ例→Servo(ESP8266)→Sweepを読みこみ、`setup()`を以下のように書きかえる。

```c++
void setup() {
  myservo.attach(D5);  // D5ピンにサーボの黄色の信号線をつなぐ。
}
```

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

```c++
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

```c++
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo myservo;  // サーボオブジェクト

extern char auth[],ssid[],pass[];

void setup()
{
  Blynk.begin(auth, ssid, pass);
  myservo.attach(D5);  // サーボモーターの信号線がD5に接続されている。
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



### 通信(Blynkへの制御、Web API)

[Blynkの文書](https://blynkapi.docs.apiary.io/#reference/0/write-pin-value-via-get/write-pin-value-via-get)によれば、ピンの値はウェブブラウザからURLを通じて設定できる。例えば、

* [http://blynk-cloud.com/auth_token/update/V1?value=0](http://blynk-cloud.com/auth_token/update/V1?value=0)
* [http://blynk-cloud.com/auth_token/update/v1?value=180](http://blynk-cloud.com/auth_token/update/v1?value=180)

(`auth_token`はBlynkのAuth Token文字列におきかえる)
にアクセスすれば、スマホでスライダーを動かしたのと同じようにサーボモーターを動かすことができる。(ただしD4ピンだとうまくいかない。なぜだ!)。

### 通信(IoT)

[Blynk](https://blynk.io)は上のWeb APIを通じて[IFTTT](https://ifttt.com)とも連携でき、[IFTTT](https://ifttt.com)はGoogle HomeやAmazon Echoと連携できるので、Blynkに対応させたデバイスは音声で制御できることになる。

詳しくは[こちら。](https://www.mgo-tec.com/blog-entry-esp32-googlehome-ifttt-webhooks-blynk.html)




