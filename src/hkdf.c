#include <string.h>
#include "hkdf.h"

void hkdf_init(hkdf_ctx *hkdf, const EVP_MD *md, uint8_t *salt, size_t salt_len, uint8_t *info, size_t info_len) {
  hkdf->md = md;
  hkdf->hash_len = EVP_MD_size(md);
  hkdf->info = info;
  hkdf->info_len = info_len;

  HMAC_CTX_init(&hkdf->prk_ctx);
  HMAC_Init_ex(&hkdf->prk_ctx, salt, salt_len, md, NULL);
}

void hkdf_update(hkdf_ctx *hkdf, uint8_t *ikm, size_t ikm_len) {
  HMAC_Update(&hkdf->prk_ctx, ikm, ikm_len);
}

int hkdf_final(hkdf_ctx *hkdf, uint8_t *okm, size_t okm_len) {
  if (okm_len > hkdf_max_length(hkdf->md)) {
    return -1;
  }

  size_t blocks = ((okm_len - 1) / hkdf->hash_len) + 1;

  uint8_t prk[hkdf->hash_len];
  unsigned int ret_len;
  HMAC_Final(&hkdf->prk_ctx, prk, &ret_len);
  HMAC_CTX_cleanup(&hkdf->prk_ctx);

  HMAC_CTX hmac;
  HMAC_CTX_init(&hmac);
  uint8_t data[blocks * hkdf->hash_len];
  for (uint8_t i = 1; i <= blocks; i++) {
    HMAC_Init_ex(&hmac, prk, ret_len, hkdf->md, NULL);
    if (i != 1) {
      HMAC_Update(&hmac, data + ((i - 2) * hkdf->hash_len), hkdf->hash_len);
    }

    HMAC_Update(&hmac, hkdf->info, hkdf->info_len);
    HMAC_Update(&hmac, &i, 1);
    HMAC_Final(&hmac, data + ((i -1) * hkdf->hash_len), &ret_len);
  }
  HMAC_CTX_cleanup(&hmac);

  memcpy(okm, data, okm_len);

  return 0;
}

void hkdf_free(hkdf_ctx *hkdf) {
}

int hkdf(const EVP_MD *md, uint8_t *ikm, size_t ikm_len, uint8_t *salt, size_t salt_len, uint8_t *info, size_t info_len, uint8_t *okm, size_t okm_len) {
  hkdf_ctx hkdf;
  hkdf_init(&hkdf, md, salt, salt_len, info, info_len);
  hkdf_update(&hkdf, ikm, ikm_len);
  int ret = hkdf_final(&hkdf, okm, okm_len);
  hkdf_free(&hkdf);

  return ret;
}

int hkdf_sha256(uint8_t *ikm, size_t ikm_len, uint8_t *salt, size_t salt_len, uint8_t *info, size_t info_len, uint8_t *okm, size_t okm_len) {
  const EVP_MD *md = EVP_sha256();
  return hkdf(md, ikm, ikm_len, salt, salt_len, info, info_len, okm, okm_len);
}
