dnl thunk template generator
m4_define([_m4_divert(STDOUT)], 1)
m4_divert_push([STDOUT])dnl
dnl
m4_define(m4_foru, [m4_cond(m4_eval($3>=$2), 1, [m4_for([$1],[$2],[$3],,[$4])])])dnl
m4_define(G_S0, [m4_foru(i, 1, $1,
        [aat[]i a[]i; \
m4_if($1, i,, [        ])])dnl
])dnl
m4_define(G_S1, [m4_foru(i, 1, $1,
        [aat[]m4_eval($1-i+1) a[]m4_eval($1-i+1); \
m4_if($1, i,, [        ])])dnl
])dnl
m4_define(G_I0, [m4_foru(i, 1, $1, [_a[]i[]m4_if($1, i,, [, ])])])dnl
m4_define(G_I1, [m4_foru(i, 1, $1, [_a[]m4_eval($1-i+1)[]m4_if($1, i,, [, ])])])dnl
m4_define(G_M, [m4_cond($3, 1, _P_)$1[]m4_cond($2, 1, _v)])dnl
m4_define(G_A, [m4_if($1, 0, [NULL, 0], [(UBYTE *)&_args, sizeof(_args)])])dnl
m4_define(THUNK,
[[#]define _THUNK[]G_M($1,$2,$3)(n, m4_cond($2, 0, [r, s, ])f, m4_foru(i, 1, $1,
  [t[]i, at[]i, aat[]i, c[]i, l[]i, ])z) \
m4_if($2, 1, void, r) f(m4_if($1, 0, void, [m4_foru(i, 1, $1, [t[]i a[]i[]m4_if($1, i,, [, ])])])) \
{ \
m4_cond($2, 0, [    uint32_t _ret; \
])dnl
m4_foru(i, 1, $1, [dnl
    _CNV(c[]i, at[]i, l[]i, i); \
])dnl
m4_if($1, 0,, [dnl
    struct { \
        G_S$3($1)dnl
    } PACKED _args = { G_I$3($1) }; \
])dnl
    m4_cond($2, 0, [_ret = ])__CALL(n, G_A($1), z); \
m4_cond(m4_eval($3==0&&$1>0), 1, [    __CSTK(sizeof(_args)); \
])dnl
m4_cond($2, 0, [    return s(r, _ret); \
])dnl
}dnl
])dnl