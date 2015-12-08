#ifndef BFC_MUL_LOOPS_VISITOR_HPP
#define BFC_MUL_LOOPS_VISITOR_HPP

#include <map>
#include "ast/mod.hpp"
#include "test_visitor.hpp"
#include "opt_seq_base_visitor.hpp"
#include "rts/types.h"
#include "source_loc.hpp"



namespace bfc {
namespace ast {

class mul_loops_visitor : public opt_seq_base_visitor {

    using map = std::map<ptrdiff_t, bf_value>;

public:

    status visit(loop &node) {
        // test if the inner sequence contains only add, sub, and mov
        test_inner_seq_visitor v;
        if (node.seq::accept(v) == CONTINUE) {
            // test if there is no net ptr movement
            if (v.net_mov() == 0) {
                map changes = v.net_changes();
                // test if first cell is decremented once each loop
                if (changes[0] == 255) { // -1 = 255 (unsigned 8bit vals)
                    // add nodes to represent the sequence
                    addMulOps(changes, node.loc());
                    return CONTINUE;
                }
            }
        }
        // else optimize inner sequence
        return opt_seq_base_visitor::handle_loop(node);
    }

    status visit(const loop &node) {
        // test if the inner sequence contains only add, sub, and mov
        test_inner_seq_visitor v;
        if (node.seq::accept(v) == CONTINUE) {
            // test if there is no net ptr movement
            if (v.net_mov() == 0) {
                map changes = v.net_changes();
                // test if first cell is decremented once each loop
                if (changes[0] == 255) { // -1 = 255 (unsigned 8bit vals)
                    // add nodes to represent the sequence
                    addMulOps(changes, node.loc());
                    return CONTINUE;
                }
            }
        }
        // else optimize inner sequence
        return opt_seq_base_visitor::handle_loop(node);
    }

private:

    void addMulOps(map changes, source_loc loc) {
        // remove the change to cell 0 from the map
        changes.erase(0);
        // create mul nodes for each change remaining in the map
        for (auto it = changes.begin(); it != changes.end(); ++it) {
            opt_seq.emplace_back(new mul(loc, it->first, it->second));
        }
        // add a final node to clear cell 0
        opt_seq.emplace_back(new set(loc, 0, 0));
    }

    class test_inner_seq_visitor : public test_visitor {

        public:
            test_inner_seq_visitor(void) : cur_cell(0){}

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
