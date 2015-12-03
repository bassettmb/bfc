#ifndef BFC_OPT_PROGRAM_VISITOR_HPP
#define BFC_OPT_PROGRAM_VISITOR_HPP

namespace bfc {
namespace ast {

class opt_program_visitor : public visitor {

public:

    node result(void) {
        return opt_program;
    }

    status visit(program &node) {
        // TODO launch optimizations here
    }
    
    status visit(const program &node) {
        // TODO launch optimizations here
    }
    
    status visit(set &node) {
        // TODO throw error here
    }
    
    status visit(const set &node) {
        // TODO throw error here
    }
    
    status visit(add &node) {
        // TODO throw error here
    }
    
    status visit(const add &node) {
        // TODO throw error here
    }
    
    status visit(sub &node) {
        // TODO throw error here
    }
    
    status visit(const sub &node) {
        // TODO throw error here
    }
    
    status visit(mov &node) {
        // TODO throw error here
    }
    
    status visit(const mov &node) {
        // TODO throw error here
    }
    
    status visit(mul &node) {
        // TODO throw error here       
    }
    
    status visit(const mul &node) {
        // TODO throw error here
    }
    
    status visit(loop &node) {
        // TODO throw error here
    }
    
    status visit(const loop &node) {
        // TODO throw error here
    }
    
    status visit(read &node) {
        // TODO throw error here
    }
    
    status visit(const read &node) {
        // TODO throw error here
    }
    
    status visit(write &node) {
        // TODO throw error here
    }
    
    status visit(const write &node) {
        // TODO throw error here
    }
    
private:

    // node containing optimized program
    node opt_program;

};

}
}

#endif /* !BFC_OPT_PROGRAM_VISITOR_HPP */
