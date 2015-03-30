# README #

This is a QuickBase API wrapper for use in C++ code. It is still quite rough, but functional. You will want to reference the QuickBase API documentation for details on the API calls other than what exists in the wrapper header file. [Quickbase API Site](http://www.quickbase.com/api-guide/index.html)

### Setup ###

#### Pre-Reqs ####

You will need to build and install the proper libcurl library for your machine and place the .lib in time-clock\custom_libraries\lib_dbg. Everything else is self-contained.

#### VS Setup Data ####
In your linker settings, make sure Additional Library Directories is set to "custom_libraries\lib_dbg"
Also make sure Additional Dependencies includes "libcurld.lib".
Finally, add CURL_STATICLIB to your Preprocessor Definitions.

### Contribution guidelines ###


### Who do I talk to? ###

* Repo owner or admin (Josiah Bruner)