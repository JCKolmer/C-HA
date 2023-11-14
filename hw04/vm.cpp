#include "vm.h"

#include <iostream>
#include <limits>

#include "util.h"


namespace vm {


vm_state create_vm(bool debug) {
    vm_state state;

    // enable vm debugging
    state.debug = debug;


    register_instruction(state, "PRINT", [](vm_state& vmstate, const item_t /*arg*/) {
        std::cout << vmstate.stack.top() << std::endl;
        return true;
    });
    register_instruction(state, "LOAD_CONST" , [](vm_state& vmstate, const item_t /*arg*/) {
        // vmstate.stack.push(item_t);
        return true;
    });
    register_instruction(state, "EXIT" , [](vm_state& vmstate, const item_t /*arg*/) {
         if(vmstate.stack.size() < 1)
        {
            throw vm_stackfail{"zu wenig Elemente im Stack"};
        }
        return false;
    });
    register_instruction(state, "POP" , [](vm_state& vmstate, const item_t /*arg*/) {
        if(vmstate.stack.size() < 1)
        {
            throw vm_stackfail{"zu wenig Elemente im Stack"};
        }
        vmstate.stack.pop();
        return true;
    });
    register_instruction(state, "ADD" , [](vm_state& vmstate, const item_t /*arg*/) {
        if(vmstate.stack.size() < 2)
        {
            throw vm_stackfail{"zu wenig Elemente im Stack"};
        }
        auto tos1 = vmstate.stack.top();
        vmstate.stack.pop();
        auto tos2 = vmstate.stack.top();
        vmstate.stack.pop();
        auto ergebnis = tos1 + tos2;
         vmstate.stack.push(ergebnis);
        return true;
    });
     register_instruction(state, "DIV" , [](vm_state& vmstate, const item_t /*arg*/) {
        if(vmstate.stack.size() < 2)
        {
            throw vm_stackfail{"zu wenig Elemente im Stack"};
        }
        auto tos1 = vmstate.stack.top();
        vmstate.stack.pop();
        auto tos2 = vmstate.stack.top();
        vmstate.stack.pop();
        if(tos1 == 0)
        {
            throw div_by_zero("TOS ist 0");
        }
        auto ergebnis = tos2 / tos1;
         vmstate.stack.push(ergebnis);
        return true;
    });
    register_instruction(state, "EQ" , [](vm_state& vmstate, const item_t /*arg*/) {
        if(vmstate.stack.size() < 2)
        {
            throw vm_stackfail{"zu wenig Elemente im Stack"};
        }
        auto tos1 = vmstate.stack.top();
        vmstate.stack.pop();
        auto tos2 = vmstate.stack.top();
        vmstate.stack.pop();
        if(tos1 == tos2)
        {
            vmstate.stack.push(1);
        }
        else 
        {
            vmstate.stack.push(0);
        }
        return true;
    });
    register_instruction(state, "NEQ" , [](vm_state& vmstate, const item_t /*arg*/) {
        if(vmstate.stack.size() < 2)
        {
            throw vm_stackfail{"zu wenig Elemente im Stack"};
        }
        auto tos1 = vmstate.stack.top();
        vmstate.stack.pop();
        auto tos2 = vmstate.stack.top();
        vmstate.stack.pop();
        if(tos1 == tos2)
        {
            vmstate.stack.push(0);
        }
        else 
        {
            vmstate.stack.push(1);
        }
        return true;
    });
     register_instruction(state, "DUP" , [](vm_state& vmstate, const item_t /*arg*/) {
        if(vmstate.stack.size() < 1)
        {
            throw vm_stackfail{"zu wenig Elemente im Stack"};
        }
        auto tos = vmstate.stack.top();
        vmstate.stack.push(tos);
        return true;
    });
    register_instruction(state, "JMP" , [](vm_state& vmstate, const item_t /*arg*/) {
        
        return true;
    });
     register_instruction(state, "JMPZ" , [](vm_state& vmstate, const item_t /*arg*/) {
        if(vmstate.stack.size() < 1)
        {
            throw vm_stackfail{"zu wenig Elemente im Stack"};
        }
        return true;
    });
    register_instruction(state, "WRITE" , [](vm_state& vmstate, const item_t /*arg*/) {
         if(vmstate.stack.size() < 1)
        {
            throw vm_stackfail{"zu wenig Elemente im Stack"};
        }
        return true;
    });
     register_instruction(state, "WRITE_CHAR" , [](vm_state& vmstate, const item_t /*arg*/) {
         if(vmstate.stack.size() < 1)
        {
            throw vm_stackfail{"zu wenig Elemente im Stack"};
        }
        return true;
    });


    // TODO create instructions

    return state;
}


void register_instruction(vm_state& state, std::string_view name,
                          const op_action_t& action) {
    size_t op_id = state.next_op_id;
    state.next_op_id += 1;
    state.instruction_ids.insert({std::string (name), op_id});
    state.instruction_names.insert({op_id,std::string (name)});
    state.instruction_actions.insert({op_id, action});
    
    // TODO make instruction available to vm
}


code_t assemble(const vm_state& state, std::string_view input_program) {
    code_t code;

    // convert each line separately
    for (auto& line : util::split(input_program, '\n')) {

        auto line_words = util::split(line, ' ');

        // only support instruction and one argument
        if (line_words.size() >= 3) {
            throw invalid_instruction{std::string{"more than one instruction argument: "} + line};
        }

        // look up instruction id
        auto& op_name = line_words[0];
        auto find_op_id = state.instruction_ids.find(op_name);
        if (find_op_id == std::end(state.instruction_ids)) {
            throw invalid_instruction{std::string{"unknown instruction: "} + op_name};
        }
        op_id_t op_id = find_op_id->second;

        // parse the argument
        item_t argument{0};
        if (line_words.size() == 2) {
            argument = std::stoll(line_words[1]);
        }

        // and save the instruction to the code store
        code.emplace_back(op_id, argument);
    }

    return code;
}


std::tuple<item_t, std::string> run(vm_state& vm, const code_t& code) {
    // to help you debugging the code!
    if (vm.debug) {
        std::cout << "=== running vm ======================" << std::endl;
        std::cout << "disassembly of run code:" << std::endl;
        for (const auto &[op_id, arg] : code) {
            if (not vm.instruction_names.contains(op_id)) {
                std::cout << "could not disassemble - op_id unknown..." << std::endl;
                std::cout << "turning off debug mode." << std::endl;
                vm.debug = false;
                break;
            }
            std::cout << vm.instruction_names[op_id] << " " << arg << std::endl;
        }
        std::cout << "=== end of disassembly" << std::endl << std::endl;
    }

    // execution loop for the machine
    std::string output = "";
    while (true) {

        auto& [op_id, arg] = code[vm.pc];

        if (vm.debug) {
            std::cout << "-- exec " << vm.instruction_names[op_id] << " arg=" << arg << " at pc=" << vm.pc << std::endl;
        }

        // increase the program counter here so its value can be overwritten
        // by the instruction when it executes!
        vm.pc += 1;
        auto find_op_action = vm.instruction_actions.at(op_id);
        if(!find_op_action(vm,arg))
        {
            break;
        }
        if(vm.instruction_names.at(op_id) == "LOAD_CONST")
        {
            vm.stack.push(arg);
        }
        if(vm.instruction_names.at(op_id) == "JMP")
        {
            if(arg<(code.size()) && arg>=0)
            {
                vm.pc = arg;
            }
            else
            {
                throw vm_segfault{"PC out of bounds"};
            }
        }
        if(vm.instruction_names.at(op_id) == "JMPZ")
        {
            if((arg<(code.size()) && arg>=0))
            {
            auto tos1 = vm.stack.top();
            vm.stack.pop();
            if(tos1 == 0)
            {
                  vm.pc = arg;
            }
            }
            else
               {
                  throw vm_segfault{"PC out of bounds"};
               }

        }
        if(vm.instruction_names.at(op_id) == "WRITE")
        {
            auto tos1 = vm.stack.top();
            output = output + std::to_string(tos1);
        }
        if(vm.instruction_names.at(op_id) == "WRITE_CHAR")
        {
            auto tos1 = vm.stack.top();
            output = output + char(tos1);
        }
        // TODO execute instruction and stop if the action returns false.
    }

    return {vm.stack.top(), output}; // TODO: return tuple(exit value, output text)
}


} // namespace vm
