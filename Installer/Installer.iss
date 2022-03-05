; Reality Core desktop application installer script.

[Setup]
AppName=RealityCore
AppVersion=1.0
WizardStyle=modern
DefaultDirName={autopf}\Reality Core
DefaultGroupName=RealityCore
OutputBaseFilename=RealityCoreInstaller

[Dirs]
Name: "{app}\iconengines"
Name: "{app}\imageformats"
Name: "{app}\platforms"
Name: "{app}\styles"
Name: "{app}\translations"

[Files]
Source: "RealityCore.exe";					DestDir: "{app}"
Source: "screen_capture_lite_shared.dll";	DestDir: "{app}"
Source: "datachannel.dll";					DestDir: "{app}"
Source: "D3Dcompiler_47.dll";               DestDir: "{app}"
Source: "opengl32sw.dll";                   DestDir: "{app}"
Source: "Qt6Core.dll";                      DestDir: "{app}"
Source: "Qt6Gui.dll";                       DestDir: "{app}"
Source: "Qt6Svg.dll";                       DestDir: "{app}"
Source: "Qt6Widgets.dll";                   DestDir: "{app}"
Source: "iconengines\qsvgicon.dll";         DestDir: "{app}\iconengines"
Source: "imageformats\*";                   DestDir: "{app}\imageformats"
Source: "platforms\qwindows.dll";           DestDir: "{app}\platforms"
Source: "styles\qwindowsvistastyle.dll";    DestDir: "{app}\styles"
Source: "translations\*";                   DestDir: "{app}\translations"

[Run]
Filename: {app}\RealityCore.exe; Description: Run Application; Flags: postinstall nowait skipifsilent unchecked