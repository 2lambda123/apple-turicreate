/*
 * Copyright 2010-2018 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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
#pragma once

#include <aws/core/client/CoreErrors.h>
#include <aws/core/Core_EXPORTS.h>

namespace Aws
{
    namespace Utils
    {
        namespace Event
        {
            /**
             * Errors encountered in event stream.
             * These errors are associated with those in aws-c-event-stream library.
             */
            enum class EventStreamErrors
            {
                EVENT_STREAM_NO_ERROR = 0,
                EVENT_STREAM_BUFFER_LENGTH_MISMATCH = 0x1000,
                EVENT_STREAM_INSUFFICIENT_BUFFER_LEN,
                EVENT_STREAM_MESSAGE_FIELD_SIZE_EXCEEDED,
                EVENT_STREAM_PRELUDE_CHECKSUM_FAILURE,
                EVENT_STREAM_MESSAGE_CHECKSUM_FAILURE,
                EVENT_STREAM_MESSAGE_INVALID_HEADERS_LEN,
                EVENT_STREAM_MESSAGE_UNKNOWN_HEADER_TYPE,
                EVENT_STREAM_MESSAGE_PARSER_ILLEGAL_STATE,
                EVENT_STREAM_UNKNOWN_ERROR
            };

            namespace EventStreamErrorsMapper
            {
                /**
                 * Get name by its error type in event stream.
                 */
                AWS_CORE_API const char* GetNameForError(Event::EventStreamErrors error);
                /**
                 * Get AWSError by EventStreamError. The Error type will always be CoreErrors::UNKNOWN as an internal error in Event Stream, and it's always not retryable.
                 */
                AWS_CORE_API Aws::Client::AWSError<Aws::Client::CoreErrors> GetAwsErrorForEventStreamError(Event::EventStreamErrors error);
            } // namespace EventStreamErrorsMapper
        } // namespace Event
    } // namespace Utils
} // namespace Aws
