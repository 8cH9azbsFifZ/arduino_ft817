
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
{"FM Call: Simpl",2961000,FT817_MODE_FM, 0 },
{"QRS",2805500,FT817_MODE_CW_NARROW, 0 },
{"QRP",2806000,FT817_MODE_CW_NARROW, 0 },
{"APRS",2925000,FT817_MODE_FM, 0 },
{"WSPR",2812460, NULL , 0 },
{"41",2656500,FT817_MODE_FM, 0 },
{"42",2657500,FT817_MODE_FM, 0 },
{"43",2658500,FT817_MODE_FM, 0 },
{"44",2659500,FT817_MODE_FM, 0 },
{"45",2660500,FT817_MODE_FM, 0 },
{"46",2661500,FT817_MODE_FM, 0 },
{"47",2662500,FT817_MODE_FM, 0 },
{"48",2663500,FT817_MODE_FM, 0 },
{"49",2664500,FT817_MODE_FM, 0 },
{"50",2665500,FT817_MODE_FM, 0 },
{"51",2666500,FT817_MODE_FM, 0 },
{"52",2667500,FT817_MODE_FM, 0 },
{"53",2668500,FT817_MODE_FM, 0 },
{"54",2669500,FT817_MODE_FM, 0 },
{"55",2670500,FT817_MODE_FM, 0 },
{"56",2671500,FT817_MODE_FM, 0 },
{"57",2672500,FT817_MODE_FM, 0 },
{"58",2673500,FT817_MODE_FM, 0 },
{"59",2674500,FT817_MODE_FM, 0 },
{"60",2675500,FT817_MODE_FM, 0 },
{"61",2676500,FT817_MODE_FM, 0 },
{"62",2677500,FT817_MODE_FM, 0 },
{"63",2678500,FT817_MODE_FM, 0 },
{"64",2679500,FT817_MODE_FM, 0 },
{"65",2680500,FT817_MODE_FM, 0 },
{"66",2681500,FT817_MODE_FM, 0 },
{"67",2682500,FT817_MODE_FM, 0 },
{"68",2683500,FT817_MODE_FM, 0 },
{"69",2684500,FT817_MODE_FM, 0 },
{"70",2685500,FT817_MODE_FM, 0 },
{"71",2686500,FT817_MODE_FM, 0 },
{"72",2687500,FT817_MODE_FM, 0 },
{"73",2688500,FT817_MODE_FM, 0 },
{"74",2689500,FT817_MODE_FM, 0 },
{"75",2690500,FT817_MODE_FM, 0 },
{"76",2691500,FT817_MODE_FM, 0 },
{"77",2692500,FT817_MODE_FM, 0 },
{"78",2693500,FT817_MODE_FM, 0 },
{"79",2694500,FT817_MODE_FM, 0 },
{"80",2695500,FT817_MODE_FM, 0 },
{"WSPR",502930, NULL , 0 },
{"S1: simpl",14521250,FT817_MODE_FM, 0 },
{"ARPS",14480000,FT817_MODE_FM, 0 },
{"Echolink",14496250,FT817_MODE_FM, 0 },
{"Echolink",14497500,FT817_MODE_FM, 0 },
{"RTTY local",14530000, NULL , 0 },
{"DV CQ: Digit",14537500, NULL , 0 },
{"PSK31: MGM P",14417000, NULL , 0 },
{"SSB CQ",14430000, NULL , 0 },
{"MGM CQ",14437000, NULL , 0 },
{"WSPR",14448900, NULL , 0 },
{"SSTV CQ",14450000, NULL , 0 },
{"ATV: ATV S",14452500, NULL , 0 },
{"RTTY CQ",14460000, NULL , 0 },
{"Fax CQ",14470000, NULL , 0 },
{"ATV CQ / Callback",14475000, NULL , 0 },
{"DB0VA",43932500,FT817_MODE_FM, -7600000},
{"DB0ESW",43905000,FT817_MODE_FM, -7600000},
{"1",43307500,FT817_MODE_FM, 0 },
{"2",43310000,FT817_MODE_FM, 0 },
{"3",43312500,FT817_MODE_FM, 0 },
{"4",43315000,FT817_MODE_FM, 0 },
{"5",43317500,FT817_MODE_FM, 0 },
{"6",43320000,FT817_MODE_FM, 0 },
{"7",43322500,FT817_MODE_FM, 0 },
{"8",43325000,FT817_MODE_FM, 0 },
{"9",43327500,FT817_MODE_FM, 0 },
{"10",43330000,FT817_MODE_FM, 0 },

};
int nchannels = sizeof(channels)/sizeof(channels[0]);
						
