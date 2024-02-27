import os
import sys

def compare_files(file1, file2, chunk_size=4096):
    with open(file1, 'rb') as f1, open(file2, 'rb') as f2:
        while True:
            chunk1 = f1.read(chunk_size)
            chunk2 = f2.read(chunk_size)

            if not chunk1 and not chunk2:
                # Both files reached the end
                return True
            elif chunk1 != chunk2:
                # Files differ
                return False
            
def print_files_in_directory(directory):
    try:
        files = os.listdir(directory)
        for file in files:
            if os.path.isfile(os.path.join(directory, file)):
                print(file)
    except OSError as e:
        print(f"Error: {e}")



def main():
    directory = "./test-bfs-files"
    success_count = 0
    failure_count = 0

    for i in range(1, int(sys.argv[1]) + 1):
        parallel_file = f"{directory}/parallel_{i}.txt"
        serial_file = f"{directory}/serial_{i}.txt"

        if os.path.exists(parallel_file) and os.path.exists(serial_file):
            if compare_files(parallel_file, serial_file):
                success_count += 1
                result = "Success"
            else:
                failure_count += 1
                result = "Failure"

            print(f"Comparison {i}: {result}")

    total_files_checked = success_count + failure_count
    print(f"\nSummary: I checked {total_files_checked} files, successes: {success_count}, failures: {failure_count}")

if __name__ == "__main__":
    main()
