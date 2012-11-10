#!/bin/sh
bandplan_path=~/src/amafu/bandplan
xsltproc $bandplan_path/tools/ft817_bandplan.xsl $bandplan_path/bandplans/bandplan.xml > t_bandplan.h
xsltproc $bandplan_path/tools/ft817_channels.xsl $bandplan_path/bandplans/bandplan.xml|grep -v "26"|grep -v WSPR|grep -v TV> t_channels.h
