#ifndef BFC_COMBINE_PTR_VISITOR_HPP
#define BFC_COMBINE_PTR_VISITOR_HPP

namespace bfc {
namespace ast {

class combine_ptr_visitor : public opt_seq_base_visitor {

public:

    status visit(mov &node) {
        // discard any zero value node
        if (node.offset() == 0) {
            return CONTINUE;
        }
        // Only attempt to combine if there is a previous node
        if (!opt_seq.empty()) {
            node prev_node = opt_seq.back();
            // try to combine with the previous node if possible
            try_combine_ptr_visitor v(node.offset());
            if (prev_node.accept(v) == CONTINUE) {
                // discard the combined node if it is 0
                if (v.new_offset() == 0) {
                    opt_seq.pop_back();
                }
                return CONTINUE;
            }
        }
        // else just copy the node
        return opt_base_visitor::handle_mov(node);
    }
    
    status visit(const mov &node) {
        // discard any zero value node
        if (node.offset() == 0) {
            return CONTINUE;
        }
        // Only attempt to combine if there is a previous node
        if (!opt_seq.empty()) {
            node prev_node = opt_seq.back();
            // try to combine with the previous node if possible
            try_combine_ptr_visitor v(node.offset());
            if (prev_node.accept(v) == CONTINUE) {
                // discard the combined node if it is 0
                if (v.new_offset() == 0) {
                    opt_seq.pop_back();
                }
                return CONTINUE;
            }
        }
        // else just copy the node
        return opt_base_visitor::handle_mov(node);
    }
    
private:

    class try_combine_ptr_visitor : public test_visitor {
        
        public:
            try_combine_inc_visitor(ptrdiff_t offset) : next_off(offset) {}
                
            ptrdiff_t new_offset() {
                return new_off;
            }
                
            status visit(mov &node) {
                // Combine the next node offset into this node
                new_off = next_off + node.offset();
                node.offset(new_off);
            }
            
            status visit(const mov &node) {
                // Combine the next node offset into this node
                new_off = next_off + node.offset();
                node.offset(new_off);
            }
            
        private:
            ptrdiff_t next_off;
            ptrdiff_t new_off;
            
    };

};

}
}

#endif /* !BFC_COMBINE_PTR_VISITOR_HPP */
