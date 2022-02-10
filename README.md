# Re-Co

Reality Core (Re-Co) for short is a virtual desktop solution which enables users to use mobile phones to interact with the desktop computer rather than investing on expensive dedicated VR gear.

## Team members

| Name                        | Student ID | UoW ID    | IIT Email                   |
| --------------------------- | ---------- | --------- | --------------------------- |
| R. W. D. Samaranayake       | 20200903   | w1838836  | wishal.20200903@iit.ac.lk   |
| R. R. Ganesh                | 2019218    | w1809915  | raahul.2019218@iit.ac.lk    |
| K. G. Ratnajothy            | 20200214   | w18099586 | kanishka.20200214@iit.ac.lk |
| M. S. J. Weerakkody         | 2019573    | w18099225 | sharven.2019573@iit.ac.lk   |
| R. A. J. A. Ranasinghe      | 20200817   | w18379400 | jayali.20200817@iit.ac.lk   |

## How to build

### Windows

When building for Windows, make sure that you have the following dependencies.

1. [Visual Studio 2022](https://visualstudio.microsoft.com/vs/).
2. [CMake](https://cmake.org/).
3. [Python](https://www.python.org/downloads/).
4. [PyCharm IDE](https://www.jetbrains.com/pycharm/).
5. [Android Studio](https://developer.android.com/studio).
6. [Qt Framework](https://www.qt.io/).
7. [Qt Visual Studio Tools](https://doc.qt.io/qtvstools/index.html).

After the above dependencies are configured, clone this repository to a local directory.

```bash
git clone https://github.com/DhirajWishal/Re-Co {SOURCE}
cd {SOURCE}
git submodule init
git submodule update
```

*Here `{SOURCE}` stands for the location where the repository is cloned to.*

Once cloned, change directory to the `{SOURCE}` directory and run the `Bootstrap.bat` file and it will generate the required build tools and will generate the required binaries to run the application.

#### Configuring Qt

It is recommended to install the latest version of Qt. After the installation, make sure to configure the Qt Visual Studio Tools with the proper version. Then you can open the qmake file present within 
`{SOURCE}`/Desktop/Server/GUI` using the Qt VS Tools extension. Thereon, you can easily build the project and run using Visual Studio.

## License

This project is licensed under MIT.
