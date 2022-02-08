"""
Main build script for Re-Co.

Once the Bootstrap.bat file is run, it will run this file using the python interpreter. 
"""

import os
import sys
import shutil


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


def create_directory(path: str) -> None:
	"""
	Create a directory if possible.

	:param path: The path to create.
	:return: None.
	"""
	try:
		os.makedirs(path)
	except FileExistsError:
		pass


def build_desktop_scipper() -> None:
	"""
	Build the decktop scipper (screen capturing API) library.

	:return: None
	"""


	# Build the screen capture lite library.
	os.system("cd \"Desktop/Scipper/ThirdParty/screen_capture_lite\" && cmake CMakeLists.txt && cmake --build . --config Release --clean-first")
	os.system("cd \"Desktop/Scipper/ThirdParty/screen_capture_lite\" && cmake CMakeLists.txt && cmake --build . --config Debug --clean-first")

	# Make the required build directories (they're made automatically by the compiler but we need it explicitly here because we need to copy paste the 
	# third party binaries there beforehand).
	create_directory("Desktop/Scipper/Builds/Debug")
	create_directory("Desktop/Scipper/Builds/Release")

	# Build premake and the project files.
	if is_on_windows():
		# Copy the screen capture lite dlls to the correct folders.
		shutil.copy("Desktop/Scipper/ThirdParty/screen_capture_lite/Debug/screen_capture_lite_shared.dll", "Desktop/Scipper/Builds/Debug")
		shutil.copy("Desktop/Scipper/ThirdParty/screen_capture_lite/Release/screen_capture_lite_shared.dll", "Desktop/Scipper/Builds/Release")

		os.system("cd \"Desktop/Scipper\" && call \"Tools/Windows/premake5\" vs2022")

	else:
		# Copy the screen capture lite dlls to the correct folders.
		shutil.copy("\"Desktop/Scipper/ThirdParty/screen_capture_lite/Debug/screen_capture_lite_shared.so\"", "\"Desktop/Scipper/Builds/Debug\"")
		shutil.copy("\"Desktop/Scipper/ThirdParty/screen_capture_lite/Release/screen_capture_lite_shared.so\"", "\"Desktop/Scipper/Builds/Release\"")

		os.system("cd \"Desktop/Scipper\" && call \"Tools/Linux/premake5\" gmake2")


if __name__ == "__main__":
	print("Reality Core build script.")

	print_statement("Building Scipper...")
	build_desktop_scipper()
