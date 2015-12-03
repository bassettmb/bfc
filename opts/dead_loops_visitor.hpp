#ifndef BFC_DEAD_LOOPS_VISITOR_HPP
#define BFC_DEAD_LOOPS_VISITOR_HPP

namespace bfc {
namespace ast {

class dead_loops_visitor : public opt_seq_base_visitor {

public:

    status visit(program &node) {
        // create sequence starting with SET(0)
        // programs start with cells set to zero
        // make this explicit to remove dead loops at the start
        seq temp_seq;
        set base(node.loc(), 0, 0);
        node temp_node(base);
        temp_seq.push_back(temp_node);
        
        // swap our optimized sequence for the empty one
        opt_seq.swap(temp_seq);
        // optimize the node's inner sequence
        node.accept(*this);
        // remove the redundant set node from the start
        opt_seq.pop_front();
        
        // create a new node from the optimized sequence
        program base(node.loc(), opt_seq);
        node cur_node(base);
        // swap back the old optimized sequence
        opt_seq.swap(temp_seq);
        // add the new node to the sequence
        opt_seq.push_back(node);
        return CONTINUE;
    }
    
    status visit(const program &node) {
        // create sequence starting with SET(0)
        // programs start with cells set to zero
        // make this explicit to remove dead loops at the start
        seq temp_seq;
        set base(node.loc(), 0, 0);
        node temp_node(base);
        temp_seq.push_back(temp_node);
        
        // swap our optimized sequence for the empty one
        opt_seq.swap(temp_seq);
        // optimize the node's inner sequence
        node.accept(*this);
        // remove the redundant set node from the start
        opt_seq.pop_front();
        
        // create a new node from the optimized sequence
        program base(node.loc(), opt_seq);
        node cur_node(base);
        // swap back the old optimized sequence
        opt_seq.swap(temp_seq);
        // add the new node to the sequence
        opt_seq.push_back(node);
        return CONTINUE;
    }
    
    status visit(loop &node) {
        // test if previous node make this a dead loop
        test_dead_loop_visitor v;
        node prev_node = opt_seq.back();
        if (prev_node.accept(v) == CONTINUE) {
            // no-op to remove this loop from the sequence
            return CONTINUE;
        }
        // else optimize inner sequence
        return opt_base_visitor::handle_loop(node);
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
        return opt_base_visitor::handle_loop(node);
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
            status visit(loop &node) { return CONTINUE; }
            status visit(const loop &node) { return CONTINUE; }
            
    };

};

}
}

#endif /* !BFC_DEAD_LOOPS_VISITOR_HPP */
