#ifndef BFC_CLEAR_LOOPS_VISITOR_HPP
#define BFC_CLEAR_LOOPS_VISITOR_HPP

namespace bfc {
namespace ast {

class clear_loops_visitor : public opt_base_visitor {

public:
    
    status visit(loop &node) {
        if (node.size() == 1) {
            // test if the inner node matches a clear loop
            test_inner_sequence_visitor v;
            if (node.accept(v) == CONTINUE) {
                // replace loop, just set cell to 0
                set base(node.loc(), 0, 0);
                node cur_node(base);
                opt_seq.push_back(cur_node);
                return CONTINUE;                
            }
        }
        // else optimize inner sequence
        opt_base_visitor:: // FIXME with protected method in base
    }
    
    status visit(const loop &node) {
        if (node.size() == 1) {
            // test if the inner node matches a clear loop
            test_inner_sequence_visitor v;
            if (node.accept(v) == CONTINUE) {
                // replace loop, just set cell to 0
                set base(node.loc(), 0, 0);
                node cur_node(base);
                opt_seq.push_back(cur_node);
                return CONTINUE;                
            }
        }
        // else optimize inner sequence
        opt_base_visitor:: // FIXME with protected method in base
    }
    
private:

    class test_inner_sequence_visitor : visitor {
        
        public: 
            status visit(program &node) { return BREAK; }
            status visit(const program &node) { return BREAK; }
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
            status visit(mov &node) { return BREAK; }
            status visit(const mov &node) { return BREAK; }
            status visit(mul &node) { return BREAK; }
            status visit(const mul &node) { return BREAK; }
            status visit(loop &node) { return BREAK; }
            status visit(const loop &node) { return BREAK; }
            status visit(read &node) { return BREAK; }
            status visit(const read &node) { return BREAK; }
            status visit(write &node) { return BREAK; }
            status visit(const write &node) { return BREAK; }
            
    }

};

}
}

#endif /* !BFC_CLEAR_LOOPS_VISITOR_HPP */
