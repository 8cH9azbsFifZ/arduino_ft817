
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
						{"2200m",13570,13780, NULL },
{"2200m: CW, QRSS, narrow digital modes",13570,13780, NULL },
{"160m",181000,185000, NULL },
{"160m",181000,183800, NULL },
{"160m",183800,184000, NULL },
{"160m: Digimode",184000,184300, NULL },
{"160m",184300,185000, NULL },
{"160m",185000,189000, NULL },
{"160m",185000,189000, NULL },
{"160m",189000,181000, NULL },
{"160m",189000,200000, NULL },
{"80m",350000,358000, NULL },
{"80m: Intercontinental QSO",350000,351000, NULL },
{"80m: Contest",351000,356000, NULL },
{"80m",356000,358000, NULL },
{"80m: small bandwidth digital modes",358000,359000, NULL },
{"80m: small bandwidth digital modes, automatic digital stations",359000,360000, NULL },
{"80m",360000,362000, NULL },
{"80m: SSB contest",360000,365000, NULL },
{"80m",365000,370000, NULL },
{"80m",370000,380000, NULL },
{"80m: Intercontinental QSO",377500,380000, NULL },
{"40m",700000,704000, NULL },
{"40m",700000,704000, NULL },
{"40m",704000,704700, NULL },
{"40m: automatic stations",704700,705000, NULL },
{"40m: automatic stations",705000,705300, NULL },
{"40m: digital modes",705300,706000, NULL },
{"40m: SSB contests",706000,710000, NULL },
{"40m",710000,720000, NULL },
{"40m",710000,713000, NULL },
{"40m: SSB contests",713000,720000, NULL },
{"40m: Intercontinental QSO",717500,720000, NULL },
{"30m",1010000,1015000, NULL },
{"30m",1010000,1014000, NULL },
{"30m: Digimode",1014000,1015000, NULL },
{"20m",1400000,1435000, NULL },
{"20m: Contest",1400000,1406000, NULL },
{"20m",1406000,1407000, NULL },
{"20m: Digimode",1407000,1408900, NULL },
{"20m: Digimode, automatic digital stations",1408900,1409900, NULL },
{"20m: International Beacon-Project, no sending",1409900,1410100, NULL },
{"20m: Digimode, automatic digital stations",1410100,1411200, NULL },
{"20m",1411200,1412500, NULL },
{"20m: Contest",1412500,1430000, NULL },
{"20m",1430000,1435000, NULL },
{"17m",1806800,1816800, NULL },
{"17m",1806800,1809500, NULL },
{"17m",1809500,1810500, NULL },
{"17m: Automatic stations",1810500,1810900, NULL },
{"17m: International Beacon-Project, no sending",1810900,1811100, NULL },
{"17m: Automatic digital stations",1811100,1812000, NULL },
{"17m",1812000,1816800, NULL },
{"15m",2100000,2107000, NULL },
{"15m",2100000,2107000, NULL },
{"15m: Digimode",2107000,2109000, NULL },
{"15m: Digimode, Automatic digital stations",2109000,2111000, NULL },
{"15m: No SSB, Digimode, Automatic digital stations",2111000,2112000, NULL },
{"15m",2112000,2114900, NULL },
{"15m: Beacons, no sending",2114900,2115100, NULL },
{"15m",2115100,2145000, NULL },
{"12m",2489000,2499000, NULL },
{"12m",2489000,2491500, NULL },
{"12m",2491500,2492500, NULL },
{"12m: Automatic stations",2492500,2492900, NULL },
{"12m: Beacons, no sending",2492900,2493100, NULL },
{"12m: Digimode, Automatic stations",2493100,2494000, NULL },
{"12m",2494000,2499000, NULL },
{"10m",2800000,2807000, NULL },
{"10m",2800000,2807000, NULL },
{"10m",2807000,2812000, NULL },
{"10m: Automatic stations",2812000,2815000, NULL },
{"10m: No SSB",2815000,2819000, NULL },
{"10m: Regional Beacon-Project, no sending",2819000,2819900, NULL },
{"10m: International Beacon-Project, no sending",2819900,2820100, NULL },
{"10m: Beacons, no sending",2820100,2822500, NULL },
{"10m: Beacons",2822500,2830000, NULL },
{"10m: Automatic digital stations",2830000,2832000, NULL },
{"10m",2832000,2910000, NULL },
{"10m: Narrow FM Simples 10 kHz Channels",2910000,2920000, NULL },
{"10m: Automatic digital modes",2920000,2930000, NULL },
{"10m",2930000,2951000, NULL },
{"10m: Safty Channel",2951000,2952000, NULL },
{"10m: Narrow FM Relais Input (RH1 - RH8)",2952000,2959000, NULL },
{"10m: Narrow FM Relais Output (RH1 - RH8)",2962000,2970000, NULL },
{"CB",2656500,2740500, NULL },
{"6m: Beacon, no sending",500000,500800, NULL },
{"6m",500800,510000, NULL },
{"6m",500800,501000, NULL },
{"6m",501000,505000, NULL },
{"6m: Digimode, no allowed in DE",505000,510000, NULL },
{"2m",14400000,14600000, NULL },
{"2m",14400000,14418000, NULL },
{"2m: EME CW and Random MS Freq.",14400000,14411000, NULL },
{"2m: EME MGM",14411000,14414000, NULL },
{"2m: EME CW",14414000,14416000, NULL },
{"2m",14418000,14436000, NULL },
{"2m: SSB",14418000,14436000, NULL },
{"2m",14436000,14439900, NULL },
{"2m: Beacons, no sending (excl. WSPR)",14440000,14450000, NULL },
{"2m",14450000,14479400, NULL },
{"2m: Lineartransponder Output",14463000,14466000, NULL },
{"2m: Lineartransponder Output",14466000,14469000, NULL },
{"2m: MGM, Packet Radio",14480000,14499000, NULL },
{"2m: Digimode, automatic stations",14480000,14498750, NULL },
{"2m",14499000,14519400, NULL },
{"2m: Relais Input",14500000,14518750, NULL },
{"2m",14519400,14520600, NULL },
{"2m",14520600,14559350, NULL },
{"2m: Relais Output",14559350,14579400, NULL },
{"2m: Space-Earth",14579400,14580600, NULL },
{"2m: Satellites",14580600,14600000, NULL },
{"70cm",43000000,44000000, NULL },
{"70cm",43000000,43198100, NULL },
{"70cm: Echolink",43002500,43005000, NULL },
{"70cm: NBFM / DV Simplex U 003-028",43007500,43035000, NULL },
{"70cm: DVR RU30 - RU31",43037500,43038750, NULL },
{"70cm: PR Duplex Input, +9.4MHz shift, 25 kHz width, RU 784 - RU 798",43040000,43057500, NULL },
{"70cm: PR Simplex, Digipeater, 25 kHz width, U048 - U050",43060000,43067500, NULL },
{"70cm: PR Duplex, +7.6MHz shift, 25 kHz width, RU 664- (RU)682",43070000,43092500, NULL },
{"70cm: NBFM Relais Input, +7.6 MHz shift, 12.5 kHz width, RU 684 - RU 690",43095000,43182500, NULL },
{"70cm: DV (RX) 12.6 kHz width, TX +7.6 MHz shift",43185000,43198750, NULL },
{"70cm",43200000,43210000, NULL },
{"70cm",43210000,43239900, NULL },
{"70cm: Beacons, no sending",43240000,43249000, NULL },
{"70cm",43250000,43299400, NULL },
{"70cm: ATV",43300000,43500000, NULL },
{"70cm",43500000,43800000, NULL },
{"70cm",43802500,44000000, NULL },
{"LPD",43307500,43479000, NULL },
{"PMR",44600620,44609375, NULL },
{"PMR: 16 Channels, FSK",44610312.5,44619687.5, NULL },
{"PMR: 8 Channels, FSK",44610625,44619375, NULL },

};
int nbands = sizeof(bands)/sizeof(bands[0]);
						
