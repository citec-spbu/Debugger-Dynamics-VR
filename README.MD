# Requirements
## Boost library
## wxWidgets library 

# Start Debugger
In the “config.txt” file you must specify the paths to the input and output files.
After this we can start the debugger.
If we have problems starting the debugger, look for the error in the "log.txt" file.
## Config:
Example: 
```
InputFILE=C:\...\in.txt 
OutputFILE=C:\...\out.txt
```
## Dll files
## Debugger use a two dll files 
```
wxbase32ud_gcc_custom.dll 
wxmsw32ud_core_gcc_custom.dll
```
You can add them to the "libs" folder or add the path to these dlls to the system paths.