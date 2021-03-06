// This file is part of the phantom program.
// Copyright (C) 2006-2014, Eugene Mamchits <mamchits@yandex-team.ru>.
// Copyright (C) 2006-2014, YANDEX LLC.
// This program may be distributed under the terms of the GNU LGPL 2.1.
// See the file ‘COPYING’ or ‘http://www.gnu.org/licenses/lgpl-2.1.html’.

#include "io_logger_file.H"

#include <pd/bq/bq_util.H>

#include <pd/base/exception.H>

namespace phantom {

namespace logger_file {
config_binding_sname(io_logger_file_t);
config_binding_value(io_logger_file_t, filename);
config_binding_value(io_logger_file_t, check_interval);
config_binding_parent(io_logger_file_t, io_t);
}

void io_logger_file_t::init() { log_file_t::_init(); }

void io_logger_file_t::run() const {
	while(true) {
		interval_t t = check_interval;

		log_debug("tick");

		if(bq_sleep(&t) < 0)
			throw exception_sys_t(log::error, errno, "bq_sleep: %m");

		check();
	}
}

void io_logger_file_t::stat_print() const { log_file_t::_stat_print(); }

void io_logger_file_t::fini() { }

} // namespace phantom
