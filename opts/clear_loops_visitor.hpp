#ifndef BFC_CLEAR_LOOPS_VISITOR_HPP
#define BFC_CLEAR_LOOPS_VISITOR_HPP

#include "ast/mod.hpp"
#include "test_visitor.hpp"
#include "opt_seq_base_visitor.hpp"

namespace bfc {
namespace ast {

class clear_loops_visitor : public opt_seq_base_visitor {

public:
    
    status visit(loop &node) {
        if (node.size() == 1) {
            // test if the inner node matches a clear loop
            test_inner_sequence_visitor v;
            if (node.seq::accept(v) == CONTINUE) {
                // replace loop, just set cell to 0
                opt_seq.emplace_back(new set(node.loc(), 0, 0));
                return CONTINUE;                
            }
        }
        // else optimize inner sequence
        opt_seq_base_visitor::handle_loop(node);
    }
    
    status visit(const loop &node) {
        if (node.size() == 1) {
            // test if the inner node matches a clear loop
            test_inner_sequence_visitor v;
            if (node.seq::accept(v) == CONTINUE) {
                // replace loop, just set cell to 0
                opt_seq.emplace_back(new set(node.loc(), 0, 0));
                return CONTINUE;                
            }
        }
        // else optimize inner sequence
        opt_seq_base_visitor::handle_loop(node);
    }
    
private:

    class test_inner_sequence_visitor : public test_visitor {
        
        public: 
            status visit(add &node) {
                return (node.value() == 1 && node.offset() == 0) ? CONTINUE : BREAK;
            }
            status visit(const add &node) {
                return (node.value() == 1 && node.offset() == 0) ? CONTINUE : BREAK;
            }
            status visit(sub &node) {
                return (node.value() == 1 && node.offset() == 0) ? CONTINUE : BREAK;
            }
            status visit(const sub &node) {
                return (node.value() == 1 && node.offset() == 0) ? CONTINUE : BREAK;
            }
            
    };

};

}
}

#endif /* !BFC_CLEAR_LOOPS_VISITOR_HPP */
