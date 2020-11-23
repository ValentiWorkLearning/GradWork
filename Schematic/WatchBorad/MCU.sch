EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
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
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 4163 2725 50  0001 C CNN
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
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 3800 2650 50  0001 C CNN
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
L Device:C C12
U 1 1 5EAD533A
P 3475 2875
F 0 "C12" H 3525 2975 50  0000 L CNN
F 1 "0.8 pF" H 3525 2775 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 3513 2725 50  0001 C CNN
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
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 3050 2725 50  0001 C CNN
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
Wire Wire Line
	6350 2850 6900 2850
$Comp
L Device:C C19
U 1 1 5EACAA30
P 6900 3000
F 0 "C19" H 7015 3046 50  0000 L CNN
F 1 "130 pF" H 7015 2955 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 6938 2850 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CGR82C500NT_C501852.html" H 6900 3000 50  0001 C CNN
	1    6900 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C20
U 1 1 5EACB58A
P 7375 3025
F 0 "C20" H 7490 3071 50  0000 L CNN
F 1 "130 pF" H 7490 2980 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 7413 2875 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CGR82C500NT_C501852.html" H 7375 3025 50  0001 C CNN
	1    7375 3025
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 3150 6900 3300
Wire Wire Line
	6900 3300 7200 3300
Wire Wire Line
	7375 3300 7375 3175
Wire Wire Line
	7375 2875 7375 2750
Wire Wire Line
	6350 2750 7375 2750
Text Label 7150 2750 0    50   ~ 0
NFC1
Text Label 6650 2850 0    50   ~ 0
NFC2
Text Notes 1925 4150 0    50   ~ 0
The SWDCLK line has an internal pull-down resistor.\nThe SWDIO line has an internal pull-up resistor.\n
Text Label 4025 4150 0    50   ~ 0
SWD_SWDIO
Text Label 4025 4050 0    50   ~ 0
SWD_SWDCLK
Wire Wire Line
	5250 1650 5250 1125
Wire Wire Line
	5250 1125 5525 1125
$Comp
L Device:C C?
U 1 1 5EAD371C
P 1175 1150
AR Path="/5EA4867C/5EAD371C" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EAD371C" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5EAD371C" Ref="C2"  Part="1" 
F 0 "C2" H 1200 1225 50  0000 L CNN
F 1 "1 uF " V 1025 1025 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1213 1000 50  0001 C CNN
F 3 "~" H 1175 1150 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R105K160NT_C475249.html" H 1175 1150 50  0001 C CNN "LCSC"
	1    1175 1150
	1    0    0    -1  
$EndComp
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
Wire Wire Line
	5450 1275 5600 1275
$Comp
L Device:C C?
U 1 1 5EB047A2
P 2475 1150
AR Path="/5EA4867C/5EB047A2" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EB047A2" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5EB047A2" Ref="C8"  Part="1" 
F 0 "C8" H 2500 1225 50  0000 L CNN
F 1 "10 uF" V 2325 1025 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2513 1000 50  0001 C CNN
F 3 "~" H 2475 1150 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 2475 1150 50  0001 C CNN "LCSC"
	1    2475 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5EB07296
P 2825 1150
AR Path="/5EA4867C/5EB07296" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EB07296" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5EB07296" Ref="C9"  Part="1" 
F 0 "C9" H 2850 1225 50  0000 L CNN
F 1 "100 nF" V 2675 1025 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2863 1000 50  0001 C CNN
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
AR Path="/5E9B1DCE/5EB07FEF" Ref="C11"  Part="1" 
F 0 "C11" H 3150 1225 50  0000 L CNN
F 1 "100 nF" V 2975 1025 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 3163 1000 50  0001 C CNN
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
AR Path="/5E9B1DCE/5EB1B82C" Ref="C6"  Part="1" 
F 0 "C6" H 2175 1225 50  0000 L CNN
F 1 "100 nF" V 2000 1025 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2188 1000 50  0001 C CNN
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
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1838 1000 50  0001 C CNN
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
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1513 1000 50  0001 C CNN
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
Connection ~ 6900 2850
Wire Wire Line
	7375 2750 7675 2750
Connection ~ 7375 2750
$Comp
L Device:Antenna_Loop AE2
U 1 1 5EB3E2CF
P 7675 2550
F 0 "AE2" H 7905 2518 50  0000 L CNN
F 1 "Antenna_Loop" H 7905 2473 50  0001 L CNN
F 2 "" H 7675 2550 50  0001 C CNN
F 3 "~" H 7675 2550 50  0001 C CNN
	1    7675 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7775 2850 7775 2750
Wire Wire Line
	6900 2850 7775 2850
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
	8275 5400 8000 5400
$Comp
L Device:C C?
U 1 1 5EB4CC38
P 8000 5550
AR Path="/5EA4867C/5EB4CC38" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EB4CC38" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5EB4CC38" Ref="C21"  Part="1" 
F 0 "C21" H 8025 5625 50  0000 L CNN
F 1 "1 uF " V 7850 5425 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 8038 5400 50  0001 C CNN
F 3 "~" H 8000 5550 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R105K160NT_C475249.html" H 8000 5550 50  0001 C CNN "LCSC"
	1    8000 5550
	1    0    0    -1  
$EndComp
Connection ~ 8000 5400
Wire Wire Line
	8000 5400 7875 5400
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
$Comp
L Device:R R?
U 1 1 5EB69362
P 10350 6050
AR Path="/5EA4867C/5EB69362" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5EB69362" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5EB69362" Ref="R8"  Part="1" 
F 0 "R8" H 10150 6025 50  0000 L CNN
F 1 "4.7k" H 10125 6100 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 10280 6050 50  0001 C CNN
F 3 "~" H 10350 6050 50  0001 C CNN
	1    10350 6050
	1    0    0    1   
$EndComp
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
Text Label 8050 5400 0    50   ~ 0
LEDA
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
F 2 "Crystals:Crystal_SMD_2012-2pin_2.0x1.2mm" H 2600 3425 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Seiko-Instruments-SC-20S-32-768kHz-20PPM-7pF_C97602.pdf" H 2600 3425 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/SMD-Crystal-Resonators_Seiko_SC-20S-32-768kHz-20PPM-7pF_Seiko-SC-20S-32-768kHz-20PPM-7pF_C97602.html" H 2600 3425 50  0001 C CNN "lcsc"
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
L Device:C C7
U 1 1 5EAF844F
P 2350 3575
F 0 "C7" H 2075 3650 50  0000 L CNN
F 1 "10 pF" H 2050 3525 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2388 3425 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CGR82C500NT_C501852.html" H 2350 3575 50  0001 C CNN
	1    2350 3575
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 3425 2500 3425
$Comp
L Device:C C10
U 1 1 5EAF8448
P 2850 3575
F 0 "C10" H 2965 3621 50  0000 L CNN
F 1 "10 pF" H 2965 3530 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2888 3425 50  0001 C CNN
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
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1188 3425 50  0001 C CNN
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
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1688 3425 50  0001 C CNN
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
L Device:Crystal_GND24_Small X1
U 1 1 5EAD6468
P 1400 3425
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
	8550 1325 8350 1325
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
AR Path="/5E9B1DCE/5ECE6A9A" Ref="#PWR021"  Part="1" 
F 0 "#PWR021" H 10050 1675 50  0001 C CNN
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
$Comp
L W25Q16BVSSIG:MX25R1635F U?
U 1 1 5ECE6AE0
P 9250 1525
AR Path="/5ECE6AE0" Ref="U?"  Part="1" 
AR Path="/5E9B1DCE/5ECE6AE0" Ref="U4"  Part="1" 
F 0 "U4" H 9250 2195 50  0000 C CNN
F 1 "MX25R1635F" H 9250 2104 50  0000 C CNN
F 2 "SMD_Packages:SOIC-8-N" H 9250 1525 50  0001 L BNN
F 3 "https://datasheet.lcsc.com/szlcsc/Macronix-MX25R1635FM2IL0_C152602.pdf" H 9250 1525 50  0001 L BNN
F 4 "https://lcsc.com/product-detail/FLASH_MXIC-Macronix-MX25R1635FM2IL0_C152602.html" H 9250 1525 50  0001 C CNN "lcsc"
	1    9250 1525
	1    0    0    -1  
$EndComp
Text Label 6600 2150 0    50   ~ 0
FLASH_CS
Text Label 6600 2250 0    50   ~ 0
FLASH_MISO
Text Label 6600 2350 0    50   ~ 0
FLASH_SCK
Text Label 6600 2450 0    50   ~ 0
FLASH_MOSI
Wire Wire Line
	6600 2150 6350 2150
Wire Wire Line
	6350 2250 6600 2250
Wire Wire Line
	6600 2350 6350 2350
Wire Wire Line
	6350 2450 6600 2450
Wire Wire Line
	6725 3450 6350 3450
Wire Wire Line
	6725 3550 6350 3550
Text Label 6725 3450 2    50   ~ 0
P16
Text Label 6725 3550 2    50   ~ 0
P17
Wire Wire Line
	6725 3750 6350 3750
Wire Wire Line
	6725 3850 6350 3850
Text Label 6725 3750 2    50   ~ 0
P19
Text Label 6725 3850 2    50   ~ 0
P20
Text Label 6725 3350 2    50   ~ 0
P15
Wire Wire Line
	6725 3350 6350 3350
Text HLabel 1100 2475 2    50   Input ~ 0
PB_1_MCU
Text HLabel 1100 2575 2    50   Input ~ 0
PB_2_MCU
Text HLabel 1100 2675 2    50   Input ~ 0
PB_3_MCU
Text HLabel 1100 2775 2    50   Input ~ 0
PB_4_MCU
Text HLabel 1100 2875 2    50   Input ~ 0
PB_5_MCU
Wire Wire Line
	1100 2475 925  2475
Wire Wire Line
	1100 2575 925  2575
Wire Wire Line
	1100 2675 925  2675
Wire Wire Line
	1100 2775 925  2775
Wire Wire Line
	1100 2875 925  2875
Text Label 925  2475 0    50   ~ 0
P15
Text Label 925  2575 0    50   ~ 0
P16
Text Label 925  2675 0    50   ~ 0
P17
Text Label 925  2775 0    50   ~ 0
P19
Text Label 925  2875 0    50   ~ 0
P20
Wire Notes Line
	725  2950 1800 2950
Wire Notes Line
	1800 2950 1800 2225
Wire Notes Line
	1800 2225 725  2225
Wire Notes Line
	725  2225 725  2950
Text Notes 1175 2350 0    50   ~ 0
PB\n
$Comp
L Connector:Conn_01x07_Female J?
U 1 1 5F025ED5
P 2125 5375
AR Path="/5F025ED5" Ref="J?"  Part="1" 
AR Path="/5E9B1DCE/5F025ED5" Ref="J2"  Part="1" 
F 0 "J2" H 2152 5401 50  0000 L CNN
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
AR Path="/5E9B1DCE/5F025EE6" Ref="#PWR05"  Part="1" 
F 0 "#PWR05" H 1825 5475 50  0001 C CNN
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
$Comp
L Device:R R?
U 1 1 5F025EEF
P 1525 4925
AR Path="/5F025EEF" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5F025EEF" Ref="R3"  Part="1" 
F 0 "R3" H 1575 5125 50  0000 L CNN
F 1 "4.7k" H 1575 5025 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1455 4925 50  0001 C CNN
F 3 "~" H 1525 4925 50  0001 C CNN
	1    1525 4925
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F025EF5
P 1275 4925
AR Path="/5F025EF5" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5F025EF5" Ref="R2"  Part="1" 
F 0 "R2" H 1325 5125 50  0000 L CNN
F 1 "4.7k" H 1325 5025 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1205 4925 50  0001 C CNN
F 3 "~" H 1275 4925 50  0001 C CNN
	1    1275 4925
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F025EFB
P 1025 4925
AR Path="/5F025EFB" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5F025EFB" Ref="R1"  Part="1" 
F 0 "R1" H 1075 5125 50  0000 L CNN
F 1 "4.7k" H 1075 5025 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 955 4925 50  0001 C CNN
F 3 "~" H 1025 4925 50  0001 C CNN
	1    1025 4925
	1    0    0    -1  
$EndComp
Wire Wire Line
	975  5175 1025 5175
Wire Wire Line
	975  5275 1275 5275
Wire Wire Line
	975  5375 1525 5375
Wire Wire Line
	1825 4525 1825 5075
Wire Wire Line
	1525 4775 1525 4525
Wire Wire Line
	1525 4525 1450 4525
Wire Wire Line
	1275 4525 1275 4775
Connection ~ 1525 4525
Wire Wire Line
	1275 4525 1025 4525
Wire Wire Line
	1025 4525 1025 4775
Connection ~ 1275 4525
Wire Wire Line
	1025 5075 1025 5175
Connection ~ 1025 5175
Wire Wire Line
	1025 5175 1925 5175
Wire Wire Line
	1275 5075 1275 5275
Connection ~ 1275 5275
Wire Wire Line
	1275 5275 1925 5275
Wire Wire Line
	1525 5075 1525 5375
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
Text Label 6600 4050 0    50   ~ 0
HEART_SDA
Text Label 6600 3950 0    50   ~ 0
HEART_INT
Text Label 6600 4150 0    50   ~ 0
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
	1525 4525 1825 4525
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
Text Label 6700 4750 2    50   ~ 0
DISP_CS
Text Label 6800 4550 2    50   ~ 0
DISP_SCLK
Text Label 6750 4450 2    50   ~ 0
DISP_SDA
Text Label 6825 4850 2    50   ~ 0
DISP_RESET
Text Label 6850 4650 2    50   ~ 0
DISP_FMARK
Text Label 7050 2050 2    50   ~ 0
Backlight_EN_DIM
Wire Wire Line
	6350 2050 7050 2050
Text Label 6725 2950 2    50   ~ 0
MPU_ADO
Text Label 6725 3050 2    50   ~ 0
MPU_INT
Wire Wire Line
	6725 2950 6350 2950
Wire Wire Line
	6350 3050 6725 3050
$Comp
L Sensor_Motion:BNO055 U?
U 1 1 5F46C7F5
P 4525 6550
AR Path="/5F46C7F5" Ref="U?"  Part="1" 
AR Path="/5E9B1DCE/5F46C7F5" Ref="U1"  Part="1" 
F 0 "U1" H 4525 7900 50  0000 C CNN
F 1 "BNO055" H 4525 7800 50  0000 C CNN
F 2 "Housings_LGA:LGA-28_5.2x3.8mm_Pitch0.5mm" H 4775 5900 50  0001 L CNN
F 3 "https://ae-https://datasheet.lcsc.com/szlcsc/Bosch-Sensortec-BNO055_C93216.pdf" H 4525 6750 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Sensors_Bosch-Sensortec_BNO055_Bosch-Sensortec-BNO055_C93216.html" H 4525 6550 50  0001 C CNN "lcsc"
	1    4525 6550
	1    0    0    -1  
$EndComp
Text Notes 5900 6525 0    50   ~ 0
32.768 KHz\n
$Comp
L Device:Crystal_Small X3
U 1 1 5F46C7FD
P 6125 6100
AR Path="/5E9B1DCE/5F46C7FD" Ref="X3"  Part="1" 
AR Path="/5F46C7FD" Ref="X?"  Part="1" 
F 0 "X3" H 6125 6233 50  0000 C CNN
F 1 "Crystal_Small" H 6125 6234 50  0001 C CNN
F 2 "Crystals:Crystal_SMD_2012-2pin_2.0x1.2mm" H 6125 6100 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Seiko-Instruments-SC-20S-32-768kHz-20PPM-7pF_C97602.pdf" H 6125 6100 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/SMD-Crystal-Resonators_Seiko_SC-20S-32-768kHz-20PPM-7pF_Seiko-SC-20S-32-768kHz-20PPM-7pF_C97602.html" H 6125 6100 50  0001 C CNN "lcsc"
	1    6125 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5875 6425 6375 6425
Wire Wire Line
	6375 6400 6375 6425
Wire Wire Line
	5875 6400 5875 6425
$Comp
L Device:C C17
U 1 1 5F46C806
P 5875 6250
AR Path="/5E9B1DCE/5F46C806" Ref="C17"  Part="1" 
AR Path="/5F46C806" Ref="C?"  Part="1" 
F 0 "C17" H 5600 6325 50  0000 L CNN
F 1 "10 pF" H 5575 6200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5913 6100 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CGR82C500NT_C501852.html" H 5875 6250 50  0001 C CNN
	1    5875 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5875 6100 6025 6100
$Comp
L Device:C C18
U 1 1 5F46C80D
P 6375 6250
AR Path="/5E9B1DCE/5F46C80D" Ref="C18"  Part="1" 
AR Path="/5F46C80D" Ref="C?"  Part="1" 
F 0 "C18" H 6490 6296 50  0000 L CNN
F 1 "10 pF" H 6490 6205 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 6413 6100 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_FH-Guangdong-Fenghua-Advanced-Tech-0603CGR82C500NT_C501852.html" H 6375 6250 50  0001 C CNN
	1    6375 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6225 6100 6375 6100
Wire Wire Line
	5125 6050 5875 6050
Wire Wire Line
	5875 6050 5875 6100
Connection ~ 5875 6100
Wire Wire Line
	5125 6550 6775 6550
Wire Wire Line
	6775 6550 6775 6050
Wire Wire Line
	6775 6050 6375 6050
Wire Wire Line
	6375 6050 6375 6100
Connection ~ 6375 6100
Text Label 5375 6050 0    50   ~ 0
Xout32_sens
Text Label 5350 6550 0    50   ~ 0
Xin32_sens
Wire Wire Line
	5125 6950 5275 6950
Text Label 5275 6950 2    50   ~ 0
GND
Wire Wire Line
	5125 6850 5275 6850
Text Label 5275 6850 2    50   ~ 0
GND
$Comp
L Device:C C?
U 1 1 5F46C823
P 5275 7250
AR Path="/5EA4867C/5F46C823" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F46C823" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5F46C823" Ref="C16"  Part="1" 
AR Path="/5F46C823" Ref="C?"  Part="1" 
F 0 "C16" H 5300 7325 50  0000 L CNN
F 1 "100 nF" V 5125 7125 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5313 7100 50  0001 C CNN
F 3 "~" H 5275 7250 50  0001 C CNN
	1    5275 7250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F46C829
P 3750 5675
AR Path="/5EA4867C/5F46C829" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F46C829" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5F46C829" Ref="C13"  Part="1" 
AR Path="/5F46C829" Ref="C?"  Part="1" 
F 0 "C13" H 3775 5750 50  0000 L CNN
F 1 "100 nF" V 3600 5550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 3788 5525 50  0001 C CNN
F 3 "~" H 3750 5675 50  0001 C CNN
	1    3750 5675
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F46C82F
P 4075 5675
AR Path="/5EA4867C/5F46C82F" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F46C82F" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5F46C82F" Ref="C14"  Part="1" 
AR Path="/5F46C82F" Ref="C?"  Part="1" 
F 0 "C14" H 4100 5750 50  0000 L CNN
F 1 "100 nF" V 3925 5550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 4113 5525 50  0001 C CNN
F 3 "~" H 4075 5675 50  0001 C CNN
	1    4075 5675
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 5525 3750 5400
Wire Wire Line
	4625 5400 4625 5850
Wire Wire Line
	4425 7250 4425 7450
Wire Wire Line
	4425 7450 4625 7450
Wire Wire Line
	5125 7050 5275 7050
Wire Wire Line
	5275 7050 5275 7100
Wire Wire Line
	5275 7400 5275 7450
Wire Wire Line
	5275 7450 4625 7450
Connection ~ 4625 7450
Wire Wire Line
	4625 7250 4625 7450
Text Label 3450 7050 0    50   ~ 0
MPU_ADO
Wire Wire Line
	3925 7050 3450 7050
Wire Wire Line
	3550 6250 3925 6250
Text Label 3550 6250 0    50   ~ 0
MPU_INT
$Comp
L Device:R R?
U 1 1 5F46C84B
P 3050 5800
AR Path="/5EA4867C/5F46C84B" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F46C84B" Ref="R?"  Part="1" 
AR Path="/5F46C84B" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5F46C84B" Ref="R6"  Part="1" 
F 0 "R6" H 3120 5846 50  0000 L CNN
F 1 "10k" H 3120 5755 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2980 5800 50  0001 C CNN
F 3 "~" H 3050 5800 50  0001 C CNN
	1    3050 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3325 6050 3325 5950
Wire Wire Line
	3325 6050 3925 6050
$Comp
L Device:R R?
U 1 1 5F46C853
P 3325 5800
AR Path="/5EA4867C/5F46C853" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F46C853" Ref="R?"  Part="1" 
AR Path="/5F46C853" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5F46C853" Ref="R7"  Part="1" 
F 0 "R7" H 3395 5846 50  0000 L CNN
F 1 "10k" H 3395 5755 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 3255 5800 50  0001 C CNN
F 3 "~" H 3325 5800 50  0001 C CNN
	1    3325 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3325 5650 3325 5400
Connection ~ 3325 5400
Wire Wire Line
	3325 5400 3750 5400
Wire Wire Line
	3450 6550 3925 6550
Text Label 3450 6550 0    50   ~ 0
MPU_BL_IND
Text Label 3450 6750 0    50   ~ 0
MPU_SDA
Text Label 3450 6850 0    50   ~ 0
MPU_SCL
Wire Wire Line
	2775 6750 3925 6750
Wire Wire Line
	3050 5650 3050 5400
Wire Wire Line
	3050 5400 3325 5400
Wire Wire Line
	3050 5950 3050 6450
Wire Wire Line
	3050 6450 3925 6450
$Comp
L Device:R R?
U 1 1 5F46C868
P 2500 5800
AR Path="/5EA4867C/5F46C868" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F46C868" Ref="R?"  Part="1" 
AR Path="/5F46C868" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5F46C868" Ref="R4"  Part="1" 
F 0 "R4" H 2570 5846 50  0000 L CNN
F 1 "10k" H 2570 5755 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2430 5800 50  0001 C CNN
F 3 "~" H 2500 5800 50  0001 C CNN
	1    2500 5800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F46C86E
P 2775 5800
AR Path="/5EA4867C/5F46C86E" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F46C86E" Ref="R?"  Part="1" 
AR Path="/5F46C86E" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5F46C86E" Ref="R5"  Part="1" 
F 0 "R5" H 2845 5846 50  0000 L CNN
F 1 "10k" H 2845 5755 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2705 5800 50  0001 C CNN
F 3 "~" H 2775 5800 50  0001 C CNN
	1    2775 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2775 5650 2775 5400
Wire Wire Line
	2500 5650 2500 5400
Connection ~ 3050 5400
Connection ~ 2775 5400
Wire Wire Line
	2775 5400 3050 5400
Wire Wire Line
	2500 5400 2775 5400
Wire Wire Line
	2775 5950 2775 6750
Wire Wire Line
	2500 6850 3925 6850
Wire Notes Line
	4900 5125 4900 5550
Wire Notes Line
	4900 5550 6825 5550
Wire Notes Line
	6825 5550 6825 7700
Wire Notes Line
	6825 7700 2350 7700
Wire Notes Line
	2350 7700 2350 5125
Wire Notes Line
	2350 5125 4900 5125
Text Label 6600 2650 0    50   ~ 0
MPU_SCL
Text Label 6600 2550 0    50   ~ 0
MPU_SDA
Wire Wire Line
	6600 2550 6350 2550
Wire Wire Line
	6350 2650 6600 2650
Wire Wire Line
	6350 3150 6825 3150
Text Label 6825 3150 2    50   ~ 0
MPU_BL_IND
Text Notes 4350 7550 0    50   ~ 0
Gyroscope & Accelerometer & Magnetometer with I2C interface
$Comp
L Connector:TestPoint TP?
U 1 1 5F6067FE
P 7475 4325
AR Path="/5EA4867C/5F6067FE" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5F6067FE" Ref="TP1"  Part="1" 
F 0 "TP1" H 7533 4397 50  0000 L CNN
F 1 "TestPoint" H 7533 4352 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 7675 4325 50  0001 C CNN
F 3 "~" H 7675 4325 50  0001 C CNN
	1    7475 4325
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5F619095
P 7700 4325
AR Path="/5EA4867C/5F619095" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5F619095" Ref="TP2"  Part="1" 
F 0 "TP2" H 7758 4397 50  0000 L CNN
F 1 "TestPoint" H 7758 4352 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 7900 4325 50  0001 C CNN
F 3 "~" H 7900 4325 50  0001 C CNN
	1    7700 4325
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5F62BA5E
P 7925 4325
AR Path="/5EA4867C/5F62BA5E" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5F62BA5E" Ref="TP3"  Part="1" 
F 0 "TP3" H 7983 4397 50  0000 L CNN
F 1 "TestPoint" H 7983 4352 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 8125 4325 50  0001 C CNN
F 3 "~" H 8125 4325 50  0001 C CNN
	1    7925 4325
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5F63E448
P 8150 4325
AR Path="/5EA4867C/5F63E448" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5F63E448" Ref="TP4"  Part="1" 
F 0 "TP4" H 8208 4397 50  0000 L CNN
F 1 "TestPoint" H 8208 4352 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 8350 4325 50  0001 C CNN
F 3 "~" H 8350 4325 50  0001 C CNN
	1    8150 4325
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5F650E32
P 8350 4325
AR Path="/5EA4867C/5F650E32" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5F650E32" Ref="TP5"  Part="1" 
F 0 "TP5" H 8408 4397 50  0000 L CNN
F 1 "TestPoint" H 8408 4352 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 8550 4325 50  0001 C CNN
F 3 "~" H 8550 4325 50  0001 C CNN
	1    8350 4325
	1    0    0    -1  
$EndComp
Wire Wire Line
	7475 4450 7475 4325
Wire Wire Line
	6350 4450 7475 4450
Wire Wire Line
	7700 4550 7700 4325
Wire Wire Line
	6350 4550 7700 4550
Wire Wire Line
	7925 4650 7925 4325
Wire Wire Line
	6350 4650 7925 4650
Wire Wire Line
	8150 4750 8150 4325
Wire Wire Line
	6350 4750 8150 4750
Wire Wire Line
	8350 4850 8350 4325
Wire Wire Line
	6350 4850 8350 4850
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
DISP_FMARK
Wire Wire Line
	9425 4150 10000 4150
Text Label 9600 3650 0    50   ~ 0
LEDK
Text Notes 9600 3300 0    50   ~ 0
Display module without touch panel\n
$Comp
L Connector_Generic:Conn_01x12 J3
U 1 1 5F7CA256
P 10200 4050
F 0 "J3" H 10280 4042 50  0000 L CNN
F 1 "Conn_01x12" H 10280 3951 50  0000 L CNN
F 2 "" H 10200 4050 50  0001 C CNN
F 3 "https://www.buydisplay.com/download/manual/ER-TFT1.28-1_Datasheet.pdf" H 10200 4050 50  0001 C CNN
	1    10200 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8BBF9F
P 9875 4700
AR Path="/5F8BBF9F" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F8BBF9F" Ref="#PWR020"  Part="1" 
F 0 "#PWR020" H 9875 4450 50  0001 C CNN
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
$Comp
L Device:C C?
U 1 1 5FA34E10
P 9225 4075
AR Path="/5EA4867C/5FA34E10" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5FA34E10" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5FA34E10" Ref="C22"  Part="1" 
F 0 "C22" H 9250 4150 50  0000 L CNN
F 1 "1 uF " V 9075 3950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9263 3925 50  0001 C CNN
F 3 "~" H 9225 4075 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R105K160NT_C475249.html" H 9225 4075 50  0001 C CNN "LCSC"
	1    9225 4075
	1    0    0    -1  
$EndComp
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
AR Path="/5E9B1DCE/5FB7DED5" Ref="#PWR07"  Part="1" 
F 0 "#PWR07" H 2075 1100 50  0001 C CNN
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
AR Path="/5E9B1DCE/5FB7E7A0" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 3700 2875 50  0001 C CNN
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
AR Path="/5E9B1DCE/5FC6D69A" Ref="#PWR08"  Part="1" 
F 0 "#PWR08" H 2275 3525 50  0001 C CNN
F 1 "GND" H 2275 3625 50  0000 C CNN
F 2 "" H 2275 3775 50  0001 C CNN
F 3 "" H 2275 3775 50  0001 C CNN
	1    2275 3775
	1    0    0    -1  
$EndComp
Wire Wire Line
	4425 7450 4050 7450
Wire Wire Line
	4050 7450 4050 7475
Connection ~ 4425 7450
$Comp
L power:GND #PWR?
U 1 1 5FC941A8
P 4050 7475
AR Path="/5FC941A8" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FC941A8" Ref="#PWR013"  Part="1" 
F 0 "#PWR013" H 4050 7225 50  0001 C CNN
F 1 "GND" H 4055 7302 50  0000 C CNN
F 2 "" H 4050 7475 50  0001 C CNN
F 3 "" H 4050 7475 50  0001 C CNN
	1    4050 7475
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F9CCFB6
P 7875 5400
AR Path="/5E9C1C3A/5F9CCFB6" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9CCFB6" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9CCFB6" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F9CCFB6" Ref="#PWR018"  Part="1" 
F 0 "#PWR018" H 7875 5250 50  0001 C CNN
F 1 "+3.3V" H 7890 5573 50  0000 C CNN
F 2 "" H 7875 5400 50  0001 C CNN
F 3 "" H 7875 5400 50  0001 C CNN
	1    7875 5400
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
AR Path="/5E9B1DCE/5FA2F8BF" Ref="#PWR023"  Part="1" 
F 0 "#PWR023" H 10500 975 50  0001 C CNN
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
AR Path="/5E9B1DCE/5FA31BF0" Ref="#PWR019"  Part="1" 
F 0 "#PWR019" H 9225 3700 50  0001 C CNN
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
P 3325 5400
AR Path="/5E9C1C3A/5FA32972" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5FA32972" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5FA32972" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FA32972" Ref="#PWR010"  Part="1" 
F 0 "#PWR010" H 3325 5250 50  0001 C CNN
F 1 "+3.3V" H 3340 5573 50  0000 C CNN
F 2 "" H 3325 5400 50  0001 C CNN
F 3 "" H 3325 5400 50  0001 C CNN
	1    3325 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4425 5400 4425 5850
Connection ~ 4425 5400
Wire Wire Line
	4425 5400 4625 5400
Wire Wire Line
	4075 5525 4075 5400
Connection ~ 4075 5400
Wire Wire Line
	4075 5400 4425 5400
Wire Wire Line
	2500 5950 2500 6850
$Comp
L power:GND #PWR?
U 1 1 5FA84810
P 3850 5825
AR Path="/5FA84810" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FA84810" Ref="#PWR012"  Part="1" 
F 0 "#PWR012" H 3850 5575 50  0001 C CNN
F 1 "GND" H 3855 5652 50  0000 C CNN
F 2 "" H 3850 5825 50  0001 C CNN
F 3 "" H 3850 5825 50  0001 C CNN
	1    3850 5825
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 5825 3850 5825
Connection ~ 3850 5825
Wire Wire Line
	3850 5825 4075 5825
Connection ~ 3750 5400
Wire Wire Line
	3750 5400 4075 5400
$Comp
L power:+3.3V #PWR?
U 1 1 5FAACA94
P 5600 1275
AR Path="/5E9C1C3A/5FAACA94" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5FAACA94" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5FAACA94" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FAACA94" Ref="#PWR015"  Part="1" 
F 0 "#PWR015" H 5600 1125 50  0001 C CNN
F 1 "+3.3V" H 5615 1448 50  0000 C CNN
F 2 "" H 5600 1275 50  0001 C CNN
F 3 "" H 5600 1275 50  0001 C CNN
	1    5600 1275
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FAB508B
P 6500 6425
AR Path="/5FAB508B" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FAB508B" Ref="#PWR016"  Part="1" 
F 0 "#PWR016" H 6500 6175 50  0001 C CNN
F 1 "GND" H 6500 6275 50  0000 C CNN
F 2 "" H 6500 6425 50  0001 C CNN
F 3 "" H 6500 6425 50  0001 C CNN
	1    6500 6425
	0    -1   -1   0   
$EndComp
Connection ~ 6375 6425
Wire Wire Line
	6375 6425 6500 6425
$Comp
L power:GND #PWR?
U 1 1 5FADF2C6
P 5450 5175
AR Path="/5FADF2C6" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FADF2C6" Ref="#PWR014"  Part="1" 
F 0 "#PWR014" H 5450 4925 50  0001 C CNN
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
AR Path="/5E9B1DCE/5FAF3706" Ref="#PWR022"  Part="1" 
F 0 "#PWR022" H 10350 6000 50  0001 C CNN
F 1 "GND" H 10350 6100 50  0000 C CNN
F 2 "" H 10350 6250 50  0001 C CNN
F 3 "" H 10350 6250 50  0001 C CNN
	1    10350 6250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FB07C4A
P 7200 3300
AR Path="/5FB07C4A" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FB07C4A" Ref="#PWR017"  Part="1" 
F 0 "#PWR017" H 7200 3050 50  0001 C CNN
F 1 "GND" H 7200 3150 50  0000 C CNN
F 2 "" H 7200 3300 50  0001 C CNN
F 3 "" H 7200 3300 50  0001 C CNN
	1    7200 3300
	1    0    0    -1  
$EndComp
Connection ~ 7200 3300
Wire Wire Line
	7200 3300 7375 3300
$Comp
L power:+3.3V #PWR?
U 1 1 5FB08B0E
P 1450 4525
AR Path="/5E9C1C3A/5FB08B0E" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5FB08B0E" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5FB08B0E" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FB08B0E" Ref="#PWR02"  Part="1" 
F 0 "#PWR02" H 1450 4375 50  0001 C CNN
F 1 "+3.3V" H 1465 4698 50  0000 C CNN
F 2 "" H 1450 4525 50  0001 C CNN
F 3 "" H 1450 4525 50  0001 C CNN
	1    1450 4525
	1    0    0    -1  
$EndComp
Connection ~ 1450 4525
Wire Wire Line
	1450 4525 1275 4525
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
AR Path="/5E9B1DCE/5FC4734F" Ref="#PWR09"  Part="1" 
F 0 "#PWR09" H 2325 825 50  0001 C CNN
F 1 "+3.3V" H 2340 1148 50  0000 C CNN
F 2 "" H 2325 975 50  0001 C CNN
F 3 "" H 2325 975 50  0001 C CNN
	1    2325 975 
	1    0    0    -1  
$EndComp
NoConn ~ 3925 6950
Text Label 6625 4250 0    50   ~ 0
HEART_IRD
Text Label 6625 4350 0    50   ~ 0
HEART_RD
Text HLabel 6600 3250 2    50   Output ~ 0
Enable_motor
Wire Wire Line
	6350 3250 6600 3250
Wire Wire Line
	6625 4250 6350 4250
Wire Wire Line
	6350 4350 6625 4350
$Comp
L Connector:TestPoint TP?
U 1 1 5FD9ED2F
P 675 6575
AR Path="/5EA4867C/5FD9ED2F" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5FD9ED2F" Ref="TP11"  Part="1" 
F 0 "TP11" H 733 6647 50  0000 L CNN
F 1 "TestPoint" H 733 6602 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 875 6575 50  0001 C CNN
F 3 "~" H 875 6575 50  0001 C CNN
	1    675  6575
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5FD9FCBC
P 900 6575
AR Path="/5EA4867C/5FD9FCBC" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5FD9FCBC" Ref="TP12"  Part="1" 
F 0 "TP12" H 958 6647 50  0000 L CNN
F 1 "TestPoint" H 958 6602 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 1100 6575 50  0001 C CNN
F 3 "~" H 1100 6575 50  0001 C CNN
	1    900  6575
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5FDA011E
P 1125 6575
AR Path="/5EA4867C/5FDA011E" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5FDA011E" Ref="TP13"  Part="1" 
F 0 "TP13" H 1183 6647 50  0000 L CNN
F 1 "TestPoint" H 1183 6602 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 1325 6575 50  0001 C CNN
F 3 "~" H 1325 6575 50  0001 C CNN
	1    1125 6575
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5FDA04CF
P 1350 6575
AR Path="/5EA4867C/5FDA04CF" Ref="TP?"  Part="1" 
AR Path="/5E9B1DCE/5FDA04CF" Ref="TP14"  Part="1" 
F 0 "TP14" H 1408 6647 50  0000 L CNN
F 1 "TestPoint" H 1408 6602 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 1550 6575 50  0001 C CNN
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
AR Path="/5E9B1DCE/5FBE7778" Ref="R25"  Part="1" 
F 0 "R25" H 10095 1321 50  0000 L CNN
F 1 "10k" H 10095 1230 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9955 1275 50  0001 C CNN
F 3 "~" H 10025 1275 50  0001 C CNN
	1    10025 1275
	1    0    0    -1  
$EndComp
Connection ~ 10025 1125
Wire Wire Line
	10025 1125 10275 1125
$Comp
L Device:R R?
U 1 1 5FBFA77B
P 10275 1275
AR Path="/5EA4867C/5FBFA77B" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5FBFA77B" Ref="R?"  Part="1" 
AR Path="/5FBFA77B" Ref="R?"  Part="1" 
AR Path="/5E9B1DCE/5FBFA77B" Ref="R26"  Part="1" 
F 0 "R26" H 10345 1321 50  0000 L CNN
F 1 "10k" H 10345 1230 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 10205 1275 50  0001 C CNN
F 3 "~" H 10275 1275 50  0001 C CNN
	1    10275 1275
	1    0    0    -1  
$EndComp
Connection ~ 10275 1125
Wire Wire Line
	10275 1125 10500 1125
Wire Wire Line
	10275 1425 10275 1525
Wire Wire Line
	9950 1525 10275 1525
Wire Wire Line
	10625 1525 10625 1725
Wire Wire Line
	10625 1225 10625 1125
$Comp
L Device:C C?
U 1 1 5ECE6AA9
P 10625 1375
AR Path="/5ECE6AA9" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/5ECE6AA9" Ref="C23"  Part="1" 
F 0 "C23" H 10740 1421 50  0000 L CNN
F 1 "0.1uF" H 10740 1330 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 10663 1225 50  0001 C CNN
F 3 "~" H 10625 1375 50  0001 C CNN
	1    10625 1375
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5ECE6AA2
P 10625 1725
AR Path="/5ECE6AA2" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5ECE6AA2" Ref="#PWR024"  Part="1" 
F 0 "#PWR024" H 10625 1475 50  0001 C CNN
F 1 "GND" H 10630 1552 50  0000 C CNN
F 2 "" H 10625 1725 50  0001 C CNN
F 3 "" H 10625 1725 50  0001 C CNN
	1    10625 1725
	1    0    0    -1  
$EndComp
Wire Wire Line
	10500 1125 10625 1125
Connection ~ 10500 1125
$EndSCHEMATC
