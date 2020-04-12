EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
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
L MotorLocal:Motor_DC M?
U 1 1 5E9679A5
P 7250 3075
F 0 "M?" H 7400 3025 50  0000 L CNN
F 1 "Motor_DC" V 7425 2825 50  0001 L CNN
F 2 "MotorsLocalLib:4x4x11" H 7250 2985 50  0001 C CNN
F 3 "https://www.aliexpress.com/item/32844746278.html?spm=a2g0o.productlist.0.0.24ef228a6Cfn5S&algo_pvid=3165a7c1-ba73-4c2c-bb27-6dacea1bed25&algo_expid=3165a7c1-ba73-4c2c-bb27-6dacea1bed25-0&btsid=0b8b15c915866028623212205ec781&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_" H 7250 2985 50  0001 C CNN
	1    7250 3075
	1    0    0    -1  
$EndComp
Text Label 6825 3150 0    50   ~ 0
GND
Wire Wire Line
	7250 2875 7250 2750
Text HLabel 6000 2750 0    50   Input ~ 0
VCC_motor
$Comp
L MosfetLocal:SL2300 VT?
U 1 1 5E950239
P 7225 3700
F 0 "VT?" H 7354 3700 50  0000 L CNN
F 1 "SL2300" H 7355 3655 50  0001 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 7225 3700 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1906271838_SLKORMICRO-Elec-SL2300_C350314.pdf" H 7225 3700 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/MOSFET_Slkor-SLKORMICRO-Elec-SL2300_C350314.html" H 7225 3700 50  0001 C CNN "lcsc"
	1    7225 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3375 7250 3450
$Comp
L Device:R R?
U 1 1 5E95D4D2
P 6950 4025
F 0 "R?" H 7020 4071 50  0000 L CNN
F 1 "10k" H 7020 3980 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6880 4025 50  0001 C CNN
F 3 "~" H 6950 4025 50  0001 C CNN
	1    6950 4025
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E95E60A
P 6675 3700
F 0 "R?" V 6468 3700 50  0000 C CNN
F 1 "330" V 6559 3700 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6605 3700 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Others_Viking-Tech-ARG03FTC3300_C217969.html" H 6675 3700 50  0001 C CNN
	1    6675 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	6825 3700 6950 3700
Wire Wire Line
	6950 3875 6950 3700
Wire Wire Line
	6950 4250 7250 4250
Wire Wire Line
	7250 4250 7250 3900
Wire Wire Line
	6950 4250 6950 4175
Text Label 7050 4250 0    50   ~ 0
GND
Wire Wire Line
	6525 3700 6150 3700
Text HLabel 6075 3700 0    50   Input ~ 0
Enable_motor
Wire Wire Line
	6800 3150 7025 3150
Wire Wire Line
	7250 2750 6000 2750
$Comp
L Connector:TestPoint TP?
U 1 1 5E966959
P 6150 3700
F 0 "TP?" H 6208 3772 50  0000 L CNN
F 1 "TestPoint" H 6208 3727 50  0001 L CNN
F 2 "" H 6350 3700 50  0001 C CNN
F 3 "~" H 6350 3700 50  0001 C CNN
	1    6150 3700
	1    0    0    -1  
$EndComp
Connection ~ 6150 3700
Wire Wire Line
	6150 3700 6075 3700
Text Notes 6275 2700 0    50   ~ 0
Place the capacitor and the diode as close as physically possible
$Comp
L Device:C C?
U 1 1 5E969686
P 7675 3150
F 0 "C?" H 7790 3196 50  0000 L CNN
F 1 "100n X7R 16V" H 7450 3000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 7713 3000 50  0001 C CNN
F 3 "~" H 7675 3150 50  0001 C CNN
	1    7675 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:D D?
U 1 1 5E96AA9C
P 8050 3150
F 0 "D?" V 8004 3229 50  0000 L CNN
F 1 "1A 20V" V 8095 3229 50  0000 L CNN
F 2 "Diodes_SMD:D_SMA_Handsoldering" H 8050 3150 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1901021833_Shandong-Jingdao-Microelectronics-SS12_C353243.pdf" H 8050 3150 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Schottky-Barrier-Diodes-SBD_Shandong-Jingdao-Microelectronics-SS12_C353243.html" V 8050 3150 50  0001 C CNN "lcsc"
	1    8050 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	7675 3000 7675 2750
Wire Wire Line
	7675 2750 7250 2750
Connection ~ 7250 2750
Wire Wire Line
	7250 3450 7675 3450
Wire Wire Line
	7675 3450 7675 3300
Connection ~ 7250 3450
Wire Wire Line
	7250 3450 7250 3500
Wire Wire Line
	7675 2750 8050 2750
Wire Wire Line
	8050 2750 8050 3000
Connection ~ 7675 2750
Wire Wire Line
	8050 3300 8050 3450
Wire Wire Line
	8050 3450 7675 3450
Connection ~ 7675 3450
$EndSCHEMATC
