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
P 7630 1300
AR Path="/5EA4867C/5F943E27" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F943E27" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/5F943E27" Ref="C?"  Part="1" 
AR Path="/5F913559/5F943E27" Ref="C29"  Part="1" 
F 0 "C29" H 7655 1375 50  0000 L CNN
F 1 "100 nF" V 7480 1175 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7668 1150 50  0001 C CNN
F 3 "~" H 7630 1300 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 7630 1300 50  0001 C CNN "lcsc"
	1    7630 1300
	0    -1   -1   0   
$EndComp
Text Label 6940 1300 0    50   ~ 0
V_Battery_P
Wire Notes Line
	600  675  600  3250
Text Notes 5200 950  0    50   ~ 0
ON/OFF with two PB\n\n
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
F 2 "Package_TO_SOT_SMD:SOT-23" H 3125 1725 50  0001 C CNN
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
F 2 "Package_TO_SOT_SMD:SOT-23" H 3125 2350 50  0001 C CNN
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
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 2450 2650 50  0001 C CNN "lcsc"
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
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 2625 1975 50  0001 C CNN "lcsc"
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
Text Notes 4430 2130 2    50   ~ 0
PB1 && PB2 => OUT=~OUT\n
Text Label 2375 900  0    50   ~ 0
V_Battery_P
$Comp
L power:GND #PWR?
U 1 1 5F943EB2
P 6800 2740
AR Path="/5F943EB2" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943EB2" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943EB2" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943EB2" Ref="#PWR035"  Part="1" 
F 0 "#PWR035" H 6800 2490 50  0001 C CNN
F 1 "GND" H 6800 2590 50  0000 C CNN
F 2 "" H 6800 2740 50  0001 C CNN
F 3 "" H 6800 2740 50  0001 C CNN
	1    6800 2740
	1    0    0    -1  
$EndComp
Text Label 8040 5030 2    50   ~ 0
V_USB
Text Label 9750 5190 2    50   ~ 0
V_OUT_MUX
Text Notes 8225 4780 0    100  ~ 0
Power Mux\n
Wire Notes Line
	11100 4580 11100 6480
Wire Notes Line
	11100 6480 6975 6480
Wire Notes Line
	6975 6480 6975 4580
Wire Notes Line
	6975 4580 11100 4580
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
P 9820 5100
AR Path="/5EA4867C/5F943F05" Ref="TP?"  Part="1" 
AR Path="/5E9C1C3A/5F943F05" Ref="TP?"  Part="1" 
AR Path="/5ED3F98E/5F943F05" Ref="TP?"  Part="1" 
AR Path="/5F913559/5F943F05" Ref="TP12"  Part="1" 
F 0 "TP12" H 9878 5172 50  0000 L CNN
F 1 "TestPoint" H 9878 5127 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 10020 5100 50  0001 C CNN
F 3 "~" H 10020 5100 50  0001 C CNN
	1    9820 5100
	1    0    0    -1  
$EndComp
Text HLabel 9920 5190 2    50   Output ~ 0
V_OUT_MUX
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
Text Label 7420 5490 0    50   ~ 0
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
NoConn ~ 3050 4340
Text Notes 3650 3900 0    100  ~ 0
Battery charger\n
Wire Notes Line
	5275 3575 5275 5375
Wire Notes Line
	2050 5375 5275 5375
Wire Notes Line
	2050 3575 5275 3575
$Comp
L power:+BATT #PWR?
U 1 1 5F943F9D
P 2480 4420
AR Path="/5E9C1C3A/5F943F9D" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F943F9D" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F9D" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F9D" Ref="#PWR039"  Part="1" 
F 0 "#PWR039" H 2480 4270 50  0001 C CNN
F 1 "+BATT" H 2495 4593 50  0000 C CNN
F 2 "" H 2480 4420 50  0001 C CNN
F 3 "" H 2480 4420 50  0001 C CNN
	1    2480 4420
	-1   0    0    -1  
$EndComp
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
Text Label 2990 4640 2    50   ~ 0
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
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_Walsin-Tech-Corp-WR06X331JTL_C384242.html" H 1475 1725 50  0001 C CNN "lcsc"
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
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_Walsin-Tech-Corp-WR06X331JTL_C384242.html" H 1475 2350 50  0001 C CNN "lcsc"
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
P 7420 1140
AR Path="/5E9C1C3A/5F9B18FF" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9B18FF" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F9B18FF" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F9B18FF" Ref="#PWR036"  Part="1" 
F 0 "#PWR036" H 7420 990 50  0001 C CNN
F 1 "+BATT" H 7435 1313 50  0000 C CNN
F 2 "" H 7420 1140 50  0001 C CNN
F 3 "" H 7420 1140 50  0001 C CNN
	1    7420 1140
	-1   0    0    -1  
$EndComp
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
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 1725 2600 50  0001 C CNN "lcsc"
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
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 2025 2600 50  0001 C CNN "lcsc"
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
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 2975 6875 50  0001 C CNN "lcsc"
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
Text Notes 9025 5810 0    50   ~ 0
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
F 4 "https://lcsc.com/product-detail/Real-time-Clocks-span-style-background-color-ff0-RTC-span_STMicroelectronics-M41T62Q6F_C113207.html" H 9475 3050 50  0001 C CNN "lcsc"
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
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 10325 3375 50  0001 C CNN "lcsc"
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
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 10375 2400 50  0001 C CNN "lcsc"
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
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 8325 2300 50  0001 C CNN "lcsc"
	1    8325 2300
	1    0    0    -1  
$EndComp
Text Label 10475 2550 0    50   ~ 0
I2C_SDA_STBY
Text Label 7750 2550 0    50   ~ 0
I2C_SCL_STBY
Text Label 5575 6325 0    50   ~ 0
I2C_SCL_STBY
Text Label 5575 6225 0    50   ~ 0
I2C_SDA_STBY
Wire Notes Line
	8150 1625 8150 675 
Wire Notes Line
	600  675  8150 675 
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
F 4 "" V 8200 3300 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Crystals_TKD-SF32WK32768D31T002_C271654.html" H 8200 3300 50  0001 C CNN "lcsc"
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
P 3790 1490
F 0 "TP20" H 3848 1562 50  0000 L CNN
F 1 "TestPoint" H 3848 1517 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 3990 1490 50  0001 C CNN
F 3 "~" H 3990 1490 50  0001 C CNN
	1    3790 1490
	-1   0    0    1   
$EndComp
Wire Wire Line
	3150 1300 3150 1525
$Comp
L power:GND #PWR0102
U 1 1 6187DAB4
P 7880 1300
F 0 "#PWR0102" H 7880 1050 50  0001 C CNN
F 1 "GND" H 7885 1127 50  0000 C CNN
F 2 "" H 7880 1300 50  0001 C CNN
F 3 "" H 7880 1300 50  0001 C CNN
	1    7880 1300
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 6188464D
P 4110 1720
F 0 "#PWR0105" H 4110 1470 50  0001 C CNN
F 1 "GND" H 4115 1547 50  0000 C CNN
F 2 "" H 4110 1720 50  0001 C CNN
F 3 "" H 4110 1720 50  0001 C CNN
	1    4110 1720
	1    0    0    -1  
$EndComp
Wire Wire Line
	4170 1600 4110 1600
Wire Wire Line
	4110 1600 4110 1720
Wire Wire Line
	4170 1500 4100 1500
Wire Wire Line
	4100 1500 4100 1450
Wire Wire Line
	4100 1400 4170 1400
Wire Wire Line
	7420 1140 7420 1300
Connection ~ 7420 1300
Wire Wire Line
	7420 1300 7480 1300
Wire Wire Line
	7780 1300 7880 1300
$Comp
L Connector:TestPoint TP?
U 1 1 5F943E5B
P 6740 1600
AR Path="/5E9C1C3A/5F943E5B" Ref="TP?"  Part="1" 
AR Path="/5ED3F98E/5F943E5B" Ref="TP?"  Part="1" 
AR Path="/5F913559/5F943E5B" Ref="TP11"  Part="1" 
F 0 "TP11" H 6798 1672 50  0000 L CNN
F 1 "TestPoint" H 6798 1627 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.0mm" H 6940 1600 50  0001 C CNN
F 3 "~" H 6940 1600 50  0001 C CNN
	1    6740 1600
	1    0    0    -1  
$EndComp
Text Notes 6710 1700 0    50   ~ 0
default level is "0"
Text Label 7680 1600 2    50   ~ 0
PWR_SW_EN_N
Wire Wire Line
	6370 1600 6740 1600
Wire Wire Line
	6740 1600 7680 1600
Connection ~ 6740 1600
Wire Wire Line
	3790 1490 3790 1450
Wire Wire Line
	3790 1450 4100 1450
Connection ~ 4100 1450
Wire Wire Line
	4100 1450 4100 1400
$Comp
L Device:C C8
U 1 1 6189A4CE
P 6800 2490
F 0 "C8" H 6915 2536 50  0000 L CNN
F 1 "10 uF" H 6915 2445 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6838 2340 50  0001 C CNN
F 3 "~" H 6800 2490 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_YAGEO-CC0603KRX7R9BB104_C14663.html" H 6800 2490 50  0001 C CNN "lcsc"
	1    6800 2490
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F943E4B
P 6800 2100
AR Path="/5EA4867C/5F943E4B" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943E4B" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943E4B" Ref="R21"  Part="1" 
F 0 "R21" V 6700 1900 50  0000 L CNN
F 1 "10k" V 6700 2200 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6730 2100 50  0001 C CNN
F 3 "~" H 6800 2100 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 6800 2100 50  0001 C CNN "lcsc"
	1    6800 2100
	-1   0    0    1   
$EndComp
$Comp
L power:+BATT #PWR0106
U 1 1 61996A40
P 6800 1910
F 0 "#PWR0106" H 6800 1760 50  0001 C CNN
F 1 "+BATT" H 6815 2083 50  0000 C CNN
F 2 "" H 6800 1910 50  0001 C CNN
F 3 "" H 6800 1910 50  0001 C CNN
	1    6800 1910
	1    0    0    -1  
$EndComp
Wire Wire Line
	6370 1500 6450 1500
Wire Wire Line
	6800 2640 6800 2740
$Comp
L SN74LVC2G74:SN74LVC2G74-EP_DCU_8 U7
U 1 1 617F76E5
P 4170 1300
F 0 "U7" H 5270 1687 60  0000 C CNN
F 1 "SN74LVC2G74-EP_DCU_8" H 5270 1581 60  0000 C CNN
F 2 "SN74LVC2G74:SN74LVC2G74" H 5270 1540 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1809142018_Texas-Instruments-SN74LVC2G74DCUR_C7851.pdf" H 4170 1300 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/Flip-Flops_Texas-Instruments-SN74LVC2G74DCUR_C7851.html" H 4170 1300 50  0001 C CNN "lcsc"
	1    4170 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R22
U 1 1 617EFB8E
P 3690 1110
F 0 "R22" H 3760 1156 50  0000 L CNN
F 1 "10k" H 3760 1065 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3620 1110 50  0001 C CNN
F 3 "~" H 3690 1110 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 3690 1110 50  0001 C CNN "lcsc"
	1    3690 1110
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR043
U 1 1 617FFD22
P 3690 910
F 0 "#PWR043" H 3690 760 50  0001 C CNN
F 1 "+BATT" H 3705 1083 50  0000 C CNN
F 2 "" H 3690 910 50  0001 C CNN
F 3 "" H 3690 910 50  0001 C CNN
	1    3690 910 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 1300 3690 1300
Wire Wire Line
	3690 1260 3690 1300
Connection ~ 3690 1300
Wire Wire Line
	3690 1300 4170 1300
Wire Wire Line
	3690 910  3690 960 
Wire Wire Line
	6800 1910 6800 1950
Wire Wire Line
	6450 2290 6800 2290
Wire Wire Line
	6800 2290 6800 2250
Wire Wire Line
	6450 1500 6450 2290
Wire Wire Line
	6800 2290 6800 2340
Connection ~ 6800 2290
$Comp
L Device:R R25
U 1 1 61851142
P 6480 1090
F 0 "R25" H 6550 1136 50  0000 L CNN
F 1 "10k" H 6550 1045 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6410 1090 50  0001 C CNN
F 3 "~" H 6480 1090 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 6480 1090 50  0001 C CNN "lcsc"
	1    6480 1090
	1    0    0    -1  
$EndComp
Wire Wire Line
	6370 1300 7420 1300
Wire Wire Line
	6370 1400 6480 1400
$Comp
L power:+BATT #PWR059
U 1 1 61870E94
P 6480 890
F 0 "#PWR059" H 6480 740 50  0001 C CNN
F 1 "+BATT" H 6495 1063 50  0000 C CNN
F 2 "" H 6480 890 50  0001 C CNN
F 3 "" H 6480 890 50  0001 C CNN
	1    6480 890 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6480 940  6480 890 
Wire Wire Line
	6480 1400 6480 1240
$Comp
L MosfetLocal:HX2301A VT3
U 1 1 618A758C
P 8150 5590
F 0 "VT3" V 8492 5590 50  0000 C CNN
F 1 "HX2301A" V 8401 5590 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8350 5690 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/MOSFETs_HX-hengjiaxing-HX2301A_C296298.html" H 8150 5590 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/MOSFETs_HX-hengjiaxing-HX2301A_C296298.html" H 8150 5590 50  0001 C CNN "lcsc"
	1    8150 5590
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R24
U 1 1 618BB59B
P 7900 5820
F 0 "R24" V 7693 5820 50  0000 C CNN
F 1 "1K" V 7784 5820 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7830 5820 50  0001 C CNN
F 3 "~" H 7900 5820 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" V 7900 5820 50  0001 C CNN "lcsc"
	1    7900 5820
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR041
U 1 1 618BC4C0
P 7560 5810
F 0 "#PWR041" H 7560 5660 50  0001 C CNN
F 1 "+5V" H 7575 5983 50  0000 C CNN
F 2 "" H 7560 5810 50  0001 C CNN
F 3 "" H 7560 5810 50  0001 C CNN
	1    7560 5810
	1    0    0    -1  
$EndComp
$Comp
L Device:R R34
U 1 1 618BE067
P 8150 6000
F 0 "R34" H 8220 6046 50  0000 L CNN
F 1 "10K" H 8220 5955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8080 6000 50  0001 C CNN
F 3 "~" H 8150 6000 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 8150 6000 50  0001 C CNN "lcsc"
	1    8150 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 5790 8150 5820
Wire Wire Line
	8150 5820 8050 5820
Wire Wire Line
	8150 5820 8150 5850
Connection ~ 8150 5820
$Comp
L power:+BATT #PWR037
U 1 1 618D4650
P 7310 5460
F 0 "#PWR037" H 7310 5310 50  0001 C CNN
F 1 "+BATT" H 7325 5633 50  0000 C CNN
F 2 "" H 7310 5460 50  0001 C CNN
F 3 "" H 7310 5460 50  0001 C CNN
	1    7310 5460
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 5820 7560 5820
Wire Wire Line
	7560 5820 7560 5810
$Comp
L power:GND #PWR045
U 1 1 618E5FB2
P 8150 6210
F 0 "#PWR045" H 8150 5960 50  0001 C CNN
F 1 "GND" H 8155 6037 50  0000 C CNN
F 2 "" H 8150 6210 50  0001 C CNN
F 3 "" H 8150 6210 50  0001 C CNN
	1    8150 6210
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 6210 8150 6150
$Comp
L MosfetLocal:HX2301A VT5
U 1 1 618EF835
P 8950 5290
F 0 "VT5" V 9292 5290 50  0000 C CNN
F 1 "HX2301A" V 9201 5290 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9150 5390 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/MOSFETs_HX-hengjiaxing-HX2301A_C296298.html" H 8950 5290 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/MOSFETs_HX-hengjiaxing-HX2301A_C296298.html" V 8950 5290 50  0001 C CNN "lcsc"
	1    8950 5290
	0    -1   -1   0   
$EndComp
Text Label 9000 5890 0    50   ~ 0
PWR_SW_EN_N
Wire Wire Line
	8950 5490 8950 5890
Wire Wire Line
	8950 5890 9000 5890
Wire Wire Line
	8350 5490 8550 5490
Wire Wire Line
	8550 5490 8550 5190
Wire Wire Line
	8550 5190 8750 5190
Wire Wire Line
	9820 5100 9820 5190
Wire Wire Line
	9150 5190 9820 5190
Wire Wire Line
	9820 5190 9920 5190
Connection ~ 9820 5190
$Comp
L Device:D D3
U 1 1 619E667E
P 8270 5030
F 0 "D3" H 8270 4813 50  0000 C CNN
F 1 "D" H 8270 4904 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323" H 8270 5030 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1810202112_Guangdong-Hottech-1N5819WS_C191023.pdf" H 8270 5030 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Schottky-Barrier-Diodes-SBD_Guangdong-Hottech-1N5819WS_C191023.html" H 8270 5030 50  0001 C CNN "lcsc"
	1    8270 5030
	-1   0    0    1   
$EndComp
Wire Wire Line
	8420 5030 8550 5030
Wire Wire Line
	8550 5030 8550 5190
Connection ~ 8550 5190
$Comp
L power:+5V #PWR042
U 1 1 619F0EBC
P 7750 5030
F 0 "#PWR042" H 7750 4880 50  0001 C CNN
F 1 "+5V" H 7765 5203 50  0000 C CNN
F 2 "" H 7750 5030 50  0001 C CNN
F 3 "" H 7750 5030 50  0001 C CNN
	1    7750 5030
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 5030 8120 5030
Wire Wire Line
	7310 5460 7310 5490
Wire Wire Line
	7310 5490 7950 5490
$Comp
L Device:C C?
U 1 1 6018B92A
P 4620 4880
AR Path="/5EA4867C/6018B92A" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/6018B92A" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/6018B92A" Ref="C?"  Part="1" 
AR Path="/5F988DA5/6018B92A" Ref="C?"  Part="1" 
AR Path="/5F913559/6018B92A" Ref="C28"  Part="1" 
F 0 "C28" H 4645 4955 50  0000 L CNN
F 1 "10 uF" V 4470 4755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4658 4730 50  0001 C CNN
F 3 "~" H 4620 4880 50  0001 C CNN
F 4 "" H 4620 4880 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 4620 4880 50  0001 C CNN "lcsc"
	1    4620 4880
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F943F8D
P 4620 5070
AR Path="/5F943F8D" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943F8D" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F8D" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5F943F8D" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F943F8D" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F8D" Ref="#PWR032"  Part="1" 
F 0 "#PWR032" H 4620 4820 50  0001 C CNN
F 1 "GND" H 4620 4920 50  0000 C CNN
F 2 "" H 4620 5070 50  0001 C CNN
F 3 "" H 4620 5070 50  0001 C CNN
	1    4620 5070
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5F943F85
P 4620 4620
AR Path="/5E9C1C3A/5F943F85" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F943F85" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F85" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F85" Ref="#PWR033"  Part="1" 
F 0 "#PWR033" H 4620 4470 50  0001 C CNN
F 1 "+5V" H 4635 4793 50  0000 C CNN
F 2 "" H 4620 4620 50  0001 C CNN
F 3 "" H 4620 4620 50  0001 C CNN
	1    4620 4620
	1    0    0    -1  
$EndComp
Text Label 4340 4640 0    50   ~ 0
V_USB
Wire Notes Line
	2050 5375 2050 3575
Text Notes 4330 4200 0    50   ~ 0
Set fast charge\ncurrent to +-120 mA
$Comp
L Device:R R?
U 1 1 5F943F65
P 4500 4340
AR Path="/5EA4867C/5F943F65" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F943F65" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F943F65" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943F65" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943F65" Ref="R20"  Part="1" 
F 0 "R20" V 4575 4290 50  0000 L CNN
F 1 "10k" V 4425 4265 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4430 4340 50  0001 C CNN
F 3 "~" H 4500 4340 50  0001 C CNN
F 4 "https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_YAGEO-RC0603FR-0710KL_C98220.html" H 4500 4340 50  0001 C CNN "lcsc"
	1    4500 4340
	0    -1   1    0   
$EndComp
Wire Wire Line
	4620 4640 4620 4620
Wire Wire Line
	4250 4640 4620 4640
Wire Wire Line
	4620 4640 4620 4730
Connection ~ 4620 4640
Wire Wire Line
	4620 5070 4620 5030
$Comp
L power:GND #PWR040
U 1 1 61BD9CFF
P 2920 4490
F 0 "#PWR040" H 2920 4240 50  0001 C CNN
F 1 "GND" V 2925 4362 50  0000 R CNN
F 2 "" H 2920 4490 50  0001 C CNN
F 3 "" H 2920 4490 50  0001 C CNN
	1    2920 4490
	0    1    1    0   
$EndComp
Wire Wire Line
	3050 4490 2920 4490
$Comp
L BatteryManagmentLocal:ME4055A U5
U 1 1 61B5CF1E
P 3650 4190
F 0 "U5" H 3650 4405 50  0000 C CNN
F 1 "ME4055A" H 3650 4314 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 3650 4190 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/lcsc/1809291612_MICRONE-Nanjing-Micro-One-Elec-ME4055AM6G-N_C82121.pdf" H 3650 4190 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Battery-Management-ICs_MICRONE-Nanjing-Micro-One-Elec-ME4055AM6G-N_C82121.html" H 3650 4190 50  0001 C CNN "lcsc"
	1    3650 4190
	1    0    0    -1  
$EndComp
Wire Wire Line
	2480 4640 2480 4420
Wire Wire Line
	2480 4640 3050 4640
NoConn ~ 4250 4490
Wire Wire Line
	4350 4340 4250 4340
$Comp
L power:GND #PWR060
U 1 1 61C7519B
P 4830 4370
F 0 "#PWR060" H 4830 4120 50  0001 C CNN
F 1 "GND" H 4835 4197 50  0000 C CNN
F 2 "" H 4830 4370 50  0001 C CNN
F 3 "" H 4830 4370 50  0001 C CNN
	1    4830 4370
	1    0    0    -1  
$EndComp
Wire Wire Line
	4830 4370 4830 4340
Wire Wire Line
	4830 4340 4650 4340
$EndSCHEMATC
