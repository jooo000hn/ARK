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

#include "interface/AFINet.h"
#include "AFNetSession.h"

#pragma pack(push, 1)

namespace ark
{

    class AFCWebSocktClient : public AFINet
    {
    public:
        AFCWebSocktClient(brynet::net::TcpService::PTR server = nullptr, brynet::net::AsyncConnector::PTR connector = nullptr);

        template<typename BaseType>
        AFCWebSocktClient(BaseType* pBaseType, void (BaseType::*handleRecieve)(const AFNetMsg*, const int64_t), void (BaseType::*handleEvent)(const AFNetEvent*))
        {
            net_msg_cb_ = std::bind(handleRecieve, pBaseType, std::placeholders::_1, std::placeholders::_2);
            net_event_cb_ = std::bind(handleEvent, pBaseType, std::placeholders::_1);

            brynet::net::base::InitSocket();
            tcp_service_ptr_ = brynet::net::TcpService::Create();
        }

        ~AFCWebSocktClient() override;

        void Update() override;
        bool StartClient(AFHeadLength len, const int dst_busid, const std::string& ip, const int port, bool ip_v6 = false) override;

        bool Shutdown() override final;
        bool SendMsg(AFMsgHead* head, const char* msg_data, const int64_t session_id) override;
        bool CloseSession(const AFGUID& session_id) override;

    protected:
        bool SendMsg(const char* msg, const size_t msg_len, const AFGUID& session_id = 0);

        void UpdateNetSession();
        void UpdateNetEvent(AFHttpSessionPtr session);
        void UpdateNetMsg(AFHttpSessionPtr session);

        bool CloseAllSession();

    private:
        std::unique_ptr<AFHttpSession> client_session_ptr_{ nullptr };
        int dst_bus_id_{ 0 };

        NET_MSG_FUNCTOR net_msg_cb_;
        NET_EVENT_FUNCTOR net_event_cb_;

        AFCReaderWriterLock rw_lock_;
        brynet::net::TcpService::PTR tcp_service_ptr_{ nullptr };
        int64_t trust_session_id_{ 1 };
    };

}

#pragma pack(pop)