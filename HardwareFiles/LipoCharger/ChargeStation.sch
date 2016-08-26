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
LIBS:special
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
LIBS:custom
LIBS:USBtiny-cache
LIBS:ChargeStation-cache
EELAYER 27 0
EELAYER END
$Descr User 7874 4000
encoding utf-8
Sheet 1 1
Title ""
Date "5 jul 2015"
Rev ""
Comp "http://creativecommons.org/licenses/by-nc-sa/4.0/"
Comment1 "Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License"
Comment2 "This work is licensed under a: "
Comment3 "Universidad de los Andes Designed by: Andrés Rengifo"
Comment4 ""
$EndDescr
$Comp
L MCP78833 U5
U 1 1 54BFE25F
P 4750 1500
F 0 "U5" H 5144 1894 60  0000 C CNN
F 1 "MCP78833" H 4900 1150 60  0000 C CNN
F 2 "" H 4750 1500 60  0000 C CNN
F 3 "" H 4750 1500 60  0000 C CNN
	1    4750 1500
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 54BFE2DE
P 3900 1600
F 0 "R2" V 3900 1700 40  0000 C CNN
F 1 "470" V 3900 1550 40  0000 C CNN
F 2 "~" V 3830 1600 30  0000 C CNN
F 3 "~" H 3900 1600 30  0000 C CNN
	1    3900 1600
	0    -1   -1   0   
$EndComp
$Comp
L R R1
U 1 1 54BFE2F5
P 3900 1500
F 0 "R1" V 3900 1600 40  0000 C CNN
F 1 "470" V 3900 1450 40  0000 C CNN
F 2 "~" V 3830 1500 30  0000 C CNN
F 3 "~" H 3900 1500 30  0000 C CNN
	1    3900 1500
	0    -1   -1   0   
$EndComp
Connection ~ 4150 1500
Connection ~ 4150 1600
$Comp
L R R3
U 1 1 54BFE42A
P 3900 1700
F 0 "R3" V 3900 1800 40  0000 C CNN
F 1 "470" V 3900 1650 40  0000 C CNN
F 2 "~" V 3830 1700 30  0000 C CNN
F 3 "~" H 3900 1700 30  0000 C CNN
	1    3900 1700
	0    -1   -1   0   
$EndComp
Connection ~ 4150 1700
$Comp
L LED D3
U 1 1 54BFE488
P 3650 1200
F 0 "D3" H 3750 1250 50  0000 C CNN
F 1 "CHARGING" H 3650 1100 50  0000 C CNN
F 2 "~" H 3650 1200 60  0000 C CNN
F 3 "~" H 3650 1200 60  0000 C CNN
	1    3650 1200
	0    1    1    0   
$EndComp
Wire Wire Line
	3650 1400 3650 1500
Connection ~ 3650 1500
Connection ~ 3650 1400
$Comp
L LED D2
U 1 1 54BFE4A9
P 3350 1200
F 0 "D2" H 3450 1250 50  0000 C CNN
F 1 "COMPLETE" H 3350 1100 50  0000 C CNN
F 2 "~" H 3350 1200 60  0000 C CNN
F 3 "~" H 3350 1200 60  0000 C CNN
	1    3350 1200
	0    1    1    0   
$EndComp
$Comp
L LED D1
U 1 1 54BFE4AF
P 3050 1200
F 0 "D1" H 3150 1250 50  0000 C CNN
F 1 "POWER" H 3050 1100 50  0000 C CNN
F 2 "~" H 3050 1200 60  0000 C CNN
F 3 "~" H 3050 1200 60  0000 C CNN
	1    3050 1200
	0    1    1    0   
$EndComp
Wire Wire Line
	3650 1600 3350 1600
Wire Wire Line
	3350 1600 3350 1400
Wire Wire Line
	3650 1700 3050 1700
Wire Wire Line
	3050 1700 3050 1400
Connection ~ 3350 1400
Connection ~ 3650 1600
Connection ~ 3650 1700
Connection ~ 3050 1400
$Comp
L VCC #PWR01
U 1 1 54BFE4D3
P 3350 900
F 0 "#PWR01" H 3350 1000 30  0001 C CNN
F 1 "VCC" H 3350 1000 30  0000 C CNN
F 2 "" H 3350 900 60  0000 C CNN
F 3 "" H 3350 900 60  0000 C CNN
	1    3350 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 1000 3350 900 
Connection ~ 3350 1000
Connection ~ 3650 1000
Connection ~ 3050 1000
Wire Wire Line
	4150 1000 4150 1400
Connection ~ 4150 1300
Connection ~ 4150 1400
Wire Wire Line
	2700 1000 4150 1000
Wire Wire Line
	5300 1400 5300 1300
Wire Wire Line
	5300 1300 6700 1300
Connection ~ 5300 1300
Connection ~ 5300 1400
$Comp
L C C2
U 1 1 54BFE642
P 5900 1500
F 0 "C2" H 5900 1600 40  0000 L CNN
F 1 "1uF" H 5906 1415 40  0000 L CNN
F 2 "~" H 5938 1350 30  0000 C CNN
F 3 "~" H 5900 1500 60  0000 C CNN
	1    5900 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 54BFE676
P 5900 1700
F 0 "#PWR02" H 5900 1700 30  0001 C CNN
F 1 "GND" H 5900 1630 30  0001 C CNN
F 2 "" H 5900 1700 60  0000 C CNN
F 3 "" H 5900 1700 60  0000 C CNN
	1    5900 1700
	1    0    0    -1  
$EndComp
Connection ~ 5900 1700
$Comp
L R R7
U 1 1 54BFE683
P 5700 1750
F 0 "R7" V 5700 1850 40  0000 C CNN
F 1 "10K" V 5700 1700 40  0000 C CNN
F 2 "~" V 5630 1750 30  0000 C CNN
F 3 "~" H 5700 1750 30  0000 C CNN
	1    5700 1750
	-1   0    0    1   
$EndComp
Wire Wire Line
	5300 1500 5700 1500
$Comp
L GND #PWR03
U 1 1 54BFE6A7
P 5700 2000
F 0 "#PWR03" H 5700 2000 30  0001 C CNN
F 1 "GND" H 5700 1930 30  0001 C CNN
F 2 "" H 5700 2000 60  0000 C CNN
F 3 "" H 5700 2000 60  0000 C CNN
	1    5700 2000
	1    0    0    -1  
$EndComp
Connection ~ 5700 2000
Connection ~ 5700 1500
Connection ~ 5300 1500
$Comp
L GND #PWR04
U 1 1 54BFE6BB
P 5300 1700
F 0 "#PWR04" H 5300 1700 30  0001 C CNN
F 1 "GND" H 5300 1630 30  0001 C CNN
F 2 "" H 5300 1700 60  0000 C CNN
F 3 "" H 5300 1700 60  0000 C CNN
	1    5300 1700
	0    -1   -1   0   
$EndComp
Connection ~ 5300 1700
Connection ~ 5300 1600
Text Label 5300 1600 0    60   ~ 0
PROG
Connection ~ 5900 1300
$Comp
L C C1
U 1 1 54BFE6F3
P 2700 1200
F 0 "C1" H 2700 1300 40  0000 L CNN
F 1 "1uF" H 2706 1115 40  0000 L CNN
F 2 "~" H 2738 1050 30  0000 C CNN
F 3 "~" H 2700 1200 60  0000 C CNN
	1    2700 1200
	1    0    0    -1  
$EndComp
Connection ~ 2700 1000
$Comp
L GND #PWR05
U 1 1 54BFE734
P 2700 1400
F 0 "#PWR05" H 2700 1400 30  0001 C CNN
F 1 "GND" H 2700 1330 30  0001 C CNN
F 2 "" H 2700 1400 60  0000 C CNN
F 3 "" H 2700 1400 60  0000 C CNN
	1    2700 1400
	1    0    0    -1  
$EndComp
Connection ~ 2700 1400
Text Label 1400 2100 0    60   ~ 0
PROG
Connection ~ 1100 2150
$Comp
L R R5
U 1 1 54BFE83A
P 1100 2400
F 0 "R5" V 1100 2500 40  0000 C CNN
F 1 "5K" V 1100 2350 40  0000 C CNN
F 2 "~" V 1030 2400 30  0000 C CNN
F 3 "~" H 1100 2400 30  0000 C CNN
	1    1100 2400
	-1   0    0    1   
$EndComp
$Comp
L R R8
U 1 1 54BFE846
P 1650 2400
F 0 "R8" V 1650 2500 40  0000 C CNN
F 1 "~" V 1650 2350 40  0000 C CNN
F 2 "~" V 1580 2400 30  0000 C CNN
F 3 "~" H 1650 2400 30  0000 C CNN
	1    1650 2400
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR06
U 1 1 54BFE867
P 1100 2650
F 0 "#PWR06" H 1100 2650 30  0001 C CNN
F 1 "GND" H 1100 2580 30  0001 C CNN
F 2 "" H 1100 2650 60  0000 C CNN
F 3 "" H 1100 2650 60  0000 C CNN
	1    1100 2650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 54BFE873
P 1650 2650
F 0 "#PWR07" H 1650 2650 30  0001 C CNN
F 1 "GND" H 1650 2580 30  0001 C CNN
F 2 "" H 1650 2650 60  0000 C CNN
F 3 "" H 1650 2650 60  0000 C CNN
	1    1650 2650
	1    0    0    -1  
$EndComp
Connection ~ 1650 2650
Connection ~ 1100 2650
Connection ~ 6400 1300
$Comp
L BATTERY BT1
U 1 1 54C00C3E
P 6400 1600
F 0 "BT1" H 6400 1800 50  0000 C CNN
F 1 "BATTERY" H 6400 1410 50  0000 C CNN
F 2 "~" H 6400 1600 60  0000 C CNN
F 3 "~" H 6400 1600 60  0000 C CNN
	1    6400 1600
	0    1    1    0   
$EndComp
$Comp
L GND #PWR08
U 1 1 54C00C5F
P 6400 1900
F 0 "#PWR08" H 6400 1900 30  0001 C CNN
F 1 "GND" H 6400 1830 30  0001 C CNN
F 2 "" H 6400 1900 60  0000 C CNN
F 3 "" H 6400 1900 60  0000 C CNN
	1    6400 1900
	1    0    0    -1  
$EndComp
Connection ~ 6400 1900
Text Notes 1100 2850 0    60   ~ 0
1K=1000mA\n2K=500mA\n5K=200mA\n10K=100mA
$Comp
L CONN_4 P1
U 1 1 54C00DA6
P 1150 1000
F 0 "P1" V 1100 1000 50  0000 C CNN
F 1 "USB" V 1200 1000 50  0000 C CNN
F 2 "" H 1150 1000 60  0000 C CNN
F 3 "" H 1150 1000 60  0000 C CNN
	1    1150 1000
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR09
U 1 1 54C00ED6
P 1500 850
F 0 "#PWR09" H 1500 850 30  0001 C CNN
F 1 "GND" H 1500 780 30  0001 C CNN
F 2 "" H 1500 850 60  0000 C CNN
F 3 "" H 1500 850 60  0000 C CNN
	1    1500 850 
	0    -1   -1   0   
$EndComp
Connection ~ 1500 850 
$Comp
L VCC #PWR010
U 1 1 54C00EE5
P 1500 1150
F 0 "#PWR010" H 1500 1250 30  0001 C CNN
F 1 "VCC" H 1500 1250 30  0000 C CNN
F 2 "" H 1500 1150 60  0000 C CNN
F 3 "" H 1500 1150 60  0000 C CNN
	1    1500 1150
	0    1    1    0   
$EndComp
Connection ~ 1500 1150
$Comp
L CONN_2 P6
U 1 1 54C00F77
P 7050 1400
F 0 "P6" V 7000 1400 40  0000 C CNN
F 1 "BATT" V 7100 1400 40  0000 C CNN
F 2 "" H 7050 1400 60  0000 C CNN
F 3 "" H 7050 1400 60  0000 C CNN
	1    7050 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 1500 6700 1850
$Comp
L GND #PWR011
U 1 1 54C011D7
P 6700 1850
F 0 "#PWR011" H 6700 1850 30  0001 C CNN
F 1 "GND" H 6700 1780 30  0001 C CNN
F 2 "" H 6700 1850 60  0000 C CNN
F 3 "" H 6700 1850 60  0000 C CNN
	1    6700 1850
	1    0    0    -1  
$EndComp
Connection ~ 6700 1850
Connection ~ 6700 1500
Connection ~ 6700 1300
$Comp
L CONN_2 P7
U 1 1 54C01BEC
P 1200 1600
F 0 "P7" V 1150 1600 40  0000 C CNN
F 1 "POWER" V 1250 1600 40  0000 C CNN
F 2 "" H 1200 1600 60  0000 C CNN
F 3 "" H 1200 1600 60  0000 C CNN
	1    1200 1600
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR012
U 1 1 54C01C05
P 1550 1500
F 0 "#PWR012" H 1550 1500 30  0001 C CNN
F 1 "GND" H 1550 1430 30  0001 C CNN
F 2 "" H 1550 1500 60  0000 C CNN
F 3 "" H 1550 1500 60  0000 C CNN
	1    1550 1500
	0    -1   -1   0   
$EndComp
Connection ~ 1550 1500
$Comp
L VCC #PWR013
U 1 1 54C01C14
P 1550 1700
F 0 "#PWR013" H 1550 1800 30  0001 C CNN
F 1 "VCC" H 1550 1800 30  0000 C CNN
F 2 "" H 1550 1700 60  0000 C CNN
F 3 "" H 1550 1700 60  0000 C CNN
	1    1550 1700
	1    0    0    -1  
$EndComp
Connection ~ 1550 1700
Wire Wire Line
	1100 2150 1650 2150
Connection ~ 1650 2150
Wire Wire Line
	1400 2100 1400 2150
Connection ~ 1400 2150
Connection ~ 1400 2100
$EndSCHEMATC
