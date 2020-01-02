EESchema Schematic File Version 4
LIBS:Pistoke-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
Title "Smart socket"
Date "14.01.2018"
Rev "0.2"
Comp "Lauri Peltonen"
Comment1 "nRF24L01 version"
Comment2 "Relays and feedback"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:Q_NPN_BEC Q301
U 1 1 5A5F6268
P 4350 2300
F 0 "Q301" H 4550 2375 50  0000 L CNN
F 1 "BC817" H 4550 2300 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 4550 2225 50  0001 L CIN
F 3 "" H 4350 2300 50  0000 L CNN
	1    4350 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 5A5F6277
P 4450 2650
F 0 "#PWR023" H 4450 2400 50  0001 C CNN
F 1 "GND" H 4450 2500 50  0000 C CNN
F 2 "" H 4450 2650 50  0000 C CNN
F 3 "" H 4450 2650 50  0000 C CNN
	1    4450 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 1050 4450 1150
Wire Wire Line
	4450 2650 4450 2500
Wire Wire Line
	4450 1850 4450 2000
$Comp
L Device:D D301
U 1 1 5A5F6280
P 3800 1500
F 0 "D301" H 3800 1600 50  0000 C CNN
F 1 "D" H 3800 1400 50  0000 C CNN
F 2 "Diodes_SMD:D_SMB_Handsoldering" H 3800 1500 50  0001 C CNN
F 3 "" H 3800 1500 50  0000 C CNN
	1    3800 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	3800 1650 3800 2000
Wire Wire Line
	3350 2000 3800 2000
Connection ~ 4450 2000
Wire Wire Line
	3800 1350 3800 1150
Wire Wire Line
	3800 1150 4450 1150
Connection ~ 4450 1150
$Comp
L Device:R R301
U 1 1 5A5F628D
P 3850 2300
F 0 "R301" V 3930 2300 50  0000 C CNN
F 1 "1k" V 3850 2300 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3780 2300 50  0001 C CNN
F 3 "" H 3850 2300 50  0000 C CNN
	1    3850 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	4000 2300 4100 2300
$Comp
L Device:Q_NPN_BEC Q302
U 1 1 5A5F629C
P 4350 5750
F 0 "Q302" H 4550 5825 50  0000 L CNN
F 1 "BC817" H 4550 5750 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 4550 5675 50  0001 L CIN
F 3 "" H 4350 5750 50  0000 L CNN
	1    4350 5750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR024
U 1 1 5A5F62A9
P 4450 6100
F 0 "#PWR024" H 4450 5850 50  0001 C CNN
F 1 "GND" H 4450 5950 50  0000 C CNN
F 2 "" H 4450 6100 50  0000 C CNN
F 3 "" H 4450 6100 50  0000 C CNN
	1    4450 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 4400 4450 4650
Wire Wire Line
	4450 6100 4450 5950
Wire Wire Line
	4450 5250 4450 5450
$Comp
L Device:D D304
U 1 1 5A5F62B2
P 3800 5000
F 0 "D304" H 3800 5100 50  0000 C CNN
F 1 "D" H 3800 4900 50  0000 C CNN
F 2 "Diodes_SMD:D_SMB_Handsoldering" H 3800 5000 50  0001 C CNN
F 3 "" H 3800 5000 50  0000 C CNN
	1    3800 5000
	0    1    1    0   
$EndComp
Wire Wire Line
	3800 5150 3800 5450
Wire Wire Line
	3350 5450 3800 5450
Connection ~ 4450 5450
Wire Wire Line
	3800 4850 3800 4650
Wire Wire Line
	3800 4650 4450 4650
Connection ~ 4450 4650
$Comp
L Device:R R309
U 1 1 5A5F62BF
P 3850 5750
F 0 "R309" V 3930 5750 50  0000 C CNN
F 1 "1k" V 3850 5750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3780 5750 50  0001 C CNN
F 3 "" H 3850 5750 50  0000 C CNN
	1    3850 5750
	0    1    1    0   
$EndComp
Wire Wire Line
	4000 5750 4100 5750
Wire Wire Line
	5050 4300 5050 4600
Wire Wire Line
	5050 950  5050 1300
Text Notes 5950 2000 0    60   ~ 0
Creepage 2.5 mm
Text Notes 7350 6150 1    60   ~ 0
Strain relief near pads
Text Notes 7350 2600 1    60   ~ 0
Strain relief near pads
Text Label 5600 2050 0    60   ~ 0
Lout1
Text Label 5700 5600 0    60   ~ 0
Lout2
Text Label 4300 2000 2    60   ~ 0
Relay1
Text Label 4250 5450 2    60   ~ 0
Relay2
Wire Wire Line
	2800 2300 3700 2300
Wire Wire Line
	2650 5750 3700 5750
Text Label 3350 2300 2    60   ~ 0
CtrlRelay1
Text Label 3350 5750 2    60   ~ 0
CtrlRelay2
$Comp
L Device:R R310
U 1 1 5A5F63BF
P 4100 6000
F 0 "R310" V 4180 6000 50  0000 C CNN
F 1 "10k" V 4100 6000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4030 6000 50  0001 C CNN
F 3 "" H 4100 6000 50  0000 C CNN
	1    4100 6000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR025
U 1 1 5A5F63C6
P 4100 6250
F 0 "#PWR025" H 4100 6000 50  0001 C CNN
F 1 "GND" H 4100 6100 50  0000 C CNN
F 2 "" H 4100 6250 50  0000 C CNN
F 3 "" H 4100 6250 50  0000 C CNN
	1    4100 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 5850 4100 5750
Connection ~ 4100 5750
Wire Wire Line
	4100 6250 4100 6150
$Comp
L Device:R R303
U 1 1 5A5F63CF
P 4100 2600
F 0 "R303" V 4180 2600 50  0000 C CNN
F 1 "10k" V 4100 2600 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4030 2600 50  0001 C CNN
F 3 "" H 4100 2600 50  0000 C CNN
	1    4100 2600
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR026
U 1 1 5A5F63D6
P 4100 2850
F 0 "#PWR026" H 4100 2600 50  0001 C CNN
F 1 "GND" H 4100 2700 50  0000 C CNN
F 2 "" H 4100 2850 50  0000 C CNN
F 3 "" H 4100 2850 50  0000 C CNN
	1    4100 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 2850 4100 2750
Wire Wire Line
	4100 2450 4100 2300
Connection ~ 4100 2300
Text HLabel 9200 900  2    60   Input ~ 0
L
Text HLabel 9200 1100 2    60   Input ~ 0
N
Text HLabel 9200 1300 2    60   Input ~ 0
Earth
Text Label 8950 900  2    60   ~ 0
L
Text Label 5050 950  2    60   ~ 0
L
Text Label 5050 4300 2    60   ~ 0
L
Text Label 8950 1100 2    60   ~ 0
N
Text Label 8950 1300 2    60   ~ 0
Earth
Wire Wire Line
	9200 900  8950 900 
Wire Wire Line
	8950 1100 9200 1100
Wire Wire Line
	9200 1300 8950 1300
Text HLabel 2800 2300 0    60   Input ~ 0
Ctrl1
Text HLabel 2650 5750 0    60   Input ~ 0
Ctrl2
Wire Notes Line
	4850 650  4850 7000
Text Notes 5000 3750 1    60   ~ 0
Isolation > 5mm
$Comp
L conn:CONN_01X01 P302
U 1 1 5A63DF64
P 7100 5600
F 0 "P302" H 7100 5750 50  0000 C CNN
F 1 "CONN_01X01" V 7200 5600 50  0000 C CNN
F 2 "Wire_Pads:SolderWirePad_single_2mmDrill" H 7100 5600 50  0001 C CNN
F 3 "" H 7100 5600 50  0000 C CNN
	1    7100 5600
	1    0    0    -1  
$EndComp
$Comp
L conn:CONN_01X01 P301
U 1 1 5A63DFE6
P 7100 2050
F 0 "P301" H 7100 2200 50  0000 C CNN
F 1 "CONN_01X01" V 7200 2050 50  0000 C CNN
F 2 "Wire_Pads:SolderWirePad_single_2mmDrill" H 7100 2050 50  0001 C CNN
F 3 "" H 7100 2050 50  0000 C CNN
	1    7100 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 1800 5050 2050
Wire Wire Line
	5050 2050 5450 2050
Wire Wire Line
	5050 5200 5050 5600
Wire Wire Line
	5050 5600 5450 5600
$Comp
L Device:LED D302
U 1 1 5A616DC8
P 3350 1350
F 0 "D302" H 3350 1450 50  0000 C CNN
F 1 "LED" H 3350 1250 50  0000 C CNN
F 2 "LEDs:LED_PLCC-2" H 3350 1350 50  0001 C CNN
F 3 "" H 3350 1350 50  0000 C CNN
	1    3350 1350
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R302
U 1 1 5A616E45
P 3350 1750
F 0 "R302" V 3430 1750 50  0000 C CNN
F 1 "10k" V 3350 1750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3280 1750 50  0001 C CNN
F 3 "" H 3350 1750 50  0000 C CNN
	1    3350 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 1050 3350 1200
Wire Wire Line
	3350 1500 3350 1600
Wire Wire Line
	3350 1900 3350 2000
Connection ~ 3800 2000
$Comp
L Device:LED D303
U 1 1 5A6177DC
P 3350 4750
F 0 "D303" H 3350 4850 50  0000 C CNN
F 1 "LED" H 3350 4650 50  0000 C CNN
F 2 "LEDs:LED_PLCC-2" H 3350 4750 50  0001 C CNN
F 3 "" H 3350 4750 50  0000 C CNN
	1    3350 4750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R304
U 1 1 5A6177E2
P 3350 5150
F 0 "R304" V 3430 5150 50  0000 C CNN
F 1 "10k" V 3350 5150 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3280 5150 50  0001 C CNN
F 3 "" H 3350 5150 50  0000 C CNN
	1    3350 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 4450 3350 4600
Wire Wire Line
	3350 4900 3350 5000
Wire Wire Line
	3350 5300 3350 5450
Connection ~ 3800 5450
Text Notes 4200 1750 1    60   ~ 0
530 mW
Text Notes 4200 5200 1    60   ~ 0
530 mW
$Comp
L Symbols_EN60617_13Mar2013:RELAY-2XCHANGE_DPDT_DetachedRepresentation_RevE_Date13Sep2012 K401
U 3 1 5A89FFC0
P 5000 1550
F 0 "K401" V 5350 1600 50  0000 C CNN
F 1 "GZSH-12V" H 5000 1250 50  0001 C CNN
F 2 "Pistoke:Relay_SPDT_Goodsky_GZ" H 5000 1550 50  0001 C CNN
F 3 "" H 5000 1550 50  0000 C CNN
	3    5000 1550
	1    0    0    1   
$EndComp
$Comp
L Symbols_EN60617_13Mar2013:RELAY-2XCHANGE_DPDT_DetachedRepresentation_RevE_Date13Sep2012 K401
U 1 1 5A8A006A
P 4800 1650
F 0 "K401" V 4700 1700 50  0000 C CNN
F 1 "GZSH-12V" H 4800 1350 50  0001 C CNN
F 2 "Pistoke:Relay_SPDT_Goodsky_GZ" H 4800 1650 50  0001 C CNN
F 3 "" H 4800 1650 50  0000 C CNN
	1    4800 1650
	1    0    0    -1  
$EndComp
$Comp
L Symbols_EN60617_13Mar2013:RELAY-2XCHANGE_DPDT_DetachedRepresentation_RevE_Date13Sep2012 K401
U 2 1 5A8A022C
P 4900 1550
F 0 "K401" V 4950 1600 50  0000 C CNN
F 1 "GZSH-12V" H 4900 1250 50  0001 C CNN
F 2 "Pistoke:Relay_SPDT_Goodsky_GZ" H 4900 1550 50  0001 C CNN
F 3 "" H 4900 1550 50  0000 C CNN
	2    4900 1550
	1    0    0    1   
$EndComp
Wire Wire Line
	5450 1400 5450 1300
Wire Wire Line
	5050 1300 5450 1300
Connection ~ 5050 1300
Wire Wire Line
	5450 1800 5450 2050
Connection ~ 5450 2050
$Comp
L Symbols_EN60617_13Mar2013:RELAY-2XCHANGE_DPDT_DetachedRepresentation_RevE_Date13Sep2012 K402
U 1 1 5A8A22A9
P 4800 5050
F 0 "K402" V 4700 5100 50  0000 C CNN
F 1 "GZSH-12V" H 4800 4750 50  0001 C CNN
F 2 "Pistoke:Relay_SPDT_Goodsky_GZ" H 4800 5050 50  0001 C CNN
F 3 "" H 4800 5050 50  0000 C CNN
	1    4800 5050
	1    0    0    -1  
$EndComp
$Comp
L Symbols_EN60617_13Mar2013:RELAY-2XCHANGE_DPDT_DetachedRepresentation_RevE_Date13Sep2012 K402
U 2 1 5A8A319B
P 4900 4950
F 0 "K402" V 4950 5000 50  0000 C CNN
F 1 "GZSH-12V" H 4900 4650 50  0001 C CNN
F 2 "Pistoke:Relay_SPDT_Goodsky_GZ" H 4900 4950 50  0001 C CNN
F 3 "" H 4900 4950 50  0000 C CNN
	2    4900 4950
	1    0    0    1   
$EndComp
$Comp
L Symbols_EN60617_13Mar2013:RELAY-2XCHANGE_DPDT_DetachedRepresentation_RevE_Date13Sep2012 K402
U 3 1 5A8A322A
P 5000 4950
F 0 "K402" V 5350 5000 50  0000 C CNN
F 1 "GZSH-12V" H 5000 4650 50  0001 C CNN
F 2 "Pistoke:Relay_SPDT_Goodsky_GZ" H 5000 4950 50  0001 C CNN
F 3 "" H 5000 4950 50  0000 C CNN
	3    5000 4950
	1    0    0    1   
$EndComp
Wire Wire Line
	5050 4600 5450 4600
Wire Wire Line
	5450 4600 5450 4800
Connection ~ 5050 4600
Wire Wire Line
	5450 5200 5450 5600
Connection ~ 5450 5600
Wire Wire Line
	5200 1800 5200 1900
Wire Wire Line
	5200 1900 5600 1900
Wire Wire Line
	5800 1900 5800 1300
Connection ~ 5450 1300
Wire Wire Line
	5600 1800 5600 1900
Connection ~ 5600 1900
Wire Wire Line
	5200 5200 5200 5350
Wire Wire Line
	5200 5350 5600 5350
Wire Wire Line
	5850 5350 5850 4600
Connection ~ 5450 4600
Wire Wire Line
	5600 5200 5600 5350
Connection ~ 5600 5350
$Comp
L power:+12V #PWR027
U 1 1 5B4A6A08
P 4450 4400
F 0 "#PWR027" H 4450 4250 50  0001 C CNN
F 1 "+12V" H 4450 4540 50  0000 C CNN
F 2 "" H 4450 4400 50  0000 C CNN
F 3 "" H 4450 4400 50  0000 C CNN
	1    4450 4400
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR028
U 1 1 5B4A6A56
P 4450 1050
F 0 "#PWR028" H 4450 900 50  0001 C CNN
F 1 "+12V" H 4450 1190 50  0000 C CNN
F 2 "" H 4450 1050 50  0000 C CNN
F 3 "" H 4450 1050 50  0000 C CNN
	1    4450 1050
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR029
U 1 1 5B4A73EB
P 3350 4450
F 0 "#PWR029" H 3350 4300 50  0001 C CNN
F 1 "+12V" H 3350 4590 50  0000 C CNN
F 2 "" H 3350 4450 50  0000 C CNN
F 3 "" H 3350 4450 50  0000 C CNN
	1    3350 4450
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR030
U 1 1 5B4A7478
P 3350 1050
F 0 "#PWR030" H 3350 900 50  0001 C CNN
F 1 "+12V" H 3350 1190 50  0000 C CNN
F 2 "" H 3350 1050 50  0000 C CNN
F 3 "" H 3350 1050 50  0000 C CNN
	1    3350 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2000 4450 2100
Wire Wire Line
	4450 1150 4450 1400
Wire Wire Line
	4450 5450 4450 5550
Wire Wire Line
	4450 4650 4450 4800
Wire Wire Line
	4100 5750 4150 5750
Wire Wire Line
	4100 2300 4150 2300
Wire Wire Line
	3800 2000 4450 2000
Wire Wire Line
	3800 5450 4450 5450
Wire Wire Line
	5050 1300 5050 1400
Wire Wire Line
	5450 2050 6900 2050
Wire Wire Line
	5050 4600 5050 4800
Wire Wire Line
	5450 5600 6900 5600
Wire Wire Line
	5450 1300 5800 1300
Wire Wire Line
	5600 1900 5800 1900
Wire Wire Line
	5450 4600 5850 4600
Wire Wire Line
	5600 5350 5850 5350
$EndSCHEMATC
