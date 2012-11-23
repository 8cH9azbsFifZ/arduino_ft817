
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
  long freq;  // frequency
  byte mode;  // mode
  long rpt;   // repeater shift
} t_channel;

const t_channel channels[] = {
						{"WSPR",13600, NULL , 0 },
	{"WSPR",183660, NULL , 0 },
{"QRP",183600,FT817_MODE_CW_NARROW, 0 },
	{"ATV",373500, NULL , 0 },
{"Emergency Region 1",376000, NULL , 0 },
{"QRP",369000, NULL , 0 },
{"Digital Speech",363000, NULL , 0 },
{"QRP",356000,FT817_MODE_CW_NARROW, 0 },
{"QRS",355500,FT817_MODE_CW_NARROW, 0 },
{"WSPR",359260, NULL , 0 },
	{"QRP",703000,FT817_MODE_CW_NARROW, 0 },
{"Emergency Region 1",711000, NULL , 0 },
{"ATV",716500, NULL , 0 },
{"Digital Speech",707000, NULL , 0 },
{"QRP",709000, NULL , 0 },
{"WSPR",703860, NULL , 0 },
	{"QRP",1011600,FT817_MODE_CW_NARROW, 0 },
{"WSPR",1013870, NULL , 0 },
	{"QRP",1406000,FT817_MODE_CW_NARROW, 0 },
{"Emergency",1430000, NULL , 0 },
{"WSPR",1409560, NULL , 0 },
	{"QRP",1808600,FT817_MODE_CW_NARROW, 0 },
{"QRP",1813000, NULL , 0 },
{"Digital Speech",1815000, NULL , 0 },
{"Emergency",1816000, NULL , 0 },
{"WSPR",1810460, NULL , 0 },
	{"QRP",2106000,FT817_MODE_CW_NARROW, 0 },
{"QRS",2105500,FT817_MODE_CW_NARROW, 0 },
{"Digital Speech",2118000, NULL , 0 },
{"WSPR",2199460, NULL , 0 },
	{"QRP",2490600,FT817_MODE_CW_NARROW, 0 },
{"QRP",2495000, NULL , 0 },
{"WSPR",2492460, NULL , 0 },
	{"QRP",2836000, NULL , 0 },
{"Digital Speech",2833000, NULL , 0 },
{"FM Call",2960000,FT817_MODE_FM, 0 },
{"FM Call: Simplex Repeater: In",2961000,FT817_MODE_FM, 0 },
{"QRS",2805500,FT817_MODE_CW_NARROW, 0 },
{"QRP",2806000,FT817_MODE_CW_NARROW, 0 },
{"APRS",2925000,FT817_MODE_FM, 0 },
{"WSPR",2812460, NULL , 0 },
{"1: Call FM.",2696500, NULL , 0 },
{"2",2697500, NULL , 0 },
{"3",2698500, NULL , 0 },
{"3A: Not allowed for CB.",2699500, NULL , 0 },
{"4: Call AM.",2700500, NULL , 0 },
{"5",2701500, NULL , 0 },
{"6",2702500, NULL , 0 },
{"7",2703500, NULL , 0 },
{"7A: Not allowed for CB.",2704500, NULL , 0 },
{"8",2705500, NULL , 0 },
{"9: Emergency",2706500, NULL , 0 },
{"10",2707500, NULL , 0 },
{"11",2708500, NULL , 0 },
{"11A: Not allowed for CB.",2709500, NULL , 0 },
{"12",2710500, NULL , 0 },
{"13",2711500,FT817_MODE_FM, 0 },
{"14",2712500,FT817_MODE_FM, 0 },
{"15",2713500,FT817_MODE_FM, 0 },
{"15A: Not allowed for CB.",2715500, NULL , 0 },
{"16",2715500,FT817_MODE_FM, 0 },
{"17",2716500,FT817_MODE_FM, 0 },
{"18",2717500,FT817_MODE_FM, 0 },
{"19",2718500,FT817_MODE_FM, 0 },
{"19A: Not allowed for CB.",2719500, NULL , 0 },
{"WSPR",502930, NULL , 0 },
{"S1: simplex channel",14521250,FT817_MODE_FM, 0 },
{"ARPS",14480000,FT817_MODE_FM, 0 },
{"Echolink",14496250,FT817_MODE_FM, 0 },
{"Echolink",14497500,FT817_MODE_FM, 0 },
{"DV CQ: Digital Speech with ",14537500, NULL , 0 },
{"PSK31: MGM PSK31",14417000, NULL , 0 },
{"SSB CQ",14430000, NULL , 0 },
{"WSPR",14448900, NULL , 0 },
{"1",43307500,FT817_MODE_FM, 0 },
{"2",43310000,FT817_MODE_FM, 0 },
{"3",43312500,FT817_MODE_FM, 0 },
{"4",43315000,FT817_MODE_FM, 0 },
{"1",44600620,FT817_MODE_FM, 0 },
{"2",44601875,FT817_MODE_FM, 0 },
{"3",44603125,FT817_MODE_FM, 0 },
{"4",44604375,FT817_MODE_FM, 0 },
{"5",44605625,FT817_MODE_FM, 0 },
{"6",44606875,FT817_MODE_FM, 0 },
{"7",44608125,FT817_MODE_FM, 0 },
{"8",44609375,FT817_MODE_FM, 0 },
	
};
int nchannels = sizeof(channels)/sizeof(channels[0]);
						
