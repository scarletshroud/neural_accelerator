#include "local_mem.h"


LocalMem::LocalMem(sc_module_name nm)
    :sc_module(nm),
    clk_i("clk_i"),
    addr_bi("addr_bi"),
    data_bi("data_bi"),
    data_o("data_o"),
    wr_i("wr_i"),
    rd_i("rd_i"),
    addr_i("addr_i")
{
    data_o.initialize(0);

    SC_METHOD(cpu_write);
    sensitive << clk_i.pos();

    SC_METHOD(bus_read);
    sensitive << clk_i.pos();
}

LocalMem::~LocalMem()
{
}

void LocalMem::bus_read()
{
    if (wr_i.read())
        mem[addr_bi.read()] = data_bi.read();
}

void LocalMem::cpu_write()
{
    if (rd_i.read())
        data_o.write(mem[addr_i.read()]);
}
