arraydump
=========

`arraydump` is a utility to create hexdumps in different forms, suitable for
comsumption by a C/C++ compiler. The tool is inspired by the well-known `xxd`
utility which is part of `vim`. We created `arraydump` to overcome some
weaknesses of `xxd`.

Advantages of arraydump over xxd
--------------------------------

`arraydump` provides the following advantages over `xxd`:

1. Element type selection:
   `arraydump` allows you to specify the element-type of the array that will be
   generated. The currently supported types are ``std::int8_t`` (via `--type
   int8`), ``std::uint8_t`` (via `--type uint8`), ``char`` (via `--type char`),
   ``signed char`` (via `--type schar`), and ``unsigned char`` (via `--type
   uchar`).

2. Use ``std::array<T, S>`` instead of C-Style arrays:
   Since ``xxd`` was designed to work for **C** projects, it makes use of plain,
   old, C-Style arrays. ``arraydump`` has been designed for **C++** projects,
   and one of the decisions made during development was to use modern facilities
   in order to promote usage modern **C++**.

3. Support for processing multiple files at once:
   `arraydump` allows you to transform multiple files at once. You can specify a
   list of files and a directory for the generated files (via `--output <dir>`).
   This makes it easy and fast to transform a lot of files at once without
   having to resort to shell scripting magic.

Disadvantages of arraydump compared to xxd
------------------------------------------

Of course we live and work in an engineering world, and (almost) no tool comes
with advantages alone. The folloing issues need to be considered when using
`arraydump`.

1. Young project:
   `arraydump` is a very young tool. Because of this, it has not seen a lot of
   use outside the `extfs` project. This means that there are probably bugs that
   have not yet surfaced and might cause wrong output to be produced. If you
   find any bugs, please do not hessitate to report them, or even better create
   a pull request.

2. Written in Python:
   In contrast to `xxd`, which is written in **C**, `arraydump` is written in
   **Python**. There is nothing inherently bad about this, it just means that you
   will need a **Python 3** compatible interpreter on your system to use
   `arraydump`. You will need to keep that in mind if you, for example, use the
   tool in your `CI` setup. Additionally, being written in an interpreted
   language, `arraydump` will probably use more resources for processing than
   `xxd`.

3. Only **C++** header files can be generated: `xxd` provides several different
   output formats as well as different modes of operation. `arraydump`, on the
   other hand, was specifically designed to produce **C++** header files. That
   is all it can do.

Usage
-----

The output of `arraydump -h` is pretty self-explanatory

.. code-block:: text

  usage: arraydump [-h] [--output dir] [--columns cols] [--extension ext]
                   [--type {int8,uint8,char,schar,uchar}]
                   file [file ...]

  Convert binaries to C++ headers

  positional arguments:
    file                  The input file to process

  optional arguments:
    -h, --help            show this help message and exit
    --output dir          The target directory for the generated file(s)
    --columns cols        The number of columns in the output
    --extension ext       The file extension for the generated header
    --type {int8,uint8,char,schar,uchar}
                          The array element type
