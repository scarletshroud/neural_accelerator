#include "bus.h"

#include "addr.h"

#define FIRST_CPU_READ 1
#define SECOND_CPU_READ 2
#define THIRD_CPU_READ 3
#define FOURTH_CPU_READ 4
#define FIFTH_CPU_READ 5
#define FIRST_CPU_WRITE 6
#define SECOND_CPU_WRITE 7
#define THIRD_CPU_WRITE 8
#define FOURTH_CPU_WRITE 9
#define FIFTH_CPU_WRITE 10
#define IO_CONTROLLER_READ 11
#define IO_CONTROLLER_WRITE 12
#define CONTROL_UNIT 13


Bus::Bus(sc_module_name nm)
    :sc_module(nm),
    clk_i("clk_i"),
    first_cpu_addr_i("first_cpu_addr_i"),
    second_cpu_addr_i("second_cpu_addr_i"),
    third_cpu_addr_i("third_cpu_addr_i"),
    fourth_cpu_addr_i("fourth_cpu_addr_i"),
    fifth_cpu_addr_i("fifth_cpu_addr_i"),
    ioc_addr_i("ioc_addr_i"),
    first_cpu_data_i("first_cpu_data_i"),
    second_cpu_data_i("second_cpu_data_i"),
    third_cpu_data_i("third_cpu_data_i"),
    fourth_cpu_data_i("fourth_cpu_data_i"),
    fifth_cpu_data_i("fifth_cpu_data_i"),
    ioc_data_i("ioc_data_i"),
    first_cpu_wr_i("first_cpu_wr_i"),
    second_cpu_wr_i("second_cpu_wr_i"),
    third_cpu_wr_i("third_cpu_wr_i"),
    fourth_cpu_wr_i("fourth_cpu_wr_i"),
    fifth_cpu_wr_i("fifth_cpu_wr_i"),
    ioc_wr_i("ioc_wr_i"),
    first_cpu_rd_i("first_cpu_rd_i"),
    second_cpu_rd_i("second_cpu_rd_i"),
    third_cpu_rd_i("third_cpu_rd_i"),
    fourth_cpu_rd_i("fourth_cpu_rd_i"),
    fifth_cpu_rd_i("fifth_cpu_rd_i"),
    ioc_rd_i("ioc_rd_i"),
    first_cpu_data_o("first_cpu_data_o"),
    second_cpu_data_o("second_cpu_data_o"),
    third_cpu_data_o("third_cpu_data_o"),
    fourth_cpu_data_o("fourth_cpu_data_o"),
    fifth_cpu_data_o("fifth_cpu_data_o"),
    first_lmem_addr_o("first_lmem_addr_o"),
    first_lmem_data_o("first_lmem_data_o"),
    second_lmem_addr_o("second_lmem_addr_o"),
    second_lmem_data_o("second_lmem_data_o"),
    third_lmem_addr_o("third_lmem_addr_o"),
    third_lmem_data_o("third_lmem_data_o"),
    fourth_lmem_addr_o("fourth_lmem_addr_o"),
    fourth_lmem_data_o("fourth_lmem_data_o"),
    fifth_lmem_addr_o("fifth_lmem_addr_o"),
    fifth_lmem_data_o("fifth_lmem_data_o"),
    ioc_data_o("ioc_data_o"),
    busy_o("busy_o"),
    first_cpu_busy_o("first_cpu_busy_o"),
    second_cpu_busy_o("second_cpu_busy_o"),
    third_cpu_busy_o("third_cpu_busy_o"),
    fourth_cpu_busy_o("fourth_cpu_busy_o"),
    fifth_cpu_busy_o("fifth_cpu_busy_o"),
    first_lmem_wr_o("first_lmem_wr_o"),
    first_lmem_rd_o("first_lmem_rd_o"),
    second_lmem_wr_o("second_lmem_wr_o"),
    second_lmem_rd_o("second_lmem_rd_o"),
    third_lmem_wr_o("third_lmem_wr_o"),
    third_lmem_rd_o("third_lmem_rd_o"),
    fourth_lmem_wr_o("fourth_lmem_wr_o"),
    fourth_lmem_rd_o("fourth_lmem_rd_o"),
    fifth_lmem_wr_o("fifth_lmem_wr_o"),
    fifth_lmem_rd_o("fifth_lmem_rd_o")
{
    first_cpu_data_o.initialize(0);
    second_cpu_data_o.initialize(0);
    third_cpu_data_o.initialize(0);
    fourth_cpu_data_o.initialize(0);
    fifth_cpu_data_o.initialize(0);
    first_lmem_data_o.initialize(0);
    ioc_data_o.initialize(0);
    busy_o.initialize(0);

    fifth_cpu_busy_o.initialize(0);
    second_cpu_busy_o.initialize(0);
    third_cpu_busy_o.initialize(0);
    fourth_cpu_busy_o.initialize(0);
    fifth_cpu_busy_o.initialize(0);

    first_lmem_wr_o.initialize(0);
    first_lmem_rd_o.initialize(0);
    second_lmem_wr_o.initialize(0);
    second_lmem_rd_o.initialize(0);
    third_lmem_wr_o.initialize(0);
    third_lmem_rd_o.initialize(0);
    fourth_lmem_wr_o.initialize(0);
    fourth_lmem_rd_o.initialize(0);
    fifth_lmem_wr_o.initialize(0);
    fifth_lmem_rd_o.initialize(0);

    SC_CTHREAD(process, clk_i.pos());
}

Bus::~Bus() {

}

void Bus::update_queue() {

    if (first_cpu_rd_i.read()) {
        queue.push(FIRST_CPU_READ);
    }

    if (second_cpu_rd_i.read()) {
        queue.push(SECOND_CPU_READ);
    }

    if (third_cpu_rd_i.read()) {
        queue.push(THIRD_CPU_READ);
    }

    if (fourth_cpu_rd_i.read()) {
        queue.push(FOURTH_CPU_READ);
    }

    if (fifth_cpu_rd_i.read()) {
        queue.push(FIFTH_CPU_READ);
    }

    if (first_cpu_wr_i.read()) {
        queue.push(FIRST_CPU_WRITE);
    }

    if (second_cpu_wr_i.read()) {
        queue.push(SECOND_CPU_WRITE);
    }

    if (third_cpu_wr_i.read()) {
        queue.push(THIRD_CPU_WRITE);
    }

    if (fourth_cpu_wr_i.read()) {
        queue.push(FOURTH_CPU_WRITE);
    }

    if (fifth_cpu_wr_i.read()) {
        queue.push(FIFTH_CPU_WRITE);
    }

    if (ioc_rd_i.read()) {
        queue.push(IO_CONTROLLER_READ);
    }

    if (ioc_wr_i.read()) {
        queue.push(IO_CONTROLLER_WRITE);
    }

    if (cu_rd_i.read() || cu_wr_i.read()) {
        queue.push(CONTROL_UNIT);
    }
}

void Bus::process() {

    while (1) {
        update_queue();

        int unit = 0;

        if (!queue.empty()) {
            unit = queue.front();
            queue.pop();
        }

        int base_addr = 0;
        int addr_offset = 0;
        float value = 0;

        first_cpu_d_ready_o.write(0);
        second_cpu_d_ready_o.write(0);
        third_cpu_d_ready_o.write(0);
        fourth_cpu_d_ready_o.write(0);
        fifth_cpu_d_ready_o.write(0);

        switch (unit) {
        case 0:
            busy_o.write(0);
            first_cpu_busy_o.write(0);
            second_cpu_busy_o.write(0);
            third_cpu_busy_o.write(0);
            fourth_cpu_busy_o.write(0);
            fifth_cpu_busy_o.write(0);

            wait();
            break;

        case FIRST_CPU_READ:
            busy_o.write(1);
            first_cpu_busy_o.write(1);
            second_cpu_busy_o.write(1);
            third_cpu_busy_o.write(1);
            fourth_cpu_busy_o.write(1);
            fifth_cpu_busy_o.write(1);

            first_cpu_d_ready_o.write(0);

            base_addr = (first_cpu_addr_i.read() / 1000) * 1000;
            addr_offset = first_cpu_addr_i.read() % 1000;
            value = 0;

            switch (base_addr) {
            case INPUT_DATA_ADDR:
                value = input_data[addr_offset];
                break;
            case LAYERS_AMOUNT_ADDR:
                value = layers_amount;
                break;
            case LAYERS_NEURONS_AMOUNT_ADDR:
                value = layers_neurons_amount[addr_offset];
                break;
            case NEURONS_OFFSET_ADDR:
                value = neurons_offset;
                break;
            case ACTIVATION_DATA_ADDR:
                value = activations[addr_offset];
                break;
            }

            wait();

            first_cpu_data_o.write(value);
            first_cpu_d_ready_o.write(1);

            wait();
            break;

        case FIRST_CPU_WRITE:

            busy_o.write(1);

            first_cpu_busy_o.write(1);
            second_cpu_busy_o.write(1);
            third_cpu_busy_o.write(1);
            fourth_cpu_busy_o.write(1);
            fifth_cpu_busy_o.write(1);

            base_addr = (first_cpu_addr_i.read() / 1000) * 1000;
            addr_offset = first_cpu_addr_i.read() % 1000;
            value = first_cpu_data_i.read();

            switch (base_addr) {
            case INPUT_DATA_ADDR:
                input_data[addr_offset] = value;
                break;
            case LAYERS_AMOUNT_ADDR:
                layers_amount = value;
                break;
            case LAYERS_NEURONS_AMOUNT_ADDR:
                layers_neurons_amount[addr_offset] = value;
                break;
            case NEURONS_OFFSET_ADDR:
                neurons_offset = value;
                break;
            case ACTIVATION_DATA_ADDR:
                activations[addr_offset] = value;
                break;
            }

            wait();

            break;

        case SECOND_CPU_READ:
            busy_o.write(1);

            first_cpu_busy_o.write(1);
            second_cpu_busy_o.write(1);
            third_cpu_busy_o.write(1);
            fourth_cpu_busy_o.write(1);
            fifth_cpu_busy_o.write(1);

            second_cpu_d_ready_o.write(0);

            base_addr = (second_cpu_addr_i.read() / 1000) * 1000;
            addr_offset = second_cpu_addr_i.read() % 1000;
            value = 0;
            switch (base_addr) {
            case INPUT_DATA_ADDR:
                value = input_data[addr_offset];
                break;
            case LAYERS_AMOUNT_ADDR:
                value = layers_amount;
                break;
            case LAYERS_NEURONS_AMOUNT_ADDR:
                value = layers_neurons_amount[addr_offset];
                break;
            case NEURONS_OFFSET_ADDR:
                value = neurons_offset;
                break;
            case ACTIVATION_DATA_ADDR:
                value = activations[addr_offset];
                break;
            }

            wait();

            second_cpu_data_o.write(value);
            second_cpu_d_ready_o.write(1);

            wait();
            break;

        case SECOND_CPU_WRITE:
            busy_o.write(1);
            first_cpu_busy_o.write(1);
            second_cpu_busy_o.write(1);
            third_cpu_busy_o.write(1);
            fourth_cpu_busy_o.write(1);
            fifth_cpu_busy_o.write(1);

            base_addr = (second_cpu_addr_i.read() / 1000) * 1000;
            addr_offset = second_cpu_addr_i.read() % 1000;
            value = second_cpu_data_i.read();

            switch (base_addr) {
            case INPUT_DATA_ADDR:
                input_data[addr_offset] = value;
                break;
            case LAYERS_AMOUNT_ADDR:
                layers_amount = value;
                break;
            case LAYERS_NEURONS_AMOUNT_ADDR:
                layers_neurons_amount[addr_offset] = value;
                break;
            case NEURONS_OFFSET_ADDR:
                neurons_offset = value;
                break;
            case ACTIVATION_DATA_ADDR:
                activations[addr_offset] = value;
                break;
            }

            wait();

            break;

        case THIRD_CPU_READ:


            busy_o.write(1);

            first_cpu_busy_o.write(1);
            second_cpu_busy_o.write(1);
            third_cpu_busy_o.write(1);
            fourth_cpu_busy_o.write(1);
            fifth_cpu_busy_o.write(1);

            third_cpu_d_ready_o.write(0);

            base_addr = (third_cpu_addr_i.read() / 1000) * 1000;
            addr_offset = third_cpu_addr_i.read() % 1000;
            value = 0;
            switch (base_addr) {
            case INPUT_DATA_ADDR:
                value = input_data[addr_offset];
                break;
            case LAYERS_AMOUNT_ADDR:
                value = layers_amount;
                break;
            case LAYERS_NEURONS_AMOUNT_ADDR:
                value = layers_neurons_amount[addr_offset];
                break;
            case NEURONS_OFFSET_ADDR:
                value = neurons_offset;
                break;
            case ACTIVATION_DATA_ADDR:
                value = activations[addr_offset];
                break;
            }

            wait();

            third_cpu_data_o.write(value);
            third_cpu_d_ready_o.write(1);

            wait();

            break;

        case THIRD_CPU_WRITE:
            busy_o.write(1);
            first_cpu_busy_o.write(1);
            second_cpu_busy_o.write(1);
            third_cpu_busy_o.write(1);
            fourth_cpu_busy_o.write(1);
            fifth_cpu_busy_o.write(1);

            base_addr = (third_cpu_addr_i.read() / 1000) * 1000;
            addr_offset = third_cpu_addr_i.read() % 1000;
            value = third_cpu_data_i.read();

            switch (base_addr) {
            case INPUT_DATA_ADDR:
                input_data[addr_offset] = value;
                break;
            case LAYERS_AMOUNT_ADDR:
                layers_amount = value;
                break;
            case LAYERS_NEURONS_AMOUNT_ADDR:
                layers_neurons_amount[addr_offset] = value;
                break;
            case NEURONS_OFFSET_ADDR:
                neurons_offset = value;
                break;
            case ACTIVATION_DATA_ADDR:
                activations[addr_offset] = value;
                break;
            }

            wait();

            break;

        case FOURTH_CPU_READ:

            busy_o.write(1);

            first_cpu_busy_o.write(1);
            second_cpu_busy_o.write(1);
            third_cpu_busy_o.write(1);
            fourth_cpu_busy_o.write(1);
            fifth_cpu_busy_o.write(1);

            fourth_cpu_d_ready_o.write(0);

            base_addr = (fourth_cpu_addr_i.read() / 1000) * 1000;
            addr_offset = fourth_cpu_addr_i.read() % 1000;
            value = 0;
            switch (base_addr) {
            case INPUT_DATA_ADDR:
                value = input_data[addr_offset];
                break;
            case LAYERS_AMOUNT_ADDR:
                value = layers_amount;
                break;
            case LAYERS_NEURONS_AMOUNT_ADDR:
                value = layers_neurons_amount[addr_offset];
                break;
            case NEURONS_OFFSET_ADDR:
                value = neurons_offset;
                break;
            case ACTIVATION_DATA_ADDR:
                value = activations[addr_offset];
                break;
            }

            wait();

            fourth_cpu_data_o.write(value);
            fourth_cpu_d_ready_o.write(1);

            wait();

            break;

        case FOURTH_CPU_WRITE:
            busy_o.write(1);
            first_cpu_busy_o.write(1);
            second_cpu_busy_o.write(1);
            third_cpu_busy_o.write(1);
            fourth_cpu_busy_o.write(1);
            fifth_cpu_busy_o.write(1);

            base_addr = (fourth_cpu_addr_i.read() / 1000) * 1000;
            addr_offset = fourth_cpu_addr_i.read() % 1000;
            value = fourth_cpu_data_i.read();

            switch (base_addr) {
            case INPUT_DATA_ADDR:
                input_data[addr_offset] = value;
                break;
            case LAYERS_AMOUNT_ADDR:
                layers_amount = value;
                break;
            case LAYERS_NEURONS_AMOUNT_ADDR:
                layers_neurons_amount[addr_offset] = value;
                break;
            case NEURONS_OFFSET_ADDR:
                neurons_offset = value;
                break;
            case ACTIVATION_DATA_ADDR:
                activations[addr_offset] = value;
                break;
            }

            wait();

            break;

        case FIFTH_CPU_READ:


            busy_o.write(1);

            first_cpu_busy_o.write(1);
            second_cpu_busy_o.write(1);
            third_cpu_busy_o.write(1);
            fourth_cpu_busy_o.write(1);
            fifth_cpu_busy_o.write(1);

            fifth_cpu_d_ready_o.write(0);

            base_addr = (fifth_cpu_addr_i.read() / 1000) * 1000;
            addr_offset = fifth_cpu_addr_i.read() % 1000;
            value = 0;
            switch (base_addr) {
            case INPUT_DATA_ADDR:
                value = input_data[addr_offset];
                break;
            case LAYERS_AMOUNT_ADDR:
                value = layers_amount;
                break;
            case LAYERS_NEURONS_AMOUNT_ADDR:
                value = layers_neurons_amount[addr_offset];
                break;
            case NEURONS_OFFSET_ADDR: 
                value = neurons_offset;
                break;
            case ACTIVATION_DATA_ADDR:
                value = activations[addr_offset];
                break;
            }

            wait();

            fifth_cpu_data_o.write(value);
            fifth_cpu_d_ready_o.write(1);

            wait();

            break;

        case FIFTH_CPU_WRITE:
            busy_o.write(1);
            first_cpu_busy_o.write(1);
            second_cpu_busy_o.write(1);
            third_cpu_busy_o.write(1);
            fourth_cpu_busy_o.write(1);
            fifth_cpu_busy_o.write(1);

            base_addr = (fifth_cpu_addr_i.read() / 1000) * 1000;
            addr_offset = fifth_cpu_addr_i.read() % 1000;
            value = fifth_cpu_data_i.read();

            switch (base_addr) {
            case INPUT_DATA_ADDR:
                input_data[addr_offset] = value;
                break;
            case LAYERS_AMOUNT_ADDR:
                layers_amount = value;
                break;
            case LAYERS_NEURONS_AMOUNT_ADDR:
                layers_neurons_amount[addr_offset] = value;
                break;
            case NEURONS_OFFSET_ADDR:
                neurons_offset = value;
                break;
            case ACTIVATION_DATA_ADDR:
                activations[addr_offset] = value;
                break;
            }

            wait();

            break;

        case IO_CONTROLLER_READ:

            busy_o.write(1);
            first_cpu_busy_o.write(1);
            second_cpu_busy_o.write(1);
            third_cpu_busy_o.write(1);
            fourth_cpu_busy_o.write(1);
            fifth_cpu_busy_o.write(1);

            base_addr = (ioc_addr_i.read() / 1000) * 1000;
            addr_offset = ioc_addr_i.read() % 1000;;
            switch (base_addr) {
            case INPUT_DATA_ADDR:
                ioc_data_o.write(input_data[addr_offset]);
                break;
            case LAYERS_AMOUNT_ADDR:
                ioc_data_o.write(layers_amount);
                break;
            case LAYERS_NEURONS_AMOUNT_ADDR:
                ioc_data_o.write(layers_neurons_amount[addr_offset]);
                break;
            case NEURONS_OFFSET_ADDR:
                ioc_data_o.write(neurons_offset);
                break;
            case ACTIVATION_DATA_ADDR:
                ioc_data_o.write(activations[addr_offset]);
                break;
            }

            wait();

            busy_o.write(0);
            break;

        case IO_CONTROLLER_WRITE:

            busy_o.write(1);
            first_cpu_busy_o.write(1);
            second_cpu_busy_o.write(1);
            third_cpu_busy_o.write(1);
            fourth_cpu_busy_o.write(1);
            fifth_cpu_busy_o.write(1);

            base_addr = (ioc_addr_i.read() / 1000) * 1000;
            addr_offset = ioc_addr_i.read() % 1000;
            switch (base_addr) {
            case INPUT_DATA_ADDR:
                activations[addr_offset] = ioc_data_i.read();
                break;

            case LAYERS_AMOUNT_ADDR:
                layers_amount = ioc_data_i.read();
                break;

            case LAYERS_NEURONS_AMOUNT_ADDR:
                layers_neurons_amount[addr_offset] = ioc_data_i.read();
                break;

            case NEURONS_OFFSET_ADDR:
                neurons_offset = ioc_data_i.read();
                break;

            case FIRST_LOCAL_MEM_ADDR:
                first_lmem_addr_o.write(addr_offset);
                first_lmem_data_o.write(ioc_data_i.read());
                first_lmem_wr_o.write(1);
                break;

            case SECOND_LOCAL_MEM_ADDR:
                second_lmem_addr_o.write(addr_offset);
                second_lmem_data_o.write(ioc_data_i.read());
                second_lmem_wr_o.write(1);
                break;

            case THIRD_LOCAL_MEM_ADDR:
                third_lmem_addr_o.write(addr_offset);
                third_lmem_data_o.write(ioc_data_i.read());
                third_lmem_wr_o.write(1);
                break;

            case FOURTH_LOCAL_MEM_ADDR:
                fourth_lmem_addr_o.write(addr_offset);
                fourth_lmem_data_o.write(ioc_data_i.read());
                fourth_lmem_wr_o.write(1);
                break;

            case FIFTH_LOCAL_MEM_ADDR:
                fifth_lmem_addr_o.write(addr_offset);
                fifth_lmem_data_o.write(ioc_data_i.read());
                fifth_lmem_wr_o.write(1);
                break;
            }

            wait();

            busy_o.write(0);

            break;

        case CONTROL_UNIT:

            if (cu_rd_i.read()) {
                busy_o.write(1);
                first_cpu_busy_o.write(1);
                second_cpu_busy_o.write(1);
                third_cpu_busy_o.write(1);
                fourth_cpu_busy_o.write(1);
                fifth_cpu_busy_o.write(1);

                base_addr = (cu_addr_i.read() / 1000) * 1000;
                addr_offset = cu_addr_i.read() % 1000;
                value = 0;
                switch (base_addr) {
                case INPUT_DATA_ADDR:
                    value = input_data[addr_offset];
                    break;
                case LAYERS_AMOUNT_ADDR:
                    value = layers_amount;
                    break;
                case LAYERS_NEURONS_AMOUNT_ADDR:
                    value = layers_neurons_amount[addr_offset];
                    break;
                case NEURONS_OFFSET_ADDR:
                    value = neurons_offset;
                    break;
                case ACTIVATION_DATA_ADDR:
                    value = activations[addr_offset];
                    break;
                }

                cu_data_o.write(value);

                wait();

                busy_o.write(0);
            }

            break;
        }
    }
}
