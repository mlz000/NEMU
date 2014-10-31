#ifndef __MOV_H__
#define __MOV_H__

make_helper(mov_i2r_b);
make_helper(mov_i2rm_b);
make_helper(mov_r2rm_b);
make_helper(mov_rm2r_b);
make_helper(mov_a2moffs_b);
make_helper(mov_moffs2a_b);
make_helper(pushi_b);

make_helper(mov_i2r_v);
make_helper(mov_i2rm_v);
make_helper(mov_r2rm_v);
make_helper(mov_rm2r_v);
make_helper(mov_a2moffs_v);
make_helper(mov_moffs2a_v);
make_helper(movsx_rmb2r_v);
make_helper(movsx_rmw2r_v);
make_helper(movzx_rmb2r_v);
make_helper(movzx_rmw2r_v);
make_helper(pushr_v);
make_helper(pushm_v);
make_helper(pushi_v);
make_helper(popr_v);
make_helper(popm_v);

make_helper(leave_v);
#endif
