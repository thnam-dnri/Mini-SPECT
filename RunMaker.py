#!/usr/bin/env python3

import os

# Directory to store output macro files
output_dir = "run_mac_files_xy"
os.makedirs(output_dir, exist_ok=True)

# 1) XY scan: −8.40 mm to +8.40 mm in 1.68 mm steps
xy_step = 1.68
xy_range = [i * xy_step for i in range(-5, 6)]  # 11 values: [−8.40, −6.72, …, 0.00, …, +6.72, +8.40]

# 2) Z‐offset scan: from −50 mm to +50 mm in 10 mm steps
#    (since phantom’s “base” Z is +200 mm, this yields final Z = 150 → 250 mm)
z_offsets = [i * 10.0 for i in range(-5, 6)]  # [−50, −40, −30, −20, −10, 0, +10, +20, +30, +40, +50]

file_count = 0

for x_off in xy_range:
    for y_off in xy_range:
        for z_off in z_offsets:
            x_str = f"{x_off:.2f}"
            y_str = f"{y_off:.2f}"
            z_str = f"{z_off:.1f}"

            # Filename encodes X, Y, and Z‐offset (in mm)
            filename = os.path.join(
                output_dir,
                f"run_x_{x_str}_y_{y_str}_zoff_{z_str}.mac"
            )

            with open(filename, "w") as f:
                # This command adds (x_off, y_off, z_off) to the phantom’s default (0,0,200 mm)
                f.write(f"/simulation/offset {x_str} {y_str} {z_str} mm\n")
                f.write("/run/initialize\n")
                f.write("/run/beamOn 100000\n")

            print(f"  Created {filename}")
            file_count += 1

print(f"\nAll {file_count} run.mac files generated in '{output_dir}'.")