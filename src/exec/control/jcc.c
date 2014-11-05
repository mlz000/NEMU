#include "exec/helper.h"

#define DATA_BYTE 1
#include "jcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jcc-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;
//jo
make_helper(jo_r_v) {
	return (suffix == 'l' ? jo_r_l(eip) : jo_r_w(eip));
}
//jno
make_helper(jno_r_v) {
	return (suffix == 'l' ? jno_r_l(eip) : jno_r_w(eip));
}
//jb
make_helper(jb_r_v) {
	return (suffix == 'l' ? jb_r_l(eip) : jb_r_w(eip));
}
//jae
make_helper(jae_r_v) {
	return (suffix == 'l' ? jae_r_l(eip) : jae_r_w(eip));
}
//je
make_helper(je_r_v) {
	return (suffix == 'l' ? je_r_l(eip) : je_r_w(eip));
}
//jne
make_helper(jne_r_v) {
	return (suffix == 'l' ? jne_r_l(eip) : jne_r_w(eip));
}
//jbe
make_helper(jbe_r_v) {
	return (suffix == 'l' ? jbe_r_l(eip) : jbe_r_w(eip));
}
//ja
make_helper(ja_r_v) {
	return (suffix == 'l' ? ja_r_l(eip) : ja_r_w(eip));
}
//js
make_helper(js_r_v) {
	return (suffix == 'l' ? js_r_l(eip) : js_r_w(eip));
}
//jns
make_helper(jns_r_v) {
	return (suffix == 'l' ? jns_r_l(eip) : jns_r_w(eip));
}
//jp
make_helper(jp_r_v) {
	return (suffix == 'l' ? jp_r_l(eip) : jp_r_w(eip));
}
//jnp
make_helper(jnp_r_v) {
	return (suffix == 'l' ? jnp_r_l(eip) : jnp_r_w(eip));
}
//jl
make_helper(jl_r_v) {
	return (suffix == 'l' ? jl_r_l(eip) : jl_r_w(eip));
}
//jge
make_helper(jge_r_v) {
	return (suffix == 'l' ? jge_r_l(eip) : jge_r_w(eip));
}
//jle
make_helper(jle_r_v) {
	return (suffix == 'l' ? jle_r_l(eip) : jle_r_w(eip));
}
//jg
make_helper(jg_r_v) {
	return (suffix == 'l' ? jg_r_l(eip) : jg_r_w(eip));
}
//jmp
make_helper(jmp_r_v) {
	return (suffix == 'l' ? jmp_r_l(eip) : jmp_r_w(eip));
}
