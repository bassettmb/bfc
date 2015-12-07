#ifndef BFC_OPT_PROGRAM_VISITOR_HPP
#define BFC_OPT_PROGRAM_VISITOR_HPP

#include <stdexcept>
#include <string>
#include <vector>
#include "ast/visitor.hpp"
#include "opts/opt_seq_base_visitor"

namespace bfc {
namespace ast {

class opt_program_visitor : public visitor {
    
    using error = std::runtime_error;
    using string = std::string;
    using vector = std::vector<opt_seq_base_visitor>;

public:

    opt_program_visitor(vector vec) : opts(std::move(vec)) {}

    node result(void) {
        return opt_program;
    }

    status visit(program &node) {
        node res;
        for (const auto &elem : opts) {
            res.accept(elem);
            res = elem.result();
        }
            
  }
    }
    
    status visit(const program &node) {
        // TODO launch optimizations here
    }
    
    status visit(set &node) {
       throw create_type_err("SET");
    }
    
    status visit(const set &node) {
        throw create_type_err("SET);
    }
    
    status visit(add &node) {
        throw create_type_err("ADD");
    }
    
    status visit(const add &node) {
        throw create_type_err("ADD");
    }
    
    status visit(sub &node) {
        throw create_type_err("SUB");
    }
    
    status visit(const sub &node) {
        throw create_type_err("SUB");
    }
    
    status visit(mov &node) {
        throw create_type_err("MOV");
    }
    
    status visit(const mov &node) {
        throw create_type_err("MOV");
    }
    
    status visit(mul &node) {
        throw create_type_err("MUL");      
    }
    
    status visit(const mul &node) {
        throw create_type_err("MUL");
    }
    
    status visit(loop &node) {
        throw create_type_err("LOOP");
    }
    
    status visit(const loop &node) {
        throw create_type_err("LOOP");
    }
    
    status visit(read &node) {
        throw create_type_err("READ");
    }
    
    status visit(const read &node) {
        throw create_type_err("READ");
    }
    
    status visit(write &node) {
        throw create_type_err("WRITE");
    }
    
    status visit(const write &node) {
        throw create_type_err("WRITE");
    }
    
private:

    // node containing optimized program
    node opt_program;
    
    // list of optimizers to run
    vector opts;
    
    // function to create an error message
    error create_type_err(const string &info) {
        return error("Program optimizer used on improper node type: " + info);
    }

};

}
}

#endif /* !BFC_OPT_PROGRAM_VISITOR_HPP */
