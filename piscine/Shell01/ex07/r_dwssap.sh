#!/bin/sh
cat /etc/passwd | grep -vwE "#" | cut -f1 -d ":"| sed -n "n;p" | rev | sort -r | sed -n "$FT_LINE1","$FT_LINE2"p | tr '\n' ',' | sed 's/, */, /g' | sed 's/\(.*\),/\1./'
