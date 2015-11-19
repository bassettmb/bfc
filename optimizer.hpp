#ifndef BFC_OPTIMIZER_HPP
#define BFC_OPTIMIZER_HPP

#include "ast/ast.hpp"

namespace bfc {

class optimizer {
    
    public:
    
        optimizer(void) {}
        
        ast_seq optimize(ast_seq & program) {
            ast_base *prev = program.clone();
            ast_seq res = optimize_pass(program);
            while (*prev != res) {
                prev = res.clone();
                res = optimize_pass(res);
            }
            return res;
        }    

    private:
    
        ast_seq optimize_pass(ast_seq & ops) {
            ast_seq res = combine_inc_mov(ops);
            zero_loops_visitor(res);
            multiply_loops_visitor(res);
            
        }
        
        ast_seq combine_inc_mov(ast_seq & ops) {
            ast_seq res();
            combine_inc_mov_visistor v(res);
            status stat = ops.accept(v);
            if (stat == BREAK) {
                // error handling
            } else {
                return res;
            }
        }
    
};

class combine_inc_mov_visitor : public ast_visitor {
    
    public:
    
        combine_inc_mov_visitor(ast_seq & seq) : res(seq)
    
        status visit(ast_add &node) {
            
        }
        
    private:
    
        ast_seq res;
    
};

}
#endif /* !BFC_OPTIMIZER_HPP */
