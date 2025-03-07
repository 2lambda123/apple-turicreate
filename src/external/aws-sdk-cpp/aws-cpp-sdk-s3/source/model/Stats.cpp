﻿/*
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

#include <aws/s3/model/Stats.h>
#include <aws/core/utils/xml/XmlSerializer.h>
#include <aws/core/utils/StringUtils.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h>

#include <utility>

using namespace Aws::Utils::Xml;
using namespace Aws::Utils;

namespace Aws
{
namespace S3
{
namespace Model
{

Stats::Stats() :
    m_bytesScanned(0),
    m_bytesScannedHasBeenSet(false),
    m_bytesProcessed(0),
    m_bytesProcessedHasBeenSet(false),
    m_bytesReturned(0),
    m_bytesReturnedHasBeenSet(false)
{
}

Stats::Stats(const XmlNode& xmlNode) :
    m_bytesScanned(0),
    m_bytesScannedHasBeenSet(false),
    m_bytesProcessed(0),
    m_bytesProcessedHasBeenSet(false),
    m_bytesReturned(0),
    m_bytesReturnedHasBeenSet(false)
{
  *this = xmlNode;
}

Stats& Stats::operator =(const XmlNode& xmlNode)
{
  XmlNode resultNode = xmlNode;

  if(!resultNode.IsNull())
  {
    XmlNode bytesScannedNode = resultNode.FirstChild("BytesScanned");
    if(!bytesScannedNode.IsNull())
    {
      m_bytesScanned = StringUtils::ConvertToInt64(StringUtils::Trim(Aws::Utils::Xml::DecodeEscapedXmlText(bytesScannedNode.GetText()).c_str()).c_str());
      m_bytesScannedHasBeenSet = true;
    }
    XmlNode bytesProcessedNode = resultNode.FirstChild("BytesProcessed");
    if(!bytesProcessedNode.IsNull())
    {
      m_bytesProcessed = StringUtils::ConvertToInt64(StringUtils::Trim(Aws::Utils::Xml::DecodeEscapedXmlText(bytesProcessedNode.GetText()).c_str()).c_str());
      m_bytesProcessedHasBeenSet = true;
    }
    XmlNode bytesReturnedNode = resultNode.FirstChild("BytesReturned");
    if(!bytesReturnedNode.IsNull())
    {
      m_bytesReturned = StringUtils::ConvertToInt64(StringUtils::Trim(Aws::Utils::Xml::DecodeEscapedXmlText(bytesReturnedNode.GetText()).c_str()).c_str());
      m_bytesReturnedHasBeenSet = true;
    }
  }

  return *this;
}

void Stats::AddToNode(XmlNode& parentNode) const
{
  Aws::StringStream ss;
  if(m_bytesScannedHasBeenSet)
  {
   XmlNode bytesScannedNode = parentNode.CreateChildElement("BytesScanned");
   ss << m_bytesScanned;
   bytesScannedNode.SetText(ss.str());
   ss.str("");
  }

  if(m_bytesProcessedHasBeenSet)
  {
   XmlNode bytesProcessedNode = parentNode.CreateChildElement("BytesProcessed");
   ss << m_bytesProcessed;
   bytesProcessedNode.SetText(ss.str());
   ss.str("");
  }

  if(m_bytesReturnedHasBeenSet)
  {
   XmlNode bytesReturnedNode = parentNode.CreateChildElement("BytesReturned");
   ss << m_bytesReturned;
   bytesReturnedNode.SetText(ss.str());
   ss.str("");
  }

}

} // namespace Model
} // namespace S3
} // namespace Aws
