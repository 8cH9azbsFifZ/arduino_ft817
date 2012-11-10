#!/bin/sh
bandplan_path=~/src/amafu/bandplan
xsltproc $bandplan_path/tools/ft817_bandplan.xsl $bandplan_path/bandplans/bandplan.xml > t_bandplan.h
xsltproc $bandplan_path/tools/ft817_channels.xsl $bandplan_path/bandplans/bandplan.xml > t_channels.h
