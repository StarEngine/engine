# Freetype 2 Android

This is simply a distribution of the Freetype 2 library, that includes Android make files ready to build the Freetype 2 library into a static and shared binaries for version 2.2 of the Android operating system.  This distribution requires release 5 of the Android Native Development Kit.

The project only includes the Freetype modules for processing TrueType and OpenType fonts.  Other font modules have been disabled.  If you want to re-enable these modules, you will need to download the Freetype 2 source code, and then copy the module source files to the appropriate location in either the "include/" or "src/" folders of this distribution.  The Freetype source code is [available here](http://download.savannah.gnu.org/releases/freetype/).  The instructions for including these new modules in the Android makefile is left as an exercise, but if you follow the pattern of the truetype module in the Android makefile, your module should compile correctly.

The code in this distribution comes from version 2.4.4 of the Freetype library.   

There is an analogous library for Xcode and iOS [here](https://github.com/cdave1/freetype2-ios).


# Install

This distribution requires release 5 of the Android Native Development Kit.

To build, cd to the Android/jni/ directory and type ndk-build.

The file Android/jni/Application.mk contains the target and platform settings used by ndk-build.  The current settings are:

    APP_ABI := armeabi armeabi-v7a
    APP_PLATFORM := android-8

To use the library in another ndk library, you will need to include the Android/jni/module.mk file in the Android.mk of the library you want to use freetype with.


# License

This code is distributed under the terms of the [Freetype License](http://www.freetype.org/FTL.TXT).  The Freetype License is also included in this distribution.  If you are going to use code in this project, please make sure you follow the instructions in the Freetype License.