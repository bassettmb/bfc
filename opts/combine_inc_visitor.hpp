#ifndef BFC_COMBINE_INC_VISITOR_HPP
#define BFC_COMBINE_INC_VISITOR_HPP

#include "ast/mod.hpp"
#include "ast/base.hpp"
#include "test_visitor.hpp"
#include "types.h"

namespace bfc { namespace ast {

class combine_inc_visitor : public opt_seq_base_visitor {

public:

    enum node_type {
        ADD = 0,
        SUB
    };

    status visit(add &node) {
        // discard any zero value node
        if (node.value() == 0) {
            return CONTINUE;
        }
        // Only attempt to combine if there is a previous node
        if (!opt_seq.empty()) {
            // try to combine with the previous node if possible
            try_combine_inc_visitor v(node.offset(), node.value(), true);
            if (opt_seq.back().accept(v) == CONTINUE) {
                opt_seq.pop_back();
                // discard the combined node if it is 0
                if (v.new_value() != 0) {
                    if (v.type() == ADD) {
                        opt_seq.emplace_back(new add(node.loc(), node.offset(), v.new_value()));
                    } else {
                        opt_seq.emplace_back(new sub(node.loc(), node.offset(), v.new_value()));
                    }
                }
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
            try_combine_inc_visitor v(node.offset(), node.value(), true);
            if (opt_seq.back().accept(v) == CONTINUE) {
                opt_seq.pop_back();
                // discard the combined node if it is 0
                if (v.new_value() != 0) {
                    if (v.type() == ADD) {
                        opt_seq.emplace_back(new add(node.loc(), node.offset(), v.new_value()));
                    } else {
                        opt_seq.emplace_back(new sub(node.loc(), node.offset(), v.new_value()));
                    }
                }
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
            try_combine_inc_visitor v(node.offset(), node.value(), false);
            if (opt_seq.back().accept(v) == CONTINUE) {
                opt_seq.pop_back();
                // discard the combined node if it is 0
                if (v.new_value() != 0) {
                    if (v.type() == ADD) {
                        opt_seq.emplace_back(new add(node.loc(), node.offset(), v.new_value()));
                    } else {
                        opt_seq.emplace_back(new sub(node.loc(), node.offset(), v.new_value()));
                    }
                    return CONTINUE;
                }
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
            try_combine_inc_visitor v(node.offset(), node.value(), false);
            if (opt_seq.back().accept(v) == CONTINUE) {
                opt_seq.pop_back();
                // discard the combined node if it is 0
                if (v.new_value() != 0) {
                    if (v.type() == ADD) {
                        opt_seq.emplace_back(new add(node.loc(), node.offset(), v.new_value()));
                    } else {
                        opt_seq.emplace_back(new sub(node.loc(), node.offset(), v.new_value()));
                    }
                    return CONTINUE;
                }
                return CONTINUE;
            }
        }
        // else make node copy
        return opt_seq_base_visitor::handle_sub(node);
    }

private:

    class try_combine_inc_visitor : public test_visitor {

        public:
            try_combine_inc_visitor(ptrdiff_t offset, bf_value val, bool isAdd) :
                isAdd(isAdd), next_off(offset),  next_val(val) {}

            bf_value new_value() {
                return new_val;
            }

            node_type type() {
                return this_type;
            }

            status visit(add &node) {
                if (node.offset() != next_off) {
                    return BREAK;
                }
                new_val = node.value();
                isAdd ? new_val += next_val : new_val -= next_val;
                this_type = ADD;
                return CONTINUE;
            }

            status visit(const add &node) {
                if (node.offset() != next_off) {
                    return BREAK;
                }
                new_val = node.value();
                isAdd ? new_val += next_val : new_val -= next_val;
                this_type = ADD;
                return CONTINUE;
            }

            status visit(sub &node) {
                if (node.offset() != next_off) {
                    return BREAK;
                }
                new_val = node.value();
                isAdd ? new_val -= next_val : new_val += next_val;
                this_type = SUB;
                return CONTINUE;
            }

            status visit(const sub &node) {
                if (node.offset() != next_off) {
                    return BREAK;
                }
                new_val = node.value();
                isAdd ? new_val -= next_val : new_val += next_val;
                this_type = SUB;
                return CONTINUE;
            }

        private:
            bool isAdd;
            ptrdiff_t next_off;
            bf_value next_val;
            bf_value new_val;
            node_type this_type;
    };

};

}
}

#endif /* !BFC_COMBINE_INC_VISITOR_HPP */
