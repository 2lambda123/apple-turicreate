/* Copyright © 2019 Apple Inc. All rights reserved.
 *
 * Use of this source code is governed by a BSD-3-clause license that can
 * be found in the LICENSE.txt file or at https://opensource.org/licenses/BSD-3-Clause
 */
#import <JavaScriptCore/JavaScriptCore.h>

@interface JSConsole : NSObject

+ (void)attachToJavaScriptContext:(JSContext *)context;

@end
