#!/bin/bash

watch 'cat /proc/net/snmp | grep Tcp | rev | column -t | rev'
