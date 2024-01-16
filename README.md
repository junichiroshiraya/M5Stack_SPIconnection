# M5Stack_SPIConnection

このコードは、M5Stack Basicで単純なSPI通信を試すために書いたものです。誰かの参考になればと思い載せています。
Visual Studio Code上のPlatform IOで作成したものですが、src/main.cppにあるコードをそのままArduino IDEに貼り付けても動作します。

## 要点
`SPI.begin(SCK, MISO, MOSI, SS)`はこの通りに書くと、M5Stackに書いてあるデフォルトのSPI端子（SCK=18, MISO=19, MOSI=23）とSS=5でSPI通信をするようになります。
`SCK, MISO, MOSI, SS`はそれぞれピンの番号に置き換えると、そのピンを利用できます。

`SPI.setHwCs(true)`を`true`にすると、CS（Chip Select、SS(Slave Select)と同じ）信号を自動的にオンオフするようになります。

`SPI.endTransaction()`と`SPI.beginTransaction()`は対で、送受信の開始・終了をします。

`SPI.beginTransaction(SPISettings())`のうち`SPISettings()`はデフォルトで`SPISettings(1000000, SPI_MSBFIRST, SPI_MODE0)`となっています。第一引数はクロック周波数(Hz)、第二引数はビット順序（MSBかLSBか）、第三引数は通信モードです。SPIの通信モードは、クロック極性（クロックが動作していない状態がLOW/HIGHのどちらか）・クロック位相（送受信のタイミングが立ち上がり（LOWからHIGH）／立ち下がり（HIGHからLOW）のどちらか）に応じて0から3まであります。
|転送モード|クロック極性|クロック位相|
|SPI_MODE0|LOW|立ち上がり|
|SPI_MODE1|LOW|立ち下がり|
|SPI_MODE2|HIGH|立ち上がり|
|SPI_MODE3|HIGH|立ち下がり|

実際にデータを送信する関数は`SPI.transfer(data)`と`SPI.write(data)`の2種類あり、前者はMISO端子での受信データを返り値として返しますが、後者は何も返しません。また、それぞれ2バイト用の`transfer16()`/`write16()`関数や4バイト用の`transfer32()`/`write32()`関数などがあります。
