/*
* This source file is part of ARK
* For the latest info, see https://github.com/QuadHex
*
* Copyright (c) 2013-2019 QuadHex authors.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#pragma once

#include "base/AFDefine.hpp"
#include "base/AFCDataList.hpp"
#include "base/AFString.hpp"
#include "base/AFArrayPod.hpp"
#include "base/AFStringPod.hpp"
#include "base/AFCData.hpp"

namespace ark
{

    class AFDataNode;

    class AFIDataNodeManager
    {
    public:
        virtual ~AFIDataNodeManager() = default;
        virtual void Clear() = 0;
        virtual const AFGUID& Self() const = 0;
        template<typename BaseType>
        bool RegisterCallback(BaseType* pBase, int (BaseType::*handler)(const AFGUID&, const std::string&, const AFIData&, const AFIData&))
        {
            DATA_NODE_EVENT_FUNCTOR functor = std::bind(handler, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
            return RegisterCallback(std::make_shared<DATA_NODE_EVENT_FUNCTOR>(functor));
        }

        virtual bool RegisterCallback(const DATA_NODE_EVENT_FUNCTOR_PTR& cb) = 0;
        virtual size_t GetNodeCount() = 0;
        virtual AFDataNode* GetNodeByIndex(size_t index) = 0;
        virtual AFDataNode* GetNode(const char* name) = 0;
        virtual bool AddNode(const char* name, const AFIData& value, const AFFeatureType feature) = 0;
        virtual bool SetNode(const char* name, const AFIData& value) = 0;

        virtual bool SetNodeBool(const char* name, const bool value) = 0;
        virtual bool SetNodeInt(const char* name, const int32_t value) = 0;
        virtual bool SetNodeInt64(const char* name, const int64_t value) = 0;
        virtual bool SetNodeFloat(const char* name, const float value) = 0;
        virtual bool SetNodeDouble(const char* name, const double value) = 0;
        virtual bool SetNodeString(const char* name, const std::string& value) = 0;

        virtual bool GetNodeBool(const char* name) = 0;
        virtual int32_t GetNodeInt(const char* name) = 0;
        virtual int64_t GetNodeInt64(const char* name) = 0;
        virtual float GetNodeFloat(const char* name) = 0;
        virtual double GetNodeDouble(const char* name) = 0;
        virtual const char* GetNodeString(const char* name) = 0;
    };

}