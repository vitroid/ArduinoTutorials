# マイコンの開発入門
* Arduino
* NodeMCU
* ESP32
* M5Stack
* M5Stick

これらのマイコン(マイクロコントローラ)を開発する環境は

* Arduino (C++)
* UIFlow (MicroPython)
* Obniz (JavaScript)

などがある。それぞれ一長一短あるが、今回は最もシンプルなハードウェアを利用できるArduinoを選ぶ。(UIFlowはその名の通りUIを設計するのには適しているが画面を持たないマイコンでは有り難みが少ない。Obnizは常時インターネット接続が前提)

## Arduino IDEのインストール

* https://www.arduino.cc/ からArduino IDE 1.8.10をダウンロードしてインストール。(2019-11-11現在)

## ハードウェア

今回準備しているのは以下の3種類。どれもArduino IDEでプログラム開発可能。

### Arduino Nano

* [解説(英語)](https://www.theengineeringprojects.com/2018/06/introduction-to-arduino-nano.html)
* ATMega328P (Arduino互換)
* 一番パッケージ小さい。
* Wifi/BlueTooth非搭載
* MiniUSB接続。
* [実売250円](https://www.amazon.co.jp/dp/B07VVWGW2V)

![Arduino Nano Pins](http://christianto.tjahyadi.com/wp-content/uploads/2014/11/nano.jpg)
Arduino Nanoのピン配列



### NodeMCU

* [解説(英語)](https://lastminuteengineers.com/esp8266-nodemcu-arduino-tutorial/)
* ESP8266チップ
* Wifi/BlueTooth搭載
* AD端子(アナログ入力端子)が1本しかない。
* いくつかのピンがWifiチップに使われていて、ユーザーの使えるピンは少ない?
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
* 3.3 V出力
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

### NodeMCU

* [hatena](https://uepon.hatenadiary.com/entry/2017/05/13/022135)
* Board: "NodeMCU 32S"

### M5StickC

* [Qiita](https://qiita.com/SamAkada/items/fa32d6072a832a10cd84)
* Board: "M5Stick-C"
* Beta版のArduino IDEが要るかも。
* 書き込み時にジャンパー線でGNDとG0を直結する必要あり。
  * [Qiita](https://qiita.com/SamAkada/items/fa32d6072a832a10cd84)

### ESP-01s

* フラッシュメモリの書き込みにはシリアルtoUSBデバイスが必要。[実売450円](https://www.amazon.co.jp/dp/B07VZX8SXD)
* 書き込みのために、基板上の抵抗(R1?)を1つ外す必要があった。

## ホストOS固有の設定

## プログラム開始

1. ArduinoマイコンをUSBで接続する。

2. Arduino IDEを開く。Newで新しいプロジェクトをひらくと、あらかじめ`setup`と`loop`が書きこまれている。`setup`はその名の通り、Arduinoの電源が入って最初に一回だけ実行される部分、`loop`は何度も繰り返し実行される部分。

4. この2つの中に、ハードウェア(LED、外付けデバイスなど)の制御の方法をいろいろ書きこむ。
5. 「✓」を押してコンパイル→エラーがでれば4へ戻る。
6. 「→」を押してArduinoに書き込む。ここでエラーが出る場合は、通信で失敗しているか、プログラムが大きすぎて書きこめないか。
7. 無事書きおわると、Arduinoはリセットされて自動的に動きはじめる。
8. 実行状況はSerial Monitorで確認。

### LEDの点滅

Arduino NanoとNodeMCUは基板上にLEDが直付けされていて、それを点滅することも可能。

Arduino NanoはD13、NodeMCUはD0、ESP-01Sはxx、Arduino IDEの中では"LED_BUILTIN"で定義済み。

```
int led=LED_BUILTIN;         // 変数ledにLED_BUILTINを代入する
void setup(){                // { }内をはじめに1度だけ実行する
  Serial.begin(9600);
  pinMode(led, OUTPUT);      // ledピンを出力にする
}
void loop(){                 // { }内を繰り返し実行する
  digitalWrite(led, HIGH);   // ledピンにHIGHを出力する
  Serial.println("on");
  delay(1000);               // 1秒(1000ms)待つ
  digitalWrite(led, LOW);    // ledピンにLOWを出力する
  Serial.println("off");
  delay(1000);               // 1秒(1000ms)待つ
}
```

Serial Monitorを開くと、実行状況(Arduinoからのメッセージ)を読みとれる。

明るさを調節する場合は、PWM出力で調節。(点灯と消灯を高速で繰りかえすことで明度を調節する方法) (LEDがPWM出力に対応したピンに接続されている場合)

```
int led=LED_BUILTIN;       
void setup(){              
  pinMode(led, OUTPUT);    
}
int 
void loop(){               
  analogWrite(led, 1023);   // Dピンに対してanalogWriteするとPWM
  delay(1000);            
  analogWrite(led, 200);    // 200/1024だけ光る。
  delay(1000);             
}
```

### 外部デバイスの制御

外付けLEDテープを光らせてみる。NeoPixel WS2812、5 V駆動。すべてのLEDの明るさを個別に指定できるLEDテープ。(ほかに、全体を同じ色で指定できるもの、色が変えられないものもある。)

とりあえず、"NeoPixel WS2812 Arduino"で検索する。

Arduino IDEにNeoPixel用のライブラリを追加する。FastLEDが便利そう。

配線とサンプルプログラムは[この記事](https://howtomechatronics.com/tutorials/arduino/how-to-control-ws2812b-individually-addressable-leds-using-arduino/)を参考にする。




### 通信(Blynkでの制御)

[Blynk](https://blynk.io)はIoT開発者のためのライブラリ。わずかなプログラムの書換えだけで、Arduinoをスマホで制御可能にする。

1. スマホにBlynkアプリをインストール。
2. アカウントを作成
3. New Projectでプロジェクト作成
4. デバイス名を選ぶ(EPS8266 or NodeMCU)。Connection TypeはWifi。
5. Auth Token(認証符丁)がメールで送られてくる。これをArduinoのプログラムに書きこむ必要がある。
6. 方眼紙の画面をタッチし、ボタンを1つ置く。
  * 200ポイント消化する。
  * 最初にもらった2000ポイントを使い切ると課金がはじまる。
7. ボタンを押すと、細かい設定の画面に入る。OutputをDigitalのD0(Onboard LED)に設定する。
8. ArduinoにはBlynkのライブラリを追加する。
9. Arduino用のプログラムは以下の通り。([Blynkのサンプル](https://examples.blynk.cc/?board=ESP8266&shield=ESP8266%20WiFi&example=GettingStarted%2FBlynkBlink))

```
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "YourAuthToken";

char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

void setup()
{
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
``` 

上のプログラムには、LEDの接続されているピンの番号などの情報は全く含まれていない。`Blynk.run()`の中で、すべてが自動的に処理される。

ボタンの代わりにスライダーを置き、それをD0ピンに連結する。スライダーの値の範囲は0〜1023とする。BlynkはD0ピンがPWM制御できると知っているので、スライダーの値がそのままLEDの明るさになる。

LEDテープを制御する場合には、BlynkのUIでのボタンの状態やスライダーの状態をそのまま端子に渡すだけではうまくいかないので、それらの状態値をArduinoのプログラム側で読みとり、適切な信号をピンに送る必要がある。このような場合にはVirtual Pinを利用する。Virtual PinはBlynk UI側からピンのように見え、Arduino側からは変数のように見える。



### 通信(IoT)

[Blynk](https://blynk.io)は[IFTTT](https://ifttt.com)とも連携でき、[IFTTT](https://ifttt.com)はGoogle HomeやAmazon Echoと連携できるので、Blynkに対応させたデバイスは音声で制御できることになる。





