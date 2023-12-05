import subprocess

# Define the program name and the output file name
program_name = "./soda"
output_file = "bug.txt"
error_message = "bytes of storage allocated but not freed"

counter = 0
try:
    while True:
        counter += 1
        print(f"{counter}th time...")
        # Run the program and capture the output
        result = subprocess.run(program_name, capture_output=True, text=True, check=True)

        if error_message in result.stderr:
            with open(output_file, 'w') as file:
                file.write(f"Output containing specific error message:\n{result.stdout}\n")
                file.write(f"Error:\n{result.stderr}")
            break
except subprocess.CalledProcessError as e:
    # If an exception occurs, save the output to the file
    with open(output_file, 'w') as file:
        file.write(e.output)
        file.write("\n")
        file.write(e.stderr)

# Notify that the script has completed its task
print("Script completed. The output of the run that caused the exception has been saved to 'bug.txt'.")
