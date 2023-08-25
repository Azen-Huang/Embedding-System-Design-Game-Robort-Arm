# Game robot arm
### Embedding System Design and Alpha-Beta pruning algorithm.
Demo Link: 
https://drive.google.com/drive/folders/1OCGwnz1k-QjAqsvO3B53MzyZcwzpEtVe?usp=share_link

***
確保Arduino有內置BLE  
並且可以include以下libary。  

'''  
#include <Arduino.h>  
#include <Servo.h>  
#include <Wire.h>  
#include <OV7670.h>  
#include <SoftwareSerial.h>  
'''  

確保C++版本為C++17  
並且可以include以下  
'''  
#include <iostream>  
#include <vector>  
#include <cstdlib>  
#include <ctime>  
#include <Windows.h>  
#include <Windows.Devices.Bluetooth.h>  
#include <Windows.Devices.Enumeration.h>  
'''  

將Arduino和c++程式同時開啟。  

因為棋盤設計和攝像頭的位置設備上的不同可能無法準確執行。  

***

![image](https://github.com/Azen-Huang/Embedding-System-Design-Game-Robort-Arm/blob/main/readme/1.png)

![image](https://github.com/Azen-Huang/Embedding-System-Design-Game-Robort-Arm/blob/main/readme/2.png)

![image](https://github.com/Azen-Huang/Embedding-System-Design-Game-Robort-Arm/blob/main/readme/3.png)

![image](https://github.com/Azen-Huang/Embedding-System-Design-Game-Robort-Arm/blob/main/readme/4.png)

![image](https://github.com/Azen-Huang/Embedding-System-Design-Game-Robort-Arm/blob/main/readme/5.png)

***