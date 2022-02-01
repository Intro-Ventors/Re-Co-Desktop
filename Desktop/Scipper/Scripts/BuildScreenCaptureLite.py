"""
Build script to build the screen capture lite library depending on the argument passed (Debug or Release).
"""

import os
import sys


if sys.argv[1] == "Debug":
	os.system("cd \"ThirdParty/screen_capture_lite\" && cmake CMakeLists.txt && cmake --build . --config Debug --clean-first")
else:
	os.system("cd \"ThirdParty/screen_capture_lite\" && cmake CMakeLists.txt && cmake --build . --config Release --clean-first")
