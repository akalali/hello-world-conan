## C++ hello-world project using CMake and _Conan install_.

This variant is enabled if the CMake variable `CONAN_CMAKE` is disabled.
Installing the dependencies has to be done before configuring CMake, which is described in the following section.

### Installing dependencies
With the [conanfile.txt](conanfile.txt) we can tell Conan to install the required dependencies and set the correct paths for our project to use.
If you look at the [conanfile.txt](conanfile.txt#L2) you'll see that `poco/1.10.1` is the package recipe that is required for this project to be built.

Since we recommend doing an out-of-source-build you should create a `build-release`-directory next to the `src`-directory and change to this directory
(for more information about different build types and their limitations see [Build types][conan-buildtypes]).
Within this directory you type

```
conan install ..
```

to install the Poco library into your local cache. Note how the transitive dependencies for Poco - OpenSSL and zlib - will be installed, too.
`..` refers to the parent directory so this only works if the command is called from a directory below the `conanfile.txt`.

Using the above mentioned `conanfile.txt` with the `conan-center` will cause an error:

```
ERROR: Missing prebuilt package for 'poco/1.10.1'
Try to build it from sources with "--build poco"
Or read "http://docs.conan.io/en/latest/faq/troubleshooting.html#error-missing-prebuilt-package"
```

That is because our `conanfile.txt` specified some Poco modules to be disabled, which requires a package that is not available in the remote repository.
Following the advise of the error output, you can type

```
conan install .. --build poco
```

Conan will automatically check if the required dependency is already contained in your local cache. So doing this will not download OpenSSL and zlib again.
After checking the local cache Poco will be built with the customized build options. To see if everything worked well, you can type

```
conan search
```

to get an output like this:

```
Existing package recipes:

openssl/1.0.2t
poco/1.10.1
zlib/1.2.11
```

You have now successfully installed the Poco library and its dependencies in your local cache.

### Using packages
If you look into your `build`-directory you will find some files that have been created by Conan:

- conan_paths.cmake
- FindPoco.cmake

The `conan_paths.cmake` is the file that is being used by the project's [CMakeLists.txt](CMakeLists.txt#L33).
It defines all the required variables for CMake to find the installed dependencies.

The `FindPoco.cmake` is a customized `Find<PackageName>.cmake` so that the usual `find_package` can be used, as in [CMakeLists.txt](src/CMakeLists.txt#L2).

Using your favorite way to configure and generate a CMake project will set up your build files so that you can build and run the application using some Poco includes.

[conan-buildtypes]: https://github.com/akalali/hello-world-conan/blob/1.0.0/README.md#build-types
