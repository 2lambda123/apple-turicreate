# -*- coding: utf-8 -*-
# Copyright © 2020 Apple Inc. All rights reserved.
#
# Use of this source code is governed by a BSD-3-clause license that can
# be found in the LICENSE.txt file or at https://opensource.org/licenses/BSD-3-Clause
from __future__ import print_function as _  # noqa
from __future__ import division as _  # noqa
from __future__ import absolute_import as _  # noqa
import logging as _logging
import sys
import six
from turicreate import __version__

# value can be set to True by build pipeline
USE_MINIMAL = False


def is_minimal_pkg():
    return USE_MINIMAL


if six.PY2:
    import imp
else:
    import importlib


def run_from_ipython():
    # Taken from https://stackoverflow.com/questions/5376837
    try:
        __IPYTHON__
        return True
    except NameError:
        return False


def run_from_python_interpreter():
    return bool(getattr(sys, "ps1", sys.flags.interactive))


IS_INTERACTIVE = run_from_python_interpreter() or run_from_ipython()


def is_py_interactive():
    return IS_INTERACTIVE


if six.PY2:
    # reentrant lock: https://docs.python.org/2/library/imp.html#imp.acquire_lock
    class _ImportLockContext:
        def __enter__(self):
            imp.acquire_lock()

        def __exit__(self, exc_type, exc_value, exc_traceback):
            imp.release_lock()


else:
    # importlib uses _imp internally; check source you will know ;-)
    from importlib._bootstrap import _ImportLockContext


def minimal_package_import_check(name):
    """
    only support `import ...`, no `from ... import` or `import ... as`
    """
    with _ImportLockContext():
        _ret = sys.modules.get(name, None)

    if _ret is not None:
        return _ret

    try:
        if six.PY2:
            # imp importing submodule is too tricky
            # moulde and pkg naming should follow pep8
            if not all([x.isalnum() or x in "._" for x in name]):
                raise ValueError("invalid module name")
            exec("import %s as __mpkg_ret" % name)
            # import a.b.c will register name as a.b.c
            return __mpkg_ret  # pylint: disable=undefined-variable
        else:
            return importlib.import_module(name)
    except ImportError as e:
        if USE_MINIMAL:
            # e.g., tesorflow.compat.v1 should report tensorflow
            if "." in name:
                name = name.split(".")[0]

            # append more information
            e.msg = (
                "{}. This is a minimal package for SFrame only, without {} pinned"
                " as a dependency. You can try install all required packages by installing"
                "full package by:\n"
                "pip install turicreate=={}"
            ).format(e.msg, name, __version__)

        raise e
