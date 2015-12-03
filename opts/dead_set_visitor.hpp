#ifndef BFC_DEAD_SET_VISITOR_HPP
#define BFC_DEAD_SET_VISITOR_HPP

namespace bfc {
namespace ast {

class dead_set_visitor : public opt_seq_base_visitor {

public:

    dead_set_visitor(void) : maybeProgramStart(true) {}
    
    status visit(set &node) {
        // only SET(0) can be dead
        if (node.value == 0) {
            // test if this is the first node of a program sequence
            if (maybeProgramStart && opt_seq.empty()) {
                // cells init to 0 on start, this set is dead
                return CONTINUE;
            }
            // mark that we are past the start of the program
            maybeProgramStart = false;
            // test if previous node makes this a dead loop
            test_dead_set_visitor v;
            node prev_node = opt_seq.back();
            if (prev_node.accept(v) == CONTINUE) {
                // no-op to remove this loop from the sequence
                return CONTINUE;
            }
        }
        // else copy the set
        return opt_seq_base_visitor::handle_loop(node);
    }
    
    status visit(const loop &node) {
        // only SET(0) can be dead
        if (node.value == 0) {
            // test if this is the first node of a program sequence
            if (maybeProgramStart && opt_seq.empty()) {
                // cells init to 0 on start, this set is dead
                return CONTINUE;
            }
            // mark that we are past the start of the program
            maybeProgramStart = false;
            // test if previous node makes this a dead loop
            test_dead_set_visitor v;
            node prev_node = opt_seq.back();
            if (prev_node.accept(v) == CONTINUE) {
                // no-op to remove this loop from the sequence
                return CONTINUE;
            }
        }
        // else copy the set
        return opt_seq_base_visitor::handle_loop(node);
    }
    
private:

    bool maybeProgramStart;

    class test_dead_set_visitor : public visitor {
        
        public:           
            // Loops only terminate when the current cell reaches 0
            // Thus SET(0) following loops are dead
            status visit(loop &node) { return CONTINUE; }
            status visit(const loop &node) { return CONTINUE; }
            
    };

};

}
}

#endif /* !BFC_DEAD_SET_VISITOR_HPP */
