#ifndef BFC_COMBINE_PTR_VISITOR_HPP
#define BFC_COMBINE_PTR_VISITOR_HPP

namespace bfc {
namespace ast {

class combine_ptr_visitor : public opt_base_visitor {

public:

    status visit(mov &node) {
        // discard any zero value node
        if (node.offset() == 0) {
            return CONTINUE;
        }
        // try to combine with the previous node if possible
        test_combine_ptr_visitor v(node.offset());
        node prev_node = opt_seq.back();
        if (prev_node.accept(v) == CONTINUE) {
            // discard the combined node if it is 0
            if (v.new_offset() == 0) {
                opt_seq.pop_back();
            }
            return CONTINUE;
        }
        // else make node copy
        return opt_base_visitor::handle_mov(node);
    }
    
    status visit(const mov &node) {
        // discard any zero value node
        if (node.offset() == 0) {
            return CONTINUE;
        }
        // try to combine with the previous node if possible
        test_combine_ptr_visitor v(node.offset());
        node prev_node = opt_seq.back();
        if (prev_node.accept(v) == CONTINUE) {
            // discard the combined node if it is 0
            if (v.new_offset() == 0) {
                opt_seq.pop_back();
            }
            return CONTINUE;
        }
        // else make node copy
        return opt_base_visitor::handle_mov(node);
    }
    
private:

    class test_combine_ptr_visitor : public test_visitor {
        
        public:
            test_combine_inc_visitor(ptrdiff_t offset) :
                next_off(offset) {}
                
            ptrdiff_t new_offset() {
                return new_off;
            }
                
            status visit(mov &node) {
                new_off = next_off + node.offset();
                node.offset(new_off);
            }
            
            status visit(const mov &node) {
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
