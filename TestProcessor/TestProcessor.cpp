#include <systemc.h>
#include <iostream>

#include "memory.hpp"

int sc_main (int, char *[]) {

	std::cout << "@" << sc_time_stamp() << " Processor starting up" << std::endl;

	int tempData = 0;
	int tempAddress = 0;

	sc_signal<bool> clock, reset, cs, write_ena, out_ready;
	sc_signal<unsigned> address, data_in, data_out;

	memory main_memory("MAIN_MEMORY");
	main_memory(clock, reset, cs, write_ena, address, data_in, data_out, out_ready);

	sc_trace_file *wf = sc_create_vcd_trace_file("processor_trace");
	sc_trace(wf, clock, "clock");
	sc_trace(wf, reset, "reset");
	sc_trace(wf, cs, "cs");
	sc_trace(wf, write_ena, "write_ena");
	sc_trace(wf, address, "address");
	sc_trace(wf, data_in, "data_in");
	sc_trace(wf, data_out, "data_out");

	clock = 0;
	reset = 0;
	cs = 0;
	write_ena = 0;
	address = 0;
	data_in = 0;

	reset = 1;
	sc_start(1, SC_NS);
	clock = 1;
	sc_start(1, SC_NS);
	clock = 0;
	sc_start(1, SC_NS);
	clock = 1;
	sc_start(1, SC_NS);
	reset = 0;

	std::cout << "----------- About to write ----------" << std::endl;

	for (int i = 0; i < 5; i++) {
		clock = 0;
		write_ena = 0;
		cs = 0;
		sc_start(1, SC_NS);
		clock = 1;
		write_ena = 1;
		cs = 1;
		address = tempAddress++;
		data_in = tempData++;
		sc_start(1, SC_NS);
	}

	std::cout << "----------- About to read ----------" << std::endl;

	write_ena = 0;
	tempAddress = 0;

	for (int i = 0; i < 5; i++) {
		clock = 0;
		cs = 0;
		sc_start(1, SC_NS);
		clock = 1;
		cs = 1;
		address = tempAddress++;
		sc_start(1, SC_NS);
		tempData = data_out;
		std::cout << "@" << sc_time_stamp() << " Got " << tempData << std::endl;
	}


	sc_close_vcd_trace_file(wf);
	std::cout << "@" << sc_time_stamp() << " Processor shutting down" << std::endl;

	return 0;
}

