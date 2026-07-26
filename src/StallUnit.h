//
// Created by zhoue on 2026/7/24.
//

#ifndef RISCV_CPU_STALLUNIT_H
#define RISCV_CPU_STALLUNIT_H
#include "ProgramCounter.h"
struct EnableSignals {
    int FetchEnable;
    int DecodeEnable;
    int ExecuteEnable;
    int MemoryEnable;
    int WriteBackEnable;
};

class StallUnit {
public:
    StallUnit() {}
    int checkStall(ID_EX_data& EX_command, uint32_t current_command_src_addr){
        if (EX_command.Memory_op != NO_MEMORY_OP and EX_command.rd_addr == current_command_src_addr){
            cout<<"STALL DETECTED"<<endl;
            return 1;
        }
        else {
            return 0;
        }
    }

    void SetStall(ProgramCounter& program_counter, Decoder& decoder) {
        if (decoder.insert_bubble == 0) {
            program_counter.enable = 0;
            decoder.insert_bubble = 1;
            cout<<"DECODER INSRT BUBBLE "<<decoder.insert_bubble<<endl;
        }
    }

    void ExitStall(ProgramCounter& program_counter,Decoder& decoder) {
        if (decoder.insert_bubble == 1) {
            program_counter.enable = 1;
            decoder.insert_bubble = 0;
            cout<<"Stall END"<<endl;
        }
    }

};
#endif //RISCV_CPU_STALLUNIT_H
