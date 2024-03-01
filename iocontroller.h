#ifndef _IO_CONTROLLER_H_
#define _IO_CONTROLLER_H_

#include "systemc.h"
#include "net_config.h"

SC_MODULE(IOController)
{
    sc_in<bool> clk_i;
    sc_out<int> addr_bo;
    sc_in<float> data_bi;
    sc_out<float> data_bo;
    sc_in<bool> cu_wr_i;
    sc_in<bool> cu_rd_i;
    sc_out<bool> wr_bo;
    sc_out<bool> rd_bo;
    sc_out<bool> busy_o;

    SC_HAS_PROCESS(IOController);

    IOController(sc_module_name nm);
    ~IOController();

    void process();
    void smem_write_initial_data();
    void print_result();

private:
    NetConfig config;

    void bus_write(int addr, float data);
    float bus_read(int addr);

    NetConfig read_file(const std::string & path);
};

#endif

