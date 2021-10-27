EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
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
U 1 1 5F943E27
P 4850 2175
AR Path="/5EA4867C/5F943E27" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F943E27" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/5F943E27" Ref="C?"  Part="1" 
AR Path="/5F913559/5F943E27" Ref="C29"  Part="1" 
F 0 "C29" H 4875 2250 50  0000 L CNN
F 1 "100 nF" V 4700 2050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4888 2025 50  0001 C CNN
F 3 "~" H 4850 2175 50  0001 C CNN
	1    4850 2175
	1    0    0    -1  
$EndComp
Wire Wire Line
	5025 1850 4850 1850
Wire Wire Line
	4850 1850 4850 2025
Wire Wire Line
	6625 1850 6875 1850
Text Label 4575 1850 0    50   ~ 0
V_Battery_P
Connection ~ 4850 1850
Wire Wire Line
	6625 1450 6825 1450
Wire Wire Line
	5025 1350 4650 1350
$Comp
L Device:R R?
U 1 1 5F943E4B
P 4500 1350
AR Path="/5EA4867C/5F943E4B" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943E4B" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943E4B" Ref="R21"  Part="1" 
F 0 "R21" V 4400 1150 50  0000 L CNN
F 1 "10k" V 4400 1450 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4430 1350 50  0001 C CNN
F 3 "~" H 4500 1350 50  0001 C CNN
	1    4500 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	4350 1350 4100 1350
Text Notes 4575 1575 0    50   ~ 0
Int 63KOhm PU\n
Wire Notes Line
	600  675  600  3250
Text Notes 5200 950  0    50   ~ 0
ON/OFF with two PB\n\n
$Comp
L Connector:TestPoint TP?
U 1 1 5F943E5B
P 6825 1450
AR Path="/5E9C1C3A/5F943E5B" Ref="TP?"  Part="1" 
AR Path="/5ED3F98E/5F943E5B" Ref="TP?"  Part="1" 
AR Path="/5F913559/5F943E5B" Ref="TP11"  Part="1" 
F 0 "TP11" H 6883 1522 50  0000 L CNN
F 1 "TestPoint" H 6883 1477 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 7025 1450 50  0001 C CNN
F 3 "~" H 7025 1450 50  0001 C CNN
	1    6825 1450
	1    0    0    -1  
$EndComp
Text HLabel 1100 1725 0    50   Output ~ 0
PB_1_MCU
Text HLabel 1100 2350 0    50   Output ~ 0
PB_2_MCU
$Comp
L MosfetLocal:SL2300 VT?
U 1 1 5F943E66
P 3125 1725
AR Path="/5EA4867C/5F943E66" Ref="VT?"  Part="1" 
AR Path="/5ED3F98E/5F943E66" Ref="VT?"  Part="1" 
AR Path="/5F913559/5F943E66" Ref="VT1"  Part="1" 
F 0 "VT1" H 3254 1725 50  0000 L CNN
F 1 "SL2300" H 3255 1680 50  0001 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3125 1725 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1906271838_SLKORMICRO-Elec-SL2300_C350314.pdf" H 3125 1725 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/MOSFET_Slkor-SLKORMICRO-Elec-SL2300_C350314.html" H 3125 1725 50  0001 C CNN "lcsc"
	1    3125 1725
	1    0    0    -1  
$EndComp
$Comp
L MosfetLocal:SL2300 VT?
U 1 1 5F943E6D
P 3125 2350
AR Path="/5EA4867C/5F943E6D" Ref="VT?"  Part="1" 
AR Path="/5ED3F98E/5F943E6D" Ref="VT?"  Part="1" 
AR Path="/5F913559/5F943E6D" Ref="VT2"  Part="1" 
F 0 "VT2" H 3254 2350 50  0000 L CNN
F 1 "SL2300" H 3255 2305 50  0001 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3125 2350 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1906271838_SLKORMICRO-Elec-SL2300_C350314.pdf" H 3125 2350 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/MOSFET_Slkor-SLKORMICRO-Elec-SL2300_C350314.html" H 3125 2350 50  0001 C CNN "lcsc"
	1    3125 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 1925 3150 2150
$Comp
L Switch:SW_Push SW?
U 1 1 5F943E75
P 2475 1150
AR Path="/5ED3F98E/5F943E75" Ref="SW?"  Part="1" 
AR Path="/5F913559/5F943E75" Ref="SW2"  Part="1" 
F 0 "SW2" V 2475 1425 50  0000 C CNN
F 1 "SW_Push" H 2475 1075 50  0000 C CNN
F 2 "OmronSwitch:SW_B3U-3000P" H 2475 1350 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/2012042009_Omron-Electronics-B3U-3000P_C963349.pdf" H 2475 1350 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Tactile-Switches_Omron-Electronics-B3U-3000P_C963349.html" H 2475 1150 50  0001 C CNN "lcsc"
	1    2475 1150
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5F943E7C
P 2300 2025
AR Path="/5ED3F98E/5F943E7C" Ref="SW?"  Part="1" 
AR Path="/5F913559/5F943E7C" Ref="SW1"  Part="1" 
F 0 "SW1" V 2350 2200 50  0000 C CNN
F 1 "SW_Push" H 2300 1975 50  0000 C CNN
F 2 "OmronSwitch:SW_B3U-3000P" H 2300 2225 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/2012042009_Omron-Electronics-B3U-3000P_C963349.pdf" H 2300 2225 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Tactile-Switches_Omron-Electronics-B3U-3000P_C963349.html" H 2300 2025 50  0001 C CNN "lcsc"
	1    2300 2025
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5F943E82
P 2450 2650
AR Path="/5EA4867C/5F943E82" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943E82" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943E82" Ref="R17"  Part="1" 
F 0 "R17" H 2575 2625 50  0000 L CNN
F 1 "10k" H 2525 2725 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2380 2650 50  0001 C CNN
F 3 "~" H 2450 2650 50  0001 C CNN
	1    2450 2650
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5F943E88
P 2625 1975
AR Path="/5EA4867C/5F943E88" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943E88" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943E88" Ref="R18"  Part="1" 
F 0 "R18" H 2425 1925 50  0000 L CNN
F 1 "10k" H 2425 2050 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2555 1975 50  0001 C CNN
F 3 "~" H 2625 1975 50  0001 C CNN
	1    2625 1975
	-1   0    0    1   
$EndComp
Wire Wire Line
	2625 1825 2625 1725
Wire Wire Line
	2625 1725 2850 1725
Wire Wire Line
	2450 2500 2450 2350
Wire Wire Line
	2450 2350 2850 2350
Wire Wire Line
	2625 2125 2625 2900
Wire Wire Line
	2625 2900 2550 2900
Wire Wire Line
	2450 2900 2450 2800
$Comp
L power:GND #PWR?
U 1 1 5F943E95
P 2550 2950
AR Path="/5F943E95" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943E95" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943E95" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943E95" Ref="#PWR031"  Part="1" 
F 0 "#PWR031" H 2550 2700 50  0001 C CNN
F 1 "GND" H 2550 2800 50  0000 C CNN
F 2 "" H 2550 2950 50  0001 C CNN
F 3 "" H 2550 2950 50  0001 C CNN
	1    2550 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 2950 2550 2900
Connection ~ 2550 2900
Wire Wire Line
	3150 2550 3150 2900
Wire Wire Line
	3150 2900 2625 2900
Connection ~ 2625 2900
Wire Wire Line
	2300 2350 2300 2225
Connection ~ 2450 2350
Wire Wire Line
	2475 1350 2475 1725
Connection ~ 2625 1725
Wire Wire Line
	2300 900  2475 900 
Wire Wire Line
	2475 900  2475 950 
Wire Wire Line
	2300 900  2300 1825
Wire Wire Line
	3150 1525 3150 1450
Text Notes 4350 2625 2    50   ~ 0
PB1 && PB2 => OUT=~OUT\n
Text Label 2375 900  0    50   ~ 0
V_Battery_P
$Comp
L power:GND #PWR?
U 1 1 5F943EB2
P 4100 1350
AR Path="/5F943EB2" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943EB2" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943EB2" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943EB2" Ref="#PWR035"  Part="1" 
F 0 "#PWR035" H 4100 1100 50  0001 C CNN
F 1 "GND" H 4100 1200 50  0000 C CNN
F 2 "" H 4100 1350 50  0001 C CNN
F 3 "" H 4100 1350 50  0001 C CNN
	1    4100 1350
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F943EB8
P 4850 2450
AR Path="/5F943EB8" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943EB8" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943EB8" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943EB8" Ref="#PWR037"  Part="1" 
F 0 "#PWR037" H 4850 2200 50  0001 C CNN
F 1 "GND" H 4850 2300 50  0000 C CNN
F 2 "" H 4850 2450 50  0001 C CNN
F 3 "" H 4850 2450 50  0001 C CNN
	1    4850 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 2325 4850 2450
$Comp
L power:GND #PWR?
U 1 1 5F943EBF
P 6875 1850
AR Path="/5F943EBF" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943EBF" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943EBF" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943EBF" Ref="#PWR043"  Part="1" 
F 0 "#PWR043" H 6875 1600 50  0001 C CNN
F 1 "GND" H 6875 1700 50  0000 C CNN
F 2 "" H 6875 1850 50  0001 C CNN
F 3 "" H 6875 1850 50  0001 C CNN
	1    6875 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F943ECC
P 8025 6075
AR Path="/5EA4867C/5F943ECC" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F943ECC" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943ECC" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943ECC" Ref="R24"  Part="1" 
F 0 "R24" V 7818 6075 50  0000 C CNN
F 1 "330" V 7909 6075 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7955 6075 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Others_Viking-Tech-ARG03FTC3300_C217969.html" H 8025 6075 50  0001 C CNN
	1    8025 6075
	0    1    1    0   
$EndComp
Text Label 8200 6075 0    50   ~ 0
Rlim
Wire Wire Line
	9975 5825 9950 5825
Wire Wire Line
	9975 6075 9950 6075
Wire Wire Line
	9975 5825 9975 6075
Connection ~ 9975 6075
$Comp
L Device:C C?
U 1 1 5F943EDA
P 7250 5775
AR Path="/5EA4867C/5F943EDA" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F943EDA" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/5F943EDA" Ref="C?"  Part="1" 
AR Path="/5F913559/5F943EDA" Ref="C30"  Part="1" 
F 0 "C30" H 7275 5850 50  0000 L CNN
F 1 "100 nF" V 7100 5650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7288 5625 50  0001 C CNN
F 3 "~" H 7250 5775 50  0001 C CNN
	1    7250 5775
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F943EE0
P 7850 5775
AR Path="/5EA4867C/5F943EE0" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F943EE0" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/5F943EE0" Ref="C?"  Part="1" 
AR Path="/5F913559/5F943EE0" Ref="C31"  Part="1" 
F 0 "C31" H 7875 5850 50  0000 L CNN
F 1 "100 nF" V 7725 5600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7888 5625 50  0001 C CNN
F 3 "~" H 7850 5775 50  0001 C CNN
	1    7850 5775
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 5625 7250 5525
Wire Wire Line
	7250 5925 7250 6075
Wire Wire Line
	7850 5925 7850 6075
Text Label 7650 5525 0    50   ~ 0
V_USB
NoConn ~ 9950 5425
Text Label 10500 5325 2    50   ~ 0
V_OUT_MUX
Text Notes 8275 4750 0    100  ~ 0
Power Mux\n
Wire Notes Line
	11150 4550 11150 6450
Wire Notes Line
	11150 6450 7025 6450
Wire Notes Line
	7025 6450 7025 4550
Wire Notes Line
	7025 4550 11150 4550
$Comp
L USB_connectors:TYPE-C-31-M-17 J?
U 1 1 5F943EF2
P 600 4900
AR Path="/5E9C1C3A/5F943EF2" Ref="J?"  Part="1" 
AR Path="/5ED3F98E/5F943EF2" Ref="J?"  Part="1" 
AR Path="/5F913559/5F943EF2" Ref="J3"  Part="1" 
F 0 "J3" H 833 5761 100 0000 C CNN
F 1 "TYPE-C-31-M-17" H 833 5761 100 0001 C CNN
F 2 "USB:TYPE-C-31-M-17" H 600 4900 100 0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1903211732_Korean-Hroparts-Elec-TYPE-C-31-M-17_C283540.pdf" H 600 4900 100 0001 C CNN
F 4 "https://lcsc.com/product-detail/Others_Korean-Hroparts-Elec-TYPE-C-31-M-17_C283540.html" H 600 4900 50  0001 C CNN "lcsc"
	1    600  4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 4675 1050 4750
Connection ~ 1050 4750
Wire Wire Line
	1050 4750 1050 4825
Wire Wire Line
	1050 4825 1275 4825
Connection ~ 1050 4825
NoConn ~ 1050 4550
NoConn ~ 1050 4475
Wire Wire Line
	1050 4250 1150 4250
Wire Wire Line
	1050 4250 1050 4325
Connection ~ 1050 4250
Text Label 1475 4250 2    50   ~ 0
V_USB
Text Notes 775  5125 0    50   ~ 0
USB for power \nsupply only\n
$Comp
L Connector:TestPoint TP?
U 1 1 5F943F05
P 10575 5225
AR Path="/5EA4867C/5F943F05" Ref="TP?"  Part="1" 
AR Path="/5E9C1C3A/5F943F05" Ref="TP?"  Part="1" 
AR Path="/5ED3F98E/5F943F05" Ref="TP?"  Part="1" 
AR Path="/5F913559/5F943F05" Ref="TP12"  Part="1" 
F 0 "TP12" H 10633 5297 50  0000 L CNN
F 1 "TestPoint" H 10633 5252 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 10775 5225 50  0001 C CNN
F 3 "~" H 10775 5225 50  0001 C CNN
	1    10575 5225
	1    0    0    -1  
$EndComp
Text HLabel 10650 5325 2    50   Output ~ 0
V_OUT_MUX
Connection ~ 10575 5325
Wire Wire Line
	10575 5325 10650 5325
Wire Wire Line
	10575 5225 10575 5325
$Comp
L Device:D_TVS D?
U 1 1 5F943F10
P 1275 4525
AR Path="/5E9C1C3A/5F943F10" Ref="D?"  Part="1" 
AR Path="/5ED3F98E/5F943F10" Ref="D?"  Part="1" 
AR Path="/5F913559/5F943F10" Ref="D1"  Part="1" 
F 0 "D1" V 1229 4604 50  0000 L CNN
F 1 "D_TVS" V 1320 4604 50  0000 L CNN
F 2 "LocalFootprints:TVS_DFN1006" H 1275 4525 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/2012141705_Leiditech-ESDA05CP_C384839.pdf" H 1275 4525 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/TVS_Leiditech-ESDA05CP_C384839.html" V 1275 4525 50  0001 C CNN "lcsc"
	1    1275 4525
	0    1    1    0   
$EndComp
Wire Wire Line
	1275 4375 1275 4250
Connection ~ 1275 4250
Wire Wire Line
	1275 4675 1275 4825
Connection ~ 1275 4825
Wire Wire Line
	1275 4825 1475 4825
Wire Wire Line
	7800 5625 7850 5625
Wire Wire Line
	7250 5525 7400 5525
Wire Wire Line
	8175 6075 8350 6075
Connection ~ 7850 5625
Wire Wire Line
	7850 5625 8350 5625
Connection ~ 7850 6075
Wire Wire Line
	7850 6075 7875 6075
Wire Wire Line
	7250 6075 7650 6075
$Comp
L power:+5V #PWR?
U 1 1 5F943F24
P 1150 4250
AR Path="/5E9C1C3A/5F943F24" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F24" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F24" Ref="#PWR028"  Part="1" 
F 0 "#PWR028" H 1150 4100 50  0001 C CNN
F 1 "+5V" H 1165 4423 50  0000 C CNN
F 2 "" H 1150 4250 50  0001 C CNN
F 3 "" H 1150 4250 50  0001 C CNN
	1    1150 4250
	1    0    0    -1  
$EndComp
Connection ~ 1150 4250
Wire Wire Line
	1150 4250 1275 4250
$Comp
L power:+5V #PWR?
U 1 1 5F943F2C
P 7400 5525
AR Path="/5E9C1C3A/5F943F2C" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F2C" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F2C" Ref="#PWR041"  Part="1" 
F 0 "#PWR041" H 7400 5375 50  0001 C CNN
F 1 "+5V" H 7415 5698 50  0000 C CNN
F 2 "" H 7400 5525 50  0001 C CNN
F 3 "" H 7400 5525 50  0001 C CNN
	1    7400 5525
	1    0    0    -1  
$EndComp
Connection ~ 7400 5525
Wire Wire Line
	7400 5525 8350 5525
$Comp
L Device:Battery_Cell BT?
U 1 1 5F943F36
P 1100 6650
AR Path="/5E9C1C3A/5F943F36" Ref="BT?"  Part="1" 
AR Path="/5ED3F98E/5F943F36" Ref="BT?"  Part="1" 
AR Path="/5F913559/5F943F36" Ref="BT1"  Part="1" 
F 0 "BT1" H 1218 6746 50  0000 L CNN
F 1 "Battery_Cell" H 1218 6655 50  0000 L CNN
F 2 "LocalFootprints:BatteryPads" V 1100 6710 50  0001 C CNN
F 3 "https://aliexpress.ru/item/33000396152.html?spm=a2g0o.productlist.0.0.43416af464CXwu&algo_pvid=e6706777-cde6-4668-9867-8799ba4921bb&algo_expid=e6706777-cde6-4668-9867-8799ba4921bb-0&btsid=0b8b037215874644191236041ea897&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_" V 1100 6710 50  0001 C CNN
	1    1100 6650
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1100 6450 1100 6325
Wire Wire Line
	1100 6750 1100 6800
Text Label 7800 5625 0    50   ~ 0
V_Battery_P
Text Notes 1025 3850 0    100  ~ 0
PSU
$Comp
L power:GND #PWR?
U 1 1 5F943F40
P 1475 4825
AR Path="/5F943F40" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943F40" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F40" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F40" Ref="#PWR029"  Part="1" 
F 0 "#PWR029" H 1475 4575 50  0001 C CNN
F 1 "GND" H 1475 4675 50  0000 C CNN
F 2 "" H 1475 4825 50  0001 C CNN
F 3 "" H 1475 4825 50  0001 C CNN
	1    1475 4825
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F943F46
P 7650 6075
AR Path="/5F943F46" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943F46" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F46" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F46" Ref="#PWR042"  Part="1" 
F 0 "#PWR042" H 7650 5825 50  0001 C CNN
F 1 "GND" H 7650 5925 50  0000 C CNN
F 2 "" H 7650 6075 50  0001 C CNN
F 3 "" H 7650 6075 50  0001 C CNN
	1    7650 6075
	1    0    0    -1  
$EndComp
Connection ~ 7650 6075
Wire Wire Line
	7650 6075 7850 6075
$Comp
L power:GND #PWR?
U 1 1 5F943F4E
P 10200 6075
AR Path="/5F943F4E" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943F4E" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F4E" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F4E" Ref="#PWR045"  Part="1" 
F 0 "#PWR045" H 10200 5825 50  0001 C CNN
F 1 "GND" H 10200 5925 50  0000 C CNN
F 2 "" H 10200 6075 50  0001 C CNN
F 3 "" H 10200 6075 50  0001 C CNN
	1    10200 6075
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR?
U 1 1 5F943F54
P 1100 6325
AR Path="/5E9C1C3A/5F943F54" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F943F54" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F54" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F54" Ref="#PWR027"  Part="1" 
F 0 "#PWR027" H 1100 6175 50  0001 C CNN
F 1 "+BATT" H 1115 6498 50  0000 C CNN
F 2 "" H 1100 6325 50  0001 C CNN
F 3 "" H 1100 6325 50  0001 C CNN
	1    1100 6325
	-1   0    0    -1  
$EndComp
Connection ~ 1100 6325
Wire Wire Line
	4575 4650 5025 4650
$Comp
L BatteryManagmentLocal:BQ21040DBVT U?
U 1 1 5F943F5D
P 2975 4550
AR Path="/5E9C1C3A/5F943F5D" Ref="U?"  Part="1" 
AR Path="/5F7F86D0/5F943F5D" Ref="U?"  Part="1" 
AR Path="/5ED3F98E/5F943F5D" Ref="U?"  Part="1" 
AR Path="/5F913559/5F943F5D" Ref="U5"  Part="1" 
F 0 "U5" H 3775 4937 60  0000 C CNN
F 1 "BQ21040DBVT" H 3775 4831 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6" H 3775 4790 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Texas-Instruments-TI-BQ21040DBVR_C202311.pdf" H 3775 4831 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/PMIC-Battery-Management_Texas-Instruments_BQ21040DBVR_Texas-Instruments-Texas-Instruments-BQ21040DBVR_C202311.html" H 2975 4550 50  0001 C CNN "lcsc"
	1    2975 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2975 4400 2975 4450
Wire Wire Line
	2975 4700 2975 4650
$Comp
L Device:R R?
U 1 1 5F943F65
P 2750 4850
AR Path="/5EA4867C/5F943F65" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F943F65" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F943F65" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943F65" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943F65" Ref="R20"  Part="1" 
F 0 "R20" V 2825 4800 50  0000 L CNN
F 1 "10k" V 2675 4775 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2680 4850 50  0001 C CNN
F 3 "~" H 2750 4850 50  0001 C CNN
	1    2750 4850
	0    1    -1   0   
$EndComp
Wire Wire Line
	2975 4850 2900 4850
Wire Wire Line
	2600 4850 2575 4850
Text Notes 2525 5125 0    50   ~ 0
Set fast charge\ncurrent to 54 mA
NoConn ~ 4575 4850
Wire Wire Line
	2575 4700 2975 4700
Wire Wire Line
	2575 4400 2650 4400
Text Notes 3650 3900 0    100  ~ 0
Battery charger\n
Wire Notes Line
	2050 5375 2050 3575
$Comp
L Device:R R?
U 1 1 5F943F7B
P 5025 4800
AR Path="/5EA4867C/5F943F7B" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F943F7B" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F943F7B" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943F7B" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943F7B" Ref="R23"  Part="1" 
F 0 "R23" H 4800 4775 50  0000 L CNN
F 1 "10k" V 5100 4725 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4955 4800 50  0001 C CNN
F 3 "~" H 5025 4800 50  0001 C CNN
	1    5025 4800
	1    0    0    1   
$EndComp
Text Label 2750 4400 0    50   ~ 0
V_USB
Wire Notes Line
	5275 3575 5275 5375
Wire Notes Line
	2050 5375 5275 5375
Wire Notes Line
	2050 3575 5275 3575
$Comp
L power:+5V #PWR?
U 1 1 5F943F85
P 2650 4400
AR Path="/5E9C1C3A/5F943F85" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F943F85" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F85" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F85" Ref="#PWR033"  Part="1" 
F 0 "#PWR033" H 2650 4250 50  0001 C CNN
F 1 "+5V" H 2665 4573 50  0000 C CNN
F 2 "" H 2650 4400 50  0001 C CNN
F 3 "" H 2650 4400 50  0001 C CNN
	1    2650 4400
	1    0    0    -1  
$EndComp
Connection ~ 2650 4400
Wire Wire Line
	2650 4400 2975 4400
$Comp
L power:GND #PWR?
U 1 1 5F943F8D
P 2375 4850
AR Path="/5F943F8D" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943F8D" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F8D" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5F943F8D" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F943F8D" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F8D" Ref="#PWR032"  Part="1" 
F 0 "#PWR032" H 2375 4600 50  0001 C CNN
F 1 "GND" H 2375 4700 50  0000 C CNN
F 2 "" H 2375 4850 50  0001 C CNN
F 3 "" H 2375 4850 50  0001 C CNN
	1    2375 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2575 4700 2575 4850
Connection ~ 2575 4850
Wire Wire Line
	2575 4850 2375 4850
$Comp
L power:+BATT #PWR?
U 1 1 5F943F9D
P 5025 4350
AR Path="/5E9C1C3A/5F943F9D" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F943F9D" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F9D" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F9D" Ref="#PWR039"  Part="1" 
F 0 "#PWR039" H 5025 4200 50  0001 C CNN
F 1 "+BATT" H 5040 4523 50  0000 C CNN
F 2 "" H 5025 4350 50  0001 C CNN
F 3 "" H 5025 4350 50  0001 C CNN
	1    5025 4350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5025 4450 5025 4350
Wire Wire Line
	4575 4450 5025 4450
Text Label 2650 6325 2    50   ~ 0
V_Battery_P
Wire Wire Line
	3925 6225 2975 6225
Wire Wire Line
	2975 7025 2975 7175
Text Notes 4550 5775 2    100  ~ 0
Fuel gauge
Wire Notes Line
	2000 5500 2000 7775
Wire Notes Line
	2000 5500 6925 5500
Wire Notes Line
	2000 7775 6925 7775
Wire Notes Line
	6925 5500 6925 7775
$Comp
L power:GND #PWR?
U 1 1 5F943FFA
P 3925 7175
AR Path="/5F943FFA" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943FFA" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943FFA" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5F943FFA" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F943FFA" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943FFA" Ref="#PWR034"  Part="1" 
F 0 "#PWR034" H 3925 6925 50  0001 C CNN
F 1 "GND" H 3925 7025 50  0000 C CNN
F 2 "" H 3925 7175 50  0001 C CNN
F 3 "" H 3925 7175 50  0001 C CNN
	1    3925 7175
	1    0    0    -1  
$EndComp
Connection ~ 3925 7175
$Comp
L power:GND #PWR?
U 1 1 5F944005
P 5600 7175
AR Path="/5F944005" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F944005" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F944005" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5F944005" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F944005" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F944005" Ref="#PWR038"  Part="1" 
F 0 "#PWR038" H 5600 6925 50  0001 C CNN
F 1 "GND" H 5600 7025 50  0000 C CNN
F 2 "" H 5600 7175 50  0001 C CNN
F 3 "" H 5600 7175 50  0001 C CNN
	1    5600 7175
	1    0    0    -1  
$EndComp
Text Label 4975 4450 2    50   ~ 0
V_Battery_P
Wire Wire Line
	1100 6325 1625 6325
Wire Wire Line
	1100 6800 1625 6800
Wire Notes Line
	1975 3575 1975 7075
Wire Notes Line
	1975 7075 525  7075
Wire Notes Line
	525  7075 525  3575
Wire Notes Line
	525  3575 1975 3575
$Comp
L Device:R R?
U 1 1 5F961CF4
P 1475 1725
AR Path="/5EA4867C/5F961CF4" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F961CF4" Ref="R?"  Part="1" 
AR Path="/5F913559/5F961CF4" Ref="R15"  Part="1" 
F 0 "R15" V 1268 1725 50  0000 C CNN
F 1 "330" V 1359 1725 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1405 1725 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Others_Viking-Tech-ARG03FTC3300_C217969.html" H 1475 1725 50  0001 C CNN
	1    1475 1725
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5F966531
P 1475 2350
AR Path="/5EA4867C/5F966531" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F966531" Ref="R?"  Part="1" 
AR Path="/5F913559/5F966531" Ref="R16"  Part="1" 
F 0 "R16" V 1268 2350 50  0000 C CNN
F 1 "330" V 1359 2350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1405 2350 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Others_Viking-Tech-ARG03FTC3300_C217969.html" H 1475 2350 50  0001 C CNN
	1    1475 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	1100 1725 1325 1725
Connection ~ 2475 1725
Wire Wire Line
	2475 1725 2625 1725
Wire Wire Line
	1100 2350 1325 2350
Connection ~ 2300 2350
Wire Wire Line
	2300 2350 2450 2350
Wire Wire Line
	5525 6325 6275 6325
$Comp
L power:+BATT #PWR?
U 1 1 5F9B18FF
P 4500 1850
AR Path="/5E9C1C3A/5F9B18FF" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9B18FF" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F9B18FF" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F9B18FF" Ref="#PWR036"  Part="1" 
F 0 "#PWR036" H 4500 1700 50  0001 C CNN
F 1 "+BATT" H 4515 2023 50  0000 C CNN
F 2 "" H 4500 1850 50  0001 C CNN
F 3 "" H 4500 1850 50  0001 C CNN
	1    4500 1850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4500 1850 4850 1850
$Comp
L power:+BATT #PWR?
U 1 1 5F9B686B
P 2300 900
AR Path="/5E9C1C3A/5F9B686B" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9B686B" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F9B686B" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F9B686B" Ref="#PWR030"  Part="1" 
F 0 "#PWR030" H 2300 750 50  0001 C CNN
F 1 "+BATT" H 2315 1073 50  0000 C CNN
F 2 "" H 2300 900 50  0001 C CNN
F 3 "" H 2300 900 50  0001 C CNN
	1    2300 900 
	-1   0    0    -1  
$EndComp
Connection ~ 2300 900 
Wire Wire Line
	2975 6725 2975 6325
Connection ~ 2975 6325
Wire Wire Line
	2975 6325 3925 6325
Wire Wire Line
	2975 6225 2975 6325
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5FCCDA1D
P 5925 4525
F 0 "#FLG02" H 5925 4600 50  0001 C CNN
F 1 "PWR_FLAG" H 5925 4698 50  0000 C CNN
F 2 "" H 5925 4525 50  0001 C CNN
F 3 "~" H 5925 4525 50  0001 C CNN
	1    5925 4525
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5FCCECA0
P 5925 4075
F 0 "#FLG01" H 5925 4150 50  0001 C CNN
F 1 "PWR_FLAG" H 5925 4248 50  0000 C CNN
F 2 "" H 5925 4075 50  0001 C CNN
F 3 "~" H 5925 4075 50  0001 C CNN
	1    5925 4075
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FCD4629
P 6200 5000
AR Path="/5FCD4629" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FCD4629" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FCD4629" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5FCD4629" Ref="#PWR026"  Part="1" 
F 0 "#PWR026" H 6200 4750 50  0001 C CNN
F 1 "GND" H 6200 4850 50  0000 C CNN
F 2 "" H 6200 5000 50  0001 C CNN
F 3 "" H 6200 5000 50  0001 C CNN
	1    6200 5000
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5FCD4DDE
P 6000 4625
AR Path="/5E9C1C3A/5FCD4DDE" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FCD4DDE" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5FCD4DDE" Ref="#PWR025"  Part="1" 
F 0 "#PWR025" H 6000 4475 50  0001 C CNN
F 1 "+5V" H 6015 4798 50  0000 C CNN
F 2 "" H 6000 4625 50  0001 C CNN
F 3 "" H 6000 4625 50  0001 C CNN
	1    6000 4625
	0    1    1    0   
$EndComp
Wire Wire Line
	5925 4525 5925 4625
Wire Wire Line
	5925 4625 6000 4625
$Comp
L power:+BATT #PWR?
U 1 1 5FCDACE3
P 6000 4200
AR Path="/5E9C1C3A/5FCDACE3" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5FCDACE3" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FCDACE3" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5FCDACE3" Ref="#PWR024"  Part="1" 
F 0 "#PWR024" H 6000 4050 50  0001 C CNN
F 1 "+BATT" H 6015 4373 50  0000 C CNN
F 2 "" H 6000 4200 50  0001 C CNN
F 3 "" H 6000 4200 50  0001 C CNN
	1    6000 4200
	0    1    -1   0   
$EndComp
Wire Wire Line
	5925 4075 5925 4200
Wire Wire Line
	5925 4200 6000 4200
$Comp
L power:GND #PWR?
U 1 1 5FCEB6E3
P 5025 5075
AR Path="/5FCEB6E3" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FCEB6E3" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FCEB6E3" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5FCEB6E3" Ref="#PWR040"  Part="1" 
F 0 "#PWR040" H 5025 4825 50  0001 C CNN
F 1 "GND" H 5025 4925 50  0000 C CNN
F 2 "" H 5025 5075 50  0001 C CNN
F 3 "" H 5025 5075 50  0001 C CNN
	1    5025 5075
	1    0    0    -1  
$EndComp
Wire Wire Line
	5025 4950 5025 5075
$Comp
L power:PWR_FLAG #FLG03
U 1 1 5FCF28D0
P 5925 4925
F 0 "#FLG03" H 5925 5000 50  0001 C CNN
F 1 "PWR_FLAG" H 5925 5098 50  0000 C CNN
F 2 "" H 5925 4925 50  0001 C CNN
F 3 "~" H 5925 4925 50  0001 C CNN
	1    5925 4925
	1    0    0    -1  
$EndComp
Wire Wire Line
	5925 5000 6200 5000
Wire Wire Line
	5925 4925 5925 5000
Text Notes 7425 5075 0    50   ~ 0
EN| VSNS | VI(IN2) > VI(IN1) |  OUT\n0  |<0.8V  |No  |IN1\n0  |<0.8V  |Yes  |IN2
Text Notes 8175 6300 0    50   ~ 0
1.5A\n
$Comp
L Device:C C?
U 1 1 600EBF62
P 1625 6550
AR Path="/5EA4867C/600EBF62" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/600EBF62" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/600EBF62" Ref="C?"  Part="1" 
AR Path="/5F988DA5/600EBF62" Ref="C?"  Part="1" 
AR Path="/5F913559/600EBF62" Ref="C23"  Part="1" 
F 0 "C23" H 1650 6625 50  0000 L CNN
F 1 "10 uF" V 1475 6425 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1663 6400 50  0001 C CNN
F 3 "~" H 1625 6550 50  0001 C CNN
F 4 "" H 1625 6550 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 1625 6550 50  0001 C CNN "lcsc"
	1    1625 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1625 6400 1625 6325
Connection ~ 1625 6325
Wire Wire Line
	1625 6325 2975 6325
Wire Wire Line
	1625 6700 1625 6800
Connection ~ 1625 6800
Wire Wire Line
	1625 6800 1900 6800
$Comp
L Device:C C?
U 1 1 600FA946
P 1775 4550
AR Path="/5EA4867C/600FA946" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/600FA946" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/600FA946" Ref="C?"  Part="1" 
AR Path="/5F988DA5/600FA946" Ref="C?"  Part="1" 
AR Path="/5F913559/600FA946" Ref="C24"  Part="1" 
F 0 "C24" H 1800 4625 50  0000 L CNN
F 1 "10 uF" V 1625 4425 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1813 4400 50  0001 C CNN
F 3 "~" H 1775 4550 50  0001 C CNN
F 4 "" H 1775 4550 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 1775 4550 50  0001 C CNN "lcsc"
	1    1775 4550
	1    0    0    -1  
$EndComp
Connection ~ 1475 4825
Wire Wire Line
	1775 4700 1775 4825
Wire Wire Line
	1475 4825 1775 4825
Wire Wire Line
	1775 4250 1775 4400
Wire Wire Line
	1275 4250 1550 4250
$Comp
L Device:C C?
U 1 1 6018B92A
P 2575 4550
AR Path="/5EA4867C/6018B92A" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/6018B92A" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/6018B92A" Ref="C?"  Part="1" 
AR Path="/5F988DA5/6018B92A" Ref="C?"  Part="1" 
AR Path="/5F913559/6018B92A" Ref="C28"  Part="1" 
F 0 "C28" H 2600 4625 50  0000 L CNN
F 1 "10 uF" V 2425 4425 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2613 4400 50  0001 C CNN
F 3 "~" H 2575 4550 50  0001 C CNN
F 4 "" H 2575 4550 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 2575 4550 50  0001 C CNN "lcsc"
	1    2575 4550
	1    0    0    -1  
$EndComp
Connection ~ 2575 4700
$Comp
L Device:C C?
U 1 1 6018C57C
P 1725 2600
AR Path="/5EA4867C/6018C57C" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/6018C57C" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/6018C57C" Ref="C?"  Part="1" 
AR Path="/5F913559/6018C57C" Ref="C25"  Part="1" 
F 0 "C25" H 1750 2675 50  0000 L CNN
F 1 "100 nF" V 1600 2425 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1763 2450 50  0001 C CNN
F 3 "~" H 1725 2600 50  0001 C CNN
	1    1725 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 601A13B5
P 2025 2600
AR Path="/5EA4867C/601A13B5" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/601A13B5" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/601A13B5" Ref="C?"  Part="1" 
AR Path="/5F913559/601A13B5" Ref="C26"  Part="1" 
F 0 "C26" H 2050 2675 50  0000 L CNN
F 1 "100 nF" V 1900 2425 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2063 2450 50  0001 C CNN
F 3 "~" H 2025 2600 50  0001 C CNN
	1    2025 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1725 2450 1725 2350
Wire Wire Line
	1725 2350 1625 2350
Wire Wire Line
	1725 2350 2300 2350
Connection ~ 1725 2350
Wire Wire Line
	2025 2450 2025 1725
Wire Wire Line
	2025 1725 1625 1725
Wire Wire Line
	2025 1725 2475 1725
Connection ~ 2025 1725
Wire Wire Line
	1725 2750 1725 2900
Wire Wire Line
	1725 2900 2025 2900
Connection ~ 2450 2900
Wire Wire Line
	2450 2900 2550 2900
Wire Wire Line
	2025 2750 2025 2900
Connection ~ 2025 2900
Wire Wire Line
	2025 2900 2450 2900
Wire Wire Line
	9975 6075 10200 6075
Wire Wire Line
	9950 5325 10575 5325
$Comp
L Device:C C?
U 1 1 60DA5CC8
P 2975 6875
AR Path="/5EA4867C/60DA5CC8" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/60DA5CC8" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/60DA5CC8" Ref="C?"  Part="1" 
AR Path="/5F913559/60DA5CC8" Ref="C27"  Part="1" 
F 0 "C27" H 3000 6950 50  0000 L CNN
F 1 "100 nF" V 2825 6750 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3013 6725 50  0001 C CNN
F 3 "~" H 2975 6875 50  0001 C CNN
	1    2975 6875
	1    0    0    -1  
$EndComp
Wire Wire Line
	3925 6825 3925 7175
Wire Wire Line
	2975 7175 3925 7175
Wire Wire Line
	5525 6225 6275 6225
$Comp
L WatchBorad-rescue:MAX17048G+T10-BatteryManagmentLocal-WatchBorad-rescue-WatchBorad-rescue U6
U 1 1 60DA50F9
P 3925 6325
AR Path="/60DA50F9" Ref="U6"  Part="1" 
AR Path="/5F913559/60DA50F9" Ref="U6"  Part="1" 
F 0 "U6" H 4725 6712 60  0000 C CNN
F 1 "MAX17048G+T10" H 4725 6606 60  0000 C CNN
F 2 "LocalFootprints:MAX17048G" H 4700 6575 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/2106070437_Maxim-Integrated-MAX17048G-T10_C2682616.pdf" H 4725 6606 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/PMIC-Battery-Management_Maxim-Integrated-MAX17048G-T10_C2682616.html" H 3925 6325 50  0001 C CNN "lcsc"
	1    3925 6325
	1    0    0    -1  
$EndComp
Wire Wire Line
	5525 6725 5600 6725
Wire Wire Line
	5600 6725 5600 6825
Wire Wire Line
	5525 6825 5600 6825
Connection ~ 5600 6825
Wire Wire Line
	5600 6825 5600 7175
Text HLabel 6275 6325 2    50   Input ~ 0
SCL_FG
Text HLabel 6275 6225 2    50   BiDi ~ 0
SDA_FG
Wire Wire Line
	1900 6800 1900 7175
Wire Wire Line
	1900 7175 2975 7175
Connection ~ 2975 7175
Wire Wire Line
	3925 6725 3925 6825
Connection ~ 3925 6825
Text HLabel 6275 6425 2    50   Output ~ 0
FG_OD_ALRT_N
Wire Wire Line
	5525 6425 6275 6425
Text Label 5625 6425 0    50   ~ 0
FG_OD_ALRT_N
$Comp
L WatchBorad-rescue:TPS2113APWR-PowerMuxes-WatchBorad-rescue-WatchBorad-rescue U8
U 1 1 60E7E02D
P 9150 5575
F 0 "U8" H 9150 6212 60  0000 C CNN
F 1 "TPS2113APWR" H 9150 6106 60  0000 C CNN
F 2 "LocalFootprints:TPS2115APWR" H 9150 6065 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/Texas-Instruments-TI-TPS2113APWR_C130052.pdf" H 9150 5325 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/PMIC-Power-Distribution-Switches_Texas-Instruments_TPS2113APWR_Texas-Instruments-Texas-Instruments-TPS2113APWR_C130052.html" H 9150 5575 50  0001 C CNN "lcsc"
	1    9150 5575
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 60EA81F2
P 1550 4250
AR Path="/5E9C1C3A/60EA81F2" Ref="TP?"  Part="1" 
AR Path="/5ED3F98E/60EA81F2" Ref="TP?"  Part="1" 
AR Path="/5F913559/60EA81F2" Ref="TP5"  Part="1" 
F 0 "TP5" H 1608 4322 50  0000 L CNN
F 1 "TestPoint" H 1608 4277 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 1750 4250 50  0001 C CNN
F 3 "~" H 1750 4250 50  0001 C CNN
	1    1550 4250
	1    0    0    -1  
$EndComp
Connection ~ 1550 4250
Wire Wire Line
	1550 4250 1775 4250
$Comp
L OnOffControllers:max16054azt+t U?
U 1 1 5F943E21
P 5025 1350
AR Path="/5ED3F98E/5F943E21" Ref="U?"  Part="1" 
AR Path="/5F913559/5F943E21" Ref="U7"  Part="1" 
F 0 "U7" H 5825 1737 60  0000 C CNN
F 1 "max16054azt+t" H 5825 1631 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6_Handsoldering" H 5825 1590 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Maxim-Integrated-MAX16054AZT-T_C79401.pdf" H 5025 1350 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/Interface-Specialized_Maxim-Integrated-MAX16054AZT-T_C79401.html" H 4875 1600 50  0001 C CNN "lcsc"
	1    5025 1350
	1    0    0    -1  
$EndComp
Text Notes 6800 1550 0    50   ~ 0
default level is "0"
Text Label 7775 1450 2    50   ~ 0
PWR_SW_EN_N
Connection ~ 6825 1450
Wire Wire Line
	6825 1450 7775 1450
Text Label 10525 5725 2    50   ~ 0
PWR_SW_EN_N
Wire Wire Line
	9950 5725 10525 5725
Text Notes 10025 5650 0    50   ~ 0
internal PU\n
Wire Notes Line
	600  3250 7125 3250
Wire Notes Line
	11150 1650 7550 1650
Text Notes 8925 1825 0    50   ~ 0
RTC_I2C
$Comp
L power:GND #PWR?
U 1 1 61A98A66
P 8225 4200
AR Path="/5E9B1DCE/61A98A66" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/61A98A66" Ref="#PWR07"  Part="1" 
F 0 "#PWR07" H 8225 3950 50  0001 C CNN
F 1 "GND" H 8230 4027 50  0000 C CNN
F 2 "" H 8225 4200 50  0001 C CNN
F 3 "" H 8225 4200 50  0001 C CNN
	1    8225 4200
	1    0    0    -1  
$EndComp
Wire Notes Line
	11150 1650 11150 4500
Wire Notes Line
	11150 4500 7550 4500
Wire Notes Line
	7550 1650 7550 4500
Wire Wire Line
	8225 4050 8225 4200
Wire Wire Line
	8225 4050 8375 4050
Text Label 8475 2750 0    50   ~ 0
XI_RTC
Wire Wire Line
	8475 2750 8775 2750
Text Label 10175 2050 0    50   ~ 0
XO_RTC
Wire Wire Line
	8625 2250 8775 2250
Wire Wire Line
	8775 3950 8375 3950
Wire Wire Line
	8375 3950 8375 4050
Connection ~ 8375 4050
Wire Wire Line
	8375 4050 8775 4050
Wire Wire Line
	10175 2050 10175 2250
$Comp
L M41T62Q6F:M41T62Q6F U?
U 1 1 61A98A80
P 9475 3050
AR Path="/5E9B1DCE/61A98A80" Ref="U?"  Part="1" 
AR Path="/5F913559/61A98A80" Ref="U10"  Part="1" 
F 0 "U10" H 9475 4220 50  0000 C CNN
F 1 "M41T62Q6F" H 9475 4129 50  0000 C CNN
F 2 "QFN50P300X300X100-17N" H 9475 3050 50  0001 L BNN
F 3 "https://datasheet.lcsc.com/lcsc/1806121917_STMicroelectronics-M41T62Q6F_C113207.pdf" H 9475 3050 50  0001 L BNN
F 4 "M41T62Q6F" H 9475 3050 50  0001 L BNN "MPN"
F 5 "1224441" H 9475 3050 50  0001 L BNN "OC_FARNELL"
F 6 "56P9316" H 9475 3050 50  0001 L BNN "OC_NEWARK"
F 7 "QFN-16" H 9475 3050 50  0001 L BNN "PACKAGE"
F 8 "STMICROELECTRONICS" H 9475 3050 50  0001 L BNN "SUPPLIER"
F 9 "https://lcsc.com/product-detail/Real-time-Clocks-span-style-background-color-ff0-RTC-span_STMicroelectronics-M41T62Q6F_C113207.html" H 9475 3050 50  0001 C CNN "lcsc"
	1    9475 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8775 3750 8375 3750
Wire Wire Line
	8375 3750 8375 3950
Connection ~ 8375 3950
$Comp
L power:GND #PWR?
U 1 1 61A98A89
P 10325 3600
AR Path="/5E9B1DCE/61A98A89" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/61A98A89" Ref="#PWR051"  Part="1" 
F 0 "#PWR051" H 10325 3350 50  0001 C CNN
F 1 "GND" H 10330 3427 50  0000 C CNN
F 2 "" H 10325 3600 50  0001 C CNN
F 3 "" H 10325 3600 50  0001 C CNN
	1    10325 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 61A98A8F
P 10325 3375
AR Path="/5EA4867C/61A98A8F" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/61A98A8F" Ref="C?"  Part="1" 
AR Path="/5E9B1DCE/61A98A8F" Ref="C?"  Part="1" 
AR Path="/61A98A8F" Ref="C?"  Part="1" 
AR Path="/5F913559/61A98A8F" Ref="C6"  Part="1" 
F 0 "C6" H 10500 3400 50  0000 L CNN
F 1 "100 nF" H 10450 3300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10363 3225 50  0001 C CNN
F 3 "~" H 10325 3375 50  0001 C CNN
	1    10325 3375
	1    0    0    -1  
$EndComp
Wire Wire Line
	10325 3525 10325 3600
Wire Wire Line
	10325 3225 10325 3100
Wire Wire Line
	10375 2100 10575 2100
Wire Wire Line
	10375 2250 10375 2100
Wire Wire Line
	8625 2150 8625 2250
Wire Wire Line
	8625 2100 8625 2150
Connection ~ 8625 2150
Wire Wire Line
	8325 2150 8625 2150
Wire Wire Line
	7750 2550 8325 2550
Wire Wire Line
	8325 2550 8775 2550
Connection ~ 8325 2550
Wire Wire Line
	8325 2450 8325 2550
Wire Wire Line
	10375 2550 10475 2550
Wire Wire Line
	10175 2550 10375 2550
Connection ~ 10375 2550
$Comp
L Device:R R?
U 1 1 61A98AAA
P 10375 2400
AR Path="/5E9B1DCE/61A98AAA" Ref="R?"  Part="1" 
AR Path="/5F913559/61A98AAA" Ref="R2"  Part="1" 
F 0 "R2" H 10445 2446 50  0000 L CNN
F 1 "10k" H 10445 2355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10305 2400 50  0001 C CNN
F 3 "~" H 10375 2400 50  0001 C CNN
	1    10375 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 61A98AB0
P 8325 2300
AR Path="/5E9B1DCE/61A98AB0" Ref="R?"  Part="1" 
AR Path="/5F913559/61A98AB0" Ref="R1"  Part="1" 
F 0 "R1" H 8395 2346 50  0000 L CNN
F 1 "10k" H 8395 2255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8255 2300 50  0001 C CNN
F 3 "~" H 8325 2300 50  0001 C CNN
	1    8325 2300
	1    0    0    -1  
$EndComp
Text Label 10475 2550 0    50   ~ 0
I2C_SDA_STBY
Wire Wire Line
	3150 1450 5025 1450
Text Label 7750 2550 0    50   ~ 0
I2C_SCL_STBY
Text Label 5575 6325 0    50   ~ 0
I2C_SCL_STBY
Text Label 5575 6225 0    50   ~ 0
I2C_SDA_STBY
Wire Notes Line
	7125 3250 7125 1625
Wire Notes Line
	8150 1625 8150 675 
Wire Notes Line
	600  675  8150 675 
Wire Notes Line
	7125 1625 8150 1625
$Comp
L power:+BATT #PWR?
U 1 1 61AF93FF
P 8625 2100
AR Path="/5E9C1C3A/61AF93FF" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/61AF93FF" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/61AF93FF" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/61AF93FF" Ref="#PWR012"  Part="1" 
F 0 "#PWR012" H 8625 1950 50  0001 C CNN
F 1 "+BATT" H 8640 2273 50  0000 C CNN
F 2 "" H 8625 2100 50  0001 C CNN
F 3 "" H 8625 2100 50  0001 C CNN
	1    8625 2100
	-1   0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR?
U 1 1 61AFA253
P 10575 2100
AR Path="/5E9C1C3A/61AFA253" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/61AFA253" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/61AFA253" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/61AFA253" Ref="#PWR056"  Part="1" 
F 0 "#PWR056" H 10575 1950 50  0001 C CNN
F 1 "+BATT" H 10590 2273 50  0000 C CNN
F 2 "" H 10575 2100 50  0001 C CNN
F 3 "" H 10575 2100 50  0001 C CNN
	1    10575 2100
	-1   0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR?
U 1 1 61AFA5F0
P 10325 3100
AR Path="/5E9C1C3A/61AFA5F0" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/61AFA5F0" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/61AFA5F0" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/61AFA5F0" Ref="#PWR044"  Part="1" 
F 0 "#PWR044" H 10325 2950 50  0001 C CNN
F 1 "+BATT" H 10340 3273 50  0000 C CNN
F 2 "" H 10325 3100 50  0001 C CNN
F 3 "" H 10325 3100 50  0001 C CNN
	1    10325 3100
	-1   0    0    -1  
$EndComp
$Comp
L Device:Crystal_Small Y1
U 1 1 61B0CA61
P 8200 3300
F 0 "Y1" V 8250 3500 50  0000 R CNN
F 1 "Crystal_Small" V 8150 3900 50  0000 R CNN
F 2 "Crystal:Crystal_SMD_3215-2Pin_3.2x1.5mm" H 8200 3300 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/2104141604_TKD-SF32WK32768D31T002_C271654.pdf" H 8200 3300 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Crystals_TKD-SF32WK32768D31T002_C271654.html" V 8200 3300 50  0001 C CNN "LCSC"
	1    8200 3300
	0    -1   -1   0   
$EndComp
Text Label 8400 3500 0    50   ~ 0
XO_RTC
Text Label 8400 3100 0    50   ~ 0
XI_RTC
Wire Wire Line
	8200 3200 8200 3100
Wire Wire Line
	8200 3100 8400 3100
Wire Wire Line
	8200 3400 8200 3500
Wire Wire Line
	8200 3500 8400 3500
Text Notes 7725 3500 0    50   ~ 0
32.768 KHz\n
NoConn ~ 10175 2350
NoConn ~ 8775 2450
$Comp
L Connector:TestPoint TP20
U 1 1 6186C8E6
P 6700 1220
F 0 "TP20" H 6758 1292 50  0000 L CNN
F 1 "TestPoint" H 6758 1247 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 6900 1220 50  0001 C CNN
F 3 "~" H 6900 1220 50  0001 C CNN
	1    6700 1220
	1    0    0    -1  
$EndComp
Wire Wire Line
	6625 1350 6700 1350
Wire Wire Line
	6700 1220 6700 1350
$EndSCHEMATC
