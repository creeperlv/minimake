# minimake

minimake is a simple make system that works across various platforms such as: Windows, Linux and MS-DOS(with DJGPP).

# Requirements

- A GCC compiler.

- A POSIX compatible shell, such as `ash` or `bash`.

- mkcproj

It is recommended to use w64devkit on Windows for the author use it to build this tool.

# Build

Run `scripts/build.sh`.

# Install

By default, the script `scripts/install.sh` will copy built file to /bin/.

Please make sure that output folder is in your `PATH`.

# Usage

## Build A Project

! Before building a project, you must configure the project first.

By running `minimake build` or `minimake make`, minimake will try to run `script/build.sh`.

## Create a project

Run `minimake new` to start a new project guide.

You can use -n and -v to specify name and version to skip the guide.

## Configure the project.

If a directory contains `minimake.mkp`, minimake will try to use `mkcproj` to generate the project layout and scripts.

If local configuration exists, values in local configuration will be used instead of the default one.

## Local Config

Use `minimake nlconfig` command to generate a new local configuration file.

In this file, you can modify default C compiler, output path and install path.

# Develop

This project is developed with `micro`, `micro-plugin-lsp` and `clangd`!

# License

The MIT License
