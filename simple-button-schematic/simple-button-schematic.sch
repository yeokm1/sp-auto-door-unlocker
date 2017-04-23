EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:simple-button-schematic-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L SW_PUSH SW?
U 1 1 5860C9AE
P 4100 3050
F 0 "SW?" H 4250 3160 50  0000 C CNN
F 1 "SW_PUSH" H 4100 2970 50  0000 C CNN
F 2 "" H 4100 3050 50  0000 C CNN
F 3 "" H 4100 3050 50  0000 C CNN
	1    4100 3050
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR?
U 1 1 5860C9FD
P 3600 3000
F 0 "#PWR?" H 3600 2850 50  0001 C CNN
F 1 "+12V" H 3600 3140 50  0000 C CNN
F 2 "" H 3600 3000 50  0000 C CNN
F 3 "" H 3600 3000 50  0000 C CNN
	1    3600 3000
	1    0    0    -1  
$EndComp
$Comp
L Battery BT?
U 1 1 5860CA13
P 3600 3300
F 0 "BT?" H 3350 3350 50  0000 L CNN
F 1 "A23 Battery" H 3150 3150 50  0000 L CNN
F 2 "" V 3600 3340 50  0000 C CNN
F 3 "" V 3600 3340 50  0000 C CNN
	1    3600 3300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5860CA46
P 3600 3600
F 0 "#PWR?" H 3600 3350 50  0001 C CNN
F 1 "GND" H 3600 3450 50  0000 C CNN
F 2 "" H 3600 3600 50  0000 C CNN
F 3 "" H 3600 3600 50  0000 C CNN
	1    3600 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 3000 3600 3150
Wire Wire Line
	3600 3600 3600 3450
$Comp
L R R?
U 1 1 5860CA67
P 4700 3050
F 0 "R?" V 4780 3050 50  0000 C CNN
F 1 "2.2K" V 4700 3050 50  0000 C CNN
F 2 "" V 4630 3050 50  0000 C CNN
F 3 "" H 4700 3050 50  0000 C CNN
	1    4700 3050
	0    1    1    0   
$EndComp
Connection ~ 3600 3050
Text GLabel 5050 3050 2    60   Input ~ 0
SMC5326P-3
Wire Wire Line
	4400 3050 4550 3050
Wire Wire Line
	4850 3050 5050 3050
Wire Wire Line
	3600 3050 3800 3050
$Comp
L Q_NPN_BCE Q?
U 1 1 5860CF6A
P 4100 3400
F 0 "Q?" V 4100 3050 50  0000 R CNN
F 1 "Q_NPN_BCE" V 4000 3200 50  0000 R CNN
F 2 "" H 4300 3500 50  0000 C CNN
F 3 "" H 4100 3400 50  0000 C CNN
	1    4100 3400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4300 3300 4450 3300
Wire Wire Line
	4450 3300 4450 3050
Connection ~ 4450 3050
Wire Wire Line
	3750 3050 3750 3300
Wire Wire Line
	3750 3300 3900 3300
Connection ~ 3750 3050
Text GLabel 4200 3750 2    60   Input ~ 0
External_Control
Wire Wire Line
	4100 3600 4100 3750
Wire Wire Line
	4100 3750 4200 3750
$EndSCHEMATC
