# README #

This is a QuickBase API wrapper for use in C++ code. It is still quite rough, but functional. You will want to reference the QuickBase API documentation for details on the API calls other than what exists in the wrapper header file. [Quickbase API Site](http://www.quickbase.com/api-guide/index.html)

### Setup ###

#### Pre-Reqs ####

You will need to build and install the proper libcurl library for your machine and place the .lib in time-clock\custom_libraries\lib_dbg. Everything else is self-contained.

#### VS Setup Data ####
In your linker settings, make sure Additional Library Directories is set to "custom_libraries\lib_dbg"
Also make sure Additional Dependencies includes "libcurld.lib".
Finally, add CURL_STATICLIB to your Preprocessor Definitions.

#### Integrating into your project ####
Integration is unfortunately semi-difficult due to its many library dependencies. For example, if you are integrating to an MFC application, the Use of MFC must be set to "Use MFC in a shared DLL". Statically linking won't work because the libraries are DLL-built. libcurld is not. You could build your own libcurld and children, if you want a statically linked binary.

Integration is not done through a .lib, simply because I hate using them. Instead, simply copy all source files (except main.cpp), the UTF-8 directory, and custom_libraries directory and place them into your application's source (I recommend placing everything in a folder so you don't become overwhelmed). Doing so comes with the added benefit of being able to modify the API if you so desire.

Note: If you modify something that you feel would be beneficial to more than just yourself, please create a issue and attach a patch!

### Contribution guidelines ###


### Who do I talk to? ###

* Repo owner or admin (Josiah Bruner)