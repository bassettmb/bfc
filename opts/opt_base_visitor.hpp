#ifndef BFC_OPT_BASE_VISITOR_HPP
#define BFC_OPT_BASE_VISITOR_HPP

namespace bfc {
namespace ast {

class opt_base_visitor : visitor {

public:

    seq result(void) {
        return opt_seq;
    }

    virtual status visit(program &node) {
        return handle_program(node);
    }
    
    virtual status visit(const program &node) {
        return handle_program(node);
    }
    
    virtual status visit(add &node) {
        return handle_add(node);
    }
    
    virtual status visit(const add &node) {
        return handle_add(node);
    }
    
    virtual status visit(sub &node) {
        return handle_sub(node);
    }
    
    virtual status visit(const sub &node) {
        return handle_sub(node);
    }
    
    virtual status visit(mov &node) {
        return handle_mov(node);
    }
    
    virtual status visit(const mov &node) {
        return handle_mov(node);
    }
    
    virtual status visit(mul &node) {
        return handle_mul(node);        
    }
    
    virtual status visit(const mul &node) {
        return handle_mul(node);
    }
    
    virtual status visit(loop &node) {
        return handle_loop(node);
    }
    
    virtual status visit(const loop &node) {
        return handle_loop(node);
    }
    
    virtual status visit(read &node) {
        return handle_read(node);
    }
    
    virtual status visit(const read &node) {
        return handle_read(node);
    }
    
    virtual status visit(write &node) {
        return handle_write(node);
    }
    
    virtual status visit(const write &node) {
        return handle_write(node);
    }
    
protected:

    status handle_program(program &node) {
        // create an empty sequence
        seq temp_seq;
        // swap our optimized sequence for the empty one
        opt_seq.swap(temp_seq);
        // optimize the node's inner sequence
        node.accept(*this);
        // create a new node from the optimized sequence
        program base(node.loc(), opt_seq);
        node cur_node(base);
        // swap back the old optimized sequence
        opt_seq.swap(temp_seq);
        // add the new node to the sequence
        opt_seq.push_back(node);
        return CONTINUE;
    }
    status handle_program(const program &node) {
        // create an empty sequence
        seq temp_seq;
        // swap our optimized sequence for the empty one
        opt_seq.swap(temp_seq);
        // optimize the node's inner sequence
        node.accept(*this);
        // create a new node from the optimized sequence
        program base(node.loc(), opt_seq);
        node cur_node(base);
        // swap back the old optimized sequence
        opt_seq.swap(temp_seq);
        // add the new node to the sequence
        opt_seq.push_back(node);
        return CONTINUE;
    }
    status handle_add(add &node) {
        add base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    status handle_add(const add &node) {
        add base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    status handle_sub(sub &node) {
        sub base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    status handle_sub(const sub &node) {
        sub base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    status handle_mul(mul &node) {
        mul base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    status handle_mul(const mul &node) {
        mul base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    status handle_mov(mov &node) {
        mov base(node.loc(), node.offset());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    status handle_mov(const mov &node) {
        mov base(node.loc(), node.offset());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    status handle_loop(loop &node) {
        // create an empty sequence
        seq temp_seq;
        // swap our optimized sequence for the empty one
        opt_seq.swap(temp_seq);
        // optimize the node's inner sequence
        node.accept(*this);
        // create a new node from the optimized sequence
        loop base(node.loc(), opt_seq);
        node cur_node(base);
        // swap back the old optimized sequence
        opt_seq.swap(temp_seq);
        // add the new node to the sequence
        opt_seq.push_back(node);
        return CONTINUE;
    }
    status handle_loop(const loop &node) {
        // create an empty sequence
        seq temp_seq;
        // swap our optimized sequence for the empty one
        opt_seq.swap(temp_seq);
        // optimize the node's inner sequence
        node.accept(*this);
        // create a new node from the optimized sequence
        loop base(node.loc(), opt_seq);
        node cur_node(base);
        // swap back the old optimized sequence
        opt_seq.swap(temp_seq);
        // add the new node to the sequence
        opt_seq.push_back(node);
        return CONTINUE;
    }
    status handle_read(read &node) {
        read base(node.loc(), node.offset());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    status handle_read(const read &node) {
        read base(node.loc(), node.offset());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    status handle_write(write &node) {
        write base(node.loc(), node.offset());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    status handle_write(const write &node) {
        write base(node.loc(), node.offset());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    
private:

    // optimized sequence of previous nodes visited
    seq opt_seq;

};

}
}

#endif /* !BFC_OPT_BASE_VISITOR_HPP */
