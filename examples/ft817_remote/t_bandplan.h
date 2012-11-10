
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

// Bands configuration
typedef struct
{   
  char *name; // name of the band
  long low;   // lower frequency
  long high;  // upper frequency
  byte mode;  // main mode for this band
} t_band;


// NB: loop the bands backwards. This will make sure, that sets of subregions not covering the whole region
// will work as expected.

const t_band bands[] = {
						{"2200m: CW, QRSS, narrow digital modes",13570,13780,FT817_MODE_CW_NARROW},
{"160m",181000,185000, NULL },
{"160m",185000,189000, NULL },
{"160m",189000,181000, NULL },
{"160m",181000,183800,FT817_MODE_CW_NARROW},
{"160m",183800,184000, NULL },
{"160m: Digimode",184000,184300,FT817_MODE_USB},
{"160m",184300,200000,FT817_MODE_USB},
{"80m: Intercontinental QSO",350000,351000,FT817_MODE_CW_NARROW},
{"80m: Contest",351000,356000,FT817_MODE_CW_NARROW},
{"80m",356000,358000,FT817_MODE_CW_NARROW},
{"80m: small bandwidth digital modes",358000,359000, NULL },
{"80m: small bandwidth digital modes, automatic digital stations",359000,360000, NULL },
{"80m",360000,362000,FT817_MODE_USB},
{"80m: SSB contest",360000,365000,FT817_MODE_USB},
{"80m",365000,370000,FT817_MODE_USB},
{"80m",370000,380000,FT817_MODE_USB},
{"80m: Intercontinental QSO",377500,380000,FT817_MODE_USB},
{"40m",700000,704000,FT817_MODE_CW_NARROW},
{"40m",704000,704700,FT817_MODE_CW_NARROW},
{"40m: automatic stations",704700,705000,FT817_MODE_CW_NARROW},
{"40m: automatic stations",705000,705300,FT817_MODE_USB},
{"40m: digital modes",705300,706000,FT817_MODE_USB},
{"40m: SSB contests",706000,710000,FT817_MODE_USB},
{"40m",710000,713000,FT817_MODE_USB},
{"40m: SSB contests",713000,720000,FT817_MODE_USB},
{"40m: Intercontinental QSO",717500,720000,FT817_MODE_USB},
{"30m",1010000,1014000,FT817_MODE_CW_NARROW},
{"30m: Digimode",1014000,1015000, NULL },
{"20m: Contest",1400000,1406000,FT817_MODE_CW_NARROW},
{"20m",1406000,1407000,FT817_MODE_CW_NARROW},
{"20m: Digimode",1407000,1408900, NULL },
{"20m: Digimode, automatic digital stations",1408900,1409900, NULL },
{"20m: International Beacon-Project, no sending",1409900,1410100, NULL },
{"20m: Digimode, automatic digital stations",1410100,1411200,FT817_MODE_USB},
{"20m",1411200,1412500,FT817_MODE_USB},
{"20m: Contest",1412500,1430000,FT817_MODE_USB},
{"20m",1430000,1435000,FT817_MODE_USB},
{"17m",1806800,1809500,FT817_MODE_CW_NARROW},
{"17m",1809500,1810500, NULL },
{"17m: Automatic stations",1810500,1810900, NULL },
{"17m: International Beacon-Project, no sending",1810900,1811100, NULL },
{"17m: Automatic digital stations",1811100,1812000,FT817_MODE_USB},
{"17m",1812000,1816800,FT817_MODE_USB},
{"15m",2100000,2107000,FT817_MODE_CW_NARROW},
{"15m: Digimode",2107000,2109000, NULL },
{"15m: Digimode, Automatic digital stations",2109000,2111000, NULL },
{"15m: No SSB, Digimode, Automatic digital stations",2111000,2112000,FT817_MODE_USB},
{"15m",2112000,2114900, NULL },
{"15m: Beacons, no sending",2114900,2115100, NULL },
{"15m",2115100,2145000,FT817_MODE_USB},
{"12m",2489000,2491500,FT817_MODE_CW_NARROW},
{"12m",2491500,2492500, NULL },
{"12m: Automatic stations",2492500,2492900, NULL },
{"12m: Beacons, no sending",2492900,2493100, NULL },
{"12m: Digimode, Automatic stations",2493100,2494000,FT817_MODE_USB},
{"12m",2494000,2499000,FT817_MODE_USB},
{"10m",2800000,2807000,FT817_MODE_CW_NARROW},
{"10m",2807000,2812000, NULL },
{"10m: Automatic stations",2812000,2815000, NULL },
{"10m: No SSB",2815000,2819000, NULL },
{"10m: Regional Beacon-Project, no sending",2819000,2819900, NULL },
{"10m: International Beacon-Project, no sending",2819900,2820100, NULL },
{"10m: Beacons, no sending",2820100,2822500, NULL },
{"10m: Beacons",2822500,2830000,FT817_MODE_USB},
{"10m: Automatic digital stations",2830000,2832000,FT817_MODE_USB},
{"10m",2832000,2910000,FT817_MODE_USB},
{"10m: Narrow FM Simples 10 kHz Channels",2910000,2920000,FT817_MODE_USB},
{"10m: Automatic digital modes",2920000,2930000,FT817_MODE_USB},
{"10m",2930000,2951000, NULL },
{"10m: What does this mean?",2951000,2952000, NULL },
{"10m: Narrow FM Relais Input (RH1 - RH8)",2952000,2959000,FT817_MODE_USB},
{"10m: Narrow FM Relais Output (RH1 - RH8)",2962000,2970000,FT817_MODE_USB},
{"6m: Beacon, no sending",500000,500800, NULL },
{"6m",500800,501000,FT817_MODE_CW_NARROW},
{"6m",501000,505000,FT817_MODE_CW_NARROW},
{"6m: Digimode, no allowed in DE",505000,510000, NULL },
{"2m",14400000,14418000,FT817_MODE_CW_NARROW},
{"2m",14418000,14436000,FT817_MODE_CW_NARROW},
{"2m",14436000,14439900,FT817_MODE_CW_NARROW},
{"2m: Beacons, no sending (excl. WSPR)",14440000,14450000, NULL },
{"2m",14450000,14479400,FT817_MODE_USB},
{"2m: MGM, Packet Radio",14480000,14499000, NULL },
{"2m",14499000,14519400,FT817_MODE_FM},
{"2m",14519400,14520600,FT817_MODE_FM},
{"2m",14520600,14559350,FT817_MODE_FM},
{"2m: Relais Output",14559350,14579400,FT817_MODE_FM},
{"2m: Space-Earth",14579400,14580600,FT817_MODE_FM},
{"2m: Satellites",14580600,14600000,FT817_MODE_FM},
{"70cm",43000000,43198100, NULL },
{"70cm",43200000,43210000,FT817_MODE_CW_NARROW},
{"70cm",43210000,43239900,FT817_MODE_CW_NARROW},
{"70cm: Beacons, no sending",43240000,43249000, NULL },
{"70cm",43250000,43299400,FT817_MODE_USB},
{"70cm: ATV",43300000,43500000,FT817_MODE_USB},
{"70cm",43500000,43800000, NULL },
{"70cm",43802500,44000000, NULL },
{"PMR",44600620,44609375,FT817_MODE_FM},
{"PMR: 16 Channels, FSK",44610312.5,44619687.5, NULL },
{"PMR: 8 Channels, FSK",44610625,44619375, NULL },

};
int nbands = sizeof(bands)/sizeof(bands[0]);
						
