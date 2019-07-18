/* Copyright © 2018 Apple Inc. All rights reserved.
 *
 * Use of this source code is governed by a BSD-3-clause license that can
 * be found in the LICENSE.txt file or at https://opensource.org/licenses/BSD-3-Clause
 */

#import <Accelerate/Accelerate.h>
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#import <MetalPerformanceShaders/MetalPerformanceShaders.h> 

#import <ml/neural_net/mps_descriptor_utils.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.14))
@interface TCMPSStyleTransfer : NSObject

@property (nonatomic) NSUInteger batch_size;
@property (nonatomic) NSNumber *content_loss_multiplier;
@property (nonatomic) NSNumber *style_loss_multiplier;
@property (nonatomic) BOOL finetune_all_params;
@property (nonatomic) BOOL pretrained_weights;

- (instancetype) initWithParameters:(NSDictionary<NSString *, NSData *> *)weights;

- (NSDictionary<NSString *, NSData *> *)exportWeights;
- (NSDictionary<NSString *, NSData *> *)predict:(NSDictionary<NSString *, NSData *> *)inputs;
- (void) setLearningRate:(NSNumber *) lr;
- (NSDictionary<NSString *, NSData *> *) train:(NSDictionary<NSString *, NSData *> *)inputs;

@end

NS_ASSUME_NONNULL_END