## **Round watch development board  summary **

###### Hardware features:

- [ ] Pulse and SPO2 measuring

- [x] Integration with ST7789V display driver

- [x] LVGL library porting

- [x] BLE custom service

- [ ] Time displaying ( RTC )

- [ ] Time synchronization over BLE Service

- [x] Battery level displaying BLE

- [ ] Battery level displaying Display

- [ ] Accelerometer clock sleep out

- [ ] Energy-Save mode

  

  ###### Android integration:

- [ ] Alarms support

- [ ] Notifications from Android device

- [ ] Music switching over Android device

  

  ###### Optional / Additional features

- [ ] Simple 3D render engine for triangles wireframe rendering

- [ ] Mobile application

- [x] CMake-based  build for project

- [x] VSCode debug & development

- [x] KiCad as CAD system for PCB

- [ ] I2S micro for audiomessages

- [ ] Research lightweight inter-processor communication

## **Part list:**

### **MCU:**

NRF52832-E73 module

#### **Accelerometer:**

MPU9250

#### Display module:

ST7789V Round, resolution 240 * 240 or 240 * 208

https://github.com/ValentiWorkLearning/ST7789_Round_DevBoard/tree/master/Panel

https://ru.aliexpress.com/item/1962405888.html?spm=a2g0o.cart.0.0.38713c00M67wvz&mp=1



#### PulseOximeter:

MAX30102/MAX30100

http://www.kosmodrom.com.ua/el.php?name=MAX30100-MODUL

#### **Logic converter:**

TX0108E

http://www.kosmodrom.com.ua/el.php?name=TXS0108EPWR

**Battery controller:**

LTC4054ES5-4.2

http://www.kosmodrom.com.ua/el.php?name=LTC4054ES5-4.2

**LDO**

1. 1.8V - MCP1700T-1802 http://www.kosmodrom.com.ua/el.php?name=MCP1700T-1802E_MB
2. 3.3V - MCP1700T-3302 http://www.kosmodrom.com.ua/el.php?name=MCP1700T-3302E_TT
3. 2.8V - LP2985 http://www.kosmodrom.com.ua/el.php?name=LP2985AIM5-2.8_NOPB

#### Schematic Libraries:

- Nordic nRF52832 MOD

https://kicad.github.io/symbols/RF_Module

- W25Q128

[https://www.snapeda.com/parts/W25Q16BVSSIG/Winbond%20Electronics/view-part/](https://www.snapeda.com/parts/W25Q16BVSSIG/Winbond Electronics/view-part/) 

- MPU-9250

[https://www.snapeda.com/parts/MPU-9250/TDK%20InvenSense/view-part/](https://www.snapeda.com/parts/MPU-9250/TDK InvenSense/view-part/)



#### Software dependencies:

* LVGL - https://github.com/littlevgl/lvgl - open-source embedded GUI library
* Callback connector - library for wrapping C++ class members into C-style callback 

https://github.com/Toxa-man/CallbackConnector 

* Lightweight C++ signals for small systems  https://github.com/larspensjo/SimpleSignal
* SDL-mirror - is used by Simulator subproject https://github.com/spurious/SDL-mirror



