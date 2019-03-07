<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: google/protobuf/descriptor.proto

namespace Google\Protobuf\Internal;

use Google\Protobuf\Internal\GPBType;
use Google\Protobuf\Internal\GPBWire;
use Google\Protobuf\Internal\RepeatedField;
use Google\Protobuf\Internal\InputStream;

use Google\Protobuf\Internal\GPBUtil;

/**
 * <pre>
 * Describes a method of a service.
 * </pre>
 *
 * Protobuf type <code>google.protobuf.MethodDescriptorProto</code>
 */
class MethodDescriptorProto extends \Google\Protobuf\Internal\Message
{
    /**
     * <code>optional string name = 1;</code>
     */
    private $name = '';
    private $has_name = false;
    /**
     * <pre>
     * Input and output type names.  These are resolved in the same way as
     * FieldDescriptorProto.type_name, but must refer to a message type.
     * </pre>
     *
     * <code>optional string input_type = 2;</code>
     */
    private $input_type = '';
    private $has_input_type = false;
    /**
     * <code>optional string output_type = 3;</code>
     */
    private $output_type = '';
    private $has_output_type = false;
    /**
     * <code>optional .google.protobuf.MethodOptions options = 4;</code>
     */
    private $options = null;
    private $has_options = false;
    /**
     * <pre>
     * Identifies if client streams multiple client messages
     * </pre>
     *
     * <code>optional bool client_streaming = 5 [default = false];</code>
     */
    private $client_streaming = false;
    private $has_client_streaming = false;
    /**
     * <pre>
     * Identifies if server streams multiple server messages
     * </pre>
     *
     * <code>optional bool server_streaming = 6 [default = false];</code>
     */
    private $server_streaming = false;
    private $has_server_streaming = false;

    public function __construct() {
        \GPBMetadata\Google\Protobuf\Internal\Descriptor::initOnce();
        parent::__construct();
    }

    /**
     * <code>optional string name = 1;</code>
     */
    public function getName()
    {
        return $this->name;
    }

    /**
     * <code>optional string name = 1;</code>
     */
    public function setName($var)
    {
        GPBUtil::checkString($var, True);
        $this->name = $var;
        $this->has_name = true;
    }

    public function hasName()
    {
        return $this->has_name;
    }

    /**
     * <pre>
     * Input and output type names.  These are resolved in the same way as
     * FieldDescriptorProto.type_name, but must refer to a message type.
     * </pre>
     *
     * <code>optional string input_type = 2;</code>
     */
    public function getInputType()
    {
        return $this->input_type;
    }

    /**
     * <pre>
     * Input and output type names.  These are resolved in the same way as
     * FieldDescriptorProto.type_name, but must refer to a message type.
     * </pre>
     *
     * <code>optional string input_type = 2;</code>
     */
    public function setInputType($var)
    {
        GPBUtil::checkString($var, True);
        $this->input_type = $var;
        $this->has_input_type = true;
    }

    public function hasInputType()
    {
        return $this->has_input_type;
    }

    /**
     * <code>optional string output_type = 3;</code>
     */
    public function getOutputType()
    {
        return $this->output_type;
    }

    /**
     * <code>optional string output_type = 3;</code>
     */
    public function setOutputType($var)
    {
        GPBUtil::checkString($var, True);
        $this->output_type = $var;
        $this->has_output_type = true;
    }

    public function hasOutputType()
    {
        return $this->has_output_type;
    }

    /**
     * <code>optional .google.protobuf.MethodOptions options = 4;</code>
     */
    public function getOptions()
    {
        return $this->options;
    }

    /**
     * <code>optional .google.protobuf.MethodOptions options = 4;</code>
     */
    public function setOptions(&$var)
    {
        GPBUtil::checkMessage($var, \Google\Protobuf\Internal\MethodOptions::class);
        $this->options = $var;
        $this->has_options = true;
    }

    public function hasOptions()
    {
        return $this->has_options;
    }

    /**
     * <pre>
     * Identifies if client streams multiple client messages
     * </pre>
     *
     * <code>optional bool client_streaming = 5 [default = false];</code>
     */
    public function getClientStreaming()
    {
        return $this->client_streaming;
    }

    /**
     * <pre>
     * Identifies if client streams multiple client messages
     * </pre>
     *
     * <code>optional bool client_streaming = 5 [default = false];</code>
     */
    public function setClientStreaming($var)
    {
        GPBUtil::checkBool($var);
        $this->client_streaming = $var;
        $this->has_client_streaming = true;
    }

    public function hasClientStreaming()
    {
        return $this->has_client_streaming;
    }

    /**
     * <pre>
     * Identifies if server streams multiple server messages
     * </pre>
     *
     * <code>optional bool server_streaming = 6 [default = false];</code>
     */
    public function getServerStreaming()
    {
        return $this->server_streaming;
    }

    /**
     * <pre>
     * Identifies if server streams multiple server messages
     * </pre>
     *
     * <code>optional bool server_streaming = 6 [default = false];</code>
     */
    public function setServerStreaming($var)
    {
        GPBUtil::checkBool($var);
        $this->server_streaming = $var;
        $this->has_server_streaming = true;
    }

    public function hasServerStreaming()
    {
        return $this->has_server_streaming;
    }

}
