/**
 * Copyright (C) 2015-2018
 * All rights reserved.
 *
 * AUTHOR(S)
 *   Zheng Shuxin
 *   E-mail: zhengshuxin@qiyi.com
 * 
 * VERSION
 *   Wed 14 Jun 2017 05:04:27 PM CST
 */

#include "stdafx.h"
#include "http_client.h"
#include "http_server.h"

http_server::http_server(acl::aio_handle& aio)
	: aio_(aio)
	, listener_(NULL)
{
}

http_server::~http_server(void)
{
	if (listener_)
		listener_->destroy();
}

bool http_server::open(const char* addr)
{
	listener_ = new acl::aio_listen_stream(&aio_);
	if (listener_->open(addr) == false)
	{
		logger_error("open %s error %s", addr, acl::last_serror());
		listener_->destroy();
		listener_ = NULL;
		return false;
	}

	listener_->add_accept_callback(this);
	logger("master manager started on %s", addr);
	return true;
}

bool http_server::accept_callback(acl::aio_socket_stream* client)
{
	http_client* hc = new http_client(client);
	hc->wait();
	return true;
}
