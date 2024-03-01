#include "control_unit.h"

#include "addr.h"

ControlUnit::ControlUnit(sc_module_name nm)
    :sc_module(nm),
    clk_i("clk_i"),
    ioc_wr_o("ioc_write_o"),
    ioc_rd_o("ioc_rd_o"),
    ioc_busy_i("ioc_busy_i"),
    first_cpu_busy_i("first_cpu_busy_i"),
    second_cpu_busy_i("second_cpu_busy_i"),
    third_cpu_busy_i("third_cpu_busy_i"),
    fourth_cpu_busy_i("fourth_cpu_busy_i"),
    fifth_cpu_busy_i("fifth_cpu_busy_i"),
    first_cpu_start_o("first_cpu_start"),
    second_cpu_start_o("second_cpu_start"),
    third_cpu_start_o("third_cpu_start"),
    fourth_cpu_start_o("fourth_cpu_start"),
    fifth_cpu_start_o("fifth_cpu_start"),
    a_size_first_cpu_o("a_size_first_cpu_o"),
    a_size_second_cpu_o("a_size_second_cpu_o"),
    a_size_third_cpu_o("a_size_third_cpu_o"),
    a_size_fourth_cpu_o("a_size_fourth_cpu_o"),
    a_size_fifth_cpu_o("a_size_fifth_cpu_o"),
    curr_neuron_first_cpu_o("curr_neuron_first_cpu_o"),
    curr_neuron_second_cpu_o("curr_neuron_second_cpu_o"),
    curr_neuron_third_cpu_o("curr_neuron_third_cpu_o"),
    curr_neuron_fourth_cpu_o("curr_neuron_fourth_cpu_o"),
    curr_neuron_fifth_cpu_o("curr_neuron_fifth_cpu_o"),
    w_offset_first_cpu_o("w_offset_first_cpu_o"),
    w_offset_second_cpu_o("w_offset_second_cpu_o"),
    w_offset_third_cpu_o("w_offset_third_cpu_o"),
    w_offset_fourth_cpu_o("w_offset_fourth_cpu_o"),
    w_offset_fifth_cpu_o("w_offset_fifth_cpu_o"),
    a_offset_first_cpu_o("a_offset_first_cpu_o"),
    a_offset_second_cpu_o("a_offset_second_cpu_o"),
    a_offset_third_cpu_o("a_offset_third_cpu_o"),
    a_offset_fourth_cpu_o("a_offset_fourth_cpu_o"),
    a_offset_fifth_cpu_o("a_offset_fifth_cpu_o"),
    n_offset_first_cpu_o("n_offset_first_cpu_o"),
    n_offset_second_cpu_o("n_offset_second_cpu_o"),
    n_offset_third_cpu_o("n_offset_third_cpu_o"),
    n_offset_fourth_cpu_o("n_offset_fourth_cpu_o"),
    n_offset_fifth_cpu_o("n_offset_fifth_cpu_o")
{
    ioc_wr_o.initialize(0);
    ioc_rd_o.initialize(0);
    first_cpu_start_o.initialize(0);
    second_cpu_start_o.initialize(0);
    third_cpu_start_o.initialize(0);
    fourth_cpu_start_o.initialize(0);
    fifth_cpu_start_o.initialize(0);
    a_size_first_cpu_o.initialize(0);
    a_size_second_cpu_o.initialize(0);
    a_size_third_cpu_o.initialize(0);
    a_size_fourth_cpu_o.initialize(0);
    a_size_fifth_cpu_o.initialize(0);
    curr_neuron_first_cpu_o.initialize(0);
    curr_neuron_second_cpu_o.initialize(0);
    curr_neuron_third_cpu_o.initialize(0);
    curr_neuron_fourth_cpu_o.initialize(0);
    curr_neuron_fifth_cpu_o.initialize(0);
    w_offset_first_cpu_o.initialize(0);
    w_offset_second_cpu_o.initialize(0);
    w_offset_third_cpu_o.initialize(0);
    w_offset_fourth_cpu_o.initialize(0);
    w_offset_fifth_cpu_o.initialize(0);
    a_offset_first_cpu_o.initialize(0);
    a_offset_second_cpu_o.initialize(0);
    a_offset_third_cpu_o.initialize(0);
    a_offset_fourth_cpu_o.initialize(0);
    a_offset_fifth_cpu_o.initialize(0);
    n_offset_first_cpu_o.initialize(0);
    n_offset_second_cpu_o.initialize(0);
    n_offset_third_cpu_o.initialize(0);
    n_offset_fourth_cpu_o.initialize(0);
    n_offset_fifth_cpu_o.initialize(0);

    SC_CTHREAD(configure, clk_i.pos());
}

ControlUnit::~ControlUnit() {

}

void ControlUnit::wait_cpu() {
    while (1) {
        if (first_cpu_busy_i.read() 
            || second_cpu_busy_i.read()
            || third_cpu_busy_i.read()
            || fourth_cpu_busy_i.read()
            || fifth_cpu_busy_i.read()
        ) {
            wait();
        }
        else {
            break;
        }
    }
}

void ControlUnit::reset_cpu_start() {
    first_cpu_start_o.write(0);
    second_cpu_start_o.write(0);
    third_cpu_start_o.write(0);
    fourth_cpu_start_o.write(0);
    fifth_cpu_start_o.write(0);
}

int update_configuration(std::vector<int> & layers_neurons, int & layers_amount, int & weights_offset, int & activations_offset, int& layers_offset, int& neurons_offset) {
    weights_offset += layers_neurons[layers_offset];

    if (neurons_offset < layers_neurons[layers_offset + 1] - 1)
        neurons_offset++;
    else {
        activations_offset += layers_neurons[layers_offset];
        layers_offset++;

        if (layers_offset == layers_amount - 1 && neurons_offset == layers_neurons[layers_offset] - 1) {
            return 1;
        }

        neurons_offset = 0;
    }

    return 0;
}

void ControlUnit::configure() {
    wait();

    ioc_wr_o.write(1);

    wait();

    ioc_wr_o.write(0);

    while (ioc_busy_i) {
        wait();
    }

    int layers_amount = bus_read(LAYERS_AMOUNT_ADDR);

    std::vector<int> layers_neurons(layers_amount);
    for (size_t i = 0; i < layers_amount; ++i) {
        layers_neurons[i] = bus_read(LAYERS_NEURONS_AMOUNT_ADDR + i);
    }

    int weights_offset = 0;
    int activations_offset = 0;
    int layers_offset = 0;
    int neurons_offset = 0;


    while (1) {

        if (neurons_offset == 0)
            wait_cpu();

        if (first_cpu_busy_i.read() == 0) {

            first_cpu_start_o.write(1);
            a_size_first_cpu_o.write(layers_neurons[layers_offset]);
            curr_neuron_first_cpu_o.write(neurons_offset);
            w_offset_first_cpu_o.write(weights_offset);
            a_offset_first_cpu_o.write(activations_offset);
            n_offset_first_cpu_o.write(neurons_offset);

            if (update_configuration(layers_neurons, layers_amount, weights_offset, activations_offset, layers_offset, neurons_offset)) {
                break;
            }
        }

        if (second_cpu_busy_i.read() == 0) {

            second_cpu_start_o.write(1);
            a_size_second_cpu_o.write(layers_neurons[layers_offset]);
            curr_neuron_second_cpu_o.write(neurons_offset);
            w_offset_second_cpu_o.write(weights_offset);
            a_offset_second_cpu_o.write(activations_offset);
            n_offset_second_cpu_o.write(neurons_offset);

            if (update_configuration(layers_neurons, layers_amount, weights_offset, activations_offset, layers_offset, neurons_offset)) {
                break;
            }
        }

        if (third_cpu_busy_i.read() == 0) {
            third_cpu_start_o.write(1);
            a_size_third_cpu_o.write(layers_neurons[layers_offset]);
            curr_neuron_third_cpu_o.write(neurons_offset);
            w_offset_third_cpu_o.write(weights_offset);
            a_offset_third_cpu_o.write(activations_offset);
            n_offset_third_cpu_o.write(neurons_offset);

            if (update_configuration(layers_neurons, layers_amount, weights_offset, activations_offset, layers_offset, neurons_offset)) {
                break;
            }
        }

        if (fourth_cpu_busy_i.read() == 0) {
            fourth_cpu_start_o.write(1);
            a_size_fourth_cpu_o.write(layers_neurons[layers_offset]);
            curr_neuron_fourth_cpu_o.write(neurons_offset);
            w_offset_fourth_cpu_o.write(weights_offset);
            a_offset_fourth_cpu_o.write(activations_offset);
            n_offset_fourth_cpu_o.write(neurons_offset);

            if (update_configuration(layers_neurons, layers_amount, weights_offset, activations_offset, layers_offset, neurons_offset)) {
                break;
            }
        }

        if (fifth_cpu_busy_i.read() == 0) {
            fifth_cpu_start_o.write(1);
            a_size_fifth_cpu_o.write(layers_neurons[layers_offset]);
            curr_neuron_fifth_cpu_o.write(neurons_offset);
            w_offset_fifth_cpu_o.write(weights_offset);
            a_offset_fifth_cpu_o.write(activations_offset);
            n_offset_fifth_cpu_o.write(neurons_offset);

            if (update_configuration(layers_neurons, layers_amount, weights_offset, activations_offset, layers_offset, neurons_offset)) {
                break;
            }
        }

        wait();
        wait();

        reset_cpu_start();
    }

    wait();

    reset_cpu_start();

    wait();

    wait_cpu();

    std::vector<float> result(3);
    for (size_t i = 0; i < 3; ++i) {
        result[i] = bus_read(ACTIVATION_DATA_ADDR + 49 + 5 + i);
        std::cout << result[i] << std::endl;
    } 

    ioc_rd_o.write(1);

    wait();

    ioc_rd_o.write(0);

    while (ioc_busy_i) {
        wait();
    }

    sc_stop();
}

void load_cpu(sc_out<bool>& cpu_start, int cpu_busy) {
    if (!cpu_busy) {
        cpu_start.write(1);
    }
}

float ControlUnit::bus_read(int addr)
{
    float data;

    wait();
    addr_bo.write(addr);
    rd_bo.write(1);

    wait();
    rd_bo.write(0);

    wait();
    data = data_bi.read();

    return data;
}