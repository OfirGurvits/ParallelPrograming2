#!/bin/bash

parallel_path="./part_III.out"
serial_path="./slowBFS/slowBFS.out"

if [ ! -e "$parallel_path" ]; then
  echo "$parallel_path does not exist. can't run tests, please compile your parallel program"
  exit 1
fi
if [ ! -e "$serial_path" ]; then
  echo "$serial_path does not exist. can't run tests, please follow the steps in explanation attached"
  exit 1
fi

library_name="networkx"

if ! pip show "$library_name" >/dev/null 2>&1; then
  echo "$library_name is not installed. can't run tests, please install the library using 'pip install networkx'"
  exit 1
fi

echo "How many tests? (default: 10): "  
read testAmount  
# Check if the input is empty
if [ -z "$testAmount" ]; then
  # Set default value
  testAmount=10
fi

echo "What is the minimum amount of nodes? (default: 50): "  
read minNodes  
# Check if the input is empty
if [ -z "$minNodes" ]; then
  # Set default value
  minNodes=50
fi

echo "What is the maximum amount of nodes? (default: 100): "  
read maxNodes  
# Check if the input is empty
if [ -z "$maxNodes" ]; then
  # Set default value
  maxNodes=100
fi


directory="test-bfs-files"

# Navigate to the directory
cd "$directory" || exit

# Delete all files ending with ".txt"
rm -f *.txt

echo "Removed Old files from $directory."

cd ../

# Run the loop for 100 iterations
for ((i=1; i<=$testAmount; i++)); do
    # Run the Python script with output redirection
    python3 test-bfs-files/createGraphs.py $minNodes $maxNodes > "test-bfs-files/graph_${i}.txt"
done
echo "Finished generating new test cases."

printf "\rRunning tests, progress: 0%%"

timingString=""

for ((i=1; i<=$testAmount; i++)); do
    time_a=$( { time ./part_III.out < "test-bfs-files/graph_${i}.txt" > "test-bfs-files/parallel_${i}.txt"; } 2>&1 | grep real | awk '{print $2}' )

    time_b=$( { time ./slowBFS/slowBFS.out < "test-bfs-files/graph_${i}.txt" > "test-bfs-files/serial_${i}.txt"; } 2>&1 | grep real | awk '{print $2}' )
    # Calculate progress percentage
    progress=$((i * 100 / testAmount))

    # Print the loading bar
    printf "\rRunning tests, progress: %d%%" "$progress"

    # Print the results
    timingString+="Graph $i: time for parallel: $time_a, time for serial: $time_b\n"
done
printf "\rFinished running tests.\n"
echo -e "\n$timingString"


python3 ./test-bfs-files/checkResults.py $testAmount
