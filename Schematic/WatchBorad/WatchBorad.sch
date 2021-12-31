EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Notes Line
	600  6300 600  7700
Wire Notes Line
	575  7775 575  8825
$Sheet
S 8000 4500 750  1675
U 5E9B1DCE
F0 "MCU" 50
F1 "MCU.sch" 50
F2 "PB_1_MCU" I R 8750 4675 50 
F3 "PB_2_MCU" I R 8750 4750 50 
F4 "PB_3_MCU" I R 8750 5800 50 
F5 "PB_4_MCU" I R 8750 5875 50 
F6 "PB_5_MCU" I R 8750 5950 50 
F7 "Enable_motor" O R 8750 6075 50 
F8 "V3V3" I L 8000 5950 50 
F9 "SDA_FG" B R 8750 4900 50 
F10 "SCL_FG" I R 8750 4975 50 
F11 "FG_OD_ALRT_N" I R 8750 5050 50 
$EndSheet
$Sheet
S 9375 4500 1050 725 
U 5F913559
F0 "PSU_logic" 50
F1 "PSU_logic.sch" 50
F2 "PB_1_MCU" O L 9375 4675 50 
F3 "PB_2_MCU" O L 9375 4750 50 
F4 "V_OUT_MUX" O L 9375 5175 50 
F5 "SDA_FG" B L 9375 4900 50 
F6 "SCL_FG" I L 9375 4975 50 
F7 "FG_OD_ALRT_N" O L 9375 5050 50 
$EndSheet
$Sheet
S 9375 5550 1050 575 
U 5F988DA5
F0 "DCDC&PB" 50
F1 "DCDC&PB.sch" 50
F2 "V3V3" O R 10425 5675 50 
F3 "PB_3_MCU_N" O L 9375 5800 50 
F4 "PB_4_MCU_N" O L 9375 5875 50 
F5 "PB_5_MCU_N" O L 9375 5950 50 
F6 "Enable_motor" I L 9375 6075 50 
F7 "DCDC_VIN" I L 9375 5650 50 
$EndSheet
Wire Wire Line
	9375 5175 9325 5175
Wire Wire Line
	9325 5175 9325 5650
Wire Wire Line
	9325 5650 9375 5650
Wire Wire Line
	8000 5950 7900 5950
Wire Wire Line
	7900 5950 7900 6400
Wire Wire Line
	7900 6400 10650 6400
Wire Wire Line
	10650 6400 10650 5675
Wire Wire Line
	10650 5675 10425 5675
Wire Wire Line
	8750 5950 9375 5950
Wire Wire Line
	8750 5875 9375 5875
Wire Wire Line
	8750 6075 9375 6075
Wire Wire Line
	8750 5800 9375 5800
Wire Wire Line
	8750 4675 9375 4675
Wire Wire Line
	9375 4750 8750 4750
Wire Wire Line
	8750 4975 9375 4975
Wire Wire Line
	9375 4900 8750 4900
Wire Wire Line
	8750 5050 9375 5050
$EndSCHEMATC
