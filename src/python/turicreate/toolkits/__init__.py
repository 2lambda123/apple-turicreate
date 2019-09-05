# -*- coding: utf-8 -*-
# Copyright © 2017 Apple Inc. All rights reserved.
#
# Use of this source code is governed by a BSD-3-clause license that can
# be found in the LICENSE.txt file or at https://opensource.org/licenses/BSD-3-Clause

'''
Turi Create offers a broad set of essential machine learning models as well as
task specific toolkits that let you to get started quickly while still giving you the
ability to go back and customize models later.
'''

from turicreate._deps import LazyModuleLoader as _LazyModuleLoader

_mod_par = 'turicreate.toolkits.'

# okay, this is a hack
_feature_engineering = _LazyModuleLoader(_mod_par + '_feature_engineering')