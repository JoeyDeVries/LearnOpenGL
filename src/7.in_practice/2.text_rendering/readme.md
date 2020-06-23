Here are the steps needed to get the text_rendering example to work.  

We will use Visual Studio 2019 in Windows 10.

Let's assume you have already successfully built all of the example projects from github.

uncomment line 167 '2.text_rendering' in CMakeLists.txt

rerun cmake

Open solution and change target from Debug to Release, with default of x64, and build just the project '7.in_practice__2.text_rendering'

"Error	C1083	Cannot open include file: 'ft2build.h': No such file or directory	7.in_practice__2.text_rendering"

You now have a working project for the text_rendering example.  It failed due to the missing Freetype2 header.

Time to get Freetype2.

Go to https://www.freetype.org/

Click on 'Download' to open https://www.freetype.org/download.html

Download the latest Stable Release, from either mirror, a file such as 'freetype-2.10.2.tar.gz'

Use a program like '7zip' to extract the tar file from the gz file.

Extract the folder 'freetype-2.10.2' from the tar file, again using 7zip.

Navigate to freetype-2.10.2\builds\windows and make a copy of the 'vc2010' folder, renaming the folder to 'vs2019' or whatever you prefer for a name.

Open 'freetype.sln' with VS 2019.  Change to 'Release' and 'x64' for a target.

In Solution Explorer, select the project 'freetype' and right mouse click for a menu, then select 'Properties'.  Under 'General', change 'Configuration Type' from dll to 'Static library (.lib)'.

Rebuild the project, and you should see that 'freetype.lib' was created.  Note that we want a 64 bit library.

Copy 'freetype.lib' into the learnopengl 'lib' folder.

Copy the contents of 'freetype-2.10.2\include' into the learnopengl 'includes' folder.

Now, try again to build the project '7.in_practice__2.text_rendering'

You will get linking errors this time, such as "bin\7.in_practice\Release\7.in_practice__2.text_rendering.exe : fatal error LNK1120: 6 unresolved externals"

To fix the linking errors, we have to add 'freetype.lib' to the project.  The best way to add the library is to edit CMakeLists.txt again, this time, on line 3, add freetype to the 'set (LIBS...' entry list. It should look like this 'set(LIBS glfw3 opengl32 assimp freetype)' 

Rerun cmake.

Build the project '7.in_practice__2.text_rendering' again, this time it should succeed and will create '7.in_practice__2.text_rendering.exe' under the 'bin' folder.

Double click on the .exe file, it will start and then immediately close.  If you want to see what error messages may or may not have been printed, open a command prompt and run the .exe again.

In the command prompt window, you will see the error message 'ERROR::FREETYPE: Failed to load font'.  So the program is working, it is looking for a font named 'arial.ttf' in a folder named 'fonts' under the .exe directory.  Let's add the folder and copy 'arial.ttf' from 'C:/Windows/Fonts' into the 'fonts' subfolder.  

This time, double click on the .exe and you will see a window stating 'This is sample text' and '(C) LearnOpenGL.com'

All done.









