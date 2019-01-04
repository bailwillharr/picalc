#!/bin/bash
ssh user@calculator "cd picalc/ && git pull"
ssh user@calculator "sudo python3 -u picalc/main.py"
