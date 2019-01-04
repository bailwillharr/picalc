#!/bin/bash
./upload.sh
ssh user@calculator "echo 'started program' && sudo python3 -u picalc/main.py"
