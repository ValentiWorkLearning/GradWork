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
$Comp
L Device:Antenna_Chip AE1
U 1 1 5EAD751A
P 3150 2550
F 0 "AE1" H 3625 2700 50  0000 R CNN
F 1 "Antenna_Chip" H 3800 2575 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3050 2725 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/TDK-ANT016008LCS2442MA2_C209892.pdf" H 3050 2725 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Antennas_TDK-ANT016008LCS2442MA2_C209892.html" H 3150 2550 50  0001 C CNN "lcsc"
	1    3150 2550
	-1   0    0    -1  
$EndComp
Connection ~ 3475 2650
Wire Wire Line
	3250 2650 3475 2650
Wire Wire Line
	3050 2650 2800 2650
Text Label 2800 2650 0    50   ~ 0
Length
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
	10075 5400 10500 5400
Text Label 10500 5400 2    50   ~ 0
LEDK
Wire Wire Line
	8000 5700 8275 5700
Text Label 8125 5700 0    50   ~ 0
GND
Text Notes 7450 6225 0    50   ~ 0
inernal pull-down\nHigh level input min 1.3V
Text Label 7675 5975 0    50   ~ 0
Backlight_EN_DIM
Wire Wire Line
	7675 5975 8275 5975
$Comp
L LocalLedDrivers:CAT4002ATD-GT3 U3
U 1 1 5EAE51FD
P 8275 5400
F 0 "U3" H 9175 5787 60  0000 C CNN
F 1 "CAT4002ATD-GT3" H 9175 5681 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6_Handsoldering" H 9175 5640 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1809111523_ON-Semiconductor-CAT4002ATD-GT3_C184641.pdf" H 8275 5400 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/LED-Drivers_ON-Semiconductor-ON-CAT4002ATD-GT3_C184641.html" H 8275 5400 50  0001 C CNN "lcsc"
	1    8275 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10075 5500 10075 5400
Connection ~ 10075 5400
Wire Wire Line
	10075 5900 10350 5900
Wire Wire Line
	10350 6200 10350 6250
Wire Notes Line
	6950 4950 11150 4950
Wire Notes Line
	11150 4950 11150 6450
Wire Notes Line
	11150 6450 6950 6450
Wire Notes Line
	6950 6450 6950 4950
Text Notes 7250 5075 0    50   ~ 0
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
Crystal oscillators
Text Notes 2375 3850 0    50   ~ 0
32.768 KHz\n
Text Notes 1250 3875 0    50   ~ 0
32 MHz
$Comp
L Device:Crystal_Small X2
U 1 1 5EAFAA45
P 2600 3425
F 0 "X2" H 2600 3558 50  0000 C CNN
F 1 "Crystal_Small" H 2600 3559 50  0001 C CNN
F 2 "Crystal:Crystal_SMD_3215-2Pin_3.2x1.5mm" H 2600 3425 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/2104141604_TKD-SF32WK32768D31T002_C271654.pdf" H 2600 3425 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Crystals_TKD-SF32WK32768D31T002_C271654.html" H 2600 3425 50  0001 C CNN "lcsc"
	1    2600 3425
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 3750 2850 3750
Wire Wire Line
	2850 3725 2850 3750
Wire Wire Line
	2350 3725 2350 3750
$Comp
L Device:C C8
U 1 1 5EAF844F
P 2350 3575
F 0 "C8" H 2075 3650 50  0000 L CNN
F 1 "10 pF" H 2050 3525 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2388 3425 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CGR82C500NT_C501852.html" H 2350 3575 50  0001 C CNN
	1    2350 3575
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 3425 2500 3425
$Comp
L Device:C C11
U 1 1 5EAF8448
P 2850 3575
F 0 "C11" H 2965 3621 50  0000 L CNN
F 1 "10 pF" H 2965 3530 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2888 3425 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CGR82C500NT_C501852.html" H 2850 3575 50  0001 C CNN
	1    2850 3575
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 3425 2850 3425
Text Label 2850 3425 2    50   ~ 0
XL2
Text Label 2350 3425 0    50   ~ 0
XL1
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
L WatchBorad-rescue:Crystal_GND24_Small-Device-WatchBorad-rescue-WatchBorad-rescue X1
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
$Comp
L Connector:Conn_01x07_Female J?
U 1 1 5F025ED5
P 2125 5375
AR Path="/5F025ED5" Ref="J?"  Part="1" 
AR Path="/5E9B1DCE/5F025ED5" Ref="J1"  Part="1" 
F 0 "J1" H 2152 5401 50  0000 L CNN
F 1 "Conn_01x07_Female" H 875 4875 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x07_P2.54mm_Vertical" H 2125 5375 50  0001 C CNN
F 3 "~" H 2125 5375 50  0001 C CNN
	1    2125 5375
	1    0    0    -1  
$EndComp
Wire Wire Line
	1825 5075 1925 5075
Text Label 975  5175 2    50   ~ 0
HEART_SCL
Text Label 975  5275 2    50   ~ 0
HEART_SDA
Text Label 975  5375 2    50   ~ 0
HEART_INT
Text Label 975  5475 2    50   ~ 0
HEART_IRD
$Comp
L power:GND #PWR?
U 1 1 5F025EE6
P 1825 5725
AR Path="/5F025EE6" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F025EE6" Ref="#PWR04"  Part="1" 
F 0 "#PWR04" H 1825 5475 50  0001 C CNN
F 1 "GND" H 1830 5552 50  0000 C CNN
F 2 "" H 1825 5725 50  0001 C CNN
F 3 "" H 1825 5725 50  0001 C CNN
	1    1825 5725
	1    0    0    -1  
$EndComp
Text Label 975  5575 2    50   ~ 0
HEART_RD
Wire Wire Line
	1925 5675 1825 5675
Wire Wire Line
	1825 5675 1825 5725
Wire Wire Line
	975  5175 1025 5175
Wire Wire Line
	975  5275 1275 5275
Wire Wire Line
	975  5375 1525 5375
Wire Wire Line
	1525 4750 1525 4500
Wire Wire Line
	1525 4500 1450 4500
Wire Wire Line
	1275 4500 1275 4750
Connection ~ 1525 4500
Wire Wire Line
	1275 4500 1025 4500
Wire Wire Line
	1025 4500 1025 4750
Connection ~ 1275 4500
Connection ~ 1025 5175
Wire Wire Line
	1025 5175 1925 5175
Connection ~ 1275 5275
Wire Wire Line
	1275 5275 1925 5275
Connection ~ 1525 5375
Wire Wire Line
	1525 5375 1925 5375
Text Notes 575  5775 0    50   ~ 0
MAX30102 Heartrate
Wire Notes Line
	550  4275 550  6000
Wire Notes Line
	550  6000 2300 6000
Wire Notes Line
	2300 6000 2300 4275
Wire Notes Line
	2300 4275 550  4275
Wire Wire Line
	6600 3950 6350 3950
Text Label 8200 4400 0    50   ~ 0
HEART_SDA
Text Label 8150 4100 0    50   ~ 0
HEART_INT
Text Label 8200 4500 0    50   ~ 0
HEART_SCL
Text Label 1675 6700 0    50   ~ 0
SWD_SWDIO
Text Label 1675 6800 0    50   ~ 0
SWD_SWDCLK
Text Label 1675 6900 0    50   ~ 0
SWD_RESET
Text Label 1675 7000 0    50   ~ 0
SWD_SWO
Text Notes 875  7125 0    50   ~ 0
SWD programming interface
Wire Notes Line
	550  6050 2150 6050
Wire Notes Line
	2150 6050 2150 7175
Wire Notes Line
	2150 7175 550  7175
Wire Wire Line
	1525 4500 1825 4500
Wire Notes Line
	550  6050 550  7175
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
Text Label 6750 3450 0    50   ~ 0
DISP_CS
Text Label 6750 3550 0    50   ~ 0
DISP_SCLK
Text Label 6800 3750 0    50   ~ 0
DISP_SDA
Text Label 7100 2450 2    50   ~ 0
Backlight_EN_DIM
Wire Wire Line
	6350 2050 7050 2050
$Comp
L Device:C C?
U 1 1 5F46C82F
P 2700 6950
AR Path="/5EA4867C/5F46C82F" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F46C82F" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5F46C82F" Ref="C16"  Part="1" 
AR Path="/5F46C82F" Ref="C?"  Part="1" 
F 0 "C16" H 2725 7025 50  0000 L CNN
F 1 "100 nF" V 2550 6825 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2738 6800 50  0001 C CNN
F 3 "~" H 2700 6950 50  0001 C CNN
	1    2700 6950
	1    0    0    -1  
$EndComp
Text Label 2525 6650 0    50   ~ 0
MPU_INT_1
Text Label 4775 6350 0    50   ~ 0
I2C_SDA
Text Label 4775 6450 0    50   ~ 0
I2C_SCL
Wire Notes Line
	6825 7700 2350 7700
Wire Notes Line
	2350 7700 2350 5125
Wire Notes Line
	2350 5125 4900 5125
Text Label 6600 2650 0    50   ~ 0
I2C_SCL
Text Label 6600 2550 0    50   ~ 0
I2C_SDA
Wire Wire Line
	6600 2550 6350 2550
Wire Wire Line
	6350 2650 6600 2650
$Comp
L Connector:TestPoint TP?
U 1 1 5F6067FE
P 8250 3750
AR Path="/5EA4867C/5F6067FE" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5F6067FE" Ref="TP6"  Part="1" 
F 0 "TP6" H 8308 3822 50  0000 L CNN
F 1 "TestPoint" H 8308 3777 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 8450 3750 50  0001 C CNN
F 3 "~" H 8450 3750 50  0001 C CNN
	1    8250 3750
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5F619095
P 8100 3550
AR Path="/5EA4867C/5F619095" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5F619095" Ref="TP7"  Part="1" 
F 0 "TP7" H 8158 3622 50  0000 L CNN
F 1 "TestPoint" H 8158 3577 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 8300 3550 50  0001 C CNN
F 3 "~" H 8300 3550 50  0001 C CNN
	1    8100 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5F62BA5E
P 7900 3300
AR Path="/5EA4867C/5F62BA5E" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5F62BA5E" Ref="TP8"  Part="1" 
F 0 "TP8" H 7958 3372 50  0000 L CNN
F 1 "TestPoint" H 7958 3327 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 8100 3300 50  0001 C CNN
F 3 "~" H 8100 3300 50  0001 C CNN
	1    7900 3300
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5F63E448
P 8000 3450
AR Path="/5EA4867C/5F63E448" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5F63E448" Ref="TP9"  Part="1" 
F 0 "TP9" H 8058 3522 50  0000 L CNN
F 1 "TestPoint" H 8058 3477 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 8200 3450 50  0001 C CNN
F 3 "~" H 8200 3450 50  0001 C CNN
	1    8000 3450
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
Wire Wire Line
	2350 3750 2275 3750
Wire Wire Line
	2275 3750 2275 3775
Connection ~ 2350 3750
$Comp
L power:GND #PWR?
U 1 1 5FC6D69A
P 2275 3775
AR Path="/5FC6D69A" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FC6D69A" Ref="#PWR07"  Part="1" 
F 0 "#PWR07" H 2275 3525 50  0001 C CNN
F 1 "GND" H 2275 3625 50  0000 C CNN
F 2 "" H 2275 3775 50  0001 C CNN
F 3 "" H 2275 3775 50  0001 C CNN
	1    2275 3775
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F9CCFB6
P 7875 5325
AR Path="/5E9C1C3A/5F9CCFB6" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9CCFB6" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9CCFB6" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F9CCFB6" Ref="#PWR015"  Part="1" 
F 0 "#PWR015" H 7875 5175 50  0001 C CNN
F 1 "+3.3V" H 7890 5498 50  0000 C CNN
F 2 "" H 7875 5325 50  0001 C CNN
F 3 "" H 7875 5325 50  0001 C CNN
	1    7875 5325
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
U 1 1 5FA32972
P 2675 5750
AR Path="/5E9C1C3A/5FA32972" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5FA32972" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5FA32972" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FA32972" Ref="#PWR09"  Part="1" 
F 0 "#PWR09" H 2675 5600 50  0001 C CNN
F 1 "+3.3V" H 2690 5923 50  0000 C CNN
F 2 "" H 2675 5750 50  0001 C CNN
F 3 "" H 2675 5750 50  0001 C CNN
	1    2675 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 6800 2700 6750
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
P 10350 6250
AR Path="/5FAF3706" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FAF3706" Ref="#PWR021"  Part="1" 
F 0 "#PWR021" H 10350 6000 50  0001 C CNN
F 1 "GND" H 10350 6100 50  0000 C CNN
F 2 "" H 10350 6250 50  0001 C CNN
F 3 "" H 10350 6250 50  0001 C CNN
	1    10350 6250
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
$Comp
L power:+3.3V #PWR?
U 1 1 5FB08B0E
P 1450 4500
AR Path="/5E9C1C3A/5FB08B0E" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5FB08B0E" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5FB08B0E" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FB08B0E" Ref="#PWR02"  Part="1" 
F 0 "#PWR02" H 1450 4350 50  0001 C CNN
F 1 "+3.3V" H 1465 4673 50  0000 C CNN
F 2 "" H 1450 4500 50  0001 C CNN
F 3 "" H 1450 4500 50  0001 C CNN
	1    1450 4500
	1    0    0    -1  
$EndComp
Connection ~ 1450 4500
Wire Wire Line
	1450 4500 1275 4500
Text HLabel 7100 4050 2    50   BiDi ~ 0
SDA_FG
Text HLabel 7100 4150 2    50   Input ~ 0
SCL_FG
Wire Wire Line
	6350 4050 7100 4050
Wire Wire Line
	6350 4150 7100 4150
Wire Wire Line
	1925 5475 975  5475
Wire Wire Line
	975  5575 1925 5575
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
P 675 6575
AR Path="/5EA4867C/5FD9ED2F" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5FD9ED2F" Ref="TP1"  Part="1" 
F 0 "TP1" H 700 6650 50  0000 L CNN
F 1 "TestPoint" H 733 6602 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 875 6575 50  0001 C CNN
F 3 "~" H 875 6575 50  0001 C CNN
	1    675  6575
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5FD9FCBC
P 900 6575
AR Path="/5EA4867C/5FD9FCBC" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5FD9FCBC" Ref="TP2"  Part="1" 
F 0 "TP2" H 925 6650 50  0000 L CNN
F 1 "TestPoint" H 958 6602 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 1100 6575 50  0001 C CNN
F 3 "~" H 1100 6575 50  0001 C CNN
	1    900  6575
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5FDA011E
P 1125 6575
AR Path="/5EA4867C/5FDA011E" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5FDA011E" Ref="TP3"  Part="1" 
F 0 "TP3" H 1150 6650 50  0000 L CNN
F 1 "TestPoint" H 1183 6602 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 1325 6575 50  0001 C CNN
F 3 "~" H 1325 6575 50  0001 C CNN
	1    1125 6575
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5FDA04CF
P 1350 6575
AR Path="/5EA4867C/5FDA04CF" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5FDA04CF" Ref="TP4"  Part="1" 
F 0 "TP4" H 1375 6650 50  0000 L CNN
F 1 "TestPoint" H 1408 6602 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 1550 6575 50  0001 C CNN
F 3 "~" H 1550 6575 50  0001 C CNN
	1    1350 6575
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 6575 1350 6700
Wire Wire Line
	1350 6700 1675 6700
Wire Wire Line
	1125 6575 1125 6800
Wire Wire Line
	1125 6800 1675 6800
Wire Wire Line
	900  6575 900  6900
Wire Wire Line
	900  6900 1675 6900
Wire Wire Line
	675  6575 675  7000
Wire Wire Line
	675  7000 1675 7000
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
$Comp
L Device:R R?
U 1 1 5F46C853
P 5800 6050
AR Path="/5EA4867C/5F46C853" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F46C853" Ref="R?"  Part="1" 
AR Path="/5F46C853" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5F46C853" Ref="R8"  Part="1" 
F 0 "R8" H 5870 6096 50  0000 L CNN
F 1 "10k" H 5870 6005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5730 6050 50  0001 C CNN
F 3 "~" H 5800 6050 50  0001 C CNN
	1    5800 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F46C86E
P 2950 6000
AR Path="/5EA4867C/5F46C86E" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F46C86E" Ref="R?"  Part="1" 
AR Path="/5F46C86E" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5F46C86E" Ref="R5"  Part="1" 
F 0 "R5" H 3020 6046 50  0000 L CNN
F 1 "10k" H 3020 5955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2880 6000 50  0001 C CNN
F 3 "~" H 2950 6000 50  0001 C CNN
	1    2950 6000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F46C868
P 2475 5975
AR Path="/5EA4867C/5F46C868" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F46C868" Ref="R?"  Part="1" 
AR Path="/5F46C868" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5F46C868" Ref="R4"  Part="1" 
F 0 "R4" H 2545 6021 50  0000 L CNN
F 1 "10k" H 2545 5930 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2405 5975 50  0001 C CNN
F 3 "~" H 2475 5975 50  0001 C CNN
	1    2475 5975
	1    0    0    -1  
$EndComp
Wire Wire Line
	6875 3150 6350 3150
$Comp
L Device:R R?
U 1 1 5FD3FDC5
P 1025 4900
AR Path="/5EA4867C/5FD3FDC5" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5FD3FDC5" Ref="R?"  Part="1" 
AR Path="/5FD3FDC5" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5FD3FDC5" Ref="R1"  Part="1" 
F 0 "R1" H 1095 4946 50  0000 L CNN
F 1 "10k" H 1095 4855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 955 4900 50  0001 C CNN
F 3 "~" H 1025 4900 50  0001 C CNN
	1    1025 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5FD402B6
P 1275 4900
AR Path="/5EA4867C/5FD402B6" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5FD402B6" Ref="R?"  Part="1" 
AR Path="/5FD402B6" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5FD402B6" Ref="R2"  Part="1" 
F 0 "R2" H 1345 4946 50  0000 L CNN
F 1 "10k" H 1345 4855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1205 4900 50  0001 C CNN
F 3 "~" H 1275 4900 50  0001 C CNN
	1    1275 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5FD40649
P 1525 4900
AR Path="/5EA4867C/5FD40649" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5FD40649" Ref="R?"  Part="1" 
AR Path="/5FD40649" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5FD40649" Ref="R3"  Part="1" 
F 0 "R3" H 1595 4946 50  0000 L CNN
F 1 "10k" H 1595 4855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1455 4900 50  0001 C CNN
F 3 "~" H 1525 4900 50  0001 C CNN
	1    1525 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5FD423EF
P 5475 6050
AR Path="/5EA4867C/5FD423EF" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5FD423EF" Ref="R?"  Part="1" 
AR Path="/5FD423EF" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5FD423EF" Ref="R7"  Part="1" 
F 0 "R7" H 5545 6096 50  0000 L CNN
F 1 "10k" H 5545 6005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5405 6050 50  0001 C CNN
F 3 "~" H 5475 6050 50  0001 C CNN
	1    5475 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8875 3175 8875 3200
Wire Wire Line
	8400 3175 8400 3200
Text Label 6775 3050 2    50   ~ 0
MPU_INT_2
$Comp
L Device:R R?
U 1 1 5FFF65BE
P 10350 6050
AR Path="/5EA4867C/5FFF65BE" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5FFF65BE" Ref="R?"  Part="1" 
AR Path="/5FFF65BE" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5FFF65BE" Ref="R14"  Part="1" 
F 0 "R14" H 10420 6096 50  0000 L CNN
F 1 "10k" H 10420 6005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10280 6050 50  0001 C CNN
F 3 "~" H 10350 6050 50  0001 C CNN
	1    10350 6050
	1    0    0    -1  
$EndComp
Text Notes 10200 5825 0    50   ~ 0
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
P 8000 5550
AR Path="/5EA4867C/6001C706" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/6001C706" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/6001C706" Ref="C?"  Part="1" 
AR Path="/5F988DA5/6001C706" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/6001C706" Ref="C20"  Part="1" 
F 0 "C20" H 8025 5625 50  0000 L CNN
F 1 "10 uF" V 7850 5425 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8038 5400 50  0001 C CNN
F 3 "~" H 8000 5550 50  0001 C CNN
F 4 "" H 8000 5550 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 8000 5550 50  0001 C CNN "lcsc"
	1    8000 5550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6002FB7F
P 2075 4650
AR Path="/5EA4867C/6002FB7F" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/6002FB7F" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/6002FB7F" Ref="C?"  Part="1" 
AR Path="/5F988DA5/6002FB7F" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/6002FB7F" Ref="C6"  Part="1" 
F 0 "C6" H 2100 4725 50  0000 L CNN
F 1 "10 uF" V 1925 4525 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2113 4500 50  0001 C CNN
F 3 "~" H 2075 4650 50  0001 C CNN
F 4 "" H 2075 4650 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 2075 4650 50  0001 C CNN "lcsc"
	1    2075 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2075 4500 1825 4500
Connection ~ 1825 4500
$Comp
L power:GND #PWR?
U 1 1 600671A4
P 2075 4825
AR Path="/600671A4" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/600671A4" Ref="#PWR06"  Part="1" 
F 0 "#PWR06" H 2075 4575 50  0001 C CNN
F 1 "GND" H 2080 4652 50  0000 C CNN
F 2 "" H 2075 4825 50  0001 C CNN
F 3 "" H 2075 4825 50  0001 C CNN
	1    2075 4825
	1    0    0    -1  
$EndComp
Wire Wire Line
	1025 5050 1025 5175
Wire Wire Line
	1275 5050 1275 5275
Wire Wire Line
	1525 5050 1525 5375
Wire Wire Line
	1825 4500 1825 5075
Wire Wire Line
	2075 4800 2075 4825
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
	7875 5325 7875 5375
Wire Wire Line
	7875 5375 8000 5375
Wire Wire Line
	8275 5375 8275 5400
Wire Wire Line
	8000 5400 8000 5375
Connection ~ 8000 5375
Wire Wire Line
	8000 5375 8275 5375
Text Label 8075 5375 0    50   ~ 0
LEDA
NoConn ~ 2800 2650
$Comp
L GC9A01:GC9A01 U11
U 1 1 60CF55BA
P 10250 4050
AR Path="/60CF55BA" Ref="U11"  Part="1" 
AR Path="/5E9B1DCE/60CF55BA" Ref="U11"  Part="1" 
F 0 "U11" H 10428 4046 50  0000 L CNN
F 1 "GC9A01" H 10428 3955 50  0000 L CNN
F 2 "LocalFootprints:GC9A01_disp" H 10000 4400 50  0001 C CNN
F 3 "https://www.buydisplay.com/download/ic/GC9A01A.pdf" H 10000 4400 50  0001 C CNN
	1    10250 4050
	1    0    0    -1  
$EndComp
Text Label 7050 3350 2    50   ~ 0
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
Text Label 6750 3250 0    50   ~ 0
P17
$Comp
L WatchBorad-rescue:LSM6DSLTR-2021-06-21_20-09-55-WatchBorad-rescue U1
U 1 1 60D5E125
P 2950 6350
AR Path="/60D5E125" Ref="U1"  Part="1" 
AR Path="/5E9B1DCE/60D5E125" Ref="U1"  Part="1" 
F 0 "U1" H 3850 6737 60  0000 C CNN
F 1 "LSM6DSLTR" H 3850 6631 60  0000 C CNN
F 2 "LocalFootprints:LSM6DSLTR" H 3850 6590 60  0001 C CNN
F 3 "" H 2950 6350 60  0000 C CNN
	1    2950 6350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D9BCF3
P 2925 7150
AR Path="/60D9BCF3" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/60D9BCF3" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 2925 6900 50  0001 C CNN
F 1 "GND" H 2930 6977 50  0000 C CNN
F 2 "" H 2925 7150 50  0001 C CNN
F 3 "" H 2925 7150 50  0001 C CNN
	1    2925 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2925 7150 2925 6950
Wire Wire Line
	2925 6850 2950 6850
Wire Wire Line
	2950 6950 2925 6950
Connection ~ 2925 6950
Wire Wire Line
	2925 6950 2925 6850
Wire Wire Line
	6350 3050 6775 3050
Text Notes 2950 5675 0    50   ~ 0
LSM6DSL addr is 1101011b
Wire Wire Line
	2950 5850 2950 5750
Wire Wire Line
	2950 6150 2950 6350
Wire Wire Line
	2950 6750 2700 6750
$Comp
L power:GND #PWR?
U 1 1 5FA84810
P 2700 7150
AR Path="/5FA84810" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FA84810" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 2700 6900 50  0001 C CNN
F 1 "GND" H 2705 6977 50  0000 C CNN
F 2 "" H 2700 7150 50  0001 C CNN
F 3 "" H 2700 7150 50  0001 C CNN
	1    2700 7150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F46C829
P 4975 7125
AR Path="/5EA4867C/5F46C829" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F46C829" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5F46C829" Ref="C14"  Part="1" 
AR Path="/5F46C829" Ref="C?"  Part="1" 
F 0 "C14" H 5000 7200 50  0000 L CNN
F 1 "100 nF" V 4825 7000 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5013 6975 50  0001 C CNN
F 3 "~" H 4975 7125 50  0001 C CNN
	1    4975 7125
	1    0    0    -1  
$EndComp
Wire Wire Line
	4975 6975 4975 6950
Wire Wire Line
	4975 6950 4750 6950
Wire Wire Line
	4975 7275 4975 7400
$Comp
L power:GND #PWR?
U 1 1 60F5C10B
P 4975 7400
AR Path="/60F5C10B" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/60F5C10B" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 4975 7150 50  0001 C CNN
F 1 "GND" H 4980 7227 50  0000 C CNN
F 2 "" H 4975 7400 50  0001 C CNN
F 3 "" H 4975 7400 50  0001 C CNN
	1    4975 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 7100 2700 7150
Wire Wire Line
	2675 5750 2675 6550
Connection ~ 2800 5750
Wire Wire Line
	2800 5750 2950 5750
Wire Wire Line
	2675 5750 2475 5750
Connection ~ 2675 5750
Wire Wire Line
	2675 5750 2800 5750
Wire Wire Line
	2950 6550 2675 6550
Wire Wire Line
	2950 6450 2800 6450
Wire Wire Line
	2800 5750 2800 6450
Wire Wire Line
	2475 6125 2475 6650
Wire Wire Line
	2475 5750 2475 5825
Wire Wire Line
	5475 6450 5475 6200
Wire Wire Line
	2475 6650 2950 6650
Connection ~ 5325 5725
Wire Wire Line
	5475 5725 5325 5725
$Comp
L power:+3.3V #PWR?
U 1 1 6123BFAB
P 5325 5725
AR Path="/5E9C1C3A/6123BFAB" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/6123BFAB" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/6123BFAB" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/6123BFAB" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 5325 5575 50  0001 C CNN
F 1 "+3.3V" H 5340 5898 50  0000 C CNN
F 2 "" H 5325 5725 50  0001 C CNN
F 3 "" H 5325 5725 50  0001 C CNN
	1    5325 5725
	1    0    0    -1  
$EndComp
Wire Wire Line
	5475 5725 5475 5900
Wire Wire Line
	5200 5725 5200 5900
Wire Wire Line
	5200 5725 5325 5725
Wire Wire Line
	4750 6350 5200 6350
Wire Wire Line
	5200 6200 5200 6350
Wire Wire Line
	4750 6450 5475 6450
$Comp
L Device:R R?
U 1 1 5F46C84B
P 5200 6050
AR Path="/5EA4867C/5F46C84B" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F46C84B" Ref="R?"  Part="1" 
AR Path="/5F46C84B" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5F46C84B" Ref="R6"  Part="1" 
F 0 "R6" H 5270 6096 50  0000 L CNN
F 1 "10k" H 5270 6005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5130 6050 50  0001 C CNN
F 3 "~" H 5200 6050 50  0001 C CNN
	1    5200 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5475 5725 5800 5725
Connection ~ 5475 5725
Wire Wire Line
	5800 6200 5800 6550
Wire Wire Line
	5800 6550 4750 6550
$Comp
L Device:R R?
U 1 1 6147056A
P 6125 6050
AR Path="/5EA4867C/6147056A" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/6147056A" Ref="R?"  Part="1" 
AR Path="/6147056A" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/6147056A" Ref="R9"  Part="1" 
F 0 "R9" H 6195 6096 50  0000 L CNN
F 1 "10k" H 6195 6005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6055 6050 50  0001 C CNN
F 3 "~" H 6125 6050 50  0001 C CNN
	1    6125 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 5725 5800 5900
Wire Wire Line
	5800 5725 6125 5725
Wire Wire Line
	6125 5725 6125 5900
Connection ~ 5800 5725
Wire Wire Line
	6125 6200 6125 6850
Wire Wire Line
	4750 6850 6125 6850
Text Label 4775 6550 0    50   ~ 0
NC_PU
Text Label 4800 6850 0    50   ~ 0
MPU_INT_2
Wire Notes Line
	4875 5125 4875 5425
Wire Notes Line
	4875 5425 6825 5425
Wire Notes Line
	6825 5425 6825 7700
Wire Notes Line
	2900 6175 3200 6175
Wire Notes Line
	3200 6175 3200 5825
Wire Notes Line
	3200 5825 4300 5825
Wire Notes Line
	4300 5825 4300 5375
Wire Notes Line
	4300 5375 2900 5375
Wire Notes Line
	2900 5375 2900 6175
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
	6350 3750 8250 3750
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
F 2 "" H 9175 2550 50  0001 C CNN
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
Wire Wire Line
	6350 3550 8100 3550
Wire Wire Line
	6350 3450 8000 3450
$Comp
L Connector:TestPoint TP?
U 1 1 5F650E32
P 8350 3850
AR Path="/5EA4867C/5F650E32" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5F650E32" Ref="TP10"  Part="1" 
F 0 "TP10" H 8408 3922 50  0000 L CNN
F 1 "TestPoint" H 8408 3877 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 8550 3850 50  0001 C CNN
F 3 "~" H 8550 3850 50  0001 C CNN
	1    8350 3850
	1    0    0    -1  
$EndComp
Text Label 7200 3850 2    50   ~ 0
DISP_RESET
Wire Wire Line
	6350 3850 8350 3850
Wire Wire Line
	7900 3350 7900 3300
Wire Wire Line
	6350 3350 7900 3350
Wire Wire Line
	6750 3250 6350 3250
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
Wire Notes Line
	11150 6650 7000 6650
Text Notes 7150 6800 0    50   ~ 0
RTC_I2C
Wire Wire Line
	10500 7550 10700 7550
$Comp
L power:GND #PWR0105
U 1 1 61774516
P 8550 9200
F 0 "#PWR0105" H 8550 8950 50  0001 C CNN
F 1 "GND" H 8555 9027 50  0000 C CNN
F 2 "" H 8550 9200 50  0001 C CNN
F 3 "" H 8550 9200 50  0001 C CNN
	1    8550 9200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0106
U 1 1 61788AB0
P 8950 7100
F 0 "#PWR0106" H 8950 6950 50  0001 C CNN
F 1 "+3.3V" H 8965 7273 50  0000 C CNN
F 2 "" H 8950 7100 50  0001 C CNN
F 3 "" H 8950 7100 50  0001 C CNN
	1    8950 7100
	1    0    0    -1  
$EndComp
Text Label 8450 7550 2    50   ~ 0
I2C_SCL
Text Label 10800 7550 0    50   ~ 0
I2C_SDA
$Comp
L M41T62Q6F:M41T62Q6F U12
U 1 1 617DA662
P 9800 8050
F 0 "U12" H 9800 9220 50  0000 C CNN
F 1 "M41T62Q6F" H 9800 9129 50  0000 C CNN
F 2 "QFN50P300X300X100-17N" H 9800 8050 50  0001 L BNN
F 3 "https://datasheet.lcsc.com/lcsc/1806121917_STMicroelectronics-M41T62Q6F_C113207.pdf" H 9800 8050 50  0001 L BNN
F 4 "M41T62Q6F" H 9800 8050 50  0001 L BNN "MPN"
F 5 "1224441" H 9800 8050 50  0001 L BNN "OC_FARNELL"
F 6 "56P9316" H 9800 8050 50  0001 L BNN "OC_NEWARK"
F 7 "QFN-16" H 9800 8050 50  0001 L BNN "PACKAGE"
F 8 "STMICROELECTRONICS" H 9800 8050 50  0001 L BNN "SUPPLIER"
F 9 "https://lcsc.com/product-detail/Real-time-Clocks-span-style-background-color-ff0-RTC-span_STMicroelectronics-M41T62Q6F_C113207.html" H 9800 8050 50  0001 C CNN "lcsc"
	1    9800 8050
	1    0    0    -1  
$EndComp
Wire Notes Line
	11150 6650 11150 9500
Wire Notes Line
	11150 9500 7000 9500
Wire Notes Line
	7000 6650 7000 9500
Wire Wire Line
	8550 9050 8550 9200
Wire Wire Line
	8550 9050 8700 9050
$Comp
L Device:Crystal_Small Y1
U 1 1 6171009D
P 7800 7900
F 0 "Y1" V 7850 8100 50  0000 R CNN
F 1 "Crystal_Small" V 7750 8500 50  0000 R CNN
F 2 "Crystal:Crystal_SMD_3215-2Pin_3.2x1.5mm" H 7800 7900 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/2104141604_TKD-SF32WK32768D31T002_C271654.pdf" H 7800 7900 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Crystals_TKD-SF32WK32768D31T002_C271654.html" V 7800 7900 50  0001 C CNN "LCSC"
	1    7800 7900
	0    -1   -1   0   
$EndComp
Text Label 8000 8100 0    50   ~ 0
XO_RTC
Text Label 8000 7700 0    50   ~ 0
XI_RTC
Wire Wire Line
	7800 7800 7800 7700
Wire Wire Line
	7800 7700 8000 7700
Wire Wire Line
	7800 8000 7800 8100
Wire Wire Line
	7800 8100 8000 8100
Text Label 8800 7750 2    50   ~ 0
XI_RTC
Wire Wire Line
	8800 7750 9100 7750
Text Label 10500 7050 0    50   ~ 0
XO_RTC
Wire Wire Line
	8950 7250 9100 7250
Wire Wire Line
	9100 8950 8700 8950
Wire Wire Line
	8700 8950 8700 9050
Connection ~ 8700 9050
Wire Wire Line
	8700 9050 9100 9050
$Comp
L Device:R R19
U 1 1 619E23FE
P 8550 7300
F 0 "R19" H 8620 7346 50  0000 L CNN
F 1 "10k" H 8620 7255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8480 7300 50  0001 C CNN
F 3 "~" H 8550 7300 50  0001 C CNN
	1    8550 7300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 7150 8950 7150
Wire Wire Line
	8950 7100 8950 7150
Connection ~ 8950 7150
Wire Wire Line
	8950 7150 8950 7250
Wire Wire Line
	8550 7450 8550 7550
Wire Wire Line
	8550 7550 9100 7550
Wire Wire Line
	8550 7550 8450 7550
Connection ~ 8550 7550
$Comp
L Device:R R22
U 1 1 61A1EFF3
P 10700 7400
F 0 "R22" H 10770 7446 50  0000 L CNN
F 1 "10k" H 10770 7355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10630 7400 50  0001 C CNN
F 3 "~" H 10700 7400 50  0001 C CNN
	1    10700 7400
	1    0    0    -1  
$EndComp
Connection ~ 10700 7550
Wire Wire Line
	10700 7550 10800 7550
Wire Wire Line
	10500 7050 10500 7250
Wire Wire Line
	10700 7250 10700 7100
Wire Wire Line
	10700 7100 10900 7100
$Comp
L power:+3.3V #PWR012
U 1 1 61A48329
P 10900 7100
F 0 "#PWR012" H 10900 6950 50  0001 C CNN
F 1 "+3.3V" H 10915 7273 50  0000 C CNN
F 2 "" H 10900 7100 50  0001 C CNN
F 3 "" H 10900 7100 50  0001 C CNN
	1    10900 7100
	1    0    0    -1  
$EndComp
$EndSCHEMATC
