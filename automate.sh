#!/bin/bash

# In current terminal tab
git add .
git commit -m "changes"
git push

# Give a little time before switching
sleep 1

# Simulate Ctrl+Page_Down to switch to next tab
xdotool key --clearmodifiers ctrl+Tab

# Small wait to let it switch tabs
sleep 1

# Send git pull and compile.sh commands
xdotool type 'git pull'
xdotool key Return
sleep 1
xdotool type 'sh ./compile.sh'
xdotool key Return
