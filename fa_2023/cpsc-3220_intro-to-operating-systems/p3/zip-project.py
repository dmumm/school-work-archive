import os
import zipfile
import sys
from pathlib import Path

# Set the current working directory as a constant
CURRENT_DIRECTORY = Path.cwd()

# List of filenames you want to zip
fixed_file_names = [
    "allocator.c",
    "allocator.h",
    "free_list.c",
    "free_list.h",
    "page_list.c",
    "page_list.h",
    "page.c",
    "page.h",
    "project3.pdf",
]  # Add your file names here

additional_file_names = sys.argv[
    1:
]  # This will get all arguments after the script name

file_names = list(dict.fromkeys(fixed_file_names + additional_file_names))

# Destination zip file path
zip_file_name = "p3_dmumm_source.zip"
zip_file_path = CURRENT_DIRECTORY / zip_file_name

# Track processed files to detect duplicates
processed_files = set()

# Create a zip file
with zipfile.ZipFile(zip_file_path, "w") as zipf:
    for file_name in file_names:
        normalized_file_name = file_name.strip('"')

        # Check if the file has already been processed
        if normalized_file_name in processed_files:
            print(
                f"Warning: Duplicate file '{normalized_file_name}' detected and will not be added again."
            )
            continue
        file_path = CURRENT_DIRECTORY / normalized_file_name
        if file_path.exists():
            zipf.write(file_path, arcname=normalized_file_name)
            print(f"{normalized_file_name} added to archive.")
        else:
            print(
                f"{normalized_file_name} does not exist and was not added to archive."
            )

print(f"Zipping process completed saved at {zip_file_path}")
