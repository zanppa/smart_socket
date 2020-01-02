EESchema Schematic File Version 4
LIBS:Pistoke-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
Title "Smart socket"
Date "14.01.2018"
Rev "0.2"
Comp "Lauri Peltonen"
Comment1 "nRF24L01 version"
Comment2 "Communications"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Pistoke-rescue:nRF24L01_module U201
U 1 1 5A5E5DAD
P 5450 4050
AR Path="/5A5E5DAD" Ref="U201"  Part="1" 
AR Path="/5A5E58C6/5A5E5DAD" Ref="U201"  Part="1" 
F 0 "U201" H 5450 4500 60  0000 C CNN
F 1 "nRF24L01_module" H 5450 3700 60  0000 C CNN
F 2 "Pistoke:nRF24L01_module" H 5450 4050 60  0001 C CNN
F 3 "" H 5450 4050 60  0001 C CNN
	1    5450 4050
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C203
U 1 1 5A5E5DB4
P 4100 4000
F 0 "C203" V 4050 4050 50  0000 L CNN
F 1 "10u X7R" V 4050 3600 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 4138 3850 50  0001 C CNN
F 3 "" H 4100 4000 50  0000 C CNN
	1    4100 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C202
U 1 1 5A5E5DBB
P 3600 4000
F 0 "C202" V 3550 4050 50  0000 L CNN
F 1 "10u X7R" V 3550 3600 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 3638 3850 50  0001 C CNN
F 3 "" H 3600 4000 50  0000 C CNN
	1    3600 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C201
U 1 1 5A5E5DC2
P 3100 4000
F 0 "C201" V 3050 4050 50  0000 L CNN
F 1 "10u X7R" V 3050 3600 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 3138 3850 50  0001 C CNN
F 3 "" H 3100 4000 50  0000 C CNN
	1    3100 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3750 3600 3750
Wire Wire Line
	4100 3850 4100 3750
Connection ~ 4100 3750
Wire Wire Line
	3600 3850 3600 3750
Connection ~ 3600 3750
Wire Wire Line
	3100 3300 3100 3750
Connection ~ 3100 3750
Wire Wire Line
	3100 4150 3100 4250
Wire Wire Line
	3100 4250 3600 4250
Connection ~ 3100 4250
Wire Wire Line
	3600 4150 3600 4250
Connection ~ 3600 4250
Wire Wire Line
	4100 4150 4100 4250
Connection ~ 4100 4250
Text HLabel 6650 3750 2    60   Input ~ 0
rfCE
Text HLabel 6650 3850 2    60   Input ~ 0
rfCSN
Text HLabel 6650 3950 2    60   Input ~ 0
rfCSK
Text HLabel 6650 4050 2    60   Input ~ 0
rfMOSI
Text HLabel 6650 4150 2    60   Input ~ 0
rfMISO
Text HLabel 6650 4250 2    60   Input ~ 0
rfIRQ
Text HLabel 3100 2750 1    60   Input ~ 0
rfPWR
Text HLabel 3100 4750 3    60   Input ~ 0
rfGND
$Comp
L Device:Ferrite_Bead_Small L201
U 1 1 5AB2A30D
P 3100 3200
F 0 "L201" H 3175 3250 50  0000 L CNN
F 1 "Ferrite_Bead_Small" H 3175 3150 50  0000 L CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 3030 3200 50  0001 C CNN
F 3 "" H 3100 3200 50  0000 C CNN
	1    3100 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 2750 3100 3100
$Comp
L Device:C C204
U 1 1 5AB2A5A8
P 4600 4000
F 0 "C204" V 4550 4050 50  0000 L CNN
F 1 "10u X7R" V 4550 3600 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 4638 3850 50  0001 C CNN
F 3 "" H 4600 4000 50  0000 C CNN
	1    4600 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 3850 4600 3750
Wire Wire Line
	4600 4150 4600 4250
Connection ~ 4600 4250
Connection ~ 4600 3750
Wire Wire Line
	6000 3750 6650 3750
Wire Wire Line
	6000 3850 6650 3850
Wire Wire Line
	6000 3950 6650 3950
Wire Wire Line
	6000 4050 6650 4050
Wire Wire Line
	6000 4150 6650 4150
Wire Wire Line
	6000 4250 6650 4250
Text Label 3300 3750 0    60   ~ 0
rfPWR_filt
Wire Wire Line
	4100 3750 4600 3750
Wire Wire Line
	3600 3750 4100 3750
Wire Wire Line
	3100 3750 3100 3850
Wire Wire Line
	3100 4250 3100 4750
Wire Wire Line
	3600 4250 4100 4250
Wire Wire Line
	4100 4250 4600 4250
Wire Wire Line
	4600 4250 4950 4250
Wire Wire Line
	4600 3750 4950 3750
$EndSCHEMATC
