
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

// Single channels
typedef struct 
{
  char *name; // channel name
  long freq;  // frequency (Hz/10)  
  byte mode;  // mode
  long shift;
  char *qth;
} t_channel;


const t_channel channels[] = {
						{"WSPR",13600, NULL ,NULL ,NULL},
	{"WSPR",183660, NULL ,NULL ,NULL},
{"QRP",183600,FT817_MODE_CW_NARROW,NULL ,NULL},
	{"ATV",373500, NULL ,NULL ,NULL},
{"Emergency Region 1",376000, NULL ,NULL ,NULL},
{"QRP",369000, NULL ,NULL ,NULL},
{"Digital Speech",363000, NULL ,NULL ,NULL},
{"QRP",356000,FT817_MODE_CW_NARROW,NULL ,NULL},
{"QRS",355500,FT817_MODE_CW_NARROW,NULL ,NULL},
{"WSPR",359260, NULL ,NULL ,NULL},
	{"QRP",703000,FT817_MODE_CW_NARROW,NULL ,NULL},
{"Emergency Region 1",711000, NULL ,NULL ,NULL},
{"ATV",716500, NULL ,NULL ,NULL},
{"Digital Speech",707000, NULL ,NULL ,NULL},
{"QRP",709000, NULL ,NULL ,NULL},
{"WSPR",703860, NULL ,NULL ,NULL},
	{"QRP",1011600,FT817_MODE_CW_NARROW,NULL ,NULL},
{"WSPR",1013870, NULL ,NULL ,NULL},
	{"QRP",1406000,FT817_MODE_CW_NARROW,NULL ,NULL},
{"Emergency",1430000, NULL ,NULL ,NULL},
{"WSPR",1409560, NULL ,NULL ,NULL},
	{"QRP",1808600,FT817_MODE_CW_NARROW,NULL ,NULL},
{"QRP",1813000, NULL ,NULL ,NULL},
{"Digital Speech",1815000, NULL ,NULL ,NULL},
{"Emergency",1816000, NULL ,NULL ,NULL},
{"WSPR",1810460, NULL ,NULL ,NULL},
	{"QRP",2106000,FT817_MODE_CW_NARROW,NULL ,NULL},
{"QRS",2105500,FT817_MODE_CW_NARROW,NULL ,NULL},
{"Digital Speech",2118000, NULL ,NULL ,NULL},
{"WSPR",2199460, NULL ,NULL ,NULL},
	{"QRP",2490600,FT817_MODE_CW_NARROW,NULL ,NULL},
{"QRP",2495000, NULL ,NULL ,NULL},
{"WSPR",2492460, NULL ,NULL ,NULL},
	{"QRP",2836000, NULL ,NULL ,NULL},
{"Digital Speech",2833000, NULL ,NULL ,NULL},
{"FM Call",2960000,FT817_MODE_FM,NULL ,NULL},
{"FM Call: Simplex Repeater: In",2961000,FT817_MODE_FM,NULL ,NULL},
{"QRS",2805500,FT817_MODE_CW_NARROW,NULL ,NULL},
{"QRP",2806000,FT817_MODE_CW_NARROW,NULL ,NULL},
{"APRS",2925000,FT817_MODE_FM,NULL ,NULL},
{"WSPR",2812460, NULL ,NULL ,NULL},
	{"1: Call FM.",2696500,FT817_MODE_AM,NULL ,NULL},
{"2",2697500,FT817_MODE_AM,NULL ,NULL},
{"3",2698500,FT817_MODE_AM,NULL ,NULL},
{"3A: Not allowed for CB.",2699500, NULL ,NULL ,NULL},
{"4: Call AM.",2700500,FT817_MODE_AM,NULL ,NULL},
{"5",2701500,FT817_MODE_AM,NULL ,NULL},
{"6",2702500,FT817_MODE_AM,NULL ,NULL},
{"7",2703500,FT817_MODE_AM,NULL ,NULL},
{"7A: Not allowed for CB.",2704500, NULL ,NULL ,NULL},
{"8",2705500,FT817_MODE_AM,NULL ,NULL},
{"9: Emergency",2706500,FT817_MODE_AM,NULL ,NULL},
{"10",2707500,FT817_MODE_AM,NULL ,NULL},
{"11",2708500,FT817_MODE_AM,NULL ,NULL},
{"11A: Not allowed for CB.",2709500, NULL ,NULL ,NULL},

	
};
int nchannels = sizeof(channels)/sizeof(channels[0]);
						
