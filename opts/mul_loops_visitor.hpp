#ifndef BFC_MUL_LOOPS_VISITOR_HPP
#define BFC_MUL_LOOPS_VISITOR_HPP

namespace bfc {
namespace ast {

class mul_loops_visitor : public opt_seq_base_visitor {
    
    using map = std::map<ptrdiff_t, bf_value>;

public:
    
    status visit(loop &node) {
        // test if the inner sequence contains only add, sub, and mov
        test_inner_seq_visitor v;
        if (node.accept(v) == CONTINUE) {
            // test if there is no net ptr movement
            if(v1.net_mov() == 0) {
                map changes = v1.net_changes();
                // test if first cell is decremented once each loop
                if (changes[0] == -1) {
                    // add nodes to represent the sequence
                    addMulOps(changes);
                    return CONTINUE;
                }
            }
        }
        // else optimize inner sequence
        opt_seq_base_visitor::handle_loop(node);
    }
    
    status visit(const loop &node) {
        // test if the inner sequence contains only add, sub, and mov
        test_inner_seq_visitor v;
        if (node.accept(v) == CONTINUE) {
            // test if there is no net ptr movement
            if(v1.net_mov() == 0) {
                map changes = v1.net_changes();
                // test if first cell is decremented once each loop
                if (changes[0] == -1) {
                    // add nodes to represent the sequence
                    addMulOps(changes);
                    return CONTINUE;
                }
            }
        }
        // else optimize inner sequence
        opt_seq_base_visitor::handle_loop(node);
    }
    
private:

    void addMulOps(map changes) {
        // remove the change to cell 0 from the map
        changes.erase(0);
        // create mul nodes for each change remaining in the map
        for (auto it = changes.begin(); it != changes.end(); ++it) {
            mul base(loc, it->first, it->second);
            node mul_node(base);
            opt_seq.push_back(mul_node);
        }
        // add a final node to clear cell 0
        set base(loc, it->first, it->second);
        node set_node(base);
        opt_seq.push_back(set_node);
    }

    class test_inner_seq_visitor : public test_visitor {
        
        public: 
            ptrdiff_t net_mov() {
                return cur_cell;
            }
            
            map net_changes() {
                return changes;
            }
            
            status visit(add &node) {
                ptrdiff_t mod_cell = cur_cell + node.offset();
                changes[mod_cell] = changes[mod_cell] + node.value();
                return CONTINUE;
            }
            
            status visit(const add &node) {
                ptrdiff_t mod_cell = cur_cell + node.offset();
                changes[mod_cell] = changes[mod_cell] + node.value();
                return CONTINUE;
            }
            
            status visit(sub &node) {
                ptrdiff_t mod_cell = cur_cell + node.offset();
                changes[mod_cell] = changes[mod_cell] - node.value();
                return CONTINUE;
            }
            
            status visit(const sub &node) {
                ptrdiff_t mod_cell = cur_cell + node.offset();
                changes[mod_cell] = changes[mod_cell] - node.value();
                return CONTINUE;
            }
            
            status visit(mov &node) {
                cur_cell += node.offset();
                return CONTINUE;
            }
            
            status visit(const mov &node) {
                cur_cell += node.offset();
                return CONTINUE;
            }
            
        private:
            ptrdiff_t cur_cell;
            map changes;
            
    };

};

}
}

#endif /* !BFC_MUL_LOOPS_VISITOR_HPP */
