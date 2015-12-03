#ifndef BFC_COMBINE_SET_VISITOR_HPP
#define BFC_COMBINE_SET_VISITOR_HPP

namespace bfc {
namespace ast {

class combine_set_visitor : public opt_seq_base_visitor {

public:

    status visit(set &node) {
        // Only attempt to combine if there is a previous node
        if (!opt_seq.empty()) {
            node prev_node = opt_seq.back();
            // try to combine with the previous node if possible
            test_combine_set_visitor v;
            if (prev_node.accept(v) == CONTINUE) {
                // discard the previous node (undone by this set)
                opt_seq.pop_back();
            }
        }
        // copy the node
        return opt_seq_base_visitor::handle_set(node);
    }
    
    status visit(const set &node) {
        // Only attempt to combine if there is a previous node
        if (!opt_seq.empty()) {
            node prev_node = opt_seq.back();
            // try to combine with the previous node if possible
            test_combine_set_visitor v;
            if (prev_node.accept(v) == CONTINUE) {
                // discard the previous node (undone by this set)
                opt_seq.pop_back();
            }
        }
        // copy the node
        return opt_seq_base_visitor::handle_set(node);
    }
    
private:

    class test_combine_set_visitor : public test_visitor {
        
        public:
            
            status visit(set &node) { return CONTINUE; }
            
            status visit(const add &set) { return CONTINUE; }
                
            status visit(add &node) { return CONTINUE; }
            
            status visit(const add &node) { return CONTINUE; }
            
            status visit(sub &node) { return CONTINUE; }
            
            status visit(const sub &node) { return CONTINUE; }
            
    };

};

}
}

#endif /* !BFC_COMBINE_SET_VISITOR_HPP */
