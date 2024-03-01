#ifndef _BUS_H_
#define _BUS_H_

#include "systemc.h"

#include <queue>

#define NODES 3

SC_MODULE(Bus)
{
    sc_in<bool>  clk_i;
    sc_in<int>  first_cpu_addr_i;
    sc_in<int>  second_cpu_addr_i;
    sc_in<int>  third_cpu_addr_i;
    sc_in<int>  fourth_cpu_addr_i;
    sc_in<int>  fifth_cpu_addr_i;
    sc_in<int>  ioc_addr_i;
    sc_in<float> first_cpu_data_i;
    sc_in<float> second_cpu_data_i;
    sc_in<float> third_cpu_data_i;
    sc_in<float> fourth_cpu_data_i;
    sc_in<float> fifth_cpu_data_i;
    sc_in<float> ioc_data_i;
    sc_in<int> cu_addr_i;
    //sc_in<int> data_len_i[NODES];
    sc_in<bool> first_cpu_wr_i;
    sc_in<bool> second_cpu_wr_i;
    sc_in<bool> third_cpu_wr_i;
    sc_in<bool> fourth_cpu_wr_i;
    sc_in<bool> fifth_cpu_wr_i;
    sc_in<bool> ioc_wr_i;
    sc_in<bool> first_cpu_rd_i;
    sc_in<bool> second_cpu_rd_i;
    sc_in<bool> third_cpu_rd_i;
    sc_in<bool> fourth_cpu_rd_i;
    sc_in<bool> fifth_cpu_rd_i;
    sc_in<bool> ioc_rd_i;
    sc_in<bool> cu_rd_i;
    sc_in<bool> cu_wr_i;
    sc_out<float> first_cpu_data_o;
    sc_out<float> second_cpu_data_o;
    sc_out<float> third_cpu_data_o;
    sc_out<float> fourth_cpu_data_o;
    sc_out<float> fifth_cpu_data_o;
    sc_out<int> first_lmem_addr_o;
    sc_out<float> first_lmem_data_o;
    sc_out<int> second_lmem_addr_o;
    sc_out<float> second_lmem_data_o;
    sc_out<int> third_lmem_addr_o;
    sc_out<float> third_lmem_data_o;
    sc_out<int> fourth_lmem_addr_o;
    sc_out<float> fourth_lmem_data_o;
    sc_out<int> fifth_lmem_addr_o;
    sc_out<float> fifth_lmem_data_o;
    sc_out<float> ioc_data_o;
    sc_out<float> cu_data_o;
    sc_out<bool> busy_o;
    sc_out<bool> first_cpu_busy_o;
    sc_out<bool> second_cpu_busy_o;
    sc_out<bool> third_cpu_busy_o;
    sc_out<bool> fourth_cpu_busy_o;
    sc_out<bool> fifth_cpu_busy_o;
    sc_out<bool> first_cpu_d_ready_o;
    sc_out<bool> second_cpu_d_ready_o;
    sc_out<bool> third_cpu_d_ready_o;
    sc_out<bool> fourth_cpu_d_ready_o;
    sc_out<bool> fifth_cpu_d_ready_o;
    sc_out<bool> first_lmem_wr_o;
    sc_out<bool> first_lmem_rd_o;
    sc_out<bool> second_lmem_wr_o;
    sc_out<bool> second_lmem_rd_o;
    sc_out<bool> third_lmem_wr_o;
    sc_out<bool> third_lmem_rd_o;
    sc_out<bool> fourth_lmem_wr_o;
    sc_out<bool> fourth_lmem_rd_o;
    sc_out<bool> fifth_lmem_wr_o;
    sc_out<bool> fifth_lmem_rd_o;

    SC_HAS_PROCESS(Bus);

    Bus(sc_module_name nm);
    ~Bus();

    void process();

private:
    void set_busy();
    void update_queue();

    float input_data[49];
    int layers_amount;
    int layers_neurons_amount[2];
    int layers_offset;
    int neurons_offset;
    float activations[57];

    std::queue<int> queue;
};


#endif // !_BUS_H_



