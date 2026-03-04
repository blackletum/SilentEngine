"""
Silent Engine Launcher

Runs a Silent Engine launcher which prompts ROM selection and launches the application.
"""

import os
import platform
import subprocess
import sys
import tkinter

from pathlib import Path
from tkinter import filedialog, messagebox

DUMPSXISO_NAME = "dumpsxiso"
BASE_PATH      = getattr(sys, '_MEIPASS', os.path.abspath("."))
DUMPSXISO_PATH = BASE_PATH / DUMPSXISO_NAME

#sudo apt install python3-tk

#`ExtractAssets.py;`` and `dumpsxiso;` on Windows. Needs a semicolon!

#pyinstaller --onefile --windowed --noconfirm \
#--add-data "../../Tools/ExtractAssets.py:." \
#--add-binary "../../Tools/dumpsxiso/Linux/dumpsxiso:." \
#--distpath "/Build/Launcher" \
#--workpath "/Build/Launcher/temp" \
#--specpath "/Build/Launcher" \
#Tools/Launcher.py && \
#rm -rf Build/Launcher/temp Build/Launcher/Launcher.spec

def generate_launcher():
    """
    Generate platform-specific Silent Engine launcher executable.
    If a generated launcher executable already exist and is outdated, it will be overwritten.
    """
    # @todo

def get_dumpsxiso_exe():
    """
    Get the platform-specific `dumpsxiso` executable to use.
    """

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

    if system_os in ["darwin", "linux"]:
        os.chmod(dumpsxiso_exe, 0o755)

    return dumpsxiso_exe

# Create window object.
root = tkinter.Tk()
root.title("Silent Engine Launcher")
root.geometry("400x200")

# Add simple label.
label = tkinter.Label(root, text="Hello, Silent Engine!")
label.pack(expand=True)

# Run window.
root.mainloop()
