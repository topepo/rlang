#ifndef RLANG_VECTOR_CHR_H
#define RLANG_VECTOR_CHR_H

#include <string.h>


static inline bool r_is_character(sexp* x) {
  return r_typeof(x) == STRSXP;
}

static inline sexp* r_chr_get(sexp* chr, r_size_t i) {
  return STRING_ELT(chr, i);
}
static inline void r_chr_poke(sexp* chr, r_size_t i, sexp* elt) {
  SET_STRING_ELT(chr, i, elt);
}

static inline sexp* r_nms_get(sexp* nms, r_size_t i) {
  if (nms == r_null) {
    static sexp* empty_str = NULL;
    if (!empty_str) empty_str = Rf_mkChar("");
    return empty_str;
  } else {
    return r_chr_get(nms, i);
  }
}

bool r_chr_has(sexp* chr, const char* c_string);


sexp* r_build_character(const char** strings, int n);

static inline sexp* r_string(const char* c_string) {
  return Rf_mkChar(c_string);
}
static inline bool r_is_r_string(sexp* x) {
  return r_typeof(x) == CHARSXP;
}

static inline sexp* r_scalar_chr(const char* c_string) {
  return Rf_mkString(c_string);
}
static inline sexp* r_as_scalar_chr(sexp* x) {
  return Rf_ScalarString(x);
}

static inline const char* r_c_string(sexp* scalar_chr) {
  return CHAR(r_chr_get(scalar_chr, 0));
}


sexp* chr_prepend(sexp* chr, sexp* r_string);
sexp* chr_append(sexp* chr, sexp* r_string);

static inline bool r_is_empty_string(sexp* str) {
  const char* c_str = CHAR(str);
  return strcmp(c_str, "") == 0;
}

static inline bool r_chr_has_empty_string_at(sexp* chr, r_size_t i) {
  return r_is_empty_string(r_chr_get(chr, i));
}

sexp* r_str_unserialise_unicode(sexp* r_string);


#endif