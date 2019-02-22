# -*- coding: utf-8 -*-
# Copyright © 2019 Apple Inc. All rights reserved.
#
# Use of this source code is governed by a BSD-3-clause license that can
# be found in the LICENSE.txt file or at https://opensource.org/licenses/BSD-3-Clause
import unittest
import sys


class MXNetImportTest(unittest.TestCase):

    def test_mxnet_import(self):

        self.assertTrue("mxnet" not in sys.modules)

        import turicreate

        self.assertTrue("mxnet" not in sys.modules)
