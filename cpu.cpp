#include "cpu.h"

#include "addr.h"

CPU::CPU(sc_module_name nm)
    :sc_module(nm),
    clk_i("clk_i"),
    addr_bo("addr_bo"),
    data_bi("data_bi"),
    start_i("start_i"),
    a_size_i("a_size_i"),
    curr_neuron_i("curr_neuron_i"),
    w_offset_i("w_offset_i"),
    a_offset_i("a_offset_i"),
    n_offset_i("n_offset_i"),
    data_lmi("data_lmi"),
    busy_bi("busy_bi"),
    d_ready_i("d_ready_i"),
    data_bo("data_bo"),
    addr_lmo("addr_lmo"),
    rd_lmo("rd_lmo"),
    wr_o("wr_o"),
    rd_o("rd_o"),
    busy_o("busy_o")
{
    addr_bo.initialize(0);
    addr_lmo.initialize(0);
    data_bo.initialize(0);
    rd_lmo.initialize(0);
    wr_o.initialize(0);
    rd_o.initialize(0);
    busy_o.initialize(0);

    SC_CTHREAD(process, clk_i.pos());
}

CPU::~CPU()
{

}

float CPU::sigmoida(float value) {
    return 1 / (1 + std::exp(-value));
}

std::vector<float> CPU::read_activations(const int a_size, const int a_offset) {
    std::vector<float> activations;
    int offset = a_offset_i.read();
    for (size_t i = 0; i < a_size; ++i) {
        activations.push_back(bus_read(ACTIVATION_DATA_ADDR + a_offset + i));
    }

    return activations;
}

std::vector<float> CPU::read_weights(const int a_size, const int w_offset) {
    std::vector<float> weights;
    for (size_t i = 0; i < a_size; ++i) {
        weights.push_back(lmem_read(w_offset + i));
    }

    return weights;
}


#define CALCULATE_UNITS 8
void CPU::process() {

    while (1) {

        if (start_i.read()) {

            std::cout << this->basename() << ":: cpu started " << std::endl;

            busy_o.write(1);

            int a_size = a_size_i.read();
            int current_neuron = curr_neuron_i.read();
            int weights_offset = w_offset_i.read();
            int activations_offset = a_offset_i.read();
            int neuron_offset = n_offset_i.read();

            std::cout << this->basename() << ":: a_size " << a_size << std::endl;
            std::cout << this->basename() << ":: current_neuron " << current_neuron << std::endl;
            std::cout << this->basename() << ":: weights_offset " << weights_offset << std::endl;
            std::cout << this->basename() << ":: activations_offset " << activations_offset << std::endl;
            std::cout << this->basename() << ":: neuron_offset " << neuron_offset << std::endl;

            std::vector<float> activations;
            std::vector<float> weights;

            if (start_i.read()) {
                activations = read_activations(a_size, activations_offset);
                std::cout << std::endl;
                std::cout << this->basename() << ":: activations read " << std::endl;
                weights = read_weights(a_size, weights_offset);
                std::cout << std::endl;
                std::cout << this->basename() << ":: weights read " << std::endl;
            }

            float sum = 0.0f;
            size_t calculated = 0;
            size_t calculation_size = 8;

            while (calculated < activations.size()) {

                if (activations.size() - calculated < CALCULATE_UNITS) {
                    calculation_size = activations.size() - calculated;
                }

                for (size_t j = 0; j < calculation_size; ++j) {
                    sum += activations[calculated + j] * weights[calculated + j];
                }

                calculated += 8;
                wait();
            }

            sum = sigmoida(sum);

            bus_write(ACTIVATION_DATA_ADDR + activations_offset + a_size + neuron_offset, sum);

            std::cout << this->basename() << ":: no busy " << std::endl;
            busy_o.write(0);
        }
        else {
            wait();
        }
    }
}

float CPU::bus_read(int addr)
{
    float data = 0;

    wait();

    addr_bo.write(addr);
    rd_o.write(1);

    wait();

    rd_o.write(0);

    while (d_ready_i.read() == 0) {
        wait();
    }

    data = data_bi.read();

    return data;
}

float CPU::lmem_read(int addr) {
    wait();

    addr_lmo.write(addr);
    rd_lmo.write(1);

    wait();
    rd_lmo.write(0);

    wait();

    return data_lmi.read();
}

void CPU::bus_write(int addr, float data)
{
    wait();
    addr_bo.write(addr);
    data_bo.write(data);
    wr_o.write(1);

    wait();
    wr_o.write(0);
}
