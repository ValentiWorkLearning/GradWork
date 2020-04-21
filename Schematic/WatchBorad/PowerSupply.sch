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
L PowerMuxes:TPS2115APWR U2
U 1 1 5E9C2ACA
P 2875 1625
F 0 "U2" H 2875 2150 60  0000 C CNN
F 1 "TPS2115APWR" H 2875 2025 60  0000 C CNN
F 2 "Housings_SSOP:TSSOP-8_4.4x3mm_Pitch0.65mm" H 2875 2115 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1809131529_Texas-Instruments-TPS2115APWR_C70287.pdf" H 2875 1375 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/Switching-Controllers_Texas-Instruments_TPS2115APWR_Texas-Instruments-Texas-Instruments-TPS2115APWR_C70287.html" H 2875 1625 50  0001 C CNN "lcsc"
	1    2875 1625
	1    0    0    -1  
$EndComp
Wire Wire Line
	2075 2125 1925 2125
$Comp
L Device:R R?
U 1 1 5E9CA89F
P 1775 2125
AR Path="/5EA4867C/5E9CA89F" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5E9CA89F" Ref="R2"  Part="1" 
F 0 "R2" V 1568 2125 50  0000 C CNN
F 1 "330" V 1659 2125 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1705 2125 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Others_Viking-Tech-ARG03FTC3300_C217969.html" H 1775 2125 50  0001 C CNN
	1    1775 2125
	0    1    1    0   
$EndComp
Text Label 1950 2125 0    50   ~ 0
Rlim
Text Label 1300 2125 0    50   ~ 0
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
P 1150 1825
AR Path="/5EA4867C/5E9D3BD7" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5E9D3BD7" Ref="C2"  Part="1" 
F 0 "C2" H 1175 1900 50  0000 L CNN
F 1 "100 nF" V 1000 1700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1188 1675 50  0001 C CNN
F 3 "~" H 1150 1825 50  0001 C CNN
	1    1150 1825
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E9D4159
P 1550 1825
AR Path="/5EA4867C/5E9D4159" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5E9D4159" Ref="C3"  Part="1" 
F 0 "C3" H 1575 1900 50  0000 L CNN
F 1 "100 nF" V 1400 1700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1588 1675 50  0001 C CNN
F 3 "~" H 1550 1825 50  0001 C CNN
	1    1550 1825
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 1675 2075 1675
Wire Wire Line
	1150 1675 1150 1575
Wire Wire Line
	1150 1575 2075 1575
Wire Wire Line
	1150 1975 1150 2125
Wire Wire Line
	1150 2125 1550 2125
Wire Wire Line
	1550 1975 1550 2125
Connection ~ 1550 2125
Wire Wire Line
	1550 2125 1625 2125
Text Label 1550 1575 0    50   ~ 0
V_USB
Text Label 1700 1675 0    50   ~ 0
V_Battery_P
Wire Wire Line
	3675 1375 4225 1375
NoConn ~ 3675 1475
Text Label 4225 1375 2    50   ~ 0
V_OUT_MUX
$Comp
L Device:Battery_Cell BT1
U 1 1 5E9EB660
P 4325 5800
F 0 "BT1" H 4443 5896 50  0000 L CNN
F 1 "Battery_Cell" H 4443 5805 50  0000 L CNN
F 2 "" V 4325 5860 50  0001 C CNN
F 3 "https://aliexpress.ru/item/33000396152.html?spm=a2g0o.productlist.0.0.43416af464CXwu&algo_pvid=e6706777-cde6-4668-9867-8799ba4921bb&algo_expid=e6706777-cde6-4668-9867-8799ba4921bb-0&btsid=0b8b037215874644191236041ea897&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_" V 4325 5860 50  0001 C CNN
	1    4325 5800
	-1   0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR01
U 1 1 5E9EC7E5
P 4325 5225
F 0 "#PWR01" H 4325 5075 50  0001 C CNN
F 1 "+BATT" H 4340 5398 50  0000 C CNN
F 2 "" H 4325 5225 50  0001 C CNN
F 3 "" H 4325 5225 50  0001 C CNN
	1    4325 5225
	-1   0    0    -1  
$EndComp
Text Label 3725 6000 2    50   ~ 0
GND
Text Label 4325 5375 2    50   ~ 0
V_Battery_P
Wire Wire Line
	3050 5625 3500 5625
$Comp
L BatteryManagmentLocal:BQ21040DBVT U1
U 1 1 5EA1363C
P 1450 5525
F 0 "U1" H 2250 5912 60  0000 C CNN
F 1 "BQ21040DBVT" H 2250 5806 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6" H 2250 5765 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Texas-Instruments-TI-BQ21040DBVR_C202311.pdf" H 2250 5806 60  0001 C CNN
F 4 "https://lcsc.com/product-detail/PMIC-Battery-Management_Texas-Instruments_BQ21040DBVR_Texas-Instruments-Texas-Instruments-BQ21040DBVR_C202311.html" H 1450 5525 50  0001 C CNN "lcsc"
	1    1450 5525
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 5375 1450 5425
Wire Wire Line
	1450 5675 1450 5625
$Comp
L Device:R R?
U 1 1 5E9FD451
P 1225 5825
AR Path="/5EA4867C/5E9FD451" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5E9FD451" Ref="R1"  Part="1" 
F 0 "R1" V 1300 5775 50  0000 L CNN
F 1 "10k" V 1150 5750 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1155 5825 50  0001 C CNN
F 3 "~" H 1225 5825 50  0001 C CNN
	1    1225 5825
	0    1    -1   0   
$EndComp
Wire Wire Line
	1450 5825 1375 5825
Wire Wire Line
	1075 5825 850  5825
Text Label 850  5825 0    50   ~ 0
GND
Text Notes 900  6100 0    50   ~ 0
Set fast charge\ncurrent to 54 mA
NoConn ~ 3050 5825
Wire Wire Line
	1050 5675 1450 5675
Wire Wire Line
	1050 5375 1450 5375
$Comp
L Device:C C?
U 1 1 5E9FB26C
P 1050 5525
AR Path="/5EA4867C/5E9FB26C" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5E9FB26C" Ref="C1"  Part="1" 
F 0 "C1" H 1075 5600 50  0000 L CNN
F 1 "1 uF 16V" V 900 5400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1088 5375 50  0001 C CNN
F 3 "~" H 1050 5525 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R105K160NT_C475249.html" H 1050 5525 50  0001 C CNN "LCSC"
	1    1050 5525
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 5925 3500 6000
Wire Wire Line
	3500 6000 3725 6000
Wire Wire Line
	4325 5225 4325 5425
Wire Wire Line
	3050 5425 4325 5425
Connection ~ 4325 5425
Wire Wire Line
	4325 5425 4325 5600
$Comp
L DCDC_Local:TPS62740DSST U4
U 1 1 5EA00C58
P 7475 1450
F 0 "U4" H 8275 1837 60  0000 C CNN
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
	4500 600  4500 2500
Wire Notes Line
	4500 2500 750  2500
Wire Notes Line
	750  2500 750  600 
Wire Notes Line
	750  600  4500 600 
Text Notes 2125 4875 0    100  ~ 0
Battery charger\n
Wire Notes Line
	4500 4600 4500 6400
Wire Notes Line
	4500 6400 750  6400
Wire Notes Line
	750  6400 750  4600
Wire Notes Line
	750  4600 4500 4600
$Comp
L Device:C C?
U 1 1 5EA15E96
P 6875 1525
AR Path="/5EA4867C/5EA15E96" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EA15E96" Ref="C4"  Part="1" 
F 0 "C4" H 6900 1600 50  0000 L CNN
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
L pspice:INDUCTOR L1
U 1 1 5EA18A55
P 9800 1350
F 0 "L1" H 9800 1475 50  0000 C CNN
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
Text Label 9250 1350 0    50   ~ 0
L_SW
Wire Wire Line
	10050 1350 10275 1350
Text Label 7325 1350 2    50   ~ 0
V_OUT_MUX
Text Label 10475 1350 2    50   ~ 0
V1V8
$Comp
L Supervisors:MAX809STRG U3
U 1 1 5EA21C4A
P 5975 2075
F 0 "U3" H 5975 2542 50  0000 C CNN
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
	6275 2075 7250 2075
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
AR Path="/5E9C1C3A/5EA4839B" Ref="C6"  Part="1" 
F 0 "C6" H 10525 1575 50  0000 L CNN
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
L BatteryManagmentLocal:STC3100IQT U5
U 1 1 5EA36940
P 8250 4975
F 0 "U5" H 8250 5390 50  0000 C CNN
F 1 "STC3100IQT" H 8250 5275 50  0000 C CNN
F 2 "Housings_DFN_QFN:DFN-8-1EP_3x3mm_Pitch0.5mm" H 8375 5750 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1804172029_STMicroelectronics-STC3100IQT_C155587.pdf" H 8250 4975 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/_STMicroelectronics_STC3100IQT_STC3100IQT_C155587.html" H 8625 5600 50  0001 C CNN "lcsc"
	1    8250 4975
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5EA405B7
P 9325 5450
AR Path="/5EA4867C/5EA405B7" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5EA405B7" Ref="R7"  Part="1" 
F 0 "R7" V 9250 5400 50  0000 L CNN
F 1 "2.2 OHM 1%" V 9425 5200 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9255 5450 50  0001 C CNN
F 3 "~" H 9325 5450 50  0001 C CNN
	1    9325 5450
	1    0    0    1   
$EndComp
Text Label 9175 5775 2    50   ~ 0
GND
$Comp
L Device:R R?
U 1 1 5E9F16F1
P 3500 5775
AR Path="/5EA4867C/5E9F16F1" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5E9F16F1" Ref="R3"  Part="1" 
F 0 "R3" V 3425 5725 50  0000 L CNN
F 1 "10k" V 3575 5700 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 3430 5775 50  0001 C CNN
F 3 "~" H 3500 5775 50  0001 C CNN
	1    3500 5775
	1    0    0    1   
$EndComp
Wire Wire Line
	4325 5900 4325 6275
Wire Wire Line
	4325 6275 3850 6275
Text Label 3850 6275 0    50   ~ 0
V_Battery_N
Wire Wire Line
	8800 5025 9325 5025
Wire Wire Line
	9325 5025 9325 5300
Text Label 8900 5025 0    50   ~ 0
V_Battery_N
Wire Wire Line
	8950 5125 8950 5775
Wire Wire Line
	9325 5600 9325 5775
Text Notes 8925 6075 0    50   ~ 0
GND (pin 5) should be directly \nconnected to negedge resistor\npin that is connected to GND plane 
$Comp
L Device:C C?
U 1 1 5EA50EBE
P 9750 5475
AR Path="/5EA4867C/5EA50EBE" Ref="C?"  Part="1" 
AR Path="/5E9C1C3A/5EA50EBE" Ref="C5"  Part="1" 
F 0 "C5" H 9775 5550 50  0000 L CNN
F 1 "1 uF 16V" V 9600 5350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9788 5325 50  0001 C CNN
F 3 "~" H 9750 5475 50  0001 C CNN
F 4 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_SANYEAR-C0603X5R105K160NT_C475249.html" H 9750 5475 50  0001 C CNN "LCSC"
	1    9750 5475
	1    0    0    -1  
$EndComp
Text Label 9325 4925 2    50   ~ 0
V_Battery_P
Wire Wire Line
	8800 4925 9325 4925
Wire Wire Line
	8800 4825 9750 4825
Wire Wire Line
	9750 4825 9750 5325
Wire Wire Line
	9750 5625 9750 5775
Connection ~ 9325 5775
Wire Wire Line
	9750 5775 9325 5775
NoConn ~ 7700 4825
$Comp
L Device:R R?
U 1 1 5EA5E00D
P 6750 4775
AR Path="/5EA4867C/5EA5E00D" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5EA5E00D" Ref="R4"  Part="1" 
F 0 "R4" V 6675 4725 50  0000 L CNN
F 1 "10k" V 6825 4700 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6680 4775 50  0001 C CNN
F 3 "~" H 6750 4775 50  0001 C CNN
	1    6750 4775
	1    0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5EA5F2E9
P 7000 4775
AR Path="/5EA4867C/5EA5F2E9" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5EA5F2E9" Ref="R5"  Part="1" 
F 0 "R5" V 6925 4725 50  0000 L CNN
F 1 "10k" V 7075 4700 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6930 4775 50  0001 C CNN
F 3 "~" H 7000 4775 50  0001 C CNN
	1    7000 4775
	1    0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5EA5F7B3
P 7425 4925
AR Path="/5EA4867C/5EA5F7B3" Ref="R?"  Part="1" 
AR Path="/5E9C1C3A/5EA5F7B3" Ref="R6"  Part="1" 
F 0 "R6" V 7250 4875 50  0000 L CNN
F 1 "200k 0.1%" V 7325 4725 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 7355 4925 50  0001 C CNN
F 3 "~" H 7425 4925 50  0001 C CNN
	1    7425 4925
	0    -1   1    0   
$EndComp
Wire Wire Line
	7575 4925 7700 4925
Wire Wire Line
	7275 4925 7125 4925
Text Label 7125 4925 0    50   ~ 0
GND
Wire Wire Line
	7000 4925 7000 5025
Wire Wire Line
	7000 5025 7700 5025
Wire Wire Line
	6750 4925 6750 5125
Wire Wire Line
	6750 5125 7700 5125
Wire Wire Line
	6750 4625 6750 4525
Wire Wire Line
	6750 4525 7000 4525
Wire Wire Line
	7000 4525 7000 4625
Text Label 6800 4525 0    50   ~ 0
V1V8
Wire Wire Line
	8950 5775 9325 5775
Wire Wire Line
	8950 5125 8800 5125
Wire Wire Line
	8800 5200 8800 5350
Wire Wire Line
	8800 5350 8625 5350
Text Label 8625 5350 0    50   ~ 0
GND
Text Notes 8350 5525 0    50   ~ 0
9 pin directly \nto plan GND\n
Text Notes 8175 4375 0    100  ~ 0
Fuel gauge
Wire Notes Line
	6200 4100 10725 4100
Wire Notes Line
	10725 4100 10725 6375
Wire Notes Line
	10725 6375 6200 6375
Wire Notes Line
	6200 6375 6200 4100
Text Notes 7750 900  0    100  ~ 0
DCDC converter\n
Wire Notes Line
	10825 625  10825 3200
Wire Notes Line
	10825 3200 4900 3200
Wire Notes Line
	4900 3200 4900 625 
Wire Notes Line
	4900 625  10825 625 
$Comp
L USB_connectors:TYPE-C-31-M-17 J1
U 1 1 5EA8D0C3
P 1450 3900
F 0 "J1" H 1683 4761 100 0000 C CNN
F 1 "TYPE-C-31-M-17" H 1683 4761 100 0001 C CNN
F 2 "" H 1450 3900 100 0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1903211732_Korean-Hroparts-Elec-TYPE-C-31-M-17_C283540.pdf" H 1450 3900 100 0001 C CNN
F 4 "https://lcsc.com/product-detail/Others_Korean-Hroparts-Elec-TYPE-C-31-M-17_C283540.html" H 1450 3900 50  0001 C CNN "lcsc"
	1    1450 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 3675 1900 3750
Connection ~ 1900 3750
Wire Wire Line
	1900 3750 1900 3825
Wire Wire Line
	1900 3825 2325 3825
Connection ~ 1900 3825
Text Label 2325 3825 2    50   ~ 0
GND
NoConn ~ 1900 3550
NoConn ~ 1900 3475
Wire Wire Line
	1900 3250 2325 3250
Wire Wire Line
	1900 3250 1900 3325
Connection ~ 1900 3250
Text Label 2325 3250 2    50   ~ 0
V_USB
Text HLabel 10575 1350 2    50   Output ~ 0
V1V8
Wire Wire Line
	10575 1350 10500 1350
Connection ~ 10500 1350
Text Notes 2100 3550 0    50   ~ 0
USB for power \nsupply only\n
$EndSCHEMATC
