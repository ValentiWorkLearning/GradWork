EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
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
L PowerMuxes:TPS2115APWR U8
U 1 1 5E9C2ACA
P 2875 1625
F 0 "U8" H 2875 2150 60  0000 C CNN
F 1 "TPS2115APWR" H 2875 2025 60  0000 C CNN
F 2 "Housings_SSOP:TSSOP-8_4.4x3mm_Pitch0.65mm" H 2875 2115 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1809131529_Texas-Instruments-TPS2115APWR_C70287.pdf" H 2875 1375 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/Switching-Controllers_Texas-Instruments_TPS2115APWR_Texas-Instruments-Texas-Instruments-TPS2115APWR_C70287.html" H 2875 1625 50  0001 C CNN "lcsc"
	1    2875 1625
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E9CA89F
P 1750 2125
AR Path="/5EA4867C/5E9CA89F" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5E9CA89F" Ref="R23"  Part="1" 
F 0 "R23" V 1543 2125 50  0000 C CNN
F 1 "330" V 1634 2125 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1680 2125 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Others_Viking-Tech-ARG03FTC3300_C217969.html" H 1750 2125 50  0001 C CNN
	1    1750 2125
	0    1    1    0   
$EndComp
Text Label 1925 2125 0    50   ~ 0
Rlim
Text Label 1125 2125 0    50   ~ 0
GND
Wire Wire Line
	3700 1875 3675 1875
Wire Wire Line
	3700 2125 3675 2125
Wire Wire Line
	3700 1875 3700 2125
Wire Wire Line
	3700 2125 3925 2125
Connection ~ 3700 2125
Text Label 3925 2125 2    50   ~ 0
GND
NoConn ~ 3675 1775
Text Notes 3725 1775 0    50   ~ 0
Internal pull-up\n
$Comp
L Device:C C?
U 1 1 5E9D3BD7
P 975 1825
AR Path="/5EA4867C/5E9D3BD7" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5E9D3BD7" Ref="C24"  Part="1" 
F 0 "C24" H 1000 1900 50  0000 L CNN
F 1 "100 nF" V 825 1700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1013 1675 50  0001 C CNN
F 3 "~" H 975 1825 50  0001 C CNN
	1    975  1825
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E9D4159
P 1575 1825
AR Path="/5EA4867C/5E9D4159" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5E9D4159" Ref="C25"  Part="1" 
F 0 "C25" H 1600 1900 50  0000 L CNN
F 1 "100 nF" V 1450 1650 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1613 1675 50  0001 C CNN
F 3 "~" H 1575 1825 50  0001 C CNN
	1    1575 1825
	1    0    0    -1  
$EndComp
Wire Wire Line
	975  1675 975  1575
Wire Wire Line
	975  1975 975  2125
Wire Wire Line
	1575 1975 1575 2125
Text Label 1375 1575 0    50   ~ 0
V_USB
NoConn ~ 3675 1475
Text Label 4225 1375 2    50   ~ 0
V_OUT_MUX
$Comp
L Device:Battery_Cell BT1
U 1 1 5E9EB660
P 5325 4400
F 0 "BT1" H 5443 4496 50  0000 L CNN
F 1 "Battery_Cell" H 5443 4405 50  0000 L CNN
F 2 "" V 5325 4460 50  0001 C CNN
F 3 "https://aliexpress.ru/item/33000396152.html?spm=a2g0o.productlist.0.0.43416af464CXwu&algo_pvid=e6706777-cde6-4668-9867-8799ba4921bb&algo_expid=e6706777-cde6-4668-9867-8799ba4921bb-0&btsid=0b8b037215874644191236041ea897&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_" V 5325 4460 50  0001 C CNN
	1    5325 4400
	-1   0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR028
U 1 1 5E9EC7E5
P 5325 3825
F 0 "#PWR028" H 5325 3675 50  0001 C CNN
F 1 "+BATT" H 5340 3998 50  0000 C CNN
F 2 "" H 5325 3825 50  0001 C CNN
F 3 "" H 5325 3825 50  0001 C CNN
	1    5325 3825
	-1   0    0    -1  
$EndComp
Text Label 4725 4600 2    50   ~ 0
GND
Text Label 5325 3975 2    50   ~ 0
V_Battery_P
Wire Wire Line
	4050 4225 4500 4225
$Comp
L BatteryManagmentLocal:BQ21040DBVT U7
U 1 1 5EA1363C
P 2450 4125
F 0 "U7" H 3250 4512 60  0000 C CNN
F 1 "BQ21040DBVT" H 3250 4406 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6" H 3250 4365 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Texas-Instruments-TI-BQ21040DBVR_C202311.pdf" H 3250 4406 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/PMIC-Battery-Management_Texas-Instruments_BQ21040DBVR_Texas-Instruments-Texas-Instruments-BQ21040DBVR_C202311.html" H 2450 4125 50  0001 C CNN "lcsc"
	1    2450 4125
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 3975 2450 4025
Wire Wire Line
	2450 4275 2450 4225
$Comp
L Device:R R?
U 1 1 5E9FD451
P 2225 4425
AR Path="/5EA4867C/5E9FD451" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5E9FD451" Ref="R26"  Part="1" 
F 0 "R26" V 2300 4375 50  0000 L CNN
F 1 "10k" V 2150 4350 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2155 4425 50  0001 C CNN
F 3 "~" H 2225 4425 50  0001 C CNN
	1    2225 4425
	0    1    -1   0   
$EndComp
Wire Wire Line
	2450 4425 2375 4425
Wire Wire Line
	2075 4425 1850 4425
Text Label 1850 4425 0    50   ~ 0
GND
Text Notes 1900 4700 0    50   ~ 0
Set fast charge\ncurrent to 54 mA
NoConn ~ 4050 4425
Wire Wire Line
	2050 4275 2450 4275
Wire Wire Line
	2050 3975 2450 3975
$Comp
L Device:C C?
U 1 1 5E9FB26C
P 2050 4125
AR Path="/5EA4867C/5E9FB26C" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5E9FB26C" Ref="C26"  Part="1" 
F 0 "C26" H 2075 4200 50  0000 L CNN
F 1 "1 uF 16V" V 1900 4000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2088 3975 50  0001 C CNN
F 3 "~" H 2050 4125 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R105K160NT_C475249.html" H 2050 4125 50  0001 C CNN "LCSC"
	1    2050 4125
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 4525 4500 4600
Wire Wire Line
	4500 4600 4725 4600
Wire Wire Line
	5325 3825 5325 4025
Wire Wire Line
	4050 4025 5325 4025
Connection ~ 5325 4025
Wire Wire Line
	5325 4025 5325 4200
$Comp
L DCDC_Local:TPS62740DSST U11
U 1 1 5EA00C58
P 7475 1450
F 0 "U11" H 8275 1837 60  0000 C CNN
F 1 "TPS62740DSST" H 8275 1700 60  0000 C CNN
F 2 "Housings_SON:WSON-12-1EP_3x2mm_Pitch0.5mm" H 8275 1690 60  0001 C CNN
F 3 "http://www.ti.com/lit/ds/slvsb02b/slvsb02b.pdf" H 7475 1450 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/DC-DC-Converters_Texas-Instruments_TPS62740DSSR_Texas-Instruments-Texas-Instruments-TPS62740DSSR_C128606.html" H 7475 1450 50  0001 C CNN "lcsc"
	1    7475 1450
	1    0    0    -1  
$EndComp
Text Notes 2000 800  0    100  ~ 0
Power Mux\n
Wire Notes Line
	4875 600  4875 2500
Wire Notes Line
	4875 2500 750  2500
Wire Notes Line
	750  2500 750  600 
Wire Notes Line
	750  600  4875 600 
Text Notes 3125 3475 0    100  ~ 0
Battery charger\n
Wire Notes Line
	1750 5000 1750 3200
$Comp
L Device:C C?
U 1 1 5EA15E96
P 6875 1525
AR Path="/5EA4867C/5EA15E96" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EA15E96" Ref="C28"  Part="1" 
F 0 "C28" H 6900 1600 50  0000 L CNN
F 1 "10 uF" V 6725 1400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 6913 1375 50  0001 C CNN
F 3 "~" H 6875 1525 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 6875 1525 50  0001 C CNN "LCSC"
	1    6875 1525
	1    0    0    -1  
$EndComp
Wire Wire Line
	7475 1350 6875 1350
Wire Wire Line
	6875 1350 6875 1375
Wire Wire Line
	6875 1675 6875 1825
Wire Wire Line
	6875 1825 6650 1825
Text Label 6650 1825 0    50   ~ 0
GND
$Comp
L pspice:INDUCTOR L3
U 1 1 5EA18A55
P 9800 1350
F 0 "L3" H 9800 1475 50  0000 C CNN
F 1 "2.2 uH 13.75 mOHM 1.2 A" H 9750 1275 50  0000 C CNN
F 2 "" H 9800 1350 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1908221840_Sunltech-Tech-SLM20162R2MIT_C412023.pdf" H 9800 1350 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Power-Inductors_Sunltech-Tech-SLM20162R2MIT_C412023.html" H 9800 1350 50  0001 C CNN "lcsc"
	1    9800 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9075 1350 9550 1350
Wire Wire Line
	7475 1900 7475 2000
Wire Wire Line
	7475 2200 7075 2200
Connection ~ 7475 2200
Connection ~ 7475 2000
Wire Wire Line
	7475 2000 7475 2100
Connection ~ 7475 2100
Wire Wire Line
	7475 2100 7475 2200
Text Label 7075 2200 0    50   ~ 0
GND
Text Notes 7150 2300 0    50   ~ 0
Vout = 1.8V\n
Text Label 9150 1350 0    50   ~ 0
L_SW_0
Wire Wire Line
	10050 1350 10175 1350
Text Label 7325 1350 2    50   ~ 0
V_OUT_MUX
Text Label 10475 1350 2    50   ~ 0
V1V8
$Comp
L Supervisors:MAX809STRG U10
U 1 1 5EA21C4A
P 5975 2075
F 0 "U10" H 5975 2542 50  0000 C CNN
F 1 "MAX809STRG" H 5975 2451 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6275 2175 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/ON-Semicon-ON-MAX809STRG_C9965.pdf" H 6275 2175 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Microprocessor-Microcontroller-Supervisors_ON-Semiconductor-ON-Semiconductor-MAX809STRG_C9965.html" H 5975 2075 50  0001 C CNN "lcsc"
	1    5975 2075
	1    0    0    -1  
$EndComp
Text Notes 5175 2175 0    50   ~ 0
no external \ncomponents\nneeded
Wire Wire Line
	5675 1900 5075 1900
Text Label 5075 1900 0    50   ~ 0
V_OUT_MUX
Wire Wire Line
	5675 2250 5075 2250
Text Label 5075 2250 0    50   ~ 0
GND
Wire Wire Line
	7250 1625 7475 1625
Wire Wire Line
	6275 2075 6375 2075
Wire Wire Line
	7250 1625 7250 2075
Text Label 6550 2075 0    50   ~ 0
DCDC_ENABLE
Text Notes 5275 2575 0    50   ~ 0
V_OUT_MUX always > 1.0 \nRESET Output Guaranteed to VCC = 1.0 V.
Wire Wire Line
	9075 2350 9075 2450
Connection ~ 9075 2450
Text Label 9525 2450 2    50   ~ 0
GND
Wire Wire Line
	7075 2550 7475 2550
Text Label 7075 2550 0    50   ~ 0
GND
Text Notes 7175 2725 0    50   ~ 0
LOAD(out)\nis disabled
NoConn ~ 9075 1850
Wire Wire Line
	9075 1750 10275 1750
Wire Wire Line
	10275 1750 10275 1350
Connection ~ 10275 1350
Wire Wire Line
	10275 1350 10500 1350
$Comp
L Device:C C?
U 1 1 5EA4839B
P 10500 1500
AR Path="/5EA4867C/5EA4839B" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EA4839B" Ref="C30"  Part="1" 
F 0 "C30" H 10525 1575 50  0000 L CNN
F 1 "10 uF" V 10350 1375 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 10538 1350 50  0001 C CNN
F 3 "~" H 10500 1500 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 10500 1500 50  0001 C CNN "LCSC"
	1    10500 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9075 2450 10500 2450
Wire Wire Line
	10500 1650 10500 2450
NoConn ~ 9075 1950
Text Notes 9150 1725 0    50   ~ 0
Connect this pin(5) directly \nto the output capacitor\n with a short trace
$Comp
L BatteryManagmentLocal:STC3100IQT U9
U 1 1 5EA36940
P 3425 6075
F 0 "U9" H 3425 6490 50  0000 C CNN
F 1 "STC3100IQT" H 3425 6375 50  0000 C CNN
F 2 "Housings_DFN_QFN:DFN-8-1EP_3x3mm_Pitch0.5mm" H 3550 6850 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1804172029_STMicroelectronics-STC3100IQT_C155587.pdf" H 3425 6075 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/_STMicroelectronics_STC3100IQT_STC3100IQT_C155587.html" H 3800 6700 50  0001 C CNN "lcsc"
	1    3425 6075
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5EA405B7
P 4500 6550
AR Path="/5EA4867C/5EA405B7" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5EA405B7" Ref="R29"  Part="1" 
F 0 "R29" V 4425 6500 50  0000 L CNN
F 1 "2.2 OHM 1%" V 4600 6300 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4430 6550 50  0001 C CNN
F 3 "~" H 4500 6550 50  0001 C CNN
	1    4500 6550
	1    0    0    1   
$EndComp
Text Label 4350 6875 2    50   ~ 0
GND
$Comp
L Device:R R?
U 1 1 5E9F16F1
P 4500 4375
AR Path="/5EA4867C/5E9F16F1" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5E9F16F1" Ref="R28"  Part="1" 
F 0 "R28" V 4425 4325 50  0000 L CNN
F 1 "10k" V 4575 4300 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4430 4375 50  0001 C CNN
F 3 "~" H 4500 4375 50  0001 C CNN
	1    4500 4375
	1    0    0    1   
$EndComp
Wire Wire Line
	5325 4500 5325 4875
Wire Wire Line
	5325 4875 4850 4875
Text Label 4850 4875 0    50   ~ 0
V_Battery_N
Wire Wire Line
	3975 6125 4500 6125
Wire Wire Line
	4500 6125 4500 6400
Text Label 4075 6125 0    50   ~ 0
V_Battery_N
Wire Wire Line
	4125 6225 4125 6875
Wire Wire Line
	4500 6700 4500 6875
Text Notes 4100 7175 0    50   ~ 0
GND (pin 5) should be directly \nconnected to negedge resistor\npin that is connected to GND plane 
$Comp
L Device:C C?
U 1 1 5EA50EBE
P 4925 6575
AR Path="/5EA4867C/5EA50EBE" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EA50EBE" Ref="C27"  Part="1" 
F 0 "C27" H 4950 6650 50  0000 L CNN
F 1 "1 uF 16V" V 4775 6450 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 4963 6425 50  0001 C CNN
F 3 "~" H 4925 6575 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R105K160NT_C475249.html" H 4925 6575 50  0001 C CNN "LCSC"
	1    4925 6575
	1    0    0    -1  
$EndComp
Text Label 4500 6025 2    50   ~ 0
V_Battery_P
Wire Wire Line
	3975 6025 4500 6025
Wire Wire Line
	3975 5925 4925 5925
Wire Wire Line
	4925 5925 4925 6425
Wire Wire Line
	4925 6725 4925 6875
Connection ~ 4500 6875
Wire Wire Line
	4925 6875 4500 6875
NoConn ~ 2875 5925
$Comp
L Device:R R?
U 1 1 5EA5E00D
P 1925 5875
AR Path="/5EA4867C/5EA5E00D" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5EA5E00D" Ref="R24"  Part="1" 
F 0 "R24" V 1850 5825 50  0000 L CNN
F 1 "10k" V 2000 5800 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1855 5875 50  0001 C CNN
F 3 "~" H 1925 5875 50  0001 C CNN
	1    1925 5875
	1    0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5EA5F2E9
P 2175 5875
AR Path="/5EA4867C/5EA5F2E9" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5EA5F2E9" Ref="R25"  Part="1" 
F 0 "R25" V 2100 5825 50  0000 L CNN
F 1 "10k" V 2250 5800 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2105 5875 50  0001 C CNN
F 3 "~" H 2175 5875 50  0001 C CNN
	1    2175 5875
	1    0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5EA5F7B3
P 2600 6025
AR Path="/5EA4867C/5EA5F7B3" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5EA5F7B3" Ref="R27"  Part="1" 
F 0 "R27" V 2425 5975 50  0000 L CNN
F 1 "200k 0.1%" V 2500 5825 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2530 6025 50  0001 C CNN
F 3 "~" H 2600 6025 50  0001 C CNN
	1    2600 6025
	0    -1   1    0   
$EndComp
Wire Wire Line
	2750 6025 2875 6025
Wire Wire Line
	2450 6025 2300 6025
Text Label 2300 6025 0    50   ~ 0
GND
Wire Wire Line
	2175 6025 2175 6125
Wire Wire Line
	2175 6125 2875 6125
Wire Wire Line
	1925 6025 1925 6225
Wire Wire Line
	1925 6225 2875 6225
Wire Wire Line
	1925 5725 1925 5625
Wire Wire Line
	1925 5625 2175 5625
Wire Wire Line
	2175 5625 2175 5725
Text Label 1975 5625 0    50   ~ 0
V1V8
Wire Wire Line
	4125 6875 4500 6875
Wire Wire Line
	4125 6225 3975 6225
Wire Wire Line
	3975 6300 3975 6450
Wire Wire Line
	3975 6450 3800 6450
Text Label 3800 6450 0    50   ~ 0
GND
Text Notes 3525 6625 0    50   ~ 0
9 pin directly \nto plan GND\n
Text Notes 3350 5475 0    100  ~ 0
Fuel gauge
Wire Notes Line
	1375 5200 5900 5200
Wire Notes Line
	5900 5200 5900 7475
Wire Notes Line
	5900 7475 1375 7475
Wire Notes Line
	1375 7475 1375 5200
Text Notes 7775 1025 0    100  ~ 0
DCDC converter 1.8V\n\n
$Comp
L USB_connectors:TYPE-C-31-M-17 J11
U 1 1 5EA8D0C3
P 750 3700
F 0 "J11" H 983 4561 100 0000 C CNN
F 1 "TYPE-C-31-M-17" H 983 4561 100 0001 C CNN
F 2 "" H 750 3700 100 0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1903211732_Korean-Hroparts-Elec-TYPE-C-31-M-17_C283540.pdf" H 750 3700 100 0001 C CNN
F 4 "https://lcsc.com/product-detail/Others_Korean-Hroparts-Elec-TYPE-C-31-M-17_C283540.html" H 750 3700 50  0001 C CNN "lcsc"
	1    750  3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 3475 1200 3550
Connection ~ 1200 3550
Wire Wire Line
	1200 3550 1200 3625
Wire Wire Line
	1200 3625 1425 3625
Connection ~ 1200 3625
Text Label 1625 3625 2    50   ~ 0
GND
NoConn ~ 1200 3350
NoConn ~ 1200 3275
Wire Wire Line
	1200 3050 1425 3050
Wire Wire Line
	1200 3050 1200 3125
Connection ~ 1200 3050
Text Label 1625 3050 2    50   ~ 0
V_USB
Text HLabel 10575 1350 2    50   Output ~ 0
V1V8
Wire Wire Line
	10575 1350 10500 1350
Connection ~ 10500 1350
Text Notes 925  3925 0    50   ~ 0
USB for power \nsupply only\n
$Comp
L Connector:TestPoint TP3
U 1 1 5EAC2CCF
P 975 1575
F 0 "TP3" H 1033 1647 50  0000 L CNN
F 1 "TestPoint" H 1033 1602 50  0001 L CNN
F 2 "testpoints:testpoint" H 1175 1575 50  0001 C CNN
F 3 "~" H 1175 1575 50  0001 C CNN
	1    975  1575
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 5EAC8917
P 10500 1225
AR Path="/5EA4867C/5EAC8917" Ref="TP?"  Part="1" 
AR Path="/5E9C1C3A/5EAC8917" Ref="TP6"  Part="1" 
F 0 "TP6" H 10558 1297 50  0000 L CNN
F 1 "TestPoint" H 10558 1252 50  0001 L CNN
F 2 "testpoints:testpoint" H 10700 1225 50  0001 C CNN
F 3 "~" H 10700 1225 50  0001 C CNN
	1    10500 1225
	1    0    0    -1  
$EndComp
Wire Wire Line
	10500 1225 10500 1350
$Comp
L Connector:TestPoint TP?
U 1 1 5EACCAB9
P 6375 2075
AR Path="/5EA4867C/5EACCAB9" Ref="TP?"  Part="1" 
AR Path="/5E9C1C3A/5EACCAB9" Ref="TP5"  Part="1" 
F 0 "TP5" H 6433 2147 50  0000 L CNN
F 1 "TestPoint" H 6433 2102 50  0001 L CNN
F 2 "testpoints:testpoint" H 6575 2075 50  0001 C CNN
F 3 "~" H 6575 2075 50  0001 C CNN
	1    6375 2075
	1    0    0    -1  
$EndComp
Connection ~ 6375 2075
Wire Wire Line
	6375 2075 7250 2075
Wire Wire Line
	3675 1375 4300 1375
$Comp
L Connector:TestPoint TP?
U 1 1 5EAC5055
P 4300 1275
AR Path="/5EA4867C/5EAC5055" Ref="TP?"  Part="1" 
AR Path="/5E9C1C3A/5EAC5055" Ref="TP4"  Part="1" 
F 0 "TP4" H 4358 1347 50  0000 L CNN
F 1 "TestPoint" H 4358 1302 50  0001 L CNN
F 2 "testpoints:testpoint" H 4500 1275 50  0001 C CNN
F 3 "~" H 4500 1275 50  0001 C CNN
	1    4300 1275
	1    0    0    -1  
$EndComp
Text HLabel 4375 1375 2    50   Output ~ 0
V_OUT_MUX
Connection ~ 4300 1375
Wire Wire Line
	4300 1375 4375 1375
Wire Wire Line
	4300 1275 4300 1375
$Comp
L DCDC_Local:TPS62740DSST U12
U 1 1 5EB570E8
P 7475 3850
F 0 "U12" H 8275 4237 60  0000 C CNN
F 1 "TPS62740DSST" H 8275 4100 60  0000 C CNN
F 2 "Housings_SON:WSON-12-1EP_3x2mm_Pitch0.5mm" H 8275 4090 60  0001 C CNN
F 3 "http://www.ti.com/lit/ds/slvsb02b/slvsb02b.pdf" H 7475 3850 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/DC-DC-Converters_Texas-Instruments_TPS62740DSSR_Texas-Instruments-Texas-Instruments-TPS62740DSSR_C128606.html" H 7475 3850 50  0001 C CNN "lcsc"
	1    7475 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5EB570EF
P 6875 3925
AR Path="/5EA4867C/5EB570EF" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EB570EF" Ref="C29"  Part="1" 
F 0 "C29" H 6900 4000 50  0000 L CNN
F 1 "10 uF" V 6725 3800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 6913 3775 50  0001 C CNN
F 3 "~" H 6875 3925 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 6875 3925 50  0001 C CNN "LCSC"
	1    6875 3925
	1    0    0    -1  
$EndComp
Wire Wire Line
	7475 3750 6875 3750
Wire Wire Line
	6875 3750 6875 3775
Wire Wire Line
	6875 4075 6875 4225
Wire Wire Line
	6875 4225 6650 4225
Text Label 6650 4225 0    50   ~ 0
GND
$Comp
L pspice:INDUCTOR L4
U 1 1 5EB570FB
P 9800 3750
F 0 "L4" H 9800 3875 50  0000 C CNN
F 1 "2.2 uH 13.75 mOHM 1.2 A" H 9750 3675 50  0000 C CNN
F 2 "" H 9800 3750 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1908221840_Sunltech-Tech-SLM20162R2MIT_C412023.pdf" H 9800 3750 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Power-Inductors_Sunltech-Tech-SLM20162R2MIT_C412023.html" H 9800 3750 50  0001 C CNN "lcsc"
	1    9800 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9075 3750 9550 3750
Wire Wire Line
	7475 4300 7325 4300
Text Label 7075 4300 0    50   ~ 0
GND
Text Notes 6850 4725 0    50   ~ 0
Vout = 2.8V (4'b1010)\n
Text Label 9150 3750 0    50   ~ 0
L_SW_1
Wire Wire Line
	10050 3750 10275 3750
Text Label 7325 3750 2    50   ~ 0
V_OUT_MUX
Text Label 10475 3750 2    50   ~ 0
V2V8
Wire Wire Line
	6950 4025 7475 4025
Wire Wire Line
	6950 4025 6950 4475
Wire Wire Line
	9075 4750 9075 4850
Connection ~ 9075 4850
Text Label 9525 4850 2    50   ~ 0
GND
Wire Wire Line
	7075 4950 7475 4950
Text Label 7075 4950 0    50   ~ 0
GND
Text Notes 7175 5125 0    50   ~ 0
LOAD(out)\nis disabled
NoConn ~ 9075 4250
Wire Wire Line
	9075 4150 10275 4150
Wire Wire Line
	10275 4150 10275 3750
Connection ~ 10275 3750
Wire Wire Line
	10275 3750 10500 3750
$Comp
L Device:C C?
U 1 1 5EB5712C
P 10500 3900
AR Path="/5EA4867C/5EB5712C" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EB5712C" Ref="C31"  Part="1" 
F 0 "C31" H 10525 3975 50  0000 L CNN
F 1 "10 uF" V 10350 3775 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 10538 3750 50  0001 C CNN
F 3 "~" H 10500 3900 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R106M160NT_C466781.html" H 10500 3900 50  0001 C CNN "LCSC"
	1    10500 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9075 4850 10500 4850
Wire Wire Line
	10500 4050 10500 4850
NoConn ~ 9075 4350
Text Notes 9150 4125 0    50   ~ 0
Connect this pin(5) directly \nto the output capacitor\n with a short trace
Text Notes 7775 3475 0    100  ~ 0
DCDC converter 2.8V\n\n
Text HLabel 10575 3750 2    50   Output ~ 0
V2V8
Wire Wire Line
	10575 3750 10500 3750
Connection ~ 10500 3750
$Comp
L Connector:TestPoint TP?
U 1 1 5EB5713A
P 10500 3625
AR Path="/5EA4867C/5EB5713A" Ref="TP?"  Part="1" 
AR Path="/5E9C1C3A/5EB5713A" Ref="TP7"  Part="1" 
F 0 "TP7" H 10558 3697 50  0000 L CNN
F 1 "TestPoint" H 10558 3652 50  0001 L CNN
F 2 "testpoints:testpoint" H 10700 3625 50  0001 C CNN
F 3 "~" H 10700 3625 50  0001 C CNN
	1    10500 3625
	1    0    0    -1  
$EndComp
Wire Wire Line
	10500 3625 10500 3750
Text Label 6375 4475 0    50   ~ 0
DCDC_ENABLE
Wire Wire Line
	6375 4475 6950 4475
Wire Wire Line
	7475 4500 7325 4500
Wire Wire Line
	7325 4500 7325 4300
Connection ~ 7325 4300
Wire Wire Line
	7325 4300 7075 4300
Wire Wire Line
	7475 4600 7375 4600
Wire Wire Line
	7475 4400 7375 4400
Wire Wire Line
	7375 4400 7375 4600
Connection ~ 7375 4600
Wire Wire Line
	7375 4600 6825 4600
Text Label 6825 4600 0    50   ~ 0
V_OUT_MUX
Wire Notes Line
	5000 600  11025 600 
Wire Notes Line
	11025 600  11025 5325
Wire Notes Line
	11025 5325 6225 5325
Wire Notes Line
	6225 5325 6225 2750
Wire Notes Line
	6225 2750 5000 2750
Wire Notes Line
	5000 600  5000 2750
$Comp
L Device:D_TVS D3
U 1 1 5EC6AFA8
P 1425 3325
F 0 "D3" V 1379 3404 50  0000 L CNN
F 1 "D_TVS" V 1470 3404 50  0000 L CNN
F 2 "" H 1425 3325 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/2003282109_PN-SILICON-PESDU0521P1_C499647.pdf" H 1425 3325 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/TVS_PN-SILICON-PESDU0521P1_C499647.html" V 1425 3325 50  0001 C CNN "lcsc"
	1    1425 3325
	0    1    1    0   
$EndComp
Wire Wire Line
	1425 3175 1425 3050
Connection ~ 1425 3050
Wire Wire Line
	1425 3050 1625 3050
Wire Wire Line
	1425 3475 1425 3625
Connection ~ 1425 3625
Wire Wire Line
	1425 3625 1625 3625
Text Label 2225 3975 0    50   ~ 0
V_USB
Wire Wire Line
	5325 4025 5450 4025
Text HLabel 5450 4025 2    50   Output ~ 0
V_Battery_P
Wire Notes Line
	1750 5000 5975 5000
Wire Notes Line
	5975 3200 5975 5000
Wire Notes Line
	1750 3200 5975 3200
Text HLabel 1525 1675 0    50   Input ~ 0
V_Battery_EN
Wire Wire Line
	1525 1675 1575 1675
Text Label 2075 1675 2    50   ~ 0
V_Battery_EN
Connection ~ 975  1575
Wire Wire Line
	975  1575 2075 1575
Wire Wire Line
	1900 2125 2075 2125
Connection ~ 1575 1675
Wire Wire Line
	1575 1675 2075 1675
Connection ~ 1575 2125
Wire Wire Line
	1575 2125 1600 2125
Wire Wire Line
	975  2125 1575 2125
$Comp
L power:+1V8 #PWR?
U 1 1 5F0D121A
P 10175 1350
F 0 "#PWR?" H 10175 1200 50  0001 C CNN
F 1 "+1V8" H 10190 1523 50  0000 C CNN
F 2 "" H 10175 1350 50  0001 C CNN
F 3 "" H 10175 1350 50  0001 C CNN
	1    10175 1350
	1    0    0    -1  
$EndComp
Connection ~ 10175 1350
Wire Wire Line
	10175 1350 10275 1350
$EndSCHEMATC
