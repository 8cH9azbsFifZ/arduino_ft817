#!/bin/sh
bandplan_path=~/src/amafu/bandplan
cat ~/src/amafu/bandplan/c_structures/t_channels.h |grep -v "gt;"> t_channels.h 
cat ~/src/amafu/bandplan/c_structures/t_repeaters.h |grep -v "gt;"> t_repeaters.h 
cat ~/src/amafu/bandplan/c_structures/ch.txt |grep -v "gt;"> ch.txt

