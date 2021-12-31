EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 6
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
L power:+BATT #PWR028
U 1 1 5E9EC7E5
P 4475 4825
F 0 "#PWR028" H 4475 4675 50  0001 C CNN
F 1 "+BATT" H 4490 4998 50  0000 C CNN
F 2 "" H 4475 4825 50  0001 C CNN
F 3 "" H 4475 4825 50  0001 C CNN
	1    4475 4825
	-1   0    0    -1  
$EndComp
Text Label 4325 5025 2    50   ~ 0
V_Battery_P
Wire Wire Line
	3200 5225 3650 5225
$Comp
L BatteryManagmentLocal:BQ21040DBVT U7
U 1 1 5EA1363C
P 1600 5125
F 0 "U7" H 2400 5512 60  0000 C CNN
F 1 "BQ21040DBVT" H 2400 5406 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6" H 2400 5365 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Texas-Instruments-TI-BQ21040DBVR_C202311.pdf" H 2400 5406 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/PMIC-Battery-Management_Texas-Instruments_BQ21040DBVR_Texas-Instruments-Texas-Instruments-BQ21040DBVR_C202311.html" H 1600 5125 50  0001 C CNN "lcsc"
	1    1600 5125
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 4975 1600 5025
Wire Wire Line
	1600 5275 1600 5225
$Comp
L Device:R R?
U 1 1 5E9FD451
P 1375 5425
AR Path="/5EA4867C/5E9FD451" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5E9FD451" Ref="R26"  Part="1" 
F 0 "R26" V 1450 5375 50  0000 L CNN
F 1 "10k" V 1300 5350 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1305 5425 50  0001 C CNN
F 3 "~" H 1375 5425 50  0001 C CNN
	1    1375 5425
	0    1    -1   0   
$EndComp
Wire Wire Line
	1600 5425 1525 5425
Wire Wire Line
	1225 5425 1200 5425
Text Notes 1150 5700 0    50   ~ 0
Set fast charge\ncurrent to 54 mA
NoConn ~ 3200 5425
Wire Wire Line
	1200 5275 1600 5275
Wire Wire Line
	1200 4975 1275 4975
$Comp
L Device:C C?
U 1 1 5E9FB26C
P 1200 5125
AR Path="/5EA4867C/5E9FB26C" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5E9FB26C" Ref="C26"  Part="1" 
F 0 "C26" H 1225 5200 50  0000 L CNN
F 1 "1 uF 16V" H 1225 5025 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1238 4975 50  0001 C CNN
F 3 "~" H 1200 5125 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R105K160NT_C475249.html" H 1200 5125 50  0001 C CNN "LCSC"
	1    1200 5125
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 5525 3650 5600
Wire Wire Line
	4475 4825 4475 5025
Connection ~ 4475 5025
$Comp
L DCDC_Local:TPS62740DSST U11
U 1 1 5EA00C58
P 4075 1675
F 0 "U11" H 4875 2062 60  0000 C CNN
F 1 "TPS62740DSST" H 4875 1925 60  0000 C CNN
F 2 "Housings_SON:WSON-12-1EP_3x2mm_Pitch0.5mm" H 4875 1915 60  0001 C CNN
F 3 "http://www.ti.com/lit/ds/slvsb02b/slvsb02b.pdf" H 4075 1675 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/DC-DC-Converters_Texas-Instruments_TPS62740DSSR_Texas-Instruments-Texas-Instruments-TPS62740DSSR_C128606.html" H 4075 1675 50  0001 C CNN "lcsc"
	1    4075 1675
	1    0    0    -1  
$EndComp
Text Notes 2275 4475 0    100  ~ 0
Battery charger\n
Wire Notes Line
	550  6000 550  4200
$Comp
L Device:C C?
U 1 1 5EA15E96
P 3475 1750
AR Path="/5EA4867C/5EA15E96" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EA15E96" Ref="C28"  Part="1" 
F 0 "C28" H 3500 1825 50  0000 L CNN
F 1 "10 uF" V 3325 1625 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 3513 1600 50  0001 C CNN
F 3 "~" H 3475 1750 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 3475 1750 50  0001 C CNN "LCSC"
	1    3475 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4075 1575 3975 1575
Wire Wire Line
	3475 1575 3475 1600
Wire Wire Line
	3475 1900 3475 2050
Wire Wire Line
	3475 2050 3250 2050
Text Label 3250 2050 0    50   ~ 0
GND
$Comp
L pspice:INDUCTOR L3
U 1 1 5EA18A55
P 6400 1575
F 0 "L3" H 6400 1700 50  0000 C CNN
F 1 "2.2 uH 13.75 mOHM 1.2 A" H 6350 1500 50  0000 C CNN
F 2 "" H 6400 1575 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1908221840_Sunltech-Tech-SLM20162R2MIT_C412023.pdf" H 6400 1575 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Power-Inductors_Sunltech-Tech-SLM20162R2MIT_C412023.html" H 6400 1575 50  0001 C CNN "lcsc"
	1    6400 1575
	1    0    0    -1  
$EndComp
Wire Wire Line
	5675 1575 6150 1575
Text Notes 3750 2525 0    50   ~ 0
Vout = 3.3V\n
Text Label 5750 1575 0    50   ~ 0
L_SW_0
Text Label 3925 1575 2    50   ~ 0
V_OUT_MUX
$Comp
L Supervisors:MAX809STRG U10
U 1 1 5EA21C4A
P 2575 2300
F 0 "U10" H 2575 2767 50  0000 C CNN
F 1 "MAX809STRG" H 2575 2676 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2875 2400 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/ON-Semicon-ON-MAX809STRG_C9965.pdf" H 2875 2400 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Microprocessor-Microcontroller-Supervisors_ON-Semiconductor-ON-Semiconductor-MAX809STRG_C9965.html" H 2575 2300 50  0001 C CNN "lcsc"
	1    2575 2300
	1    0    0    -1  
$EndComp
Text Label 1675 2125 0    50   ~ 0
V_OUT_MUX
Wire Wire Line
	3850 1850 4075 1850
Wire Wire Line
	2875 2300 2975 2300
Wire Wire Line
	3850 1850 3850 2300
Text Label 3150 2300 0    50   ~ 0
DCDC_ENABLE
Text Notes 1875 2800 0    50   ~ 0
V_OUT_MUX always > 1.0 \nRESET Output Guaranteed to VCC = 1.0 V.
Wire Wire Line
	5675 2575 5675 2675
Connection ~ 5675 2675
Wire Wire Line
	3675 2775 4075 2775
Text Notes 3775 2950 0    50   ~ 0
LOAD(out)\nis disabled
NoConn ~ 5675 2075
Wire Wire Line
	5675 1975 6875 1975
Wire Wire Line
	6875 1975 6875 1575
Connection ~ 6875 1575
Wire Wire Line
	6875 1575 7100 1575
$Comp
L Device:C C?
U 1 1 5EA4839B
P 7100 1725
AR Path="/5EA4867C/5EA4839B" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EA4839B" Ref="C30"  Part="1" 
F 0 "C30" H 7125 1800 50  0000 L CNN
F 1 "10 uF" V 6950 1600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 7138 1575 50  0001 C CNN
F 3 "~" H 7100 1725 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 7100 1725 50  0001 C CNN "LCSC"
	1    7100 1725
	1    0    0    -1  
$EndComp
Wire Wire Line
	5675 2675 5900 2675
Wire Wire Line
	7100 1875 7100 2675
NoConn ~ 5675 2175
Text Notes 5750 1950 0    50   ~ 0
Connect this pin(5) directly \nto the output capacitor\n with a short trace
$Comp
L BatteryManagmentLocal:STC3100IQT U9
U 1 1 5EA36940
P 8375 5075
F 0 "U9" H 8375 5490 50  0000 C CNN
F 1 "STC3100IQT" H 8375 5375 50  0000 C CNN
F 2 "Housings_DFN_QFN:DFN-8-1EP_3x3mm_Pitch0.5mm" H 8500 5850 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1804172029_STMicroelectronics-STC3100IQT_C155587.pdf" H 8375 5075 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/_STMicroelectronics_STC3100IQT_STC3100IQT_C155587.html" H 8750 5700 50  0001 C CNN "lcsc"
	1    8375 5075
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E9F16F1
P 3650 5375
AR Path="/5EA4867C/5E9F16F1" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5E9F16F1" Ref="R28"  Part="1" 
F 0 "R28" H 3425 5350 50  0000 L CNN
F 1 "10k" V 3725 5300 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 3580 5375 50  0001 C CNN
F 3 "~" H 3650 5375 50  0001 C CNN
	1    3650 5375
	1    0    0    1   
$EndComp
Text Label 4450 5275 0    50   ~ 0
V_Battery_N
Wire Wire Line
	7825 5125 7300 5125
Wire Wire Line
	7300 5125 7300 5400
Wire Wire Line
	7675 5225 7675 5875
Wire Wire Line
	7300 5700 7300 5875
Text Notes 7700 6175 2    50   ~ 0
GND (pin 5) should be directly \nconnected to negedge resistor\npin that is connected to GND plane 
$Comp
L Device:C C?
U 1 1 5EA50EBE
P 6875 5575
AR Path="/5EA4867C/5EA50EBE" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EA50EBE" Ref="C27"  Part="1" 
F 0 "C27" H 6900 5650 50  0000 L CNN
F 1 "1 uF 16V" V 6725 5450 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 6913 5425 50  0001 C CNN
F 3 "~" H 6875 5575 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R105K160NT_C475249.html" H 6875 5575 50  0001 C CNN "LCSC"
	1    6875 5575
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7825 4925 6875 4925
Wire Wire Line
	6875 4925 6875 5425
Wire Wire Line
	6875 5725 6875 5875
Connection ~ 7300 5875
Wire Wire Line
	6875 5875 7300 5875
NoConn ~ 8925 4925
$Comp
L Device:R R?
U 1 1 5EA5E00D
P 9875 4875
AR Path="/5EA4867C/5EA5E00D" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5EA5E00D" Ref="R24"  Part="1" 
F 0 "R24" H 9925 4725 50  0000 L CNN
F 1 "10k" V 9800 4800 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9805 4875 50  0001 C CNN
F 3 "~" H 9875 4875 50  0001 C CNN
	1    9875 4875
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5EA5F2E9
P 9625 4875
AR Path="/5EA4867C/5EA5F2E9" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5EA5F2E9" Ref="R25"  Part="1" 
F 0 "R25" H 9650 4725 50  0000 L CNN
F 1 "10k" V 9550 4800 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9555 4875 50  0001 C CNN
F 3 "~" H 9625 4875 50  0001 C CNN
	1    9625 4875
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5EA5F7B3
P 9200 5025
AR Path="/5EA4867C/5EA5F7B3" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5EA5F7B3" Ref="R27"  Part="1" 
F 0 "R27" V 9025 4975 50  0000 L CNN
F 1 "200k 0.1%" V 9100 4825 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9130 5025 50  0001 C CNN
F 3 "~" H 9200 5025 50  0001 C CNN
	1    9200 5025
	0    1    1    0   
$EndComp
Wire Wire Line
	9050 5025 8925 5025
Wire Wire Line
	9350 5025 9500 5025
Wire Wire Line
	9625 5025 9625 5125
Wire Wire Line
	9625 5125 8925 5125
Wire Wire Line
	9875 5025 9875 5225
Wire Wire Line
	9875 5225 8925 5225
Wire Wire Line
	9875 4725 9875 4625
Wire Wire Line
	9875 4625 9750 4625
Wire Wire Line
	9625 4625 9625 4725
Wire Wire Line
	7675 5875 7300 5875
Wire Wire Line
	7675 5225 7825 5225
Text Notes 8625 5550 2    50   ~ 0
9 pin directly \nto plan GND\n
Text Notes 8450 4475 2    100  ~ 0
Fuel gauge
Wire Notes Line
	5900 4200 5900 6475
Text Notes 4375 1250 0    100  ~ 0
DCDC converter 1.8V\n\n
Text HLabel 7175 1575 2    50   Output ~ 0
V3V3
Wire Wire Line
	7175 1575 7100 1575
Connection ~ 7100 1575
$Comp
L Connector:TestPoint TP?
U 1 1 5EAC8917
P 7100 1450
AR Path="/5EA4867C/5EAC8917" Ref="TP?"  Part="1" 
AR Path="/5E9C1C3A/5EAC8917" Ref="TP6"  Part="1" 
F 0 "TP6" H 7158 1522 50  0000 L CNN
F 1 "TestPoint" H 7158 1477 50  0001 L CNN
F 2 "testpoints:testpoint" H 7300 1450 50  0001 C CNN
F 3 "~" H 7300 1450 50  0001 C CNN
	1    7100 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 1450 7100 1575
$Comp
L Connector:TestPoint TP?
U 1 1 5EACCAB9
P 2975 2300
AR Path="/5EA4867C/5EACCAB9" Ref="TP?"  Part="1" 
AR Path="/5E9C1C3A/5EACCAB9" Ref="TP5"  Part="1" 
F 0 "TP5" H 3033 2372 50  0000 L CNN
F 1 "TestPoint" H 3033 2327 50  0001 L CNN
F 2 "testpoints:testpoint" H 3175 2300 50  0001 C CNN
F 3 "~" H 3175 2300 50  0001 C CNN
	1    2975 2300
	1    0    0    -1  
$EndComp
Connection ~ 2975 2300
Wire Wire Line
	2975 2300 3850 2300
Text Label 1375 4975 0    50   ~ 0
V_USB
Wire Notes Line
	1100 825  1100 3150
Wire Notes Line
	7625 825  7625 3150
Wire Notes Line
	1100 825  7625 825 
Wire Notes Line
	1100 3150 7625 3150
Wire Wire Line
	4075 2125 3975 2125
Wire Wire Line
	3975 2125 3975 2225
Wire Wire Line
	3975 2425 4075 2425
Wire Wire Line
	4075 2325 3975 2325
Connection ~ 3975 2325
Wire Wire Line
	3975 2325 3975 2425
Connection ~ 3975 2225
Wire Wire Line
	3975 2225 3975 2325
Wire Wire Line
	3975 2225 4075 2225
Wire Wire Line
	3975 2125 3975 1575
Connection ~ 3975 2125
Connection ~ 3975 1575
Wire Wire Line
	3975 1575 3475 1575
Wire Wire Line
	6650 1575 6875 1575
$Comp
L power:+3.3V #PWR?
U 1 1 5FAEEF72
P 6875 1450
F 0 "#PWR?" H 6875 1300 50  0001 C CNN
F 1 "+3.3V" H 6890 1623 50  0000 C CNN
F 2 "" H 6875 1450 50  0001 C CNN
F 3 "" H 6875 1450 50  0001 C CNN
	1    6875 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6875 1450 6875 1575
Text Notes 2925 2400 0    50   ~ 0
PP output\n
$Comp
L Device:C C?
U 1 1 5FAF7A75
P 2075 2300
AR Path="/5EA4867C/5FAF7A75" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5FAF7A75" Ref="C?"  Part="1" 
F 0 "C?" H 2100 2375 50  0000 L CNN
F 1 "100 nF" V 1950 2125 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2113 2150 50  0001 C CNN
F 3 "~" H 2075 2300 50  0001 C CNN
	1    2075 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1675 2125 2075 2125
Wire Wire Line
	1675 2475 2075 2475
Wire Wire Line
	2075 2125 2075 2150
Connection ~ 2075 2125
Wire Wire Line
	2075 2125 2275 2125
Wire Wire Line
	2075 2450 2075 2475
Connection ~ 2075 2475
Wire Wire Line
	2075 2475 2275 2475
Text Notes 1775 2875 0    50   ~ 0
If V_OUT_MUX below 3.0V than DC/DC is off
Wire Notes Line
	5225 4200 5225 6000
Wire Notes Line
	550  6000 5225 6000
Wire Notes Line
	550  4200 5225 4200
$Comp
L power:+3.3V #PWR?
U 1 1 5FB373C5
P 9750 4500
F 0 "#PWR?" H 9750 4350 50  0001 C CNN
F 1 "+3.3V" H 9765 4673 50  0000 C CNN
F 2 "" H 9750 4500 50  0001 C CNN
F 3 "" H 9750 4500 50  0001 C CNN
	1    9750 4500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9750 4500 9750 4625
Connection ~ 9750 4625
Wire Wire Line
	9750 4625 9625 4625
$Comp
L Device:R R?
U 1 1 5FB3C59D
P 7300 5550
AR Path="/5EA4867C/5FB3C59D" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5FB3C59D" Ref="R?"  Part="1" 
F 0 "R?" H 7375 5500 50  0000 L CNN
F 1 "0.15 Ohm" V 7200 5375 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 7230 5550 50  0001 C CNN
F 3 "~" H 7300 5550 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Chip-Resistor-Surface-Mount_UNI-ROYAL-Uniroyal-Elec-0603WAF150LT5E_C45879.html" V 7300 5550 50  0001 C CNN "lcsc"
	1    7300 5550
	-1   0    0    1   
$EndComp
Wire Wire Line
	4950 5125 7300 5125
Connection ~ 7300 5125
Text Label 9900 5125 0    50   ~ 0
SDA_FG
Text Label 9900 5225 0    50   ~ 0
SCL_FG
Wire Wire Line
	9625 5125 10175 5125
Connection ~ 9625 5125
Wire Wire Line
	9875 5225 10175 5225
Connection ~ 9875 5225
Wire Notes Line
	5900 4200 10825 4200
Wire Notes Line
	5900 6475 10825 6475
Wire Notes Line
	10825 4200 10825 6475
Text HLabel 10175 5125 2    50   BiDi ~ 0
SDA_FG
Text HLabel 10175 5225 2    50   Input ~ 0
SCL_FG
Wire Wire Line
	4950 5125 4950 5275
Wire Wire Line
	3200 5025 4475 5025
$Comp
L power:+5V #PWR?
U 1 1 5FD39B85
P 1275 4975
F 0 "#PWR?" H 1275 4825 50  0001 C CNN
F 1 "+5V" H 1290 5148 50  0000 C CNN
F 2 "" H 1275 4975 50  0001 C CNN
F 3 "" H 1275 4975 50  0001 C CNN
	1    1275 4975
	1    0    0    -1  
$EndComp
Connection ~ 1275 4975
Wire Wire Line
	1275 4975 1600 4975
$Comp
L Switch:SW_Push SW?
U 1 1 5FDD967A
P 8650 2425
F 0 "SW?" H 8650 2710 50  0000 C CNN
F 1 "SW_Push" H 8650 2619 50  0000 C CNN
F 2 "" H 8650 2625 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Omron-Electronics-B3U-3000PM-B_C306884.pdf" H 8650 2625 50  0001 C CNN
F 4 "https://lcsc.com/products/Tactile-Switches_427.html?q=b3u-3000" H 8650 2425 50  0001 C CNN "lcsc"
	1    8650 2425
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5FDD9681
P 9350 2425
F 0 "SW?" H 9350 2710 50  0000 C CNN
F 1 "SW_Push" H 9350 2619 50  0000 C CNN
F 2 "" H 9350 2625 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Omron-Electronics-B3U-3000PM-B_C306884.pdf" H 9350 2625 50  0001 C CNN
F 4 "https://lcsc.com/products/Tactile-Switches_427.html?q=b3u-3000" H 9350 2425 50  0001 C CNN "lcsc"
	1    9350 2425
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5FDD9688
P 10075 2425
F 0 "SW?" H 10075 2710 50  0000 C CNN
F 1 "SW_Push" H 10075 2619 50  0000 C CNN
F 2 "" H 10075 2625 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Omron-Electronics-B3U-3000PM-B_C306884.pdf" H 10075 2625 50  0001 C CNN
F 4 "https://lcsc.com/products/Tactile-Switches_427.html?q=b3u-3000" H 10075 2425 50  0001 C CNN "lcsc"
	1    10075 2425
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5FDD968E
P 8650 1800
AR Path="/5EA4867C/5FDD968E" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5FDD968E" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5FDD968E" Ref="R?"  Part="1" 
F 0 "R?" H 8720 1846 50  0000 L CNN
F 1 "10k" H 8720 1755 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 8580 1800 50  0001 C CNN
F 3 "~" H 8650 1800 50  0001 C CNN
	1    8650 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5FDD9694
P 9350 1800
AR Path="/5EA4867C/5FDD9694" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5FDD9694" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5FDD9694" Ref="R?"  Part="1" 
F 0 "R?" H 9420 1846 50  0000 L CNN
F 1 "10k" H 9420 1755 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9280 1800 50  0001 C CNN
F 3 "~" H 9350 1800 50  0001 C CNN
	1    9350 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 1325 9350 1650
Wire Wire Line
	9350 1325 8650 1325
Wire Wire Line
	8650 1325 8650 1650
Wire Wire Line
	8550 1325 8650 1325
Connection ~ 8650 1325
$Comp
L Device:R R?
U 1 1 5FDD969F
P 10075 1800
AR Path="/5EA4867C/5FDD969F" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5FDD969F" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5FDD969F" Ref="R?"  Part="1" 
F 0 "R?" H 10145 1846 50  0000 L CNN
F 1 "10k" H 10145 1755 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 10005 1800 50  0001 C CNN
F 3 "~" H 10075 1800 50  0001 C CNN
	1    10075 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	10075 1325 10075 1650
Wire Wire Line
	10075 1950 10075 2125
Wire Wire Line
	9350 1950 9350 2125
Wire Wire Line
	8650 2625 8650 2825
Wire Wire Line
	8650 2825 8750 2825
Wire Wire Line
	10075 2825 10075 2625
Wire Wire Line
	9350 2625 9350 2825
Text Label 9025 2825 0    50   ~ 0
GND
Wire Wire Line
	8650 2125 8550 2125
Text HLabel 8550 2125 0    50   Output ~ 0
PB_3_MCU_N
Wire Wire Line
	9350 2125 9250 2125
Text HLabel 9250 2125 0    50   Output ~ 0
PB_4_MCU_N
Connection ~ 9350 2125
Wire Wire Line
	9350 2125 9350 2225
Wire Wire Line
	10075 2125 9950 2125
Text HLabel 9950 2125 0    50   Output ~ 0
PB_5_MCU_N
Connection ~ 10075 2125
Wire Wire Line
	10075 2125 10075 2225
Connection ~ 8650 2125
Wire Wire Line
	8650 2125 8650 2225
Wire Wire Line
	8650 1950 8650 2125
Text Notes 9225 1100 0    50   ~ 0
PB\n
$Comp
L power:GND #PWR?
U 1 1 5FDD96C0
P 8750 2825
AR Path="/5FDD96C0" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FDD96C0" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FDD96C0" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5FDD96C0" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 8750 2575 50  0001 C CNN
F 1 "GND" H 8750 2675 50  0000 C CNN
F 2 "" H 8750 2825 50  0001 C CNN
F 3 "" H 8750 2825 50  0001 C CNN
	1    8750 2825
	1    0    0    -1  
$EndComp
Connection ~ 8750 2825
$Comp
L power:+3.3V #PWR?
U 1 1 5FDDC176
P 8550 1325
F 0 "#PWR?" H 8550 1175 50  0001 C CNN
F 1 "+3.3V" H 8565 1498 50  0000 C CNN
F 2 "" H 8550 1325 50  0001 C CNN
F 3 "" H 8550 1325 50  0001 C CNN
	1    8550 1325
	1    0    0    -1  
$EndComp
Wire Notes Line
	10550 875  10550 3100
Wire Notes Line
	10550 3100 7975 3100
Wire Notes Line
	7975 3100 7975 875 
Wire Notes Line
	7975 875  10550 875 
Wire Wire Line
	9350 1325 10075 1325
Connection ~ 9350 1325
Wire Wire Line
	8750 2825 9350 2825
Connection ~ 9350 2825
Wire Wire Line
	9350 2825 10075 2825
Wire Wire Line
	4475 5025 7825 5025
Text HLabel 4375 5200 0    50   Input ~ 0
V_Battery_P
Wire Wire Line
	4375 5200 4475 5200
Wire Wire Line
	4475 5200 4475 5025
Text HLabel 4375 5275 0    50   Input ~ 0
V_Battery_N
$Comp
L power:GND #PWR?
U 1 1 5FE05C98
P 1000 5425
AR Path="/5FE05C98" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FE05C98" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FE05C98" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5FE05C98" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1000 5175 50  0001 C CNN
F 1 "GND" H 1000 5275 50  0000 C CNN
F 2 "" H 1000 5425 50  0001 C CNN
F 3 "" H 1000 5425 50  0001 C CNN
	1    1000 5425
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FE06757
P 3650 5600
AR Path="/5FE06757" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FE06757" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FE06757" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5FE06757" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3650 5350 50  0001 C CNN
F 1 "GND" H 3650 5450 50  0000 C CNN
F 2 "" H 3650 5600 50  0001 C CNN
F 3 "" H 3650 5600 50  0001 C CNN
	1    3650 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 5275 1200 5425
Connection ~ 1200 5275
Connection ~ 1200 5425
Wire Wire Line
	1200 5425 1000 5425
Wire Wire Line
	4375 5275 4950 5275
$Comp
L power:GND #PWR?
U 1 1 5FE12A7E
P 7825 5875
AR Path="/5FE12A7E" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FE12A7E" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FE12A7E" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5FE12A7E" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7825 5625 50  0001 C CNN
F 1 "GND" H 7825 5725 50  0000 C CNN
F 2 "" H 7825 5875 50  0001 C CNN
F 3 "" H 7825 5875 50  0001 C CNN
	1    7825 5875
	1    0    0    -1  
$EndComp
Connection ~ 7675 5875
Wire Wire Line
	7825 5300 7825 5875
Connection ~ 7825 5875
Wire Wire Line
	7675 5875 7825 5875
Wire Wire Line
	9500 5025 9500 5875
$Comp
L power:GND #PWR?
U 1 1 5FE1F2A7
P 9500 5875
AR Path="/5FE1F2A7" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FE1F2A7" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FE1F2A7" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5FE1F2A7" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 9500 5625 50  0001 C CNN
F 1 "GND" H 9500 5725 50  0000 C CNN
F 2 "" H 9500 5875 50  0001 C CNN
F 3 "" H 9500 5875 50  0001 C CNN
	1    9500 5875
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FE2581C
P 1675 2475
AR Path="/5FE2581C" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FE2581C" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FE2581C" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5FE2581C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1675 2225 50  0001 C CNN
F 1 "GND" H 1675 2325 50  0000 C CNN
F 2 "" H 1675 2475 50  0001 C CNN
F 3 "" H 1675 2475 50  0001 C CNN
	1    1675 2475
	1    0    0    -1  
$EndComp
Text HLabel 1675 2125 0    50   Input ~ 0
V_OUT_MUX
$Comp
L power:GND #PWR?
U 1 1 5FE3FD26
P 3675 2775
AR Path="/5FE3FD26" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FE3FD26" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FE3FD26" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5FE3FD26" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3675 2525 50  0001 C CNN
F 1 "GND" H 3675 2625 50  0000 C CNN
F 2 "" H 3675 2775 50  0001 C CNN
F 3 "" H 3675 2775 50  0001 C CNN
	1    3675 2775
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FE402E6
P 5900 2675
AR Path="/5FE402E6" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FE402E6" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FE402E6" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5FE402E6" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5900 2425 50  0001 C CNN
F 1 "GND" H 5900 2525 50  0000 C CNN
F 2 "" H 5900 2675 50  0001 C CNN
F 3 "" H 5900 2675 50  0001 C CNN
	1    5900 2675
	1    0    0    -1  
$EndComp
Connection ~ 5900 2675
Wire Wire Line
	5900 2675 7100 2675
Wire Wire Line
	1200 4975 1100 4975
Connection ~ 1200 4975
Text HLabel 1100 4975 0    50   Input ~ 0
V_USB
$EndSCHEMATC
