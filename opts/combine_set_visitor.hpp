#ifndef BFC_COMBINE_SET_VISITOR_HPP
#define BFC_COMBINE_SET_VISITOR_HPP

#include "ast/mod.hpp"
#include "test_visitor.hpp"
#include "opt_seq_base_visitor.hpp"
#include "types.h"

namespace bfc {
namespace ast {

class combine_set_visitor : public opt_seq_base_visitor {

public:

    status visit(set &node) {
        // Only attempt to combine if there is a previous node
        if (!opt_seq.empty()) {
            // try to combine with the previous node if possible
            test_combine_set_visitor v;
            if (opt_seq.back().accept(v) == CONTINUE) {
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
            // try to combine with the previous node if possible
            test_combine_set_visitor v;
            if (opt_seq.back().accept(v) == CONTINUE) {
                // discard the previous node (undone by this set)
                opt_seq.pop_back();
            }
        }
        // copy the node
        return opt_seq_base_visitor::handle_set(node);
    }
    
    status visit(add &node) {
        // discard any zero value node
        if (node.value() == 0) {
            return CONTINUE;
        }
        // Only attempt to combine if there is a previous node
        if (!opt_seq.empty()) {
            // try to combine with the previous node if possible
            try_combine_set_inc_visitor v(node.offset(), node.value(), true);
            if (opt_seq.back().accept(v) == CONTINUE) {
                opt_seq.pop_back();
                opt_seq.emplace_back(new set(node.loc(), node.offset(), v.new_value()));
                return CONTINUE;
            }
        }
        // else make node copy
        return opt_seq_base_visitor::handle_add(node);
    }

    status visit(const add &node) {
        // discard any zero value node
        if (node.value() == 0) {
            return CONTINUE;
        }
        // Only attempt to combine if there is a previous node
        if (!opt_seq.empty()) {
            // try to combine with the previous node if possible
            try_combine_set_inc_visitor v(node.offset(), node.value(), true);
            if (opt_seq.back().accept(v) == CONTINUE) {
                opt_seq.pop_back();
                opt_seq.emplace_back(new set(node.loc(), node.offset(), v.new_value()));
                return CONTINUE;
            }
        }
        // else make node copy
        return opt_seq_base_visitor::handle_add(node);
    }

    status visit(sub &node) {
        // discard any zero value node
        if (node.value() == 0) {
            return CONTINUE;
        }
        // Only attempt to combine if there is a previous node
        if (!opt_seq.empty()) {
            // try to combine with the previous node if possible
            try_combine_set_inc_visitor v(node.offset(), node.value(), false);
            if (opt_seq.back().accept(v) == CONTINUE) {
                opt_seq.pop_back();
                opt_seq.emplace_back(new set(node.loc(), node.offset(), v.new_value()));
                return CONTINUE;
            }
        }
        // else make node copy
        return opt_seq_base_visitor::handle_sub(node);
    }

    status visit(const sub &node) {
        // discard any zero value node
        if (node.value() == 0) {
            return CONTINUE;
        }
        // Only attempt to combine if there is a previous node
        if (!opt_seq.empty()) {
            // try to combine with the previous node if possible
            try_combine_set_inc_visitor v(node.offset(), node.value(), false);
            if (opt_seq.back().accept(v) == CONTINUE) {
                opt_seq.pop_back();
                opt_seq.emplace_back(new set(node.loc(), node.offset(), v.new_value()));
                return CONTINUE;
            }
        }
        // else make node copy
        return opt_seq_base_visitor::handle_sub(node);
    }
    
private:

    class test_combine_set_visitor : public test_visitor {
        
        public:
            
            status visit(set &node) { return CONTINUE; }
            
            status visit(const set &node) { return CONTINUE; }
                
            status visit(add &node) { return CONTINUE; }
            
            status visit(const add &node) { return CONTINUE; }
            
            status visit(sub &node) { return CONTINUE; }
            
            status visit(const sub &node) { return CONTINUE; }
            
    };
    
    class try_combine_set_inc_visitor : public test_visitor {

        public:
            try_combine_set_inc_visitor(ptrdiff_t offset, bf_value val, bool isAdd) :
                isAdd(isAdd), next_off(offset),  next_val(val) {}

            bf_value new_value() {
                return new_val;
            }

            status visit(set &node) {
                if (node.offset() != next_off) {
                    return BREAK;
                }
                new_val = node.value();
                isAdd ? new_val += next_val : new_val -= next_val;
                return CONTINUE;
            }

            status visit(const set &node) {
                if (node.offset() != next_off) {
                    return BREAK;
                }
                new_val = node.value();
                isAdd ? new_val += next_val : new_val -= next_val;
                return CONTINUE;
            }

        private:
            bool isAdd;
            ptrdiff_t next_off;
            bf_value next_val;
            bf_value new_val;
    };

};

}
}

#endif /* !BFC_COMBINE_SET_VISITOR_HPP */
