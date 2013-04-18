#ifndef __HKDF_H
#define __HKDF_H

#include <stddef.h>
#include <stdint.h>
#include <openssl/hmac.h>

#define hkdf_max_length(md) EVP_MD_size(md) * 255

struct hkdf_ctx {
  const EVP_MD *md;
  HMAC_CTX prk_ctx;
  size_t hash_len;
  uint8_t *info;
  size_t info_len;
};

typedef struct hkdf_ctx hkdf_ctx;

void hkdf_init(hkdf_ctx *hkdf, const EVP_MD *md, uint8_t *salt, size_t salt_len, uint8_t *info, size_t info_len);
void hkdf_init_sha256(hkdf_ctx *hkdf, uint8_t *salt, size_t salt_len, uint8_t *info, size_t info_len);
void hkdf_update(hkdf_ctx *hkdf, uint8_t *ikm, size_t ikm_len);
int hkdf_final(hkdf_ctx *hkdf, uint8_t *out, size_t out_len);
void hkdf_free(hkdf_ctx *hkdf);

int hkdf(const EVP_MD *md, uint8_t *ikm, size_t ikm_len, uint8_t *salt, size_t salt_len, uint8_t *info, size_t info_len, uint8_t *okm, size_t okm_len);
int hkdf_sha256(uint8_t *ikm, size_t ikm_len, uint8_t *salt, size_t salt_len, uint8_t *info, size_t info_len, uint8_t *okm, size_t okm_len);

#endif
