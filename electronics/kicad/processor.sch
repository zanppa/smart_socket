EESchema Schematic File Version 4
LIBS:Pistoke-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
Title "Smart socket"
Date "14.01.2018"
Rev "0.2"
Comp "Lauri Peltonen"
Comment1 "Processor and I/O"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L stm32:STM32F103R4Tx U301
U 1 1 5A7A549B
P 6000 3950
F 0 "U301" H 4000 5875 50  0000 L BNN
F 1 "STM32F103R4Tx" H 8000 5875 50  0000 R BNN
F 2 "Housings_QFP:LQFP-64_10x10mm_Pitch0.5mm" H 8000 5825 50  0000 R TNN
F 3 "" H 6000 3950 50  0000 C CNN
	1    6000 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C301
U 1 1 5A7A552A
P 4500 1400
F 0 "C301" H 4525 1500 50  0000 L CNN
F 1 "100n" H 4525 1300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4538 1250 50  0001 C CNN
F 3 "" H 4500 1400 50  0000 C CNN
	1    4500 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C302
U 1 1 5A7A5585
P 4750 1400
F 0 "C302" H 4775 1500 50  0000 L CNN
F 1 "100n" H 4775 1300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4788 1250 50  0001 C CNN
F 3 "" H 4750 1400 50  0000 C CNN
	1    4750 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C303
U 1 1 5A7A55AC
P 5000 1400
F 0 "C303" H 5025 1500 50  0000 L CNN
F 1 "100n" H 5025 1300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5038 1250 50  0001 C CNN
F 3 "" H 5000 1400 50  0000 C CNN
	1    5000 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C304
U 1 1 5A7A55D2
P 5250 1400
F 0 "C304" H 5275 1500 50  0000 L CNN
F 1 "100n" H 5275 1300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5288 1250 50  0001 C CNN
F 3 "" H 5250 1400 50  0000 C CNN
	1    5250 1400
	1    0    0    -1  
$EndComp
Text Label 4000 1750 0    60   ~ 0
gnd
Text Label 1650 1550 0    60   ~ 0
gnd
Text Label 3800 1000 0    60   ~ 0
vdd
Text Label 1650 1200 0    60   ~ 0
vdd
Text HLabel 1350 1200 0    60   Input ~ 0
VDD
Text HLabel 1350 1550 0    60   Input ~ 0
GND
Text Label 6400 6300 0    60   ~ 0
gnd
$Comp
L Device:Crystal Y301
U 1 1 5A7A6250
P 2250 2800
F 0 "Y301" H 2250 2950 50  0000 C CNN
F 1 "8.000MHz" H 2250 2650 50  0000 C CNN
F 2 "Crystals:Crystal_HC18-U_Vertical" H 2250 2800 50  0001 C CNN
F 3 "" H 2250 2800 50  0000 C CNN
	1    2250 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R313
U 1 1 5A7A62BD
P 2900 2800
F 0 "R313" V 2980 2800 50  0000 C CNN
F 1 "0" V 2900 2800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2830 2800 50  0001 C CNN
F 3 "" H 2900 2800 50  0000 C CNN
	1    2900 2800
	0    1    1    0   
$EndComp
$Comp
L Device:R R312
U 1 1 5A7A6305
P 2250 2450
F 0 "R312" V 2330 2450 50  0000 C CNN
F 1 "1M*" V 2250 2450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2180 2450 50  0001 C CNN
F 3 "" H 2250 2450 50  0000 C CNN
	1    2250 2450
	0    1    1    0   
$EndComp
$Comp
L Device:C C305
U 1 1 5A7A639F
P 1900 3150
F 0 "C305" H 1925 3250 50  0000 L CNN
F 1 "40p" H 1925 3050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1938 3000 50  0001 C CNN
F 3 "" H 1900 3150 50  0000 C CNN
	1    1900 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C306
U 1 1 5A7A641B
P 2550 3150
F 0 "C306" H 2575 3250 50  0000 L CNN
F 1 "40p" H 2575 3050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2588 3000 50  0001 C CNN
F 3 "" H 2550 3150 50  0000 C CNN
	1    2550 3150
	1    0    0    -1  
$EndComp
Text Label 1900 3550 0    60   ~ 0
gnd
Text Label 2550 3550 0    60   ~ 0
gnd
$Comp
L Device:Crystal Y302
U 1 1 5A7A71B9
P 2250 5450
F 0 "Y302" H 2250 5600 50  0000 C CNN
F 1 "32.768k" H 2250 5300 50  0000 C CNN
F 2 "Crystals:Crystal_C26-LF_d2.1mm_l6.5mm_Horizontal" H 2250 5450 50  0001 C CNN
F 3 "" H 2250 5450 50  0000 C CNN
	1    2250 5450
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R315
U 1 1 5A7A71BF
P 2900 5450
F 0 "R315" V 2980 5450 50  0000 C CNN
F 1 "0" V 2900 5450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2830 5450 50  0001 C CNN
F 3 "" H 2900 5450 50  0000 C CNN
	1    2900 5450
	0    1    1    0   
$EndComp
$Comp
L Device:R R314
U 1 1 5A7A71C5
P 2250 5100
F 0 "R314" V 2330 5100 50  0000 C CNN
F 1 "1M*" V 2250 5100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2180 5100 50  0001 C CNN
F 3 "" H 2250 5100 50  0000 C CNN
	1    2250 5100
	0    1    1    0   
$EndComp
$Comp
L Device:C C307
U 1 1 5A7A71CB
P 1900 5800
F 0 "C307" H 1925 5900 50  0000 L CNN
F 1 "6p" H 1925 5700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1938 5650 50  0001 C CNN
F 3 "" H 1900 5800 50  0000 C CNN
	1    1900 5800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C308
U 1 1 5A7A71D1
P 2550 5800
F 0 "C308" H 2575 5900 50  0000 L CNN
F 1 "6p" H 2575 5700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2588 5650 50  0001 C CNN
F 3 "" H 2550 5800 50  0000 C CNN
	1    2550 5800
	1    0    0    -1  
$EndComp
Text Label 1900 6200 0    60   ~ 0
gnd
Text Label 2550 6200 0    60   ~ 0
gnd
Text HLabel 8500 2650 2    60   Output ~ 0
rfCE
Text HLabel 8500 2750 2    60   Output ~ 0
rfCSN
Text HLabel 8500 2850 2    60   Output ~ 0
rfSCK
Text HLabel 8500 3050 2    60   Output ~ 0
rfMOSI
Text HLabel 8500 2950 2    60   Input ~ 0
rfMISO
Text Label 7950 1400 0    60   ~ 0
gnd
$Comp
L conn:CONN_02X03 P303
U 1 1 5A7AAC6C
P 7600 1100
F 0 "P303" H 7600 1300 50  0000 C CNN
F 1 "CONN_02X03" H 7600 900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03_Pitch2.54mm" H 7600 -100 50  0001 C CNN
F 3 "" H 7600 -100 50  0000 C CNN
	1    7600 1100
	1    0    0    -1  
$EndComp
Text Label 7200 1400 0    60   ~ 0
gnd
$Comp
L Device:R R306
U 1 1 5A7AAF7D
P 8450 1100
F 0 "R306" V 8530 1100 50  0000 C CNN
F 1 "100k" V 8450 1100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 8380 1100 50  0001 C CNN
F 3 "" H 8450 1100 50  0000 C CNN
	1    8450 1100
	0    1    1    0   
$EndComp
$Comp
L Device:R R305
U 1 1 5A7AAFE3
P 6850 1100
F 0 "R305" V 6930 1100 50  0000 C CNN
F 1 "100k" V 6850 1100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6780 1100 50  0001 C CNN
F 3 "" H 6850 1100 50  0000 C CNN
	1    6850 1100
	0    1    1    0   
$EndComp
Text Label 6600 1100 2    60   ~ 0
boot0
Text Label 8750 1100 0    60   ~ 0
boot1
Text Label 3500 2550 2    60   ~ 0
boot0
Text Label 8400 4250 0    60   ~ 0
boot1
Text Notes 7150 750  0    60   ~ 0
Boot mode selection
Text Notes 9450 1200 0    60   ~ 0
In-circuit serial programming
Text Label 10400 1350 0    60   ~ 0
vdd
Text Label 10400 2100 0    60   ~ 0
gnd
$Comp
L Device:R R307
U 1 1 5A7AC899
P 10000 1600
F 0 "R307" V 10080 1600 50  0000 C CNN
F 1 "100" V 10000 1600 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 9930 1600 50  0001 C CNN
F 3 "" H 10000 1600 50  0000 C CNN
	1    10000 1600
	0    1    1    0   
$EndComp
$Comp
L Device:R R308
U 1 1 5A7AC92B
P 9700 1700
F 0 "R308" V 9780 1700 50  0000 C CNN
F 1 "100" V 9700 1700 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 9630 1700 50  0001 C CNN
F 3 "" H 9700 1700 50  0000 C CNN
	1    9700 1700
	0    1    1    0   
$EndComp
Text Label 9250 1600 2    60   ~ 0
swdio
Text Label 9250 1700 2    60   ~ 0
swdclk
Text Label 8400 3650 0    60   ~ 0
swdio
Text Label 8400 3750 0    60   ~ 0
swdclk
$Comp
L conn:CONN_01X05 P304
U 1 1 5A7AE408
P 10850 1700
F 0 "P304" H 10850 2000 50  0000 C CNN
F 1 "CONN_01X05" V 10950 1700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 10850 1700 50  0001 C CNN
F 3 "" H 10850 1700 50  0000 C CNN
	1    10850 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R311
U 1 1 5A7AE4C2
P 10000 1800
F 0 "R311" V 10080 1800 50  0000 C CNN
F 1 "100" V 10000 1800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 9930 1800 50  0001 C CNN
F 3 "" H 10000 1800 50  0000 C CNN
	1    10000 1800
	0    1    1    0   
$EndComp
Text Label 9250 1800 2    60   ~ 0
nrst
Text Label 3500 2350 2    60   ~ 0
nrst
Text HLabel 8700 4050 2    60   Output ~ 0
ctrl1
Text HLabel 8700 4150 2    60   Output ~ 0
ctrl2
Text HLabel 8500 3150 2    60   Input ~ 0
rfIRQ
$Comp
L conn:CONN_01X02 P305
U 1 1 5A7EA6DD
P 9650 3300
F 0 "P305" H 9650 3450 50  0000 C CNN
F 1 "CONN_01X02" V 9750 3300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 9650 3300 50  0001 C CNN
F 3 "" H 9650 3300 50  0000 C CNN
	1    9650 3300
	1    0    0    -1  
$EndComp
Text Label 8950 3250 0    60   ~ 0
UART1_TX
Text Label 8950 3350 0    60   ~ 0
UART1_RX
Text Label 3250 2800 0    60   ~ 0
OSCIN
Text Label 3050 2950 0    60   ~ 0
OSCOUT
Text Label 2500 2450 0    60   ~ 0
XTAL11
Text Label 1900 2800 2    60   ~ 0
XTAL12
Text Label 3650 5450 2    60   ~ 0
OSC32IN
Text Label 3650 5550 2    60   ~ 0
OSC32OUT
Text Label 2550 5300 0    60   ~ 0
XTAL21
Text Label 1900 5450 2    60   ~ 0
XTAL22
Text Label 10600 1600 2    60   ~ 0
swdiocon
Text Label 10600 1700 2    60   ~ 0
swdclkcon
Text Label 10600 1800 2    60   ~ 0
nrstcon
Text Label 7900 1100 0    60   ~ 0
boot1con
Text Label 7300 1100 2    60   ~ 0
boot0con
$Comp
L conn:CONN_01X10 P307
U 1 1 5A7F0BD8
P 10800 5850
F 0 "P307" H 10800 6400 50  0000 C CNN
F 1 "CONN_01X10" V 10900 5850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x05_Pitch2.54mm" H 10800 5850 50  0001 C CNN
F 3 "" H 10800 5850 50  0000 C CNN
	1    10800 5850
	1    0    0    -1  
$EndComp
Text Label 10500 5700 2    60   ~ 0
gnd
Text Label 10100 4850 2    60   ~ 0
vdd
Text Label 8500 2350 0    60   ~ 0
PA0
Text Label 8500 2450 0    60   ~ 0
PA1
Text Label 8500 2550 0    60   ~ 0
PA2
Text Label 8400 4350 0    60   ~ 0
PB3
Text Label 8400 4450 0    60   ~ 0
PB4
Text Label 8400 4550 0    60   ~ 0
PB5
Text Label 8400 4650 0    60   ~ 0
PB6
Text Label 8400 4750 0    60   ~ 0
PB7
Text Label 8400 4850 0    60   ~ 0
PB8
Text Label 8400 4950 0    60   ~ 0
PB9
Text Label 8400 5050 0    60   ~ 0
PB10
Text Label 3550 4050 0    60   ~ 0
PC0
Text Label 3550 4150 0    60   ~ 0
PC1
Text Label 3550 4250 0    60   ~ 0
PC2
Text Label 3550 4350 0    60   ~ 0
PC3
Text Label 3550 4450 0    60   ~ 0
PC4
Text Label 3550 4550 0    60   ~ 0
PC5
Text Label 3550 4650 0    60   ~ 0
PC6
Text Label 3550 4750 0    60   ~ 0
PC7
NoConn ~ 3450 4050
NoConn ~ 3450 4150
NoConn ~ 3450 4350
NoConn ~ 3450 4650
NoConn ~ 8500 2450
NoConn ~ 3900 5050
NoConn ~ 3900 5150
NoConn ~ 3900 5250
NoConn ~ 3900 5350
NoConn ~ 3900 3850
Text Label 10100 6300 0    60   ~ 0
PA0
Text Label 10350 5900 0    60   ~ 0
PB6
Text Label 10350 6100 0    60   ~ 0
PB7
Text Label 10350 5400 0    60   ~ 0
PB3
Text Label 10350 5600 0    60   ~ 0
PB4
Text Label 10350 5800 0    60   ~ 0
PB5
Text Label 10350 6000 0    60   ~ 0
PB8
Text Label 10350 6200 0    60   ~ 0
PB9
$Comp
L Device:Q_NPN_BEC Q303
U 1 1 5A9EFDF8
P 3350 7200
F 0 "Q303" H 3550 7275 50  0000 L CNN
F 1 "BC817" H 3550 7200 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 3550 7125 50  0001 L CIN
F 3 "" H 3350 7200 50  0000 L CNN
	1    3350 7200
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NPN_BEC Q304
U 1 1 5A9F0512
P 4850 7200
F 0 "Q304" H 5050 7275 50  0000 L CNN
F 1 "BC817" H 5050 7200 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 5050 7125 50  0001 L CIN
F 3 "" H 4850 7200 50  0000 L CNN
	1    4850 7200
	1    0    0    -1  
$EndComp
Text Label 4950 7600 0    60   ~ 0
gnd
Text Label 3450 7600 0    60   ~ 0
gnd
$Comp
L Device:R R318
U 1 1 5A9F0A57
P 3450 6750
F 0 "R318" V 3530 6750 50  0000 C CNN
F 1 "100" V 3450 6750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3380 6750 50  0001 C CNN
F 3 "" H 3450 6750 50  0000 C CNN
	1    3450 6750
	-1   0    0    1   
$EndComp
$Comp
L Device:R R319
U 1 1 5A9F158D
P 4950 6750
F 0 "R319" V 5030 6750 50  0000 C CNN
F 1 "100" V 4950 6750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4880 6750 50  0001 C CNN
F 3 "" H 4950 6750 50  0000 C CNN
	1    4950 6750
	-1   0    0    1   
$EndComp
$Comp
L Device:R R320
U 1 1 5A9F1B27
P 2850 7200
F 0 "R320" V 2930 7200 50  0000 C CNN
F 1 "10k" V 2850 7200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2780 7200 50  0001 C CNN
F 3 "" H 2850 7200 50  0000 C CNN
	1    2850 7200
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R321
U 1 1 5A9F1BAA
P 4400 7200
F 0 "R321" V 4480 7200 50  0000 C CNN
F 1 "10k" V 4400 7200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4330 7200 50  0001 C CNN
F 3 "" H 4400 7200 50  0000 C CNN
	1    4400 7200
	0    -1   -1   0   
$EndComp
$Comp
L conn:CONN_01X08 P306
U 1 1 5A9F2660
P 1000 6600
F 0 "P306" H 1000 7150 50  0000 C CNN
F 1 "CONN_01X10" V 1100 6600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x04_Pitch2.54mm" H 1000 6600 50  0001 C CNN
F 3 "" H 1000 6600 50  0000 C CNN
	1    1000 6600
	-1   0    0    -1  
$EndComp
Text Label 1250 6250 0    60   ~ 0
vdd
Text Label 1250 6350 0    60   ~ 0
vdd
Wire Wire Line
	5250 1750 5250 1550
Wire Wire Line
	4000 1750 4500 1750
Wire Wire Line
	5000 1550 5000 1750
Connection ~ 5000 1750
Wire Wire Line
	4750 1550 4750 1750
Connection ~ 4750 1750
Wire Wire Line
	4500 1550 4500 1750
Connection ~ 4500 1750
Wire Wire Line
	6100 1000 6100 1950
Wire Wire Line
	4300 1000 4500 1000
Wire Wire Line
	4500 1000 4500 1250
Wire Wire Line
	4750 1250 4750 1000
Connection ~ 4750 1000
Wire Wire Line
	5000 1250 5000 1000
Connection ~ 5000 1000
Wire Wire Line
	5250 1250 5250 1000
Connection ~ 5250 1000
Wire Wire Line
	1650 1200 1350 1200
Wire Wire Line
	1650 1550 1350 1550
Wire Wire Line
	5800 5950 5800 6300
Wire Wire Line
	5800 6300 5900 6300
Wire Wire Line
	5900 5950 5900 6300
Connection ~ 5900 6300
Wire Wire Line
	6000 5950 6000 6300
Connection ~ 6000 6300
Wire Wire Line
	6100 5950 6100 6300
Connection ~ 6100 6300
Wire Wire Line
	6200 5950 6200 6300
Connection ~ 6200 6300
Wire Wire Line
	5800 1950 5800 1000
Connection ~ 5800 1000
Wire Wire Line
	5900 1950 5900 1000
Connection ~ 5900 1000
Wire Wire Line
	6000 1950 6000 1000
Connection ~ 6000 1000
Wire Wire Line
	6200 1000 6200 1950
Connection ~ 6100 1000
Wire Wire Line
	2100 2800 1900 2800
Wire Wire Line
	1900 2450 1900 2800
Wire Wire Line
	1900 3550 1900 3300
Wire Wire Line
	2550 3550 2550 3300
Wire Wire Line
	2400 2800 2550 2800
Wire Wire Line
	2550 2450 2550 2800
Connection ~ 2550 2800
Wire Wire Line
	2550 2450 2400 2450
Wire Wire Line
	2100 2450 1900 2450
Connection ~ 1900 2800
Wire Wire Line
	3500 2800 3500 3650
Wire Wire Line
	3500 3650 3900 3650
Connection ~ 1900 2950
Wire Wire Line
	2100 5450 1900 5450
Wire Wire Line
	1900 5100 1900 5450
Wire Wire Line
	1900 6200 1900 5950
Wire Wire Line
	2550 6200 2550 5950
Wire Wire Line
	2400 5450 2550 5450
Wire Wire Line
	2550 5100 2550 5450
Connection ~ 2550 5450
Wire Wire Line
	2550 5100 2400 5100
Wire Wire Line
	2100 5100 1900 5100
Connection ~ 1900 5450
Wire Wire Line
	3050 5450 3900 5450
Wire Wire Line
	3900 5550 3100 5550
Wire Wire Line
	3100 5550 3100 5600
Wire Wire Line
	3100 5600 1900 5600
Connection ~ 1900 5600
Wire Wire Line
	7950 900  7950 1000
Wire Wire Line
	7950 1000 7850 1000
Wire Wire Line
	7350 1000 7200 1000
Wire Wire Line
	7200 1000 7200 900 
Wire Wire Line
	7200 1400 7200 1200
Wire Wire Line
	7200 1200 7350 1200
Wire Wire Line
	7950 1400 7950 1200
Wire Wire Line
	7950 1200 7850 1200
Wire Wire Line
	7350 1100 7000 1100
Wire Wire Line
	6700 1100 6600 1100
Wire Wire Line
	7850 1100 8300 1100
Wire Wire Line
	8600 1100 8750 1100
Wire Wire Line
	3900 2550 3500 2550
Wire Wire Line
	8400 4250 8100 4250
Wire Wire Line
	10400 1350 10400 1500
Wire Wire Line
	10400 1500 10650 1500
Wire Wire Line
	10400 2100 10400 1900
Wire Wire Line
	10400 1900 10650 1900
Wire Wire Line
	9250 1600 9850 1600
Wire Wire Line
	9550 1700 9250 1700
Wire Wire Line
	10150 1600 10650 1600
Wire Wire Line
	10650 1700 9850 1700
Wire Wire Line
	8100 3650 8400 3650
Wire Wire Line
	8100 3750 8400 3750
Wire Wire Line
	10650 1800 10150 1800
Wire Wire Line
	9850 1800 9250 1800
Wire Wire Line
	3500 2350 3900 2350
Wire Wire Line
	8100 2850 8500 2850
Wire Wire Line
	8500 3050 8100 3050
Wire Wire Line
	8500 2950 8100 2950
Wire Wire Line
	8500 2750 8100 2750
Wire Wire Line
	8500 2650 8100 2650
Wire Wire Line
	8100 4050 8700 4050
Wire Wire Line
	8700 4150 8100 4150
Wire Wire Line
	8500 3150 8100 3150
Wire Wire Line
	9450 3250 8100 3250
Wire Wire Line
	8100 3350 9450 3350
Wire Wire Line
	3450 4050 3900 4050
Wire Wire Line
	3900 4150 3450 4150
Wire Wire Line
	3900 4350 3450 4350
Wire Wire Line
	3450 4650 3900 4650
Wire Wire Line
	3050 2800 3500 2800
Wire Wire Line
	3900 3750 3400 3750
Wire Wire Line
	3400 3750 3400 2950
Wire Wire Line
	3400 2950 1900 2950
Wire Wire Line
	9800 5500 10100 5500
Wire Wire Line
	10600 5700 10500 5700
Wire Wire Line
	8100 4350 8400 4350
Wire Wire Line
	8400 4450 8100 4450
Wire Wire Line
	8100 4550 8400 4550
Wire Wire Line
	8400 4650 8100 4650
Wire Wire Line
	8100 4750 8400 4750
Wire Wire Line
	8400 4850 8100 4850
Wire Wire Line
	8100 4950 8400 4950
Wire Wire Line
	8100 5550 8400 5550
Wire Wire Line
	8100 2350 8500 2350
Wire Wire Line
	8100 2450 8500 2450
Wire Wire Line
	8100 2550 9200 2550
Wire Wire Line
	8400 5050 8100 5050
Wire Wire Line
	10600 6300 10100 6300
Wire Wire Line
	10350 5400 10600 5400
Wire Wire Line
	10350 5600 10600 5600
Wire Wire Line
	10600 5800 10350 5800
Wire Wire Line
	10350 5900 10600 5900
Wire Wire Line
	10600 6000 10350 6000
Wire Wire Line
	10350 6100 10600 6100
Wire Wire Line
	10600 6200 10350 6200
Wire Wire Line
	3450 7400 3450 7600
Wire Wire Line
	4950 7400 4950 7600
Wire Wire Line
	3000 7200 3150 7200
Wire Wire Line
	2700 7200 2300 7200
Wire Wire Line
	3450 6900 3450 7000
Wire Wire Line
	4650 7200 4550 7200
Wire Wire Line
	4250 7200 3900 7200
Wire Wire Line
	4950 6900 4950 7000
Wire Wire Line
	1250 6250 1200 6250
Wire Wire Line
	1200 6350 1250 6350
Wire Wire Line
	4950 6450 4950 6600
Wire Wire Line
	1200 6450 4950 6450
Wire Wire Line
	3450 6600 3450 6550
Wire Wire Line
	3450 6550 1200 6550
Text Label 1350 6450 0    60   ~ 0
led1
Text Label 1350 6550 0    60   ~ 0
led2
Text Label 1300 6650 0    60   ~ 0
gnd
Text Label 1300 6750 0    60   ~ 0
gnd
Wire Wire Line
	1300 6650 1200 6650
Wire Wire Line
	1200 6750 1300 6750
Wire Wire Line
	1200 6850 1550 6850
Wire Wire Line
	1200 6950 2400 6950
$Comp
L Device:R R316
U 1 1 5A9F750D
P 1900 6700
F 0 "R316" V 1980 6700 50  0000 C CNN
F 1 "4.7k" V 1900 6700 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1830 6700 50  0001 C CNN
F 3 "" H 1900 6700 50  0000 C CNN
	1    1900 6700
	0    1    1    0   
$EndComp
$Comp
L Device:R R317
U 1 1 5A9F7B29
P 2700 6700
F 0 "R317" V 2780 6700 50  0000 C CNN
F 1 "4.7k" V 2700 6700 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2630 6700 50  0001 C CNN
F 3 "" H 2700 6700 50  0000 C CNN
	1    2700 6700
	0    1    1    0   
$EndComp
Text Label 2150 6700 0    60   ~ 0
vdd
Text Label 3000 6700 0    60   ~ 0
vdd
Wire Wire Line
	3000 6700 2850 6700
Wire Wire Line
	2550 6700 2400 6700
Wire Wire Line
	2400 6700 2400 6950
Wire Wire Line
	2150 6700 2050 6700
Wire Wire Line
	1750 6700 1550 6700
Wire Wire Line
	1550 6700 1550 6850
Connection ~ 1550 6850
Connection ~ 2400 6950
Text Label 8400 5150 0    60   ~ 0
PB11
Text Label 8400 5250 0    60   ~ 0
PB12
Text Label 8400 5350 0    60   ~ 0
PB13
Text Label 8400 5450 0    60   ~ 0
PB14
Text Label 8400 5550 0    60   ~ 0
PB15
Wire Wire Line
	8100 5150 8400 5150
Wire Wire Line
	8400 5250 8100 5250
Wire Wire Line
	8100 5350 8400 5350
Wire Wire Line
	8400 5450 8100 5450
Text Label 3900 7200 0    60   ~ 0
PB11
Text Label 2300 7200 0    60   ~ 0
PB12
Text Label 2050 6850 0    60   ~ 0
PB13
Text Label 2700 6950 0    60   ~ 0
PB14
NoConn ~ 8400 5550
NoConn ~ 8400 5050
NoConn ~ 8100 3850
NoConn ~ 8100 3550
NoConn ~ 8100 3450
Text Notes 4400 750  0    60   ~ 0
One cap near each power pin
$Comp
L Device:Ferrite_Bead_Small L301
U 1 1 5AB33195
P 10100 5100
F 0 "L301" H 10175 5150 50  0000 L CNN
F 1 "Ferrite_Bead_Small" H 10175 5050 50  0001 L CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 10030 5100 50  0001 C CNN
F 3 "" H 10100 5100 50  0000 C CNN
	1    10100 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 4850 10100 5000
Wire Wire Line
	10100 5200 10100 5500
$Comp
L Device:C C310
U 1 1 5AB33864
P 10100 5750
F 0 "C310" H 10125 5850 50  0000 L CNN
F 1 "10u" H 10125 5650 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 10138 5600 50  0001 C CNN
F 3 "" H 10100 5750 50  0000 C CNN
	1    10100 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C309
U 1 1 5AB3465A
P 9800 5750
F 0 "C309" H 9825 5850 50  0000 L CNN
F 1 "10u" H 9825 5650 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 9838 5600 50  0001 C CNN
F 3 "" H 9800 5750 50  0000 C CNN
	1    9800 5750
	1    0    0    -1  
$EndComp
Text Label 9800 6050 2    60   ~ 0
gnd
Text Label 10100 6050 2    60   ~ 0
gnd
Wire Wire Line
	10100 6050 10100 5900
Wire Wire Line
	9800 5900 9800 6050
Connection ~ 10100 5500
Wire Wire Line
	9800 5600 9800 5500
Text Label 9800 5500 0    60   ~ 0
vdd_io
Text Notes 10300 4800 0    60   ~ 0
I/O extension
Text Notes 1850 5000 0    60   ~ 0
Real-time clock
Text Notes 2050 2350 0    60   ~ 0
Main clock
$Comp
L Device:C C311
U 1 1 5B283E1D
P 5500 1400
F 0 "C311" H 5525 1500 50  0000 L CNN
F 1 "100n" H 5525 1300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5538 1250 50  0001 C CNN
F 3 "" H 5500 1400 50  0000 C CNN
	1    5500 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 1250 5500 1000
Connection ~ 5500 1000
Wire Wire Line
	5500 1750 5500 1550
Connection ~ 5250 1750
$Comp
L Device:Ferrite_Bead_Small L302
U 1 1 5B4A034A
P 4200 1000
F 0 "L302" V 4275 1050 50  0000 L CNN
F 1 "Ferrite_Bead_Small" V 4275 950 50  0001 L CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 4130 1000 50  0001 C CNN
F 3 "" H 4200 1000 50  0000 C CNN
	1    4200 1000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4100 1000 3800 1000
Connection ~ 4500 1000
Text Label 4400 1000 0    60   ~ 0
vdd_filt
Text Label 7200 900  2    60   ~ 0
vdd_filt
Text Label 7950 900  0    60   ~ 0
vdd_filt
$Comp
L Pistoke-rescue:TEST TP305
U 1 1 5B4E75DF
P 3150 4700
AR Path="/5B4E75DF" Ref="TP305"  Part="1" 
AR Path="/5A7A5454/5B4E75DF" Ref="TP305"  Part="1" 
F 0 "TP305" H 3150 5000 50  0000 C BNN
F 1 "TEST" H 3150 4950 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3150 4700 50  0001 C CNN
F 3 "" H 3150 4700 50  0000 C CNN
	1    3150 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 4700 3150 4950
Wire Wire Line
	3150 4950 3900 4950
$Comp
L Pistoke-rescue:TEST TP302
U 1 1 5B4E9006
P 3050 2650
AR Path="/5B4E9006" Ref="TP302"  Part="1" 
AR Path="/5A7A5454/5B4E9006" Ref="TP302"  Part="1" 
F 0 "TP302" H 3050 2950 50  0000 C BNN
F 1 "Vbat" H 3050 2900 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3050 2650 50  0001 C CNN
F 3 "" H 3050 2650 50  0000 C CNN
	1    3050 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 2650 3700 2650
Wire Wire Line
	3700 2650 3700 2750
Wire Wire Line
	3700 2750 3900 2750
Text Label 3250 2650 0    60   ~ 0
vbat
Text Label 3550 4850 0    60   ~ 0
PC8
Text Label 3550 4950 0    60   ~ 0
PC9
Wire Wire Line
	3450 4250 3900 4250
NoConn ~ 3450 4250
$Comp
L Pistoke-rescue:TEST TP301
U 1 1 5B4EC6AE
P 9200 2550
AR Path="/5B4EC6AE" Ref="TP301"  Part="1" 
AR Path="/5A7A5454/5B4EC6AE" Ref="TP301"  Part="1" 
F 0 "TP301" H 9200 2850 50  0000 C BNN
F 1 "TEST" H 9200 2800 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 9200 2550 50  0001 C CNN
F 3 "" H 9200 2550 50  0000 C CNN
	1    9200 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 4450 3900 4450
Wire Wire Line
	3450 4550 3900 4550
Wire Wire Line
	3450 4750 3900 4750
Wire Wire Line
	3450 4850 3900 4850
NoConn ~ 3450 4450
NoConn ~ 3450 4550
NoConn ~ 3450 4750
NoConn ~ 3450 4850
Wire Wire Line
	5000 1750 5250 1750
Wire Wire Line
	4750 1750 5000 1750
Wire Wire Line
	4500 1750 4750 1750
Wire Wire Line
	4750 1000 5000 1000
Wire Wire Line
	5000 1000 5250 1000
Wire Wire Line
	5250 1000 5500 1000
Wire Wire Line
	5900 6300 6000 6300
Wire Wire Line
	6000 6300 6100 6300
Wire Wire Line
	6100 6300 6200 6300
Wire Wire Line
	6200 6300 6400 6300
Wire Wire Line
	5800 1000 5900 1000
Wire Wire Line
	5900 1000 6000 1000
Wire Wire Line
	6000 1000 6100 1000
Wire Wire Line
	6100 1000 6200 1000
Wire Wire Line
	2550 2800 2750 2800
Wire Wire Line
	2550 2800 2550 3000
Wire Wire Line
	1900 2800 1900 2950
Wire Wire Line
	1900 2950 1900 3000
Wire Wire Line
	2550 5450 2750 5450
Wire Wire Line
	2550 5450 2550 5650
Wire Wire Line
	1900 5450 1900 5600
Wire Wire Line
	1900 5600 1900 5650
Wire Wire Line
	1550 6850 2050 6850
Wire Wire Line
	2400 6950 2700 6950
Wire Wire Line
	10100 5500 10600 5500
Wire Wire Line
	10100 5500 10100 5600
Wire Wire Line
	5500 1000 5800 1000
Wire Wire Line
	5250 1750 5500 1750
Wire Wire Line
	4500 1000 4750 1000
Text Notes 2200 3100 0    50   ~ 0
HC49
Text Notes 2350 2450 0    50   ~ 0
NP
Text Notes 2150 5700 0    50   ~ 0
<= 7pF
Text Notes 2350 5100 0    50   ~ 0
NP
Text Notes 5600 8050 0    50   ~ 0
The VREF+ and VREF- pins are not available, they are internally connected to the ADC voltage supply (VDDA) and ground (VSSA).
$EndSCHEMATC
