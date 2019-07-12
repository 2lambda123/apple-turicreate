#import <Accelerate/Accelerate.h>
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#import <MetalPerformanceShaders/MetalPerformanceShaders.h> 

#include <ml/neural_net/style_transfer/mps_style_transfer_utils.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.14))
@interface TCMPSStyleTransferResidualNode : NSObject 

@property (nonatomic) MPSNNImageNode *m_output;

- (instancetype) initWithParameters:(NSString *)name
                          inputNode:(MPSNNImageNode *)inputNode
                             device:(id<MTLDevice>)dev
                          cmd_queue:(id<MTLCommandQueue>)cmd_q
                         descriptor:(TCMPSResidualDescriptor *)descriptor
                        initWeights:(NSDictionary<NSString *, NSData *> *) weights;

- (MPSNNImageNode *) backwardPass:(MPSNNImageNode *) inputNode;

@end

NS_ASSUME_NONNULL_END