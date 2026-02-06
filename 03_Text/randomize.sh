#!/bin/bash

DELAY=${1:-0.005}

FILE=$(mktemp)


Y=0
 while IFS= read -r LINE; do
    X=0
    for ((i=0; i<${#LINE}; i++)); do
        C="${LINE:i:1}"
        if [[ "$C" != " "  && "$C" != '\t' ]]; then
            echo "$C $Y $X" >> "$FILE"
        fi
        X=$((X + 1))
    done
    Y=$(( Y+1 ))
done

clear
tput cup 0 0

shuf "$FILE" | while read -r C Y X; do
    tput cup $Y $X
    printf "%s" "$C"
    sleep $DELAY
done

rm "$FILE"
tput cup $(( Y+1 )) 0;


