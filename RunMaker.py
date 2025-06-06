#!/usr/bin/env python3

import os

# Directory where run.mac files will be written
# Changed directory name to avoid conflicts if you run both scripts
output_dir = "run_mac_files_xy"
os.makedirs(output_dir, exist_ok=True)

# Define the step and range for offsets
step = 1.68
# Values: 10*1.68, 9*1.68, ..., 0, ..., -9*1.68, -10*1.68
# This gives 21 values from 16.80 down to -16.80
offset_values = [i * step for i in range(10, -11, -1)]

file_count = 0

# Loop through all x-offset values
for x_off in offset_values:
    # Loop through all y-offset values
    for y_off in offset_values:
        # Format the offsets with two decimal places
        x_off_str = f"{x_off:.2f}"
        y_off_str = f"{y_off:.2f}"

        # Create a filename like "run_x_16.80_y_16.80.mac", etc.
        # This helps distinguish files based on both x and y offsets
        filename = os.path.join(output_dir, f"run_x_{x_off_str}_y_{y_off_str}.mac")

        with open(filename, "w") as f:
            # Write the three lines, inserting the current x and y offsets
            # The z-offset remains 0.0 mm
            f.write(f"/simulation/offset {x_off_str} {y_off_str} 0.0 mm\n")
            f.write("/run/initialize\n")
            f.write("/run/beamOn 1000\n")

        print(f"  Created {filename}")
        file_count += 1

print(f"\nAll {file_count} run.mac files generated in '{output_dir}'.")