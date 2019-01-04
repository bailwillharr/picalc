#!/bin/bash
echo "please wait..."
rsync -r --delete-before . user@calculator:~/picalc/
