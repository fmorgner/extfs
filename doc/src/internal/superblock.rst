The Superblock
==============

The **superblock** of an ext2/3/4 file system describes the structure and
configuration of the file system. This information is used by the
implementation to determine the physical and logical structure of the file
system. This section describes the structure of the superblock itself.

Definitions
-----------

All fields described in this section are stored on the disk in little-endian
format, regardless of the system architecture.

.. warning:: The implementation currently only works in little-endian
  architectures. If you would like to get involved in implementing big-endian
  support, please file an issue at the project repository over at
  `Github <https://github.com/fmorgner/extfs>`_

The code in `Implementation`_ makes us of several :code:`using` directives to
reduce the amount of typing as well as make the code more readable. The
following aliases are declared in ``fs/detail/types.hpp``:

.. doxygentypedef:: fs::detail::u32
.. doxygentypedef:: fs::detail::s32
.. doxygentypedef:: fs::detail::u16
.. doxygentypedef:: fs::detail::s16
.. doxygentypedef:: fs::detail::u08
.. doxygentypedef:: fs::detail::u32_arr
.. doxygentypedef:: fs::detail::u08_arr
.. doxygentypedef:: fs::detail::chr_arr

Structure
---------

.. todo:: Describe structure of the superblock

Implementation
--------------

.. doxygenstruct:: fs::detail::extfs_superblock
  :members:
