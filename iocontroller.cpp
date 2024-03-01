#include "iocontroller.h"
#include "addr.h"

#include <iostream>

IOController::IOController(sc_module_name nm)
    :sc_module(nm),
    clk_i("clk_i"),
    addr_bo("addr_bo"),
    data_bi("data_bi"),
    data_bo("data_bo"),
    cu_wr_i("wr_i"),
    cu_rd_i("rd_i"),
    wr_bo("wr_o"),
    rd_bo("rd_o"),
    busy_o("busy_o")
{
    addr_bo.initialize(0);
    data_bo.initialize(0);
    wr_bo.initialize(0);
    rd_bo.initialize(0);
    busy_o.initialize(0);

    config = read_file("C:\\Users\\User\\Documents\\neural_hw\\neural_hw\\initial_data.txt");

    SC_THREAD(smem_write_initial_data, cu_wr_i.pos());

    SC_THREAD(print_result, cu_rd_i.pos());
}

IOController::~IOController() {

}


void IOController::smem_write_initial_data() {

    busy_o.write(1);

    sc_time t_delay(10, SC_NS);

    std::vector<float>& input = config.get_input();

    for (size_t i = 0; i < input.size(); ++i) {
        bus_write(INPUT_DATA_ADDR + i, input[i]);
    }

    bus_write(LAYERS_AMOUNT_ADDR, config.get_layers_amount());

    std::vector<int>& layers_neurons_amount = config.get_layers_neurons_amount();
    for (size_t i = 0; i < layers_neurons_amount.size(); ++i) {
        bus_write(LAYERS_NEURONS_AMOUNT_ADDR + i, layers_neurons_amount[i]);
    }

    std::vector<float>& weights = config.get_weights();

    for (size_t i = 0; i < weights.size(); ++i) {
        bus_write(FIRST_LOCAL_MEM_ADDR + i, weights[i]);
        bus_write(SECOND_LOCAL_MEM_ADDR + i, weights[i]);
        bus_write(THIRD_LOCAL_MEM_ADDR + i, weights[i]);
        bus_write(FOURTH_LOCAL_MEM_ADDR + i, weights[i]);
        bus_write(FIFTH_LOCAL_MEM_ADDR + i, weights[i]);
    }

    busy_o.write(0);
}

float IOController::bus_read(int addr)
{
    sc_time t_delay(10, SC_NS);

    int data;

    wait(t_delay);
    rd_bo.write(1);
    // addr_bo.write(addr);

    wait(t_delay);
    rd_bo.write(0);

    wait(t_delay);
    data = data_bi.read();

    return data;
}

void IOController::bus_write(int addr, float data)
{
    sc_time t_delay(10, SC_NS);

    wr_bo.write(1);
    addr_bo.write(addr);
    data_bo.write(data);

    wait(t_delay);

    wr_bo.write(0);
}

NetConfig IOController::read_file(const std::string& path) {

    std::ifstream in(path);

    std::vector<float> inputs(49);
    std::vector<int> layer_neurons_amount(3);
    std::vector<float> weights(260);

    if (in.is_open()) {
        for (size_t i = 0; i < 49; ++i) {
            in >> inputs[i];
        }

        for (size_t i = 0; i < 3; ++i) {
            in >> layer_neurons_amount[i];
        }

        for (size_t i = 0; i < 260; ++i) {
            in >> weights[i];
        }
    }

    return NetConfig(inputs, 3, layer_neurons_amount, weights);
}

void IOController::print_result() {
    /*std::cout << "print";
      std::vector<float> result(3);
      for (size_t i = 0; i < 3; ++i) {
          result[i] = bus_read(ACTIVATION_DATA_ADDR + 49 + 5 + i);
          std::cout << result[i];
      } */
}