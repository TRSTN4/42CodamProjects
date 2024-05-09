#!/bin/sh
ifconfig -a | grep "ether " | cut -c 8- | tr " " "," | tr -d '\n' | tr "," "\n"
