"""
Silent Engine Launcher

Runs a simple launcher which prompts ROM selection for asset extraction and launches the application.
"""

import ctypes
import customtkinter
import os
import platform
import subprocess
import sys

from pathlib       import Path
from customtkinter import filedialog

DUMPSXISO_NAME = "dumpsxiso"
BASE_PATH      = Path(getattr(sys, '_MEIPASS', os.path.abspath(".")))
DUMPSXISO_PATH = BASE_PATH / DUMPSXISO_NAME

def _get_dumpsxiso_exe():
    """
    Get the platform-specific `dumpsxiso` executable to use.
    """
    # Define executable path.
    system_os = platform.system().lower()
    if system_os == "windows":
        dumpsxiso_exe = os.path.join(DUMPSXISO_PATH, "Windows", DUMPSXISO_NAME + ".exe")
    elif system_os == "darwin": # macOS
        dumpsxiso_exe = os.path.join(DUMPSXISO_PATH, "macOS", DUMPSXISO_NAME)
    elif system_os == "linux":
        dumpsxiso_exe = os.path.join(DUMPSXISO_PATH, "Linux", DUMPSXISO_NAME)
    else:
        raise Exception(f"'{system_os}' is unsupported.")

    if not os.path.isfile(dumpsxiso_exe):
        raise Exception(f"`{DUMPSXISO_NAME}` executable not found at '{dumpsxiso_exe}'.")

    # Set permissions.
    if system_os in ["darwin", "linux"]:
        os.chmod(dumpsxiso_exe, 0o755)

    return dumpsxiso_exe

def _select_rom_file():
    file_path = filedialog.askopenfilename(
        title="Select a Silent Hill ROM",
        filetypes=[("Silent Hill ROM Image", "*.BIN")])
    
    if file_path:
        print(f"Selected: {file_path}")
        return file_path

    return None

def main():
    WIDTH  = 400
    HEIGHT = 500

    customtkinter.set_appearance_mode("System")

    # Create window object.
    root = customtkinter.CTk()
    root.title("Silent Engine Launcher")
    root.geometry(f"{WIDTH}x{HEIGHT}")

    # Add simple label.
    label = customtkinter.CTkLabel(root, text="Hello, world!")
    label.pack(expand=True)

    def handle_click():
        romPath = _select_rom_file()
        if romPath:
            label.configure(text=f"Path: ...{romPath[-30:]}") # Show truncated path.

    button = customtkinter.CTkButton(root, text="Browse Files", command=handle_click)
    button.pack(expand=True)

    # Run window.
    root.mainloop()

if __name__ == "__main__":
    main()
