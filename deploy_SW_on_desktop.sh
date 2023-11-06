#!/bin/bash

# Check if the filename parameter is provided
if [ -z "$1" ]; then
    echo "Usage: bash deploy_SW_on_desktop.sh NAME_OF_FILE"
    exit 1
fi

# Extract the filename from the first parameter
filename="$1"

# Copy the file to the Desktop with the provided filename
cp "build/Nordend" "/home/ert/Desktop/$filename"

# Set executable permission for the copied file
chmod +x "/home/ert/Desktop/$filename"

# Set a custom icon for the file on the Desktop
gio set "/home/ert/Desktop/$filename" 'metadata::custom-icon' file:///home/ert/Firefox_wallpaper.png

# gio info Nordend  # list info on file
