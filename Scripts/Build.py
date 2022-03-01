"""
Main build script for Re-Co-Desktop.

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


def build_desktop() -> None:
	"""
	Build the desktop application.

	:return: None
	"""

	# Build the screen capture lite library.
	os.system(
		'cd "RealityCore/ThirdParty/screen_capture_lite" && cmake CMakeLists.txt && cmake --build . --config Release --clean-first'
	)
	os.system(
		'cd "RealityCore/ThirdParty/screen_capture_lite" && cmake CMakeLists.txt && cmake --build . --config Debug --clean-first'
	)

	# Get the dependencies for libdatachannel.
	os.system(
		'cd "RealityCore/ThirdParty/libdatachannel/" && git submodule update --init --recursive --depth 1'
	)
	print(
		"Please read the BUILD.md file of the libdatachannel library and build it manually. (https://github.com/paullouisageneau/libdatachannel/blob/master/BUILDING.md)"
	)


if __name__ == "__main__":
	print("Reality Core build script.")

	print_statement("Building Desktop...")
	build_desktop()
