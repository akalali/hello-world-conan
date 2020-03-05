## C++ hello-world project using CMake and _Conan cmake_.

This variant is enabled if the CMake variable `CONAN_CMAKE` is enabled.
Installing the dependencies is done during the configuration-step in CMake, which is described in the following section.

### Installing dependencies
With the [conan_run.cmake](cmake/conan_run.cmake) we can tell Conan to install the required dependencies and set the correct paths for our project to use.
If you look at the [conan_run.cmake](cmake/conan_run.cmake#L10) you'll see that `poco/1.10.1` is the package recipe that is required for this project to be built.

The `conan_run.cmake` is the file that is being used by the project's [CMakeLists.txt](CMakeLists.txt#L27).
It downloads another file - `conan.cmake` - and uses its function [`conan_cmake_run`](cmake/conan_run.cmake#L10) to call Conan.
This will install the required dependencies. The [conan_run.cmake](cmake/conan_run.cmake#L13) additionally defines some customized build options.
These options can be found in [conan_options.cmake](cmake/conan_options.cmake).

Since we recommend doing an out-of-source-build you should create a `build-release`-directory next to the `src`-directory
(for more information about different build types and their limitations see [Build types][conan-buildtypes]).

Using your favorite way to configure and generate a CMake project will set up your build files so that you can build and run the application using some Poco includes.
If you configure your project using CMake, you will get an error, stating that the Conan executable was not found.
You have to set the variable `CONAN_CMD` to your Conan executable (see [Prerequisites - Setting up Conan][conan-setup]).

If your Conan executable was successfully found, you will see Conan installing the Poco library into your local cache. Note how the transitive dependencies for Poco - OpenSSL and zlib - will be installed, too.

### Using packages
If you look into your `build`-directory you will find some files that have been created by Conan:

- conan_paths.cmake
- FindPoco.cmake

The `conan_paths.cmake` is the file that is being used by the project's [CMakeLists.txt](CMakeLists.txt#L33).
It defines all the required variables for CMake to find the installed dependencies.

The `FindPoco.cmake` is a customized `Find<PackageName>.cmake` so that the usual `find_package` can be used, as in [CMakeLists.txt](src/CMakeLists.txt#L2).

Now you can run the application using some Poco includes.

[conan-setup]: https://github.com/akalali/hello-world-conan/blob/1.0.0/README.md#setting-up-conan
[conan-buildtypes]: https://github.com/akalali/hello-world-conan/blob/1.0.0/README.md#build-types
