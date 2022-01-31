"""
Main build script for Re-Co.

Once the Bootstrap.bat file is run, it will run this file using the python interpreter. 
"""

import os
import sys


def is_on_windows() -> bool:
	"""
	Check if the current platform is windows.

	:return: Boolean value stating if its on windows or not.
	"""
	return sys.platform.startswith("win32")


def print_statement(message: str) -> None:
	"""
	Print a statement to the console.

	:param message: The message to be printed.
	:return: None.
	"""
	print("=========================", message, "=========================")


def build_desktop_scipper() -> None:
	"""
	Build the decktop scipper (screen capturing API) library.

	:return: None
	"""

	# Build premake.
	if is_on_windows():
		os.system("cd \"Desktop/Scipper/ThirdParty/premake-core-5.0.0\" && call Bootstrap.bat")
	else:
		os.system("cd \"Desktop/Scipper/ThirdParty/premake-core-5.0.0\" && call make")

	# Build the screen capture lite library.
	os.system("cd \"Desktop/Scipper/ThirdParty/screen_capture_lite\" && cmake CMakeLists.txt && cmake --build . --config Release")

	# Generate the project files or makefiles depending on the platform.
	if is_on_windows():
		os.system("cd \"Desktop/Scipper\" && call \"ThirdParty/premake-core-5.0.0/bin/release/premake5\" vs2022")
	else:
		os.system("cd \"Desktop/Scipper\" && call \"ThirdParty/premake-core-5.0.0/bin/release/premake5\" gmake2")



if __name__ == "__main__":
	print("Reality Core build script.")

	print_statement("Building Scipper...")
	build_desktop_scipper()
