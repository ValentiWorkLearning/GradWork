EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 5
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
L Switch:SW_Push SW6
U 1 1 5ED3FE88
P 4375 2425
F 0 "SW6" H 4375 2710 50  0000 C CNN
F 1 "SW_Push" H 4375 2619 50  0000 C CNN
F 2 "" H 4375 2625 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Omron-Electronics-B3U-3000PM-B_C306884.pdf" H 4375 2625 50  0001 C CNN
F 4 "https://lcsc.com/products/Tactile-Switches_427.html?q=b3u-3000" H 4375 2425 50  0001 C CNN "lcsc"
	1    4375 2425
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW7
U 1 1 5ED42E2A
P 4375 3025
F 0 "SW7" H 4375 3310 50  0000 C CNN
F 1 "SW_Push" H 4375 3219 50  0000 C CNN
F 2 "" H 4375 3225 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Omron-Electronics-B3U-3000PM-B_C306884.pdf" H 4375 3225 50  0001 C CNN
F 4 "https://lcsc.com/products/Tactile-Switches_427.html?q=b3u-3000" H 4375 3025 50  0001 C CNN "lcsc"
	1    4375 3025
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW5
U 1 1 5ED485F9
P 3825 5800
F 0 "SW5" H 3825 6085 50  0000 C CNN
F 1 "SW_Push" H 3825 5994 50  0000 C CNN
F 2 "" H 3825 6000 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Omron-Electronics-B3U-3000PM-B_C306884.pdf" H 3825 6000 50  0001 C CNN
F 4 "https://lcsc.com/products/Tactile-Switches_427.html?q=b3u-3000" H 3825 5800 50  0001 C CNN "lcsc"
	1    3825 5800
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW8
U 1 1 5ED48600
P 4525 5800
F 0 "SW8" H 4525 6085 50  0000 C CNN
F 1 "SW_Push" H 4525 5994 50  0000 C CNN
F 2 "" H 4525 6000 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Omron-Electronics-B3U-3000PM-B_C306884.pdf" H 4525 6000 50  0001 C CNN
F 4 "https://lcsc.com/products/Tactile-Switches_427.html?q=b3u-3000" H 4525 5800 50  0001 C CNN "lcsc"
	1    4525 5800
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW9
U 1 1 5ED498DD
P 5150 5800
F 0 "SW9" H 5150 6085 50  0000 C CNN
F 1 "SW_Push" H 5150 5994 50  0000 C CNN
F 2 "" H 5150 6000 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Omron-Electronics-B3U-3000PM-B_C306884.pdf" H 5150 6000 50  0001 C CNN
F 4 "https://lcsc.com/products/Tactile-Switches_427.html?q=b3u-3000" H 5150 5800 50  0001 C CNN "lcsc"
	1    5150 5800
	0    -1   -1   0   
$EndComp
$Comp
L OnOffControllers:max16054azt+t U6
U 1 1 5ED4F00B
P 5650 2125
F 0 "U6" H 6450 2512 60  0000 C CNN
F 1 "max16054azt+t" H 6450 2406 60  0000 C CNN
F 2 "21-0114C" H 6450 2365 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Maxim-Integrated-MAX16054AZT-T_C79401.pdf" H 5650 2125 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/Interface-Specialized_Maxim-Integrated-MAX16054AZT-T_C79401.html" H 5500 2375 50  0001 C CNN "lcsc"
	1    5650 2125
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5EDEB467
P 5475 2950
AR Path="/5EA4867C/5EDEB467" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EDEB467" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/5EDEB467" Ref="C23"  Part="1" 
F 0 "C23" H 5500 3025 50  0000 L CNN
F 1 "100 nF" V 5325 2825 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5513 2800 50  0001 C CNN
F 3 "~" H 5475 2950 50  0001 C CNN
	1    5475 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 2625 5475 2625
Wire Wire Line
	5475 2625 5475 2800
Wire Wire Line
	5475 3100 5475 3225
Wire Wire Line
	5475 3225 5725 3225
Text Label 5725 3225 2    50   ~ 0
GND
Wire Wire Line
	7250 2625 7500 2625
Text Label 7500 2625 2    50   ~ 0
GND
Wire Wire Line
	4375 2225 5650 2225
Wire Wire Line
	4375 2625 4375 2725
Wire Wire Line
	4375 3225 5475 3225
Connection ~ 5475 3225
$Comp
L MosfetLocal:HX2301A VT2
U 1 1 5EDF815A
P 8600 2125
F 0 "VT2" H 8805 2079 50  0000 L CNN
F 1 "HX2301A" H 8805 2170 50  0000 L CNN
F 2 "" H 8800 2225 50  0001 C CNN
F 3 "~" H 8600 2125 50  0001 C CNN
	1    8600 2125
	1    0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5EDFEF6D
P 8075 1500
AR Path="/5EA4867C/5EDFEF6D" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5EDFEF6D" Ref="R22"  Part="1" 
F 0 "R22" H 8145 1546 50  0000 L CNN
F 1 "10k" H 8145 1455 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 8005 1500 50  0001 C CNN
F 3 "~" H 8075 1500 50  0001 C CNN
	1    8075 1500
	1    0    0    -1  
$EndComp
Text HLabel 5200 2625 0    50   Input ~ 0
V_Battery_P
Text Label 5250 2625 0    50   ~ 0
V_Battery_P
Connection ~ 5475 2625
Wire Wire Line
	5200 2625 5475 2625
Text Label 7550 1325 0    50   ~ 0
V_Battery_P
Wire Wire Line
	8075 1325 8075 1350
Wire Wire Line
	8075 1650 8075 2125
Connection ~ 8075 2125
Wire Wire Line
	8075 2125 8400 2125
Wire Wire Line
	7250 2125 8075 2125
Wire Wire Line
	8075 1325 8700 1325
Wire Wire Line
	8700 1325 8700 1925
Text Label 8950 2450 0    50   ~ 0
V_Battery_EN
Wire Wire Line
	8700 2325 8700 2450
Wire Wire Line
	8700 2450 9475 2450
Text HLabel 9475 2450 2    50   Output ~ 0
V_Battery_EN
Wire Wire Line
	5650 2125 5275 2125
$Comp
L Device:R R?
U 1 1 5EE0DDD9
P 5125 2125
AR Path="/5EA4867C/5EE0DDD9" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5EE0DDD9" Ref="R20"  Part="1" 
F 0 "R20" V 5025 1925 50  0000 L CNN
F 1 "10k" V 5025 2225 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5055 2125 50  0001 C CNN
F 3 "~" H 5125 2125 50  0001 C CNN
	1    5125 2125
	0    1    1    0   
$EndComp
Wire Wire Line
	4975 2125 4725 2125
Text Label 4725 2125 0    50   ~ 0
GND
NoConn ~ 7250 2225
Wire Wire Line
	4375 2725 3675 2725
Wire Wire Line
	3675 2725 3675 1950
Connection ~ 4375 2725
Wire Wire Line
	4375 2725 4375 2825
Wire Wire Line
	4375 2225 4375 1950
Connection ~ 4375 2225
$Comp
L Device:R R?
U 1 1 5EE120DC
P 3675 1800
AR Path="/5EA4867C/5EE120DC" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5EE120DC" Ref="R16"  Part="1" 
F 0 "R16" H 3745 1846 50  0000 L CNN
F 1 "10k" H 3745 1755 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 3605 1800 50  0001 C CNN
F 3 "~" H 3675 1800 50  0001 C CNN
	1    3675 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5EE128AC
P 4375 1800
AR Path="/5EA4867C/5EE128AC" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5EE128AC" Ref="R18"  Part="1" 
F 0 "R18" H 4445 1846 50  0000 L CNN
F 1 "10k" H 4445 1755 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4305 1800 50  0001 C CNN
F 3 "~" H 4375 1800 50  0001 C CNN
	1    4375 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4375 1325 4375 1650
Wire Wire Line
	4375 1325 3675 1325
Wire Wire Line
	3675 1325 3675 1650
Wire Wire Line
	3675 2725 3050 2725
Connection ~ 3675 2725
Wire Wire Line
	4150 2225 4375 2225
Text HLabel 3050 2725 0    50   Output ~ 0
PB_2_MCU
Text HLabel 4150 2225 0    50   Output ~ 0
PB_1_MCU
Wire Wire Line
	7550 1325 8075 1325
Connection ~ 8075 1325
Text Notes 5200 2350 0    50   ~ 0
Int 63KOhm PU\n
Text HLabel 3575 1325 0    50   Input ~ 0
V1V8
Wire Wire Line
	3575 1325 3675 1325
Connection ~ 3675 1325
Text Label 3925 1325 0    50   ~ 0
V1V8
$Comp
L Device:R R?
U 1 1 5EE20738
P 3825 5175
AR Path="/5EA4867C/5EE20738" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5EE20738" Ref="R17"  Part="1" 
F 0 "R17" H 3895 5221 50  0000 L CNN
F 1 "10k" H 3895 5130 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 3755 5175 50  0001 C CNN
F 3 "~" H 3825 5175 50  0001 C CNN
	1    3825 5175
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5EE2073E
P 4525 5175
AR Path="/5EA4867C/5EE2073E" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5EE2073E" Ref="R19"  Part="1" 
F 0 "R19" H 4595 5221 50  0000 L CNN
F 1 "10k" H 4595 5130 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4455 5175 50  0001 C CNN
F 3 "~" H 4525 5175 50  0001 C CNN
	1    4525 5175
	1    0    0    -1  
$EndComp
Wire Wire Line
	4525 4700 4525 5025
Wire Wire Line
	4525 4700 3825 4700
Wire Wire Line
	3825 4700 3825 5025
Text HLabel 3725 4700 0    50   Input ~ 0
V1V8
Wire Wire Line
	3725 4700 3825 4700
Connection ~ 3825 4700
Text Label 4075 4700 0    50   ~ 0
V1V8
$Comp
L Device:R R?
U 1 1 5EE21F41
P 5150 5175
AR Path="/5EA4867C/5EE21F41" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5EE21F41" Ref="R21"  Part="1" 
F 0 "R21" H 5220 5221 50  0000 L CNN
F 1 "10k" H 5220 5130 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5080 5175 50  0001 C CNN
F 3 "~" H 5150 5175 50  0001 C CNN
	1    5150 5175
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 4700 5150 5025
Wire Wire Line
	5150 4700 4525 4700
Connection ~ 4525 4700
Wire Wire Line
	5150 5325 5150 5500
Wire Wire Line
	4525 5325 4525 5500
Wire Wire Line
	3825 6000 3825 6200
Wire Wire Line
	3825 6200 4525 6200
Wire Wire Line
	5150 6200 5150 6000
Wire Wire Line
	4525 6000 4525 6200
Connection ~ 4525 6200
Wire Wire Line
	4525 6200 5150 6200
Text Label 4200 6200 0    50   ~ 0
GND
Wire Wire Line
	3825 5500 3725 5500
Text HLabel 3725 5500 0    50   Output ~ 0
PB_3_MCU
Wire Wire Line
	4525 5500 4425 5500
Text HLabel 4425 5500 0    50   Output ~ 0
PB_4_MCU
Connection ~ 4525 5500
Wire Wire Line
	4525 5500 4525 5600
Wire Wire Line
	5150 5500 5025 5500
Text HLabel 5025 5500 0    50   Output ~ 0
PB_5_MCU
Connection ~ 5150 5500
Wire Wire Line
	5150 5500 5150 5600
Connection ~ 3825 5500
Wire Wire Line
	3825 5500 3825 5600
Wire Wire Line
	3825 5325 3825 5500
Wire Notes Line
	2175 950  2175 3525
Wire Notes Line
	2175 3525 10400 3525
Wire Notes Line
	10400 3525 10400 950 
Wire Notes Line
	10400 950  2175 950 
Text Notes 5825 1225 0    50   ~ 0
ON/OFF with two PB\n\n
Wire Notes Line
	2800 4325 2800 6350
Wire Notes Line
	2800 6350 6075 6350
Wire Notes Line
	6075 6350 6075 4325
Wire Notes Line
	6075 4325 2800 4325
Text Notes 4400 4475 0    50   ~ 0
PB\n
$Comp
L Connector:TestPoint TP?
U 1 1 5EEBF81A
P 7625 2125
AR Path="/5E9C1C3A/5EEBF81A" Ref="TP?"  Part="1" 
AR Path="/5ED3F98E/5EEBF81A" Ref="TP2"  Part="1" 
F 0 "TP2" H 7683 2197 50  0000 L CNN
F 1 "TestPoint" H 7683 2152 50  0001 L CNN
F 2 "testpoints:testpoint" H 7825 2125 50  0001 C CNN
F 3 "~" H 7825 2125 50  0001 C CNN
	1    7625 2125
	1    0    0    -1  
$EndComp
$EndSCHEMATC
