EESchema Schematic File Version 4
LIBS:Pistoke-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 4
Title "Smart socket"
Date "14.01.2018"
Rev "0.2"
Comp "Lauri Peltonen"
Comment1 "nRF24L01 version"
Comment2 "Main sheet"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:Earth #PWR01
U 1 1 5A5BDEEC
P 10300 3950
F 0 "#PWR01" H 10300 3700 50  0001 C CNN
F 1 "Earth" H 10300 3800 50  0001 C CNN
F 2 "" H 10300 3950 50  0000 C CNN
F 3 "" H 10300 3950 50  0000 C CNN
	1    10300 3950
	1    0    0    -1  
$EndComp
$Comp
L power:HT #PWR02
U 1 1 5A5BDF18
P 10100 1450
F 0 "#PWR02" H 10100 1570 50  0001 C CNN
F 1 "HT" H 10100 1540 50  0000 C CNN
F 2 "" H 10100 1450 50  0000 C CNN
F 3 "" H 10100 1450 50  0000 C CNN
	1    10100 1450
	1    0    0    -1  
$EndComp
$Comp
L Pistoke-rescue:GNDPWR #PWR03
U 1 1 5A5BDFBC
P 9450 3050
F 0 "#PWR03" H 9450 2850 50  0001 C CNN
F 1 "GNDPWR" H 9450 2920 50  0000 C CNN
F 2 "" H 9450 3000 50  0000 C CNN
F 3 "" H 9450 3000 50  0000 C CNN
	1    9450 3050
	1    0    0    -1  
$EndComp
Text Notes 9800 2350 0    60   ~ 0
Creepage > 2.5 mm
Wire Wire Line
	10400 3800 10300 3800
Wire Wire Line
	10300 3800 10300 3950
Text Notes 11000 2950 1    60   ~ 0
Strain relief near pads
$Comp
L power:+5V #PWR04
U 1 1 5A5C1E65
P 1250 3400
F 0 "#PWR04" H 1250 3250 50  0001 C CNN
F 1 "+5V" H 1250 3540 50  0000 C CNN
F 2 "" H 1250 3400 50  0000 C CNN
F 3 "" H 1250 3400 50  0000 C CNN
	1    1250 3400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5A5C1E6B
P 1250 4100
F 0 "#PWR05" H 1250 3850 50  0001 C CNN
F 1 "GND" H 1250 3950 50  0000 C CNN
F 2 "" H 1250 4100 50  0000 C CNN
F 3 "" H 1250 4100 50  0000 C CNN
	1    1250 4100
	1    0    0    -1  
$EndComp
$Comp
L Pistoke-rescue:PWR_brick U101
U 1 1 5A5C2451
P 8150 2300
F 0 "U101" H 8150 2600 60  0000 C CNN
F 1 "IRM-03-12" H 8150 2000 60  0000 C CNN
F 2 "Pistoke:IRM-03" H 8150 2300 60  0001 C CNN
F 3 "" H 8150 2300 60  0001 C CNN
	1    8150 2300
	-1   0    0    -1  
$EndComp
Connection ~ 10100 1800
$Comp
L Device:Varistor RV101
U 1 1 5A5C2A13
P 9450 2500
F 0 "RV101" V 9575 2500 50  0000 C CNN
F 1 "EPCOS S14 < 1kV?" V 9325 2500 50  0000 C CNN
F 2 "Varistors:RV_Disc_D9_W3.5_P5" V 9380 2500 50  0001 C CNN
F 3 "" H 9450 2500 50  0000 C CNN
	1    9450 2500
	1    0    0    1   
$EndComp
$Comp
L Device:C C103
U 1 1 5A5C2A8C
P 7800 2800
F 0 "C103" V 7850 2900 50  0000 L TNN
F 1 "2.2nF 3kVDC Y" V 7850 2700 50  0000 R TNN
F 2 "Capacitors_THT:C_Disc_D7.5mm_W5.0mm_P7.50mm" H 7838 2650 50  0001 C CNN
F 3 "" H 7800 2800 50  0000 C CNN
F 4 "Vishay 564R30TSD22" H 7800 2800 60  0001 C CNN "Comment"
	1    7800 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	8850 2800 9000 2800
Wire Wire Line
	8550 2800 7950 2800
Wire Wire Line
	7200 2800 7650 2800
$Comp
L power:+5V #PWR06
U 1 1 5A5C31CA
P 4700 1800
F 0 "#PWR06" H 4700 1650 50  0001 C CNN
F 1 "+5V" H 4700 1940 50  0000 C CNN
F 2 "" H 4700 1800 50  0000 C CNN
F 3 "" H 4700 1800 50  0000 C CNN
	1    4700 1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5A5C356D
P 6950 2800
F 0 "#PWR07" H 6950 2550 50  0001 C CNN
F 1 "GND" H 6950 2650 50  0000 C CNN
F 2 "" H 6950 2800 50  0000 C CNN
F 3 "" H 6950 2800 50  0000 C CNN
	1    6950 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C104
U 1 1 5A5C4C6B
P 8700 2800
F 0 "C104" V 8750 2900 50  0000 L TNN
F 1 "2.2nF 3kVDC Y" V 8750 2700 50  0000 R TNN
F 2 "Capacitors_THT:C_Disc_D7.5mm_W5.0mm_P7.50mm" H 8738 2650 50  0001 C CNN
F 3 "" H 8700 2800 50  0000 C CNN
F 4 "Vishay 564R30TSD22" H 8700 2800 60  0001 C CNN "Comment"
	1    8700 2800
	0    1    1    0   
$EndComp
$Comp
L Device:C C102
U 1 1 5A5C5643
P 6950 2300
F 0 "C102" H 6975 2400 50  0000 L CNN
F 1 "10u" H 6975 2200 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 6988 2150 50  0001 C CNN
F 3 "" H 6950 2300 50  0000 C CNN
	1    6950 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C101
U 1 1 5A5C5709
P 6650 2300
F 0 "C101" H 6675 2400 50  0000 L CNN
F 1 "10u" H 6675 2200 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 6688 2150 50  0001 C CNN
F 3 "" H 6650 2300 50  0000 C CNN
	1    6650 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 3800 2950 3800
Wire Wire Line
	2350 3900 2950 3900
Wire Wire Line
	2350 4000 2950 4000
Wire Wire Line
	2350 3700 2950 3700
Wire Wire Line
	2350 3600 2950 3600
Wire Wire Line
	2350 3500 2950 3500
Text Label 2950 3500 0    60   ~ 0
rfCE
Text Label 2950 3600 0    60   ~ 0
rfCSN
Text Label 2950 3700 0    60   ~ 0
rfCSK
Text Label 2950 3900 0    60   ~ 0
rfMOSI
Text Label 2950 3800 0    60   ~ 0
rfMISO
Text Label 2950 4000 0    60   ~ 0
rfIRQ
$Sheet
S 1500 3400 850  700 
U 5A5E58C6
F0 "RF" 60
F1 "RF.sch" 60
F2 "rfCE" I R 2350 3500 60 
F3 "rfCSN" I R 2350 3600 60 
F4 "rfCSK" I R 2350 3700 60 
F5 "rfMOSI" I R 2350 3900 60 
F6 "rfMISO" I R 2350 3800 60 
F7 "rfIRQ" I R 2350 4000 60 
F8 "rfPWR" I L 1500 3500 60 
F9 "rfGND" I L 1500 4000 60 
$EndSheet
Wire Wire Line
	1500 3500 1250 3500
Wire Wire Line
	1250 3500 1250 3400
Wire Wire Line
	1500 4000 1250 4000
Wire Wire Line
	1250 4000 1250 4100
Text Label 7150 5100 2    60   ~ 0
Ctrl1
Text Label 7150 5200 2    60   ~ 0
Ctrl2
Wire Wire Line
	7600 5100 7150 5100
Wire Wire Line
	7150 5200 7600 5200
$Comp
L power:HT #PWR08
U 1 1 5A626681
P 9050 5050
F 0 "#PWR08" H 9050 5170 50  0001 C CNN
F 1 "HT" H 9050 5140 50  0000 C CNN
F 2 "" H 9050 5050 50  0000 C CNN
F 3 "" H 9050 5050 50  0000 C CNN
	1    9050 5050
	1    0    0    -1  
$EndComp
$Comp
L Pistoke-rescue:GNDPWR #PWR09
U 1 1 5A626707
P 9150 5400
F 0 "#PWR09" H 9150 5200 50  0001 C CNN
F 1 "GNDPWR" H 9150 5270 50  0000 C CNN
F 2 "" H 9150 5350 50  0000 C CNN
F 3 "" H 9150 5350 50  0000 C CNN
	1    9150 5400
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR010
U 1 1 5A62678D
P 8950 5750
F 0 "#PWR010" H 8950 5500 50  0001 C CNN
F 1 "Earth" H 8950 5600 50  0001 C CNN
F 2 "" H 8950 5750 50  0000 C CNN
F 3 "" H 8950 5750 50  0000 C CNN
	1    8950 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 5100 9050 5100
Wire Wire Line
	9050 5100 9050 5050
Wire Wire Line
	8650 5350 9150 5350
Wire Wire Line
	9150 5350 9150 5400
Wire Wire Line
	8650 5550 8950 5550
Wire Wire Line
	8950 5550 8950 5750
Text Label 8250 2800 2    60   ~ 0
Mid
Wire Notes Line
	8100 6450 8100 600 
Text Notes 8200 4600 1    60   ~ 0
Creepage & clearance > 5 mm
Wire Wire Line
	6650 2450 6650 2600
Wire Wire Line
	6650 2600 6950 2600
Wire Wire Line
	6950 2450 6950 2600
Connection ~ 6950 2600
Wire Wire Line
	7200 2450 7200 2600
Connection ~ 7200 2600
Wire Wire Line
	7200 2150 7650 2150
Wire Wire Line
	5900 1950 6200 1950
Wire Wire Line
	6950 1750 6950 1950
Connection ~ 6950 1950
Wire Wire Line
	6650 1950 6650 2150
Wire Wire Line
	9900 1800 10100 1800
Wire Wire Line
	10100 1450 10100 1800
Wire Wire Line
	8650 2150 9450 2150
Wire Wire Line
	8650 2450 9000 2450
Wire Wire Line
	9000 2450 9000 2800
Wire Wire Line
	9450 2650 9450 2800
Connection ~ 9000 2800
Connection ~ 9450 2800
Wire Wire Line
	10100 2800 10100 3100
$Comp
L conn:CONN_01X01 P101
U 1 1 5A63F172
P 10600 1800
F 0 "P101" H 10600 1950 50  0000 C CNN
F 1 "CONN_01X01" V 10700 1800 50  0001 C CNN
F 2 "Wire_Pads:SolderWirePad_single_2mmDrill" H 10600 1800 50  0001 C CNN
F 3 "" H 10600 1800 50  0000 C CNN
	1    10600 1800
	1    0    0    -1  
$EndComp
$Comp
L conn:Screw_Terminal_1x01 J101
U 1 1 5A63F20B
P 10600 3800
F 0 "J101" H 10600 3950 50  0000 C TNN
F 1 "Screw_Terminal_1x01" V 10450 3800 50  0001 C TNN
F 2 "Mounting_Holes:MountingHole_4.3mm_M4_Pad" H 10600 3675 50  0001 C CNN
F 3 "" H 10600 3700 50  0001 C CNN
	1    10600 3800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7300 3550 7200 3550
Wire Wire Line
	7200 3550 7200 3700
$Comp
L conn:Screw_Terminal_1x01 J102
U 1 1 5A61206A
P 7500 3550
F 0 "J102" H 7500 3700 50  0000 C TNN
F 1 "Screw_Terminal_1x01" V 7350 3550 50  0001 C TNN
F 2 "Mounting_Holes:MountingHole_4.3mm_M4_Pad" H 7500 3425 50  0001 C CNN
F 3 "" H 7500 3450 50  0001 C CNN
	1    7500 3550
	-1   0    0    -1  
$EndComp
$Comp
L conn:CONN_01X01 P102
U 1 1 5A613031
P 10600 2800
F 0 "P102" H 10600 2950 50  0000 C CNN
F 1 "CONN_01X01" V 10700 2800 50  0001 C CNN
F 2 "Wire_Pads:SolderWirePad_single_2mmDrill" H 10600 2800 50  0001 C CNN
F 3 "" H 10600 2800 50  0000 C CNN
	1    10600 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5A614D50
P 7200 3700
F 0 "#PWR011" H 7200 3450 50  0001 C CNN
F 1 "GND" H 7200 3550 50  0000 C CNN
F 2 "" H 7200 3700 50  0000 C CNN
F 3 "" H 7200 3700 50  0000 C CNN
	1    7200 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:Fuse F101
U 1 1 5A776F90
P 9750 1800
F 0 "F101" V 9830 1800 50  0000 C CNN
F 1 "Fuse" V 9675 1800 50  0000 C CNN
F 2 "Fuse_Holders_and_Fuses:Fuseholder_Fuse_TR5_Littlefuse-No560_No460" V 9680 1800 50  0001 C CNN
F 3 "" H 9750 1800 50  0000 C CNN
	1    9750 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	9450 1800 9600 1800
Wire Wire Line
	10100 3100 10400 3100
Wire Wire Line
	10100 3350 10400 3350
$Comp
L conn:CONN_01X01 P103
U 1 1 5A77D950
P 10600 3100
F 0 "P103" H 10600 3250 50  0000 C CNN
F 1 "CONN_01X01" V 10700 3100 50  0001 C CNN
F 2 "Wire_Pads:SolderWirePad_single_2mmDrill" H 10600 3100 50  0001 C CNN
F 3 "" H 10600 3100 50  0000 C CNN
	1    10600 3100
	1    0    0    -1  
$EndComp
$Comp
L conn:CONN_01X01 P104
U 1 1 5A77DA26
P 10600 3350
F 0 "P104" H 10600 3500 50  0000 C CNN
F 1 "CONN_01X01" V 10700 3350 50  0001 C CNN
F 2 "Wire_Pads:SolderWirePad_single_2mmDrill" H 10600 3350 50  0001 C CNN
F 3 "" H 10600 3350 50  0000 C CNN
	1    10600 3350
	1    0    0    -1  
$EndComp
$Sheet
S 1500 1800 1250 900 
U 5A7A5454
F0 "Processor" 60
F1 "processor.sch" 60
F2 "VDD" I L 1500 1900 60 
F3 "GND" I L 1500 2050 60 
F4 "rfCE" O R 2750 1900 60 
F5 "rfCSN" O R 2750 2000 60 
F6 "rfSCK" O R 2750 2100 60 
F7 "rfMOSI" O R 2750 2200 60 
F8 "rfMISO" I R 2750 2300 60 
F9 "ctrl1" O R 2750 2500 60 
F10 "ctrl2" O R 2750 2600 60 
F11 "rfIRQ" I R 2750 2400 60 
$EndSheet
$Sheet
S 7600 5000 1050 800 
U 5A5F513F
F0 "Relays" 60
F1 "Relays.sch" 60
F2 "L" I R 8650 5100 60 
F3 "N" I R 8650 5350 60 
F4 "Earth" I R 8650 5550 60 
F5 "Ctrl1" I L 7600 5100 60 
F6 "Ctrl2" I L 7600 5200 60 
$EndSheet
Wire Wire Line
	2750 2200 3350 2200
Wire Wire Line
	2750 2300 3350 2300
Wire Wire Line
	2750 2400 3350 2400
Wire Wire Line
	2750 2100 3350 2100
Wire Wire Line
	2750 2000 3350 2000
Wire Wire Line
	2750 1900 3350 1900
Text Label 3350 1900 0    60   ~ 0
rfCE
Text Label 3350 2000 0    60   ~ 0
rfCSN
Text Label 3350 2100 0    60   ~ 0
rfCSK
Text Label 3350 2200 0    60   ~ 0
rfMOSI
Text Label 3350 2300 0    60   ~ 0
rfMISO
Text Label 3350 2400 0    60   ~ 0
rfIRQ
Text Label 3350 2500 0    60   ~ 0
Ctrl1
Text Label 3350 2600 0    60   ~ 0
Ctrl2
Wire Wire Line
	2750 2500 3350 2500
Wire Wire Line
	3350 2600 2750 2600
$Comp
L power:+5V #PWR012
U 1 1 5A7BD91D
P 1250 1850
F 0 "#PWR012" H 1250 1700 50  0001 C CNN
F 1 "+5V" H 1250 1990 50  0000 C CNN
F 2 "" H 1250 1850 50  0000 C CNN
F 3 "" H 1250 1850 50  0000 C CNN
	1    1250 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 1900 1250 1900
Wire Wire Line
	1250 1900 1250 1850
$Comp
L power:GND #PWR013
U 1 1 5A7BF3CB
P 1250 2250
F 0 "#PWR013" H 1250 2000 50  0001 C CNN
F 1 "GND" H 1250 2100 50  0000 C CNN
F 2 "" H 1250 2250 50  0000 C CNN
F 3 "" H 1250 2250 50  0000 C CNN
	1    1250 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 2050 1250 2050
Wire Wire Line
	1250 2050 1250 2250
$Comp
L Pistoke-rescue:Mounting_Hole MK101
U 1 1 5A7C387F
P 1000 7100
F 0 "MK101" H 1000 7300 50  0000 C CNN
F 1 "Mounting_Hole" H 1000 7225 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_4.3mm_M4" H 1000 7100 60  0001 C CNN
F 3 "" H 1000 7100 60  0001 C CNN
	1    1000 7100
	1    0    0    -1  
$EndComp
$Comp
L Pistoke-rescue:Mounting_Hole MK103
U 1 1 5A7C4226
P 1000 7400
F 0 "MK103" H 1000 7600 50  0000 C CNN
F 1 "Mounting_Hole" H 1000 7525 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_4.3mm_M4" H 1000 7400 60  0001 C CNN
F 3 "" H 1000 7400 60  0001 C CNN
	1    1000 7400
	1    0    0    -1  
$EndComp
$Comp
L Pistoke-rescue:Mounting_Hole MK102
U 1 1 5A7C43D6
P 1550 7100
F 0 "MK102" H 1550 7300 50  0000 C CNN
F 1 "Mounting_Hole" H 1550 7225 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_4.3mm_M4" H 1550 7100 60  0001 C CNN
F 3 "" H 1550 7100 60  0001 C CNN
	1    1550 7100
	1    0    0    -1  
$EndComp
$Comp
L Pistoke-rescue:Mounting_Hole MK104
U 1 1 5A7C43DC
P 1550 7400
F 0 "MK104" H 1550 7600 50  0000 C CNN
F 1 "Mounting_Hole" H 1550 7525 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_4.3mm_M4" H 1550 7400 60  0001 C CNN
F 3 "" H 1550 7400 60  0001 C CNN
	1    1550 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 1800 9450 2150
Connection ~ 9450 2150
Text Label 8850 2150 0    60   ~ 0
L_fused
Connection ~ 10100 2800
Connection ~ 10100 3100
Text Notes 10050 3350 1    60   ~ 0
Keep short
$Comp
L Pistoke-rescue:Mounting_Hole MK105
U 1 1 5B32B987
P 2150 7100
F 0 "MK105" H 2150 7300 50  0000 C CNN
F 1 "Mounting_Hole" H 2150 7225 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_4.3mm_M4" H 2150 7100 60  0001 C CNN
F 3 "" H 2150 7100 60  0001 C CNN
	1    2150 7100
	1    0    0    -1  
$EndComp
$Comp
L Pistoke-rescue:Mounting_Hole MK106
U 1 1 5B32B98D
P 2150 7400
F 0 "MK106" H 2150 7600 50  0000 C CNN
F 1 "Mounting_Hole" H 2150 7525 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_4.3mm_M4" H 2150 7400 60  0001 C CNN
F 3 "" H 2150 7400 60  0001 C CNN
	1    2150 7400
	1    0    0    -1  
$EndComp
$Comp
L Pistoke-rescue:Mounting_Hole MK107
U 1 1 5B33E037
P 2750 7100
F 0 "MK107" H 2750 7300 50  0000 C CNN
F 1 "Mounting_Hole" H 2750 7225 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_4.3mm_M4" H 2750 7100 60  0001 C CNN
F 3 "" H 2750 7100 60  0001 C CNN
	1    2750 7100
	1    0    0    -1  
$EndComp
$Comp
L regul:SPX2920U-3.3 U102
U 1 1 5B4A43D9
P 5500 2000
F 0 "U102" H 5500 2300 50  0000 C CNN
F 1 "R-78E3.3-0.5" H 5500 2200 50  0000 C CNN
F 2 "Pistoke:R-78" H 5500 2100 50  0000 C CIN
F 3 "" H 5500 2000 50  0000 C CNN
	1    5500 2000
	-1   0    0    -1  
$EndComp
Connection ~ 6650 1950
Wire Wire Line
	4700 1800 4700 1950
$Comp
L power:+12V #PWR014
U 1 1 5B4A48F0
P 6950 1750
F 0 "#PWR014" H 6950 1600 50  0001 C CNN
F 1 "+12V" H 6950 1890 50  0000 C CNN
F 2 "" H 6950 1750 50  0000 C CNN
F 3 "" H 6950 1750 50  0000 C CNN
	1    6950 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C106
U 1 1 5B4A97FB
P 5000 2350
F 0 "C106" H 5025 2450 50  0000 L CNN
F 1 "10u" H 5025 2250 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 5038 2200 50  0001 C CNN
F 3 "" H 5000 2350 50  0000 C CNN
	1    5000 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C105
U 1 1 5B4A98F3
P 4700 2350
F 0 "C105" H 4725 2450 50  0000 L CNN
F 1 "10u" H 4725 2250 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 4738 2200 50  0001 C CNN
F 3 "" H 4700 2350 50  0000 C CNN
	1    4700 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5B4A99DA
P 4700 2650
F 0 "#PWR015" H 4700 2400 50  0001 C CNN
F 1 "GND" H 4700 2500 50  0000 C CNN
F 2 "" H 4700 2650 50  0000 C CNN
F 3 "" H 4700 2650 50  0000 C CNN
	1    4700 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 5B4A9AB4
P 5000 2650
F 0 "#PWR016" H 5000 2400 50  0001 C CNN
F 1 "GND" H 5000 2500 50  0000 C CNN
F 2 "" H 5000 2650 50  0000 C CNN
F 3 "" H 5000 2650 50  0000 C CNN
	1    5000 2650
	1    0    0    -1  
$EndComp
Connection ~ 4700 1950
Wire Wire Line
	4700 2500 4700 2650
Wire Wire Line
	5000 2650 5000 2500
Wire Wire Line
	5000 1950 5000 2200
Connection ~ 5000 1950
$Comp
L power:GND #PWR017
U 1 1 5B4AFE7C
P 5500 2650
F 0 "#PWR017" H 5500 2400 50  0001 C CNN
F 1 "GND" H 5500 2500 50  0000 C CNN
F 2 "" H 5500 2650 50  0000 C CNN
F 3 "" H 5500 2650 50  0000 C CNN
	1    5500 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2250 5500 2650
Wire Wire Line
	4150 1950 4300 1950
$Comp
L Device:R R102
U 1 1 5B4C310F
P 6200 2250
F 0 "R102" V 6280 2250 50  0000 C CNN
F 1 "10k" V 6200 2250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6130 2250 50  0001 C CNN
F 3 "" H 6200 2250 50  0000 C CNN
	1    6200 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D102
U 1 1 5B4C3244
P 6200 2650
F 0 "D102" H 6200 2750 50  0000 C CNN
F 1 "LED" H 6200 2550 50  0000 C CNN
F 2 "LEDs:LED_PLCC-2" H 6200 2650 50  0001 C CNN
F 3 "" H 6200 2650 50  0000 C CNN
	1    6200 2650
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR018
U 1 1 5B4C3AF2
P 6200 2950
F 0 "#PWR018" H 6200 2700 50  0001 C CNN
F 1 "GND" H 6200 2800 50  0000 C CNN
F 2 "" H 6200 2950 50  0000 C CNN
F 3 "" H 6200 2950 50  0000 C CNN
	1    6200 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 1700 6200 1950
Connection ~ 6200 1950
Wire Wire Line
	6200 2400 6200 2500
Wire Wire Line
	6200 2800 6200 2950
$Comp
L Device:R R101
U 1 1 5B4C3F5F
P 4300 2200
F 0 "R101" V 4380 2200 50  0000 C CNN
F 1 "1.13k" V 4300 2200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4230 2200 50  0001 C CNN
F 3 "" H 4300 2200 50  0000 C CNN
	1    4300 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D101
U 1 1 5B4C3F65
P 4300 2600
F 0 "D101" H 4300 2700 50  0000 C CNN
F 1 "LED" H 4300 2500 50  0000 C CNN
F 2 "LEDs:LED_PLCC-2" H 4300 2600 50  0001 C CNN
F 3 "" H 4300 2600 50  0000 C CNN
	1    4300 2600
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR019
U 1 1 5B4C3F6B
P 4300 2900
F 0 "#PWR019" H 4300 2650 50  0001 C CNN
F 1 "GND" H 4300 2750 50  0000 C CNN
F 2 "" H 4300 2900 50  0000 C CNN
F 3 "" H 4300 2900 50  0000 C CNN
	1    4300 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 2350 4300 2450
Wire Wire Line
	4300 2750 4300 2900
Wire Wire Line
	4300 1700 4300 1950
$Comp
L Pistoke-rescue:TEST TP104
U 1 1 5B4EF952
P 6200 1700
F 0 "TP104" H 6200 2000 50  0000 C BNN
F 1 "TEST" H 6200 1950 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 6200 1700 50  0001 C CNN
F 3 "" H 6200 1700 50  0000 C CNN
	1    6200 1700
	1    0    0    -1  
$EndComp
$Comp
L Pistoke-rescue:TEST TP105
U 1 1 5B4EFAB5
P 6350 1700
F 0 "TP105" H 6350 2000 50  0000 C BNN
F 1 "TEST" H 6350 1950 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 6350 1700 50  0001 C CNN
F 3 "" H 6350 1700 50  0000 C CNN
	1    6350 1700
	1    0    0    -1  
$EndComp
$Comp
L Pistoke-rescue:TEST TP106
U 1 1 5B4EFBAC
P 6500 1700
F 0 "TP106" H 6500 2000 50  0000 C BNN
F 1 "TEST" H 6500 1950 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 6500 1700 50  0001 C CNN
F 3 "" H 6500 1700 50  0000 C CNN
	1    6500 1700
	1    0    0    -1  
$EndComp
$Comp
L Pistoke-rescue:TEST TP101
U 1 1 5B4EFEBA
P 4150 1700
F 0 "TP101" H 4150 2000 50  0000 C BNN
F 1 "TEST" H 4150 1950 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 4150 1700 50  0001 C CNN
F 3 "" H 4150 1700 50  0000 C CNN
	1    4150 1700
	1    0    0    -1  
$EndComp
$Comp
L Pistoke-rescue:TEST TP102
U 1 1 5B4EFEC0
P 4300 1700
F 0 "TP102" H 4300 2000 50  0000 C BNN
F 1 "TEST" H 4300 1950 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 4300 1700 50  0001 C CNN
F 3 "" H 4300 1700 50  0000 C CNN
	1    4300 1700
	1    0    0    -1  
$EndComp
$Comp
L Pistoke-rescue:TEST TP103
U 1 1 5B4EFEC6
P 4450 1700
F 0 "TP103" H 4450 2000 50  0000 C BNN
F 1 "TEST" H 4450 1950 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 4450 1700 50  0001 C CNN
F 3 "" H 4450 1700 50  0000 C CNN
	1    4450 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 1700 4150 1950
Connection ~ 4300 1950
Wire Wire Line
	4450 1700 4450 1950
Connection ~ 4450 1950
Wire Wire Line
	6350 1700 6350 1950
Connection ~ 6350 1950
Wire Wire Line
	6500 1700 6500 1950
Connection ~ 6500 1950
$Comp
L power:GND #PWR020
U 1 1 5B4F3B36
P 4450 3800
F 0 "#PWR020" H 4450 3550 50  0001 C CNN
F 1 "GND" H 4450 3650 50  0000 C CNN
F 2 "" H 4450 3800 50  0000 C CNN
F 3 "" H 4450 3800 50  0000 C CNN
	1    4450 3800
	1    0    0    -1  
$EndComp
$Comp
L Pistoke-rescue:TEST TP107
U 1 1 5B4F3E82
P 4300 3650
F 0 "TP107" H 4300 3950 50  0000 C BNN
F 1 "TEST" H 4300 3900 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 4300 3650 50  0001 C CNN
F 3 "" H 4300 3650 50  0000 C CNN
	1    4300 3650
	1    0    0    -1  
$EndComp
$Comp
L Pistoke-rescue:TEST TP108
U 1 1 5B4F3E88
P 4450 3650
F 0 "TP108" H 4450 3950 50  0000 C BNN
F 1 "TEST" H 4450 3900 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 4450 3650 50  0001 C CNN
F 3 "" H 4450 3650 50  0000 C CNN
	1    4450 3650
	1    0    0    -1  
$EndComp
$Comp
L Pistoke-rescue:TEST TP109
U 1 1 5B4F3E8E
P 4600 3650
F 0 "TP109" H 4600 3950 50  0000 C BNN
F 1 "TEST" H 4600 3900 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 4600 3650 50  0001 C CNN
F 3 "" H 4600 3650 50  0000 C CNN
	1    4600 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR021
U 1 1 5B4F3F90
P 4600 3800
F 0 "#PWR021" H 4600 3550 50  0001 C CNN
F 1 "GND" H 4600 3650 50  0000 C CNN
F 2 "" H 4600 3800 50  0000 C CNN
F 3 "" H 4600 3800 50  0000 C CNN
	1    4600 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR022
U 1 1 5B4F4091
P 4300 3800
F 0 "#PWR022" H 4300 3550 50  0001 C CNN
F 1 "GND" H 4300 3650 50  0000 C CNN
F 2 "" H 4300 3800 50  0000 C CNN
F 3 "" H 4300 3800 50  0000 C CNN
	1    4300 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 3650 4300 3800
Wire Wire Line
	4450 3650 4450 3800
Wire Wire Line
	4600 3650 4600 3800
Wire Wire Line
	7200 1950 7200 2150
$Comp
L Pistoke-rescue:Mounting_Hole MK108
U 1 1 5B5A1C22
P 2750 7400
F 0 "MK108" H 2750 7600 50  0000 C CNN
F 1 "Mounting_Hole" H 2750 7525 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_4.3mm_M4" H 2750 7400 60  0001 C CNN
F 3 "" H 2750 7400 60  0001 C CNN
	1    2750 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 1800 10400 1800
Wire Wire Line
	6950 2600 7200 2600
Wire Wire Line
	6950 2600 6950 2800
Wire Wire Line
	7200 2600 7200 2800
Wire Wire Line
	6950 1950 7200 1950
Wire Wire Line
	6950 1950 6950 2150
Wire Wire Line
	9000 2800 9450 2800
Wire Wire Line
	9450 2800 9450 3050
Wire Wire Line
	9450 2800 10100 2800
Wire Wire Line
	9450 2150 9450 2350
Wire Wire Line
	10100 2800 10400 2800
Wire Wire Line
	10100 3100 10100 3350
Wire Wire Line
	6650 1950 6950 1950
Wire Wire Line
	4700 1950 4700 2200
Wire Wire Line
	4700 1950 5000 1950
Wire Wire Line
	5000 1950 5100 1950
Wire Wire Line
	6200 1950 6350 1950
Wire Wire Line
	6200 1950 6200 2100
Wire Wire Line
	4300 1950 4450 1950
Wire Wire Line
	4300 1950 4300 2050
Wire Wire Line
	4450 1950 4700 1950
Wire Wire Line
	6350 1950 6500 1950
Wire Wire Line
	6500 1950 6650 1950
Wire Wire Line
	7200 2450 7650 2450
$EndSCHEMATC
