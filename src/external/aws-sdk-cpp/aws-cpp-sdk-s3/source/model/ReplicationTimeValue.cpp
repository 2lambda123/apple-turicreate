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

#include <aws/s3/model/ReplicationTimeValue.h>
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

ReplicationTimeValue::ReplicationTimeValue() :
    m_minutes(0),
    m_minutesHasBeenSet(false)
{
}

ReplicationTimeValue::ReplicationTimeValue(const XmlNode& xmlNode) :
    m_minutes(0),
    m_minutesHasBeenSet(false)
{
  *this = xmlNode;
}

ReplicationTimeValue& ReplicationTimeValue::operator =(const XmlNode& xmlNode)
{
  XmlNode resultNode = xmlNode;

  if(!resultNode.IsNull())
  {
    XmlNode minutesNode = resultNode.FirstChild("Minutes");
    if(!minutesNode.IsNull())
    {
      m_minutes = StringUtils::ConvertToInt32(StringUtils::Trim(Aws::Utils::Xml::DecodeEscapedXmlText(minutesNode.GetText()).c_str()).c_str());
      m_minutesHasBeenSet = true;
    }
  }

  return *this;
}

void ReplicationTimeValue::AddToNode(XmlNode& parentNode) const
{
  Aws::StringStream ss;
  if(m_minutesHasBeenSet)
  {
   XmlNode minutesNode = parentNode.CreateChildElement("Minutes");
   ss << m_minutes;
   minutesNode.SetText(ss.str());
   ss.str("");
  }

}

} // namespace Model
} // namespace S3
} // namespace Aws
