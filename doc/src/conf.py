#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import sys
import subprocess

subprocess.call('cd ../../ && doxygen', shell=True)

html_theme = 'sphinx_rtd_theme'

extensions = [
    'breathe',
    'sphinx.ext.todo',
]

breathe_projects = {'extfs': os.path.abspath('../../build/xml') }
breathe_default_project = 'extfs'


source_suffix = '.rst'
master_doc = 'index'

project = 'extfs'
copyright = '2016, Felix Morgner'
author = 'Felix Morgner'

version = '1.0.0'
release = '1.0.0'

language = 'en'

exclude_patterns = [
    'build',
    'Thumbs.db',
    '.DS_Store',
    'ext/breathe',
]

pygments_style = 'sphinx'

todo_include_todos = True

htmlhelp_basename = 'extfsdoc'

man_pages = [
    (master_doc, 'extfs', 'extfs Documentation',
     [author], 1)
]

rst_epilog = '.. |project_name| replace:: **%s**' % project

primary_domain = 'cpp'
