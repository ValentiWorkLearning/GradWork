EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 6
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
L OnOffControllers:max16054azt+t U6
U 1 1 5ED4F00B
P 5575 1750
F 0 "U6" H 6375 2137 60  0000 C CNN
F 1 "max16054azt+t" H 6375 2031 60  0000 C CNN
F 2 "21-0114C" H 6375 1990 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Maxim-Integrated-MAX16054AZT-T_C79401.pdf" H 5575 1750 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/Interface-Specialized_Maxim-Integrated-MAX16054AZT-T_C79401.html" H 5425 2000 50  0001 C CNN "lcsc"
	1    5575 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5EDEB467
P 5400 2575
AR Path="/5EA4867C/5EDEB467" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EDEB467" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/5EDEB467" Ref="C23"  Part="1" 
F 0 "C23" H 5425 2650 50  0000 L CNN
F 1 "100 nF" V 5250 2450 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5438 2425 50  0001 C CNN
F 3 "~" H 5400 2575 50  0001 C CNN
	1    5400 2575
	1    0    0    -1  
$EndComp
Wire Wire Line
	5575 2250 5400 2250
Wire Wire Line
	5400 2250 5400 2425
Wire Wire Line
	7175 2250 7425 2250
$Comp
L MosfetLocal:HX2301A VT2
U 1 1 5EDF815A
P 8525 1750
F 0 "VT2" H 8730 1704 50  0000 L CNN
F 1 "HX2301A" H 8730 1795 50  0000 L CNN
F 2 "" H 8725 1850 50  0001 C CNN
F 3 "~" H 8525 1750 50  0001 C CNN
	1    8525 1750
	1    0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5EDFEF6D
P 8000 1125
AR Path="/5EA4867C/5EDFEF6D" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5EDFEF6D" Ref="R22"  Part="1" 
F 0 "R22" H 8070 1171 50  0000 L CNN
F 1 "10k" H 8070 1080 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 7930 1125 50  0001 C CNN
F 3 "~" H 8000 1125 50  0001 C CNN
	1    8000 1125
	1    0    0    -1  
$EndComp
Text Label 5125 2250 0    50   ~ 0
V_Battery_P
Connection ~ 5400 2250
Wire Wire Line
	5125 2250 5400 2250
Text Label 7475 950  0    50   ~ 0
V_Battery_P
Wire Wire Line
	8000 950  8000 975 
Wire Wire Line
	8000 1275 8000 1750
Connection ~ 8000 1750
Wire Wire Line
	8000 1750 8325 1750
Wire Wire Line
	7175 1750 7550 1750
Wire Wire Line
	8000 950  8625 950 
Wire Wire Line
	8625 950  8625 1550
Text Label 9400 2075 2    50   ~ 0
V_Battery_P_SW
Wire Wire Line
	8625 1950 8625 2075
Wire Wire Line
	8625 2075 9400 2075
Wire Wire Line
	5575 1750 5200 1750
$Comp
L Device:R R?
U 1 1 5EE0DDD9
P 5050 1750
AR Path="/5EA4867C/5EE0DDD9" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5EE0DDD9" Ref="R20"  Part="1" 
F 0 "R20" V 4950 1550 50  0000 L CNN
F 1 "10k" V 4950 1850 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4980 1750 50  0001 C CNN
F 3 "~" H 5050 1750 50  0001 C CNN
	1    5050 1750
	0    1    1    0   
$EndComp
Wire Wire Line
	4900 1750 4650 1750
NoConn ~ 7175 1850
Wire Wire Line
	7475 950  8000 950 
Connection ~ 8000 950 
Text Notes 5125 1975 0    50   ~ 0
Int 63KOhm PU\n
Wire Notes Line
	1550 575  1550 3150
Wire Notes Line
	1550 3150 10325 3150
Wire Notes Line
	10325 3150 10325 575 
Wire Notes Line
	10325 575  1550 575 
Text Notes 5750 850  0    50   ~ 0
ON/OFF with two PB\n\n
$Comp
L Connector:TestPoint TP?
U 1 1 5EEBF81A
P 7550 1750
AR Path="/5E9C1C3A/5EEBF81A" Ref="TP?"  Part="1" 
AR Path="/5ED3F98E/5EEBF81A" Ref="TP2"  Part="1" 
F 0 "TP2" H 7608 1822 50  0000 L CNN
F 1 "TestPoint" H 7608 1777 50  0001 L CNN
F 2 "testpoints:testpoint" H 7750 1750 50  0001 C CNN
F 3 "~" H 7750 1750 50  0001 C CNN
	1    7550 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2225 1625 3025 1625
Text HLabel 2225 1625 0    50   Output ~ 0
PB_1_MCU
Wire Wire Line
	2850 2250 2225 2250
Text HLabel 2225 2250 0    50   Output ~ 0
PB_2_MCU
$Comp
L MosfetLocal:SL2300 VT?
U 1 1 5FD1BA2C
P 3675 1625
AR Path="/5EA4867C/5FD1BA2C" Ref="VT?"  Part="1" 
AR Path="/5ED3F98E/5FD1BA2C" Ref="VT?"  Part="1" 
F 0 "VT?" H 3804 1625 50  0000 L CNN
F 1 "SL2300" H 3805 1580 50  0001 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3675 1625 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1906271838_SLKORMICRO-Elec-SL2300_C350314.pdf" H 3675 1625 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/MOSFET_Slkor-SLKORMICRO-Elec-SL2300_C350314.html" H 3675 1625 50  0001 C CNN "lcsc"
	1    3675 1625
	1    0    0    -1  
$EndComp
$Comp
L MosfetLocal:SL2300 VT?
U 1 1 5FD1D042
P 3675 2250
AR Path="/5EA4867C/5FD1D042" Ref="VT?"  Part="1" 
AR Path="/5ED3F98E/5FD1D042" Ref="VT?"  Part="1" 
F 0 "VT?" H 3804 2250 50  0000 L CNN
F 1 "SL2300" H 3805 2205 50  0001 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3675 2250 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1906271838_SLKORMICRO-Elec-SL2300_C350314.pdf" H 3675 2250 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/MOSFET_Slkor-SLKORMICRO-Elec-SL2300_C350314.html" H 3675 2250 50  0001 C CNN "lcsc"
	1    3675 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 1825 3700 2050
$Comp
L Switch:SW_Push SW?
U 1 1 5FD1F2C6
P 3025 1050
F 0 "SW?" V 3025 1325 50  0000 C CNN
F 1 "SW_Push" H 3025 975 50  0000 C CNN
F 2 "" H 3025 1250 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Omron-Electronics-B3U-3000PM-B_C306884.pdf" H 3025 1250 50  0001 C CNN
F 4 "https://lcsc.com/products/Tactile-Switches_427.html?q=b3u-3000" H 3025 1050 50  0001 C CNN "lcsc"
	1    3025 1050
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5FD1FC43
P 2850 1925
F 0 "SW?" V 2875 2150 50  0000 C CNN
F 1 "SW_Push" H 2850 1875 50  0000 C CNN
F 2 "" H 2850 2125 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Omron-Electronics-B3U-3000PM-B_C306884.pdf" H 2850 2125 50  0001 C CNN
F 4 "https://lcsc.com/products/Tactile-Switches_427.html?q=b3u-3000" H 2850 1925 50  0001 C CNN "lcsc"
	1    2850 1925
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5FD221B3
P 3000 2550
AR Path="/5EA4867C/5FD221B3" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5FD221B3" Ref="R?"  Part="1" 
F 0 "R?" H 3125 2525 50  0000 L CNN
F 1 "10k" H 3075 2625 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2930 2550 50  0001 C CNN
F 3 "~" H 3000 2550 50  0001 C CNN
	1    3000 2550
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5FD22D59
P 3175 1875
AR Path="/5EA4867C/5FD22D59" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5FD22D59" Ref="R?"  Part="1" 
F 0 "R?" H 3025 1825 50  0000 L CNN
F 1 "10k" H 2975 1950 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 3105 1875 50  0001 C CNN
F 3 "~" H 3175 1875 50  0001 C CNN
	1    3175 1875
	-1   0    0    1   
$EndComp
Wire Wire Line
	3175 1725 3175 1625
Wire Wire Line
	3175 1625 3400 1625
Wire Wire Line
	3000 2400 3000 2250
Wire Wire Line
	3000 2250 3400 2250
Wire Wire Line
	3175 2025 3175 2800
Wire Wire Line
	3175 2800 3100 2800
Wire Wire Line
	3000 2800 3000 2700
$Comp
L power:GND #PWR?
U 1 1 5FD2AC63
P 3100 2850
AR Path="/5FD2AC63" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FD2AC63" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FD2AC63" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3100 2600 50  0001 C CNN
F 1 "GND" H 3100 2700 50  0000 C CNN
F 2 "" H 3100 2850 50  0001 C CNN
F 3 "" H 3100 2850 50  0001 C CNN
	1    3100 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 2850 3100 2800
Connection ~ 3100 2800
Wire Wire Line
	3100 2800 3000 2800
Wire Wire Line
	3700 2450 3700 2800
Wire Wire Line
	3700 2800 3175 2800
Connection ~ 3175 2800
Wire Wire Line
	3000 2250 2850 2250
Wire Wire Line
	2850 2250 2850 2125
Connection ~ 3000 2250
Wire Wire Line
	3025 1250 3025 1625
Wire Wire Line
	3025 1625 3175 1625
Connection ~ 3175 1625
Wire Wire Line
	2850 800  3025 800 
Wire Wire Line
	3025 800  3025 850 
Wire Wire Line
	2850 800  2850 1725
Wire Wire Line
	3700 1425 3700 1350
Wire Wire Line
	3700 1350 4350 1350
Wire Wire Line
	4350 1350 4350 1850
Wire Wire Line
	4350 1850 5575 1850
Text Notes 4925 2075 2    50   ~ 0
PB1 && PB2 => OUT=~OUT\n
Text Label 2925 800  0    50   ~ 0
V_Battery_P
Connection ~ 2850 2250
Connection ~ 3025 1625
$Comp
L power:GND #PWR?
U 1 1 5FD54CC0
P 4650 1750
AR Path="/5FD54CC0" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FD54CC0" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FD54CC0" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4650 1500 50  0001 C CNN
F 1 "GND" H 4650 1600 50  0000 C CNN
F 2 "" H 4650 1750 50  0001 C CNN
F 3 "" H 4650 1750 50  0001 C CNN
	1    4650 1750
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FD55B3B
P 5400 2850
AR Path="/5FD55B3B" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FD55B3B" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FD55B3B" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5400 2600 50  0001 C CNN
F 1 "GND" H 5400 2700 50  0000 C CNN
F 2 "" H 5400 2850 50  0001 C CNN
F 3 "" H 5400 2850 50  0001 C CNN
	1    5400 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 2725 5400 2850
$Comp
L power:GND #PWR?
U 1 1 5FD57BCE
P 7425 2250
AR Path="/5FD57BCE" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5FD57BCE" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FD57BCE" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7425 2000 50  0001 C CNN
F 1 "GND" H 7425 2100 50  0000 C CNN
F 2 "" H 7425 2250 50  0001 C CNN
F 3 "" H 7425 2250 50  0001 C CNN
	1    7425 2250
	1    0    0    -1  
$EndComp
$Comp
L PowerMuxes:TPS2115APWR U?
U 1 1 5FD7B81D
P 8350 4400
AR Path="/5E9C1C3A/5FD7B81D" Ref="U?"  Part="1" 
AR Path="/5ED3F98E/5FD7B81D" Ref="U?"  Part="1" 
F 0 "U?" H 8350 4925 60  0000 C CNN
F 1 "TPS2115APWR" H 8350 4800 60  0000 C CNN
F 2 "Housings_SSOP:TSSOP-8_4.4x3mm_Pitch0.65mm" H 8350 4890 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1809131529_Texas-Instruments-TPS2115APWR_C70287.pdf" H 8350 4150 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/Switching-Controllers_Texas-Instruments_TPS2115APWR_Texas-Instruments-Texas-Instruments-TPS2115APWR_C70287.html" H 8350 4400 50  0001 C CNN "lcsc"
	1    8350 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5FD7B823
P 7225 4900
AR Path="/5EA4867C/5FD7B823" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5FD7B823" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5FD7B823" Ref="R?"  Part="1" 
F 0 "R?" V 7018 4900 50  0000 C CNN
F 1 "330" V 7109 4900 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 7155 4900 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Others_Viking-Tech-ARG03FTC3300_C217969.html" H 7225 4900 50  0001 C CNN
	1    7225 4900
	0    1    1    0   
$EndComp
Text Label 7400 4900 0    50   ~ 0
Rlim
Wire Wire Line
	9175 4650 9150 4650
Wire Wire Line
	9175 4900 9150 4900
Wire Wire Line
	9175 4650 9175 4900
Wire Wire Line
	9175 4900 9400 4900
Connection ~ 9175 4900
NoConn ~ 9150 4550
Text Notes 9200 4550 0    50   ~ 0
Internal pull-up\n
$Comp
L Device:C C?
U 1 1 5FD7B833
P 6450 4600
AR Path="/5EA4867C/5FD7B833" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5FD7B833" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/5FD7B833" Ref="C?"  Part="1" 
F 0 "C?" H 6475 4675 50  0000 L CNN
F 1 "100 nF" V 6300 4475 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 6488 4450 50  0001 C CNN
F 3 "~" H 6450 4600 50  0001 C CNN
	1    6450 4600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5FD7B839
P 7050 4600
AR Path="/5EA4867C/5FD7B839" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5FD7B839" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/5FD7B839" Ref="C?"  Part="1" 
F 0 "C?" H 7075 4675 50  0000 L CNN
F 1 "100 nF" V 6925 4425 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 7088 4450 50  0001 C CNN
F 3 "~" H 7050 4600 50  0001 C CNN
	1    7050 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 4450 6450 4350
Wire Wire Line
	6450 4750 6450 4900
Wire Wire Line
	7050 4750 7050 4900
Text Label 6850 4350 0    50   ~ 0
V_USB
NoConn ~ 9150 4250
Text Label 9700 4150 2    50   ~ 0
V_OUT_MUX
Text Notes 7475 3575 0    100  ~ 0
Power Mux\n
Wire Notes Line
	10350 3375 10350 5275
Wire Notes Line
	10350 5275 6225 5275
Wire Notes Line
	6225 5275 6225 3375
Wire Notes Line
	6225 3375 10350 3375
$Comp
L USB_connectors:TYPE-C-31-M-17 J?
U 1 1 5FD7B84B
P 925 4875
AR Path="/5E9C1C3A/5FD7B84B" Ref="J?"  Part="1" 
AR Path="/5ED3F98E/5FD7B84B" Ref="J?"  Part="1" 
F 0 "J?" H 1158 5736 100 0000 C CNN
F 1 "TYPE-C-31-M-17" H 1158 5736 100 0001 C CNN
F 2 "" H 925 4875 100 0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1903211732_Korean-Hroparts-Elec-TYPE-C-31-M-17_C283540.pdf" H 925 4875 100 0001 C CNN
F 4 "https://lcsc.com/product-detail/Others_Korean-Hroparts-Elec-TYPE-C-31-M-17_C283540.html" H 925 4875 50  0001 C CNN "lcsc"
	1    925  4875
	1    0    0    -1  
$EndComp
Wire Wire Line
	1375 4650 1375 4725
Connection ~ 1375 4725
Wire Wire Line
	1375 4725 1375 4800
Wire Wire Line
	1375 4800 1600 4800
Connection ~ 1375 4800
NoConn ~ 1375 4525
NoConn ~ 1375 4450
Wire Wire Line
	1375 4225 1475 4225
Wire Wire Line
	1375 4225 1375 4300
Connection ~ 1375 4225
Text Label 1800 4225 2    50   ~ 0
V_USB
Text Notes 1100 5100 0    50   ~ 0
USB for power \nsupply only\n
Wire Wire Line
	9150 4150 9775 4150
$Comp
L Connector:TestPoint TP?
U 1 1 5FD7B85F
P 9775 4050
AR Path="/5EA4867C/5FD7B85F" Ref="TP?"  Part="1" 
AR Path="/5E9C1C3A/5FD7B85F" Ref="TP?"  Part="1" 
AR Path="/5ED3F98E/5FD7B85F" Ref="TP?"  Part="1" 
F 0 "TP?" H 9833 4122 50  0000 L CNN
F 1 "TestPoint" H 9833 4077 50  0001 L CNN
F 2 "testpoints:testpoint" H 9975 4050 50  0001 C CNN
F 3 "~" H 9975 4050 50  0001 C CNN
	1    9775 4050
	1    0    0    -1  
$EndComp
Text HLabel 9850 4150 2    50   Output ~ 0
V_OUT_MUX
Connection ~ 9775 4150
Wire Wire Line
	9775 4150 9850 4150
Wire Wire Line
	9775 4050 9775 4150
$Comp
L Device:D_TVS D?
U 1 1 5FD7B86A
P 1600 4500
AR Path="/5E9C1C3A/5FD7B86A" Ref="D?"  Part="1" 
AR Path="/5ED3F98E/5FD7B86A" Ref="D?"  Part="1" 
F 0 "D?" V 1554 4579 50  0000 L CNN
F 1 "D_TVS" V 1645 4579 50  0000 L CNN
F 2 "" H 1600 4500 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/2003282109_PN-SILICON-PESDU0521P1_C499647.pdf" H 1600 4500 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/TVS_PN-SILICON-PESDU0521P1_C499647.html" V 1600 4500 50  0001 C CNN "lcsc"
	1    1600 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	1600 4350 1600 4225
Connection ~ 1600 4225
Wire Wire Line
	1600 4225 1800 4225
Wire Wire Line
	1600 4650 1600 4800
Connection ~ 1600 4800
Wire Wire Line
	1600 4800 1800 4800
Wire Wire Line
	7000 4450 7050 4450
Wire Wire Line
	6450 4350 6600 4350
Wire Wire Line
	7375 4900 7550 4900
Connection ~ 7050 4450
Wire Wire Line
	7050 4450 7550 4450
Connection ~ 7050 4900
Wire Wire Line
	7050 4900 7075 4900
Wire Wire Line
	6450 4900 6850 4900
$Comp
L power:+5V #PWR?
U 1 1 5FD7B880
P 1475 4225
AR Path="/5E9C1C3A/5FD7B880" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FD7B880" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1475 4075 50  0001 C CNN
F 1 "+5V" H 1490 4398 50  0000 C CNN
F 2 "" H 1475 4225 50  0001 C CNN
F 3 "" H 1475 4225 50  0001 C CNN
	1    1475 4225
	1    0    0    -1  
$EndComp
Connection ~ 1475 4225
Wire Wire Line
	1475 4225 1600 4225
$Comp
L power:+5V #PWR?
U 1 1 5FD7B888
P 6600 4350
AR Path="/5E9C1C3A/5FD7B888" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5FD7B888" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6600 4200 50  0001 C CNN
F 1 "+5V" H 6615 4523 50  0000 C CNN
F 2 "" H 6600 4350 50  0001 C CNN
F 3 "" H 6600 4350 50  0001 C CNN
	1    6600 4350
	1    0    0    -1  
$EndComp
Connection ~ 6600 4350
Wire Wire Line
	6600 4350 7550 4350
Connection ~ 7550 1750
Wire Wire Line
	7550 1750 8000 1750
$Comp
L Device:Battery_Cell BT?
U 1 1 5FDB2945
P 1075 6625
AR Path="/5E9C1C3A/5FDB2945" Ref="BT?"  Part="1" 
AR Path="/5ED3F98E/5FDB2945" Ref="BT?"  Part="1" 
F 0 "BT?" H 1193 6721 50  0000 L CNN
F 1 "Battery_Cell" H 1193 6630 50  0000 L CNN
F 2 "" V 1075 6685 50  0001 C CNN
F 3 "https://aliexpress.ru/item/33000396152.html?spm=a2g0o.productlist.0.0.43416af464CXwu&algo_pvid=e6706777-cde6-4668-9867-8799ba4921bb&algo_expid=e6706777-cde6-4668-9867-8799ba4921bb-0&btsid=0b8b037215874644191236041ea897&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_" V 1075 6685 50  0001 C CNN
	1    1075 6625
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1075 6425 1075 6300
Wire Wire Line
	1075 6725 1075 6775
Text Label 7000 4450 0    50   ~ 0
V_Battery_P_SW
Text Notes 1350 3825 0    100  ~ 0
PSU
$Comp
L power:GND #PWR?
U 1 1 5F834978
P 1800 4800
AR Path="/5F834978" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F834978" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F834978" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1800 4550 50  0001 C CNN
F 1 "GND" H 1800 4650 50  0000 C CNN
F 2 "" H 1800 4800 50  0001 C CNN
F 3 "" H 1800 4800 50  0001 C CNN
	1    1800 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F834EDC
P 6850 4900
AR Path="/5F834EDC" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F834EDC" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F834EDC" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6850 4650 50  0001 C CNN
F 1 "GND" H 6850 4750 50  0000 C CNN
F 2 "" H 6850 4900 50  0001 C CNN
F 3 "" H 6850 4900 50  0001 C CNN
	1    6850 4900
	1    0    0    -1  
$EndComp
Connection ~ 6850 4900
Wire Wire Line
	6850 4900 7050 4900
$Comp
L power:GND #PWR?
U 1 1 5F835979
P 9400 4900
AR Path="/5F835979" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F835979" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F835979" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 9400 4650 50  0001 C CNN
F 1 "GND" H 9400 4750 50  0000 C CNN
F 2 "" H 9400 4900 50  0001 C CNN
F 3 "" H 9400 4900 50  0001 C CNN
	1    9400 4900
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR?
U 1 1 5F848817
P 1075 6300
AR Path="/5E9C1C3A/5F848817" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F848817" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F848817" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1075 6150 50  0001 C CNN
F 1 "+BATT" H 1090 6473 50  0000 C CNN
F 2 "" H 1075 6300 50  0001 C CNN
F 3 "" H 1075 6300 50  0001 C CNN
	1    1075 6300
	-1   0    0    -1  
$EndComp
Connection ~ 1075 6300
Wire Wire Line
	5325 4450 5775 4450
$Comp
L BatteryManagmentLocal:BQ21040DBVT U?
U 1 1 5F85B795
P 3725 4350
AR Path="/5E9C1C3A/5F85B795" Ref="U?"  Part="1" 
AR Path="/5F7F86D0/5F85B795" Ref="U?"  Part="1" 
AR Path="/5ED3F98E/5F85B795" Ref="U?"  Part="1" 
F 0 "U?" H 4525 4737 60  0000 C CNN
F 1 "BQ21040DBVT" H 4525 4631 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6" H 4525 4590 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Texas-Instruments-TI-BQ21040DBVR_C202311.pdf" H 4525 4631 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/PMIC-Battery-Management_Texas-Instruments_BQ21040DBVR_Texas-Instruments-Texas-Instruments-BQ21040DBVR_C202311.html" H 3725 4350 50  0001 C CNN "lcsc"
	1    3725 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3725 4200 3725 4250
Wire Wire Line
	3725 4500 3725 4450
$Comp
L Device:R R?
U 1 1 5F85B79D
P 3500 4650
AR Path="/5EA4867C/5F85B79D" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F85B79D" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F85B79D" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F85B79D" Ref="R?"  Part="1" 
F 0 "R?" V 3575 4600 50  0000 L CNN
F 1 "10k" V 3425 4575 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 3430 4650 50  0001 C CNN
F 3 "~" H 3500 4650 50  0001 C CNN
	1    3500 4650
	0    1    -1   0   
$EndComp
Wire Wire Line
	3725 4650 3650 4650
Wire Wire Line
	3350 4650 3325 4650
Text Notes 3275 4925 0    50   ~ 0
Set fast charge\ncurrent to 54 mA
NoConn ~ 5325 4650
Wire Wire Line
	3325 4500 3725 4500
Wire Wire Line
	3325 4200 3400 4200
$Comp
L Device:C C?
U 1 1 5F85B7AA
P 3325 4350
AR Path="/5EA4867C/5F85B7AA" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F85B7AA" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/5F85B7AA" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/5F85B7AA" Ref="C?"  Part="1" 
F 0 "C?" H 3350 4425 50  0000 L CNN
F 1 "1 uF 16V" H 3350 4250 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 3363 4200 50  0001 C CNN
F 3 "~" H 3325 4350 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R105K160NT_C475249.html" H 3325 4350 50  0001 C CNN "LCSC"
	1    3325 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5775 4750 5775 4825
Text Notes 4400 3700 0    100  ~ 0
Battery charger\n
Wire Notes Line
	2800 5175 2800 3375
$Comp
L Device:R R?
U 1 1 5F85B7B5
P 5775 4600
AR Path="/5EA4867C/5F85B7B5" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F85B7B5" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F85B7B5" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F85B7B5" Ref="R?"  Part="1" 
F 0 "R?" H 5550 4575 50  0000 L CNN
F 1 "10k" V 5850 4525 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5705 4600 50  0001 C CNN
F 3 "~" H 5775 4600 50  0001 C CNN
	1    5775 4600
	1    0    0    1   
$EndComp
Text Label 3500 4200 0    50   ~ 0
V_USB
Wire Notes Line
	6025 3375 6025 5175
Wire Notes Line
	2800 5175 6025 5175
Wire Notes Line
	2800 3375 6025 3375
$Comp
L power:+5V #PWR?
U 1 1 5F85B7C0
P 3400 4200
AR Path="/5E9C1C3A/5F85B7C0" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F85B7C0" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F85B7C0" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3400 4050 50  0001 C CNN
F 1 "+5V" H 3415 4373 50  0000 C CNN
F 2 "" H 3400 4200 50  0001 C CNN
F 3 "" H 3400 4200 50  0001 C CNN
	1    3400 4200
	1    0    0    -1  
$EndComp
Connection ~ 3400 4200
Wire Wire Line
	3400 4200 3725 4200
$Comp
L power:GND #PWR?
U 1 1 5F85B7CA
P 3125 4650
AR Path="/5F85B7CA" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F85B7CA" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F85B7CA" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5F85B7CA" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F85B7CA" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3125 4400 50  0001 C CNN
F 1 "GND" H 3125 4500 50  0000 C CNN
F 2 "" H 3125 4650 50  0001 C CNN
F 3 "" H 3125 4650 50  0001 C CNN
	1    3125 4650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F85B7D0
P 5775 4825
AR Path="/5F85B7D0" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F85B7D0" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F85B7D0" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5F85B7D0" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F85B7D0" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5775 4575 50  0001 C CNN
F 1 "GND" H 5775 4675 50  0000 C CNN
F 2 "" H 5775 4825 50  0001 C CNN
F 3 "" H 5775 4825 50  0001 C CNN
	1    5775 4825
	1    0    0    -1  
$EndComp
Wire Wire Line
	3325 4500 3325 4650
Connection ~ 3325 4500
Connection ~ 3325 4650
Wire Wire Line
	3325 4650 3125 4650
$Comp
L power:+BATT #PWR?
U 1 1 5F85E980
P 5775 4150
AR Path="/5E9C1C3A/5F85E980" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F85E980" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F85E980" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5775 4000 50  0001 C CNN
F 1 "+BATT" H 5790 4323 50  0000 C CNN
F 2 "" H 5775 4150 50  0001 C CNN
F 3 "" H 5775 4150 50  0001 C CNN
	1    5775 4150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5775 4250 5775 4150
Wire Wire Line
	5325 4250 5775 4250
Text Label 2625 6300 2    50   ~ 0
V_Battery_P
$Comp
L BatteryManagmentLocal:STC3100IQT U?
U 1 1 5F89D234
P 4450 6350
AR Path="/5E9C1C3A/5F89D234" Ref="U?"  Part="1" 
AR Path="/5F7F86D0/5F89D234" Ref="U?"  Part="1" 
AR Path="/5ED3F98E/5F89D234" Ref="U?"  Part="1" 
F 0 "U?" H 4450 6765 50  0000 C CNN
F 1 "STC3100IQT" H 4450 6650 50  0000 C CNN
F 2 "Housings_DFN_QFN:DFN-8-1EP_3x3mm_Pitch0.5mm" H 4575 7125 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1804172029_STMicroelectronics-STC3100IQT_C155587.pdf" H 4450 6350 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/_STMicroelectronics_STC3100IQT_STC3100IQT_C155587.html" H 4825 6975 50  0001 C CNN "lcsc"
	1    4450 6350
	-1   0    0    -1  
$EndComp
Text Label 2200 6400 0    50   ~ 0
V_Battery_N
Wire Wire Line
	3375 6400 3375 6675
Wire Wire Line
	3750 6500 3750 7150
Wire Wire Line
	3375 6975 3375 7150
Text Notes 3775 7450 2    50   ~ 0
GND (pin 5) should be directly \nconnected to negedge resistor\npin that is connected to GND plane 
$Comp
L Device:C C?
U 1 1 5F89D241
P 2950 6850
AR Path="/5EA4867C/5F89D241" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5F89D241" Ref="C?"  Part="1" 
AR Path="/5F7F86D0/5F89D241" Ref="C?"  Part="1" 
AR Path="/5ED3F98E/5F89D241" Ref="C?"  Part="1" 
F 0 "C?" H 2975 6925 50  0000 L CNN
F 1 "1 uF 16V" V 2800 6725 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2988 6700 50  0001 C CNN
F 3 "~" H 2950 6850 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R105K160NT_C475249.html" H 2950 6850 50  0001 C CNN "LCSC"
	1    2950 6850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3900 6200 2950 6200
Wire Wire Line
	2950 6200 2950 6700
Wire Wire Line
	2950 7000 2950 7150
Connection ~ 3375 7150
Wire Wire Line
	2950 7150 3375 7150
NoConn ~ 5000 6200
$Comp
L Device:R R?
U 1 1 5F89D24D
P 5950 6150
AR Path="/5EA4867C/5F89D24D" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F89D24D" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F89D24D" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F89D24D" Ref="R?"  Part="1" 
F 0 "R?" H 6000 6000 50  0000 L CNN
F 1 "10k" V 5875 6075 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5880 6150 50  0001 C CNN
F 3 "~" H 5950 6150 50  0001 C CNN
	1    5950 6150
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5F89D253
P 5700 6150
AR Path="/5EA4867C/5F89D253" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F89D253" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F89D253" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F89D253" Ref="R?"  Part="1" 
F 0 "R?" H 5725 6000 50  0000 L CNN
F 1 "10k" V 5625 6075 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5630 6150 50  0001 C CNN
F 3 "~" H 5700 6150 50  0001 C CNN
	1    5700 6150
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5F89D259
P 5275 6300
AR Path="/5EA4867C/5F89D259" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F89D259" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F89D259" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F89D259" Ref="R?"  Part="1" 
F 0 "R?" V 5100 6250 50  0000 L CNN
F 1 "200k 0.1%" V 5175 6100 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5205 6300 50  0001 C CNN
F 3 "~" H 5275 6300 50  0001 C CNN
	1    5275 6300
	0    1    1    0   
$EndComp
Wire Wire Line
	5125 6300 5000 6300
Wire Wire Line
	5425 6300 5575 6300
Wire Wire Line
	5700 6300 5700 6400
Wire Wire Line
	5700 6400 5000 6400
Wire Wire Line
	5950 6300 5950 6500
Wire Wire Line
	5950 6500 5000 6500
Wire Wire Line
	5950 6000 5950 5900
Wire Wire Line
	5950 5900 5825 5900
Wire Wire Line
	5700 5900 5700 6000
Wire Wire Line
	3750 7150 3375 7150
Wire Wire Line
	3750 6500 3900 6500
Text Notes 4700 6825 2    50   ~ 0
9 pin directly \nto plan GND\n
Text Notes 4525 5750 2    100  ~ 0
Fuel gauge
Wire Notes Line
	1975 5475 1975 7750
$Comp
L power:+3.3V #PWR?
U 1 1 5F89D26D
P 5825 5775
AR Path="/5E9C1C3A/5F89D26D" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F89D26D" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F89D26D" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5825 5625 50  0001 C CNN
F 1 "+3.3V" H 5840 5948 50  0000 C CNN
F 2 "" H 5825 5775 50  0001 C CNN
F 3 "" H 5825 5775 50  0001 C CNN
	1    5825 5775
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5825 5775 5825 5900
Connection ~ 5825 5900
Wire Wire Line
	5825 5900 5700 5900
$Comp
L Device:R R?
U 1 1 5F89D277
P 3375 6825
AR Path="/5EA4867C/5F89D277" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5F89D277" Ref="R?"  Part="1" 
AR Path="/5F7F86D0/5F89D277" Ref="R?"  Part="1" 
AR Path="/5ED3F98E/5F89D277" Ref="R?"  Part="1" 
F 0 "R?" H 3450 6775 50  0000 L CNN
F 1 "0.15 Ohm" V 3275 6650 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 3305 6825 50  0001 C CNN
F 3 "~" H 3375 6825 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Chip-Resistor-Surface-Mount_UNI-ROYAL-Uniroyal-Elec-0603WAF150LT5E_C45879.html" V 3375 6825 50  0001 C CNN "lcsc"
	1    3375 6825
	-1   0    0    1   
$EndComp
Text Label 5975 6400 0    50   ~ 0
SDA_FG
Text Label 5975 6500 0    50   ~ 0
SCL_FG
Wire Wire Line
	5700 6400 6250 6400
Connection ~ 5700 6400
Wire Wire Line
	5950 6500 6250 6500
Connection ~ 5950 6500
Wire Notes Line
	1975 5475 6900 5475
Wire Notes Line
	1975 7750 6900 7750
Wire Notes Line
	6900 5475 6900 7750
Text HLabel 6250 6400 2    50   BiDi ~ 0
SDA_FG
Text HLabel 6250 6500 2    50   Input ~ 0
SCL_FG
$Comp
L power:GND #PWR?
U 1 1 5F89D28A
P 3900 7150
AR Path="/5F89D28A" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F89D28A" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F89D28A" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5F89D28A" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F89D28A" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3900 6900 50  0001 C CNN
F 1 "GND" H 3900 7000 50  0000 C CNN
F 2 "" H 3900 7150 50  0001 C CNN
F 3 "" H 3900 7150 50  0001 C CNN
	1    3900 7150
	1    0    0    -1  
$EndComp
Connection ~ 3750 7150
Wire Wire Line
	3900 6575 3900 7150
Connection ~ 3900 7150
Wire Wire Line
	3750 7150 3900 7150
Wire Wire Line
	5575 6300 5575 7150
$Comp
L power:GND #PWR?
U 1 1 5F89D295
P 5575 7150
AR Path="/5F89D295" Ref="#PWR?"  Part="1" 
AR Path="/5E9B1DCE/5F89D295" Ref="#PWR?"  Part="1" 
AR Path="/5ED3F98E/5F89D295" Ref="#PWR?"  Part="1" 
AR Path="/5E9C1C3A/5F89D295" Ref="#PWR?"  Part="1" 
AR Path="/5F7F86D0/5F89D295" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5575 6900 50  0001 C CNN
F 1 "GND" H 5575 7000 50  0000 C CNN
F 2 "" H 5575 7150 50  0001 C CNN
F 3 "" H 5575 7150 50  0001 C CNN
	1    5575 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1875 6400 3375 6400
Text Label 5725 4250 2    50   ~ 0
V_Battery_P
Wire Wire Line
	1075 6300 3900 6300
Wire Wire Line
	1075 6775 1875 6775
Wire Wire Line
	1875 6775 1875 6400
Wire Notes Line
	1950 3550 1950 7050
Wire Notes Line
	1950 7050 500  7050
Wire Notes Line
	500  7050 500  3550
Wire Notes Line
	500  3550 1950 3550
Wire Wire Line
	3375 6400 3900 6400
Connection ~ 3375 6400
$EndSCHEMATC
