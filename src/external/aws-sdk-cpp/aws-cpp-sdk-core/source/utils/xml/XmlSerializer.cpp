/*
  * Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
  *
  * Licensed under the Apache License, Version 2.0 (the "License").
  * You may not use this file except in compliance with the License.
  * A copy of the License is located at
  *
  *  http://aws.amazon.com/apache2.0
  *
  * or in the "license" file accompanying this file. This file is distributed
  * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
  * express or implied. See the License for the specific language governing
  * permissions and limitations under the License.
  */

#include <aws/core/utils/xml/XmlSerializer.h>

#include <aws/core/utils/StringUtils.h>
#include <aws/core/external/tinyxml2/tinyxml2.h>

#include <utility>
#include <algorithm>
#include <iostream>

using namespace Aws::Utils::Xml;
using namespace Aws::Utils;

Aws::String Aws::Utils::Xml::DecodeEscapedXmlText(const Aws::String& textToDecode)
{
    Aws::String decodedString = textToDecode;
    StringUtils::Replace(decodedString, "&quot;", "\"");
    StringUtils::Replace(decodedString, "&apos;", "'");
    StringUtils::Replace(decodedString, "&lt;", "<");
    StringUtils::Replace(decodedString, "&gt;", ">");
    StringUtils::Replace(decodedString, "&amp;", "&");

    return decodedString;
}

XmlNode::XmlNode(const XmlNode& other) : m_node(other.m_node), m_doc(other.m_doc)
{
}

XmlNode& XmlNode::operator=(const XmlNode& other)
{
    if(this == &other)
    {
        return *this;
    }

    m_node = other.m_node;
    m_doc = other.m_doc;

    return *this;
}

const Aws::String XmlNode::GetName() const
{
    return m_node->Value();
}

void XmlNode::SetName(const Aws::String& name)
{
    m_node->SetValue(name.c_str(), false);
}

const Aws::String XmlNode::GetAttributeValue(const Aws::String& name) const
{
	auto pointer =  m_node->ToElement()->Attribute(name.c_str(), nullptr);
	return pointer ? pointer : "";
}

void XmlNode::SetAttributeValue(const Aws::String& name, const Aws::String& value)
{
    m_node->ToElement()->SetAttribute(name.c_str(), value.c_str());
}

bool XmlNode::HasNextNode() const
{
    return m_node->NextSibling() != nullptr;
}

XmlNode XmlNode::NextNode() const
{
    return XmlNode(m_node->NextSiblingElement(), *m_doc);
}

XmlNode XmlNode::NextNode(const char* name) const
{
    return XmlNode(m_node->NextSiblingElement(name), *m_doc);
}

XmlNode XmlNode::NextNode(const Aws::String& name) const
{
    return NextNode(name.c_str());
}

XmlNode XmlNode::FirstChild() const
{
    return XmlNode(m_node->FirstChildElement(), *m_doc);
}

XmlNode XmlNode::FirstChild(const char* name) const
{
    return XmlNode(m_node->FirstChildElement(name), *m_doc);
}

XmlNode XmlNode::FirstChild(const Aws::String& name) const
{
    return FirstChild(name.c_str());
}

bool XmlNode::HasChildren() const
{
    return !m_node->NoChildren();
}

XmlNode XmlNode::Parent() const
{
    return XmlNode(m_node->Parent()->ToElement(), *m_doc);
}

Aws::String XmlNode::GetText() const
{
    if (m_node != nullptr)
    {
        Aws::External::tinyxml2::XMLPrinter printer;
        Aws::External::tinyxml2::XMLNode* node = m_node->FirstChild();
        while (node != nullptr)
        {
            node->Accept(&printer);
            node = node->NextSibling();
        }

        return printer.CStr();
    }

    return {};
}

void XmlNode::SetText(const Aws::String& textValue)
{
    if (m_node != nullptr)
    {
        Aws::External::tinyxml2::XMLText* text = m_doc->m_doc->NewText(textValue.c_str());
        m_node->InsertEndChild(text);
    }
}

XmlNode XmlNode::CreateChildElement(const Aws::String& name)
{
    Aws::External::tinyxml2::XMLElement* element = m_doc->m_doc->NewElement(name.c_str());
    return XmlNode(m_node->InsertEndChild(element), *m_doc);
}

XmlNode XmlNode::CreateSiblingElement(const Aws::String& name)
{
    Aws::External::tinyxml2::XMLElement* element = m_doc->m_doc->NewElement(name.c_str());
    return XmlNode(m_node->Parent()->InsertEndChild(element), *m_doc);
}

bool XmlNode::IsNull()
{
    return m_node == nullptr;
}

static const char* XML_SERIALIZER_ALLOCATION_TAG = "XmlDocument";

XmlDocument::XmlDocument()
{
    m_doc = Aws::New<Aws::External::tinyxml2::XMLDocument>(XML_SERIALIZER_ALLOCATION_TAG, true, Aws::External::tinyxml2::Whitespace::PRESERVE_WHITESPACE);
}

XmlDocument::XmlDocument(XmlDocument&& doc) : m_doc{ doc.m_doc } // take the innards
{
    doc.m_doc = nullptr; // leave nothing behind
}

XmlDocument::~XmlDocument()
{
    Aws::Delete(m_doc);
}

XmlNode XmlDocument::GetRootElement() const
{
    return XmlNode(m_doc->FirstChildElement(), *this);
}

bool XmlDocument::WasParseSuccessful() const
{
    return !m_doc->Error();
}

Aws::String XmlDocument::GetErrorMessage() const
{
    return !WasParseSuccessful() ? m_doc->ErrorName() : "";
}

Aws::String XmlDocument::ConvertToString() const
{
    Aws::External::tinyxml2::XMLPrinter printer;
    printer.PushHeader(false, true);
    m_doc->Accept(&printer);

    return printer.CStr();
}

XmlDocument XmlDocument::CreateFromXmlStream(Aws::IOStream& xmlStream)
{
    Aws::String xmlString((Aws::IStreamBufIterator(xmlStream)), Aws::IStreamBufIterator());
    return CreateFromXmlString(xmlString);
}

XmlDocument XmlDocument::CreateFromXmlString(const Aws::String& xmlText)
{
    XmlDocument xmlDocument;
    xmlDocument.m_doc->Parse(xmlText.c_str(), xmlText.size());
    return xmlDocument;
}

XmlDocument XmlDocument::CreateWithRootNode(const Aws::String& rootNodeName)
{
    XmlDocument xmlDocument;
    Aws::External::tinyxml2::XMLElement* rootNode = xmlDocument.m_doc->NewElement(rootNodeName.c_str());
    xmlDocument.m_doc->LinkEndChild(rootNode);

    return xmlDocument;
}
