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
 * Describes a field within a message.
 * </pre>
 *
 * Protobuf type <code>google.protobuf.FieldDescriptorProto</code>
 */
class FieldDescriptorProto extends \Google\Protobuf\Internal\Message
{
    /**
     * <code>optional string name = 1;</code>
     */
    private $name = '';
    private $has_name = false;
    /**
     * <code>optional int32 number = 3;</code>
     */
    private $number = 0;
    private $has_number = false;
    /**
     * <code>optional .google.protobuf.FieldDescriptorProto.Label label = 4;</code>
     */
    private $label = 0;
    private $has_label = false;
    /**
     * <pre>
     * If type_name is set, this need not be set.  If both this and type_name
     * are set, this must be one of TYPE_ENUM, TYPE_MESSAGE or TYPE_GROUP.
     * </pre>
     *
     * <code>optional .google.protobuf.FieldDescriptorProto.Type type = 5;</code>
     */
    private $type = 0;
    private $has_type = false;
    /**
     * <pre>
     * For message and enum types, this is the name of the type.  If the name
     * starts with a '.', it is fully-qualified.  Otherwise, C++-like scoping
     * rules are used to find the type (i.e. first the nested types within this
     * message are searched, then within the parent, on up to the root
     * namespace).
     * </pre>
     *
     * <code>optional string type_name = 6;</code>
     */
    private $type_name = '';
    private $has_type_name = false;
    /**
     * <pre>
     * For extensions, this is the name of the type being extended.  It is
     * resolved in the same manner as type_name.
     * </pre>
     *
     * <code>optional string extendee = 2;</code>
     */
    private $extendee = '';
    private $has_extendee = false;
    /**
     * <pre>
     * For numeric types, contains the original text representation of the value.
     * For booleans, "true" or "false".
     * For strings, contains the default text contents (not escaped in any way).
     * For bytes, contains the C escaped value.  All bytes &gt;= 128 are escaped.
     * TODO(kenton):  Base-64 encode?
     * </pre>
     *
     * <code>optional string default_value = 7;</code>
     */
    private $default_value = '';
    private $has_default_value = false;
    /**
     * <pre>
     * If set, gives the index of a oneof in the containing type's oneof_decl
     * list.  This field is a member of that oneof.
     * </pre>
     *
     * <code>optional int32 oneof_index = 9;</code>
     */
    private $oneof_index = 0;
    private $has_oneof_index = false;
    /**
     * <pre>
     * JSON name of this field. The value is set by protocol compiler. If the
     * user has set a "json_name" option on this field, that option's value
     * will be used. Otherwise, it's deduced from the field's name by converting
     * it to camelCase.
     * </pre>
     *
     * <code>optional string json_name = 10;</code>
     */
    private $json_name = '';
    private $has_json_name = false;
    /**
     * <code>optional .google.protobuf.FieldOptions options = 8;</code>
     */
    private $options = null;
    private $has_options = false;

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
     * <code>optional int32 number = 3;</code>
     */
    public function getNumber()
    {
        return $this->number;
    }

    /**
     * <code>optional int32 number = 3;</code>
     */
    public function setNumber($var)
    {
        GPBUtil::checkInt32($var);
        $this->number = $var;
        $this->has_number = true;
    }

    public function hasNumber()
    {
        return $this->has_number;
    }

    /**
     * <code>optional .google.protobuf.FieldDescriptorProto.Label label = 4;</code>
     */
    public function getLabel()
    {
        return $this->label;
    }

    /**
     * <code>optional .google.protobuf.FieldDescriptorProto.Label label = 4;</code>
     */
    public function setLabel($var)
    {
        GPBUtil::checkEnum($var, \Google\Protobuf\Internal\FieldDescriptorProto_Label::class);
        $this->label = $var;
        $this->has_label = true;
    }

    public function hasLabel()
    {
        return $this->has_label;
    }

    /**
     * <pre>
     * If type_name is set, this need not be set.  If both this and type_name
     * are set, this must be one of TYPE_ENUM, TYPE_MESSAGE or TYPE_GROUP.
     * </pre>
     *
     * <code>optional .google.protobuf.FieldDescriptorProto.Type type = 5;</code>
     */
    public function getType()
    {
        return $this->type;
    }

    /**
     * <pre>
     * If type_name is set, this need not be set.  If both this and type_name
     * are set, this must be one of TYPE_ENUM, TYPE_MESSAGE or TYPE_GROUP.
     * </pre>
     *
     * <code>optional .google.protobuf.FieldDescriptorProto.Type type = 5;</code>
     */
    public function setType($var)
    {
        GPBUtil::checkEnum($var, \Google\Protobuf\Internal\FieldDescriptorProto_Type::class);
        $this->type = $var;
        $this->has_type = true;
    }

    public function hasType()
    {
        return $this->has_type;
    }

    /**
     * <pre>
     * For message and enum types, this is the name of the type.  If the name
     * starts with a '.', it is fully-qualified.  Otherwise, C++-like scoping
     * rules are used to find the type (i.e. first the nested types within this
     * message are searched, then within the parent, on up to the root
     * namespace).
     * </pre>
     *
     * <code>optional string type_name = 6;</code>
     */
    public function getTypeName()
    {
        return $this->type_name;
    }

    /**
     * <pre>
     * For message and enum types, this is the name of the type.  If the name
     * starts with a '.', it is fully-qualified.  Otherwise, C++-like scoping
     * rules are used to find the type (i.e. first the nested types within this
     * message are searched, then within the parent, on up to the root
     * namespace).
     * </pre>
     *
     * <code>optional string type_name = 6;</code>
     */
    public function setTypeName($var)
    {
        GPBUtil::checkString($var, True);
        $this->type_name = $var;
        $this->has_type_name = true;
    }

    public function hasTypeName()
    {
        return $this->has_type_name;
    }

    /**
     * <pre>
     * For extensions, this is the name of the type being extended.  It is
     * resolved in the same manner as type_name.
     * </pre>
     *
     * <code>optional string extendee = 2;</code>
     */
    public function getExtendee()
    {
        return $this->extendee;
    }

    /**
     * <pre>
     * For extensions, this is the name of the type being extended.  It is
     * resolved in the same manner as type_name.
     * </pre>
     *
     * <code>optional string extendee = 2;</code>
     */
    public function setExtendee($var)
    {
        GPBUtil::checkString($var, True);
        $this->extendee = $var;
        $this->has_extendee = true;
    }

    public function hasExtendee()
    {
        return $this->has_extendee;
    }

    /**
     * <pre>
     * For numeric types, contains the original text representation of the value.
     * For booleans, "true" or "false".
     * For strings, contains the default text contents (not escaped in any way).
     * For bytes, contains the C escaped value.  All bytes &gt;= 128 are escaped.
     * TODO(kenton):  Base-64 encode?
     * </pre>
     *
     * <code>optional string default_value = 7;</code>
     */
    public function getDefaultValue()
    {
        return $this->default_value;
    }

    /**
     * <pre>
     * For numeric types, contains the original text representation of the value.
     * For booleans, "true" or "false".
     * For strings, contains the default text contents (not escaped in any way).
     * For bytes, contains the C escaped value.  All bytes &gt;= 128 are escaped.
     * TODO(kenton):  Base-64 encode?
     * </pre>
     *
     * <code>optional string default_value = 7;</code>
     */
    public function setDefaultValue($var)
    {
        GPBUtil::checkString($var, True);
        $this->default_value = $var;
        $this->has_default_value = true;
    }

    public function hasDefaultValue()
    {
        return $this->has_default_value;
    }

    /**
     * <pre>
     * If set, gives the index of a oneof in the containing type's oneof_decl
     * list.  This field is a member of that oneof.
     * </pre>
     *
     * <code>optional int32 oneof_index = 9;</code>
     */
    public function getOneofIndex()
    {
        return $this->oneof_index;
    }

    /**
     * <pre>
     * If set, gives the index of a oneof in the containing type's oneof_decl
     * list.  This field is a member of that oneof.
     * </pre>
     *
     * <code>optional int32 oneof_index = 9;</code>
     */
    public function setOneofIndex($var)
    {
        GPBUtil::checkInt32($var);
        $this->oneof_index = $var;
        $this->has_oneof_index = true;
    }

    public function hasOneofIndex()
    {
        return $this->has_oneof_index;
    }

    /**
     * <pre>
     * JSON name of this field. The value is set by protocol compiler. If the
     * user has set a "json_name" option on this field, that option's value
     * will be used. Otherwise, it's deduced from the field's name by converting
     * it to camelCase.
     * </pre>
     *
     * <code>optional string json_name = 10;</code>
     */
    public function getJsonName()
    {
        return $this->json_name;
    }

    /**
     * <pre>
     * JSON name of this field. The value is set by protocol compiler. If the
     * user has set a "json_name" option on this field, that option's value
     * will be used. Otherwise, it's deduced from the field's name by converting
     * it to camelCase.
     * </pre>
     *
     * <code>optional string json_name = 10;</code>
     */
    public function setJsonName($var)
    {
        GPBUtil::checkString($var, True);
        $this->json_name = $var;
        $this->has_json_name = true;
    }

    public function hasJsonName()
    {
        return $this->has_json_name;
    }

    /**
     * <code>optional .google.protobuf.FieldOptions options = 8;</code>
     */
    public function getOptions()
    {
        return $this->options;
    }

    /**
     * <code>optional .google.protobuf.FieldOptions options = 8;</code>
     */
    public function setOptions(&$var)
    {
        GPBUtil::checkMessage($var, \Google\Protobuf\Internal\FieldOptions::class);
        $this->options = $var;
        $this->has_options = true;
    }

    public function hasOptions()
    {
        return $this->has_options;
    }

}
