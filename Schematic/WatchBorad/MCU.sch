EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 2 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Nordic:nRF52832-QFxx U2
U 1 1 5EA43A4B
P 5450 3350
F 0 "U2" H 6100 5300 100 0000 C CNN
F 1 "nRF52832-QFxx" H 6100 5175 50  0000 C CNN
F 2 "Housings_DFN_QFN:QFN-48-1EP_6x6mm_Pitch0.4mm" H 5450 1250 50  0001 C CNN
F 3 "http://infocenter.nordicsemi.com/pdf/nRF52832_PS_v1.4.pdf" H 4950 3550 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/RF-Transceiver-ICs_Nordic-Semicon-NRF52832-QFAA-R_C77540.html" H 5450 3350 50  0001 C CNN "lcsc"
	1    5450 3350
	1    0    0    -1  
$EndComp
Text Notes 3375 -1175 0    50   ~ 0
https://devzone.nordicsemi.com/nordic/power
Text Notes 3750 -1375 0    100  ~ 0
Useful sources
$Comp
L Device:C C15
U 1 1 5EAD01A9
P 4125 2875
F 0 "C15" H 3950 2975 50  0000 L CNN
F 1 "0.8 pF" H 3875 2775 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4163 2725 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CGR82C500NT_C501852.html" H 4125 2875 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CG0R8C500NT_C501845.html" H 4125 2875 50  0001 C CNN "lcsc"
	1    4125 2875
	1    0    0    -1  
$EndComp
Wire Wire Line
	4125 2725 4125 2650
Wire Wire Line
	4125 2650 4550 2650
Wire Wire Line
	4125 2650 3950 2650
Connection ~ 4125 2650
$Comp
L Device:L 3.9nH1
U 1 1 5EAD15C8
P 3800 2650
F 0 "3.9nH1" V 3750 2650 50  0000 C CNN
F 1 "L" V 3899 2650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3800 2650 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1907301703_Cybermax-CMCC1608C3N9SSP_C405057.pdf" H 3800 2650 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/HF-Inductors_Cybermax_CMCC1608C3N9SSP_Cybermax-CMCC1608C3N9SSP_C405057.html" V 3800 2650 50  0001 C CNN "lcsc"
	1    3800 2650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4125 3025 4125 3125
Wire Wire Line
	5450 5050 5450 5175
Text Notes 2300 -750 0    50   ~ 0
https://product.tdk.com/info/en/documents/antenna/designnote/dn-ant016008lcs2442ma2.pdf
Text Notes 600  2175 0    50   ~ 0
https://product.tdk.com/en/search/rf/rf/antenna/simulation?pid=1432889562964
Text Notes 2300 -525 0    50   ~ 0
https://infocenter.nordicsemi.com/pdf/nwp_017.pdf?cp=12_11
$Comp
L Device:C C13
U 1 1 5EAD533A
P 3475 2875
F 0 "C13" H 3525 2975 50  0000 L CNN
F 1 "0.8 pF" H 3525 2775 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3513 2725 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CGR82C500NT_C501852.html" H 3475 2875 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CG0R8C500NT_C501845.html" H 3475 2875 50  0001 C CNN "lcsc"
	1    3475 2875
	1    0    0    -1  
$EndComp
Wire Wire Line
	3475 2725 3475 2650
Wire Wire Line
	3475 2650 3650 2650
Wire Wire Line
	3475 3025 3475 3125
Text Notes 2300 -850 0    50   ~ 0
https://devzone.nordicsemi.com/nordic/short-range-guides/b/hardware-and-layout/posts/general-pcb-design-guidelines-for-nrf52
Connection ~ 3475 2650
Wire Wire Line
	3250 2650 3475 2650
Text Notes 2300 -950 0    50   ~ 0
https://devzone.nordicsemi.com/nordic/nordic-blog/b/blog/posts/nfc-tag-antenna-tuning
Text Notes 1925 4175 0    50   ~ 0
The SWDCLK line has an internal pull-down resistor.\nThe SWDIO line has an internal pull-up resistor.\n
Text Label 4025 4150 0    50   ~ 0
SWD_SWDIO
Text Label 4025 4050 0    50   ~ 0
SWD_SWDCLK
Wire Wire Line
	5250 1650 5250 1125
Wire Wire Line
	5250 1125 5525 1125
Text Label 5525 1125 2    50   ~ 0
DEC4
Wire Wire Line
	900  975  1175 975 
Text Label 900  975  0    50   ~ 0
DEC4
Wire Wire Line
	3475 3125 3700 3125
Wire Wire Line
	4550 3150 4325 3150
Wire Wire Line
	4550 3550 4325 3550
Text Label 4325 3150 0    50   ~ 0
XC1
Text Label 4325 3550 0    50   ~ 0
XC2
Wire Wire Line
	6350 1850 6525 1850
Wire Wire Line
	6350 1950 6525 1950
Text Label 6525 1950 2    50   ~ 0
XL2
Text Label 6525 1850 2    50   ~ 0
XL1
Wire Wire Line
	5450 1650 5450 1275
$Comp
L Device:C C?
U 1 1 5EB047A2
P 2475 1150
AR Path="/5EA4867C/5EB047A2" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EB047A2" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5EB047A2" Ref="C9"  Part="1" 
F 0 "C9" H 2500 1225 50  0000 L CNN
F 1 "10 uF" V 2325 1025 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2513 1000 50  0001 C CNN
F 3 "~" H 2475 1150 50  0001 C CNN
F 4 "" H 2475 1150 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 2475 1150 50  0001 C CNN "lcsc"
	1    2475 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5EB07296
P 2825 1150
AR Path="/5EA4867C/5EB07296" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EB07296" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5EB07296" Ref="C10"  Part="1" 
F 0 "C10" H 2850 1225 50  0000 L CNN
F 1 "100 nF" V 2675 1025 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2863 1000 50  0001 C CNN
F 3 "~" H 2825 1150 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 2825 1150 50  0001 C CNN "lcsc"
	1    2825 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5EB07FEF
P 3125 1150
AR Path="/5EA4867C/5EB07FEF" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EB07FEF" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5EB07FEF" Ref="C12"  Part="1" 
F 0 "C12" H 3150 1225 50  0000 L CNN
F 1 "100 nF" V 2975 1025 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3163 1000 50  0001 C CNN
F 3 "~" H 3125 1150 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 3125 1150 50  0001 C CNN "lcsc"
	1    3125 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2475 1300 2475 1350
Connection ~ 2475 1350
Wire Wire Line
	2475 1350 2825 1350
Wire Wire Line
	2825 1300 2825 1350
Connection ~ 2825 1350
Wire Wire Line
	2825 1350 3125 1350
Wire Wire Line
	3125 1300 3125 1350
Wire Wire Line
	2325 975  2475 975 
Wire Wire Line
	2475 975  2475 1000
Connection ~ 2475 975 
Wire Wire Line
	2475 975  2825 975 
Wire Wire Line
	2825 975  2825 1000
Connection ~ 2825 975 
Wire Wire Line
	2825 975  3125 975 
Wire Wire Line
	3125 975  3125 1000
Text Notes 2375 1450 0    50   ~ 0
48 pin\n
Text Notes 2800 1450 0    50   ~ 0
13,36 pins\n
$Comp
L Device:C C?
U 1 1 5EB1B82C
P 2150 1150
AR Path="/5EA4867C/5EB1B82C" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EB1B82C" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5EB1B82C" Ref="C7"  Part="1" 
F 0 "C7" H 2175 1225 50  0000 L CNN
F 1 "100 nF" V 2000 1025 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2188 1000 50  0001 C CNN
F 3 "~" H 2150 1150 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 2150 1150 50  0001 C CNN "lcsc"
	1    2150 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1175 1300 1175 1350
Wire Wire Line
	1175 975  1175 1000
Wire Wire Line
	2150 1000 2150 975 
Wire Wire Line
	2150 975  1950 975 
Wire Wire Line
	2150 1300 2150 1350
Wire Wire Line
	2150 1350 2475 1350
Text Label 1950 975  0    50   ~ 0
DEC1
Text Label 5150 775  2    50   ~ 0
DEC1
Wire Wire Line
	4950 1650 4950 775 
Wire Wire Line
	4950 775  5150 775 
Wire Wire Line
	5050 1650 5050 900 
Wire Wire Line
	5050 900  5225 900 
Wire Wire Line
	5150 1650 5150 1000
Wire Wire Line
	5150 1000 5300 1000
Text Label 5225 900  2    50   ~ 0
DEC2
Text Label 5300 1000 2    50   ~ 0
DEC3
Wire Notes Line
	3325 3350 4275 3350
Wire Notes Line
	4275 2300 3325 2300
Text Notes 3425 2450 0    50   ~ 0
Impedance matching
$Comp
L Device:C C?
U 1 1 5EB30059
P 1800 1150
AR Path="/5EA4867C/5EB30059" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EB30059" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5EB30059" Ref="C5"  Part="1" 
F 0 "C5" H 1825 1225 50  0000 L CNN
F 1 "100 pF" V 1650 1025 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1838 1000 50  0001 C CNN
F 3 "~" H 1800 1150 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 1800 1150 50  0001 C CNN "lcsc"
	1    1800 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 1000 1800 975 
Wire Wire Line
	1800 975  1600 975 
Wire Wire Line
	1800 1300 1800 1350
Text Label 1600 975  0    50   ~ 0
DEC2
Connection ~ 2150 1350
$Comp
L Device:C C?
U 1 1 5EB34F3F
P 1475 1150
AR Path="/5EA4867C/5EB34F3F" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EB34F3F" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5EB34F3F" Ref="C3"  Part="1" 
F 0 "C3" H 1500 1225 50  0000 L CNN
F 1 "100 pF" V 1325 1025 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1513 1000 50  0001 C CNN
F 3 "~" H 1475 1150 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 1475 1150 50  0001 C CNN "lcsc"
	1    1475 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1475 1000 1475 975 
Wire Wire Line
	1475 975  1275 975 
Wire Wire Line
	1475 1300 1475 1350
Text Label 1275 975  0    50   ~ 0
DEC3
Wire Wire Line
	1175 1350 1475 1350
Connection ~ 1475 1350
Wire Wire Line
	1475 1350 1800 1350
Connection ~ 1800 1350
Text Label 4025 3950 0    50   ~ 0
SWD_RESET
Wire Wire Line
	4025 3950 4550 3950
Wire Wire Line
	4025 4050 4550 4050
Wire Wire Line
	4025 4150 4550 4150
Wire Wire Line
	6350 3650 6725 3650
Text Label 6725 3650 2    50   ~ 0
SWD_SWO
Wire Wire Line
	8475 5950 8900 5950
Text Label 8900 5950 2    50   ~ 0
LEDK
Wire Wire Line
	6400 6250 6675 6250
Text Label 6525 6250 0    50   ~ 0
GND
Text Notes 5850 6775 0    50   ~ 0
inernal pull-down\nHigh level input min 1.3V
Text Label 6075 6525 0    50   ~ 0
Backlight_EN_DIM
Wire Wire Line
	6075 6525 6675 6525
$Comp
L LocalLedDrivers:CAT4002ATD-GT3 U3
U 1 1 5EAE51FD
P 6675 5950
F 0 "U3" H 7575 6337 60  0000 C CNN
F 1 "CAT4002ATD-GT3" H 7575 6231 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6_Handsoldering" H 7575 6190 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1809111523_ON-Semiconductor-CAT4002ATD-GT3_C184641.pdf" H 6675 5950 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/LED-Drivers_ON-Semiconductor-ON-CAT4002ATD-GT3_C184641.html" H 6675 5950 50  0001 C CNN "lcsc"
	1    6675 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8475 6050 8475 5950
Connection ~ 8475 5950
Wire Wire Line
	8475 6450 8750 6450
Wire Wire Line
	8750 6750 8750 6800
Wire Notes Line
	5350 5500 9550 5500
Wire Notes Line
	9550 5500 9550 7000
Wire Notes Line
	9550 7000 5350 7000
Wire Notes Line
	5350 7000 5350 5500
Text Notes 5650 5625 0    50   ~ 0
Constant current led driver\n
Wire Notes Line
	725  3975 725  3000
Wire Notes Line
	3225 3975 725  3975
Wire Notes Line
	3225 3000 3225 3975
Wire Notes Line
	725  3000 3225 3000
Text Notes 1725 3125 0    50   ~ 0
Crystal oscillator\n
Text Notes 1250 3875 0    50   ~ 0
32 MHz
Connection ~ 1400 3750
Wire Wire Line
	1650 3750 1400 3750
Wire Wire Line
	1650 3725 1650 3750
Wire Wire Line
	1150 3750 1400 3750
Wire Wire Line
	1150 3725 1150 3750
$Comp
L Device:C C1
U 1 1 5EAE71D2
P 1150 3575
F 0 "C1" H 875 3650 50  0000 L CNN
F 1 "10 pF" H 850 3525 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1188 3425 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CGR82C500NT_C501852.html" H 1150 3575 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603JRNPO9BN100_C106245.html" H 1150 3575 50  0001 C CNN "lcsc"
	1    1150 3575
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 3425 1300 3425
$Comp
L Device:C C4
U 1 1 5EAE3306
P 1650 3575
F 0 "C4" H 1765 3621 50  0000 L CNN
F 1 "10 pF" H 1765 3530 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1688 3425 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CGR82C500NT_C501852.html" H 1650 3575 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603JRNPO9BN100_C106245.html" H 1650 3575 50  0001 C CNN "lcsc"
	1    1650 3575
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 3425 1650 3425
Text Label 1650 3425 2    50   ~ 0
XC2
Text Label 1150 3425 0    50   ~ 0
XC1
Wire Wire Line
	1400 3325 1400 3125
Wire Wire Line
	1400 3525 1400 3750
$Comp
L WatchBorad-rescue:Crystal_GND24_Small-Device-WatchBorad-rescue-WatchBorad-rescue-WatchBorad-rescue X1
U 1 1 5EAD6468
P 1400 3425
AR Path="/5EAD6468" Ref="X1"  Part="1" 
AR Path="/5E9B1DCE/5EAD6468" Ref="X1"  Part="1" 
F 0 "X1" H 1450 3575 50  0000 L CNN
F 1 "Crystal_GND24_Small" H 1544 3380 50  0001 L CNN
F 2 "Crystals:Crystal_SMD_2016-4pin_2.0x1.6mm" H 1400 3425 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1906211833_XTY-7216-3200A1010-00_C389798.pdf" H 1400 3425 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/New-Arrivals_XTY-7216-3200A1010-00_C389798.html" H 1400 3425 50  0001 C CNN "lcsc"
	1    1400 3425
	1    0    0    -1  
$EndComp
Wire Notes Line
	3600 700  3600 1525
Wire Notes Line
	3600 1525 700  1525
Wire Notes Line
	700  1525 700  700 
Wire Notes Line
	700  700  3600 700 
Text Notes 1450 800  0    50   ~ 0
Decoupling caps\n
Text Label 8350 1325 2    50   ~ 0
FLASH_CS
Wire Wire Line
	8550 1325 8450 1325
Text Label 8350 1425 2    50   ~ 0
FLASH_SCK
Wire Wire Line
	8550 1425 8350 1425
Wire Wire Line
	8550 1525 8350 1525
Text Label 8350 1525 2    50   ~ 0
FLASH_MOSI
Wire Wire Line
	8550 1625 8350 1625
Text Label 8350 1625 2    50   ~ 0
FLASH_MISO
Wire Wire Line
	9950 1425 10025 1425
$Comp
L power:GND #PWR?
U 1 1 5ECE6A9A
P 10050 1925
AR Path="/5ECE6A9A" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5ECE6A9A" Ref="#PWR020"  Part="1" 
F 0 "#PWR020" H 10050 1675 50  0001 C CNN
F 1 "GND" H 10055 1752 50  0000 C CNN
F 2 "" H 10050 1925 50  0001 C CNN
F 3 "" H 10050 1925 50  0001 C CNN
	1    10050 1925
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 1825 10050 1825
Wire Wire Line
	10050 1825 10050 1925
Wire Notes Line
	7650 575  7650 2325
Wire Notes Line
	7650 2325 11100 2325
Wire Notes Line
	11100 2325 11100 575 
Wire Notes Line
	11100 575  7650 575 
Text Notes 8925 725  0    50   ~ 0
SPI FLASH Memory\n
Text Label 6600 4750 0    50   ~ 0
FLASH_SCK
Text Label 6600 4650 0    50   ~ 0
FLASH_MOSI
Wire Wire Line
	6600 2150 6350 2150
Wire Wire Line
	6600 2350 6350 2350
Text HLabel 1150 2400 2    50   Input ~ 0
PB_1_MCU
Text HLabel 1150 2500 2    50   Input ~ 0
PB_2_MCU
Text HLabel 1150 2650 2    50   Input ~ 0
PB_3_MCU
Text HLabel 1150 2750 2    50   Input ~ 0
PB_4_MCU
Text HLabel 1150 2850 2    50   Input ~ 0
PB_5_MCU
Text Notes 1150 2350 0    50   ~ 0
PB\n
Wire Wire Line
	6600 3950 6350 3950
Text Label 8200 4400 0    50   ~ 0
HEART_SDA
Text Label 8150 4100 0    50   ~ 0
HEART_INT
Text Label 8200 4500 0    50   ~ 0
HEART_SCL
Text Label 1825 4950 0    50   ~ 0
SWD_SWDIO
Text Label 1825 5050 0    50   ~ 0
SWD_SWDCLK
Text Label 1825 5150 0    50   ~ 0
SWD_RESET
Text Label 1825 5250 0    50   ~ 0
SWD_SWO
Text Notes 1025 5375 0    50   ~ 0
SWD programming interface
Wire Notes Line
	700  4300 2300 4300
Wire Notes Line
	2300 4300 2300 5425
Wire Notes Line
	2300 5425 700  5425
Wire Notes Line
	700  4300 700  5425
Text HLabel 1075 1950 0    50   Input ~ 0
V3V3
Text Label 1375 1950 2    50   ~ 0
V3V3
Wire Notes Line
	700  1600 1600 1600
Wire Notes Line
	1600 1600 1600 2000
Wire Notes Line
	1600 2000 700  2000
Wire Notes Line
	700  2000 700  1600
Text Notes 950  1775 0    50   ~ 0
Power HL\n\n
Text Label 7000 3550 2    50   ~ 0
DISP_CS
Text Label 7000 3450 2    50   ~ 0
DISP_SCLK
Text Label 7000 3350 2    50   ~ 0
DISP_SDA
Text Label 7100 2450 2    50   ~ 0
Backlight_EN_DIM
Wire Wire Line
	6350 2050 7050 2050
Text Label 6600 2550 0    50   ~ 0
I2C_SCL
Text Label 6600 2650 0    50   ~ 0
I2C_SDA
Wire Wire Line
	6600 2550 6350 2550
Wire Wire Line
	6350 2650 6600 2650
$Comp
L Connector:TestPoint TP?
U 1 1 5F6067FE
P 8350 3550
AR Path="/5EA4867C/5F6067FE" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5F6067FE" Ref="TP6"  Part="1" 
F 0 "TP6" H 8408 3622 50  0000 L CNN
F 1 "TestPoint" H 8408 3577 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 8550 3550 50  0001 C CNN
F 3 "~" H 8550 3550 50  0001 C CNN
	1    8350 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5F619095
P 8100 3450
AR Path="/5EA4867C/5F619095" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5F619095" Ref="TP7"  Part="1" 
F 0 "TP7" H 8158 3522 50  0000 L CNN
F 1 "TestPoint" H 8158 3477 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 8300 3450 50  0001 C CNN
F 3 "~" H 8300 3450 50  0001 C CNN
	1    8100 3450
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5F62BA5E
P 7600 3250
AR Path="/5EA4867C/5F62BA5E" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5F62BA5E" Ref="TP8"  Part="1" 
F 0 "TP8" H 7658 3322 50  0000 L CNN
F 1 "TestPoint" H 7658 3277 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 7800 3250 50  0001 C CNN
F 3 "~" H 7800 3250 50  0001 C CNN
	1    7600 3250
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5F63E448
P 7900 3300
AR Path="/5EA4867C/5F63E448" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5F63E448" Ref="TP9"  Part="1" 
F 0 "TP9" H 7958 3372 50  0000 L CNN
F 1 "TestPoint" H 7958 3327 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 8100 3300 50  0001 C CNN
F 3 "~" H 8100 3300 50  0001 C CNN
	1    7900 3300
	1    0    0    -1  
$EndComp
Wire Notes Line
	8875 4900 11150 4900
Wire Notes Line
	11150 3150 11150 4900
Wire Notes Line
	8875 3150 8875 4900
Wire Notes Line
	8875 3150 11150 3150
Text Label 9600 3750 0    50   ~ 0
LEDA
Wire Wire Line
	10000 4550 9425 4550
Text Label 9425 4550 0    50   ~ 0
DISP_RESET
Text Label 9425 4250 0    50   ~ 0
DISP_CS
Wire Wire Line
	9425 4250 10000 4250
Wire Wire Line
	9425 4350 10000 4350
Text Label 9425 4350 0    50   ~ 0
DISP_SCLK
Text Label 9425 4150 0    50   ~ 0
DISP_DC
Wire Wire Line
	9425 4150 10000 4150
Text Label 9600 3650 0    50   ~ 0
LEDK
Text Notes 9600 3300 0    50   ~ 0
Display module without touch panel\n
$Comp
L power:GND #PWR?
U 1 1 5F8BBF9F
P 9875 4700
AR Path="/5F8BBF9F" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F8BBF9F" Ref="#PWR019"  Part="1" 
F 0 "#PWR019" H 9875 4450 50  0001 C CNN
F 1 "GND" H 9875 4550 50  0000 C CNN
F 2 "" H 9875 4700 50  0001 C CNN
F 3 "" H 9875 4700 50  0001 C CNN
	1    9875 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9875 4700 9875 4650
Wire Wire Line
	9875 3550 10000 3550
Wire Wire Line
	9600 3650 10000 3650
Wire Wire Line
	9600 3750 10000 3750
Wire Wire Line
	10000 3950 9875 3950
Connection ~ 9875 3950
Wire Wire Line
	9875 3950 9875 3550
Wire Wire Line
	10000 4050 9875 4050
Connection ~ 9875 4050
Wire Wire Line
	9875 4050 9875 3950
Connection ~ 9875 4650
Wire Wire Line
	9875 4650 9875 4050
Wire Wire Line
	9425 4450 10000 4450
Text Label 9425 4450 0    50   ~ 0
DISP_SDA
Wire Wire Line
	10000 4650 9875 4650
Wire Wire Line
	9875 4650 9225 4650
Wire Wire Line
	9225 4650 9225 4225
Wire Wire Line
	9225 3925 9225 3850
Wire Wire Line
	9225 3850 10000 3850
Wire Wire Line
	1800 1350 2075 1350
$Comp
L power:GND #PWR?
U 1 1 5FB7DED5
P 2075 1350
AR Path="/5FB7DED5" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FB7DED5" Ref="#PWR05"  Part="1" 
F 0 "#PWR05" H 2075 1100 50  0001 C CNN
F 1 "GND" H 2075 1200 50  0000 C CNN
F 2 "" H 2075 1350 50  0001 C CNN
F 3 "" H 2075 1350 50  0001 C CNN
	1    2075 1350
	1    0    0    -1  
$EndComp
Connection ~ 2075 1350
Wire Wire Line
	2075 1350 2150 1350
$Comp
L power:GND #PWR?
U 1 1 5FB7E7A0
P 3700 3125
AR Path="/5FB7E7A0" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FB7E7A0" Ref="#PWR010"  Part="1" 
F 0 "#PWR010" H 3700 2875 50  0001 C CNN
F 1 "GND" H 3700 2975 50  0000 C CNN
F 2 "" H 3700 3125 50  0001 C CNN
F 3 "" H 3700 3125 50  0001 C CNN
	1    3700 3125
	1    0    0    -1  
$EndComp
Connection ~ 3700 3125
Wire Wire Line
	3700 3125 4125 3125
Wire Notes Line
	3325 2300 3325 3350
Wire Notes Line
	4275 2300 4275 3350
Connection ~ 1150 3750
$Comp
L power:GND #PWR?
U 1 1 5FBEC583
P 825 3775
AR Path="/5FBEC583" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FBEC583" Ref="#PWR01"  Part="1" 
F 0 "#PWR01" H 825 3525 50  0001 C CNN
F 1 "GND" H 825 3625 50  0000 C CNN
F 2 "" H 825 3775 50  0001 C CNN
F 3 "" H 825 3775 50  0001 C CNN
	1    825  3775
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F9CCFB6
P 6275 5875
AR Path="/5E9C1C3A/5F9CCFB6" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9CCFB6" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9CCFB6" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F9CCFB6" Ref="#PWR015"  Part="1" 
F 0 "#PWR015" H 6275 5725 50  0001 C CNN
F 1 "+3.3V" H 6290 6048 50  0000 C CNN
F 2 "" H 6275 5875 50  0001 C CNN
F 3 "" H 6275 5875 50  0001 C CNN
	1    6275 5875
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F9E01B3
P 1475 1950
AR Path="/5E9C1C3A/5F9E01B3" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9E01B3" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9E01B3" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F9E01B3" Ref="#PWR03"  Part="1" 
F 0 "#PWR03" H 1475 1800 50  0001 C CNN
F 1 "+3.3V" H 1490 2123 50  0000 C CNN
F 2 "" H 1475 1950 50  0001 C CNN
F 3 "" H 1475 1950 50  0001 C CNN
	1    1475 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1075 1950 1475 1950
Wire Wire Line
	825  3775 825  3750
Wire Wire Line
	825  3750 1150 3750
Wire Wire Line
	1400 3125 825  3125
Wire Wire Line
	825  3125 825  3750
Connection ~ 825  3750
$Comp
L power:+3.3V #PWR?
U 1 1 5FA2F8BF
P 10500 1125
AR Path="/5E9C1C3A/5FA2F8BF" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5FA2F8BF" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5FA2F8BF" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FA2F8BF" Ref="#PWR022"  Part="1" 
F 0 "#PWR022" H 10500 975 50  0001 C CNN
F 1 "+3.3V" H 10515 1298 50  0000 C CNN
F 2 "" H 10500 1125 50  0001 C CNN
F 3 "" H 10500 1125 50  0001 C CNN
	1    10500 1125
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5FA31BF0
P 9225 3850
AR Path="/5E9C1C3A/5FA31BF0" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5FA31BF0" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5FA31BF0" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FA31BF0" Ref="#PWR018"  Part="1" 
F 0 "#PWR018" H 9225 3700 50  0001 C CNN
F 1 "+3.3V" H 9240 4023 50  0000 C CNN
F 2 "" H 9225 3850 50  0001 C CNN
F 3 "" H 9225 3850 50  0001 C CNN
	1    9225 3850
	1    0    0    -1  
$EndComp
Connection ~ 9225 3850
$Comp
L power:+3.3V #PWR?
U 1 1 5FAACA94
P 5750 1275
AR Path="/5E9C1C3A/5FAACA94" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5FAACA94" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5FAACA94" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FAACA94" Ref="#PWR014"  Part="1" 
F 0 "#PWR014" H 5750 1125 50  0001 C CNN
F 1 "+3.3V" H 5765 1448 50  0000 C CNN
F 2 "" H 5750 1275 50  0001 C CNN
F 3 "" H 5750 1275 50  0001 C CNN
	1    5750 1275
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FADF2C6
P 5450 5175
AR Path="/5FADF2C6" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FADF2C6" Ref="#PWR013"  Part="1" 
F 0 "#PWR013" H 5450 4925 50  0001 C CNN
F 1 "GND" H 5450 5025 50  0000 C CNN
F 2 "" H 5450 5175 50  0001 C CNN
F 3 "" H 5450 5175 50  0001 C CNN
	1    5450 5175
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FAF3706
P 8750 6800
AR Path="/5FAF3706" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FAF3706" Ref="#PWR021"  Part="1" 
F 0 "#PWR021" H 8750 6550 50  0001 C CNN
F 1 "GND" H 8750 6650 50  0000 C CNN
F 2 "" H 8750 6800 50  0001 C CNN
F 3 "" H 8750 6800 50  0001 C CNN
	1    8750 6800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FB07C4A
P 8750 3250
AR Path="/5FB07C4A" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FB07C4A" Ref="#PWR016"  Part="1" 
F 0 "#PWR016" H 8750 3000 50  0001 C CNN
F 1 "GND" H 8750 3100 50  0000 C CNN
F 2 "" H 8750 3250 50  0001 C CNN
F 3 "" H 8750 3250 50  0001 C CNN
	1    8750 3250
	1    0    0    -1  
$EndComp
Text HLabel 7100 4050 2    50   BiDi ~ 0
SDA_FG
Text HLabel 7100 4150 2    50   Input ~ 0
SCL_FG
Wire Wire Line
	6350 4050 7100 4050
Wire Wire Line
	6350 4150 7100 4150
NoConn ~ 5650 1650
$Comp
L power:+3.3V #PWR?
U 1 1 5FC4734F
P 2325 975
AR Path="/5E9C1C3A/5FC4734F" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5FC4734F" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5FC4734F" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FC4734F" Ref="#PWR08"  Part="1" 
F 0 "#PWR08" H 2325 825 50  0001 C CNN
F 1 "+3.3V" H 2340 1148 50  0000 C CNN
F 2 "" H 2325 975 50  0001 C CNN
F 3 "" H 2325 975 50  0001 C CNN
	1    2325 975 
	1    0    0    -1  
$EndComp
Text Label 8200 4300 0    50   ~ 0
HEART_IRD
Text Label 8150 4200 0    50   ~ 0
HEART_RD
Text HLabel 6800 4850 2    50   Output ~ 0
Enable_motor
$Comp
L Connector:TestPoint TP?
U 1 1 5FD9ED2F
P 825 4825
AR Path="/5EA4867C/5FD9ED2F" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5FD9ED2F" Ref="TP1"  Part="1" 
F 0 "TP1" H 850 4900 50  0000 L CNN
F 1 "TestPoint" H 883 4852 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 1025 4825 50  0001 C CNN
F 3 "~" H 1025 4825 50  0001 C CNN
	1    825  4825
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5FD9FCBC
P 1050 4825
AR Path="/5EA4867C/5FD9FCBC" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5FD9FCBC" Ref="TP2"  Part="1" 
F 0 "TP2" H 1075 4900 50  0000 L CNN
F 1 "TestPoint" H 1108 4852 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 1250 4825 50  0001 C CNN
F 3 "~" H 1250 4825 50  0001 C CNN
	1    1050 4825
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5FDA011E
P 1275 4825
AR Path="/5EA4867C/5FDA011E" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5FDA011E" Ref="TP3"  Part="1" 
F 0 "TP3" H 1300 4900 50  0000 L CNN
F 1 "TestPoint" H 1333 4852 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 1475 4825 50  0001 C CNN
F 3 "~" H 1475 4825 50  0001 C CNN
	1    1275 4825
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5FDA04CF
P 1500 4825
AR Path="/5EA4867C/5FDA04CF" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5FDA04CF" Ref="TP4"  Part="1" 
F 0 "TP4" H 1525 4900 50  0000 L CNN
F 1 "TestPoint" H 1558 4852 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 1700 4825 50  0001 C CNN
F 3 "~" H 1700 4825 50  0001 C CNN
	1    1500 4825
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 4825 1500 4950
Wire Wire Line
	1500 4950 1825 4950
Wire Wire Line
	1275 4825 1275 5050
Wire Wire Line
	1275 5050 1825 5050
Wire Wire Line
	1050 4825 1050 5150
Wire Wire Line
	1050 5150 1825 5150
Wire Wire Line
	825  4825 825  5250
Wire Wire Line
	825  5250 1825 5250
Wire Wire Line
	9950 1125 10025 1125
$Comp
L Device:R R?
U 1 1 5FBE7778
P 10025 1275
AR Path="/5EA4867C/5FBE7778" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5FBE7778" Ref="R?"  Part="1" 
AR Path="/5FBE7778" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5FBE7778" Ref="R12"  Part="1" 
F 0 "R12" H 10095 1321 50  0000 L CNN
F 1 "10k" H 10095 1230 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9955 1275 50  0001 C CNN
F 3 "~" H 10025 1275 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 10025 1275 50  0001 C CNN "lcsc"
	1    10025 1275
	1    0    0    -1  
$EndComp
Connection ~ 10025 1125
Wire Wire Line
	10025 1125 10300 1125
$Comp
L Device:R R?
U 1 1 5FBFA77B
P 10300 1275
AR Path="/5EA4867C/5FBFA77B" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5FBFA77B" Ref="R?"  Part="1" 
AR Path="/5FBFA77B" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5FBFA77B" Ref="R13"  Part="1" 
F 0 "R13" H 10370 1321 50  0000 L CNN
F 1 "10k" H 10370 1230 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10230 1275 50  0001 C CNN
F 3 "~" H 10300 1275 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 10300 1275 50  0001 C CNN "lcsc"
	1    10300 1275
	1    0    0    -1  
$EndComp
Connection ~ 10300 1125
Wire Wire Line
	10300 1125 10500 1125
Wire Wire Line
	10300 1425 10300 1525
Wire Wire Line
	9950 1525 10300 1525
Wire Wire Line
	10625 1525 10625 1725
Wire Wire Line
	10625 1225 10625 1125
$Comp
L power:GND #PWR?
U 1 1 5ECE6AA2
P 10625 1725
AR Path="/5ECE6AA2" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5ECE6AA2" Ref="#PWR023"  Part="1" 
F 0 "#PWR023" H 10625 1475 50  0001 C CNN
F 1 "GND" H 10630 1552 50  0000 C CNN
F 2 "" H 10625 1725 50  0001 C CNN
F 3 "" H 10625 1725 50  0001 C CNN
	1    10625 1725
	1    0    0    -1  
$EndComp
Wire Wire Line
	10500 1125 10625 1125
Connection ~ 10500 1125
Wire Wire Line
	6875 3150 6350 3150
Wire Wire Line
	8875 3175 8875 3200
Wire Wire Line
	8400 3175 8400 3200
Text Label 6775 3050 2    50   ~ 0
MPU_INT_2
$Comp
L Device:R R?
U 1 1 5FFF65BE
P 8750 6600
AR Path="/5EA4867C/5FFF65BE" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5FFF65BE" Ref="R?"  Part="1" 
AR Path="/5FFF65BE" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5FFF65BE" Ref="R14"  Part="1" 
F 0 "R14" H 8820 6646 50  0000 L CNN
F 1 "10k" H 8820 6555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8680 6600 50  0001 C CNN
F 3 "~" H 8750 6600 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 8750 6600 50  0001 C CNN "lcsc"
	1    8750 6600
	1    0    0    -1  
$EndComp
Text Notes 8600 6375 0    50   ~ 0
I_led is set 7.5 mA 
$Comp
L Device:C C?
U 1 1 5FFF84B6
P 1175 1150
AR Path="/5EA4867C/5FFF84B6" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5FFF84B6" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/5FFF84B6" Ref="C?"  Part="1" 
AR Path="/5F988DA5/5FFF84B6" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5FFF84B6" Ref="C2"  Part="1" 
F 0 "C2" H 1200 1225 50  0000 L CNN
F 1 "10 uF" V 1025 1025 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1213 1000 50  0001 C CNN
F 3 "~" H 1175 1150 50  0001 C CNN
F 4 "" H 1175 1150 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 1175 1150 50  0001 C CNN "lcsc"
	1    1175 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6000A4F0
P 9225 4075
AR Path="/5EA4867C/6000A4F0" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/6000A4F0" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/6000A4F0" Ref="C?"  Part="1" 
AR Path="/5F988DA5/6000A4F0" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/6000A4F0" Ref="C21"  Part="1" 
F 0 "C21" H 9250 4150 50  0000 L CNN
F 1 "10 uF" V 9075 3950 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9263 3925 50  0001 C CNN
F 3 "~" H 9225 4075 50  0001 C CNN
F 4 "" H 9225 4075 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 9225 4075 50  0001 C CNN "lcsc"
	1    9225 4075
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6001C706
P 6400 6100
AR Path="/5EA4867C/6001C706" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/6001C706" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/6001C706" Ref="C?"  Part="1" 
AR Path="/5F988DA5/6001C706" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/6001C706" Ref="C20"  Part="1" 
F 0 "C20" H 6425 6175 50  0000 L CNN
F 1 "10 uF" V 6250 5975 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6438 5950 50  0001 C CNN
F 3 "~" H 6400 6100 50  0001 C CNN
F 4 "" H 6400 6100 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 6400 6100 50  0001 C CNN "lcsc"
	1    6400 6100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60116727
P 10625 1375
AR Path="/5EA4867C/60116727" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/60116727" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/60116727" Ref="C22"  Part="1" 
AR Path="/60116727" Ref="C?"  Part="1" 
F 0 "C22" H 10800 1400 50  0000 L CNN
F 1 "100 nF" H 10750 1300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10663 1225 50  0001 C CNN
F 3 "~" H 10625 1375 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 10625 1375 50  0001 C CNN "lcsc"
	1    10625 1375
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6013CFEB
P 8450 1050
AR Path="/5EA4867C/6013CFEB" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/6013CFEB" Ref="R?"  Part="1" 
AR Path="/6013CFEB" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/6013CFEB" Ref="R11"  Part="1" 
F 0 "R11" H 8520 1096 50  0000 L CNN
F 1 "10k" H 8520 1005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8380 1050 50  0001 C CNN
F 3 "~" H 8450 1050 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 8450 1050 50  0001 C CNN "lcsc"
	1    8450 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 1200 8450 1325
Connection ~ 8450 1325
Wire Wire Line
	8450 1325 8350 1325
Wire Wire Line
	8450 900  8450 825 
$Comp
L power:+3.3V #PWR?
U 1 1 60175997
P 8450 825
AR Path="/5E9C1C3A/60175997" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/60175997" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/60175997" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/60175997" Ref="#PWR017"  Part="1" 
F 0 "#PWR017" H 8450 675 50  0001 C CNN
F 1 "+3.3V" H 8465 998 50  0000 C CNN
F 2 "" H 8450 825 50  0001 C CNN
F 3 "" H 8450 825 50  0001 C CNN
	1    8450 825 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 1275 5750 1275
Wire Wire Line
	6275 5875 6275 5925
Wire Wire Line
	6275 5925 6400 5925
Wire Wire Line
	6675 5925 6675 5950
Wire Wire Line
	6400 5950 6400 5925
Connection ~ 6400 5925
Wire Wire Line
	6400 5925 6675 5925
Text Label 6475 5925 0    50   ~ 0
LEDA
$Comp
L GC9A01:GC9A01 U11
U 1 1 60CF55BA
P 10250 4050
AR Path="/60CF55BA" Ref="U11"  Part="1" 
AR Path="/5E9B1DCE/60CF55BA" Ref="U11"  Part="1" 
F 0 "U11" H 10428 4046 50  0000 L CNN
F 1 "GC9A01" H 10428 3955 50  0000 L CNN
F 2 "LocalFootprints:GC9A01_Extended_FPC" H 10000 4400 50  0001 C CNN
F 3 "https://www.buydisplay.com/download/ic/GC9A01A.pdf" H 10000 4400 50  0001 C CNN
F 4 "https://www.aliexpress.com/item/1005002297668304.html?spm=a2g0o.productlist.0.0.2d323cfbmTWYJD&algo_pvid=a7cd72c7-e7b7-4a28-818d-25cad6b70960&algo_exp_id=a7cd72c7-e7b7-4a28-818d-25cad6b70960-0&pdp_ext_f=%7B%22sku_id%22%3A%2212000021496494507%22%7D" H 10250 4050 50  0001 C CNN "lcsc"
	1    10250 4050
	1    0    0    -1  
$EndComp
Text Label 7000 3750 2    50   ~ 0
DISP_DC
$Comp
L W25Q16BVSSIG:MX25R1635F U?
U 1 1 5ECE6AE0
P 9250 1525
AR Path="/5ECE6AE0" Ref="U?"  Part="1" 
AR Path="/5E9B1DCE/5ECE6AE0" Ref="U4"  Part="1" 
F 0 "U4" H 9250 2195 50  0000 C CNN
F 1 "MX25R1635F" H 9250 2104 50  0000 C CNN
F 2 "LocalFootprints:W25Q128JVPIQ" H 9250 1525 50  0001 L BNN
F 3 "https://datasheet.lcsc.com/lcsc/1809140423_Winbond-Elec-W25Q128JVPIQ_C190862.pdf" H 9250 1525 50  0001 L BNN
F 4 "https://lcsc.com/product-detail/FLASH_Winbond-Elec-W25Q128JVPIQTR_C190862.html" H 9250 1525 50  0001 C CNN "lcsc"
	1    9250 1525
	1    0    0    -1  
$EndComp
Text Label 6600 4550 0    50   ~ 0
FLASH_CS
Text Label 6600 4450 0    50   ~ 0
FLASH_MISO
Text Label 6750 2950 2    50   ~ 0
P5
Text Label 7050 2050 2    50   ~ 0
P6
Text Label 8350 3850 0    50   ~ 0
P23
Wire Wire Line
	6350 3050 6775 3050
Text HLabel 2925 4775 0    50   Input ~ 0
FG_OD_ALRT_N
$Comp
L Device:R R?
U 1 1 60E1353E
P 3550 4625
AR Path="/5EA4867C/60E1353E" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/60E1353E" Ref="R?"  Part="1" 
AR Path="/60E1353E" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/60E1353E" Ref="R10"  Part="1" 
F 0 "R10" H 3620 4671 50  0000 L CNN
F 1 "10k" H 3620 4580 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3480 4625 50  0001 C CNN
F 3 "~" H 3550 4625 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 3550 4625 50  0001 C CNN "lcsc"
	1    3550 4625
	1    0    0    -1  
$EndComp
Wire Wire Line
	2925 4775 3550 4775
$Comp
L power:+3.3V #PWR?
U 1 1 60E38347
P 3550 4475
AR Path="/5E9C1C3A/60E38347" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/60E38347" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/60E38347" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/60E38347" Ref="#PWR0104"  Part="1" 
F 0 "#PWR0104" H 3550 4325 50  0001 C CNN
F 1 "+3.3V" H 3565 4648 50  0000 C CNN
F 2 "" H 3550 4475 50  0001 C CNN
F 3 "" H 3550 4475 50  0001 C CNN
	1    3550 4475
	1    0    0    -1  
$EndComp
Text Label 2975 4775 0    50   ~ 0
FG_OD_ALRT_N
Text Label 6875 3150 2    50   ~ 0
FG_OD_ALRT_N
Wire Wire Line
	6350 4850 6800 4850
Wire Wire Line
	8400 2875 8400 2850
$Comp
L Device:C C18
U 1 1 5EACAA30
P 8400 3025
F 0 "C18" H 8515 3071 50  0000 L CNN
F 1 "130 pF" H 8515 2980 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8438 2875 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CGR82C500NT_C501852.html" H 8400 3025 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CG131J500NT_C327424.html" H 8400 3025 50  0001 C CNN "lcsc"
	1    8400 3025
	1    0    0    -1  
$EndComp
$Comp
L Device:C C19
U 1 1 5EACB58A
P 8875 3025
F 0 "C19" H 8990 3071 50  0000 L CNN
F 1 "130 pF" H 8990 2980 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8913 2875 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CGR82C500NT_C501852.html" H 8875 3025 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CG131J500NT_C327424.html" H 8875 3025 50  0001 C CNN "lcsc"
	1    8875 3025
	1    0    0    -1  
$EndComp
Text Label 8200 2850 0    50   ~ 0
NFC2
Text Label 8200 2750 0    50   ~ 0
NFC1
Wire Wire Line
	8875 2875 8875 2750
Wire Wire Line
	8400 3200 8750 3200
Wire Wire Line
	9275 2850 9275 2750
Connection ~ 8875 2750
Wire Wire Line
	8875 2750 9175 2750
Connection ~ 8400 2850
Wire Wire Line
	8400 2850 9275 2850
$Comp
L Device:Antenna_Loop AE2
U 1 1 5EB3E2CF
P 9175 2550
F 0 "AE2" H 9405 2518 50  0000 L CNN
F 1 "Antenna_Loop" H 9405 2473 50  0001 L CNN
F 2 "LocalFootprints:BatteryPads" H 9175 2550 50  0001 C CNN
F 3 "~" H 9175 2550 50  0001 C CNN
	1    9175 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 3250 8750 3200
Connection ~ 8750 3200
Wire Wire Line
	8750 3200 8875 3200
Wire Wire Line
	6350 2750 8875 2750
Wire Wire Line
	6350 2850 8400 2850
$Comp
L Connector:TestPoint TP?
U 1 1 5F650E32
P 8600 3700
AR Path="/5EA4867C/5F650E32" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5F650E32" Ref="TP10"  Part="1" 
F 0 "TP10" H 8658 3772 50  0000 L CNN
F 1 "TestPoint" H 8658 3727 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 8800 3700 50  0001 C CNN
F 3 "~" H 8800 3700 50  0001 C CNN
	1    8600 3700
	1    0    0    -1  
$EndComp
Text Label 7000 3250 2    50   ~ 0
DISP_RESET
Wire Wire Line
	6350 3850 8350 3850
Wire Wire Line
	7900 3350 7900 3300
Wire Wire Line
	6350 3350 7900 3350
Wire Wire Line
	6350 4350 6700 4350
Text Label 900  2750 2    50   ~ 0
U_PUSH2
Text Label 900  2650 2    50   ~ 0
U_PUSH1
Wire Wire Line
	1150 2650 900  2650
Wire Wire Line
	900  2750 1150 2750
Text Label 900  2850 2    50   ~ 0
U_PUSH3
Wire Wire Line
	900  2850 1150 2850
Text Label 900  2400 2    50   ~ 0
P_PUSH1
Text Label 900  2500 2    50   ~ 0
P_PUSH2
Wire Wire Line
	900  2500 1150 2500
Wire Wire Line
	1150 2400 900  2400
Text Label 6600 3950 0    50   ~ 0
U_PUSH1
Text Label 6700 4250 0    50   ~ 0
U_PUSH2
Wire Wire Line
	6350 4250 6700 4250
Text Label 6700 4350 0    50   ~ 0
U_PUSH3
Wire Notes Line
	500  2950 1700 2950
Wire Notes Line
	1700 2950 1700 2250
Wire Notes Line
	1700 2250 500  2250
Wire Notes Line
	500  2250 500  2950
Text Label 6600 2150 0    50   ~ 0
P_PUSH1
Text Label 6600 2350 0    50   ~ 0
P_PUSH2
Wire Wire Line
	6350 2450 7100 2450
Wire Wire Line
	6750 2950 6350 2950
Text Label 6950 2250 2    50   ~ 0
MPU_INT_1
Wire Wire Line
	6350 2250 6950 2250
$Comp
L Connector:TestPoint TP?
U 1 1 60F01B53
P 7200 4450
AR Path="/5EA4867C/60F01B53" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/60F01B53" Ref="TP16"  Part="1" 
F 0 "TP16" H 7258 4522 50  0000 L CNN
F 1 "TestPoint" H 7258 4477 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 7400 4450 50  0001 C CNN
F 3 "~" H 7400 4450 50  0001 C CNN
	1    7200 4450
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 60F12FC7
P 7450 4550
AR Path="/5EA4867C/60F12FC7" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/60F12FC7" Ref="TP17"  Part="1" 
F 0 "TP17" H 7508 4622 50  0000 L CNN
F 1 "TestPoint" H 7508 4577 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 7650 4550 50  0001 C CNN
F 3 "~" H 7650 4550 50  0001 C CNN
	1    7450 4550
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 60F24537
P 7700 4650
AR Path="/5EA4867C/60F24537" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/60F24537" Ref="TP18"  Part="1" 
F 0 "TP18" H 7758 4722 50  0000 L CNN
F 1 "TestPoint" H 7758 4677 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 7900 4650 50  0001 C CNN
F 3 "~" H 7900 4650 50  0001 C CNN
	1    7700 4650
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 60F35800
P 7950 4750
AR Path="/5EA4867C/60F35800" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/60F35800" Ref="TP19"  Part="1" 
F 0 "TP19" H 8008 4822 50  0000 L CNN
F 1 "TestPoint" H 8008 4777 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 8150 4750 50  0001 C CNN
F 3 "~" H 8150 4750 50  0001 C CNN
	1    7950 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 4750 7950 4750
Wire Wire Line
	6350 4650 7700 4650
Wire Wire Line
	6350 4550 7450 4550
Wire Wire Line
	6350 4450 7200 4450
$Comp
L power:GND #PWR?
U 1 1 61835D4B
P 2800 2725
AR Path="/61835D4B" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/61835D4B" Ref="#PWR04"  Part="1" 
F 0 "#PWR04" H 2800 2475 50  0001 C CNN
F 1 "GND" H 2800 2575 50  0000 C CNN
F 2 "" H 2800 2725 50  0001 C CNN
F 3 "" H 2800 2725 50  0001 C CNN
	1    2800 2725
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 2725 2800 2650
Wire Wire Line
	2800 2650 3050 2650
Text Label 6475 4050 0    50   ~ 0
I2C_SDA_STBY
Text Label 6475 4150 0    50   ~ 0
I2C_SCL_STBY
$Comp
L Device:Antenna_Chip AE1
U 1 1 5EAD751A
P 3150 2550
F 0 "AE1" H 3625 2700 50  0000 R CNN
F 1 "Antenna_Chip" H 3800 2575 50  0000 R CNN
F 2 "ANT2012LL13R2400A:ANT2012LL13R2400A" H 3050 2725 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1809191926_YAGEO-ANT2012LL13R2400A_C141581.pdf" H 3050 2725 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Antennas_YAGEO-ANT2012LL13R2400A_C141581.html" H 3150 2550 50  0001 C CNN "lcsc"
	1    3150 2550
	-1   0    0    -1  
$EndComp
Wire Notes Line
	5175 8400 700  8400
Wire Wire Line
	4350 6030 4640 6030
Connection ~ 4350 6030
Wire Wire Line
	4350 6090 4350 6030
Wire Wire Line
	4160 6030 4350 6030
Wire Wire Line
	4640 6030 4640 6090
Wire Wire Line
	3810 7000 4640 7000
Wire Wire Line
	4640 7000 4640 6390
Wire Wire Line
	3810 6900 4350 6900
Wire Wire Line
	4350 6900 4350 6390
Wire Notes Line
	2810 5810 2810 6000
Wire Notes Line
	4040 5810 2810 5810
Wire Notes Line
	4040 6480 4040 5810
Wire Notes Line
	3880 6480 4040 6480
Wire Notes Line
	3880 6000 3880 6480
Wire Notes Line
	2810 6000 3880 6000
Connection ~ 4160 6030
Wire Wire Line
	4160 6030 3960 6030
Wire Wire Line
	4160 6030 4160 5900
$Comp
L power:+3.3V #PWR09
U 1 1 61C0E946
P 4160 5900
F 0 "#PWR09" H 4160 5750 50  0001 C CNN
F 1 "+3.3V" H 4175 6073 50  0000 C CNN
F 2 "" H 4160 5900 50  0001 C CNN
F 3 "" H 4160 5900 50  0001 C CNN
	1    4160 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3960 6400 3960 6390
Wire Wire Line
	3810 6400 3960 6400
Wire Wire Line
	3960 6090 3960 6030
Text Notes 2820 5960 0    50   ~ 0
LSM6DSL addr is 1101011b
Connection ~ 970  5920
Wire Wire Line
	850  5920 970  5920
Wire Wire Line
	850  7200 850  5920
Wire Wire Line
	2410 7200 850  7200
$Comp
L LSM6DSRTR:LSM6DSRTR U1
U 1 1 617DAA03
P 2310 6400
F 0 "U1" H 3110 6665 50  0000 C CNN
F 1 "LSM6DSRTR" H 3110 6574 50  0000 C CNN
F 2 "LSM6DSRTR:LSM6DSRTR_LGA-14L" H 2310 6800 50  0001 L CNN
F 3 "https://www.st.com/resource/en/datasheet/lsm6dsr.pdf" H 2310 6900 50  0001 L CNN
F 4 "https://www.lcsc.com/product-detail/Motion-Sensors-Accelerometers_STMicroelectronics-LSM6DSRTR_C784817.html" H 2310 6400 50  0001 C CNN "lcsc"
	1    2310 6400
	1    0    0    -1  
$EndComp
Connection ~ 1110 5920
Wire Wire Line
	1110 5920 970  5920
Wire Wire Line
	970  7100 970  5920
Wire Wire Line
	2410 7100 970  7100
Wire Wire Line
	1110 7000 2410 7000
Wire Wire Line
	1110 7000 1110 6400
Wire Wire Line
	1380 6900 2410 6900
Wire Wire Line
	1380 6400 1380 6900
Wire Wire Line
	1710 6800 2410 6800
Wire Wire Line
	1710 6800 1710 6400
Wire Wire Line
	1380 5920 1380 6100
Connection ~ 1380 5920
Wire Wire Line
	1710 5920 1710 6100
Wire Wire Line
	1380 5920 1710 5920
Wire Wire Line
	1110 5920 1380 5920
Wire Wire Line
	1380 5920 1380 5890
Wire Wire Line
	1110 6100 1110 5920
Wire Wire Line
	2090 6400 2090 6500
Connection ~ 2090 6400
Wire Wire Line
	2090 6350 2090 6400
$Comp
L power:+3.3V #PWR?
U 1 1 6123BFAB
P 1380 5890
AR Path="/5E9C1C3A/6123BFAB" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/6123BFAB" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/6123BFAB" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/6123BFAB" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 1380 5740 50  0001 C CNN
F 1 "+3.3V" H 1395 6063 50  0000 C CNN
F 2 "" H 1380 5890 50  0001 C CNN
F 3 "" H 1380 5890 50  0001 C CNN
	1    1380 5890
	1    0    0    -1  
$EndComp
Wire Wire Line
	2410 6500 2090 6500
Wire Wire Line
	2090 6400 2410 6400
$Comp
L power:+3.3V #PWR06
U 1 1 61ABDECF
P 2090 6350
F 0 "#PWR06" H 2090 6200 50  0001 C CNN
F 1 "+3.3V" H 2105 6523 50  0000 C CNN
F 2 "" H 2090 6350 50  0001 C CNN
F 3 "" H 2090 6350 50  0001 C CNN
	1    2090 6350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F46C82F
P 950 7850
AR Path="/5EA4867C/5F46C82F" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F46C82F" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5F46C82F" Ref="C16"  Part="1" 
AR Path="/5F46C82F" Ref="C?"  Part="1" 
F 0 "C16" H 975 7925 50  0000 L CNN
F 1 "100 nF" V 800 7725 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 988 7700 50  0001 C CNN
F 3 "~" H 950 7850 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 950 7850 50  0001 C CNN "lcsc"
	1    950  7850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FA84810
P 1130 8150
AR Path="/5FA84810" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FA84810" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 1130 7900 50  0001 C CNN
F 1 "GND" H 1135 7977 50  0000 C CNN
F 2 "" H 1130 8150 50  0001 C CNN
F 3 "" H 1130 8150 50  0001 C CNN
	1    1130 8150
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 617ECB05
P 1130 7460
AR Path="/5E9C1C3A/617ECB05" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/617ECB05" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/617ECB05" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/617ECB05" Ref="#PWR02"  Part="1" 
F 0 "#PWR02" H 1130 7310 50  0001 C CNN
F 1 "+3.3V" H 1145 7633 50  0000 C CNN
F 2 "" H 1130 7460 50  0001 C CNN
F 3 "" H 1130 7460 50  0001 C CNN
	1    1130 7460
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F46C829
P 1320 7850
AR Path="/5EA4867C/5F46C829" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F46C829" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5F46C829" Ref="C14"  Part="1" 
AR Path="/5F46C829" Ref="C?"  Part="1" 
F 0 "C14" H 1345 7925 50  0000 L CNN
F 1 "100 nF" V 1170 7725 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1358 7700 50  0001 C CNN
F 3 "~" H 1320 7850 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 1320 7850 50  0001 C CNN "lcsc"
	1    1320 7850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1320 8100 1130 8100
Wire Wire Line
	1130 8100 1130 8150
Wire Wire Line
	950  8100 1130 8100
Connection ~ 1130 8100
Wire Wire Line
	1130 7530 1130 7460
Wire Wire Line
	950  7530 1130 7530
Connection ~ 1130 7530
Wire Wire Line
	1130 7530 1320 7530
Wire Wire Line
	950  8000 950  8100
Wire Wire Line
	950  7530 950  7700
Wire Wire Line
	1320 7530 1320 7700
Wire Wire Line
	1320 8000 1320 8100
Connection ~ 3930 7300
Wire Wire Line
	3930 7200 3930 7300
Wire Wire Line
	3810 7200 3930 7200
Wire Wire Line
	3930 7300 3930 7390
Wire Wire Line
	3810 7300 3930 7300
Text Label 3910 7000 0    50   ~ 0
MPU_INT_2
Text Label 2220 6800 2    50   ~ 0
NC_PU
$Comp
L power:GND #PWR?
U 1 1 60D9BCF3
P 3930 7390
AR Path="/60D9BCF3" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/60D9BCF3" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 3930 7140 50  0001 C CNN
F 1 "GND" H 3935 7217 50  0000 C CNN
F 2 "" H 3930 7390 50  0001 C CNN
F 3 "" H 3930 7390 50  0001 C CNN
	1    3930 7390
	1    0    0    -1  
$EndComp
Text Label 2220 6900 2    50   ~ 0
I2C_SCL
Text Label 2220 7000 2    50   ~ 0
I2C_SDA
Text Label 3910 6900 0    50   ~ 0
MPU_INT_1
Wire Notes Line
	700  5650 5180 5650
Wire Notes Line
	5180 5650 5180 8400
Wire Notes Line
	700  5650 700  8400
$Comp
L Device:R R?
U 1 1 5F46C868
P 1110 6250
AR Path="/5EA4867C/5F46C868" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F46C868" Ref="R?"  Part="1" 
AR Path="/5F46C868" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5F46C868" Ref="R4"  Part="1" 
F 0 "R4" H 1180 6296 50  0000 L CNN
F 1 "10k" H 1180 6205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1040 6250 50  0001 C CNN
F 3 "~" H 1110 6250 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 1110 6250 50  0001 C CNN "lcsc"
	1    1110 6250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F46C86E
P 1380 6250
AR Path="/5EA4867C/5F46C86E" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F46C86E" Ref="R?"  Part="1" 
AR Path="/5F46C86E" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5F46C86E" Ref="R5"  Part="1" 
F 0 "R5" H 1450 6296 50  0000 L CNN
F 1 "10k" H 1450 6205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1310 6250 50  0001 C CNN
F 3 "~" H 1380 6250 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 1380 6250 50  0001 C CNN "lcsc"
	1    1380 6250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F46C84B
P 1710 6250
AR Path="/5EA4867C/5F46C84B" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F46C84B" Ref="R?"  Part="1" 
AR Path="/5F46C84B" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5F46C84B" Ref="R6"  Part="1" 
F 0 "R6" H 1780 6296 50  0000 L CNN
F 1 "10k" H 1780 6205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1640 6250 50  0001 C CNN
F 3 "~" H 1710 6250 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 1710 6250 50  0001 C CNN "lcsc"
	1    1710 6250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5FD423EF
P 3960 6240
AR Path="/5EA4867C/5FD423EF" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5FD423EF" Ref="R?"  Part="1" 
AR Path="/5FD423EF" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5FD423EF" Ref="R7"  Part="1" 
F 0 "R7" H 4030 6286 50  0000 L CNN
F 1 "10k" H 4030 6195 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3890 6240 50  0001 C CNN
F 3 "~" H 3960 6240 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 3960 6240 50  0001 C CNN "lcsc"
	1    3960 6240
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6147056A
P 4640 6240
AR Path="/5EA4867C/6147056A" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/6147056A" Ref="R?"  Part="1" 
AR Path="/6147056A" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/6147056A" Ref="R9"  Part="1" 
F 0 "R9" H 4710 6286 50  0000 L CNN
F 1 "10k" H 4710 6195 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4570 6240 50  0001 C CNN
F 3 "~" H 4640 6240 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 4640 6240 50  0001 C CNN "lcsc"
	1    4640 6240
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F46C853
P 4350 6240
AR Path="/5EA4867C/5F46C853" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F46C853" Ref="R?"  Part="1" 
AR Path="/5F46C853" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5F46C853" Ref="R8"  Part="1" 
F 0 "R8" H 4420 6286 50  0000 L CNN
F 1 "10k" H 4420 6195 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4280 6240 50  0001 C CNN
F 3 "~" H 4350 6240 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 4350 6240 50  0001 C CNN "lcsc"
	1    4350 6240
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3250 7600 3250
Wire Wire Line
	6350 3450 8100 3450
Wire Wire Line
	6350 3550 8350 3550
Wire Wire Line
	8600 3750 8600 3700
Wire Wire Line
	6350 3750 8600 3750
$EndSCHEMATC
