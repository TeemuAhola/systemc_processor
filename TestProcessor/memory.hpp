/*
 * memory.hpp
 *
 *  Created on: Aug 24, 2019
 *      Author: teemu
 */

#ifndef MEMORY_HPP_
#define MEMORY_HPP_

#include <systemc.h>

SC_MODULE (memory) {
	sc_in_clk   clk;
	sc_in<bool> reset;
	sc_in<bool> cs;
	sc_in<bool> write_ena;
	sc_in<unsigned> address;
  	sc_in<unsigned> data_in;
  	sc_out<unsigned> data_out;
  	sc_out<bool> out_ready;

  	unsigned m_memory[1024];

  	SC_CTOR(memory) {
  		SC_CTHREAD(access, clk.pos())
  	}

  	void access();
};


#endif /* MEMORY_HPP_ */
