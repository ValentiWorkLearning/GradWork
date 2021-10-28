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
Wire Wire Line
	3400 2100 3400 2175
Text Label 3850 1700 2    50   ~ 0
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
Text HLabel 6900 2100 2    50   Output ~ 0
V3V3
$Comp
L Connector:TestPoint TP?
U 1 1 5F9A38D0
P 6750 2000
AR Path="/5EA4867C/5F9A38D0" Ref="TP?"  Part="1" 
AR Path="/5E9C1C3A/5F9A38D0" Ref="TP?"  Part="1" 
AR Path="/5F7F86D0/5F9A38D0" Ref="TP?"  Part="1" 
AR Path="/5F988DA5/5F9A38D0" Ref="TP15"  Part="1" 
F 0 "TP15" H 6808 2072 50  0000 L CNN
F 1 "TestPoint" H 6808 2027 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 6950 2000 50  0001 C CNN
F 3 "~" H 6950 2000 50  0001 C CNN
	1    6750 2000
	1    0    0    -1  
$EndComp
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
Wire Notes Line
	1025 1025 1025 3350
Wire Notes Line
	9100 1025 9100 3350
Wire Notes Line
	1025 1025 9100 1025
Wire Notes Line
	1025 3350 9100 3350
$Comp
L power:+3.3V #PWR?
U 1 1 5F9A38F1
P 6550 2000
AR Path="/5E9C1C3A/5F9A38F1" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9A38F1" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5F9A38F1" Ref="#PWR053"  Part="1" 
F 0 "#PWR053" H 6550 1850 50  0001 C CNN
F 1 "+3.3V" H 6565 2173 50  0000 C CNN
F 2 "" H 6550 2000 50  0001 C CNN
F 3 "" H 6550 2000 50  0001 C CNN
	1    6550 2000
	1    0    0    -1  
$EndComp
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
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 2000 2500 50  0001 C CNN "lcsc"
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
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 7975 5500 50  0001 C CNN "lcsc"
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
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 8675 5500 50  0001 C CNN "lcsc"
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
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 9400 5500 50  0001 C CNN "lcsc"
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
F 4 "https://www.aliexpress.com/item/32844746278.html?spm=a2g0o.productlist.0.0.24ef228a6Cfn5S&algo_pvid=3165a7c1-ba73-4c2c-bb27-6dacea1bed25&algo_expid=3165a7c1-ba73-4c2c-bb27-6dacea1bed25-0&btsid=0b8b15c915866028623212205ec781&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_" H 2975 4550 50  0001 C CNN "lcsc"
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
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 2675 5500 50  0001 C CNN "lcsc"
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
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_Walsin-Tech-Corp-WR06X331JTL_C384242.html" H 2400 5175 50  0001 C CNN "lcsc"
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
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_Samsung-Electro-Mechanics-CL10B104KO8NNNC_C66501.html" H 3400 4625 50  0001 C CNN "lcsc"
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
P 5750 3000
AR Path="/5FC58698" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FC58698" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FC58698" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5FC58698" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5FC58698" Ref="#PWR?"  Part="1" 
AR Path="/5F988DA5/5FC58698" Ref="#PWR052"  Part="1" 
F 0 "#PWR052" H 5750 2750 50  0001 C CNN
F 1 "GND" H 5750 2850 50  0000 C CNN
F 2 "" H 5750 3000 50  0001 C CNN
F 3 "" H 5750 3000 50  0001 C CNN
	1    5750 3000
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5FCE6443
P 6200 1900
AR Path="/5F913559/5FCE6443" Ref="#FLG?"  Part="1" 
AR Path="/5F988DA5/5FCE6443" Ref="#FLG04"  Part="1" 
F 0 "#FLG04" H 6200 1975 50  0001 C CNN
F 1 "PWR_FLAG" H 6200 2073 50  0000 C CNN
F 2 "" H 6200 1900 50  0001 C CNN
F 3 "~" H 6200 1900 50  0001 C CNN
	1    6200 1900
	1    0    0    -1  
$EndComp
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
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_Walsin-Tech-Corp-WR06X331JTL_C384242.html" H 7100 5050 50  0001 C CNN "lcsc"
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
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_Walsin-Tech-Corp-WR06X331JTL_C384242.html" H 7100 5150 50  0001 C CNN "lcsc"
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
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_Walsin-Tech-Corp-WR06X331JTL_C384242.html" H 7100 5250 50  0001 C CNN "lcsc"
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
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 7725 5500 50  0001 C CNN "lcsc"
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
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 8425 5500 50  0001 C CNN "lcsc"
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
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 9150 5500 50  0001 C CNN "lcsc"
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
Text Notes 7000 2000 0    50   ~ 0
Vout = 3.0V\n
$Comp
L Device:C C?
U 1 1 61961E73
P 5900 2250
AR Path="/5EA4867C/61961E73" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/61961E73" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/61961E73" Ref="C?"  Part="1" 
AR Path="/5F988DA5/61961E73" Ref="C40"  Part="1" 
F 0 "C40" H 6050 2300 50  0000 L CNN
F 1 "10 uF" H 6025 2225 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5938 2100 50  0001 C CNN
F 3 "~" H 5900 2250 50  0001 C CNN
F 4 "" H 5900 2250 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 5900 2250 50  0001 C CNN "lcsc"
	1    5900 2250
	1    0    0    -1  
$EndComp
$Comp
L TPS73501DRBR:TPS73501DRBR U12
U 1 1 61768B9E
P 4950 2400
F 0 "U12" H 4950 2970 50  0000 C CNN
F 1 "TPS73501DRBR" H 4950 2879 50  0000 C CNN
F 2 "TPS73501DRBR:TPS73501DRBR" H 4950 2400 50  0001 L BNN
F 3 "" H 4950 2400 50  0001 L BNN
F 4 "https://lcsc.com/product-detail/Linear-Voltage-Regulators-LDO_Texas-Instruments-TPS73501DRBR_C130077.html" H 4950 2400 50  0001 C CNN "lcsc"
	1    4950 2400
	1    0    0    -1  
$EndComp
Text Notes 4150 1450 0    100  ~ 0
LDO 3.0V\n\n
Connection ~ 2900 2500
Wire Wire Line
	2900 2500 3800 2500
Wire Wire Line
	5650 2100 5900 2100
Wire Wire Line
	5900 2400 5900 2600
Wire Wire Line
	5900 2100 6550 2100
Connection ~ 5900 2100
Wire Wire Line
	6750 2000 6750 2100
Connection ~ 6750 2100
Wire Wire Line
	6750 2100 6900 2100
Wire Wire Line
	6550 2000 6550 2100
Connection ~ 6550 2100
Wire Wire Line
	6550 2100 6750 2100
Wire Wire Line
	6550 2000 6200 2000
Wire Wire Line
	6200 2000 6200 1900
Connection ~ 6550 2000
Wire Wire Line
	5650 2600 5750 2600
Wire Wire Line
	5750 3000 5750 2600
Connection ~ 5750 2600
Wire Wire Line
	5750 2600 5900 2600
Text Notes 7550 2650 0    50   ~ 0
Vout=(R1+R2)/R2 * 1.208\n
$Comp
L Device:R R19
U 1 1 617DD2C1
P 7300 2800
F 0 "R19" H 7370 2846 50  0000 L CNN
F 1 "220k" H 7370 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7230 2800 50  0001 C CNN
F 3 "~" H 7300 2800 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_FH-Guangdong-Fenghua-Advanced-Tech-RS-03K224JT_C118377.html" H 7300 2800 50  0001 C CNN "lcsc"
	1    7300 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 617DD9E3
P 7300 2450
F 0 "R3" H 7370 2496 50  0000 L CNN
F 1 "330k" H 7370 2405 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7230 2450 50  0001 C CNN
F 3 "~" H 7300 2450 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_Resistor-Today-AECR0603F330KK9_C328354.html" H 7300 2450 50  0001 C CNN "lcsc"
	1    7300 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 2200 4250 2200
Wire Wire Line
	3800 2500 3800 2100
Wire Wire Line
	3800 2100 4250 2100
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
	3400 1700 3400 1800
Wire Wire Line
	4000 1700 4000 2200
Wire Wire Line
	3400 1700 4000 1700
$Comp
L power:GND #PWR058
U 1 1 617FB898
P 7300 3000
F 0 "#PWR058" H 7300 2750 50  0001 C CNN
F 1 "GND" H 7305 2827 50  0000 C CNN
F 2 "" H 7300 3000 50  0001 C CNN
F 3 "" H 7300 3000 50  0001 C CNN
	1    7300 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 2600 7300 2650
Wire Wire Line
	7300 2950 7300 3000
$Comp
L power:+3.3V #PWR057
U 1 1 61802C4D
P 7300 2250
F 0 "#PWR057" H 7300 2100 50  0001 C CNN
F 1 "+3.3V" H 7315 2423 50  0000 C CNN
F 2 "" H 7300 2250 50  0001 C CNN
F 3 "" H 7300 2250 50  0001 C CNN
	1    7300 2250
	1    0    0    -1  
$EndComp
Text Label 6950 2650 2    50   ~ 0
LDO_RDIV
Wire Wire Line
	6950 2650 7300 2650
Connection ~ 7300 2650
Wire Wire Line
	7300 2250 7300 2300
Text Label 4200 2300 2    50   ~ 0
LDO_RDIV
Wire Wire Line
	4200 2300 4250 2300
$EndSCHEMATC
