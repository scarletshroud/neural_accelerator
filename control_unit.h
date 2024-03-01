#ifndef _CONTROL_UNIT_H_
#define _CONTROL_UNIT_H_

#include "systemc.h"

SC_MODULE(ControlUnit)
{
    sc_in<bool>  clk_i;
    sc_out<bool> ioc_wr_o;
    sc_out<bool> ioc_rd_o;
    sc_in<bool> ioc_busy_i;
    sc_in<bool> first_cpu_busy_i;
    sc_in<bool> second_cpu_busy_i;
    sc_in<bool> third_cpu_busy_i;
    sc_in<bool> fourth_cpu_busy_i;
    sc_in<bool> fifth_cpu_busy_i;
    sc_in<float> data_bi;
    sc_out<int> addr_bo;
    sc_out<bool> rd_bo;
    sc_out<bool> wr_bo;
    sc_out<bool> first_cpu_start_o;
    sc_out<bool> second_cpu_start_o;
    sc_out<bool> third_cpu_start_o;
    sc_out<bool> fourth_cpu_start_o;
    sc_out<bool> fifth_cpu_start_o;
    sc_out<int> a_size_first_cpu_o;
    sc_out<int> a_size_second_cpu_o;
    sc_out<int> a_size_third_cpu_o;
    sc_out<int> a_size_fourth_cpu_o;
    sc_out<int> a_size_fifth_cpu_o;
    sc_out<int> curr_neuron_first_cpu_o;
    sc_out<int> curr_neuron_second_cpu_o;
    sc_out<int> curr_neuron_third_cpu_o;
    sc_out<int> curr_neuron_fourth_cpu_o;
    sc_out<int> curr_neuron_fifth_cpu_o;
    sc_out<int> w_offset_first_cpu_o;
    sc_out<int> w_offset_second_cpu_o;
    sc_out<int> w_offset_third_cpu_o;
    sc_out<int> w_offset_fourth_cpu_o;
    sc_out<int> w_offset_fifth_cpu_o;
    sc_out<int> a_offset_first_cpu_o;
    sc_out<int> a_offset_second_cpu_o;
    sc_out<int> a_offset_third_cpu_o;
    sc_out<int> a_offset_fourth_cpu_o;
    sc_out<int> a_offset_fifth_cpu_o;
    sc_out<int> n_offset_first_cpu_o;
    sc_out<int> n_offset_second_cpu_o;
    sc_out<int> n_offset_third_cpu_o;
    sc_out<int> n_offset_fourth_cpu_o;
    sc_out<int> n_offset_fifth_cpu_o;

    SC_HAS_PROCESS(ControlUnit);

    ControlUnit(sc_module_name nm);
    ~ControlUnit();

private:
    void configure();
    float  bus_read(int addr);
    void wait_cpu();
    void reset_cpu_start();
};

#endif // !_CONTROL_UNIT_H_


