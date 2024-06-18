#!/bin/bash

# Directory containing the maps
MAP_DIR="map_files/invalid"

# Result file
VALRESULT="Valgrind_Result.txt"
> "$VALRESULT"

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Temporary file for individual valgrind results
TEMPRESULT="Valgrind_Temp_Result.txt"

# Function to test a map with Valgrind
test_map() {
    local map_file="$1"
    local map_basename="${map_file##*/}"

    valgrind --leak-check=full ./cub3D "$map_file" &> "$TEMPRESULT"
    VALGRIND_EXIT_STATUS=$?

    if [ $VALGRIND_EXIT_STATUS -ne 0 ]; then
        if [ $VALGRIND_EXIT_STATUS -eq 134 ]; then
            printf "${RED}[KO] Map: $map_basename (Abort)${NC}\n"
            echo "Error with map: $map_basename (Abort)" >> "$VALRESULT"
        elif [ $VALGRIND_EXIT_STATUS -eq 139 ]; then
            printf "${RED}[KO] Map: $map_basename (Segmentation fault)${NC}\n"
            echo "Error with map: $map_basename (Segmentation fault)" >> "$VALRESULT"
        else
            printf "${RED}[KO] Map: $map_basename (Valgrind exit status: $VALGRIND_EXIT_STATUS)${NC}\n"
            echo "Error with map: $map_basename (Valgrind exit status: $VALGRIND_EXIT_STATUS)" >> "$VALRESULT"
        fi
        echo "Valgrind output:" >> "$VALRESULT"
        cat "$TEMPRESULT" >> "$VALRESULT"
        echo -e "\n" >> "$VALRESULT"
    else
        PRID=$(expr ${#BASHPID} + 6)
        RESULT=$(grep "All heap blocks were freed" "$TEMPRESULT" | cut -b $PRID-61)
        if [ "$RESULT" == "All heap blocks were freed -- no leaks are possible" ]; then
            printf "${GREEN}[OK] Map: $map_basename${NC}\n"
        else
            printf "${RED}[KO] Map: $map_basename${NC}\n"
            echo "Error with map: $map_basename" >> "$VALRESULT"
            echo "Valgrind output:" >> "$VALRESULT"
            cat "$TEMPRESULT" >> "$VALRESULT"
            echo -e "\n" >> "$VALRESULT"
        fi
    fi

    # Clean up the temporary result file for the next iteration
    > "$TEMPRESULT"
}

# Main loop to run each map
for i in {0..9}; do
    map_file="$MAP_DIR/map${i}.cub"
    if [ -f "$map_file" ]; then
        test_map "$map_file"
    else
        echo "Map file not found: $map_file"
    fi
done

# Clean up the temporary result file
rm -f "$TEMPRESULT"

exit 0
