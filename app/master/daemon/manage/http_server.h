/**
 * Copyright (C) 2015-2018
 * All rights reserved.
 *
 * AUTHOR(S)
 *   Zheng Shuxin
 *   E-mail: zhengshuxin@qiyi.com
 * 
 * VERSION
 *   Wed 14 Jun 2017 05:04:32 PM CST
 */

#pragma once

class http_server : public acl::aio_accept_callback
{
public:
	http_server(acl::aio_handle& aio);
	~http_server(void);

	bool open(const char* addr);

protected:
	// @override
	bool accept_callback(acl::aio_socket_stream* client);

private:
	acl::aio_handle& aio_;
	acl::aio_listen_stream* listener_;
};
