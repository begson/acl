/**
 * Copyright (C) 2015-2018
 * All rights reserved.
 *
 * AUTHOR(S)
 *   Zheng Shuxin
 *   E-mail: zhengshuxin@qiyi.com
 * 
 * VERSION
 *   Wed 14 Jun 2017 05:30:59 PM CST
 */

#include "stdafx.h"
#include "manager.h"

manager::manager(void)
	: event_(NULL)
	, aio_(NULL)
	, handle_(NULL)
	, server_(NULL)
{
}

manager::~manager(void)
{
	delete server_;
	delete handle_;
	if (aio_)
		acl_aio_free2(aio_, 1);
}

void manager::init(ACL_EVENT* event, const char* addr)
{
	acl_assert(event);

	if (addr == NULL || *addr == 0)
		return;

	event_  = event;
	aio_    = acl_aio_create3(event);
	handle_ = new acl::aio_handle(aio_);
	server_ = new http_server(*handle_);

	server_->open(addr);
}
