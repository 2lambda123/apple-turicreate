# Copyright (c) 2011 Daniel James
#
# Use, modification and distribution is subject to the Boost Software
# License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

#[foo_py
def foo:
    #=print('foo')
    #<-
    print('bar')
    #->
#]
