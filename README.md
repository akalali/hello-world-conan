## C++ hello-world project using CMake and Conan.

This simple hello-world project uses [Poco][poco-github] as a third party library. Poco is included in this project via [Conan][conan].

There are two variants of how to use this repository. They are tagged so you can checkout your desired variant:

For the [Conan install variant][conan-install], see [Setting up Conan][conan-install-setup].

For the [Conan cmake variant][conan-cmake], see [Setting up Conan][conan-cmake-setup].

### Setting up Conan
To install conan, see the [Conan documentation][conan-doc]. It is recommended to use a [virtual environment][venv] with python.

After you activated your virtual environment and installed Conan(see [install packages][venv-active]), check if conan is set up correctly by typing `conan`.
Conan should have automatically set up a remote repository, the [Conan center][conan-center]. If you type

```
conan remote list
```

you will get a list of all your remote repositories. For a new install this should be:

```
conan-center: https://conan.bintray.com [Verify SSL: True]
```


If you type 

```
conan search poco
```

you will get the message

```
There are no packages matching the 'poco' pattern
```

which means that no Poco package is found in your local cache.

If you type

```
conan search poco --remote=conan-center
```

you will get an output similar to the following (depending on the remote Poco versions available):

```
Existing package recipes:

poco/1.8.1
poco/1.9.3
poco/1.9.4
poco/1.10.0
poco/1.10.1
```

### Installing dependencies
With the [conanfile.txt](conanfile.txt) we can tell conan to install the required dependencies and set the correct paths for our project to use. If you look at the [conanfile.txt](conanfile.txt#L2) you'll see that `poco/1.10.1` is the package recipe that is required for this project to be built.

Since we recommend doing an out-of-source-build you should create a `build`-directory next to the `src`-directory and change to this directory. Within this directory you type

```
conan install ..
```

to install the Poco library into your local cache. Note how the transitive dependencies for Poco - OpenSSL and zlib - will be installed, too.

Using the above mentioned `conanfile.txt` with the `conan-center` will cause an error:

```
ERROR: Missing prebuilt package for 'poco/1.10.1'
Try to build it from sources with "--build poco"
Or read "http://docs.conan.io/en/latest/faq/troubleshooting.html#error-missing-prebuilt-package"
```

That is because our `conanfile.txt` specified some Poco modules to be disabled, which requires a package that is not available in the remote repository. Following the advise of the error output, you can type

```
conan install .. --build poco
```

Conan will automatically check if the required dependency is already contained in your local cache. So doing this will not download OpenSSL and zlib again. After checking the local cache Poco will be built with the customized build options. To see if everything worked well, you can type

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

You have now succesfully installed the Poco library and its dependencies in your local cache.

### Using packages
If you look into your `build`-directory you will find some files that have been created by Conan:

- conanbuildinfo.cmake
- conanbuildinfo.txt
- conaninfo.txt

The `conanbuildinfo.cmake` is the file that is being used by the project's [CMakeLists.txt](CMakeLists.txt#L19). It defines a funcion [`conan_basic_setup`](CMakeLists.txt#L20) that sets all the required variables for CMake to find the installed dependencies. Especially the variable `CONAN_LIBS` is set, which is used in the [CMakeLists.txt](src/libs/PocoTimer/CMakeLists.txt#L28) of the PocoTimer library, to specify the Poco libraries to use when linking the PocoTimer.

Using your favorite way to configure and generate a CMake project will set up your build files so that you can build and run the application using some Poco includes.

### Installing dependencies
With the [conan.cmake](cmake/conan.cmake) we can tell conan to install the required dependencies and set the correct paths for our project to use. If you look at the [conan.cmake](cmake/conan.cmake#L11) you'll see that `poco/1.10.1` is the package recipe that is required for this project to be built.

The `conan.cmake` is the file that is being used by the project's [CMakeLists.txt](CMakeLists.txt#L20). It downloads another file - `conan.cmake` - and uses its function [`conan_cmake_run`](cmake/conan.cmake#L11) to call Conan. This will install the required dependencies. The [conan.cmake](cmake/conan.cmake#L14) additionally defines some customized build options. These options can be found in [conan_options.cmake](cmake/conan_options.cmake).

If you configure your project using CMake, you will get an error, stating that the Conan executable was not found. You have to set the variable `CONAN_CMD` to your Conan executable (see [anchor](#setting-up-conan)).

If your Conan executable was successfully found, you will see Conan installing the Poco library into your local cache. Note how the transitive dependencies for Poco - OpenSSL and zlib - will be installed, too.

### Using packages
If you look into your `build`-directory you will find some files that have been created by Conan:

- conan_paths.cmake
- FindPoco.cmake

The `conan_paths.cmake` is the file that is being used by the project's [CMakeLists.txt](CMakeLists.txt#L23). It defines all the required variables for CMake to find the installed dependencies.

The `FindPoco.cmake` is a customized `Find<PackageName>.cmake` so that the usual `find_package` can be used, as in [CMakeLists.txt](src/CMakeLists.txt#L2).

Using your favorite way to configure and generate a CMake project will set up your build files so that you can build and run the application using some Poco includes.

### Additional information

#### Profiles

[conan-install]: https://github.com/akalali/hello-world-conan/tree/conan-install-1.0.0
[conan-install-setup]: https://github.com/akalali/hello-world-conan/blob/conan-install-1.0.0/README.md#setting-up-conan
[conan-cmake]: https://github.com/akalali/hello-world-conan/tree/conan-cmake-1.0.0
[conan-cmake-setup]: https://github.com/akalali/hello-world-conan/blob/conan-cmake-1.0.0/README.md#setting-up-conan
[poco-github]: https://github.com/pocoproject/poco
[conan]: https://conan.io/
[conan-doc]: https://docs.conan.io/en/latest/installation.html#install-with-pip-recommended
[venv]: https://docs.python.org/3/library/venv.html
[venv-active]: https://packaging.python.org/guides/installing-using-pip-and-virtual-environments/
[conan-center]: https://conan.io/center/
