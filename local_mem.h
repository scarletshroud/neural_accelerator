#ifndef _MEM_H
#define _MEM_H

#include "systemc.h"


SC_MODULE(LocalMem)
{

    sc_in<bool> clk_i;
    sc_in<int> addr_bi;
    sc_in<float> data_bi;
    sc_out<float> data_o;
    sc_in<bool> wr_i;
    sc_in<bool> rd_i;
    sc_in<int> addr_i;

    SC_HAS_PROCESS(LocalMem);

    LocalMem(sc_module_name nm);
    ~LocalMem();

    void cpu_write();
    void bus_read();

private:
    float mem[260];
};


#endif