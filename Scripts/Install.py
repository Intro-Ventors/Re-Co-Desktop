"""
Installer script to install the application. For now, this only supports Windows.
"""

import os
import shutil


if __name__ == "__main__":
    print("Reality Core installer script v1.0")
    print("Make sure that the application is built using the release mode and the executable is available at RealityCore/release.")

    # Get the Qt SDK directory.
    qt_directory = input("Please enter the path to the Qt SDK (ie: \"C:\\SDKs\\Qt6\\6.2.3\\msvc2019_64\"): ")
    qt_dependency_generator = qt_directory + "\\bin\\windeployqt.exe"

    # Copy the generated executable from the release directory to the exporting directory.
    shutil.copy("RealityCore\\release\\RealityCore.exe", "Installer")

    # Run the Qt dependency scanner.
    os.system(f"cd \"Installer\" && call {qt_dependency_generator} RealityCore.exe")

    # Finally, compile the Inno script
    os.system("cd \"Installer\" && call \"..\\Tools\\Windows\\InnoSetup\\ISCC\" Installer.iss")
