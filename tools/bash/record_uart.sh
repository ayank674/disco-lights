#!/usr/bin/env bash

# --- Check admin privileges ---
if [ "$EUID" -ne 0 ]; then
    echo "This script must be run as root (sudo)." 1>&2
    exit 1
fi

# Default values
PORT="/dev/ttyACM0"
BAUD=1843200
DURATION=8
OUTFILE="logs/record.bin"

# Parse flags
while getopts "p:b:d:o:h" opt; do
    case "$opt" in
        p) PORT="$OPTARG" ;;
        b) BAUD="$OPTARG" ;;
        d) DURATION="$OPTARG" ;;
        o) OUTFILE="$OPTARG" ;;
        h)
            echo "Usage: $0 [-p PORT] [-b BAUD] [-d DURATION] [-o OUTFILE]"
            exit 0
            ;;
        *)
            echo "Invalid option. Use -h for help."
            exit 1
            ;;
    esac
done

# Configure serial port
stty -F "$PORT" raw "$BAUD" cs8 -cstopb -parenb -ixon -crtscts

echo "Recording from $PORT at $BAUD baud for $DURATION seconds..."
echo "Output will be saved to $OUTFILE"

# Open Serial Port
exec 3<> "$PORT"

## Sync byte Start
echo -n "STRT" >&3

# Record
timeout "${DURATION}s" cat <&3 > "$OUTFILE"

sleep 0.5

## Sync byte stop
echo -n "STOP" >&3

echo "Recording complete."
FILESIZE=$(stat -c%s "$OUTFILE")
echo "Captured $FILESIZE bytes."

if [ "$DURATION" -gt 0 ]; then
    SAMPLES=$(( FILESIZE / 2 ))
    ACTUAL_SRATE=$(( SAMPLES / DURATION ))
    echo "Actual sampling rate: $ACTUAL_SRATE samples/sec"
fi
