/*
 * memory.c
 *
 *  Created on: Aug 24, 2019
 *      Author: teemu
 */

#include <iostream>
#include <cstring>

#include "memory.hpp"

void memory::access() {

	while(true) {

		do {
			wait();

			if (reset.read()) {
				std::cout << "@" << sc_time_stamp() << " Reseting" << std::endl;
				memset(m_memory, 0, sizeof(m_memory));
			}

		} while ( ! cs.read() );

		if (write_ena.read()) {
			std::cout << "@" << sc_time_stamp() << " Writing data " << data_in.read() << " to address " << address.read() << std::endl;
			m_memory[address.read()] = data_in.read();
		} else {
			std::cout << "@" << sc_time_stamp() << " Reading data " << m_memory[address.read()] << " from address " << address.read() << std::endl;
			data_out.write(m_memory[address.read()]);
		}

	};

}
