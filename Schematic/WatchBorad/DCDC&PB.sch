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
L Device:C C?
U 1 1 5F9A3897
P 3400 1950
AR Path="/5EA4867C/5F9A3897" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F9A3897" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/5F9A3897" Ref="C?"  Part="1" 
AR Path="/5F988DA5/5F9A3897" Ref="C33"  Part="1" 
F 0 "C33" H 3425 2025 50  0000 L CNN
F 1 "10 uF" V 3250 1825 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3438 1800 50  0001 C CNN
F 3 "~" H 3400 1950 50  0001 C CNN
F 4 "" H 3400 1950 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 3400 1950 50  0001 C CNN "lcsc"
	1    3400 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 1775 3400 1800
Wire Wire Line
	3400 2100 3400 2175
$Comp
L pspice:INDUCTOR L?
U 1 1 5F9A38A1
P 4800 1425
AR Path="/5E9C1C3A/5F9A38A1" Ref="L?"  Part="1" 
AR Path="/5F7F86D0/5F9A38A1" Ref="L?"  Part="1" 
AR Path="/5F988DA5/5F9A38A1" Ref="L1"  Part="1" 
F 0 "L1" H 4800 1550 50  0000 C CNN
F 1 "2.2 uH 13.75 mOHM 1.2 A" H 4750 1350 50  0000 C CNN
F 2 "Inductors_SMD:L_0805_HandSoldering" H 4800 1425 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1908221840_Sunltech-Tech-SLM20162R2MIT_C412023.pdf" H 4800 1425 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Power-Inductors_Sunltech-Tech-SLM20162R2MIT_C412023.html" H 4800 1425 50  0001 C CNN "lcsc"
	1    4800 1425
	1    0    0    -1  
$EndComp
Text Label 4200 1675 0    50   ~ 0
L_SW_1
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
F 1 "MAX809S" H 2500 2876 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 2800 2600 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1901021830_Youtai-Semiconductor-Co-Ltd-MAX809S_C347371.pdf" H 2800 2600 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Microprocessor-Microcontroller-Supervisors_UMW-Youtai-Semiconductor-Co-Ltd-MAX809S_C347371.html" H 2500 2500 50  0001 C CNN "lcsc"
	1    2500 2500
	1    0    0    -1  
$EndComp
Text Label 1600 2325 0    50   ~ 0
V_OUT_MUX
Wire Wire Line
	2800 2500 2900 2500
Text Label 3175 2500 0    50   ~ 0
DCDC_ENABLE
Text Notes 1800 3000 0    50   ~ 0
V_OUT_MUX always > 1.0 \nRESET Output Guaranteed to VCC = 1.0 V.
Connection ~ 7675 1775
Wire Wire Line
	7675 1775 7900 1775
$Comp
L Device:C C?
U 1 1 5F9A38C2
P 7900 1925
AR Path="/5EA4867C/5F9A38C2" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F9A38C2" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/5F9A38C2" Ref="C?"  Part="1" 
AR Path="/5F988DA5/5F9A38C2" Ref="C35"  Part="1" 
F 0 "C35" H 8050 1975 50  0000 L CNN
F 1 "10 uF" H 8025 1900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7938 1775 50  0001 C CNN
F 3 "~" H 7900 1925 50  0001 C CNN
F 4 "" H 7900 1925 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 7900 1925 50  0001 C CNN "lcsc"
	1    7900 1925
	1    0    0    -1  
$EndComp
Text Notes 4025 1325 0    100  ~ 0
DCDC converter 3.3V\n\n
Text HLabel 7975 1775 2    50   Output ~ 0
V3V3
Wire Wire Line
	7975 1775 7900 1775
Connection ~ 7900 1775
$Comp
L Connector:TestPoint TP?
U 1 1 5F9A38D0
P 7900 1650
AR Path="/5EA4867C/5F9A38D0" Ref="TP?"  Part="1" 
AR Path="/5E9C1C3A/5F9A38D0" Ref="TP?"  Part="1" 
AR Path="/5F7F86D0/5F9A38D0" Ref="TP?"  Part="1" 
AR Path="/5F988DA5/5F9A38D0" Ref="TP15"  Part="1" 
F 0 "TP15" H 7958 1722 50  0000 L CNN
F 1 "TestPoint" H 7958 1677 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 8100 1650 50  0001 C CNN
F 3 "~" H 8100 1650 50  0001 C CNN
	1    7900 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 1650 7900 1775
$Comp
L Connector:TestPoint TP?
U 1 1 5F9A38D7
P 2900 2500
AR Path="/5EA4867C/5F9A38D7" Ref="TP?"  Part="1" 
AR Path="/5E9C1C3A/5F9A38D7" Ref="TP?"  Part="1" 
AR Path="/5F7F86D0/5F9A38D7" Ref="TP?"  Part="1" 
AR Path="/5F988DA5/5F9A38D7" Ref="TP14"  Part="1" 
F 0 "TP14" H 2958 2572 50  0000 L CNN
F 1 "TestPoint" H 2958 2527 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 3100 2500 50  0001 C CNN
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
	9100 1025 9100 3350
Wire Notes Line
	1025 1025 9100 1025
Wire Notes Line
	1025 3350 9100 3350
Wire Wire Line
	7450 1775 7675 1775
$Comp
L power:+3.3V #PWR?
U 1 1 5F9A38F1
P 7675 1650
AR Path="/5E9C1C3A/5F9A38F1" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A38F1" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A38F1" Ref="#PWR053"  Part="1" 
F 0 "#PWR053" H 7675 1500 50  0001 C CNN
F 1 "+3.3V" H 7690 1823 50  0000 C CNN
F 2 "" H 7675 1650 50  0001 C CNN
F 3 "" H 7675 1650 50  0001 C CNN
	1    7675 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7675 1650 7675 1675
Text Notes 2850 2600 0    50   ~ 0
PP output\n
$Comp
L Device:C C?
U 1 1 5F9A38F9
P 2000 2500
AR Path="/5EA4867C/5F9A38F9" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F9A38F9" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/5F9A38F9" Ref="C?"  Part="1" 
AR Path="/5F988DA5/5F9A38F9" Ref="C32"  Part="1" 
F 0 "C32" H 2025 2575 50  0000 L CNN
F 1 "100 nF" V 1875 2325 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2038 2350 50  0001 C CNN
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
If V_OUT_MUX below 2.93V than DC/DC is off
$Comp
L Switch:SW_Push SW?
U 1 1 5F9A3909
P 7975 4775
AR Path="/5E9C1C3A/5F9A3909" Ref="SW?"  Part="1" 
AR Path="/5F7F86D0/5F9A3909" Ref="SW?"  Part="1" 
AR Path="/5F988DA5/5F9A3909" Ref="SW3"  Part="1" 
F 0 "SW3" H 7975 5060 50  0000 C CNN
F 1 "SW_Push" H 7975 4969 50  0000 C CNN
F 2 "OmronSwitch:SW_B3U-3000P" H 7975 4975 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/2012042009_Omron-Electronics-B3U-3000P_C963349.pdf" H 7975 4975 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Tactile-Switches_Omron-Electronics-B3U-3000P_C963349.html" H 7975 4775 50  0001 C CNN "lcsc"
	1    7975 4775
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5F9A3910
P 8675 4775
AR Path="/5E9C1C3A/5F9A3910" Ref="SW?"  Part="1" 
AR Path="/5F7F86D0/5F9A3910" Ref="SW?"  Part="1" 
AR Path="/5F988DA5/5F9A3910" Ref="SW4"  Part="1" 
F 0 "SW4" H 8675 5060 50  0000 C CNN
F 1 "SW_Push" H 8675 4969 50  0000 C CNN
F 2 "OmronSwitch:SW_B3U-3000P" H 8675 4975 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/2012042009_Omron-Electronics-B3U-3000P_C963349.pdf" H 8675 4975 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Tactile-Switches_Omron-Electronics-B3U-3000P_C963349.html" H 8675 4775 50  0001 C CNN "lcsc"
	1    8675 4775
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5F9A3917
P 9400 4775
AR Path="/5E9C1C3A/5F9A3917" Ref="SW?"  Part="1" 
AR Path="/5F7F86D0/5F9A3917" Ref="SW?"  Part="1" 
AR Path="/5F988DA5/5F9A3917" Ref="SW5"  Part="1" 
F 0 "SW5" H 9400 5060 50  0000 C CNN
F 1 "SW_Push" H 9400 4969 50  0000 C CNN
F 2 "OmronSwitch:SW_B3U-3000P" H 9400 4975 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/2012042009_Omron-Electronics-B3U-3000P_C963349.pdf" H 9400 4975 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Tactile-Switches_Omron-Electronics-B3U-3000P_C963349.html" H 9400 4775 50  0001 C CNN "lcsc"
	1    9400 4775
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5F9A391D
P 7975 5500
AR Path="/5EA4867C/5F9A391D" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F9A391D" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F9A391D" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F9A391D" Ref="R?"  Part="1" 
AR Path="/5F988DA5/5F9A391D" Ref="R31"  Part="1" 
F 0 "R31" H 8045 5546 50  0000 L CNN
F 1 "10k" H 8045 5455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7905 5500 50  0001 C CNN
F 3 "~" H 7975 5500 50  0001 C CNN
	1    7975 5500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F9A3923
P 8675 5500
AR Path="/5EA4867C/5F9A3923" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F9A3923" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F9A3923" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F9A3923" Ref="R?"  Part="1" 
AR Path="/5F988DA5/5F9A3923" Ref="R32"  Part="1" 
F 0 "R32" H 8745 5546 50  0000 L CNN
F 1 "10k" H 8745 5455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8605 5500 50  0001 C CNN
F 3 "~" H 8675 5500 50  0001 C CNN
	1    8675 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8675 4350 8675 4575
Wire Wire Line
	8675 4350 7975 4350
Wire Wire Line
	7975 4350 7975 4575
Wire Wire Line
	7875 4350 7975 4350
Connection ~ 7975 4350
$Comp
L Device:R R?
U 1 1 5F9A392E
P 9400 5500
AR Path="/5EA4867C/5F9A392E" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F9A392E" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F9A392E" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F9A392E" Ref="R?"  Part="1" 
AR Path="/5F988DA5/5F9A392E" Ref="R33"  Part="1" 
F 0 "R33" H 9470 5546 50  0000 L CNN
F 1 "10k" H 9470 5455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9330 5500 50  0001 C CNN
F 3 "~" H 9400 5500 50  0001 C CNN
	1    9400 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 4350 9400 4575
Wire Wire Line
	7975 5650 7975 5850
Wire Wire Line
	9400 5850 9400 5650
Wire Wire Line
	8675 5650 8675 5850
Text HLabel 6675 5050 0    50   Output ~ 0
PB_3_MCU_N
Text HLabel 6675 5150 0    50   Output ~ 0
PB_4_MCU_N
Text Notes 8550 4125 0    100  ~ 0
PB\n
$Comp
L power:GND #PWR?
U 1 1 5F9A394A
P 8675 5850
AR Path="/5F9A394A" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F9A394A" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F9A394A" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5F9A394A" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A394A" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A394A" Ref="#PWR055"  Part="1" 
F 0 "#PWR055" H 8675 5600 50  0001 C CNN
F 1 "GND" H 8675 5700 50  0000 C CNN
F 2 "" H 8675 5850 50  0001 C CNN
F 3 "" H 8675 5850 50  0001 C CNN
	1    8675 5850
	1    0    0    -1  
$EndComp
Connection ~ 8675 5850
$Comp
L power:+3.3V #PWR?
U 1 1 5F9A3951
P 7875 4350
AR Path="/5E9C1C3A/5F9A3951" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A3951" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A3951" Ref="#PWR054"  Part="1" 
F 0 "#PWR054" H 7875 4200 50  0001 C CNN
F 1 "+3.3V" H 7890 4523 50  0000 C CNN
F 2 "" H 7875 4350 50  0001 C CNN
F 3 "" H 7875 4350 50  0001 C CNN
	1    7875 4350
	1    0    0    -1  
$EndComp
Wire Notes Line
	9875 3900 9875 6125
Wire Notes Line
	9875 6150 6000 6150
Wire Notes Line
	6000 6150 6000 3925
Wire Notes Line
	6000 3925 9875 3900
Wire Wire Line
	8675 4350 9400 4350
Connection ~ 8675 4350
Wire Wire Line
	8675 5850 9150 5850
$Comp
L power:GND #PWR?
U 1 1 5F9A3960
P 1600 2675
AR Path="/5F9A3960" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F9A3960" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F9A3960" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5F9A3960" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A3960" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A3960" Ref="#PWR046"  Part="1" 
F 0 "#PWR046" H 1600 2425 50  0001 C CNN
F 1 "GND" H 1600 2525 50  0000 C CNN
F 2 "" H 1600 2675 50  0001 C CNN
F 3 "" H 1600 2675 50  0001 C CNN
	1    1600 2675
	1    0    0    -1  
$EndComp
Text HLabel 1600 2325 0    50   Input ~ 0
DCDC_VIN
$Comp
L MotorLocal:Motor_DC M?
U 1 1 5F9A3975
P 2975 4550
AR Path="/5EA4867C/5F9A3975" Ref="M?"  Part="1" 
AR Path="/5F7F86D0/5F9A3975" Ref="M?"  Part="1" 
AR Path="/5F988DA5/5F9A3975" Ref="M1"  Part="1" 
F 0 "M1" H 3125 4500 50  0000 L CNN
F 1 "Motor_DC" V 3150 4300 50  0001 L CNN
F 2 "LocalFootprints:VibrationMorot4x4x11" H 2975 4460 50  0001 C CNN
F 3 "https://www.aliexpress.com/item/32844746278.html?spm=a2g0o.productlist.0.0.24ef228a6Cfn5S&algo_pvid=3165a7c1-ba73-4c2c-bb27-6dacea1bed25&algo_expid=3165a7c1-ba73-4c2c-bb27-6dacea1bed25-0&btsid=0b8b15c915866028623212205ec781&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_" H 2975 4460 50  0001 C CNN
	1    2975 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2975 4350 2975 4225
$Comp
L MosfetLocal:SL2300 VT?
U 1 1 5F9A397D
P 2950 5175
AR Path="/5EA4867C/5F9A397D" Ref="VT?"  Part="1" 
AR Path="/5F7F86D0/5F9A397D" Ref="VT?"  Part="1" 
AR Path="/5F988DA5/5F9A397D" Ref="VT4"  Part="1" 
F 0 "VT4" H 3079 5175 50  0000 L CNN
F 1 "SL2300" H 3080 5130 50  0001 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 2950 5175 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1906271838_SLKORMICRO-Elec-SL2300_C350314.pdf" H 2950 5175 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/MOSFET_Slkor-SLKORMICRO-Elec-SL2300_C350314.html" H 2950 5175 50  0001 C CNN "lcsc"
	1    2950 5175
	1    0    0    -1  
$EndComp
Wire Wire Line
	2975 4850 2975 4925
$Comp
L Device:R R?
U 1 1 5F9A3984
P 2675 5500
AR Path="/5EA4867C/5F9A3984" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F9A3984" Ref="R?"  Part="1" 
AR Path="/5F988DA5/5F9A3984" Ref="R27"  Part="1" 
F 0 "R27" H 2745 5546 50  0000 L CNN
F 1 "10k" H 2745 5455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2605 5500 50  0001 C CNN
F 3 "~" H 2675 5500 50  0001 C CNN
	1    2675 5500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F9A398A
P 2400 5175
AR Path="/5EA4867C/5F9A398A" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F9A398A" Ref="R?"  Part="1" 
AR Path="/5F988DA5/5F9A398A" Ref="R26"  Part="1" 
F 0 "R26" V 2193 5175 50  0000 C CNN
F 1 "330" V 2284 5175 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2330 5175 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Others_Viking-Tech-ARG03FTC3300_C217969.html" H 2400 5175 50  0001 C CNN
	1    2400 5175
	0    1    1    0   
$EndComp
Wire Wire Line
	2550 5175 2675 5175
Wire Wire Line
	2675 5350 2675 5175
Wire Wire Line
	2675 5725 2825 5725
Wire Wire Line
	2975 5725 2975 5375
Wire Wire Line
	2675 5725 2675 5650
Wire Wire Line
	2250 5175 1875 5175
Text HLabel 1800 5175 0    50   Input ~ 0
Enable_motor
Wire Wire Line
	2525 4625 2750 4625
Wire Wire Line
	2975 4225 1725 4225
$Comp
L Connector:TestPoint TP?
U 1 1 5F9A3999
P 1875 5175
AR Path="/5EA4867C/5F9A3999" Ref="TP?"  Part="1" 
AR Path="/5F7F86D0/5F9A3999" Ref="TP?"  Part="1" 
AR Path="/5F988DA5/5F9A3999" Ref="TP13"  Part="1" 
F 0 "TP13" H 1933 5247 50  0000 L CNN
F 1 "TestPoint" H 1933 5202 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 2075 5175 50  0001 C CNN
F 3 "~" H 2075 5175 50  0001 C CNN
	1    1875 5175
	1    0    0    -1  
$EndComp
Connection ~ 1875 5175
Wire Wire Line
	1875 5175 1800 5175
Text Notes 2000 4175 0    50   ~ 0
Place the capacitor and the diode as close as physically possible
$Comp
L Device:C C?
U 1 1 5F9A39A2
P 3400 4625
AR Path="/5EA4867C/5F9A39A2" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/5F9A39A2" Ref="C?"  Part="1" 
AR Path="/5F988DA5/5F9A39A2" Ref="C34"  Part="1" 
F 0 "C34" H 3515 4671 50  0000 L CNN
F 1 "100n X7R 16V" H 3175 4475 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3438 4475 50  0001 C CNN
F 3 "~" H 3400 4625 50  0001 C CNN
	1    3400 4625
	1    0    0    -1  
$EndComp
$Comp
L Device:D D?
U 1 1 5F9A39A9
P 3775 4625
AR Path="/5EA4867C/5F9A39A9" Ref="D?"  Part="1" 
AR Path="/5F7F86D0/5F9A39A9" Ref="D?"  Part="1" 
AR Path="/5F988DA5/5F9A39A9" Ref="D2"  Part="1" 
F 0 "D2" V 3729 4704 50  0000 L CNN
F 1 "1A 20V" V 3820 4704 50  0000 L CNN
F 2 "Diodes_SMD:D_SMA_Handsoldering" H 3775 4625 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/2004140934_Slkor-SLKORMICRO-Elec-SS12_C513476.pdf" H 3775 4625 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Schottky-Barrier-Diodes-SBD_Slkor-SLKORMICRO-Elec-SS12_C513476.html" V 3775 4625 50  0001 C CNN "lcsc"
	1    3775 4625
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 4475 3400 4225
Wire Wire Line
	3400 4225 2975 4225
Connection ~ 2975 4225
Wire Wire Line
	2975 4925 3400 4925
Wire Wire Line
	3400 4925 3400 4775
Connection ~ 2975 4925
Wire Wire Line
	2975 4925 2975 4975
Wire Wire Line
	3400 4225 3775 4225
Wire Wire Line
	3775 4225 3775 4475
Connection ~ 3400 4225
Wire Wire Line
	3775 4775 3775 4925
Wire Wire Line
	3775 4925 3400 4925
Connection ~ 3400 4925
$Comp
L power:GND #PWR?
U 1 1 5F9A39BC
P 2825 5825
AR Path="/5F9A39BC" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F9A39BC" Ref="#PWR?"  Part="1" 
AR Path="/5EA4867C/5F9A39BC" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A39BC" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A39BC" Ref="#PWR049"  Part="1" 
F 0 "#PWR049" H 2825 5575 50  0001 C CNN
F 1 "GND" H 2825 5675 50  0000 C CNN
F 2 "" H 2825 5825 50  0001 C CNN
F 3 "" H 2825 5825 50  0001 C CNN
	1    2825 5825
	1    0    0    -1  
$EndComp
Wire Wire Line
	2825 5825 2825 5725
Connection ~ 2825 5725
Wire Wire Line
	2825 5725 2975 5725
$Comp
L power:GND #PWR?
U 1 1 5F9A39C5
P 2525 4625
AR Path="/5F9A39C5" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F9A39C5" Ref="#PWR?"  Part="1" 
AR Path="/5EA4867C/5F9A39C5" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A39C5" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A39C5" Ref="#PWR048"  Part="1" 
F 0 "#PWR048" H 2525 4375 50  0001 C CNN
F 1 "GND" H 2525 4475 50  0000 C CNN
F 2 "" H 2525 4625 50  0001 C CNN
F 3 "" H 2525 4625 50  0001 C CNN
	1    2525 4625
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F9A39CB
P 1725 4225
AR Path="/5E9C1C3A/5F9A39CB" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A39CB" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A39CB" Ref="#PWR047"  Part="1" 
F 0 "#PWR047" H 1725 4075 50  0001 C CNN
F 1 "+3.3V" H 1740 4398 50  0000 C CNN
F 2 "" H 1725 4225 50  0001 C CNN
F 3 "" H 1725 4225 50  0001 C CNN
	1    1725 4225
	1    0    0    -1  
$EndComp
Wire Notes Line
	975  3925 4850 3925
Wire Notes Line
	4850 3925 4850 6175
Wire Notes Line
	4850 6175 975  6175
Wire Notes Line
	975  6175 975  3925
$Comp
L power:GND #PWR?
U 1 1 5F9A39D5
P 3400 2175
AR Path="/5F9A39D5" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F9A39D5" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F9A39D5" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5F9A39D5" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A39D5" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A39D5" Ref="#PWR050"  Part="1" 
F 0 "#PWR050" H 3400 1925 50  0001 C CNN
F 1 "GND" H 3400 2025 50  0000 C CNN
F 2 "" H 3400 2175 50  0001 C CNN
F 3 "" H 3400 2175 50  0001 C CNN
	1    3400 2175
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FC58698
P 6225 3075
AR Path="/5FC58698" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FC58698" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FC58698" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5FC58698" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5FC58698" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5FC58698" Ref="#PWR052"  Part="1" 
F 0 "#PWR052" H 6225 2825 50  0001 C CNN
F 1 "GND" H 6225 2925 50  0000 C CNN
F 2 "" H 6225 3075 50  0001 C CNN
F 3 "" H 6225 3075 50  0001 C CNN
	1    6225 3075
	1    0    0    -1  
$EndComp
Wire Wire Line
	6225 3075 6225 2975
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5FCE6443
P 7325 1650
AR Path="/5F913559/5FCE6443" Ref="#FLG?"  Part="1" 
AR Path="/5F988DA5/5FCE6443" Ref="#FLG04"  Part="1" 
F 0 "#FLG04" H 7325 1725 50  0001 C CNN
F 1 "PWR_FLAG" H 7325 1823 50  0000 C CNN
F 2 "" H 7325 1650 50  0001 C CNN
F 3 "~" H 7325 1650 50  0001 C CNN
	1    7325 1650
	1    0    0    -1  
$EndComp
Connection ~ 7675 1675
Wire Wire Line
	7675 1675 7675 1775
Connection ~ 2675 5175
Text HLabel 6675 5250 0    50   Output ~ 0
PB_5_MCU_N
Wire Wire Line
	8675 4975 8675 5150
Wire Wire Line
	9400 4975 9400 5250
$Comp
L Device:R R?
U 1 1 601F6C7F
P 7100 5050
AR Path="/5EA4867C/601F6C7F" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/601F6C7F" Ref="R?"  Part="1" 
AR Path="/5F988DA5/601F6C7F" Ref="R28"  Part="1" 
F 0 "R28" V 7050 4800 50  0000 C CNN
F 1 "330" V 7050 5350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7030 5050 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Others_Viking-Tech-ARG03FTC3300_C217969.html" H 7100 5050 50  0001 C CNN
	1    7100 5050
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 601F97CB
P 7100 5150
AR Path="/5EA4867C/601F97CB" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/601F97CB" Ref="R?"  Part="1" 
AR Path="/5F988DA5/601F97CB" Ref="R29"  Part="1" 
F 0 "R29" V 7050 4900 50  0000 C CNN
F 1 "330" V 7050 5450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7030 5150 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Others_Viking-Tech-ARG03FTC3300_C217969.html" H 7100 5150 50  0001 C CNN
	1    7100 5150
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 601F9B6C
P 7100 5250
AR Path="/5EA4867C/601F9B6C" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/601F9B6C" Ref="R?"  Part="1" 
AR Path="/5F988DA5/601F9B6C" Ref="R30"  Part="1" 
F 0 "R30" V 7050 5000 50  0000 C CNN
F 1 "330" V 7050 5550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7030 5250 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Others_Viking-Tech-ARG03FTC3300_C217969.html" H 7100 5250 50  0001 C CNN
	1    7100 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	7975 4975 7975 5050
Wire Wire Line
	7250 5050 7725 5050
Connection ~ 7975 5050
Wire Wire Line
	7975 5050 7975 5350
Wire Wire Line
	7250 5150 8425 5150
Connection ~ 8675 5150
Wire Wire Line
	8675 5150 8675 5350
Connection ~ 9400 5250
Wire Wire Line
	9400 5250 9400 5350
Wire Wire Line
	6950 5250 6675 5250
Wire Wire Line
	6675 5150 6950 5150
Wire Wire Line
	6950 5050 6675 5050
$Comp
L Device:C C?
U 1 1 60210246
P 7725 5500
AR Path="/5EA4867C/60210246" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/60210246" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/60210246" Ref="C?"  Part="1" 
AR Path="/5F988DA5/60210246" Ref="C36"  Part="1" 
F 0 "C36" H 7750 5575 50  0000 L CNN
F 1 "100 nF" V 7600 5325 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7763 5350 50  0001 C CNN
F 3 "~" H 7725 5500 50  0001 C CNN
	1    7725 5500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60210B3B
P 8425 5500
AR Path="/5EA4867C/60210B3B" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/60210B3B" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/60210B3B" Ref="C?"  Part="1" 
AR Path="/5F988DA5/60210B3B" Ref="C37"  Part="1" 
F 0 "C37" H 8450 5575 50  0000 L CNN
F 1 "100 nF" V 8300 5325 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8463 5350 50  0001 C CNN
F 3 "~" H 8425 5500 50  0001 C CNN
	1    8425 5500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60210F0B
P 9150 5500
AR Path="/5EA4867C/60210F0B" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/60210F0B" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/60210F0B" Ref="C?"  Part="1" 
AR Path="/5F988DA5/60210F0B" Ref="C38"  Part="1" 
F 0 "C38" H 9175 5575 50  0000 L CNN
F 1 "100 nF" V 9025 5325 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9188 5350 50  0001 C CNN
F 3 "~" H 9150 5500 50  0001 C CNN
	1    9150 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 5650 9150 5850
Connection ~ 9150 5850
Wire Wire Line
	9150 5850 9400 5850
Wire Wire Line
	9150 5250 9150 5350
Connection ~ 9150 5250
Wire Wire Line
	9150 5250 9400 5250
Wire Wire Line
	8425 5650 8425 5850
Connection ~ 8425 5850
Wire Wire Line
	8425 5850 8675 5850
Wire Wire Line
	7250 5250 9150 5250
Wire Wire Line
	8425 5350 8425 5150
Connection ~ 8425 5150
Wire Wire Line
	8425 5150 8675 5150
Wire Wire Line
	7725 5350 7725 5050
Connection ~ 7725 5050
Wire Wire Line
	7725 5050 7975 5050
Wire Wire Line
	7725 5650 7725 5850
Wire Wire Line
	7725 5850 7975 5850
Connection ~ 7975 5850
Wire Wire Line
	7975 5850 8425 5850
$Comp
L WatchBorad-rescue:LTC3533-DCDC_Local U?
U 1 1 61909063
P 4775 2275
AR Path="/61909063" Ref="U?"  Part="1" 
AR Path="/5F988DA5/61909063" Ref="U12"  Part="1" 
F 0 "U12" H 4775 2825 50  0000 C CNN
F 1 "LTC3533" H 4775 2300 50  0000 C CNN
F 2 "Package_DFN_QFN:DFN-14-1EP_3x4mm_P0.5mm_EP1.7x3.3mm" H 4775 2375 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1912111437_Analog-Devices-LTC3533EDE-TRPBF_C461524.pdf" H 4775 2375 50  0001 C CNN
	1    4775 2275
	1    0    0    -1  
$EndComp
Wire Wire Line
	4625 2875 4625 2975
Wire Wire Line
	4625 2975 4725 2975
Wire Wire Line
	4725 2875 4725 2975
Connection ~ 4725 2975
Wire Wire Line
	4725 2975 4825 2975
Wire Wire Line
	4825 2875 4825 2975
Connection ~ 4825 2975
Wire Wire Line
	4825 2975 4925 2975
Wire Wire Line
	4925 2875 4925 2975
Connection ~ 4925 2975
Wire Wire Line
	4550 1425 4175 1425
Wire Wire Line
	4175 1425 4175 1675
Wire Wire Line
	4175 1675 4575 1675
Wire Wire Line
	5050 1425 5400 1425
Wire Wire Line
	5400 1425 5400 1675
Wire Wire Line
	5400 1675 4975 1675
$Comp
L Device:R R?
U 1 1 6191DAA1
P 4150 2750
AR Path="/5EA4867C/6191DAA1" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/6191DAA1" Ref="R?"  Part="1" 
AR Path="/5F988DA5/6191DAA1" Ref="R3"  Part="1" 
F 0 "R3" H 4220 2796 50  0000 L CNN
F 1 "33.2k" H 4220 2705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4080 2750 50  0001 C CNN
F 3 "~" H 4150 2750 50  0001 C CNN
	1    4150 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4625 2975 4150 2975
Wire Wire Line
	4150 2975 4150 2900
Connection ~ 4625 2975
Wire Wire Line
	4150 2600 4150 2475
Wire Wire Line
	4150 2475 4275 2475
Wire Wire Line
	3400 1775 4000 1775
Text Notes 7500 1400 0    50   ~ 0
Vout = 3.3V\n
Wire Wire Line
	3775 2500 3775 2375
Wire Wire Line
	3775 2375 4275 2375
Wire Wire Line
	4000 1775 4000 2075
Wire Wire Line
	4000 2075 4275 2075
Wire Wire Line
	4275 2175 4000 2175
Wire Wire Line
	4000 2175 4000 2075
Connection ~ 4000 2075
$Comp
L Device:R R?
U 1 1 6193FCF4
P 5400 2725
AR Path="/5EA4867C/6193FCF4" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/6193FCF4" Ref="R?"  Part="1" 
AR Path="/5F988DA5/6193FCF4" Ref="R19"  Part="1" 
F 0 "R19" H 5470 2771 50  0000 L CNN
F 1 "200k" H 5470 2680 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5330 2725 50  0001 C CNN
F 3 "~" H 5400 2725 50  0001 C CNN
	1    5400 2725
	1    0    0    -1  
$EndComp
Wire Wire Line
	4925 2975 5400 2975
Wire Wire Line
	7900 2075 7900 2150
$Comp
L Device:C C?
U 1 1 619482E5
P 5750 2725
AR Path="/5EA4867C/619482E5" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/619482E5" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/619482E5" Ref="C?"  Part="1" 
AR Path="/5F988DA5/619482E5" Ref="C8"  Part="1" 
F 0 "C8" H 5775 2800 50  0000 L CNN
F 1 "100 nF" H 5775 2625 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5788 2575 50  0001 C CNN
F 3 "~" H 5750 2725 50  0001 C CNN
	1    5750 2725
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 2875 5400 2975
Connection ~ 5400 2975
Wire Wire Line
	5400 2975 5750 2975
Wire Wire Line
	5750 2875 5750 2975
Wire Wire Line
	5325 2475 5400 2475
Wire Wire Line
	5750 2475 5750 2575
Wire Wire Line
	5400 2575 5400 2475
Connection ~ 5400 2475
Text Label 5025 1675 0    50   ~ 0
L_SW_2
Wire Wire Line
	5325 2075 5475 2075
Wire Wire Line
	5325 2175 5475 2175
Wire Wire Line
	5475 2175 5475 2075
$Comp
L Device:C C?
U 1 1 61961E73
P 7450 1925
AR Path="/5EA4867C/61961E73" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/61961E73" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/61961E73" Ref="C?"  Part="1" 
AR Path="/5F988DA5/61961E73" Ref="C40"  Part="1" 
F 0 "C40" H 7600 1975 50  0000 L CNN
F 1 "10 uF" H 7575 1900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7488 1775 50  0001 C CNN
F 3 "~" H 7450 1925 50  0001 C CNN
F 4 "" H 7450 1925 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 7450 1925 50  0001 C CNN "lcsc"
	1    7450 1925
	1    0    0    -1  
$EndComp
Wire Wire Line
	5475 2075 5475 1775
Connection ~ 5475 2075
Connection ~ 7450 1775
Wire Wire Line
	7450 2075 7450 2150
Wire Wire Line
	7450 2150 7900 2150
Connection ~ 7900 2150
Wire Wire Line
	7900 2150 7900 2975
Wire Wire Line
	7325 1650 7325 1675
Wire Wire Line
	7325 1675 7675 1675
$Comp
L Device:R R?
U 1 1 619772C6
P 6775 1925
AR Path="/5EA4867C/619772C6" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/619772C6" Ref="R?"  Part="1" 
AR Path="/5F988DA5/619772C6" Ref="R25"  Part="1" 
F 0 "R25" H 6845 1971 50  0000 L CNN
F 1 "340k" H 6845 1880 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6705 1925 50  0001 C CNN
F 3 "~" H 6775 1925 50  0001 C CNN
	1    6775 1925
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6197810D
P 7100 2725
AR Path="/5EA4867C/6197810D" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/6197810D" Ref="R?"  Part="1" 
AR Path="/5F988DA5/6197810D" Ref="R35"  Part="1" 
F 0 "R35" H 7170 2771 50  0000 L CNN
F 1 "200k" H 7170 2680 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7030 2725 50  0001 C CNN
F 3 "~" H 7100 2725 50  0001 C CNN
	1    7100 2725
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 2875 7100 2975
Wire Wire Line
	7100 2975 7900 2975
Connection ~ 5750 2975
Wire Wire Line
	5400 2475 5750 2475
Wire Wire Line
	7100 2275 7100 2375
$Comp
L Device:R R?
U 1 1 61996769
P 6375 2375
AR Path="/5EA4867C/61996769" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/61996769" Ref="R?"  Part="1" 
AR Path="/5F988DA5/61996769" Ref="R22"  Part="1" 
F 0 "R22" V 6325 2125 50  0000 L CNN
F 1 "107k" V 6375 2275 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6305 2375 50  0001 C CNN
F 3 "~" H 6375 2375 50  0001 C CNN
	1    6375 2375
	0    1    1    0   
$EndComp
Wire Wire Line
	5475 1775 6775 1775
Wire Wire Line
	5325 2275 6775 2275
Connection ~ 6775 1775
$Comp
L Device:C C?
U 1 1 619CAFA1
P 6375 2600
AR Path="/5EA4867C/619CAFA1" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/619CAFA1" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/619CAFA1" Ref="C?"  Part="1" 
AR Path="/5F988DA5/619CAFA1" Ref="C11"  Part="1" 
F 0 "C11" V 6325 2375 50  0000 L CNN
F 1 "4.7 pF" V 6500 2475 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6413 2450 50  0001 C CNN
F 3 "~" H 6375 2600 50  0001 C CNN
	1    6375 2600
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 619CBCE2
P 6825 2375
AR Path="/5EA4867C/619CBCE2" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/619CBCE2" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/619CBCE2" Ref="C?"  Part="1" 
AR Path="/5F988DA5/619CBCE2" Ref="C17"  Part="1" 
F 0 "C17" V 6775 2150 50  0000 L CNN
F 1 "330 pF" V 6950 2250 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6863 2225 50  0001 C CNN
F 3 "~" H 6825 2375 50  0001 C CNN
	1    6825 2375
	0    1    1    0   
$EndComp
Wire Wire Line
	6775 1775 7100 1775
Wire Wire Line
	5325 2375 6050 2375
Wire Wire Line
	6975 2375 7025 2375
Connection ~ 7100 2375
Wire Wire Line
	7100 2375 7100 2575
Wire Wire Line
	6050 2375 6050 2600
Wire Wire Line
	6050 2600 6225 2600
Connection ~ 6050 2375
Wire Wire Line
	6050 2375 6225 2375
Wire Wire Line
	6525 2375 6675 2375
Wire Wire Line
	7025 2600 7025 2375
Wire Wire Line
	6525 2600 7025 2600
Connection ~ 7025 2375
Wire Wire Line
	7025 2375 7100 2375
$Comp
L Device:R R?
U 1 1 619E85E1
P 7100 1925
AR Path="/5EA4867C/619E85E1" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/619E85E1" Ref="R?"  Part="1" 
AR Path="/5F988DA5/619E85E1" Ref="R34"  Part="1" 
F 0 "R34" H 7170 1971 50  0000 L CNN
F 1 "6.49k" H 7170 1880 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7030 1925 50  0001 C CNN
F 3 "~" H 7100 1925 50  0001 C CNN
	1    7100 1925
	1    0    0    -1  
$EndComp
Connection ~ 7100 1775
Wire Wire Line
	7100 1775 7450 1775
Wire Wire Line
	6775 2075 6775 2175
Connection ~ 6775 2275
Wire Wire Line
	6775 2275 7100 2275
$Comp
L Device:C C?
U 1 1 619ED8AC
P 6950 2175
AR Path="/5EA4867C/619ED8AC" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/619ED8AC" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/619ED8AC" Ref="C?"  Part="1" 
AR Path="/5F988DA5/619ED8AC" Ref="C39"  Part="1" 
F 0 "C39" V 6900 2400 50  0000 L CNN
F 1 "47 pF" V 7000 2400 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6988 2025 50  0001 C CNN
F 3 "~" H 6950 2175 50  0001 C CNN
	1    6950 2175
	0    1    1    0   
$EndComp
Wire Wire Line
	7100 2075 7100 2175
Wire Wire Line
	6800 2175 6775 2175
Connection ~ 6775 2175
Wire Wire Line
	6775 2175 6775 2275
Wire Wire Line
	5750 2975 6225 2975
Connection ~ 7100 2975
Connection ~ 6225 2975
Wire Wire Line
	6225 2975 7100 2975
Text Label 5975 2275 0    50   ~ 0
DCDC_FB
Text Label 5700 2375 0    50   ~ 0
COMP
$EndSCHEMATC
