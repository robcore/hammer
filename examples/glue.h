#ifndef HAMMER_EXAMPLES_GLUE__H
#define HAMMER_EXAMPLES_GLUE__H

#include <assert.h>
#include "../src/hammer.h"

///
// API Additions
///

#define H_RULE(rule, def) const HParser *rule = def
#define H_ARULE(rule, def) const HParser *rule = h_action(def, act_ ## rule)
#define H_VRULE(rule, def) const HParser *rule = \
  h_attr_bool(def, validate_ ## rule)
#define H_VARULE(rule, def) const HParser *rule = \
  h_attr_bool(h_action(def, act_ ## rule), validate_ ## rule)
#define H_AVRULE(rule, def) const HParser *rule = \
  h_action(h_attr_bool(def, validate_ ## rule), act_ ## rule)

const HParsedToken *act_ignore(const HParseResult *p);
const HParsedToken *act_index(int i, const HParseResult *p);
const HParsedToken *act_index0(const HParseResult *p);
const HParsedToken *act_flatten(const HParseResult *p);

const HParsedToken *h_token_flatten(HArena *arena, const HParsedToken *p);

void h_seq_snoc(HParsedToken *xs, const HParsedToken *x);
void h_seq_append(HParsedToken *xs, const HParsedToken *ys);

HParsedToken *h_make_token(HArena *arena, HTokenType type, void *value);
HParsedToken *h_make_token_seq(HArena *arena);

#define H_MAKE(TYP) \
  ((TYP *) h_arena_malloc(p->arena, sizeof(TYP)))

#define H_MAKE_TOKEN(TYP, VAL) \
  h_make_token(p->arena, TT_ ## TYP, VAL)

HParsedToken *h_carray_index(const HCountedArray *a, size_t i);
HParsedToken *h_seq_index(const HParsedToken *p, size_t i);
void *h_seq_index_user(HTokenType type, const HParsedToken *p, size_t i);

#define H_SEQ_INDEX(TYP, SEQ, IDX) \
  ((TYP *) h_seq_index_user(TT_ ## TYP, SEQ, IDX))

#define H_FIELD(TYP, IDX) \
  H_SEQ_INDEX(TYP, p->ast, IDX)

#endif
