#pragma once

#include <string>

enum mut_type {
    mut, 
    imm
};

enum my_type {
    mut_arr_seq, 
    imm_arr_seq, 
    mut_lst_seq, 
    imm_lst_seq
};

std::string ToString(my_type t) {
    switch (t) {
        case mut_arr_seq: {
            return "mut_arr_seq";
        }
        case imm_arr_seq: {
            return "imm_arr_seq";
        }
        case mut_lst_seq: {
            return "mut_lst_seq";
        }
        case imm_lst_seq: {
            return "imm_lst_seq";
        }
        default: {
            return "unknown_seq_type";
        }
    }
}

enum my_element_type {
    int_type, 
    double_type, 
    complex_type, 
    unknown_type
};

std::string ToString(my_element_type t) {
    switch (t) {
        case int_type: {
            return "int   ";
        }
        case double_type: {
            return "double";
        }
        case complex_type: {
            return "complex";
        }
        default: {
            return "unknown_element_type";
        }
    }
}