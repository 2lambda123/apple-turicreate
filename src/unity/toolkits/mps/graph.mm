#include <unity/toolkits/mps/graph.h>

#include <unity/toolkits/mps/layers/addition_layer.h>
#include <unity/toolkits/mps/layers/convolution_layer.h>
#include <unity/toolkits/mps/layers/instance_norm_layer.h>
#include <unity/toolkits/mps/layers/average_pooling_layer.h>
#include <unity/toolkits/mps/layers/relu_layer.h>
#include <unity/toolkits/mps/layers/sigmoid_layer.h>
#include <unity/toolkits/mps/layers/nearest_upsampling_layer.h>

namespace turi{
    namespace mps {

        void Graph::add_node(){
            printf("TODO: add node to the current graph");
        }

        void Graph::compile(){
            printf("TODO: compile the graph for forward and backward pass");
        }

        void Graph::clear(){
            printf("TODO: clear the exsisting graph structure");
        }

        void update_weights(){
            printf("TODO: update graph weights");
        }

        void set_trainable_layers(std::map<std::string, bool> trainable){
            
        }

        void Graph::forward(){
            printf("TODO: forward pass");
        }

        void Graph::backward(){
            printf("TODO: backward pass");
        }
    }
}