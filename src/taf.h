/* metar.c -- metar/taf decoder
   $Id: taf.h,v 1.0 2021/08/15 13:32:00 yannickmcosta Exp $
   Copyright 2004,2005 Kees Leune <kees@leune.org>
   Copyright 2021 Yannick McCabe-Costa <yannick@mccabecosta.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* max size for a URL */
#define  URL_MAXSIZE 300

/* max size for a NOAA report */
#define  TAF_MAXSIZE 512

/* where to fetch reports */
#define  TAFURL "https://tgftp.nws.noaa.gov/data/forecasts/taf/stations"

/* clouds */
typedef struct {
	char type[3];
	int  level;
} cloud_t;

/* linked list of clouds */
typedef struct cloudlist_el {
	cloud_t *cloud;
	struct cloudlist_el *next;
} cloudlist_t;

/* linked list of clouds */
typedef struct obslist_el {
	char *obs;
	struct obslist_el *next;
} obslist_t;

/* reports will be translated to this struct */
typedef struct {
	char station[10];
	int  day;
	int  time;
	int  winddir;  // winddir == -1 signifies variable winds
	int  windstr;
	int  windgust;
	char windunit[5];
	int  vis;
	char visunit[5];
	int  qnh;
	char qnhunit[5];
	int  qnhfp;	// fixed-point decimal places
	int  temp;
	int  dewp;
	cloudlist_t *clouds;
	obslist_t *obs;
} taf_t;

typedef struct {
	char date[36];
	char report[1024];
} noaa_t;

/* Parse the METAR contain in the report string. Place the parsed report in
 * the metar struct.
 */
void parse_Taf(char *report, taf_t *taf);

/* parse the NOAA report contained in the noaa_data buffer. Place a parsed
 * data in the metar struct. 
 */
void parse_NOAA_data(char *noaa_data, noaa_t *noaa);  
