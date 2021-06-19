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
L OnOffControllers:max16054azt+t U?
U 1 1 5F943E21
P 5600 1775
AR Path="/5ED3F98E/5F943E21" Ref="U?"  Part="1" 
AR Path="/5F913559/5F943E21" Ref="U7"  Part="1" 
F 0 "U7" H 6400 2162 60  0000 C CNN
F 1 "max16054azt+t" H 6400 2056 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6_Handsoldering" H 6400 2015 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Maxim-Integrated-MAX16054AZT-T_C79401.pdf" H 5600 1775 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/Interface-Specialized_Maxim-Integrated-MAX16054AZT-T_C79401.html" H 5450 2025 50  0001 C CNN "lcsc"
	1    5600 1775
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F943E27
P 5425 2600
AR Path="/5EA4867C/5F943E27" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F943E27" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/5F943E27" Ref="C?"  Part="1" 
AR Path="/5F913559/5F943E27" Ref="C29"  Part="1" 
F 0 "C29" H 5450 2675 50  0000 L CNN
F 1 "100 nF" V 5275 2475 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5463 2450 50  0001 C CNN
F 3 "~" H 5425 2600 50  0001 C CNN
	1    5425 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 2275 5425 2275
Wire Wire Line
	5425 2275 5425 2450
Wire Wire Line
	7200 2275 7450 2275
$Comp
L MosfetLocal:HX2301A VT?
U 1 1 5F943E30
P 8550 1775
AR Path="/5ED3F98E/5F943E30" Ref="VT?"  Part="1" 
AR Path="/5F913559/5F943E30" Ref="VT3"  Part="1" 
F 0 "VT3" H 8755 1729 50  0000 L CNN
F 1 "HX2301A" H 8755 1820 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 8750 1875 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/MOSFET_HX-hengjiaxing-HX2301A_C296298.html" H 8550 1775 50  0001 C CNN
	1    8550 1775
	1    0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5F943E36
P 8025 1150
AR Path="/5EA4867C/5F943E36" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943E36" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943E36" Ref="R25"  Part="1" 
F 0 "R25" H 8095 1196 50  0000 L CNN
F 1 "10k" H 8095 1105 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7955 1150 50  0001 C CNN
F 3 "~" H 8025 1150 50  0001 C CNN
	1    8025 1150
	1    0    0    -1  
$EndComp
Text Label 5150 2275 0    50   ~ 0
V_Battery_P
Connection ~ 5425 2275
Text Label 7500 975  0    50   ~ 0
V_Battery_P
Wire Wire Line
	8025 975  8025 1000
Wire Wire Line
	8025 1300 8025 1775
Connection ~ 8025 1775
Wire Wire Line
	8025 1775 8350 1775
Wire Wire Line
	7200 1775 7575 1775
Wire Wire Line
	8025 975  8250 975 
Wire Wire Line
	8650 975  8650 1575
Text Label 9425 2100 2    50   ~ 0
V_Battery_P_SW
Wire Wire Line
	8650 1975 8650 2100
Wire Wire Line
	8650 2100 9425 2100
Wire Wire Line
	5600 1775 5225 1775
$Comp
L Device:R R?
U 1 1 5F943E4B
P 5075 1775
AR Path="/5EA4867C/5F943E4B" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943E4B" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943E4B" Ref="R21"  Part="1" 
F 0 "R21" V 4975 1575 50  0000 L CNN
F 1 "10k" V 4975 1875 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5005 1775 50  0001 C CNN
F 3 "~" H 5075 1775 50  0001 C CNN
	1    5075 1775
	0    1    1    0   
$EndComp
Wire Wire Line
	4925 1775 4675 1775
NoConn ~ 7200 1875
Wire Wire Line
	7500 975  8025 975 
Connection ~ 8025 975 
Text Notes 5150 2000 0    50   ~ 0
Int 63KOhm PU\n
Wire Notes Line
	1175 600  1175 3175
Wire Notes Line
	1175 3175 10350 3175
Wire Notes Line
	10350 3175 10350 600 
Wire Notes Line
	9950 600  1175 600 
Text Notes 5775 875  0    50   ~ 0
ON/OFF with two PB\n\n
$Comp
L Connector:TestPoint TP?
U 1 1 5F943E5B
P 7575 1775
AR Path="/5E9C1C3A/5F943E5B" Ref="TP?"  Part="1" 
AR Path="/5ED3F98E/5F943E5B" Ref="TP?"  Part="1" 
AR Path="/5F913559/5F943E5B" Ref="TP11"  Part="1" 
F 0 "TP11" H 7633 1847 50  0000 L CNN
F 1 "TestPoint" H 7633 1802 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 7775 1775 50  0001 C CNN
F 3 "~" H 7775 1775 50  0001 C CNN
	1    7575 1775
	1    0    0    -1  
$EndComp
Text HLabel 1675 1650 0    50   Output ~ 0
PB_1_MCU
Text HLabel 1675 2275 0    50   Output ~ 0
PB_2_MCU
$Comp
L MosfetLocal:SL2300 VT?
U 1 1 5F943E66
P 3700 1650
AR Path="/5EA4867C/5F943E66" Ref="VT?"  Part="1" 
AR Path="/5ED3F98E/5F943E66" Ref="VT?"  Part="1" 
AR Path="/5F913559/5F943E66" Ref="VT1"  Part="1" 
F 0 "VT1" H 3829 1650 50  0000 L CNN
F 1 "SL2300" H 3830 1605 50  0001 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3700 1650 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1906271838_SLKORMICRO-Elec-SL2300_C350314.pdf" H 3700 1650 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/MOSFET_Slkor-SLKORMICRO-Elec-SL2300_C350314.html" H 3700 1650 50  0001 C CNN "lcsc"
	1    3700 1650
	1    0    0    -1  
$EndComp
$Comp
L MosfetLocal:SL2300 VT?
U 1 1 5F943E6D
P 3700 2275
AR Path="/5EA4867C/5F943E6D" Ref="VT?"  Part="1" 
AR Path="/5ED3F98E/5F943E6D" Ref="VT?"  Part="1" 
AR Path="/5F913559/5F943E6D" Ref="VT2"  Part="1" 
F 0 "VT2" H 3829 2275 50  0000 L CNN
F 1 "SL2300" H 3830 2230 50  0001 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3700 2275 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1906271838_SLKORMICRO-Elec-SL2300_C350314.pdf" H 3700 2275 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/MOSFET_Slkor-SLKORMICRO-Elec-SL2300_C350314.html" H 3700 2275 50  0001 C CNN "lcsc"
	1    3700 2275
	1    0    0    -1  
$EndComp
Wire Wire Line
	3725 1850 3725 2075
$Comp
L Switch:SW_Push SW?
U 1 1 5F943E75
P 3050 1075
AR Path="/5ED3F98E/5F943E75" Ref="SW?"  Part="1" 
AR Path="/5F913559/5F943E75" Ref="SW2"  Part="1" 
F 0 "SW2" V 3050 1350 50  0000 C CNN
F 1 "SW_Push" H 3050 1000 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_B3U-3000P-B" H 3050 1275 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Omron-Electronics-B3U-3000PM-B_C306884.pdf" H 3050 1275 50  0001 C CNN
F 4 "https://lcsc.com/products/Tactile-Switches_427.html?q=b3u-3000" H 3050 1075 50  0001 C CNN "lcsc"
	1    3050 1075
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5F943E7C
P 2875 1950
AR Path="/5ED3F98E/5F943E7C" Ref="SW?"  Part="1" 
AR Path="/5F913559/5F943E7C" Ref="SW1"  Part="1" 
F 0 "SW1" V 2925 2125 50  0000 C CNN
F 1 "SW_Push" H 2875 1900 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_B3U-3000P-B" H 2875 2150 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Omron-Electronics-B3U-3000PM-B_C306884.pdf" H 2875 2150 50  0001 C CNN
F 4 "https://lcsc.com/products/Tactile-Switches_427.html?q=b3u-3000" H 2875 1950 50  0001 C CNN "lcsc"
	1    2875 1950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5F943E82
P 3025 2575
AR Path="/5EA4867C/5F943E82" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943E82" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943E82" Ref="R17"  Part="1" 
F 0 "R17" H 3150 2550 50  0000 L CNN
F 1 "10k" H 3100 2650 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2955 2575 50  0001 C CNN
F 3 "~" H 3025 2575 50  0001 C CNN
	1    3025 2575
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5F943E88
P 3200 1900
AR Path="/5EA4867C/5F943E88" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943E88" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943E88" Ref="R18"  Part="1" 
F 0 "R18" H 3000 1850 50  0000 L CNN
F 1 "10k" H 3000 1975 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3130 1900 50  0001 C CNN
F 3 "~" H 3200 1900 50  0001 C CNN
	1    3200 1900
	-1   0    0    1   
$EndComp
Wire Wire Line
	3200 1750 3200 1650
Wire Wire Line
	3200 1650 3425 1650
Wire Wire Line
	3025 2425 3025 2275
Wire Wire Line
	3025 2275 3425 2275
Wire Wire Line
	3200 2050 3200 2825
Wire Wire Line
	3200 2825 3125 2825
Wire Wire Line
	3025 2825 3025 2725
$Comp
L power:GND #PWR?
U 1 1 5F943E95
P 3125 2875
AR Path="/5F943E95" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943E95" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943E95" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943E95" Ref="#PWR031"  Part="1" 
F 0 "#PWR031" H 3125 2625 50  0001 C CNN
F 1 "GND" H 3125 2725 50  0000 C CNN
F 2 "" H 3125 2875 50  0001 C CNN
F 3 "" H 3125 2875 50  0001 C CNN
	1    3125 2875
	1    0    0    -1  
$EndComp
Wire Wire Line
	3125 2875 3125 2825
Connection ~ 3125 2825
Wire Wire Line
	3725 2475 3725 2825
Wire Wire Line
	3725 2825 3200 2825
Connection ~ 3200 2825
Wire Wire Line
	2875 2275 2875 2150
Connection ~ 3025 2275
Wire Wire Line
	3050 1275 3050 1650
Connection ~ 3200 1650
Wire Wire Line
	2875 825  3050 825 
Wire Wire Line
	3050 825  3050 875 
Wire Wire Line
	2875 825  2875 1750
Wire Wire Line
	3725 1450 3725 1375
Wire Wire Line
	3725 1375 4375 1375
Wire Wire Line
	4375 1375 4375 1875
Wire Wire Line
	4375 1875 5600 1875
Text Notes 4950 2100 2    50   ~ 0
PB1 && PB2 => OUT=~OUT\n
Text Label 2950 825  0    50   ~ 0
V_Battery_P
$Comp
L power:GND #PWR?
U 1 1 5F943EB2
P 4675 1775
AR Path="/5F943EB2" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943EB2" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943EB2" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943EB2" Ref="#PWR035"  Part="1" 
F 0 "#PWR035" H 4675 1525 50  0001 C CNN
F 1 "GND" H 4675 1625 50  0000 C CNN
F 2 "" H 4675 1775 50  0001 C CNN
F 3 "" H 4675 1775 50  0001 C CNN
	1    4675 1775
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F943EB8
P 5425 2875
AR Path="/5F943EB8" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943EB8" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943EB8" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943EB8" Ref="#PWR037"  Part="1" 
F 0 "#PWR037" H 5425 2625 50  0001 C CNN
F 1 "GND" H 5425 2725 50  0000 C CNN
F 2 "" H 5425 2875 50  0001 C CNN
F 3 "" H 5425 2875 50  0001 C CNN
	1    5425 2875
	1    0    0    -1  
$EndComp
Wire Wire Line
	5425 2750 5425 2875
$Comp
L power:GND #PWR?
U 1 1 5F943EBF
P 7450 2275
AR Path="/5F943EBF" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943EBF" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943EBF" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943EBF" Ref="#PWR043"  Part="1" 
F 0 "#PWR043" H 7450 2025 50  0001 C CNN
F 1 "GND" H 7450 2125 50  0000 C CNN
F 2 "" H 7450 2275 50  0001 C CNN
F 3 "" H 7450 2275 50  0001 C CNN
	1    7450 2275
	1    0    0    -1  
$EndComp
$Comp
L PowerMuxes:TPS2115APWR U?
U 1 1 5F943EC6
P 8375 4425
AR Path="/5E9C1C3A/5F943EC6" Ref="U?"  Part="1" 
AR Path="/5ED3F98E/5F943EC6" Ref="U?"  Part="1" 
AR Path="/5F913559/5F943EC6" Ref="U8"  Part="1" 
F 0 "U8" H 8375 4950 60  0000 C CNN
F 1 "TPS2115APWR" H 8375 4825 60  0000 C CNN
F 2 "Housings_SSOP:TSSOP-8_4.4x3mm_Pitch0.65mm" H 8375 4915 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1809131529_Texas-Instruments-TPS2115APWR_C70287.pdf" H 8375 4175 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/Switching-Controllers_Texas-Instruments_TPS2115APWR_Texas-Instruments-Texas-Instruments-TPS2115APWR_C70287.html" H 8375 4425 50  0001 C CNN "lcsc"
	1    8375 4425
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F943ECC
P 7250 4925
AR Path="/5EA4867C/5F943ECC" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F943ECC" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943ECC" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943ECC" Ref="R24"  Part="1" 
F 0 "R24" V 7043 4925 50  0000 C CNN
F 1 "330" V 7134 4925 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7180 4925 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Others_Viking-Tech-ARG03FTC3300_C217969.html" H 7250 4925 50  0001 C CNN
	1    7250 4925
	0    1    1    0   
$EndComp
Text Label 7425 4925 0    50   ~ 0
Rlim
Wire Wire Line
	9200 4675 9175 4675
Wire Wire Line
	9200 4925 9175 4925
Wire Wire Line
	9200 4675 9200 4925
Wire Wire Line
	9200 4925 9425 4925
Connection ~ 9200 4925
NoConn ~ 9175 4575
Text Notes 9225 4575 0    50   ~ 0
Internal pull-up\n
$Comp
L Device:C C?
U 1 1 5F943EDA
P 6475 4625
AR Path="/5EA4867C/5F943EDA" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F943EDA" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/5F943EDA" Ref="C?"  Part="1" 
AR Path="/5F913559/5F943EDA" Ref="C30"  Part="1" 
F 0 "C30" H 6500 4700 50  0000 L CNN
F 1 "100 nF" V 6325 4500 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6513 4475 50  0001 C CNN
F 3 "~" H 6475 4625 50  0001 C CNN
	1    6475 4625
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F943EE0
P 7075 4625
AR Path="/5EA4867C/5F943EE0" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F943EE0" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/5F943EE0" Ref="C?"  Part="1" 
AR Path="/5F913559/5F943EE0" Ref="C31"  Part="1" 
F 0 "C31" H 7100 4700 50  0000 L CNN
F 1 "100 nF" V 6950 4450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7113 4475 50  0001 C CNN
F 3 "~" H 7075 4625 50  0001 C CNN
	1    7075 4625
	1    0    0    -1  
$EndComp
Wire Wire Line
	6475 4475 6475 4375
Wire Wire Line
	6475 4775 6475 4925
Wire Wire Line
	7075 4775 7075 4925
Text Label 6875 4375 0    50   ~ 0
V_USB
NoConn ~ 9175 4275
Text Label 9725 4175 2    50   ~ 0
V_OUT_MUX
Text Notes 7500 3600 0    100  ~ 0
Power Mux\n
Wire Notes Line
	10375 3400 10375 5300
Wire Notes Line
	10375 5300 6250 5300
Wire Notes Line
	6250 5300 6250 3400
Wire Notes Line
	6250 3400 10375 3400
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
Wire Wire Line
	9175 4175 9800 4175
$Comp
L Connector:TestPoint TP?
U 1 1 5F943F05
P 9800 4075
AR Path="/5EA4867C/5F943F05" Ref="TP?"  Part="1" 
AR Path="/5E9C1C3A/5F943F05" Ref="TP?"  Part="1" 
AR Path="/5ED3F98E/5F943F05" Ref="TP?"  Part="1" 
AR Path="/5F913559/5F943F05" Ref="TP12"  Part="1" 
F 0 "TP12" H 9858 4147 50  0000 L CNN
F 1 "TestPoint" H 9858 4102 50  0001 L CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 10000 4075 50  0001 C CNN
F 3 "~" H 10000 4075 50  0001 C CNN
	1    9800 4075
	1    0    0    -1  
$EndComp
Text HLabel 9875 4175 2    50   Output ~ 0
V_OUT_MUX
Connection ~ 9800 4175
Wire Wire Line
	9800 4175 9875 4175
Wire Wire Line
	9800 4075 9800 4175
$Comp
L Device:D_TVS D?
U 1 1 5F943F10
P 1275 4525
AR Path="/5E9C1C3A/5F943F10" Ref="D?"  Part="1" 
AR Path="/5ED3F98E/5F943F10" Ref="D?"  Part="1" 
AR Path="/5F913559/5F943F10" Ref="D1"  Part="1" 
F 0 "D1" V 1229 4604 50  0000 L CNN
F 1 "D_TVS" V 1320 4604 50  0000 L CNN
F 2 "" H 1275 4525 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/2003282109_PN-SILICON-PESDU0521P1_C499647.pdf" H 1275 4525 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/TVS_PN-SILICON-PESDU0521P1_C499647.html" V 1275 4525 50  0001 C CNN "lcsc"
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
	7025 4475 7075 4475
Wire Wire Line
	6475 4375 6625 4375
Wire Wire Line
	7400 4925 7575 4925
Connection ~ 7075 4475
Wire Wire Line
	7075 4475 7575 4475
Connection ~ 7075 4925
Wire Wire Line
	7075 4925 7100 4925
Wire Wire Line
	6475 4925 6875 4925
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
P 6625 4375
AR Path="/5E9C1C3A/5F943F2C" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F2C" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F2C" Ref="#PWR041"  Part="1" 
F 0 "#PWR041" H 6625 4225 50  0001 C CNN
F 1 "+5V" H 6640 4548 50  0000 C CNN
F 2 "" H 6625 4375 50  0001 C CNN
F 3 "" H 6625 4375 50  0001 C CNN
	1    6625 4375
	1    0    0    -1  
$EndComp
Connection ~ 6625 4375
Wire Wire Line
	6625 4375 7575 4375
Connection ~ 7575 1775
Wire Wire Line
	7575 1775 8025 1775
$Comp
L Device:Battery_Cell BT?
U 1 1 5F943F36
P 1100 6650
AR Path="/5E9C1C3A/5F943F36" Ref="BT?"  Part="1" 
AR Path="/5ED3F98E/5F943F36" Ref="BT?"  Part="1" 
AR Path="/5F913559/5F943F36" Ref="BT1"  Part="1" 
F 0 "BT1" H 1218 6746 50  0000 L CNN
F 1 "Battery_Cell" H 1218 6655 50  0000 L CNN
F 2 "Battery_Holders:Keystone_107_1x23mm-CoinCell" V 1100 6710 50  0001 C CNN
F 3 "https://aliexpress.ru/item/33000396152.html?spm=a2g0o.productlist.0.0.43416af464CXwu&algo_pvid=e6706777-cde6-4668-9867-8799ba4921bb&algo_expid=e6706777-cde6-4668-9867-8799ba4921bb-0&btsid=0b8b037215874644191236041ea897&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_" V 1100 6710 50  0001 C CNN
	1    1100 6650
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1100 6450 1100 6325
Wire Wire Line
	1100 6750 1100 6800
Text Label 7025 4475 0    50   ~ 0
V_Battery_P_SW
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
P 6875 4925
AR Path="/5F943F46" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943F46" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F46" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F46" Ref="#PWR042"  Part="1" 
F 0 "#PWR042" H 6875 4675 50  0001 C CNN
F 1 "GND" H 6875 4775 50  0000 C CNN
F 2 "" H 6875 4925 50  0001 C CNN
F 3 "" H 6875 4925 50  0001 C CNN
	1    6875 4925
	1    0    0    -1  
$EndComp
Connection ~ 6875 4925
Wire Wire Line
	6875 4925 7075 4925
$Comp
L power:GND #PWR?
U 1 1 5F943F4E
P 9425 4925
AR Path="/5F943F4E" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943F4E" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F4E" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F4E" Ref="#PWR045"  Part="1" 
F 0 "#PWR045" H 9425 4675 50  0001 C CNN
F 1 "GND" H 9425 4775 50  0000 C CNN
F 2 "" H 9425 4925 50  0001 C CNN
F 3 "" H 9425 4925 50  0001 C CNN
	1    9425 4925
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
	5350 4475 5800 4475
$Comp
L BatteryManagmentLocal:BQ21040DBVT U?
U 1 1 5F943F5D
P 3750 4375
AR Path="/5E9C1C3A/5F943F5D" Ref="U?"  Part="1" 
AR Path="/5F7F86D0/5F943F5D" Ref="U?"  Part="1" 
AR Path="/5ED3F98E/5F943F5D" Ref="U?"  Part="1" 
AR Path="/5F913559/5F943F5D" Ref="U5"  Part="1" 
F 0 "U5" H 4550 4762 60  0000 C CNN
F 1 "BQ21040DBVT" H 4550 4656 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6" H 4550 4615 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Texas-Instruments-TI-BQ21040DBVR_C202311.pdf" H 4550 4656 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/PMIC-Battery-Management_Texas-Instruments_BQ21040DBVR_Texas-Instruments-Texas-Instruments-BQ21040DBVR_C202311.html" H 3750 4375 50  0001 C CNN "lcsc"
	1    3750 4375
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 4225 3750 4275
Wire Wire Line
	3750 4525 3750 4475
$Comp
L Device:R R?
U 1 1 5F943F65
P 3525 4675
AR Path="/5EA4867C/5F943F65" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F943F65" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F943F65" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943F65" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943F65" Ref="R20"  Part="1" 
F 0 "R20" V 3600 4625 50  0000 L CNN
F 1 "10k" V 3450 4600 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3455 4675 50  0001 C CNN
F 3 "~" H 3525 4675 50  0001 C CNN
	1    3525 4675
	0    1    -1   0   
$EndComp
Wire Wire Line
	3750 4675 3675 4675
Wire Wire Line
	3375 4675 3350 4675
Text Notes 3300 4950 0    50   ~ 0
Set fast charge\ncurrent to 54 mA
NoConn ~ 5350 4675
Wire Wire Line
	3350 4525 3750 4525
Wire Wire Line
	3350 4225 3425 4225
Text Notes 4425 3725 0    100  ~ 0
Battery charger\n
Wire Notes Line
	2825 5200 2825 3400
$Comp
L Device:R R?
U 1 1 5F943F7B
P 5800 4625
AR Path="/5EA4867C/5F943F7B" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F943F7B" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F943F7B" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943F7B" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943F7B" Ref="R23"  Part="1" 
F 0 "R23" H 5575 4600 50  0000 L CNN
F 1 "10k" V 5875 4550 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5730 4625 50  0001 C CNN
F 3 "~" H 5800 4625 50  0001 C CNN
	1    5800 4625
	1    0    0    1   
$EndComp
Text Label 3525 4225 0    50   ~ 0
V_USB
Wire Notes Line
	6050 3400 6050 5200
Wire Notes Line
	2825 5200 6050 5200
Wire Notes Line
	2825 3400 6050 3400
$Comp
L power:+5V #PWR?
U 1 1 5F943F85
P 3425 4225
AR Path="/5E9C1C3A/5F943F85" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F943F85" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F85" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F85" Ref="#PWR033"  Part="1" 
F 0 "#PWR033" H 3425 4075 50  0001 C CNN
F 1 "+5V" H 3440 4398 50  0000 C CNN
F 2 "" H 3425 4225 50  0001 C CNN
F 3 "" H 3425 4225 50  0001 C CNN
	1    3425 4225
	1    0    0    -1  
$EndComp
Connection ~ 3425 4225
Wire Wire Line
	3425 4225 3750 4225
$Comp
L power:GND #PWR?
U 1 1 5F943F8D
P 3150 4675
AR Path="/5F943F8D" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F943F8D" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F8D" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5F943F8D" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F943F8D" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F8D" Ref="#PWR032"  Part="1" 
F 0 "#PWR032" H 3150 4425 50  0001 C CNN
F 1 "GND" H 3150 4525 50  0000 C CNN
F 2 "" H 3150 4675 50  0001 C CNN
F 3 "" H 3150 4675 50  0001 C CNN
	1    3150 4675
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 4525 3350 4675
Connection ~ 3350 4675
Wire Wire Line
	3350 4675 3150 4675
$Comp
L power:+BATT #PWR?
U 1 1 5F943F9D
P 5800 4175
AR Path="/5E9C1C3A/5F943F9D" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F943F9D" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F943F9D" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F943F9D" Ref="#PWR039"  Part="1" 
F 0 "#PWR039" H 5800 4025 50  0001 C CNN
F 1 "+BATT" H 5815 4348 50  0000 C CNN
F 2 "" H 5800 4175 50  0001 C CNN
F 3 "" H 5800 4175 50  0001 C CNN
	1    5800 4175
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5800 4275 5800 4175
Wire Wire Line
	5350 4275 5800 4275
Text Label 2650 6325 2    50   ~ 0
V_Battery_P
$Comp
L BatteryManagmentLocal:STC3100IQT U?
U 1 1 5F943FA7
P 4475 6375
AR Path="/5E9C1C3A/5F943FA7" Ref="U?"  Part="1" 
AR Path="/5F7F86D0/5F943FA7" Ref="U?"  Part="1" 
AR Path="/5ED3F98E/5F943FA7" Ref="U?"  Part="1" 
AR Path="/5F913559/5F943FA7" Ref="U6"  Part="1" 
F 0 "U6" H 4475 6790 50  0000 C CNN
F 1 "STC3100IQT" H 4475 6675 50  0000 C CNN
F 2 "Housings_DFN_QFN:DFN-8-1EP_3x3mm_Pitch0.5mm" H 4600 7150 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1804172029_STMicroelectronics-STC3100IQT_C155587.pdf" H 4475 6375 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/_STMicroelectronics_STC3100IQT_STC3100IQT_C155587.html" H 4850 7000 50  0001 C CNN "lcsc"
	1    4475 6375
	-1   0    0    -1  
$EndComp
Text Label 2225 6425 0    50   ~ 0
V_Battery_N
Wire Wire Line
	3400 6425 3400 6700
Wire Wire Line
	3775 6525 3775 7175
Wire Wire Line
	3400 7000 3400 7175
Text Notes 3800 7475 2    50   ~ 0
GND (pin 5) should be directly \nconnected to negedge resistor\npin that is connected to GND plane 
Wire Wire Line
	3925 6225 2975 6225
Wire Wire Line
	2975 7025 2975 7175
Connection ~ 3400 7175
Wire Wire Line
	2975 7175 3400 7175
NoConn ~ 5025 6225
$Comp
L Device:R R?
U 1 1 5F943FCB
P 5300 6325
AR Path="/5EA4867C/5F943FCB" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F943FCB" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F943FCB" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943FCB" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943FCB" Ref="R22"  Part="1" 
F 0 "R22" V 5125 6275 50  0000 L CNN
F 1 "200k 0.1%" V 5200 6125 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5230 6325 50  0001 C CNN
F 3 "~" H 5300 6325 50  0001 C CNN
	1    5300 6325
	0    1    1    0   
$EndComp
Wire Wire Line
	5150 6325 5025 6325
Wire Wire Line
	5450 6325 5600 6325
Wire Wire Line
	3775 7175 3400 7175
Wire Wire Line
	3775 6525 3925 6525
Text Notes 4725 6850 2    50   ~ 0
9 pin directly \nto plan GND\n
Text Notes 4550 5775 2    100  ~ 0
Fuel gauge
Wire Notes Line
	2000 5500 2000 7775
$Comp
L Device:R R?
U 1 1 5F943FE9
P 3400 6850
AR Path="/5EA4867C/5F943FE9" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F943FE9" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F943FE9" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F943FE9" Ref="R?"  Part="1" 
AR Path="/5F913559/5F943FE9" Ref="R19"  Part="1" 
F 0 "R19" H 3475 6800 50  0000 L CNN
F 1 "0.15 Ohm" V 3300 6675 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3330 6850 50  0001 C CNN
F 3 "~" H 3400 6850 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Chip-Resistor-Surface-Mount_UNI-ROYAL-Uniroyal-Elec-0603WAF150LT5E_C45879.html" V 3400 6850 50  0001 C CNN "lcsc"
	1    3400 6850
	-1   0    0    1   
$EndComp
Text Label 6000 6425 0    50   ~ 0
SDA_FG
Text Label 6000 6525 0    50   ~ 0
SCL_FG
Wire Notes Line
	2000 5500 6925 5500
Wire Notes Line
	2000 7775 6925 7775
Wire Notes Line
	6925 5500 6925 7775
Text HLabel 6275 6425 2    50   BiDi ~ 0
SDA_FG
Text HLabel 6275 6525 2    50   Input ~ 0
SCL_FG
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
Connection ~ 3775 7175
Wire Wire Line
	3925 6600 3925 7175
Connection ~ 3925 7175
Wire Wire Line
	3775 7175 3925 7175
Wire Wire Line
	5600 6325 5600 7175
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
Wire Wire Line
	1900 6425 3400 6425
Text Label 5750 4275 2    50   ~ 0
V_Battery_P
Wire Wire Line
	1100 6325 1625 6325
Wire Wire Line
	1100 6800 1625 6800
Wire Wire Line
	1900 6800 1900 6425
Wire Notes Line
	1975 3575 1975 7075
Wire Notes Line
	1975 7075 525  7075
Wire Notes Line
	525  7075 525  3575
Wire Notes Line
	525  3575 1975 3575
Wire Wire Line
	3400 6425 3925 6425
Connection ~ 3400 6425
$Comp
L Device:R R?
U 1 1 5F961CF4
P 2050 1650
AR Path="/5EA4867C/5F961CF4" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F961CF4" Ref="R?"  Part="1" 
AR Path="/5F913559/5F961CF4" Ref="R15"  Part="1" 
F 0 "R15" V 1843 1650 50  0000 C CNN
F 1 "330" V 1934 1650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1980 1650 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Others_Viking-Tech-ARG03FTC3300_C217969.html" H 2050 1650 50  0001 C CNN
	1    2050 1650
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5F966531
P 2050 2275
AR Path="/5EA4867C/5F966531" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F966531" Ref="R?"  Part="1" 
AR Path="/5F913559/5F966531" Ref="R16"  Part="1" 
F 0 "R16" V 1843 2275 50  0000 C CNN
F 1 "330" V 1934 2275 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1980 2275 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Others_Viking-Tech-ARG03FTC3300_C217969.html" H 2050 2275 50  0001 C CNN
	1    2050 2275
	0    1    1    0   
$EndComp
Wire Wire Line
	1675 1650 1900 1650
Connection ~ 3050 1650
Wire Wire Line
	3050 1650 3200 1650
Wire Wire Line
	1675 2275 1900 2275
Connection ~ 2875 2275
Wire Wire Line
	2875 2275 3025 2275
Wire Wire Line
	5025 6425 6275 6425
Wire Wire Line
	5025 6525 6275 6525
Text Notes 5725 6200 0    50   ~ 0
PUs next to MCU\n
$Comp
L power:+BATT #PWR?
U 1 1 5F9B1170
P 8250 975
AR Path="/5E9C1C3A/5F9B1170" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9B1170" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F9B1170" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F9B1170" Ref="#PWR044"  Part="1" 
F 0 "#PWR044" H 8250 825 50  0001 C CNN
F 1 "+BATT" H 8265 1148 50  0000 C CNN
F 2 "" H 8250 975 50  0001 C CNN
F 3 "" H 8250 975 50  0001 C CNN
	1    8250 975 
	-1   0    0    -1  
$EndComp
Connection ~ 8250 975 
Wire Wire Line
	8250 975  8650 975 
$Comp
L power:+BATT #PWR?
U 1 1 5F9B18FF
P 5075 2275
AR Path="/5E9C1C3A/5F9B18FF" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9B18FF" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F9B18FF" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F9B18FF" Ref="#PWR036"  Part="1" 
F 0 "#PWR036" H 5075 2125 50  0001 C CNN
F 1 "+BATT" H 5090 2448 50  0000 C CNN
F 2 "" H 5075 2275 50  0001 C CNN
F 3 "" H 5075 2275 50  0001 C CNN
	1    5075 2275
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5075 2275 5425 2275
$Comp
L power:+BATT #PWR?
U 1 1 5F9B686B
P 2875 825
AR Path="/5E9C1C3A/5F9B686B" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F9B686B" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F9B686B" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5F9B686B" Ref="#PWR030"  Part="1" 
F 0 "#PWR030" H 2875 675 50  0001 C CNN
F 1 "+BATT" H 2890 998 50  0000 C CNN
F 2 "" H 2875 825 50  0001 C CNN
F 3 "" H 2875 825 50  0001 C CNN
	1    2875 825 
	-1   0    0    -1  
$EndComp
Connection ~ 2875 825 
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
P 675 2925
F 0 "#FLG02" H 675 3000 50  0001 C CNN
F 1 "PWR_FLAG" H 675 3098 50  0000 C CNN
F 2 "" H 675 2925 50  0001 C CNN
F 3 "~" H 675 2925 50  0001 C CNN
	1    675  2925
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5FCCECA0
P 675 2475
F 0 "#FLG01" H 675 2550 50  0001 C CNN
F 1 "PWR_FLAG" H 675 2648 50  0000 C CNN
F 2 "" H 675 2475 50  0001 C CNN
F 3 "~" H 675 2475 50  0001 C CNN
	1    675  2475
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FCD4629
P 950 3400
AR Path="/5FCD4629" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FCD4629" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FCD4629" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5FCD4629" Ref="#PWR026"  Part="1" 
F 0 "#PWR026" H 950 3150 50  0001 C CNN
F 1 "GND" H 950 3250 50  0000 C CNN
F 2 "" H 950 3400 50  0001 C CNN
F 3 "" H 950 3400 50  0001 C CNN
	1    950  3400
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5FCD4DDE
P 750 3025
AR Path="/5E9C1C3A/5FCD4DDE" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FCD4DDE" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5FCD4DDE" Ref="#PWR025"  Part="1" 
F 0 "#PWR025" H 750 2875 50  0001 C CNN
F 1 "+5V" H 765 3198 50  0000 C CNN
F 2 "" H 750 3025 50  0001 C CNN
F 3 "" H 750 3025 50  0001 C CNN
	1    750  3025
	0    1    1    0   
$EndComp
Wire Wire Line
	675  2925 675  3025
Wire Wire Line
	675  3025 750  3025
$Comp
L power:+BATT #PWR?
U 1 1 5FCDACE3
P 750 2600
AR Path="/5E9C1C3A/5FCDACE3" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5FCDACE3" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FCDACE3" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5FCDACE3" Ref="#PWR024"  Part="1" 
F 0 "#PWR024" H 750 2450 50  0001 C CNN
F 1 "+BATT" H 765 2773 50  0000 C CNN
F 2 "" H 750 2600 50  0001 C CNN
F 3 "" H 750 2600 50  0001 C CNN
	1    750  2600
	0    1    -1   0   
$EndComp
Wire Wire Line
	675  2475 675  2600
Wire Wire Line
	675  2600 750  2600
$Comp
L power:GND #PWR?
U 1 1 5FCEB6E3
P 5800 4900
AR Path="/5FCEB6E3" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FCEB6E3" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FCEB6E3" Ref="#PWR?"  Part="1" 
AR Path="/5F913559/5FCEB6E3" Ref="#PWR040"  Part="1" 
F 0 "#PWR040" H 5800 4650 50  0001 C CNN
F 1 "GND" H 5800 4750 50  0000 C CNN
F 2 "" H 5800 4900 50  0001 C CNN
F 3 "" H 5800 4900 50  0001 C CNN
	1    5800 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 4775 5800 4900
$Comp
L power:PWR_FLAG #FLG03
U 1 1 5FCF28D0
P 675 3325
F 0 "#FLG03" H 675 3400 50  0001 C CNN
F 1 "PWR_FLAG" H 675 3498 50  0000 C CNN
F 2 "" H 675 3325 50  0001 C CNN
F 3 "~" H 675 3325 50  0001 C CNN
	1    675  3325
	1    0    0    -1  
$EndComp
Wire Wire Line
	675  3400 950  3400
Wire Wire Line
	675  3325 675  3400
Text Notes 6650 3925 0    50   ~ 0
D1| D0 | VI(IN2) > VI(IN1) |  OUT\n0  |1  |No  |IN1\n0  |1  |Yes  |IN2
Text Notes 7400 5150 0    50   ~ 0
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
	1275 4250 1775 4250
$Comp
L Device:C C?
U 1 1 6018A9C5
P 2975 6875
AR Path="/5EA4867C/6018A9C5" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/6018A9C5" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/6018A9C5" Ref="C?"  Part="1" 
AR Path="/5F988DA5/6018A9C5" Ref="C?"  Part="1" 
AR Path="/5F913559/6018A9C5" Ref="C27"  Part="1" 
F 0 "C27" H 3000 6950 50  0000 L CNN
F 1 "10 uF" V 2825 6750 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3013 6725 50  0001 C CNN
F 3 "~" H 2975 6875 50  0001 C CNN
F 4 "" H 2975 6875 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 2975 6875 50  0001 C CNN "lcsc"
	1    2975 6875
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6018B92A
P 3350 4375
AR Path="/5EA4867C/6018B92A" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/6018B92A" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/6018B92A" Ref="C?"  Part="1" 
AR Path="/5F988DA5/6018B92A" Ref="C?"  Part="1" 
AR Path="/5F913559/6018B92A" Ref="C28"  Part="1" 
F 0 "C28" H 3375 4450 50  0000 L CNN
F 1 "10 uF" V 3200 4250 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3388 4225 50  0001 C CNN
F 3 "~" H 3350 4375 50  0001 C CNN
F 4 "" H 3350 4375 50  0001 C CNN "LCSC"
F 5 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 3350 4375 50  0001 C CNN "lcsc"
	1    3350 4375
	1    0    0    -1  
$EndComp
Connection ~ 3350 4525
$Comp
L Device:C C?
U 1 1 6018C57C
P 2300 2525
AR Path="/5EA4867C/6018C57C" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/6018C57C" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/6018C57C" Ref="C?"  Part="1" 
AR Path="/5F913559/6018C57C" Ref="C25"  Part="1" 
F 0 "C25" H 2325 2600 50  0000 L CNN
F 1 "100 nF" V 2175 2350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2338 2375 50  0001 C CNN
F 3 "~" H 2300 2525 50  0001 C CNN
	1    2300 2525
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 601A13B5
P 2600 2525
AR Path="/5EA4867C/601A13B5" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/601A13B5" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/601A13B5" Ref="C?"  Part="1" 
AR Path="/5F913559/601A13B5" Ref="C26"  Part="1" 
F 0 "C26" H 2625 2600 50  0000 L CNN
F 1 "100 nF" V 2475 2350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2638 2375 50  0001 C CNN
F 3 "~" H 2600 2525 50  0001 C CNN
	1    2600 2525
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 2375 2300 2275
Wire Wire Line
	2300 2275 2200 2275
Wire Wire Line
	2300 2275 2875 2275
Connection ~ 2300 2275
Wire Wire Line
	2600 2375 2600 1650
Wire Wire Line
	2600 1650 2200 1650
Wire Wire Line
	2600 1650 3050 1650
Connection ~ 2600 1650
Wire Wire Line
	2300 2675 2300 2825
Wire Wire Line
	2300 2825 2600 2825
Connection ~ 3025 2825
Wire Wire Line
	3025 2825 3125 2825
Wire Wire Line
	2600 2675 2600 2825
Connection ~ 2600 2825
Wire Wire Line
	2600 2825 3025 2825
$EndSCHEMATC
