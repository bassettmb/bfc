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
    
    virtual status visit(const program &node) {
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
    
    virtual status visit(add &node) {
        add base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    
    virtual status visit(const add &node) {
        add base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    
    virtual status visit(sub &node) {
        sub base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    
    virtual status visit(const sub &node) {
        sub base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    
    virtual status visit(mov &node) {
        mov base(node.loc(), node.offset());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    
    virtual status visit(const mov &node) {
        mov base(node.loc(), node.offset());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    
    virtual status visit(mul &node) {
        mul base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;        
    }
    
    virtual status visit(const mul &node) {
        mul base(node.loc(), node.offset(), node.value());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    
    virtual status visit(loop &node) {
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
    
    virtual status visit(const loop &node) {
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
    
    virtual status visit(read &node) {
        read base(node.loc(), node.offset());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    
    virtual status visit(const read &node) {
        read base(node.loc(), node.offset());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    
    virtual status visit(write &node) {
        write base(node.loc(), node.offset());
        node cur_node(base);
        opt_seq.push_back(node);
        return CONTINUE;
    }
    
    virtual status visit(const write &node) {
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
