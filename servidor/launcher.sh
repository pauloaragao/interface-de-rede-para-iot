#!/bin/sh
# launcher.sh

sleep 60

cd /
cd home/pi
sudo python3 MQTTInfluxDBBridge.py
cd /
