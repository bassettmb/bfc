#ifndef BFC_OPT_VISITORs_HPP
#define BFC_OPT_VISITORS_HPP

namespace bfc {
namespace ast {

class combine_visitor {

public:

    seq result(void) {
        return opt_seq;
    }

    status visit(program &node) {
        // create new optimizing visitor
        combine_visitor vis();
        // optimize the inner sequence
        node.accept(vis);
        // create a new node from the optimized sequence
        program base(node.loc(), vis.result());
        node cur_node(base);
        opt_seq.push_back(node);
        prev_type = PROGRAM;
        return CONTINUE;
    }
    
    status visit(const program &node) {
        // create new optimizing visitor
        combine_visitor vis();
        // optimize the inner sequence
        node.accept(vis);
        // create a new node from the optimized sequence
        program base(node.loc(), vis.result());
        node cur_node(base);
        opt_seq.push_back(node);
        prev_type = PROGRAM;
        return CONTINUE;
    }
    
    status visit(add &node) {
        if (prev_type == ADD || prev_type == SUB) {
            node prev_node = opt_seq.back();
            if (prev_node.get().offset() == node.offset()) {
                if (prev_type == ADD) {
                    bf_value val = prev_node.get().value() + node.value();
                    prev_node.get().value(val);
                } else {
                    bf_value val = prev_node.get().value() - node.value();
                    prev_node.get().value(val);
                }            
                return CONTINUE;
            }
        }
        // else
        add base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        prev_type = ADD;
        return CONTINUE;
    }
    
    status visit(const add &node) {
        if (prev_type == ADD || prev_type == SUB) {
            node prev_node = opt_seq.back();
            if (prev_node.get().offset() == node.offset()) {
                if (prev_type == ADD) {
                    bf_value val = prev_node.get().value() + node.value();
                    prev_node.get().value(val);
                } else {
                    bf_value val = prev_node.get().value() - node.value();
                    prev_node.get().value(val);
                }            
                return CONTINUE;
            }
        }
        // else
        add base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        prev_type = ADD;
        return CONTINUE;
    }
    
    status visit(sub &node) {
        if (prev_type == ADD || prev_type == SUB) {
            node prev_node = opt_seq.back();
            if (prev_node.get().offset() == node.offset()) {
                if (prev_type == SUB) {
                    bf_value val = prev_node.get().value() + node.value();
                    prev_node.get().value(val);
                } else {
                    bf_value val = prev_node.get().value() - node.value();
                    prev_node.get().value(val);
                }            
                return CONTINUE;
            }
        }
        // else
        add base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        prev_type = ADD;
        return CONTINUE;
    }
    
    status visit(const sub &node) {
        if (prev_type == ADD || prev_type == SUB) {
            node prev_node = opt_seq.back();
            if (prev_node.get().offset() == node.offset()) {
                if (prev_type == SUB) {
                    bf_value val = prev_node.get().value() + node.value();
                    prev_node.get().value(val);
                } else {
                    bf_value val = prev_node.get().value() - node.value();
                    prev_node.get().value(val);
                }            
                return CONTINUE;
            }
        }
        // else
        add base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        prev_type = ADD;
        return CONTINUE;
    }
    
    status visit(mov &node) {
        if (prev_type == MOV) {
            node prev_node = opt_seq.back();
            ptrdiff_t val = prev_node.get().offset() + node.offset();
            prev_node.get().offset(val);
        } else {
            mov base(node.loc(), node.offset());
            node cur_node(base);
            opt_seq.push_back(node);
            prev_type = MOV;
        }
        return CONTINUE;
    }
    
    status visit(const mov &node) {
        if (prev_type == MOV) {
            node prev_node = opt_seq.back();
            ptrdiff_t val = prev_node.get().offset() + node.offset();
            prev_node.get().offset(val);
        } else {
            mov base(node.loc(), node.offset());
            node cur_node(base);
            opt_seq.push_back(node);
            prev_type = MOV;
        }
        return CONTINUE;
    }
    
    status visit(mul &node) {
        mul base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        prev_type = MUL;
        return CONTINUE;        
    }
    
    status visit(const mul &node) {
        mul base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        prev_type = MUL;
        return CONTINUE;
    }
    
    virtual status visit(loop &node) {
        // create new optimizing visitor
        combine_visitor vis();
        // optimize the inner sequence
        node.accept(vis);
        // create a new node from the optimized sequence
        loop base(node.loc(), vis.result());
        node cur_node(base);
        opt_seq.push_back(node);
        prev_type = LOOP;
        return CONTINUE;
    }
    
    virtual status visit(const loop &node) {
        // create new optimizing visitor
        combine_visitor vis();
        // optimize the inner sequence
        node.accept(vis);
        // create a new node from the optimized sequence
        loop base(node.loc(), vis.result());
        node cur_node(base);
        opt_seq.push_back(node);
        prev_type = LOOP;
        return CONTINUE;
    }
    
    status visit(read &node) {
        read base(node.loc(), node.offset());
        node cur_node(base);
        opt_seq.push_back(node);
        prev_type = READ;
        return CONTINUE;
    }
    
    status visit(const read &node) {
        read base(node.loc(), node.offset());
        node cur_node(base);
        opt_seq.push_back(node);
        prev_type = READ;
        return CONTINUE;
    }
    
    status visit(write &node) {
        write base(node.loc(), node.offset());
        node cur_node(base);
        opt_seq.push_back(node);
        prev_type = WRITE;
        return CONTINUE;
    }
    
    status visit(const write &node) {
        write base(node.loc(), node.offset());
        node cur_node(base);
        opt_seq.push_back(node);
        prev_type = WRITE;
        return CONTINUE;
    }
    
private:

    // optimized sequence of previous nodes visited
    seq opt_seq;
    // type of last node visited
    node_type prev_type;

};

}
}

#endif /* !BFC_OPT_VISITORS_HPP */
