EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
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
L DCDC_Local:TPS62740DSST U?
U 1 1 5F9A3890
P 4000 1875
AR Path="/5E9C1C3A/5F9A3890" Ref="U?"  Part="1" 
AR Path="/5F7F86D0/5F9A3890" Ref="U?"  Part="1" 
AR Path="/5F988DA5/5F9A3890" Ref="U10"  Part="1" 
F 0 "U10" H 4800 2262 60  0000 C CNN
F 1 "TPS62740DSST" H 4800 2125 60  0000 C CNN
F 2 "Housings_SON:WSON-12-1EP_3x2mm_Pitch0.5mm" H 4800 2115 60  0001 C CNN
F 3 "http://www.ti.com/lit/ds/slvsb02b/slvsb02b.pdf" H 4000 1875 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/DC-DC-Converters_Texas-Instruments_TPS62740DSSR_Texas-Instruments-Texas-Instruments-TPS62740DSSR_C128606.html" H 4000 1875 50  0001 C CNN "lcsc"
	1    4000 1875
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F9A3897
P 3400 1950
AR Path="/5EA4867C/5F9A3897" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F9A3897" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/5F9A3897" Ref="C?"  Part="1" 
AR Path="/5F988DA5/5F9A3897" Ref="C30"  Part="1" 
F 0 "C30" H 3425 2025 50  0000 L CNN
F 1 "10 uF" V 3250 1825 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 3438 1800 50  0001 C CNN
F 3 "~" H 3400 1950 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 3400 1950 50  0001 C CNN "LCSC"
	1    3400 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 1775 3900 1775
Wire Wire Line
	3400 1775 3400 1800
Wire Wire Line
	3400 2100 3400 2175
$Comp
L pspice:INDUCTOR L?
U 1 1 5F9A38A1
P 6325 1775
AR Path="/5E9C1C3A/5F9A38A1" Ref="L?"  Part="1" 
AR Path="/5F7F86D0/5F9A38A1" Ref="L?"  Part="1" 
AR Path="/5F988DA5/5F9A38A1" Ref="L1"  Part="1" 
F 0 "L1" H 6325 1900 50  0000 C CNN
F 1 "2.2 uH 13.75 mOHM 1.2 A" H 6275 1700 50  0000 C CNN
F 2 "Inductors_SMD:L_0805_HandSoldering" H 6325 1775 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1908221840_Sunltech-Tech-SLM20162R2MIT_C412023.pdf" H 6325 1775 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Power-Inductors_Sunltech-Tech-SLM20162R2MIT_C412023.html" H 6325 1775 50  0001 C CNN "lcsc"
	1    6325 1775
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 1775 6075 1775
Text Notes 3675 2725 0    50   ~ 0
Vout = 3.3V\n
Text Label 5675 1775 0    50   ~ 0
L_SW_0
Text Label 3850 1775 2    50   ~ 0
V_OUT_MUX
$Comp
L Supervisors:MAX809STRG U?
U 1 1 5F9A38AC
P 2500 2500
AR Path="/5E9C1C3A/5F9A38AC" Ref="U?"  Part="1" 
AR Path="/5F7F86D0/5F9A38AC" Ref="U?"  Part="1" 
AR Path="/5F988DA5/5F9A38AC" Ref="U9"  Part="1" 
F 0 "U9" H 2500 2967 50  0000 C CNN
F 1 "MAX809STRG" H 2500 2876 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 2800 2600 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/ON-Semicon-ON-MAX809STRG_C9965.pdf" H 2800 2600 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Microprocessor-Microcontroller-Supervisors_ON-Semiconductor-ON-Semiconductor-MAX809STRG_C9965.html" H 2500 2500 50  0001 C CNN "lcsc"
	1    2500 2500
	1    0    0    -1  
$EndComp
Text Label 1600 2325 0    50   ~ 0
V_OUT_MUX
Wire Wire Line
	3775 2050 4000 2050
Wire Wire Line
	2800 2500 2900 2500
Wire Wire Line
	3775 2050 3775 2500
Text Label 3075 2500 0    50   ~ 0
DCDC_ENABLE
Text Notes 1800 3000 0    50   ~ 0
V_OUT_MUX always > 1.0 \nRESET Output Guaranteed to VCC = 1.0 V.
Wire Wire Line
	3600 2975 4000 2975
Text Notes 3700 3150 0    50   ~ 0
LOAD(out)\nis disabled
NoConn ~ 5600 2275
Wire Wire Line
	5600 2175 6800 2175
Wire Wire Line
	6800 2175 6800 1775
Connection ~ 6800 1775
Wire Wire Line
	6800 1775 7025 1775
$Comp
L Device:C C?
U 1 1 5F9A38C2
P 7025 1925
AR Path="/5EA4867C/5F9A38C2" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F9A38C2" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/5F9A38C2" Ref="C?"  Part="1" 
AR Path="/5F988DA5/5F9A38C2" Ref="C32"  Part="1" 
F 0 "C32" H 7050 2000 50  0000 L CNN
F 1 "10 uF" V 6875 1800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 7063 1775 50  0001 C CNN
F 3 "~" H 7025 1925 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 7025 1925 50  0001 C CNN "LCSC"
	1    7025 1925
	1    0    0    -1  
$EndComp
Wire Wire Line
	7025 2075 7025 2875
NoConn ~ 5600 2375
Text Notes 5675 2150 0    50   ~ 0
Connect this pin(5) directly \nto the output capacitor\n with a short trace
Text Notes 4300 1450 0    100  ~ 0
DCDC converter 3.3V\n\n
Text HLabel 7100 1775 2    50   Output ~ 0
V3V3
Wire Wire Line
	7100 1775 7025 1775
Connection ~ 7025 1775
$Comp
L Connector:TestPoint TP?
U 1 1 5F9A38D0
P 7025 1650
AR Path="/5EA4867C/5F9A38D0" Ref="TP?"  Part="1" 
AR Path="/5E9C1C3A/5F9A38D0" Ref="TP?"  Part="1" 
AR Path="/5F7F86D0/5F9A38D0" Ref="TP?"  Part="1" 
AR Path="/5F988DA5/5F9A38D0" Ref="TP10"  Part="1" 
F 0 "TP10" H 7083 1722 50  0000 L CNN
F 1 "TestPoint" H 7083 1677 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 7225 1650 50  0001 C CNN
F 3 "~" H 7225 1650 50  0001 C CNN
	1    7025 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7025 1650 7025 1775
$Comp
L Connector:TestPoint TP?
U 1 1 5F9A38D7
P 2900 2500
AR Path="/5EA4867C/5F9A38D7" Ref="TP?"  Part="1" 
AR Path="/5E9C1C3A/5F9A38D7" Ref="TP?"  Part="1" 
AR Path="/5F7F86D0/5F9A38D7" Ref="TP?"  Part="1" 
AR Path="/5F988DA5/5F9A38D7" Ref="TP8"  Part="1" 
F 0 "TP8" H 2958 2572 50  0000 L CNN
F 1 "TestPoint" H 2958 2527 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3100 2500 50  0001 C CNN
F 3 "~" H 3100 2500 50  0001 C CNN
	1    2900 2500
	1    0    0    -1  
$EndComp
Connection ~ 2900 2500
Wire Wire Line
	2900 2500 3775 2500
Wire Notes Line
	1025 1025 1025 3350
Wire Notes Line
	7550 1025 7550 3350
Wire Notes Line
	1025 1025 7550 1025
Wire Notes Line
	1025 3350 7550 3350
Wire Wire Line
	4000 2325 3900 2325
Wire Wire Line
	3900 2325 3900 2425
Wire Wire Line
	3900 2625 4000 2625
Wire Wire Line
	4000 2525 3900 2525
Connection ~ 3900 2525
Wire Wire Line
	3900 2525 3900 2625
Connection ~ 3900 2425
Wire Wire Line
	3900 2425 3900 2525
Wire Wire Line
	3900 2425 4000 2425
Wire Wire Line
	3900 2325 3900 1775
Connection ~ 3900 2325
Connection ~ 3900 1775
Wire Wire Line
	3900 1775 3400 1775
Wire Wire Line
	6575 1775 6800 1775
$Comp
L power:+3.3V #PWR?
U 1 1 5F9A38F1
P 6800 1650
AR Path="/5E9C1C3A/5F9A38F1" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A38F1" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A38F1" Ref="#PWR055"  Part="1" 
F 0 "#PWR055" H 6800 1500 50  0001 C CNN
F 1 "+3.3V" H 6815 1823 50  0000 C CNN
F 2 "" H 6800 1650 50  0001 C CNN
F 3 "" H 6800 1650 50  0001 C CNN
	1    6800 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 1650 6800 1675
Text Notes 2850 2600 0    50   ~ 0
PP output\n
$Comp
L Device:C C?
U 1 1 5F9A38F9
P 2000 2500
AR Path="/5EA4867C/5F9A38F9" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F9A38F9" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/5F9A38F9" Ref="C?"  Part="1" 
AR Path="/5F988DA5/5F9A38F9" Ref="C29"  Part="1" 
F 0 "C29" H 2025 2575 50  0000 L CNN
F 1 "100 nF" V 1875 2325 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2038 2350 50  0001 C CNN
F 3 "~" H 2000 2500 50  0001 C CNN
	1    2000 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2325 2000 2325
Wire Wire Line
	1600 2675 2000 2675
Wire Wire Line
	2000 2325 2000 2350
Connection ~ 2000 2325
Wire Wire Line
	2000 2325 2200 2325
Wire Wire Line
	2000 2650 2000 2675
Connection ~ 2000 2675
Wire Wire Line
	2000 2675 2200 2675
Text Notes 1700 3075 0    50   ~ 0
If V_OUT_MUX below 3.0V than DC/DC is off
$Comp
L Switch:SW_Push SW?
U 1 1 5F9A3909
P 8575 2625
AR Path="/5E9C1C3A/5F9A3909" Ref="SW?"  Part="1" 
AR Path="/5F7F86D0/5F9A3909" Ref="SW?"  Part="1" 
AR Path="/5F988DA5/5F9A3909" Ref="SW3"  Part="1" 
F 0 "SW3" H 8575 2910 50  0000 C CNN
F 1 "SW_Push" H 8575 2819 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_B3U-3000P-B" H 8575 2825 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Omron-Electronics-B3U-3000PM-B_C306884.pdf" H 8575 2825 50  0001 C CNN
F 4 "https://lcsc.com/products/Tactile-Switches_427.html?q=b3u-3000" H 8575 2625 50  0001 C CNN "lcsc"
	1    8575 2625
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5F9A3910
P 9275 2625
AR Path="/5E9C1C3A/5F9A3910" Ref="SW?"  Part="1" 
AR Path="/5F7F86D0/5F9A3910" Ref="SW?"  Part="1" 
AR Path="/5F988DA5/5F9A3910" Ref="SW4"  Part="1" 
F 0 "SW4" H 9275 2910 50  0000 C CNN
F 1 "SW_Push" H 9275 2819 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_B3U-3000P-B" H 9275 2825 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Omron-Electronics-B3U-3000PM-B_C306884.pdf" H 9275 2825 50  0001 C CNN
F 4 "https://lcsc.com/products/Tactile-Switches_427.html?q=b3u-3000" H 9275 2625 50  0001 C CNN "lcsc"
	1    9275 2625
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5F9A3917
P 10000 2625
AR Path="/5E9C1C3A/5F9A3917" Ref="SW?"  Part="1" 
AR Path="/5F7F86D0/5F9A3917" Ref="SW?"  Part="1" 
AR Path="/5F988DA5/5F9A3917" Ref="SW5"  Part="1" 
F 0 "SW5" H 10000 2910 50  0000 C CNN
F 1 "SW_Push" H 10000 2819 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_B3U-3000P-B" H 10000 2825 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Omron-Electronics-B3U-3000PM-B_C306884.pdf" H 10000 2825 50  0001 C CNN
F 4 "https://lcsc.com/products/Tactile-Switches_427.html?q=b3u-3000" H 10000 2625 50  0001 C CNN "lcsc"
	1    10000 2625
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5F9A391D
P 8575 2000
AR Path="/5EA4867C/5F9A391D" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F9A391D" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F9A391D" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F9A391D" Ref="R?"  Part="1" 
AR Path="/5F988DA5/5F9A391D" Ref="R22"  Part="1" 
F 0 "R22" H 8645 2046 50  0000 L CNN
F 1 "10k" H 8645 1955 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 8505 2000 50  0001 C CNN
F 3 "~" H 8575 2000 50  0001 C CNN
	1    8575 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F9A3923
P 9275 2000
AR Path="/5EA4867C/5F9A3923" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F9A3923" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F9A3923" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F9A3923" Ref="R?"  Part="1" 
AR Path="/5F988DA5/5F9A3923" Ref="R23"  Part="1" 
F 0 "R23" H 9345 2046 50  0000 L CNN
F 1 "10k" H 9345 1955 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9205 2000 50  0001 C CNN
F 3 "~" H 9275 2000 50  0001 C CNN
	1    9275 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9275 1525 9275 1850
Wire Wire Line
	9275 1525 8575 1525
Wire Wire Line
	8575 1525 8575 1850
Wire Wire Line
	8475 1525 8575 1525
Connection ~ 8575 1525
$Comp
L Device:R R?
U 1 1 5F9A392E
P 10000 2000
AR Path="/5EA4867C/5F9A392E" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F9A392E" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F9A392E" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F9A392E" Ref="R?"  Part="1" 
AR Path="/5F988DA5/5F9A392E" Ref="R24"  Part="1" 
F 0 "R24" H 10070 2046 50  0000 L CNN
F 1 "10k" H 10070 1955 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9930 2000 50  0001 C CNN
F 3 "~" H 10000 2000 50  0001 C CNN
	1    10000 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 1525 10000 1850
Wire Wire Line
	10000 2150 10000 2325
Wire Wire Line
	9275 2150 9275 2325
Wire Wire Line
	8575 2825 8575 3025
Wire Wire Line
	8575 3025 8675 3025
Wire Wire Line
	10000 3025 10000 2825
Wire Wire Line
	9275 2825 9275 3025
Text Label 8950 3025 0    50   ~ 0
GND
Wire Wire Line
	8575 2325 8475 2325
Text HLabel 8475 2325 0    50   Output ~ 0
PB_3_MCU_N
Wire Wire Line
	9275 2325 9175 2325
Text HLabel 9175 2325 0    50   Output ~ 0
PB_4_MCU_N
Connection ~ 9275 2325
Wire Wire Line
	9275 2325 9275 2425
Wire Wire Line
	10000 2325 9875 2325
Text HLabel 9875 2325 0    50   Output ~ 0
PB_5_MCU_N
Connection ~ 10000 2325
Wire Wire Line
	10000 2325 10000 2425
Connection ~ 8575 2325
Wire Wire Line
	8575 2325 8575 2425
Wire Wire Line
	8575 2150 8575 2325
Text Notes 9150 1300 0    100  ~ 0
PB\n
$Comp
L power:GND #PWR?
U 1 1 5F9A394A
P 8675 3025
AR Path="/5F9A394A" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F9A394A" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F9A394A" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5F9A394A" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A394A" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A394A" Ref="#PWR057"  Part="1" 
F 0 "#PWR057" H 8675 2775 50  0001 C CNN
F 1 "GND" H 8675 2875 50  0000 C CNN
F 2 "" H 8675 3025 50  0001 C CNN
F 3 "" H 8675 3025 50  0001 C CNN
	1    8675 3025
	1    0    0    -1  
$EndComp
Connection ~ 8675 3025
$Comp
L power:+3.3V #PWR?
U 1 1 5F9A3951
P 8475 1525
AR Path="/5E9C1C3A/5F9A3951" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A3951" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A3951" Ref="#PWR056"  Part="1" 
F 0 "#PWR056" H 8475 1375 50  0001 C CNN
F 1 "+3.3V" H 8490 1698 50  0000 C CNN
F 2 "" H 8475 1525 50  0001 C CNN
F 3 "" H 8475 1525 50  0001 C CNN
	1    8475 1525
	1    0    0    -1  
$EndComp
Wire Notes Line
	10475 1075 10475 3300
Wire Notes Line
	10475 3300 7900 3300
Wire Notes Line
	7900 3300 7900 1075
Wire Notes Line
	7900 1075 10475 1075
Wire Wire Line
	9275 1525 10000 1525
Connection ~ 9275 1525
Wire Wire Line
	8675 3025 9275 3025
Connection ~ 9275 3025
Wire Wire Line
	9275 3025 10000 3025
$Comp
L power:GND #PWR?
U 1 1 5F9A3960
P 1600 2675
AR Path="/5F9A3960" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F9A3960" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F9A3960" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5F9A3960" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A3960" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A3960" Ref="#PWR048"  Part="1" 
F 0 "#PWR048" H 1600 2425 50  0001 C CNN
F 1 "GND" H 1600 2525 50  0000 C CNN
F 2 "" H 1600 2675 50  0001 C CNN
F 3 "" H 1600 2675 50  0001 C CNN
	1    1600 2675
	1    0    0    -1  
$EndComp
Text HLabel 1600 2325 0    50   Input ~ 0
DCDC_VIN
$Comp
L power:GND #PWR?
U 1 1 5F9A3967
P 3600 2975
AR Path="/5F9A3967" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F9A3967" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F9A3967" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5F9A3967" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A3967" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A3967" Ref="#PWR050"  Part="1" 
F 0 "#PWR050" H 3600 2725 50  0001 C CNN
F 1 "GND" H 3600 2825 50  0000 C CNN
F 2 "" H 3600 2975 50  0001 C CNN
F 3 "" H 3600 2975 50  0001 C CNN
	1    3600 2975
	1    0    0    -1  
$EndComp
$Comp
L MotorLocal:Motor_DC M?
U 1 1 5F9A3975
P 5950 4725
AR Path="/5EA4867C/5F9A3975" Ref="M?"  Part="1" 
AR Path="/5F7F86D0/5F9A3975" Ref="M?"  Part="1" 
AR Path="/5F988DA5/5F9A3975" Ref="M1"  Part="1" 
F 0 "M1" H 6100 4675 50  0000 L CNN
F 1 "Motor_DC" V 6125 4475 50  0001 L CNN
F 2 "LocalFootprints:VibrationMorot4x4x11" H 5950 4635 50  0001 C CNN
F 3 "https://www.aliexpress.com/item/32844746278.html?spm=a2g0o.productlist.0.0.24ef228a6Cfn5S&algo_pvid=3165a7c1-ba73-4c2c-bb27-6dacea1bed25&algo_expid=3165a7c1-ba73-4c2c-bb27-6dacea1bed25-0&btsid=0b8b15c915866028623212205ec781&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_" H 5950 4635 50  0001 C CNN
	1    5950 4725
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 4525 5950 4400
$Comp
L MosfetLocal:SL2300 VT?
U 1 1 5F9A397D
P 5925 5350
AR Path="/5EA4867C/5F9A397D" Ref="VT?"  Part="1" 
AR Path="/5F7F86D0/5F9A397D" Ref="VT?"  Part="1" 
AR Path="/5F988DA5/5F9A397D" Ref="VT4"  Part="1" 
F 0 "VT4" H 6054 5350 50  0000 L CNN
F 1 "SL2300" H 6055 5305 50  0001 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 5925 5350 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1906271838_SLKORMICRO-Elec-SL2300_C350314.pdf" H 5925 5350 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/MOSFET_Slkor-SLKORMICRO-Elec-SL2300_C350314.html" H 5925 5350 50  0001 C CNN "lcsc"
	1    5925 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 5025 5950 5100
$Comp
L Device:R R?
U 1 1 5F9A3984
P 5650 5675
AR Path="/5EA4867C/5F9A3984" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F9A3984" Ref="R?"  Part="1" 
AR Path="/5F988DA5/5F9A3984" Ref="R21"  Part="1" 
F 0 "R21" H 5720 5721 50  0000 L CNN
F 1 "10k" H 5720 5630 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5580 5675 50  0001 C CNN
F 3 "~" H 5650 5675 50  0001 C CNN
	1    5650 5675
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F9A398A
P 5375 5350
AR Path="/5EA4867C/5F9A398A" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F9A398A" Ref="R?"  Part="1" 
AR Path="/5F988DA5/5F9A398A" Ref="R20"  Part="1" 
F 0 "R20" V 5168 5350 50  0000 C CNN
F 1 "330" V 5259 5350 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5305 5350 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Others_Viking-Tech-ARG03FTC3300_C217969.html" H 5375 5350 50  0001 C CNN
	1    5375 5350
	0    1    1    0   
$EndComp
Wire Wire Line
	5525 5350 5650 5350
Wire Wire Line
	5650 5525 5650 5350
Wire Wire Line
	5650 5900 5800 5900
Wire Wire Line
	5950 5900 5950 5550
Wire Wire Line
	5650 5900 5650 5825
Wire Wire Line
	5225 5350 4850 5350
Text HLabel 4775 5350 0    50   Input ~ 0
Enable_motor
Wire Wire Line
	5500 4800 5725 4800
Wire Wire Line
	5950 4400 4700 4400
$Comp
L Connector:TestPoint TP?
U 1 1 5F9A3999
P 4850 5350
AR Path="/5EA4867C/5F9A3999" Ref="TP?"  Part="1" 
AR Path="/5F7F86D0/5F9A3999" Ref="TP?"  Part="1" 
AR Path="/5F988DA5/5F9A3999" Ref="TP9"  Part="1" 
F 0 "TP9" H 4908 5422 50  0000 L CNN
F 1 "TestPoint" H 4908 5377 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 5050 5350 50  0001 C CNN
F 3 "~" H 5050 5350 50  0001 C CNN
	1    4850 5350
	1    0    0    -1  
$EndComp
Connection ~ 4850 5350
Wire Wire Line
	4850 5350 4775 5350
Text Notes 4975 4350 0    50   ~ 0
Place the capacitor and the diode as close as physically possible
$Comp
L Device:C C?
U 1 1 5F9A39A2
P 6375 4800
AR Path="/5EA4867C/5F9A39A2" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/5F9A39A2" Ref="C?"  Part="1" 
AR Path="/5F988DA5/5F9A39A2" Ref="C31"  Part="1" 
F 0 "C31" H 6490 4846 50  0000 L CNN
F 1 "100n X7R 16V" H 6150 4650 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 6413 4650 50  0001 C CNN
F 3 "~" H 6375 4800 50  0001 C CNN
	1    6375 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:D D?
U 1 1 5F9A39A9
P 6750 4800
AR Path="/5EA4867C/5F9A39A9" Ref="D?"  Part="1" 
AR Path="/5F7F86D0/5F9A39A9" Ref="D?"  Part="1" 
AR Path="/5F988DA5/5F9A39A9" Ref="D2"  Part="1" 
F 0 "D2" V 6704 4879 50  0000 L CNN
F 1 "1A 20V" V 6795 4879 50  0000 L CNN
F 2 "Diodes_SMD:D_SMA_Handsoldering" H 6750 4800 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1901021833_Shandong-Jingdao-Microelectronics-SS12_C353243.pdf" H 6750 4800 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Schottky-Barrier-Diodes-SBD_Shandong-Jingdao-Microelectronics-SS12_C353243.html" V 6750 4800 50  0001 C CNN "lcsc"
	1    6750 4800
	0    1    1    0   
$EndComp
Wire Wire Line
	6375 4650 6375 4400
Wire Wire Line
	6375 4400 5950 4400
Connection ~ 5950 4400
Wire Wire Line
	5950 5100 6375 5100
Wire Wire Line
	6375 5100 6375 4950
Connection ~ 5950 5100
Wire Wire Line
	5950 5100 5950 5150
Wire Wire Line
	6375 4400 6750 4400
Wire Wire Line
	6750 4400 6750 4650
Connection ~ 6375 4400
Wire Wire Line
	6750 4950 6750 5100
Wire Wire Line
	6750 5100 6375 5100
Connection ~ 6375 5100
$Comp
L power:GND #PWR?
U 1 1 5F9A39BC
P 5800 6000
AR Path="/5F9A39BC" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F9A39BC" Ref="#PWR?"  Part="1" 
AR Path="/5EA4867C/5F9A39BC" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A39BC" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A39BC" Ref="#PWR053"  Part="1" 
F 0 "#PWR053" H 5800 5750 50  0001 C CNN
F 1 "GND" H 5800 5850 50  0000 C CNN
F 2 "" H 5800 6000 50  0001 C CNN
F 3 "" H 5800 6000 50  0001 C CNN
	1    5800 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 6000 5800 5900
Connection ~ 5800 5900
Wire Wire Line
	5800 5900 5950 5900
$Comp
L power:GND #PWR?
U 1 1 5F9A39C5
P 5500 4800
AR Path="/5F9A39C5" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F9A39C5" Ref="#PWR?"  Part="1" 
AR Path="/5EA4867C/5F9A39C5" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A39C5" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A39C5" Ref="#PWR052"  Part="1" 
F 0 "#PWR052" H 5500 4550 50  0001 C CNN
F 1 "GND" H 5500 4650 50  0000 C CNN
F 2 "" H 5500 4800 50  0001 C CNN
F 3 "" H 5500 4800 50  0001 C CNN
	1    5500 4800
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F9A39CB
P 4700 4400
AR Path="/5E9C1C3A/5F9A39CB" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A39CB" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A39CB" Ref="#PWR051"  Part="1" 
F 0 "#PWR051" H 4700 4250 50  0001 C CNN
F 1 "+3.3V" H 4715 4573 50  0000 C CNN
F 2 "" H 4700 4400 50  0001 C CNN
F 3 "" H 4700 4400 50  0001 C CNN
	1    4700 4400
	1    0    0    -1  
$EndComp
Wire Notes Line
	3950 4100 7825 4100
Wire Notes Line
	7825 4100 7825 6350
Wire Notes Line
	7825 6350 3950 6350
Wire Notes Line
	3950 6350 3950 4100
$Comp
L power:GND #PWR?
U 1 1 5F9A39D5
P 3400 2175
AR Path="/5F9A39D5" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F9A39D5" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F9A39D5" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5F9A39D5" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A39D5" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A39D5" Ref="#PWR049"  Part="1" 
F 0 "#PWR049" H 3400 1925 50  0001 C CNN
F 1 "GND" H 3400 2025 50  0000 C CNN
F 2 "" H 3400 2175 50  0001 C CNN
F 3 "" H 3400 2175 50  0001 C CNN
	1    3400 2175
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 2775 5700 2775
Wire Wire Line
	5700 2775 5700 2875
Wire Wire Line
	5700 2875 5600 2875
Connection ~ 5700 2875
Wire Wire Line
	5700 2875 6200 2875
$Comp
L power:GND #PWR?
U 1 1 5FC58698
P 6200 2975
AR Path="/5FC58698" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FC58698" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FC58698" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5FC58698" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5FC58698" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5FC58698" Ref="#PWR054"  Part="1" 
F 0 "#PWR054" H 6200 2725 50  0001 C CNN
F 1 "GND" H 6200 2825 50  0000 C CNN
F 2 "" H 6200 2975 50  0001 C CNN
F 3 "" H 6200 2975 50  0001 C CNN
	1    6200 2975
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2975 6200 2875
Connection ~ 6200 2875
Wire Wire Line
	6200 2875 7025 2875
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5FCE6443
P 6575 1450
AR Path="/5F913559/5FCE6443" Ref="#FLG?"  Part="1" 
AR Path="/5F988DA5/5FCE6443" Ref="#FLG03"  Part="1" 
F 0 "#FLG03" H 6575 1525 50  0001 C CNN
F 1 "PWR_FLAG" H 6575 1623 50  0000 C CNN
F 2 "" H 6575 1450 50  0001 C CNN
F 3 "~" H 6575 1450 50  0001 C CNN
	1    6575 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6575 1450 6575 1675
Wire Wire Line
	6575 1675 6800 1675
Connection ~ 6800 1675
Wire Wire Line
	6800 1675 6800 1775
$EndSCHEMATC
