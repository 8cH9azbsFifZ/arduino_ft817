/* Unmodified lines */


/*
	 This file is part of xmlbandplan.

    Xmlbandplan is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Xmlbandplan is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Xmlbandplan.  If not, see http://www.gnu.org/licenses/;.	  
*/

/*
 * This file has been created by xmlbandplan.
 */


#include "FT817.h" 

typedef struct 
{
  prog_char *name; // channel name
  prog_int32_t freq;  // frequency (Hz/10)  
  prog_uint16_t mode;  // mode
  prog_int32_t shift;
  prog_char *qth;
} t_channel;

		
	 

	


	

	 

	

	

	




	
	

	 

	
	







	

	 

	
	







	

	 

	



	

	 

	




	

	 
	
	






	


	 
	






	

	 
	
	



	

	 

	








	


	

	






















































































	

	 

	

	


	


	 

	

















	

	 

	



	

	

	






































































	

	

	

	
	









	
/* String definitions */


prog_char ch1_name[] PROGMEM = 	"WSPR";
prog_char ch1_qth[] PROGMEM =  "";
prog_char ch2_name[] PROGMEM = 	"WSPR";
prog_char ch2_qth[] PROGMEM =  "";
prog_char ch3_name[] PROGMEM = "QRP";
prog_char ch3_qth[] PROGMEM =  "";
prog_char ch4_name[] PROGMEM = 	"ATV";
prog_char ch4_qth[] PROGMEM =  "";
prog_char ch5_name[] PROGMEM = "Emergency Region 1";
prog_char ch5_qth[] PROGMEM =  "";
prog_char ch6_name[] PROGMEM = "QRP";
prog_char ch6_qth[] PROGMEM =  "";
prog_char ch7_name[] PROGMEM = "Digital Speech";
prog_char ch7_qth[] PROGMEM =  "";
prog_char ch8_name[] PROGMEM = "QRP";
prog_char ch8_qth[] PROGMEM =  "";
prog_char ch9_name[] PROGMEM = "QRS";
prog_char ch9_qth[] PROGMEM =  "";
prog_char ch10_name[] PROGMEM = "WSPR";
prog_char ch10_qth[] PROGMEM =  "";
prog_char ch11_name[] PROGMEM = 	"QRP";
prog_char ch11_qth[] PROGMEM =  "";
prog_char ch12_name[] PROGMEM = "Emergency Region 1";
prog_char ch12_qth[] PROGMEM =  "";
prog_char ch13_name[] PROGMEM = "ATV";
prog_char ch13_qth[] PROGMEM =  "";
prog_char ch14_name[] PROGMEM = "Digital Speech";
prog_char ch14_qth[] PROGMEM =  "";
prog_char ch15_name[] PROGMEM = "QRP";
prog_char ch15_qth[] PROGMEM =  "";
prog_char ch16_name[] PROGMEM = "WSPR";
prog_char ch16_qth[] PROGMEM =  "";
prog_char ch17_name[] PROGMEM = 	"QRP";
prog_char ch17_qth[] PROGMEM =  "";
prog_char ch18_name[] PROGMEM = "WSPR";
prog_char ch18_qth[] PROGMEM =  "";
prog_char ch19_name[] PROGMEM = 	"QRP";
prog_char ch19_qth[] PROGMEM =  "";
prog_char ch20_name[] PROGMEM = "Emergency";
prog_char ch20_qth[] PROGMEM =  "";
prog_char ch21_name[] PROGMEM = "WSPR";
prog_char ch21_qth[] PROGMEM =  "";
prog_char ch22_name[] PROGMEM = 	"QRP";
prog_char ch22_qth[] PROGMEM =  "";
prog_char ch23_name[] PROGMEM = "QRP";
prog_char ch23_qth[] PROGMEM =  "";
prog_char ch24_name[] PROGMEM = "Digital Speech";
prog_char ch24_qth[] PROGMEM =  "";
prog_char ch25_name[] PROGMEM = "Emergency";
prog_char ch25_qth[] PROGMEM =  "";
prog_char ch26_name[] PROGMEM = "WSPR";
prog_char ch26_qth[] PROGMEM =  "";
prog_char ch27_name[] PROGMEM = 	"QRP";
prog_char ch27_qth[] PROGMEM =  "";
prog_char ch28_name[] PROGMEM = "QRS";
prog_char ch28_qth[] PROGMEM =  "";
prog_char ch29_name[] PROGMEM = "Digital Speech";
prog_char ch29_qth[] PROGMEM =  "";
prog_char ch30_name[] PROGMEM = "WSPR";
prog_char ch30_qth[] PROGMEM =  "";
prog_char ch31_name[] PROGMEM = 	"QRP";
prog_char ch31_qth[] PROGMEM =  "";
prog_char ch32_name[] PROGMEM = "QRP";
prog_char ch32_qth[] PROGMEM =  "";
prog_char ch33_name[] PROGMEM = "WSPR";
prog_char ch33_qth[] PROGMEM =  "";
prog_char ch34_name[] PROGMEM = 	"QRP";
prog_char ch34_qth[] PROGMEM =  "";
prog_char ch35_name[] PROGMEM = "Digital Speech";
prog_char ch35_qth[] PROGMEM =  "";
prog_char ch36_name[] PROGMEM = "FM Call";
prog_char ch36_qth[] PROGMEM =  "";
prog_char ch37_name[] PROGMEM = "FM Call";
prog_char ch37_qth[] PROGMEM =  "";
prog_char ch38_name[] PROGMEM = "QRS";
prog_char ch38_qth[] PROGMEM =  "";
prog_char ch39_name[] PROGMEM = "QRP";
prog_char ch39_qth[] PROGMEM =  "";
prog_char ch40_name[] PROGMEM = "APRS";
prog_char ch40_qth[] PROGMEM =  "";
prog_char ch41_name[] PROGMEM = "WSPR";
prog_char ch41_qth[] PROGMEM =  "";
prog_char ch42_name[] PROGMEM = 	"1";
prog_char ch42_qth[] PROGMEM =  "";
prog_char ch43_name[] PROGMEM = "2";
prog_char ch43_qth[] PROGMEM =  "";
prog_char ch44_name[] PROGMEM = "3";
prog_char ch44_qth[] PROGMEM =  "";
prog_char ch45_name[] PROGMEM = "3A";
prog_char ch45_qth[] PROGMEM =  "";
prog_char ch46_name[] PROGMEM = "4";
prog_char ch46_qth[] PROGMEM =  "";
prog_char ch47_name[] PROGMEM = "5";
prog_char ch47_qth[] PROGMEM =  "";
prog_char ch48_name[] PROGMEM = "6";
prog_char ch48_qth[] PROGMEM =  "";
prog_char ch49_name[] PROGMEM = "7";
prog_char ch49_qth[] PROGMEM =  "";
prog_char ch50_name[] PROGMEM = "7A";
prog_char ch50_qth[] PROGMEM =  "";
prog_char ch51_name[] PROGMEM = "8";
prog_char ch51_qth[] PROGMEM =  "";
prog_char ch52_name[] PROGMEM = "9";
prog_char ch52_qth[] PROGMEM =  "";
prog_char ch53_name[] PROGMEM = "10";
prog_char ch53_qth[] PROGMEM =  "";
prog_char ch54_name[] PROGMEM = "11";
prog_char ch54_qth[] PROGMEM =  "";
prog_char ch55_name[] PROGMEM = "11A";
prog_char ch55_qth[] PROGMEM =  "";
prog_char ch56_name[] PROGMEM = "12";
prog_char ch56_qth[] PROGMEM =  "";
prog_char ch57_name[] PROGMEM = "13";
prog_char ch57_qth[] PROGMEM =  "";
prog_char ch58_name[] PROGMEM = "14";
prog_char ch58_qth[] PROGMEM =  "";
prog_char ch59_name[] PROGMEM = "15";
prog_char ch59_qth[] PROGMEM =  "";
prog_char ch60_name[] PROGMEM = "15A";
prog_char ch60_qth[] PROGMEM =  "";
prog_char ch61_name[] PROGMEM = "16";
prog_char ch61_qth[] PROGMEM =  "";
prog_char ch62_name[] PROGMEM = "17";
prog_char ch62_qth[] PROGMEM =  "";
prog_char ch63_name[] PROGMEM = "18";
prog_char ch63_qth[] PROGMEM =  "";
prog_char ch64_name[] PROGMEM = "19";
prog_char ch64_qth[] PROGMEM =  "";
prog_char ch65_name[] PROGMEM = "19A";
prog_char ch65_qth[] PROGMEM =  "";
prog_char ch66_name[] PROGMEM = "20";
prog_char ch66_qth[] PROGMEM =  "";
prog_char ch67_name[] PROGMEM = "21";
prog_char ch67_qth[] PROGMEM =  "";
prog_char ch68_name[] PROGMEM = "22";
prog_char ch68_qth[] PROGMEM =  "";
prog_char ch69_name[] PROGMEM = "23";
prog_char ch69_qth[] PROGMEM =  "";
prog_char ch70_name[] PROGMEM = "24";
prog_char ch70_qth[] PROGMEM =  "";
prog_char ch71_name[] PROGMEM = "25";
prog_char ch71_qth[] PROGMEM =  "";
prog_char ch72_name[] PROGMEM = "26";
prog_char ch72_qth[] PROGMEM =  "";
prog_char ch73_name[] PROGMEM = "27";
prog_char ch73_qth[] PROGMEM =  "";
prog_char ch74_name[] PROGMEM = "28";
prog_char ch74_qth[] PROGMEM =  "";
prog_char ch75_name[] PROGMEM = "29";
prog_char ch75_qth[] PROGMEM =  "";
prog_char ch76_name[] PROGMEM = "30";
prog_char ch76_qth[] PROGMEM =  "";
prog_char ch77_name[] PROGMEM = "31";
prog_char ch77_qth[] PROGMEM =  "";
prog_char ch78_name[] PROGMEM = "32";
prog_char ch78_qth[] PROGMEM =  "";
prog_char ch79_name[] PROGMEM = "33";
prog_char ch79_qth[] PROGMEM =  "";
prog_char ch80_name[] PROGMEM = "34";
prog_char ch80_qth[] PROGMEM =  "";
prog_char ch81_name[] PROGMEM = "35";
prog_char ch81_qth[] PROGMEM =  "";
prog_char ch82_name[] PROGMEM = "36";
prog_char ch82_qth[] PROGMEM =  "";
prog_char ch83_name[] PROGMEM = "37";
prog_char ch83_qth[] PROGMEM =  "";
prog_char ch84_name[] PROGMEM = "38";
prog_char ch84_qth[] PROGMEM =  "";
prog_char ch85_name[] PROGMEM = "39";
prog_char ch85_qth[] PROGMEM =  "";
prog_char ch86_name[] PROGMEM = "40";
prog_char ch86_qth[] PROGMEM =  "";
prog_char ch87_name[] PROGMEM = "41";
prog_char ch87_qth[] PROGMEM =  "";
prog_char ch88_name[] PROGMEM = "42";
prog_char ch88_qth[] PROGMEM =  "";
prog_char ch89_name[] PROGMEM = "43";
prog_char ch89_qth[] PROGMEM =  "";
prog_char ch90_name[] PROGMEM = "44";
prog_char ch90_qth[] PROGMEM =  "";
prog_char ch91_name[] PROGMEM = "45";
prog_char ch91_qth[] PROGMEM =  "";
prog_char ch92_name[] PROGMEM = "46";
prog_char ch92_qth[] PROGMEM =  "";
prog_char ch93_name[] PROGMEM = "47";
prog_char ch93_qth[] PROGMEM =  "";
prog_char ch94_name[] PROGMEM = "48";
prog_char ch94_qth[] PROGMEM =  "";
prog_char ch95_name[] PROGMEM = "49";
prog_char ch95_qth[] PROGMEM =  "";
prog_char ch96_name[] PROGMEM = "50";
prog_char ch96_qth[] PROGMEM =  "";
prog_char ch97_name[] PROGMEM = "51";
prog_char ch97_qth[] PROGMEM =  "";
prog_char ch98_name[] PROGMEM = "52";
prog_char ch98_qth[] PROGMEM =  "";
prog_char ch99_name[] PROGMEM = "53";
prog_char ch99_qth[] PROGMEM =  "";
prog_char ch100_name[] PROGMEM = "54";
prog_char ch100_qth[] PROGMEM =  "";
prog_char ch101_name[] PROGMEM = "55";
prog_char ch101_qth[] PROGMEM =  "";
prog_char ch102_name[] PROGMEM = "56";
prog_char ch102_qth[] PROGMEM =  "";
prog_char ch103_name[] PROGMEM = "57";
prog_char ch103_qth[] PROGMEM =  "";
prog_char ch104_name[] PROGMEM = "58";
prog_char ch104_qth[] PROGMEM =  "";
prog_char ch105_name[] PROGMEM = "59";
prog_char ch105_qth[] PROGMEM =  "";
prog_char ch106_name[] PROGMEM = "60";
prog_char ch106_qth[] PROGMEM =  "";
prog_char ch107_name[] PROGMEM = "61";
prog_char ch107_qth[] PROGMEM =  "";
prog_char ch108_name[] PROGMEM = "62";
prog_char ch108_qth[] PROGMEM =  "";
prog_char ch109_name[] PROGMEM = "63";
prog_char ch109_qth[] PROGMEM =  "";
prog_char ch110_name[] PROGMEM = "64";
prog_char ch110_qth[] PROGMEM =  "";
prog_char ch111_name[] PROGMEM = "65";
prog_char ch111_qth[] PROGMEM =  "";
prog_char ch112_name[] PROGMEM = "66";
prog_char ch112_qth[] PROGMEM =  "";
prog_char ch113_name[] PROGMEM = "67";
prog_char ch113_qth[] PROGMEM =  "";
prog_char ch114_name[] PROGMEM = "68";
prog_char ch114_qth[] PROGMEM =  "";
prog_char ch115_name[] PROGMEM = "69";
prog_char ch115_qth[] PROGMEM =  "";
prog_char ch116_name[] PROGMEM = "70";
prog_char ch116_qth[] PROGMEM =  "";
prog_char ch117_name[] PROGMEM = "71";
prog_char ch117_qth[] PROGMEM =  "";
prog_char ch118_name[] PROGMEM = "72";
prog_char ch118_qth[] PROGMEM =  "";
prog_char ch119_name[] PROGMEM = "73";
prog_char ch119_qth[] PROGMEM =  "";
prog_char ch120_name[] PROGMEM = "74";
prog_char ch120_qth[] PROGMEM =  "";
prog_char ch121_name[] PROGMEM = "75";
prog_char ch121_qth[] PROGMEM =  "";
prog_char ch122_name[] PROGMEM = "76";
prog_char ch122_qth[] PROGMEM =  "";
prog_char ch123_name[] PROGMEM = "77";
prog_char ch123_qth[] PROGMEM =  "";
prog_char ch124_name[] PROGMEM = "78";
prog_char ch124_qth[] PROGMEM =  "";
prog_char ch125_name[] PROGMEM = "79";
prog_char ch125_qth[] PROGMEM =  "";
prog_char ch126_name[] PROGMEM = "80";
prog_char ch126_qth[] PROGMEM =  "";
prog_char ch127_name[] PROGMEM = 	"WSPR";
prog_char ch127_qth[] PROGMEM =  "";
prog_char ch128_name[] PROGMEM = 	"S1";
prog_char ch128_qth[] PROGMEM =  "";
prog_char ch129_name[] PROGMEM = "ARPS";
prog_char ch129_qth[] PROGMEM =  "";
prog_char ch130_name[] PROGMEM = "Echolink";
prog_char ch130_qth[] PROGMEM =  "";
prog_char ch131_name[] PROGMEM = "Echolink";
prog_char ch131_qth[] PROGMEM =  "";
prog_char ch132_name[] PROGMEM = "RTTY local";
prog_char ch132_qth[] PROGMEM =  "";
prog_char ch133_name[] PROGMEM = "DV CQ";
prog_char ch133_qth[] PROGMEM =  "";
prog_char ch134_name[] PROGMEM = "PSK31";
prog_char ch134_qth[] PROGMEM =  "";
prog_char ch135_name[] PROGMEM = "SSB CQ";
prog_char ch135_qth[] PROGMEM =  "";
prog_char ch136_name[] PROGMEM = "MGM CQ";
prog_char ch136_qth[] PROGMEM =  "";
prog_char ch137_name[] PROGMEM = "WSPR";
prog_char ch137_qth[] PROGMEM =  "";
prog_char ch138_name[] PROGMEM = "SSTV CQ";
prog_char ch138_qth[] PROGMEM =  "";
prog_char ch139_name[] PROGMEM = "ATV";
prog_char ch139_qth[] PROGMEM =  "";
prog_char ch140_name[] PROGMEM = "RTTY CQ";
prog_char ch140_qth[] PROGMEM =  "";
prog_char ch141_name[] PROGMEM = "Fax CQ";
prog_char ch141_qth[] PROGMEM =  "";
prog_char ch142_name[] PROGMEM = "ATV CQ / Callback";
prog_char ch142_qth[] PROGMEM =  "";
prog_char ch143_name[] PROGMEM = 		"DB0VA";
prog_char ch143_qth[] PROGMEM =  "JO40bc";
prog_char ch144_name[] PROGMEM = "DB0ESW";
prog_char ch144_qth[] PROGMEM =  "JO51ae";
prog_char ch145_name[] PROGMEM = 	"1";
prog_char ch145_qth[] PROGMEM =  "";
prog_char ch146_name[] PROGMEM = "2";
prog_char ch146_qth[] PROGMEM =  "";
prog_char ch147_name[] PROGMEM = "3";
prog_char ch147_qth[] PROGMEM =  "";
prog_char ch148_name[] PROGMEM = "4";
prog_char ch148_qth[] PROGMEM =  "";
prog_char ch149_name[] PROGMEM = "5";
prog_char ch149_qth[] PROGMEM =  "";
prog_char ch150_name[] PROGMEM = "6";
prog_char ch150_qth[] PROGMEM =  "";
prog_char ch151_name[] PROGMEM = "7";
prog_char ch151_qth[] PROGMEM =  "";
prog_char ch152_name[] PROGMEM = "8";
prog_char ch152_qth[] PROGMEM =  "";
prog_char ch153_name[] PROGMEM = "9";
prog_char ch153_qth[] PROGMEM =  "";
prog_char ch154_name[] PROGMEM = "10";
prog_char ch154_qth[] PROGMEM =  "";
prog_char ch155_name[] PROGMEM = "11";
prog_char ch155_qth[] PROGMEM =  "";
prog_char ch156_name[] PROGMEM = "12";
prog_char ch156_qth[] PROGMEM =  "";
prog_char ch157_name[] PROGMEM = "13";
prog_char ch157_qth[] PROGMEM =  "";
prog_char ch158_name[] PROGMEM = "14";
prog_char ch158_qth[] PROGMEM =  "";
prog_char ch159_name[] PROGMEM = "15";
prog_char ch159_qth[] PROGMEM =  "";
prog_char ch160_name[] PROGMEM = "16";
prog_char ch160_qth[] PROGMEM =  "";
prog_char ch161_name[] PROGMEM = "17";
prog_char ch161_qth[] PROGMEM =  "";
prog_char ch162_name[] PROGMEM = "18";
prog_char ch162_qth[] PROGMEM =  "";
prog_char ch163_name[] PROGMEM = "19";
prog_char ch163_qth[] PROGMEM =  "";
prog_char ch164_name[] PROGMEM = "20";
prog_char ch164_qth[] PROGMEM =  "";
prog_char ch165_name[] PROGMEM = "21";
prog_char ch165_qth[] PROGMEM =  "";
prog_char ch166_name[] PROGMEM = "22";
prog_char ch166_qth[] PROGMEM =  "";
prog_char ch167_name[] PROGMEM = "23";
prog_char ch167_qth[] PROGMEM =  "";
prog_char ch168_name[] PROGMEM = "24";
prog_char ch168_qth[] PROGMEM =  "";
prog_char ch169_name[] PROGMEM = "25";
prog_char ch169_qth[] PROGMEM =  "";
prog_char ch170_name[] PROGMEM = "26";
prog_char ch170_qth[] PROGMEM =  "";
prog_char ch171_name[] PROGMEM = "27";
prog_char ch171_qth[] PROGMEM =  "";
prog_char ch172_name[] PROGMEM = "28";
prog_char ch172_qth[] PROGMEM =  "";
prog_char ch173_name[] PROGMEM = "29";
prog_char ch173_qth[] PROGMEM =  "";
prog_char ch174_name[] PROGMEM = "30";
prog_char ch174_qth[] PROGMEM =  "";
prog_char ch175_name[] PROGMEM = "31";
prog_char ch175_qth[] PROGMEM =  "";
prog_char ch176_name[] PROGMEM = "32";
prog_char ch176_qth[] PROGMEM =  "";
prog_char ch177_name[] PROGMEM = "33";
prog_char ch177_qth[] PROGMEM =  "";
prog_char ch178_name[] PROGMEM = "34";
prog_char ch178_qth[] PROGMEM =  "";
prog_char ch179_name[] PROGMEM = "35";
prog_char ch179_qth[] PROGMEM =  "";
prog_char ch180_name[] PROGMEM = "36";
prog_char ch180_qth[] PROGMEM =  "";
prog_char ch181_name[] PROGMEM = "37";
prog_char ch181_qth[] PROGMEM =  "";
prog_char ch182_name[] PROGMEM = "38";
prog_char ch182_qth[] PROGMEM =  "";
prog_char ch183_name[] PROGMEM = "39";
prog_char ch183_qth[] PROGMEM =  "";
prog_char ch184_name[] PROGMEM = "40";
prog_char ch184_qth[] PROGMEM =  "";
prog_char ch185_name[] PROGMEM = "41";
prog_char ch185_qth[] PROGMEM =  "";
prog_char ch186_name[] PROGMEM = "42";
prog_char ch186_qth[] PROGMEM =  "";
prog_char ch187_name[] PROGMEM = "43";
prog_char ch187_qth[] PROGMEM =  "";
prog_char ch188_name[] PROGMEM = "44";
prog_char ch188_qth[] PROGMEM =  "";
prog_char ch189_name[] PROGMEM = "45";
prog_char ch189_qth[] PROGMEM =  "";
prog_char ch190_name[] PROGMEM = "46";
prog_char ch190_qth[] PROGMEM =  "";
prog_char ch191_name[] PROGMEM = "47";
prog_char ch191_qth[] PROGMEM =  "";
prog_char ch192_name[] PROGMEM = "48";
prog_char ch192_qth[] PROGMEM =  "";
prog_char ch193_name[] PROGMEM = "49";
prog_char ch193_qth[] PROGMEM =  "";
prog_char ch194_name[] PROGMEM = "50";
prog_char ch194_qth[] PROGMEM =  "";
prog_char ch195_name[] PROGMEM = "51";
prog_char ch195_qth[] PROGMEM =  "";
prog_char ch196_name[] PROGMEM = "52";
prog_char ch196_qth[] PROGMEM =  "";
prog_char ch197_name[] PROGMEM = "53";
prog_char ch197_qth[] PROGMEM =  "";
prog_char ch198_name[] PROGMEM = "54";
prog_char ch198_qth[] PROGMEM =  "";
prog_char ch199_name[] PROGMEM = "55";
prog_char ch199_qth[] PROGMEM =  "";
prog_char ch200_name[] PROGMEM = "56";
prog_char ch200_qth[] PROGMEM =  "";
prog_char ch201_name[] PROGMEM = "57";
prog_char ch201_qth[] PROGMEM =  "";
prog_char ch202_name[] PROGMEM = "58";
prog_char ch202_qth[] PROGMEM =  "";
prog_char ch203_name[] PROGMEM = "59";
prog_char ch203_qth[] PROGMEM =  "";
prog_char ch204_name[] PROGMEM = "60";
prog_char ch204_qth[] PROGMEM =  "";
prog_char ch205_name[] PROGMEM = "61";
prog_char ch205_qth[] PROGMEM =  "";
prog_char ch206_name[] PROGMEM = "62";
prog_char ch206_qth[] PROGMEM =  "";
prog_char ch207_name[] PROGMEM = "63";
prog_char ch207_qth[] PROGMEM =  "";
prog_char ch208_name[] PROGMEM = "64";
prog_char ch208_qth[] PROGMEM =  "";
prog_char ch209_name[] PROGMEM = "65";
prog_char ch209_qth[] PROGMEM =  "";
prog_char ch210_name[] PROGMEM = "66";
prog_char ch210_qth[] PROGMEM =  "";
prog_char ch211_name[] PROGMEM = "67";
prog_char ch211_qth[] PROGMEM =  "";
prog_char ch212_name[] PROGMEM = "68";
prog_char ch212_qth[] PROGMEM =  "";
prog_char ch213_name[] PROGMEM = "69";
prog_char ch213_qth[] PROGMEM =  "";
prog_char ch214_name[] PROGMEM = 	"1";
prog_char ch214_qth[] PROGMEM =  "";
prog_char ch215_name[] PROGMEM = "2";
prog_char ch215_qth[] PROGMEM =  "";
prog_char ch216_name[] PROGMEM = "3";
prog_char ch216_qth[] PROGMEM =  "";
prog_char ch217_name[] PROGMEM = "4";
prog_char ch217_qth[] PROGMEM =  "";
prog_char ch218_name[] PROGMEM = "5";
prog_char ch218_qth[] PROGMEM =  "";
prog_char ch219_name[] PROGMEM = "6";
prog_char ch219_qth[] PROGMEM =  "";
prog_char ch220_name[] PROGMEM = "7";
prog_char ch220_qth[] PROGMEM =  "";
/* Channels structure */
PROGMEM  t_channel channels[] = {

{ch1_name, 13600, NULL , 0,ch1_qth},
{ch2_name, 183660, NULL , 0,ch2_qth},
{ch3_name, 183600,FT817_MODE_CW_NARROW, 0,ch3_qth},
{ch4_name, 373500, NULL , 0,ch4_qth},
{ch5_name, 376000, NULL , 0,ch5_qth},
{ch6_name, 369000, NULL , 0,ch6_qth},
{ch7_name, 363000, NULL , 0,ch7_qth},
{ch8_name, 356000,FT817_MODE_CW_NARROW, 0,ch8_qth},
{ch9_name, 355500,FT817_MODE_CW_NARROW, 0,ch9_qth},
{ch10_name, 359260, NULL , 0,ch10_qth},
{ch11_name, 703000,FT817_MODE_CW_NARROW, 0,ch11_qth},
{ch12_name, 711000, NULL , 0,ch12_qth},
{ch13_name, 716500, NULL , 0,ch13_qth},
{ch14_name, 707000, NULL , 0,ch14_qth},
{ch15_name, 709000, NULL , 0,ch15_qth},
{ch16_name, 703860, NULL , 0,ch16_qth},
{ch17_name, 1011600,FT817_MODE_CW_NARROW, 0,ch17_qth},
{ch18_name, 1013870, NULL , 0,ch18_qth},
{ch19_name, 1406000,FT817_MODE_CW_NARROW, 0,ch19_qth},
{ch20_name, 1430000, NULL , 0,ch20_qth},
{ch21_name, 1409560, NULL , 0,ch21_qth},
{ch22_name, 1808600,FT817_MODE_CW_NARROW, 0,ch22_qth},
{ch23_name, 1813000, NULL , 0,ch23_qth},
{ch24_name, 1815000, NULL , 0,ch24_qth},
{ch25_name, 1816000, NULL , 0,ch25_qth},
{ch26_name, 1810460, NULL , 0,ch26_qth},
{ch27_name, 2106000,FT817_MODE_CW_NARROW, 0,ch27_qth},
{ch28_name, 2105500,FT817_MODE_CW_NARROW, 0,ch28_qth},
{ch29_name, 2118000, NULL , 0,ch29_qth},
{ch30_name, 2199460, NULL , 0,ch30_qth},
{ch31_name, 2490600,FT817_MODE_CW_NARROW, 0,ch31_qth},
{ch32_name, 2495000, NULL , 0,ch32_qth},
{ch33_name, 2492460, NULL , 0,ch33_qth},
{ch34_name, 2836000, NULL , 0,ch34_qth},
{ch35_name, 2833000, NULL , 0,ch35_qth},
{ch36_name, 2960000,FT817_MODE_FM, 0,ch36_qth},
{ch37_name, 2961000,FT817_MODE_FM, 0,ch37_qth},
{ch38_name, 2805500,FT817_MODE_CW_NARROW, 0,ch38_qth},
{ch39_name, 2806000,FT817_MODE_CW_NARROW, 0,ch39_qth},
{ch40_name, 2925000,FT817_MODE_FM, 0,ch40_qth},
{ch41_name, 2812460, NULL , 0,ch41_qth},
{ch42_name, 2696500, NULL , 0,ch42_qth},
{ch43_name, 2697500, NULL , 0,ch43_qth},
{ch44_name, 2698500, NULL , 0,ch44_qth},
{ch45_name, 2699500, NULL , 0,ch45_qth},
{ch46_name, 2700500, NULL , 0,ch46_qth},
{ch47_name, 2701500, NULL , 0,ch47_qth},
{ch48_name, 2702500, NULL , 0,ch48_qth},
{ch49_name, 2703500, NULL , 0,ch49_qth},
{ch50_name, 2704500, NULL , 0,ch50_qth},
{ch51_name, 2705500, NULL , 0,ch51_qth},
{ch52_name, 2706500, NULL , 0,ch52_qth},
{ch53_name, 2707500, NULL , 0,ch53_qth},
{ch54_name, 2708500, NULL , 0,ch54_qth},
{ch55_name, 2709500, NULL , 0,ch55_qth},
{ch56_name, 2710500, NULL , 0,ch56_qth},
{ch57_name, 2711500,FT817_MODE_FM, 0,ch57_qth},
{ch58_name, 2712500,FT817_MODE_FM, 0,ch58_qth},
{ch59_name, 2713500,FT817_MODE_FM, 0,ch59_qth},
{ch60_name, 2715500, NULL , 0,ch60_qth},
{ch61_name, 2715500,FT817_MODE_FM, 0,ch61_qth},
{ch62_name, 2716500,FT817_MODE_FM, 0,ch62_qth},
{ch63_name, 2717500,FT817_MODE_FM, 0,ch63_qth},
{ch64_name, 2718500,FT817_MODE_FM, 0,ch64_qth},
{ch65_name, 2719500, NULL , 0,ch65_qth},
{ch66_name, 2720500,FT817_MODE_FM, 0,ch66_qth},
{ch67_name, 2721500,FT817_MODE_FM, 0,ch67_qth},
{ch68_name, 2722500,FT817_MODE_FM, 0,ch68_qth},
{ch69_name, 2725500,FT817_MODE_FM, 0,ch69_qth},
{ch70_name, 2723500,FT817_MODE_FM, 0,ch70_qth},
{ch71_name, 2724500,FT817_MODE_FM, 0,ch71_qth},
{ch72_name, 2726500,FT817_MODE_FM, 0,ch72_qth},
{ch73_name, 2727500,FT817_MODE_FM, 0,ch73_qth},
{ch74_name, 2728500,FT817_MODE_FM, 0,ch74_qth},
{ch75_name, 2729500,FT817_MODE_FM, 0,ch75_qth},
{ch76_name, 2730500,FT817_MODE_FM, 0,ch76_qth},
{ch77_name, 2731500,FT817_MODE_FM, 0,ch77_qth},
{ch78_name, 2732500,FT817_MODE_FM, 0,ch78_qth},
{ch79_name, 2733500,FT817_MODE_FM, 0,ch79_qth},
{ch80_name, 2734500,FT817_MODE_FM, 0,ch80_qth},
{ch81_name, 2735500,FT817_MODE_FM, 0,ch81_qth},
{ch82_name, 2736500,FT817_MODE_FM, 0,ch82_qth},
{ch83_name, 2737500,FT817_MODE_FM, 0,ch83_qth},
{ch84_name, 2738500,FT817_MODE_FM, 0,ch84_qth},
{ch85_name, 2737500,FT817_MODE_FM, 0,ch85_qth},
{ch86_name, 2740500,FT817_MODE_FM, 0,ch86_qth},
{ch87_name, 2656500,FT817_MODE_FM, 0,ch87_qth},
{ch88_name, 2657500,FT817_MODE_FM, 0,ch88_qth},
{ch89_name, 2658500,FT817_MODE_FM, 0,ch89_qth},
{ch90_name, 2659500,FT817_MODE_FM, 0,ch90_qth},
{ch91_name, 2660500,FT817_MODE_FM, 0,ch91_qth},
{ch92_name, 2661500,FT817_MODE_FM, 0,ch92_qth},
{ch93_name, 2662500,FT817_MODE_FM, 0,ch93_qth},
{ch94_name, 2663500,FT817_MODE_FM, 0,ch94_qth},
{ch95_name, 2664500,FT817_MODE_FM, 0,ch95_qth},
{ch96_name, 2665500,FT817_MODE_FM, 0,ch96_qth},
{ch97_name, 2666500,FT817_MODE_FM, 0,ch97_qth},
{ch98_name, 2667500,FT817_MODE_FM, 0,ch98_qth},
{ch99_name, 2668500,FT817_MODE_FM, 0,ch99_qth},
{ch100_name, 2669500,FT817_MODE_FM, 0,ch100_qth},
{ch101_name, 2670500,FT817_MODE_FM, 0,ch101_qth},
{ch102_name, 2671500,FT817_MODE_FM, 0,ch102_qth},
{ch103_name, 2672500,FT817_MODE_FM, 0,ch103_qth},
{ch104_name, 2673500,FT817_MODE_FM, 0,ch104_qth},
{ch105_name, 2674500,FT817_MODE_FM, 0,ch105_qth},
{ch106_name, 2675500,FT817_MODE_FM, 0,ch106_qth},
{ch107_name, 2676500,FT817_MODE_FM, 0,ch107_qth},
{ch108_name, 2677500,FT817_MODE_FM, 0,ch108_qth},
{ch109_name, 2678500,FT817_MODE_FM, 0,ch109_qth},
{ch110_name, 2679500,FT817_MODE_FM, 0,ch110_qth},
{ch111_name, 2680500,FT817_MODE_FM, 0,ch111_qth},
{ch112_name, 2681500,FT817_MODE_FM, 0,ch112_qth},
{ch113_name, 2682500,FT817_MODE_FM, 0,ch113_qth},
{ch114_name, 2683500,FT817_MODE_FM, 0,ch114_qth},
{ch115_name, 2684500,FT817_MODE_FM, 0,ch115_qth},
{ch116_name, 2685500,FT817_MODE_FM, 0,ch116_qth},
{ch117_name, 2686500,FT817_MODE_FM, 0,ch117_qth},
{ch118_name, 2687500,FT817_MODE_FM, 0,ch118_qth},
{ch119_name, 2688500,FT817_MODE_FM, 0,ch119_qth},
{ch120_name, 2689500,FT817_MODE_FM, 0,ch120_qth},
{ch121_name, 2690500,FT817_MODE_FM, 0,ch121_qth},
{ch122_name, 2691500,FT817_MODE_FM, 0,ch122_qth},
{ch123_name, 2692500,FT817_MODE_FM, 0,ch123_qth},
{ch124_name, 2693500,FT817_MODE_FM, 0,ch124_qth},
{ch125_name, 2694500,FT817_MODE_FM, 0,ch125_qth},
{ch126_name, 2695500,FT817_MODE_FM, 0,ch126_qth},
{ch127_name, 502930, NULL , 0,ch127_qth},
{ch128_name, 14521250,FT817_MODE_FM, 0,ch128_qth},
{ch129_name, 14480000,FT817_MODE_FM, 0,ch129_qth},
{ch130_name, 14496250,FT817_MODE_FM, 0,ch130_qth},
{ch131_name, 14497500,FT817_MODE_FM, 0,ch131_qth},
{ch132_name, 14530000, NULL , 0,ch132_qth},
{ch133_name, 14537500, NULL , 0,ch133_qth},
{ch134_name, 14417000, NULL , 0,ch134_qth},
{ch135_name, 14430000, NULL , 0,ch135_qth},
{ch136_name, 14437000, NULL , 0,ch136_qth},
{ch137_name, 14448900, NULL , 0,ch137_qth},
{ch138_name, 14450000, NULL , 0,ch138_qth},
{ch139_name, 14452500, NULL , 0,ch139_qth},
{ch140_name, 14460000, NULL , 0,ch140_qth},
{ch141_name, 14470000, NULL , 0,ch141_qth},
{ch142_name, 14475000, NULL , 0,ch142_qth},
{ch143_name, 43932500,FT817_MODE_FM, -760000,ch143_qth},
{ch144_name, 43905000,FT817_MODE_FM, -760000,ch144_qth},
{ch145_name, 43307500,FT817_MODE_FM, 0,ch145_qth},
{ch146_name, 43310000,FT817_MODE_FM, 0,ch146_qth},
{ch147_name, 43312500,FT817_MODE_FM, 0,ch147_qth},
{ch148_name, 43315000,FT817_MODE_FM, 0,ch148_qth},
{ch149_name, 43317500,FT817_MODE_FM, 0,ch149_qth},
{ch150_name, 43320000,FT817_MODE_FM, 0,ch150_qth},
{ch151_name, 43322500,FT817_MODE_FM, 0,ch151_qth},
{ch152_name, 43325000,FT817_MODE_FM, 0,ch152_qth},
{ch153_name, 43327500,FT817_MODE_FM, 0,ch153_qth},
{ch154_name, 43330000,FT817_MODE_FM, 0,ch154_qth},
{ch155_name, 43332500,FT817_MODE_FM, 0,ch155_qth},
{ch156_name, 43335000,FT817_MODE_FM, 0,ch156_qth},
{ch157_name, 43337500,FT817_MODE_FM, 0,ch157_qth},
{ch158_name, 43340000,FT817_MODE_FM, 0,ch158_qth},
{ch159_name, 43342500,FT817_MODE_FM, 0,ch159_qth},
{ch160_name, 43345000,FT817_MODE_FM, 0,ch160_qth},
{ch161_name, 43347500,FT817_MODE_FM, 0,ch161_qth},
{ch162_name, 43350000,FT817_MODE_FM, 0,ch162_qth},
{ch163_name, 43352500,FT817_MODE_FM, 0,ch163_qth},
{ch164_name, 43355000,FT817_MODE_FM, 0,ch164_qth},
{ch165_name, 43357500,FT817_MODE_FM, 0,ch165_qth},
{ch166_name, 43360000,FT817_MODE_FM, 0,ch166_qth},
{ch167_name, 43362500,FT817_MODE_FM, 0,ch167_qth},
{ch168_name, 43365000,FT817_MODE_FM, 0,ch168_qth},
{ch169_name, 43367500,FT817_MODE_FM, 0,ch169_qth},
{ch170_name, 43370000,FT817_MODE_FM, 0,ch170_qth},
{ch171_name, 43372500,FT817_MODE_FM, 0,ch171_qth},
{ch172_name, 43375000,FT817_MODE_FM, 0,ch172_qth},
{ch173_name, 43377500,FT817_MODE_FM, 0,ch173_qth},
{ch174_name, 43380000,FT817_MODE_FM, 0,ch174_qth},
{ch175_name, 43382500,FT817_MODE_FM, 0,ch175_qth},
{ch176_name, 43385000,FT817_MODE_FM, 0,ch176_qth},
{ch177_name, 43387500,FT817_MODE_FM, 0,ch177_qth},
{ch178_name, 43390000,FT817_MODE_FM, 0,ch178_qth},
{ch179_name, 43392500,FT817_MODE_FM, 0,ch179_qth},
{ch180_name, 43395000,FT817_MODE_FM, 0,ch180_qth},
{ch181_name, 43397500,FT817_MODE_FM, 0,ch181_qth},
{ch182_name, 43400000,FT817_MODE_FM, 0,ch182_qth},
{ch183_name, 43402500,FT817_MODE_FM, 0,ch183_qth},
{ch184_name, 43405000,FT817_MODE_FM, 0,ch184_qth},
{ch185_name, 43407500,FT817_MODE_FM, 0,ch185_qth},
{ch186_name, 43410000,FT817_MODE_FM, 0,ch186_qth},
{ch187_name, 43412500,FT817_MODE_FM, 0,ch187_qth},
{ch188_name, 43415000,FT817_MODE_FM, 0,ch188_qth},
{ch189_name, 43417500,FT817_MODE_FM, 0,ch189_qth},
{ch190_name, 43420000,FT817_MODE_FM, 0,ch190_qth},
{ch191_name, 43422500,FT817_MODE_FM, 0,ch191_qth},
{ch192_name, 43425000,FT817_MODE_FM, 0,ch192_qth},
{ch193_name, 43427500,FT817_MODE_FM, 0,ch193_qth},
{ch194_name, 43430000,FT817_MODE_FM, 0,ch194_qth},
{ch195_name, 43432500,FT817_MODE_FM, 0,ch195_qth},
{ch196_name, 43435000,FT817_MODE_FM, 0,ch196_qth},
{ch197_name, 43437500,FT817_MODE_FM, 0,ch197_qth},
{ch198_name, 43440000,FT817_MODE_FM, 0,ch198_qth},
{ch199_name, 43442500,FT817_MODE_FM, 0,ch199_qth},
{ch200_name, 43445000,FT817_MODE_FM, 0,ch200_qth},
{ch201_name, 43447500,FT817_MODE_FM, 0,ch201_qth},
{ch202_name, 43450000,FT817_MODE_FM, 0,ch202_qth},
{ch203_name, 43452500,FT817_MODE_FM, 0,ch203_qth},
{ch204_name, 43455000,FT817_MODE_FM, 0,ch204_qth},
{ch205_name, 43457500,FT817_MODE_FM, 0,ch205_qth},
{ch206_name, 43460000,FT817_MODE_FM, 0,ch206_qth},
{ch207_name, 43462500,FT817_MODE_FM, 0,ch207_qth},
{ch208_name, 43465000,FT817_MODE_FM, 0,ch208_qth},
{ch209_name, 43467500,FT817_MODE_FM, 0,ch209_qth},
{ch210_name, 43470000,FT817_MODE_FM, 0,ch210_qth},
{ch211_name, 43472500,FT817_MODE_FM, 0,ch211_qth},
{ch212_name, 43475000,FT817_MODE_FM, 0,ch212_qth},
{ch213_name, 43477500,FT817_MODE_FM, 0,ch213_qth},
{ch214_name, 44600620,FT817_MODE_FM, 0,ch214_qth},
{ch215_name, 44601875,FT817_MODE_FM, 0,ch215_qth},
{ch216_name, 44603125,FT817_MODE_FM, 0,ch216_qth},
{ch217_name, 44604375,FT817_MODE_FM, 0,ch217_qth},
{ch218_name, 44605625,FT817_MODE_FM, 0,ch218_qth},
{ch219_name, 44606875,FT817_MODE_FM, 0,ch219_qth},
{ch220_name, 44608125,FT817_MODE_FM, 0,ch220_qth},
};
int nchannels = 221;
