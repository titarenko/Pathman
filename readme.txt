Pathman.
Copyright (c) Constantin Titarenko (constantin.titarenko@gmail.com), March 5, 2011.

This small 3D game was written as a solution for qualifying round of Extreme Programming Night (http://xpn.com.ua/).

Main character has few lives that can be lost when meeting with enemy.
The goal is to collect all coins and not to lose all lives.

Game controls:

W - move up (forward);
S - move down (back);
A - move left;
D - move right;
Mouse - view angles;
Mouse's wheel - distance from the game board;
Space - pause level;
Escape - abort level.

However, game controls can be customized using game configuration files.

If you are advanced user and you want to customize game (that can be done very easily
since game was designed to be customizable) start from config.xml file
and use technical documentation to figure out parameters' purposes (though all parameters
are enough self-documenting and self-describing). Game assets file (Assets.paf) is a zip 
archive with password "VidIvDiefboiljIlcofs".

See acknowledgements at acknowledgements.txt.

Warning!

If you are developer then you should know that this application uses modified version of Irrlicht 1.7.2! Details can be found at Irrlicht/Changes/readme.txt.

Additional notes.

In order to build application you should:

1) open Pathman.sln in Microsoft Visual C++ 2008 (Express Edition) or above;
2) choose Release build configuration;
3) build solution;
4) pack assets:
	4.1) if you have installed 7-Zip then run PackAssets.bat;
	4.2) otherwise change attribute "Path" of the "assets" element in the config.xml from "Assets.paf" to "./Assets/" (that will instruct Pathman to use unpacked assets).