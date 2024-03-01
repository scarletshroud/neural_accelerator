#ifndef _CPU_H
#define _CPU_H

#include "systemc.h"

SC_MODULE(CPU)
{
    sc_in<bool>  clk_i;
    sc_out<int>  addr_bo;
    sc_in<float>   data_bi;
    sc_in<bool> start_i;
    sc_in<int> a_size_i;
    sc_in<int> curr_neuron_i;
    sc_in<int> w_offset_i;
    sc_in<int> a_offset_i;
    sc_in<int> n_offset_i;
    sc_in<float> data_lmi;
    sc_in<bool> busy_bi;
    sc_in<bool> d_ready_i;
    sc_out<float>  data_bo;
    sc_out<int> addr_lmo;
    sc_out<bool> rd_lmo;
    sc_out<bool> wr_o;
    sc_out<bool> rd_o;
    sc_out<bool> busy_o;

    SC_HAS_PROCESS(CPU);

    CPU(sc_module_name nm);
    ~CPU();

    void mainThread();
    void process();
private:
    float bus_read(int addr);
    float lmem_read(int addr);
    void bus_write(int addr, float data);

    float sigmoida(float value);

    std::vector<float>  read_activations(const int a_size, const int a_offset);
    std::vector<float>  read_weights(const int a_size, const int w_offset);

    std::vector<float> weights_fifo;
    std::vector<float> activation_fifo;
};

#endif
