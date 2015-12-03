#ifndef BFC_DEAD_LOOPS_VISITOR_HPP
#define BFC_DEAD_LOOPS_VISITOR_HPP

namespace bfc {
namespace ast {

class dead_loops_visitor : public opt_seq_base_visitor {

public:
    
    status visit(loop &node) {
        // test if previous node make this a dead loop
        test_dead_loop_visitor v;
        node prev_node = opt_seq.back();
        if (prev_node.accept(v) == CONTINUE) {
            // no-op to remove this loop from the sequence
            return CONTINUE;
        }
        // else optimize inner sequence
        return opt_seq_base_visitor::handle_loop(node);
    }
    
    status visit(const loop &node) {
        // test if previous node make this a dead loop
        test_dead_loop_visitor v;
        node prev_node = opt_seq.back();
        if (prev_node.accept(v) == CONTINUE) {
            // no-op to remove this loop from the sequence
            return CONTINUE;
        }
        // else optimize inner sequence
        return opt_seq_base_visitor::handle_loop(node);
    }
    
private:

    class test_dead_loop_visitor : public visitor {
        
        public: 
            status visit(set &node) {
                return (node.value() == 0 && node.offset() == 0) ? CONTINUE : BREAK;
            }
            status visit(const set &node) {
                return (node.value() == 0 && node.offset() == 0) ? CONTINUE : BREAK;
            }
            
            // Loops only terminate when the current cell reaches 0
            // Thus loops following loops are dead
            status visit(loop &node) { return CONTINUE; }
            status visit(const loop &node) { return CONTINUE; }
            
    };

};

}
}

#endif /* !BFC_DEAD_LOOPS_VISITOR_HPP */
