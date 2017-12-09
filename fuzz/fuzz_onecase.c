#include "ed25519.h"

int fuzz_sign_then_verify(const unsigned char *data, unsigned long long size) {
  int ret = 0;

  public_key_t pub;
  private_key_t priv;
  ret = ed25519_create_keypair(&priv, &pub);
  if (ret == 0) return 1; /* error */

  signature_t sig;
  ed25519_sign(&sig, data, size, &pub, &priv);

  ret = ed25519_verify(&sig, data, size, &pub);
  if (ret == 0)
    return 1; /* invalid signature */
  else
    return 0;
}
